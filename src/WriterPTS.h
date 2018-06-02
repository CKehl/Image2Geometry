/*
 * WriterVTK.h
 *
 *  Created on: 30 may 2013
 *      Author: christian
 */

#ifndef WRITERPTS_H_
#define WRITERPTS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <osg/Vec3>
#include "opencv_includes.h"





class WriterPTS {
public:
	WriterPTS();
	virtual ~WriterPTS();
	void write(std::vector<osg::Vec3>* points, std::string filename);
	void write(std::vector<cv::Point3f>* points, std::string filename);

};

#endif /* WRITERPTS_H_ */
