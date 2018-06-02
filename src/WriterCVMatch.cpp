/*
 * WriterCVMatch.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: christian
 */

#include "WriterCVMatch.h"

WriterCVMatch::WriterCVMatch() {
	// TODO Auto-generated constructor stub

}

WriterCVMatch::~WriterCVMatch() {
	// TODO Auto-generated destructor stub
}

void WriterCVMatch::write(std::vector<cv::KeyPoint>* points_syn, std::vector<cv::KeyPoint>* points_real, std::vector<cv::DMatch>* matches, std::string filename)
{
	std::string fname = filename;
	std::ofstream pts_file;
	pts_file.open(fname.c_str(), std::ios::out|std::ios::trunc);
	if(pts_file.is_open())
	{
		for(uint idx = 0; idx < (matches->size()); idx++)
		{

			pts_file << std::fixed << std::setprecision(5) << points_syn->at(matches->at(idx).queryIdx).pt.x << " ";
			pts_file << std::fixed << std::setprecision(5) << points_syn->at(matches->at(idx).queryIdx).pt.y << " ";
			pts_file << "=> ";
			pts_file << std::fixed << std::setprecision(5) << points_real->at(matches->at(idx).trainIdx).pt.x << " ";
			pts_file << std::fixed << std::setprecision(5) << points_real->at(matches->at(idx).trainIdx).pt.y << " ";
			pts_file << std::endl;
		}
		pts_file.close();
	}
	else
		std::cout << "Cannot open file." << std::endl;
}
