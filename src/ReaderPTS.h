/*
 * ReaderPTS.h
 *
 *  Created on: 17 aug. 2013
 *      Author: christian
 */

#ifndef READERPTS_H_
#define READERPTS_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
//#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Vector.h"
#include "std_typedefs.h"


class ReaderPTS {
public:
	ReaderPTS();
	virtual ~ReaderPTS();

	inline void SetFilename(std::string fname){filename = fname;}
	virtual void read(void);
	inline std::vector<Vector3> GetData(void){ return points; }
	inline std::vector<Vector3>* GetDataPointer(void) { return &points; }
	inline uint GetNumberOfSegments(void){return 1; }
	inline MinMaxD GetExtent(void) {return extents;}
	inline MinMaxD* GetExtentPointer(void) {return &extents;}
	inline void SetSeparator(std::string separator) { mSeparator = separator; }

protected:
	std::vector<Vector3> points;
	std::string filename;
	MinMaxD extents;
	std::string mSeparator;
};

#endif /* READERPTS_H_ */
