/*
 * CirclePairReader.h
 *
 *  Created on: 2 jan. 2016
 *      Author: christian
 */

#ifndef CIRCLEPAIRREADER_H_
#define CIRCLEPAIRREADER_H_

#include "Circle.h"
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
//#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "std_typedefs.h"

class CirclePairReader {
public:
	CirclePairReader();
	virtual ~CirclePairReader();

	inline void SetFileName(std::string filename)
	{
		_filename = filename;
	}

	inline std::vector< std::pair<Circle, Circle> > GetCircleCorrespondences(void)
	{
		return _list;
	}

	void read(void);

protected:
	std::string _filename;
	std::vector< std::pair<Circle, Circle> > _list;
};

#endif /* CIRCLEPAIRREADER_H_ */
