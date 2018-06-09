/*
 * ReaderPT2.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: christian
 */

#include "ReaderPT2.h"

ReaderPT2::ReaderPT2() : points(std::vector<Vector2>()), connectors(std::vector<uint>()), filename(""), mSeparator(" ") {
	// TODO Auto-generated constructor stub

}

ReaderPT2::~ReaderPT2() {
	// TODO Auto-generated destructor stub
}

void ReaderPT2::read(void)
{
#ifdef DEBUG
	std::cout << "Read file ..." << std::endl;
#endif
	std::string line;
	std::ifstream ptsfile(filename.c_str());
	std::vector<std::string> strs;
	if(ptsfile.is_open()==true)
	{

		//while(! ptsfile.eof())
		std::getline(ptsfile,line);
		while(ptsfile.good()==true)
		{

			Vector2 v;
			uint connector;


			boost::split(strs, line, boost::is_any_of(mSeparator));
			for(uint k = 0; k < strs.size(); k++)
				boost::algorithm::trim(strs.at(k));
			v.u() = float(atof(strs.at(0).c_str()));
			v.v() = float(atof(strs.at(1).c_str()));
			connector = uint(atoi(strs.at(3).c_str()));
#ifdef DEBUG
			//std::cout << "Entry: point (" << v.u() << ", " << v.v() << "), correlation: " << connector << std::endl;
#endif
			strs.clear();

			points.push_back(v);
			connectors.push_back(connector);
			std::getline(ptsfile,line);
			if(ptsfile.eof()==true)
				break;
		}
#ifdef DEBUG
		std::cout << "File reading operation done." << std::endl;
#endif
		ptsfile.close();
	}
	else std::cout << "Unable to open empty style positions file" << std::endl;
}
