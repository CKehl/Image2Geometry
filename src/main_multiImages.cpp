/*
 * main_multiImages.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Christian Kehl
 */

#include "main.h"
	uint feature_method = 0;
	float _gamma = 1.0;
	float _contrast = 1.0;
	float _brightness = 0.0;
	bool wallis = false;
	// === Matcher parameters === //
	/*
	rmatcher.setConfidenceLevel(0.90);
	rmatcher.setMinDistanceToEpipolar(8.0);
	rmatcher.setRatio(0.75);
	*/
	float _confidence = 0.90f;
	float _distance = 8.0f;
	float _ratio = 0.75f;

	/*
	 * SIFT
	 * 3 octaves, contrast threshold 0.04, edge threshold 10, sigma = 1.4
	 * octaves: 3-4 good
	 * contrast threshold - remove jiggling/unstable pounts, 0.02-0.05 good for natural images
	 * edge contrast - remove "doubles" along edges (typical well working: 10)
	 * sigma - gaussian filter kernel size (1.4)
	 */
	int _siftOctaves = 3;
	double _siftContrastThreshold = 0.04;
	double _siftEdgeThreshold = 10;
	double _siftSigma = 1.4;

	/*
	 * SURF
	 * double hessianThreshold, int nOctaves=4, int nOctaveLayers=2, bool extended=true, bool upright=false
	 * hessian values 300-500 good
	 * octaves, layer - more reduce the points, but make them more distinct
	 * extended: false - 64 float vector, true - 128 float vector
	 * upright: false - full orientation computation, true: U-SURF
	 */
	double _surfThreshold = 400;
	int _surfOctaves = 4;
	int _surfLayers = 2;
	bool _surfExtended = true;
	bool _surfUpright = false;

	//int _maxSize=45, int _responseThreshold=30 /*significant*/, int _lineThresholdProjected=10, int _lineThresholdBinarized=8, int _suppressNonmaxSize=5 /*little significance*/
	/*
	 * STAR/CenSurE parameters
	 * optimal: (45,20,14,10,13)
	 */
	int _starMaxSize=45;
	int _starThreshold = 30;
	int _starLineThresholdProj = 10;
	int _starLineThresholdBin = 8;
	int _starNonMaxSupression = 5;

	/*
	 * FREAK parameters
	 */
	int _freak_octaves = 4;
	float _freak_patternsize = 22.0f;

	/*
	 * MSCR parameters
	 */
	int _mscr_delta = 5;
	int _mscr_min_area = 60;
	int _mscr_max_area = 14400;
	double _mscr_max_variation = 0.25;
	double _mscr_min_diversity= 0.2;
	int _mscr_max_evolution = 200;
	double _mscr_area_threshold = 1.01;
	double _mscr_min_margin=0.003;
	int _mscr_edge_blur_size=5;

	/*
	 * FAST parameters
	 */
	int _fastThreshold = 20;
	bool _fastNonMaxSupression = true;

	/*
	 * BRIEF parameter
	 */
	int _briefSize = 32;

	/*
	 * Discriminative Colours parameters
	 */
	int _dcdPatch = 21;
	int _dcdProbs = 25;
	int _dcdScale = 5;
	float _dcdSigma = 21.0/4.0;
	bool _dcdFast = false;
	bool useGammaAdaptation=false;
//#define MONTECARLO


void registerImageToGeometry(std::string geometry_path, std::string configuration_path, std::map<std::string, ImageFileDescriptor> imagefile_list, std::vector<cv::Point2f>& object_keypoints, std::vector<cv::Point3f> object_points) {
	// Load textured geometry from file
#ifdef DEBUG
	std::cout << "Reading node file ..." << std::endl;
#endif
	if(!boost::filesystem::exists(geometry_path))
	{
		std::cout << "Missing input model for optimization - EXITING..." << std::endl;
		exit(1);
	}
	osg::ref_ptr<osg::Group> scene = reinterpret_cast<osg::Group*>(osgDB::readNodeFile(geometry_path));

	/* ====================================================================================================
	 * 		I m a g e   s y n t h e t i s a t i o n - set up (3D virtual) scene and rasterizsation
	 * ==================================================================================================== */
	srand(clock());
	SyntheticScene renderer;
	renderer.setBackgroundColour(osg::Vec4f(0.0f,0.0f,0.0f,1.0f));
	scene->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	scene->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(6.0f), osg::StateAttribute::ON);
	scene->getOrCreateStateSet()->setAttribute(new osg::CullFace(osg::CullFace::BACK));
	// Shaders for gamma or brightness-contrast adaptation
	if(useGammaAdaptation)
	{
		osg::ref_ptr<osg::Program> screenspace = new osg::Program();
		osg::ref_ptr<osg::Shader> sspace_vshader = new osg::Shader(osg::Shader::VERTEX);
		osg::ref_ptr<osg::Shader> sspace_fshader = new osg::Shader(osg::Shader::FRAGMENT);
		sspace_vshader->loadShaderSourceFromFile(geom_base+"shaderGamma.vert");
		//sspace_vshader = osg::Shader::readShaderFile(osg::Shader::VERTEX, geom_base+"shaderGamma.vert");
		sspace_fshader->loadShaderSourceFromFile(geom_base+"shaderGamma.frag");
		//sspace_fshader = osg::Shader::readShaderFile(osg::Shader::FRAGMENT, geom_base+"shaderGamma.frag");
		screenspace->addShader(sspace_vshader);
		screenspace->addShader(sspace_fshader);
		osg::ref_ptr<osg::Uniform> gamma_uniform = new osg::Uniform(osg::Uniform::FLOAT, "gamma");
		gamma_uniform->set(_gamma);
		osg::ref_ptr<osg::Uniform> contrast_uniform = new osg::Uniform(osg::Uniform::FLOAT, "contrast");
		contrast_uniform->set(_contrast);
		osg::ref_ptr<osg::Uniform> brightness_uniform = new osg::Uniform(osg::Uniform::FLOAT, "brightness");
		brightness_uniform->set(_brightness);
		int texUnit = 0;
		osg::ref_ptr<osg::Uniform> sampler_uniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "Texture0");
		sampler_uniform->set(texUnit);
		scene->getOrCreateStateSet()->setAttributeAndModes(screenspace, osg::StateAttribute::ON);
		scene->getOrCreateStateSet()->addUniform(gamma_uniform);
		scene->getOrCreateStateSet()->addUniform(contrast_uniform);
		scene->getOrCreateStateSet()->addUniform(brightness_uniform);
		scene->getOrCreateStateSet()->addUniform(sampler_uniform);
	}
	renderer.SetScene(scene.get());
	/* =====================================================================================================
	 * 							E n d   o f   i m a g e   s y n t h e t i s a t i o n
	 * ===================================================================================================== */

	/* ----------------------------------------------------------------------------------------------------
	 * 										Read camera calibration matrix
	 * ---------------------------------------------------------------------------------------------------- */
	cv::FileStorage fs(configuration_path, cv::FileStorage::READ); // Read the settings
	if (!fs.isOpened())
	{
		std::cout << "Could not open the configuration file: \"" << configuration_path << "\"" << std::endl;
		return -1;
	}
	fs["Camera_Matrix"] >> cameraMatrix;
	fs["Distortion_Coefficients"] >> distCoeffs;
	fs.release();
#ifdef DEBUG
	std::cout << "Camera configuration read." << std::endl;
#endif

	/* ====================================================================================================
	 * 	Here comes the main part: synthetisation for each position-orientation given from sensor files.
	 * 	Then, the mobile photo is loaded from harddisk. Then, feature detection, description and matching
	 * 	are run on both the synthetic (i.e. rendered) image and the photograph. Then, after establishing
	 * 	the 2D feature point correlation, the 2D features in the synthetic image are taken and raycasted
	 * 	through the virtual camera onto the surface geometry (only actual surfaces work - no point sets/clouds
	 * 	/whatever-you-call-point-'geometry' !!). Then, we have a 2D-3D feature point correlation in the
	 * 	synthetic image, and thus (due to previous feature correlation) also a 2D-3D correspondence for
	 * 	photograph feature points.
	 * ==================================================================================================== */
	// TODO: still to be refined, especially by taking out circle constraints
	int img_nr = 0;
	for(std::map<std::string, ImageFileDescriptor>::iterator _iterator = imagefile_list.begin(); _iterator != imagefile_list.end(); _iterator++)
	{
		/*
		 * Generate Scene
		 */
#ifdef DEBUG
		std::cout << "Construct camera configuration from file ..." << std::endl;
#endif
		CameraConfiguration cam;
		// Open Reader, read - if return-value is negative, no file available
		ReaderEXIF exif_reader;
#ifdef DEBUG
#ifndef SILENT
		std::cout << "Camera: " << _iterator->second.exif_file << std::endl;
#endif // SILENT
#endif // DEBUG
		exif_reader.SetFileName(_iterator->second.exif_file);
		if(exif_reader.read() != -1)
		{
			// info from data available
			EXIFdescriptor desc = exif_reader.GetEXIFdescriptor();
			cam.SetFocalLength(double(desc.GetFocalLength()));
			cam.SetCx(double(desc.GetCCDWidth()));
			cam.SetCy(double(desc.GetCCDHeight()));
			cam.SetSX(desc.GetImageWidth());
			cam.SetSY(desc.GetImageHeight());
			cam.SetX0(desc.GetImageWidth()/2.0 + 0.5);
			cam.SetY0(desc.GetImageHeight()/2.0 + 0.5);
#ifdef DEBUG
#ifndef SILENT
			std::cout << desc << std::endl;
#endif // SILENT
#endif // DEBUG
			if(img_nr == 0)
			{
				renderer.SetCameraConfiguration(&cam);
				renderer.Initialize();
			}
		}

#ifdef DEBUG
		std::cout << "Construct artificial scene ..." << std::endl;
#endif

		std::string line;
		double declination_value = 0;
		if((_iterator->second.declination_file!="") && (boost::filesystem::exists(_iterator->second.declination_file)))
		{
#ifndef SILENT
			std::cout << "Read declination." << std::endl;
#endif
			std::ifstream declfile(_iterator->second.declination_file.c_str());
			if(declfile.is_open()==true)
			{
				if(declfile.good()==true)
				{
					std::getline(declfile,line);
					line = boost::trim_copy(line);
					declination_value = double(atof(line.c_str()));
				}
				declfile.close();
			}
		}

		cv::Mat M = ReadAndMorphMatrix(_iterator->second.matrix_file, declination_value);
		//-----------------------------------------------------------------------------------
		//	generate synthetic image
		//-----------------------------------------------------------------------------------
		cv::Mat synthetic_image;
		osg::Matrixd transformation = OpenCV_OSG_Glue::convertMatd(M);
		renderer.SetCameraMatrix(transformation);
		synthetic_image = renderer.GetFrameCV();

		//-----------------------------------------------------------------------------------
		//	read photograph from harddisk
		//-----------------------------------------------------------------------------------
		cv::Mat reference_image;
		cv::Mat ref_img = cv::imread(_iterator->second.image_file);
		cv::undistort(ref_img,reference_image,cameraMatrix, distCoeffs, cv::noArray());
		ref_img.release();

		//-----------------------------------------------------------------------------------
		//	perform uniform histogram equalisation (aka Wallis filter, see [1]) on
		//	synthetic image and photograph.
		//	[1] Wallis, K. F. "Seasonal adjustment and relations between variables",
		//	Journal of the American Statistical Association, 1974, 69(345), p. 18-31
		//-----------------------------------------------------------------------------------
		if(wallis) {
			cv::Mat syn_img;
			//WallisGrayscaleChannelOnly(synthetic_image, syn_img, 3);
			Wallis(synthetic_image, syn_img, 9);
			//WallisGrayscaleChannelOnly(reference_image, ref_img, 3);
			Wallis(reference_image, ref_img, 9);
			syn_img.copyTo(synthetic_image);
			ref_img.copyTo(reference_image);
			syn_img.release();
			ref_img.release();
		}

		//-----------------------------------------------------------------------------------
		//	Starting the image-to-image feature-based registration
		//-----------------------------------------------------------------------------------
#ifdef DEBUG
		std::cout << "Starting registration procedure." << std::endl;
#endif
		cv::Mat img_matches;
		int numKeyPoints = 15000;
		//int numKeyPoints = 0;	// enable this if you want to get ALL features, not capped at 15k
		std::vector<cv::DMatch> matches;
		cv::Ptr<cv::FeatureDetector> detector, detector_additional;
		cv::Ptr<cv::DescriptorExtractor> extractor, extractor_additional;
		cv::Ptr<cv::OpponentColorDescriptorExtractor> OppExtractor;
		cv::Ptr<cv::DescriptorMatcher > matcher, matcher_additional;

		bool _multistage = false;
		bool _bruteforce = false;
		bool _flann = false;

		switch(feature_method)
		{
			case 0: {
				_flann = true;
				//instantiate detector, extractor, matcher
				//Typical parameters:
				//	3 octaves, contrast threshold 0.04, edge threshold 10, sigma = 1.4 [numKeyPoints, 3, 0.04, 10, 1.4]
				//	4 octaves, contrast threshold 0.02, edge threshold 10, sigma = 1.4 [numKeyPoints, 4, 0.02, 10, 1.4]
				detector = new cv::SiftFeatureDetector(numKeyPoints, _siftOctaves, _siftContrastThreshold, _siftEdgeThreshold, _siftSigma);
				extractor = new cv::SiftDescriptorExtractor();
				matcher = new cv::FlannBasedMatcher(new cv::flann::KDTreeIndexParams(4), new cv::flann::SearchParams(64));
				break;
			}
			case 1: {
				_flann = true;
				/*
				 * Constructor: Hessian Response Threshold, # Octaves, # Octave Layers, Extended (128 Responses)/ Simple (32 responses), Upright/not upright
				 */
				detector = new cv::SurfFeatureDetector(_surfThreshold, _surfOctaves, _surfLayers, _surfExtended, _surfUpright);
				extractor = new cv::SurfDescriptorExtractor(_surfThreshold, _surfOctaves, _surfLayers, _surfExtended, _surfUpright);
				matcher = new cv::FlannBasedMatcher(new cv::flann::KDTreeIndexParams(4), new cv::flann::SearchParams(64));
				break;
			}
			case 2: {
				_bruteforce = true;
				//	MSCR (for colour images) experimentally good parameterisation for natural images:
				//	cv::MserFeatureDetector(5,100,30000,0.10,0.239,200,1.029,0.001,5)
				//	alternative: cv::MserFeatureDetector(5,100,30000,0.10,0.02,255,1.01,0.003,3)
				//	cv::BriefDescriptorExtractor(16)
				detector_additional = new cv::MserFeatureDetector(_mscr_delta,_mscr_min_area,_mscr_max_area,_mscr_max_variation,_mscr_min_diversity,_mscr_max_evolution,_mscr_area_threshold,_mscr_min_margin,_mscr_edge_blur_size);
				extractor_additional = new cv::BriefDescriptorExtractor(_briefSize);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true);
				break;
			}
			case 3: {
				/*
				 * int _delta=5, int _min_area=60, int _max_area=14400,
      	  	  	  double _max_variation=0.25, double _min_diversity=.2,
      	  	  	  int _max_evolution=200, double _area_threshold=1.01,
      	  	  	  double _min_margin=0.003, int _edge_blur_size=5
				 */
				_bruteforce = true;
				detector_additional = new cv::MserFeatureDetector(_mscr_delta,_mscr_min_area,_mscr_max_area,_mscr_max_variation,_mscr_min_diversity,_mscr_max_evolution,_mscr_area_threshold,_mscr_min_margin,_mscr_edge_blur_size);
				extractor_additional = new cv::SiftDescriptorExtractor();
				matcher_additional = new cv::BFMatcher(cv::NORM_L2, true);
				break;
			}
			case 4: {
				detector_additional = new cv::SiftFeatureDetector(numKeyPoints, _siftOctaves, _siftContrastThreshold, _siftEdgeThreshold, _siftSigma);
				extractor_additional = new cv::BriefDescriptorExtractor(_briefSize);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true);
				_bruteforce = true;
				break;
			}
			case 5: {
				/*
				 * Standard parameterisation:
				 * table_number = 12, key_size = 20, multi_probe_level = 2
				 * detector = new cv::FastFeatureDetector(20, true);
				 * extractor = new cv::BriefDescriptorExtractor(32);
				 * matcher = new cv::FlannBasedMatcher(new cv::flann::LshIndexParams(6,12,1), new cv::flann::SearchParams(64));
				 */
				_bruteforce = true;
				detector_additional = new cv::FastFeatureDetector(_fastThreshold, _fastNonMaxSupression);
				extractor_additional = new cv::BriefDescriptorExtractor(_briefSize);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true);
				break;
			}
			case 6: {
				// STAR point parameters:
				//	int _maxSize=45
				//	int _responseThreshold=20 /*significant influence*/
				//	int _lineThresholdProjected=14
				//	int _lineThresholdBinarized=10
				//	int _suppressNonmaxSize=13 /*little significance; kernel size*/

				_bruteforce = true;
				detector_additional = new cv::StarFeatureDetector(_starMaxSize,_starThreshold,_starLineThresholdProj,_starLineThresholdBin,_starNonMaxSupression);
				extractor_additional = new cv::BriefDescriptorExtractor(_briefSize);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true);
				break;
			}
			case 7: {
				_bruteforce = true;
				detector_additional = new cv::StarFeatureDetector(_starMaxSize,_starThreshold,_starLineThresholdProj,_starLineThresholdBin,_starNonMaxSupression);
				extractor_additional = new cv::SurfDescriptorExtractor(_surfThreshold,_surfOctaves,_surfLayers,_surfExtended,_surfUpright);
				matcher_additional = new cv::BFMatcher(cv::NORM_L2, true);
				break;
			}
			case 8: {
				_bruteforce = true;
				detector_additional = new cv::MserFeatureDetector(_mscr_delta,_mscr_min_area,_mscr_max_area,_mscr_max_variation,_mscr_min_diversity,_mscr_max_evolution,_mscr_area_threshold,_mscr_min_margin,_mscr_edge_blur_size);
				extractor_additional = new cv::DCSiftDescriptorExtractor(_dcdPatch,_dcdProbs,_dcdScale,_dcdSigma,_dcdFast);
				matcher_additional = new cv::BFMatcher(cv::NORM_L1, true);
				break;
			}
			case 9: {
				_bruteforce = true;
				detector_additional = new cv::SiftFeatureDetector(numKeyPoints, _siftOctaves, _siftContrastThreshold, _siftEdgeThreshold, _siftSigma);
				extractor_additional = new cv::DCSiftDescriptorExtractor(_dcdPatch,_dcdProbs,_dcdScale,_dcdSigma,_dcdFast);
				matcher_additional = new cv::BFMatcher(cv::NORM_L1, true);
				break;
			}
			case 10: {
				_bruteforce = true;
				detector_additional = new cv::SiftFeatureDetector(numKeyPoints, _siftOctaves, _siftContrastThreshold, _siftEdgeThreshold, _siftSigma);
				extractor_additional = new cv::FREAK(true,true,_freak_patternsize, _freak_octaves);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING2, true);
				break;
			}
			case 11: {
				_bruteforce = true;
				detector_additional = new cv::FastFeatureDetector(_fastThreshold, _fastNonMaxSupression);
				extractor_additional = new cv::FREAK(true,true,_freak_patternsize, _freak_octaves);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING2, true);
				break;
			}
			case 12: {
				_bruteforce = true;
				detector_additional = new cv::FastFeatureDetector(_fastThreshold, _fastNonMaxSupression);
				extractor_additional = new cv::SiftDescriptorExtractor();
				matcher_additional = new cv::BFMatcher(cv::NORM_L2, true);
				break;
			}
			case 13: {
				_bruteforce = true;
				detector_additional = new cv::StarFeatureDetector();
				extractor_additional = new cv::SiftDescriptorExtractor();
				matcher_additional = new cv::BFMatcher(cv::NORM_L2, true);
				break;
			}
			case 14: {
				bruteforce = true;
				detector_additional = new cv::OrbFeatureDetector(500, 1.4, 5, 31, 0, 4, cv::ORB::HARRIS_SCORE, 21);
				extractor_additional = new cv::OrbDescriptorExtractor();
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true); // ONLY FOR WTA_K = 2 (std)
				break;
			}
			case 15: {
				/** Constructor
				     * @param orientationNormalized enable orientation normalization
				     * @param scaleNormalized enable scale normalization
				     * @param patternScale scaling of the description pattern - 22.0 std
				     * @param nOctaves number of octaves covered by the detected keypoints
				     * @param selectedPairs (optional) user defined selected pairs
				*/
				bruteforce = true;
				detector_additional = new cv::SiftFeatureDetector(numKeyPoints, _siftOctaves, _siftContrastThreshold, _siftEdgeThreshold, _siftSigma);
				extractor_additional = new cv::FREAK(true, true, _freak_patternsize, _freak_octaves);
				matcher_additional = new cv::BFMatcher(cv::NORM_HAMMING, true);
				break;
			}
			default:
			{
				//instantiate detector, extractor, matcher
				_flann = true;
				detector = new cv::SiftFeatureDetector(numKeyPoints);
				extractor = new cv::SiftDescriptorExtractor();
				matcher = new cv::FlannBasedMatcher(new cv::flann::KDTreeIndexParams(4), new cv::flann::SearchParams(64));
				break;
			}
		}

		std::vector<cv::KeyPoint> syn_keypoints;
		std::vector<cv::KeyPoint> ref_keypoints;
		int num_inliers = 0;


		if(_multistage || _flann)
		{
#ifdef DEBUG
			std::cout << "Using FLANN robust matcher ... kNNmatch." << std::endl;
#endif
			//Instantiate robust matcher
			RobustMatcher rmatcher;
			rmatcher.setConfidenceLevel(_confidence);
			rmatcher.setMinDistanceToEpipolar(_distance);
			rmatcher.setRatio(_ratio);
			rmatcher.setFeatureDetector(detector);
			rmatcher.setDescriptorExtractor(extractor);
			rmatcher.setDescriptorMatcher(matcher);
			rmatcher.match(synthetic_image, reference_image, matches, syn_keypoints, ref_keypoints);
			num_inliers = rmatcher.getNumberOfInliers();
		}

		if(_multistage || _bruteforce)
		{
#ifdef DEBUG
			std::cout << "Using bruteforce accurate matcher ... no kNN." << std::endl;
#endif
			std::vector<cv::KeyPoint> ref_cp, syn_cp;
			std::vector<cv::DMatch> matches_add;
			AccurateMatcher accmatcher;
			accmatcher.setConfidenceLevel(_confidence);
			accmatcher.setMinDistanceToEpipolar(_distance);
			accmatcher.setFeatureDetector(detector_additional);
			if(extractor_additional!=NULL)
				accmatcher.setDescriptorExtractor(extractor_additional);
			else
				accmatcher.setDescriptorExtractorOppColor(OppExtractor);
			accmatcher.setDescriptorMatcher(matcher_additional);
			accmatcher.match(synthetic_image, reference_image, matches_add, syn_cp, ref_cp);
			int ref_offset = ref_keypoints.size(), syn_offset = syn_keypoints.size();
			for(uint i = 0; i < ref_cp.size(); i++)
				ref_keypoints.push_back(ref_cp.at(i));
			for(uint i = 0; i < syn_cp.size(); i++)
				syn_keypoints.push_back(syn_cp.at(i));
			// query = syn, train = ref
			for(std::vector<cv::DMatch>::iterator rit = matches_add.begin(); rit != matches_add.end(); rit++)
			{
				rit->queryIdx+=syn_offset;
				rit->trainIdx+=ref_offset;
			}
			for(uint i = 0; i < matches_add.size(); i++)
				matches.push_back(matches_add.at(i));

			num_inliers = accmatcher.getNumberOfInliers();
		}

		if( (matches.empty()) || (syn_keypoints.empty()) || (ref_keypoints.empty()) )
		{
#ifdef DEBUG
			std::cerr << "No matching features found. Continuing ..." << std::endl;
#endif
			continue;
		}
#ifdef DEBUG
		else
		{
			std::cout << "Features found." << std::endl;
		}
#endif


#ifdef DEBUG
		std::cout << "Writing match images ..." << std::endl;
#ifndef SILENT
		//cv::drawMatches( synthetic_image, syn_keypoints, reference_image, ref_keypoints, matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>() );
		drawMatches(synthetic_image, syn_keypoints, reference_image, ref_keypoints, matches, img_matches,cv::Scalar(255,255,255), cv::Scalar(124,0,99), 7, 2, 4, false);
		cv::imwrite(_iterator->second.temp_file, img_matches);
#endif // SILENT
#endif // DEBUG

		//------------------------------------------------------------------------------------
		//	(2D) Point correlations are determined; now, 2D synthetic keypoints are collected
		//	and then ray-casted on the scene object.
		//------------------------------------------------------------------------------------
#ifdef DEBUG
		std::cout << "Collecting object keypoints ..." << std::endl;
#endif
		//std::vector<cv::Point2f> object_keypoints;
		//std::vector<cv::Point3f> object_points;
		for(uint i = 0; i < matches.size(); i++)
		{
			object_keypoints.push_back(syn_keypoints.at(matches.at(i).queryIdx).pt);
		}
		//-----------------------------------------------------------------------------------
		//	Raycasting 2D features to obtain 3D features
		//-----------------------------------------------------------------------------------
		renderer.clear_points_to_cast();
#ifdef DEBUG
		std::cout << "Raycasting feature points ..." << std::endl;
#ifndef SILENT
		std::cout << "Adding " << object_keypoints.size() << " synthetic 2D image points ..." << std::endl;
#endif
#endif
		cv::Point2f pt;
		for(uint i = 0; i < object_keypoints.size(); i++)
		{
			pt = object_keypoints.at(i);
			renderer.add_point_to_cast(osg::Vec2( pt.x, pt.y ));
		}
		renderer.RaycastIntersections();
#ifdef DEBUG
		std::cout << "Retrieving " << renderer.GetNumberOfIntersections() << " 3D correspondence points ... " << std::endl;
#endif
		object_keypoints.clear();
		osg::Vec3 geom_point;
		cv::Point3f pt3D;
		for(uint i = 0; i < renderer.GetNumberOfIntersections(); i++)
		{
			geom_point = renderer.GetIntersection(i);
			if(geom_point != VOID_INTERSECTION)
			{
				pt3D = cv::Point3f(geom_point.x(), geom_point.y(), geom_point.z());
				object_points.push_back(pt3D);
				object_keypoints.push_back(ref_keypoints.at(matches.at(i).trainIdx).pt);
#ifdef DEBUG
#ifndef SILENT
				std::cout << syn_keypoints.at(matches.at(i).queryIdx).pt << " (syn) => " << ref_keypoints.at(matches.at(i).trainIdx).pt << " (ref) => " << pt3D << std::endl;
#endif
#endif
			}
		}

#ifdef DEBUG
		std::cout << "writing feature points to disk for checking purposes." << std::endl;
		WriterPTS obj_pts_writer;
		obj_pts_writer.write(&object_points, _iterator->second.ptsfile);

		WriterPT2 obj_pt_writer;
		obj_pt_writer.write(&object_keypoints, _iterator->second.pt2file);

		WriterCVMatch obj_cv_writer;
		obj_cv_writer.write(&syn_keypoints, &ref_keypoints, &matches, _iterator->second.cvfile);

		std::string featfile_path = _iterator->second.ptsfile.substr(0, _iterator->second.ptsfile.find_last_of("."))+".feat";
		std::ofstream featfile;
		featfile.open(featfile_path.c_str(), std::ios::out|std::ios::trunc);
		if(featfile.is_open())
		{
			featfile << "# pts ref: " << ref_keypoints.size() << std::endl;
			featfile << "# pts syn: " << syn_keypoints.size() << std::endl;
			featfile << "# corresp: " << object_points.size() << std::endl;
			featfile << "# inliers: " << num_inliers << std::endl;
			featfile << "inlier ratio: " << (float(num_inliers)/float(object_points.size())) << std::endl;
		}
		featfile.close();
#endif
#ifdef DEBUG
		std::cout << "Optimization successful." << std::endl;
		std::cout << "Image " << img_nr << " done." << std::endl;
#endif
		img_nr++;
	}
}

int main(int argc, char* argv[])
{
	std::string out_ext = "png";
	std::string geometry_path;
	std::string input_folder = "";
	std::string configuration_path;
	std::string listfile;
	std::string output_folder = "";
	std::string extension;

	cv::Mat cameraMatrix(3,3,CV_64FC1);
	cv::Mat distCoeffs(5,1,CV_64FC1);

	//bool single_image = true;
	std::map<std::string, ImageFileDescriptor> imagefile_list;

	/* =========================================================================================================
	 * 					S T A R T   O F   I N I T I A L I S A T I O N   S E C T I O N
	 * ========================================================================================================= */
	options_description desc("Allowed options", strlen("Allowed options"));
	desc.add_options()
	    ("help", "produce help message")
	    ("input_geometry", value<std::string>()->required(), "input PLY/OBJ/OSG/IVE file")
	    ("input_folder", value<std::string>()->required(), "input folder (holding photo, declination and exif file)")
	    ("input_list", value<std::string>()->required(), "naming all relevant filenames")
	    ("input_configuration", value<std::string>()->required(), "input configuration file")
	    ("output_folder", value<std::string>()->required(), "output folder (holding matches, matrices, matching image)")
	    ("method", value<int>(),"feature detection and description method; SIFT = 0, SURF = 1, ORB = 2, MSCR = 3, BRISK/FREAK = 4, STAR/FREAK = 5, BRISK = 6, FAST/BRIEF = 7, 8 = MSCR_DCSIFT, 9 = SIFT+MSCR DCSIFT")
	    ("confidence", value<float>(), "demanded confidence of the matching")
	    ("distance", value<float>(), "demanded maximum epipolar distance to the epiline of the homography matrix when matching")
	    ("ratio", value<float>(), "Ratio distance between best and 2nd-best match that has to be exceeded (both matches must be reasonably close)")
	    ("gamma", value<float>(), "optional gamma adaptation for screenspace rendering")
	    ("contrast",value<float>(), "optional contrast adaptation")
	    ("brightness", value<float>(), "optional brightness adaptation")
	    ("surf_thr", value<double>(), "SURF hessian threshold")
	    ("surf_oct", value<int>(), "SURF number of octaves")
	    ("surf_lyr", value<int>(), "SURF number of layers per octave")
	    ("surf_ext", value<int>(), "SURF extended: yes (1), no (0), default: yes")
	    ("usurf", value<int>(), "Upright SURF: yes (1), no(0), default: no")
	    ("psize", value<float>(), "FREAK/BRISK option - pattern size")
	    ("octaves", value<int>(), "FREAK/BRISK option - octaves")
	    ("brisk_thr", value<int>(), "BRISK option - threshold")
	    ("fast_thr", value<int>(), "FAST threshold")
	    ("fast_spr", value<int>(), "FAST - use non-max supression (1) or not (0); default: 1")
	    ("star_size", value<int>(), "STAR maximum filter size")
	    ("star_thr", value<int>(), "STAR response threshold")
	    ("star_line1", value<int>(), "STAR projected line threshold")
	    ("star_line2", value<int>(), "STAR binarized line threshold")
	    ("star_spr", value<int>(), "STAR non-maximum supression threshold")
	    ("brief_size", value<int>(), "BRIEF descriptor size")
	    ("mscr_d",value<int>(), "MSCR option - delta")
	    ("mscr_mnarea", value<int>(), "MSCR option - min area")
	    ("mscr_mxarea", value<int>(), "MSCR option - max area")
	    ("mscr_mxvar", value<double>(), "MSCR option - max variability")
	    ("mscr_mndiv", value<double>(), "MSCR option - min diversity")
	    ("mscr_mxevo", value<int>(), "MSCR option - max evolution")
	    ("mscr_thr", value<double>(), "MSCR option - area threshold")
	    ("mscr_mnmarg", value<double>(), "MSCR option - min margin")
	    ("mscr_edge", value<int>(), "MSCR option - edge blur size")
	    ("dcd_patch", value<int>(), "DC Descriptor - patchsize")
	    ("dcd_probs", value<int>(), "DC Descriptor - probs/descriptor size (11,25 and 50 allowed)")
	    ("dcd_scale", value<float>(), "DC Descriptor - feature region scale factor")
	    ("dcd_sigma", value<float>(), "DC Descriptor - filter sigma")
	    ("dcd_fast", value<int>(), "DC Descriptor - fast computation on (1) or off (0)")
	    ("voting", value<int>(), "switches on voting")
	    ("constraints", value<int>(), "switch for using constraints")
	    ("wallis", value<int>(), "use (>=1) or not use (0 or nothing) the wallis filter");

	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	std::string geom_base = "";

	if (vm.count("input_geometry"))
	{
		geometry_path = vm["input_geometry"].as<std::string>();
#ifndef SILENT
		std::cout << "Input file: " << geometry_path << std::endl;
#endif

		uint slashpos = geometry_path.find_last_of(".");
		extension = geometry_path.substr(slashpos+1, geometry_path.npos);
		geom_base = geometry_path.substr(0, geometry_path.find_last_of("/")+1);
		if( (extension.find("ply",0) == extension.npos) && (extension.find("osg",0) == extension.npos) && (extension.find("ive",0) == extension.npos) && (extension.find("obj",0) == extension.npos) )
		{
			std::cout << "Input file has no supported extension. Wrong Format. Existing..." << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "No input file given. Exiting ..." << std::endl;
		return 1;
	}

	if(vm.count("input_folder"))
	{
		input_folder = vm["input_folder"].as<std::string>();
		if(input_folder.find_last_of("/")!=(input_folder.npos-1))
			input_folder+="/";
#ifndef SILENT
		std::cout << "Input folder: " << input_folder << std::endl;
#endif
	}

	if(vm.count("output_folder"))
	{
		output_folder = vm["output_folder"].as<std::string>();
		if(output_folder.find_last_of("/")!=(output_folder.npos-1))
			output_folder+="/";
#ifndef SILENT
		std::cout << "Output folder: " << output_folder << std::endl;
#endif
	}

	if(vm.count("input_list"))
	{
		listfile = vm["input_list"].as<std::string>();
#ifndef SILENT
		std::cout << "list file: " << input_folder+listfile << std::endl;
#endif

		std::string listfile_path = input_folder+listfile;
		std::string line;
		std::ifstream ptsfile(listfile_path.c_str());
		std::vector<std::string> strs; strs.reserve(2);
		if(ptsfile.is_open()==true)
		{

			//while(! ptsfile.eof())
			std::getline(ptsfile,line);
			while(ptsfile.good()==true)
			{
				boost::split(strs, line, boost::is_any_of(" "));
				std::string base_name;
				if(strs.size() > 0)
				{
					uint dotpos = strs[0].find_last_of(".");
					base_name = strs[0].substr(0,dotpos);

					imagefile_list[base_name] = ImageFileDescriptor();
					std::string fext = "";
					for(uint k = 0; k < strs.size(); k++)
					{
						uint dotpos = strs[k].find_last_of(".");
						fext = strs[k].substr(dotpos+1, strs[k].size());
						if( (fext == "dat") && (strs[k].find("vecs")==strs[k].npos) && (strs[k].find("declination")==strs[k].npos) )
						{
							//matrix file
							imagefile_list[base_name].matrix_file = input_folder + strs[k];
							//std::cout << "have matrix file" << std::endl;
							//break;
						}
						if( (fext == "dat") && (strs[k].find("declination")!=strs[k].npos) )
						{
							//vector file
							imagefile_list[base_name].declination_file = input_folder + strs[k];
							//std::cout << "have declination file" << std::endl;
							//break;
						}
						if((fext=="tif") || (fext=="jpg") || (fext=="png") || (fext=="bmp"))
						{
							//image file
							imagefile_list[base_name].image_file = input_folder + strs[k];
							imagefile_list[base_name].temp_file = output_folder + base_name +"_match."+fext;
							//break;
						}
						if(fext=="exif")
						{
							//exif file
							imagefile_list[base_name].exif_file = input_folder + strs[k];
							//break;
						}
					}
					imagefile_list[base_name].ptsfile = output_folder + base_name + ".pts";
					imagefile_list[base_name].pt2file = output_folder + base_name + ".match";
					imagefile_list[base_name].cvfile =  output_folder + base_name + ".cv";
					imagefile_list[base_name].circle_file = input_folder + base_name + "_circle" + ".match";

					std::getline(ptsfile,line);
				}
				if(ptsfile.eof()==true)
					break;

				strs.clear();
				strs.reserve(2);

			}
			ptsfile.close();
			strs.clear();
		}
	}

	if(vm.count("input_configuration"))
	{
		configuration_path = vm["input_configuration"].as<std::string>();
#ifndef SILENT
		std::cout << "Camera configuration: " << configuration_path << std::endl;
#endif
	}

	if(vm.count("method"))
	{
		feature_method = uint(vm["method"].as<int>());
	}

	if(vm.count("confidence"))
	{
		_confidence = vm["confidence"].as<float>();
	}

	if(vm.count("distance"))
	{
		_distance = vm["distance"].as<float>();
	}

	if(vm.count("ratio"))
	{
		_ratio = vm["ratio"].as<float>();
	}

	if(vm.count("gamma"))
	{
		_gamma = vm["gamma"].as<float>();
	}

	if(vm.count("contrast"))
	{
		_contrast = vm["contrast"].as<float>();
	}

	if(vm.count("brightness"))
	{
		_brightness = vm["brightness"].as<float>();
	}

	if(vm.count("wallis"))
	{
		int v = vm["wallis"].as<int>();
		if(v>0)
			wallis = true;
		else
			wallis = false;
	}

	if(vm.count("surf_thr"))
		_surfThreshold = vm["surf_thr"].as<double>();
	if(vm.count("surf_oct"))
		_surfOctaves = vm["surf_oct"].as<int>();
	if(vm.count("surf_lyr"))
		_surfLayers = vm["surf_lyr"].as<int>();
	if(vm.count("surf_ext") && (vm["surf_ext"].as<int>()==0))
		_surfExtended = false;
	else
		_surfExtended = true;
	if(vm.count("usurf") && (vm["usurf"].as<int>()>0))
		_surfUpright = true;
	else
		_surfUpright = false;

	/*
	 * BRISK/FREAK
	 */
	if(vm.count("psize"))
	{
		_freak_patternsize = vm["psize"].as<float>();
	}

	if(vm.count("octaves"))
	{
		_freak_octaves = vm["octaves"].as<int>();
	}

	if(vm.count("fast_thr"))
		_fastThreshold = vm["fast_thr"].as<int>();
	if((vm.count("fast_spr")) && (vm["fast_spr"].as<int>() > 0))
		_fastNonMaxSupression = true;
	else if((vm.count("fast_spr")) && (vm["fast_spr"].as<int>() == 0))
		_fastNonMaxSupression = false;

	if(vm.count("star_size"))
		_starMaxSize = vm["star_size"].as<int>();
	if(vm.count("star_thr"))
		_starThreshold = vm["star_thr"].as<int>();
	if(vm.count("star_line1"))
		_starLineThresholdProj = vm["star_line1"].as<int>();
	if(vm.count("star_line2"))
		_starLineThresholdBin = vm["star_line2"].as<int>();
	if(vm.count("star_spr"))
		_starNonMaxSupression = vm["star_spr"].as<int>();

	if(vm.count("brief_size"))
		_briefSize = vm["brief_size"].as<int>();

	if(vm.count("mscr_d"))
		_mscr_delta = vm["mscr_d"].as<int>();
	if(vm.count("mscr_mnarea"))
		_mscr_min_area = vm["mscr_mnarea"].as<int>();
	if(vm.count("mscr_mxarea"))
		_mscr_max_area = vm["mscr_mxarea"].as<int>();
	if(vm.count("mscr_mxvar"))
		_mscr_max_variation = vm["mscr_mxvar"].as<double>();
	if(vm.count("mscr_mndiv"))
		_mscr_min_diversity = vm["mscr_mndiv"].as<double>();
	if(vm.count("mscr_mxevo"))
		_mscr_max_evolution = vm["mscr_mxevo"].as<int>();
	if(vm.count("mscr_thr"))
		_mscr_area_threshold = vm["mscr_thr"].as<double>();
	if(vm.count("mscr_mnmarg"))
		_mscr_min_margin = vm["mscr_mnmarg"].as<double>();
	if(vm.count("mscr_edge"))
		_mscr_edge_blur_size = vm["mscr_edge"].as<int>();

	if(vm.count("dcd_patch"))
		_dcdPatch = vm["dcd_patch"].as<int>();
	if(vm.count("dcd_probs"))
		_dcdProbs = vm["dcd_probs"].as<int>();
	if(vm.count("dcd_scale"))
		_dcdScale = vm["dcd_scale"].as<int>();
    if(vm.count("dcd_sigma"))
    	_dcdSigma = vm["dcd_sigma"].as<float>();
	if((vm.count("dcd_fast")) && (vm["dcd_fast"].as<int>() > 0))
		_dcdFast = true;
	if(vm.count("gamma")||vm.count("contrast")||vm.count("brightness")) {
		useGammaAdaptation=true;
	}
/* =========================================================================================================
 * 						E N D   O F   I N I T I A L I S A T I O N   S E C T I O N
 * ========================================================================================================= */

	std::vector<cv::Point2f> image_keypoints;
	std::vector<cv::Point3f> object_keypoints;
	registerImageToGeometry(geometry_path, configuration_path, imagefile_list, image_keypoints, object_keypoints);








	return 0;
}

cv::Mat ReadAndMorphMatrix(std::string _matrixpath, double declination)
{
	/*
	 * Composing TR vectors
	 */
#ifdef DEBUG
	std::cout << "Read initial matrix data from file ..." << std::endl;
#endif
	cv::Mat T = cv::Mat::zeros(3,1,CV_64FC1), R = cv::Mat::eye(3,3,CV_64FC1), Rvec = cv::Mat::zeros(3,1,CV_64FC1);
	DATtoOCV matrix_reader;
	cv::Mat pose = cv::Mat::eye(4,4,CV_64FC1);
	matrix_reader.SetFileName(_matrixpath);
	matrix_reader.read();
	pose = matrix_reader.GetMatrix();
	cv::Mat pose_tr = cv::Mat::eye(4,4,pose.type());
	pose.copyTo(pose_tr);
	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<3; n++)
		{
			R.at<double>(m,n) = pose_tr.at<double>(m,n);
		}
		T.at<double>(m,0) = pose_tr.at<double>(m,3);
	}

#ifdef MONTECARLO
	/*
	 * for testing: vary input (cause input is perfect) => monte carlo study
	 */
#ifdef DEBUG
	std::cout << "Monte Carlo modification of matrix ..." << std::endl;
#endif // DEBUG
	cv::Mat euler = RotationsCV::EulerFromMatrix(R); // giving phi-theta-psi in z-x-z coord transform
	//srand(clock());
	euler.at<double>(0,0) += (-(5.0*M_PI)/180.0) + ( (rand()/RAND_MAX) * ((10.0*M_PI)/180.0) );
	euler.at<double>(1,0) += (-(5.0*M_PI)/180.0) + ( (rand()/RAND_MAX) * ((10.0*M_PI)/180.0) );
	euler.at<double>(2,0) += (-(5.0*M_PI)/180.0) + ( (rand()/RAND_MAX) * ((10.0*M_PI)/180.0) ) - osg::DegreesToRadians(0.2677055299282074);

	R = RotationsCV::MatrixFromEuler(euler);
	T.at<double>(0,0) += (-1.5 + (rand()/RAND_MAX)*3.0);
	T.at<double>(1,0) += (-1.5 + (rand()/RAND_MAX)*3.0);
	T.at<double>(2,0) += (-1.5 + (rand()/RAND_MAX)*3.0);
#else
	/*
	 * TODO: Insert here true declination
	 */
	double edata[] = {0,0,-osg::DegreesToRadians(declination)};
	cv::Mat declination_vector = cv::Mat(3,1,CV_64FC1, edata);
	cv::Mat declination_matrix = RotationsCV::MatrixFromEuler(declination_vector);
	R = declination_matrix * R;
#endif
	cv::Rodrigues(R, Rvec);

#ifdef DEBUG
	std::cout << "Declination matrix:" << std::endl;
	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<3; n++)
		{
			std::cout << declination_matrix.at<double>(m,n) << " ";
		}
		std::cout << std::endl;
	}
#endif


	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<3; n++)
		{
			pose.at<double>(m,n) = R.at<double>(m,n);
		}
		pose.at<double>(m,3) = T.at<double>(m,0);
	}

#ifndef SILENT
	std::cout << "Initial pose:" << std::endl;
	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<4; n++)
		{
			std::cout << pose.at<double>(m,n) << " ";
		}
		std::cout << std::endl;
	}
#endif


	return pose;
}

void StorePose(cv::Mat tvec, cv::Mat rvec, std::string _outpath)
{
	cv::Mat T = cv::Mat::zeros(3,1,CV_64FC1), R = cv::Mat::eye(3,3,CV_64FC1);
	cv::Mat pose = cv::Mat::eye(4,4,CV_64FC1);
	cv::Rodrigues(rvec, R);
	T = tvec;
	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<3; n++)
		{
			pose.at<double>(m,n) = R.at<double>(m,n);
		}
		pose.at<double>(m,3) = T.at<double>(m,0);
	}

#ifndef SILENT
	std::cout << "Final pose:" << std::endl;
	for(int m = 0; m<3; m++)
	{
		for(int n = 0; n<4; n++)
		{
			std::cout << pose.at<double>(m,n) << " ";
		}
		std::cout << std::endl;
	}
#endif
}



