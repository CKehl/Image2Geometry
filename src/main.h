/*
 * main.h
 *
 *  Created on: Jun 23, 2015
 *      Author: christian
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <istream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "opencv_includes.h"
#include "ImagingPrimitives.h"
#include "BoundRenderScene.h"
#include "SyntheticScene.h"
#include "OCVtoDAT.h"
#include "DATtoOCV.h"
#include "OpenCVOSGGlue.h"
#include "ReaderEXIF.h"
#include "ImageFileDescriptor.h"
#include "Rotations.h"
#include "GeometryIntersector.h"
#include "WriterPTS.h"
#include "WriterPT2.h"
#include "WriterCVMatch.h"
#include "AccurateMatcher.h"
#include "RobustMatcher.h"
#include "DiscriminativeColorDescriptor.h"
#include "DCSiftDescriptorExtractor.h"
#include "Circle.h"
#include "CirclePairReader.h"
#include "ConstrainedMatcher.h"
#include "VotingRegionMatcher.h"
#include "OneWayRobustMatcher.h"

#include <boost/program_options.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/version.hpp>
#include <boost/filesystem.hpp>

#include <osg/Point>
#include <osg/Group>
#include <osg/Image>
#include <osg/CullFace>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Shader>
#include <osg/Program>
#include <osg/Uniform>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

//using namespace cv;
//using namespace std;
using namespace boost::program_options;

/*
 * executes image masking
 */
//void mask_image(ImageFileDescriptor files);
//cv::Mat process_image(ImageFileDescriptor files, osg::Node* scene);
//cv::Mat generatePBOImage(ImageFileDescriptor files, osg::Node* scene, CameraConfiguration* cam, cv::Mat _mat);
//cv::Mat generateImage(ImageFileDescriptor files, osg::Node* scene, CameraConfiguration* cam, cv::Mat _mat);
cv::Mat ReadAndMorphMatrix(std::string _matrixpath, double declination);
void StorePose(cv::Mat tvec, cv::Mat rvec, std::string _outpath);
//void DetectFeatureVectors(cv::Mat image, FeatureList* result);
//void DetectDescriptorVectors(cv::Mat image, FeatureList* feature_points, DescriptorList* result);
//void BruteForceMatch(DescriptorList* ref_desc, DescriptorList* syn_desc, MatchList* ref_matches, MatchList* syn_matches);
//void FLANNMatch(DescriptorList* ref_desc, DescriptorList* syn_desc, MatchList* ref_matches, MatchList* syn_matches);
//void kNNMatch(DescriptorList* ref_desc, DescriptorList* syn_desc, MatchList* ref_matches, MatchList* syn_matches, float ratio);
//void SymmetryTestRejection(MatchList* ref_matches, MatchList* syn_matches);
//void ImageScaleRejection(FeatureList* ref_points, FeatureList* syn_points, MatchList* ref_matches, MatchList* syn_matches, cv::Size_<int> imagesize, double scale_fraction);
//void DistanceRefusal(FeatureList* ref_points, FeatureList* syn_points, MatchList* ref_matches, MatchList* syn_matches, double distance_limit);
//void RANSACTest(FeatureList* ref_points, FeatureList* syn_points, MatchList* ref_matches, MatchList* syn_matches, double distance, double confidence, double minInlierRatio);
//void RatioTest(MatchList* ref_matches, MatchList* syn_matches);

//void DoRaycasting(std::vector<cv::Point2f>* syn_points, std::vector<cv::Point3f>* results, CameraConfiguration* camera, osg::Node* scene, cv::Mat view);

class MatchEntry : public cv::DMatch {
public:
	inline MatchEntry() : cv::DMatch() {}
	inline MatchEntry(const cv::DMatch& _in) : cv::DMatch(_in) {}
	inline ~MatchEntry() {}

	inline bool operator==(const MatchEntry& rhs)
	{
		bool result = false;
		if( (queryIdx==rhs.queryIdx) && (trainIdx==rhs.trainIdx) )
			result = true;
		return result;
	}

	inline bool operator!=(const MatchEntry& rhs)
	{
		bool result = true;
		if( (queryIdx==rhs.queryIdx) && (trainIdx==rhs.trainIdx) )
			result = false;
		return result;
	}
    // less is better
    inline bool operator<( const MatchEntry &m ) const
    {
        return distance < m.distance;
    }
};

#endif /* MAIN_H_ */
