/*
 * OpenCVOSGGlue.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: christian
 */

#include "OpenCVOSGGlue.h"

OpenCV_OSG_Glue::OpenCV_OSG_Glue() {
	// TODO Auto-generated constructor stub

}

OpenCV_OSG_Glue::~OpenCV_OSG_Glue() {
	// TODO Auto-generated destructor stub
}

cv::Mat OpenCV_OSG_Glue::convertImage(osg::Image* img)
{
	int w = img->s(), h = img->t(), c = (img->getPixelSizeInBits() / 8);

	uchar* data = new uchar[img->getTotalSizeInBytes()];
	memcpy(data, (img->data()), img->getTotalSizeInBytes());
	//std::cout << "W: " << w << " H: " << h << " D: " << c << std::endl;
	cv::Mat result, rgb;
	if(c<2)
		result = cv::Mat(h, w, CV_8UC1, data);
	else if(c<4)
		result = cv::Mat(h, w, CV_8UC3, data);
	else if(c<5)
		result = cv::Mat(h, w, CV_8UC4, data);
	result.copyTo(rgb);
	cv::cvtColor(rgb,result,CV_RGB2BGR);
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertMatrix(osg::Matrixd* mat)
{
	cv::Mat result = cv::Mat::eye(4,4,CV_64FC1);
	double* data = (double*)(mat->ptr());
	for(int i = 0; i<4; i++)
		for(int j = 0; j<4; j++)
			result.at<double>(i,j) = data[j*4+i];
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertMatrix(osg::Matrixf* mat)
{
	cv::Mat result = cv::Mat::eye(4,4,CV_64FC1);
	float* data = (float*)(mat->ptr());
	for(int i = 0; i<4; i++)
		for(int j = 0; j<4; j++)
			result.at<float>(i,j) = data[j*4+i];
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertVector(osg::Vec2d* vec)
{
	cv::Mat result;
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertVector(osg::Vec2f* vec)
{
	cv::Mat result;
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertVector(osg::Vec3d* vec)
{
	cv::Mat result;
	return result;
}

cv::Mat OpenCV_OSG_Glue::convertVector(osg::Vec3f* vec)
{
	cv::Mat result;
	return result;
}

osg::Vec2f OpenCV_OSG_Glue::convertVector2f(cv::Mat vec)
{
	osg::Vec2f result;
	return result;
}

osg::Vec3f OpenCV_OSG_Glue::convertVector3f(cv::Mat vec)
{
	osg::Vec3f result;
	return result;
}

osg::Vec2d OpenCV_OSG_Glue::convertVector2d(cv::Mat vec)
{
	osg::Vec2d result;
	return result;
}

osg::Vec3d OpenCV_OSG_Glue::convertVector3d(cv::Mat vec)
{
	osg::Vec3d result;
	return result;
}

osg::Matrixf OpenCV_OSG_Glue::convertMatf(cv::Mat mat)
{
	osg::Matrixf result = osg::Matrixf::identity();
	float* data = (float*)(result.ptr());
	for(int i = 0; i<mat.rows; i++)
		for(int j = 0; j<mat.cols; j++)
			data[j*4+i] = mat.at<float>(i,j);
	result.set(data);
#ifdef DEBUG
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
			std::cout << data[j*4+i] << " ";
	    std::cout << std::endl;
	}
#endif
	return result;
}

osg::Matrixd OpenCV_OSG_Glue::convertMatd(cv::Mat mat)
{
	osg::Matrixd result = osg::Matrixd::identity();
	double* data = (double*)(result.ptr());
	for(int i = 0; i<mat.rows; i++)
		for(int j = 0; j<mat.cols; j++)
			data[j*4+i] = mat.at<double>(i,j);
	result.set(data);
#ifdef DEBUG
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
			std::cout << data[j*4+i] << " ";
	    std::cout << std::endl;
	}
#endif
	return result;
}

