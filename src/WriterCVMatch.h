/*
 * WriterCVMatch.h
 *
 *  Created on: Dec 17, 2015
 *      Author: christian
 */

#ifndef WRITERCVMATCH_H_
#define WRITERCVMATCH_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <osg/Vec2>
#include "opencv_includes.h"

class WriterCVMatch {
public:
	WriterCVMatch();
	virtual ~WriterCVMatch();
	//void write(std::vector<osg::Vec2>* points, std::string filename);
	//void write(std::vector<cv::Point2f>* points, std::string filename);
	void write(std::vector<cv::KeyPoint>* points_syn, std::vector<cv::KeyPoint>* points_real, std::vector<cv::DMatch>* matches, std::string filename);
};

#endif /* WRITERCVMATCH_H_ */
