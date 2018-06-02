/*
 * OpenCVOSGGlue.h
 *
 *  Created on: Jun 28, 2015
 *      Author: christian
 */

#ifndef OPENCVOSGGLUE_H_
#define OPENCVOSGGLUE_H_

#include "opencv_includes.h"
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include <osg/Matrixf>
#include <osg/Image>

class OpenCV_OSG_Glue {
public:
	OpenCV_OSG_Glue();
	virtual ~OpenCV_OSG_Glue();

	static cv::Mat convertImage(osg::Image* img);
	static cv::Mat convertMatrix(osg::Matrixd* mat);
	static cv::Mat convertMatrix(osg::Matrixf* mat);
	static cv::Mat convertVector(osg::Vec2d* vec);
	static cv::Mat convertVector(osg::Vec2f* vec);
	static cv::Mat convertVector(osg::Vec3d* vec);
	static cv::Mat convertVector(osg::Vec3f* vec);
	static osg::Vec2f convertVector2f(cv::Mat vec);
	static osg::Vec3f convertVector3f(cv::Mat vec);
	static osg::Vec2d convertVector2d(cv::Mat vec);
	static osg::Vec3d convertVector3d(cv::Mat vec);
	static osg::Matrixf convertMatf(cv::Mat mat);
	static osg::Matrixd convertMatd(cv::Mat mat);
};

inline size_t sizeOf(CvMat _inmat)
{
	size_t result = 0;
	switch(CV_MAT_TYPE(_inmat.type))
	{
	case CV_32FC1:
		result = sizeof(float);
		break;
	case CV_64FC1:
		result = sizeof(double);
		break;
	case CV_8UC1:
		result = sizeof(unsigned char);
		break;
	case CV_32SC1:
		result = sizeof(short);
		break;
	default:
		result = 4;
		break;
	}
	return result;
}

#endif /* OPENCVOSGGLUE_H_ */
