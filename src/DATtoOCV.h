/*
 * DATtoOCV.h
 *
 *  Created on: Jun 29, 2015
 *      Author: christian
 */

#ifndef DATTOOCV_H_
#define DATTOOCV_H_

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

class DATtoOCV {
protected:
	cv::Mat _matrix;
	std::string _filename;

public:
	DATtoOCV();
	virtual ~DATtoOCV();
	inline void SetFileName(std::string filename) { _filename = filename; }
	inline cv::Mat GetMatrix(void) { return _matrix; }
	virtual void read(void);
};

#endif /* DATTOOCV_H_ */
