/*
 * ReaderPTS.cpp
 *
 *  Created on: 17 aug. 2013
 *      Author: christian
 */

#include "ReaderPTS.h"

ReaderPTS::ReaderPTS() : points(std::vector<Vector3>()), filename(""), extents(MinMaxD()), mSeparator(" ") {
	// TODO Auto-generated constructor stub

}

ReaderPTS::~ReaderPTS() {
	// TODO Auto-generated destructor stub
}

void ReaderPTS::read(void)
{
#ifdef DEBUG
	std::cout << "Read file ..." << std::endl;
#endif
	std::string line;
	//std::filebuf filepts;
	//filepts.open(filename.c_str(), std::ios::in);
	//std::ifstream ptsfile(&filepts);
	std::ifstream ptsfile(filename.c_str());
	std::vector<std::string> strs;
	if(ptsfile.is_open()==true)
	{

		//while(! ptsfile.eof())
		std::getline(ptsfile,line);
		while(ptsfile.good()==true)
		{
//#ifdef DEBUG
//			std::cout << "Read new line ..." << std::endl;
//#endif
			Vector3 v;
			//std::getline(ptsfile,line);

			boost::split(strs, line, boost::is_any_of(mSeparator));
			for(uint k = 0; k < strs.size(); k++)
				boost::algorithm::trim(strs.at(k));
			v.x() = float(atof(strs.at(0).c_str()));
			v.y() = float(atof(strs.at(1).c_str()));
			v.z() = float(atof(strs.at(2).c_str()));
			strs.clear();
			//res = atof(line.c_str());
			points.push_back(v);
//#ifdef DEBUG
//			std::cout << line << std::endl;
//#endif
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
