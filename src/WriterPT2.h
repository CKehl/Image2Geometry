/*
 * WriterPT2.h
 *
 *  Created on: Jul 24, 2015
 *      Author: christian
 */

#ifndef WRITERPT2_H_
#define WRITERPT2_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <osg/Vec2>
#include "opencv_includes.h"

class WriterPT2 {
public:
	WriterPT2();
	virtual ~WriterPT2();
	void write(std::vector<osg::Vec2>* points, std::string filename);
	void write(std::vector<cv::Point2f>* points, std::string filename);
};

#endif /* WRITERPT2_H_ */
