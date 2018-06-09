/*
 * ReaderPT2.h
 *
 *  Created on: Apr 23, 2015
 *      Author: christian
 */

#ifndef READERPT2_H_
#define READERPT2_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Vector.h"
#include "std_typedefs.h"

class ReaderPT2 {
public:
	ReaderPT2();
	virtual ~ReaderPT2();
	inline void SetFilename(std::string fname){filename = fname;}
	virtual void read(void);
	inline std::vector<Vector2> GetData(void){ return points; }
	inline std::vector<Vector2>* GetDataPointer(void) { return &points; }
	inline std::vector<uint> GetConnectors(void) { return connectors; }
	inline std::vector<uint>* GetConnectorsPointer(void) { return &connectors; }
	inline uint GetNumberOfSegments(void){return 1; }
	inline void SetSeparator(std::string separator) { mSeparator = separator; }

protected:
	std::vector<Vector2> points;
	std::vector<uint> connectors;
	std::string filename;
	std::string mSeparator;
};

#endif /* READERPT2_H_ */
