/*
 * ReaderEXIF.cpp
 *
 *  Created on: 18 maart 2015
 *      Author: christian
 */

#ifndef READEREXIF_H_
#define READEREXIF_H_

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

#include "ImagingPrimitives.h"

class ReaderEXIF
{
public:
	inline ReaderEXIF() : _filename(""), _result(EXIFdescriptor()) {}
	inline ~ReaderEXIF() {}
	int read();

	inline std::string GetFileName() { return _filename; }
	inline EXIFdescriptor GetEXIFdescriptor() { return _result; }

	inline void SetFileName(std::string filename) { _filename = filename; }

private:
	std::string _filename;
	EXIFdescriptor _result;
};

#endif /* READEREXIF_H_ */
