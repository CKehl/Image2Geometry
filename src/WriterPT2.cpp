/*
 * WriterPT2.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: christian
 */

#include "WriterPT2.h"

WriterPT2::WriterPT2() {
	// TODO Auto-generated constructor stub

}

WriterPT2::~WriterPT2() {
	// TODO Auto-generated destructor stub
}

void WriterPT2::write(std::vector<osg::Vec2>* points, std::string filename)
{
	std::string fname = filename;
	std::ofstream pts_file;
	pts_file.open(fname.c_str(), std::ios::out|std::ios::trunc);
	if(pts_file.is_open())
	{
		for(uint idx = 0; idx < (points->size()); idx++)
		{
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).x() << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).y() << " ";
			pts_file << "=> ";
			pts_file << idx << " ";
			pts_file << std::endl;
		}
		pts_file.close();
	}
	else
		std::cout << "Cannot open file." << std::endl;
}

void WriterPT2::write(std::vector<cv::Point2f>* points, std::string filename)
{
	std::string fname = filename;
	std::ofstream pts_file;
	pts_file.open(fname.c_str(), std::ios::out|std::ios::trunc);
	if(pts_file.is_open())
	{
		for(uint idx = 0; idx < (points->size()); idx++)
		{

			pts_file << std::fixed << std::setprecision(5) << points->at(idx).x << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).y << " ";
			pts_file << "=> ";
			pts_file << idx << " ";
			pts_file << std::endl;
		}
		pts_file.close();
	}
	else
		std::cout << "Cannot open file." << std::endl;
}
