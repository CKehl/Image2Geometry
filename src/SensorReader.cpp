/*
 * SensorReader.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: christian
 */

#include "SensorReader.h"

void SensorReader::read(void)
{
#ifdef DEBUG_1
	std::cout << "Read sensor data file " << _filename << "..." << std::endl;
#endif
	std::string line;
	std::ifstream textfile(_filename.c_str());
	std::vector<std::string> strs;
	uint row_num = 0;

	_data.clear();

	if(textfile.is_open()==true)
	{

		std::getline(textfile,line);
		while(textfile.good()==true)
		{
			strs.clear();
#ifdef DEBUG_1
			std::cout << "Reading entry " << row_num << "." << std::endl;
#endif
			SensorEntry datum;
			boost::split(strs, line, boost::is_any_of("|"));
			for(uint k = 0; k < strs.size(); k++)
				strs.at(k) = boost::algorithm::trim_copy(strs.at(k));

			//Filepath
			datum.SetFilepath(strs.at(0));
#ifdef DEBUG_1
			std::cout << "Path: " << strs.at(0) << "." << std::endl;
#endif
			//GPS vector
			std::vector<std::string> valuestrings;
			std::string val_string = strs.at(1);
#ifdef DEBUG_1
			std::cout << "GPS string: " << val_string << std::endl;
#endif
			boost::split(valuestrings, val_string, boost::is_any_of(","));
			for(uint k = 0; k < valuestrings.size(); k++)
				valuestrings.at(k) = boost::algorithm::trim_copy(valuestrings.at(k));
			cv::Mat gps_mat = cv::Mat::zeros(3,1,CV_32FC1);
			gps_mat.at<float>(0,0) = float(atof(valuestrings.at(0).c_str()));
			gps_mat.at<float>(1,0) = float(atof(valuestrings.at(1).c_str()));
			gps_mat.at<float>(2,0) = float(atof(valuestrings.at(2).c_str()));
			datum.SetGPS_vec(gps_mat);
#ifdef DEBUG_1
			std::cout << "GPS vector " << gps_mat.at<float>(0,0) << ", " <<  gps_mat.at<float>(1,0) << ", " <<  gps_mat.at<float>(2,0) << "." << std::endl;
#endif
			//Rotation vector
			val_string = strs.at(2);
#ifdef DEBUG_1
			std::cout << "Rotation string: " << val_string << std::endl;
#endif
			boost::split(valuestrings, val_string, boost::is_any_of(","));
			for(uint k = 0; k < valuestrings.size(); k++)
				valuestrings.at(k) = boost::algorithm::trim_copy(valuestrings.at(k));
			cv::Mat rot_vec = cv::Mat::zeros(3,1,CV_32FC1);
			rot_vec.at<float>(0,0) = float(atof(valuestrings.at(0).c_str()));
			rot_vec.at<float>(1,0) = float(atof(valuestrings.at(1).c_str()));
			rot_vec.at<float>(2,0) = float(atof(valuestrings.at(2).c_str()));
			datum.SetRotation_vec(rot_vec);
#ifdef DEBUG_1
			std::cout << "Rotation vector " << rot_vec.at<float>(0,0) << ", " <<  rot_vec.at<float>(1,0) << ", " <<  rot_vec.at<float>(2,0) << "." << std::endl;
#endif
			// reorientation angle
			datum.SetReorientationAngle(atof(strs.at(4).c_str()));
#ifdef DEBUG_1
			std::cout << "Reorientation: " << atof(strs.at(4).c_str()) << std::endl;
#endif
			// magnetic declination
			datum.SetDeclination(atof(strs.at(5).c_str()));
#ifdef DEBUG_1
			std::cout << "Declination: " << atof(strs.at(5).c_str()) << std::endl;
#endif
			_data.push_back(datum);

			strs.clear();

			std::getline(textfile,line);
			if(textfile.eof()==true)
				break;
			row_num++;
		}
#ifdef DEBUG_1
		std::cout << "File reading operation done." << std::endl;
#endif
		textfile.close();

	}
	else
		std::cout << "Unable to open empty matrix file" << std::endl;
}


