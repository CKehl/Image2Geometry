/*
 * opencv_includes.h
 *
 *  Created on: May 25, 2015
 *      Author: christian
 */

#ifndef OPENCV_INCLUDES_H_
#define OPENCV_INCLUDES_H_

#include <opencv2/core/core.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/internal.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
//#include <opencv2/calib3d/>
//#include <opencv2/calib3d/epnp.h>
//#include <opencv2/calib3d/p3p.h>
//#include <cvconfig.h>
#include <opencv2/photo/photo.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv/cxcore.h>
#ifdef HAVE_TEGRA_OPTIMIZATION
#include "opencv2/features2d/features2d_tegra.hpp"
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

inline std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

inline double sq (double a) {return a*a;}

inline bool CompareResponse(const cv::KeyPoint& first, const cv::KeyPoint& second)
{
	if(first.response < second.response)
		return true;
	else
		return false;
}

inline bool CompareQueryID(const cv::DMatch& first, const cv::DMatch& second)
{
	if(first.queryIdx < second.queryIdx)
		return true;
	else
		return false;
}

inline bool CompareTrainID(const cv::DMatch& first, const cv::DMatch& second)
{
	if(first.trainIdx < second.trainIdx)
		return true;
	else
		return false;
}


#include <vector>
inline void drawMatches(const cv::Mat& img1, const std::vector<cv::KeyPoint>& keypoints1, const cv::Mat& img2, const std::vector<cv::KeyPoint>& keypoints2, const std::vector<cv::DMatch>& matches1to2, cv::Mat& outImg, const cv::Scalar& matchColor, const cv::Scalar& otherColor, int ptRadius, int ptThickness , int lineSize, bool showAllPoints = true)
{
	cv::Size sz1 = img1.size();
	cv::Size sz2 = img2.size();
	cv::Mat(sz1.height, sz1.width+sz2.width, CV_8UC3).copyTo(outImg);
	cv::Mat left(outImg, cv::Rect(0, 0, sz1.width, sz1.height));
	img1.copyTo(left);
    cv::Mat right(outImg, cv::Rect(sz1.width, 0, sz2.width, sz2.height));
    img2.copyTo(right);

    cv::Point2f tPoint;
    if(showAllPoints)
    {
		//im3.adjustROI(0, 0, -sz1.width, sz2.width);
		for(uint i = 0; i < keypoints1.size(); i++)
		{
			cv::circle(outImg, keypoints1.at(i).pt, ptRadius, otherColor,ptThickness, CV_AA, 0);
		}
		//im3.adjustROI(0, 0, sz1.width, 0);
		for(uint i = 0; i < keypoints2.size(); i++)
		{
			tPoint = keypoints2.at(i).pt;
			tPoint.x+=float(sz1.width);
			cv::circle(outImg, tPoint, ptRadius, otherColor,ptThickness, CV_AA, 0);
		}
    }

	cv::Point2f tOP;
	for(uint i = 0; i < matches1to2.size(); i++)
	{
		tOP = keypoints1.at(matches1to2.at(i).queryIdx).pt;
		tPoint = keypoints2.at(matches1to2.at(i).trainIdx).pt;
		tPoint.x+=float(sz1.width);
		cv::circle(outImg, tOP, ptRadius, matchColor, -1, CV_AA, 0);
		cv::circle(outImg, tPoint, ptRadius, matchColor, -1, CV_AA, 0);
		cv::line(outImg, tOP, tPoint, matchColor, lineSize, CV_AA, 0);
	}

}

inline cv::Vec3b getClampedValue(const cv::Mat& img, long x, long y, long width, long height)
{
	cv::Vec3b result = cv::Vec3b(0,0,0);
	if(width==-1)
		width = img.size().width;
	if(height==-1)
		height = img.size().height;
	if((x>0) && (x<width) && (y>0) && (y<height))
		result = img.at<cv::Vec3b>(y,x);
	return result;
}

inline void WallisGrayscaleChannelOnly(const cv::Mat& imgIn, cv::Mat& outImg, int kernelSize, float targetStDev = 50.0f, float targetMean = 256.0f, float alfa = 0.0f, float limit = 10.0f) {
	cv::Mat ycrcbIn = cv::Mat::zeros(imgIn.size(), CV_8UC3);
	cv::Mat ycrcbOut = cv::Mat::zeros(imgIn.size(), CV_8UC3);
	cv::Mat(imgIn.size().height, imgIn.size().width, CV_8UC3).copyTo(outImg);
	cv::cvtColor(imgIn, ycrcbIn, CV_BGR2YCrCb);
	/*
	 * Original Wallis - just on Y-channel
	 */
	cv::Vec3b pix, sout;
	long half = (kernelSize - 1) / 2;
	long w = imgIn.size().width, h = imgIn.size().height;
	float mY, stdY;
	long c,r;
	long xt, yt;
	//int cg = 1; // Wallis standard value
	//float b = 1.5; // Wallis standard value
	//float r1, r0; // Wallis shift and scale parameters
	int size = kernelSize*kernelSize;
	long c_start, c_end, r_start, r_end;
	for (long x = 0; x < w; x++){
	  for (long y = 0; y < h; y++){
		// compute statistics
	    mY=0;
	    c_start = x - half; r_start = y - half;
	    c_end = x + half; r_end = y + half;
	    for (c = c_start; c < c_end; c++){
	    	for (r = r_start; r < r_end; r++){
	    	  pix = getClampedValue(ycrcbIn, c,r,w,h);
	    	  mY += pix.val[0];
	    	}
	    }
	    mY = mY / size;
	    stdY=0;
	    for (c = c_start; c < c_end; c++){
	      for (r = r_start; r < r_end; r++){
	    	  pix = getClampedValue(ycrcbIn, c,r,w,h);
	    	  stdY += sq(pix.val[0]-mY);
	      }
	    }
	    stdY = sqrt(stdY / size);

	    //Calc new values
	    xt = x; yt = y;
	    pix = ycrcbIn.at<cv::Vec3b>(yt,xt);

	    //r1 = cg * to_dev / (cg * stdB + to_dev / cg);
	    //r0 = b * to_av + (1 - b - r1) * mB;
	    //sout.val[0] = pixB.val[0] * r1 + r0 ;
	    // HIPS implementation
	    if(int(targetMean)==256)
	    	sout.val[0] = alfa * pix.val[0] + (1-alfa) * mY + (pix.val[0]-mY) * targetStDev / (targetStDev/limit+stdY);
	    else
	    	sout.val[0] = alfa * targetMean + (1-alfa) * mY + (pix.val[0]-mY) * targetStDev / (targetStDev/limit+stdY);

	    sout.val[1] = pix.val[1];
	    sout.val[2] = pix.val[2];
	    // Write new output value
	    ycrcbOut.at<cv::Vec3b>(y, x) = sout;
	  }
	}

	cv::cvtColor(ycrcbOut, outImg, CV_YCrCb2BGR);
	ycrcbIn.release();
	ycrcbOut.release();
}

inline void Wallis(const cv::Mat& imgIn, cv::Mat& outImg, int kernelSize, float targetStDev = 50.0f, float targetMean = 256.0f, float alfa = 0.0f, float limit = 10.0f) {
	cv::Mat(imgIn.size().height, imgIn.size().width, CV_8UC3).copyTo(outImg);
	//CvScalar pixR, pixB, pixG, sout;
	cv::Vec3b pix, sout;

	long half = (kernelSize - 1) / 2;
	//long x_end = imgIn.size().width - kernelSize;
	//long y_end = imgIn.size().height - kernelSize;
	long w = imgIn.size().width, h = imgIn.size().height;
	float mR, mG, mB, stdR, stdG, stdB;
	long c,r;
	long xt, yt;
	//int cg = 1; // Wallis standard value
	//float b = 1.5; // Wallis standard value
	//float r1, r0; // Wallis shift and scale parameters
	int size = kernelSize*kernelSize;
	long c_start, c_end, r_start, r_end;
	//for (long x = 0; x < x_end; x++){
	//  for (long y = 0; y < y_end; y++){
	for (long x = 0; x < w; x++){
	  for (long y = 0; y < h; y++){
		// compute statistics
	    mR=mG=mB=0;
	    c_start = x - half; r_start = y - half;
	    c_end = x + half; r_end = y + half;
	    //c_end = x + (kernelSize - 1); r_end = y + kernelSize - 1;
	    //for (c = x; c < c_end; c++){
	    //  for (r = y; r < r_end; r++){
	    for (c = c_start; c < c_end; c++){
	    	for (r = r_start; r < r_end; r++){
	    	  //imgIn.at<cv::Vec3b>(r,c).val[0];
	    	  //pix = imgIn.at<cv::Vec3b>(r,c);
	    	  pix = getClampedValue(imgIn, c,r,w,h);
	    	  mR += pix.val[2];
	    	  mG += pix.val[1];
	    	  mB += pix.val[0];
	    	}
	    }
	    mR = mR / size;
	    mG = mG / size;
	    mB = mB / size;
	    stdR=stdB=stdG=0;
	    //for (c = x; c < c_end; c++){
	    //  for (r = y; r < r_end; r++){
	    for (c = c_start; c < c_end; c++){
	      for (r = r_start; r < r_end; r++){
	    	  //pix = imgIn.at<cv::Vec3b>(r,c);
	    	  pix = getClampedValue(imgIn, c,r,w,h);
	    	  stdR += sq(pix.val[2]-mR);
	    	  stdG += sq(pix.val[1]-mG);
	    	  stdB += sq(pix.val[0]-mB);
	      }
	    }
	    stdB = sqrt(stdB / size);
	    stdR = sqrt(stdR / size);
	    stdG = sqrt(stdG / size);

	    //Calc new values
	    //xt = x+half+1; yt = y+half+1;
	    //xt = x+half; yt = y+half;
	    xt = x; yt = y;
	    pix = imgIn.at<cv::Vec3b>(yt,xt);

	    //r1 = cg * to_dev / (cg * stdB + to_dev / cg);
	    //r0 = b * to_av + (1 - b - r1) * mB;
	    //sout.val[0] = pixB.val[0] * r1 + r0 ;
	    // HIPS implementation
	    if(int(targetMean)==256)
	    	sout.val[0] = alfa * pix.val[0] + (1-alfa) * mB + (pix.val[0]-mB) * targetStDev / (targetStDev/limit+stdB);
	    else
	    	sout.val[0] = alfa * targetMean + (1-alfa) * mB + (pix.val[0]-mB) * targetStDev / (targetStDev/limit+stdB);


	    //r1 = cg * to_dev / (cg * stdG + to_dev / cg);
	    //r0 = b * to_av + (1 - b - r1) * mG;
	    //sout.val[1] = pixG.val[0] * r1 + r0 ;
	    // HIPS implementation
	    if(int(targetMean)==256)
	    	sout.val[1] = alfa * pix.val[1] + (1-alfa) * mG + (pix.val[1]-mG) * targetStDev / (targetStDev/limit+stdG);
	    else
	    	sout.val[1] = alfa * targetMean + (1-alfa) * mG + (pix.val[1]-mG) * targetStDev / (targetStDev/limit+stdG);

	    //r1 = cg * to_dev / (cg * stdR + to_dev / cg);
	    //r0 = b * to_av + (1 - b - r1) * mR;
	    //sout.val[2] = pixR.val[0] * r1 + r0 ;
	    // HIPS implementation
	    if(int(targetMean)==256)
	    	sout.val[2] = alfa * pix.val[2] + (1-alfa) * mR + (pix.val[2]-mR) * targetStDev / (targetStDev/limit+stdR);
	    else
	    	sout.val[2] = alfa * targetMean + (1-alfa) * mR + (pix.val[2]-mR) * targetStDev / (targetStDev/limit+stdR);

	    // Write new output value
	    //cvSet2D(out, y+half+1, x+half+1, sout);
	    //outImg.at<cv::Vec3b>(y+half+1, x+half+1) = sout;
	    outImg.at<cv::Vec3b>(y, x) = sout;
	  }
#ifdef DEBUG
	  fprintf(stderr,"\b\b\b\b\b\b\b\b\b%4ld\\%4ld",x+1,w);
#endif /* DEBUG */
	}
}



typedef cv::KeyPoint Feature;
//typedef cv::Mat FeatureDescriptor;
typedef std::vector<Feature> FeatureList;
//typedef std::vector<FeatureDescriptor> DescriptorList;
typedef cv::Mat DescriptorList;
typedef std::vector<cv::DMatch> MatchList;

#endif /* OPENCV_INCLUDES_H_ */
