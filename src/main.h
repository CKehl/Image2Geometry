/*
 * main.h
 *
 *  Created on: Jun 2, 2018
 *      Author: Christian Kehl
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

using namespace boost::program_options;

/*
 * executes image masking
 */
void registerImageToGeometry(std::string geometry_path, std::string configuration_path, std::map<std::string, ImageFileDescriptor> imagefile_list, std::vector<cv::Point2f>& object_keypoints, std::vector<cv::Point3f> object_points);
cv::Mat ReadAndMorphMatrix(std::string _matrixpath, double declination);
void StorePose(cv::Mat tvec, cv::Mat rvec, std::string _outpath);
void LevMar_Reimplementation(const CvMat* objectPoints, const CvMat* imagePoints, const CvMat* A, const CvMat* distCoeffs, CvMat* rvec, CvMat* tvec, int useExtrinsicGuess);
bool solvePnP_reimp(cv::InputArray _opoints, cv::InputArray _ipoints, cv::InputArray _cameraMatrix, cv::InputArray _distCoeffs, cv::OutputArray _rvec, cv::OutputArray _tvec, bool useExtrinsicGuess, int flags);

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
