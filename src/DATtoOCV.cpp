/*
 * DATtoOCV.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: christian
 */

#include "DATtoOCV.h"

DATtoOCV::DATtoOCV() : _matrix(cv::Mat()), _filename("") {
	// TODO Auto-generated constructor stub

}

DATtoOCV::~DATtoOCV() {
	// TODO Auto-generated destructor stub
}

void DATtoOCV::read(void)
{
#ifdef DEBUG
	std::cout << "Read matrix file " << _filename << "..." << std::endl;
#endif
	std::string line;
	std::ifstream dat_file(_filename.c_str());
	std::vector<std::string> strs;
	uint row_num = 0;

	_matrix = cv::Mat::eye(4,4,CV_64FC1);

	if(dat_file.is_open()==true)
	{

		std::getline(dat_file,line);
		while(dat_file.good()==true)
		{

			boost::split(strs, line, boost::is_any_of(" "));
			for(uint k = 0; k < strs.size(); k++)
				strs.at(k) = boost::algorithm::trim_copy(strs.at(k));

			_matrix.at<double>(row_num,0) = double(atof(strs.at(0).c_str()));
			_matrix.at<double>(row_num,1) = double(atof(strs.at(1).c_str()));
			_matrix.at<double>(row_num,2) = double(atof(strs.at(2).c_str()));
			_matrix.at<double>(row_num,3) = double(atof(strs.at(3).c_str()));
			strs.clear();

			std::getline(dat_file,line);
			if(dat_file.eof()==true)
				break;
			row_num++;
		}
#ifdef DEBUG
		std::cout << "File reading operation done." << std::endl;
#endif
		dat_file.close();

	}
	else
		std::cout << "Unable to open empty matrix file" << std::endl;
}
