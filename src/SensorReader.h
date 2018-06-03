/*
 * SensorReader.h
 *
 *  Created on: Oct 10, 2015
 *      Author: christian
 */

#ifndef SENSORREADER_H_
#define SENSORREADER_H_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "opencv_includes.h"
#include <iomanip>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>

class SensorEntry
{
public:
	inline SensorEntry() {}
	inline virtual ~SensorEntry() {}
	inline void SetFilepath(std::string filepath) { _filepath = filepath; }
	inline void SetGPS_vec(cv::Mat gps_vec) { _gps_vec = gps_vec; }
	inline void SetRotation_vec(cv::Mat rot_vec) { _rot_vec = rot_vec; }
	inline void SetReorientationAngle(double reorientation_angle) { _reorient_angle = reorientation_angle; }
	inline void SetDeclination(double declination) { _declination = declination; }
	inline std::string& filepath(void) { return _filepath; }
	inline cv::Mat& gps_vec(void) { return _gps_vec; }
	inline cv::Mat& rotation_vec(void) { return _rot_vec; }
	inline double reorientation_angle(void) { return _reorient_angle; }
	inline double declination(void) { return _declination; }

private:
	std::string _filepath;
	cv::Mat _gps_vec;
	cv::Mat _rot_vec;
	double _reorient_angle;
	double _declination;
};

class SensorReader {
public:
	inline SensorReader() : _filename(""), _data(std::vector<SensorEntry>()) {}
	inline virtual ~SensorReader() {}
	inline std::vector<SensorEntry>& data(void) { return _data; }
	inline void SetFileName(std::string filename) { _filename = filename; }
	void read(void);

private:
	std::string _filename;
	std::vector<SensorEntry> _data;
};

#endif /* SENSORREADER_H_ */
