/*
 * OCVtoDAT.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: christian
 */

#include "OCVtoDAT.h"

OCVtoDAT::OCVtoDAT() : _matrix(cv::Mat(4,4,CV_64FC1)),_filename("") {
	// TODO Auto-generated constructor stub

}

OCVtoDAT::~OCVtoDAT() {
	// TODO Auto-generated destructor stub
}

void OCVtoDAT::write(void)
{
	std::ofstream dat_file;
	dat_file.open(_filename.c_str(), std::ios::out|std::ios::trunc);
	uint k = 0;
	if(dat_file.is_open())
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				//if(_matrix.depth() == CV_32F)
				//	dat_file << _matrix.at<float>(i,j) << " ";
				//else if(_matrix.depth() == CV_64F)
				//	dat_file << _matrix.at<double>(i,j) << " ";
				dat_file << _matrix.at<double>(i,j) << " ";
			}
			dat_file << std::endl;
		}
		dat_file.close();
	}
	else
		std::cout << "Cannot open DAT file." << std::endl;
}

