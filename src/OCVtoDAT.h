/*
 * OCVtoDAT.h
 *
 *  Created on: Apr 24, 2015
 *      Author: christian
 */

#ifndef OCVTODAT_H_
#define OCVTODAT_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "std_typedefs.h"

#include "opencv_includes.h"

class OCVtoDAT {
protected:
	cv::Mat _matrix;
	std::string _filename;

public:
	OCVtoDAT();
	virtual ~OCVtoDAT();
	inline void SetFileName(std::string filename) { _filename = filename; }
	inline void SetMatrix(cv::Mat matrix) { _matrix = matrix; }
	virtual void write(void);
};

#endif /* OCVTODAT_H_ */
