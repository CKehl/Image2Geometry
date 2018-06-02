/*
 * CirclePairReader.cpp
 *
 *  Created on: 2 jan. 2016
 *      Author: christian
 */

#include "CirclePairReader.h"

CirclePairReader::CirclePairReader() : _filename(""), _list(std::vector< std::pair<Circle, Circle> >()) {
	// TODO Auto-generated constructor stub

}

CirclePairReader::~CirclePairReader() {
	// TODO Auto-generated destructor stub
}

void CirclePairReader::read(void)
{
#ifdef DEBUG
	std::cout << "Read matrix file " << _filename << "..." << std::endl;
#endif
	std::string line;
	std::ifstream dat_file(_filename.c_str());
	std::vector<std::string> strs;
	std::vector<std::string> ptvec;
	uint row_num = 0;

	if(dat_file.is_open()==true)
	{

		std::getline(dat_file,line);
		while(dat_file.good()==true)
		{
#ifdef DEBUG
			std::cout << line << std::endl;
#endif /* DEBUG */
			boost::split(strs, line, boost::is_any_of(" "));
			for(uint k = 0; k < strs.size(); k++)
				strs.at(k) = boost::algorithm::trim_copy(strs.at(k));
//#ifdef DEBUG
//			for(uint k = 0; k < strs.size(); k++)
//				std::cout << strs[k] << std::endl;
//#endif /* DEBUG */

			assert(strs.size()==7);

			std::pair<Circle, Circle> entry;
			// syn.x syn.y syn.r => ref.x ref.y ref.r

			entry.first = Circle(double(atof(strs.at(2).c_str())), cv::Point2f(double(atof(strs.at(0).c_str())), double(atof(strs.at(1).c_str()))));
			entry.second = Circle(double(atof(strs.at(6).c_str())), cv::Point2f(double(atof(strs.at(4).c_str())), double(atof(strs.at(5).c_str()))));
			_list.push_back(entry);

			strs.clear();

			std::getline(dat_file,line);
			if(dat_file.eof()==true)
				break;
			row_num++;
		}
#ifdef DEBUG
		std::cout << "File reading operation done." << std::endl;
#endif
		dat_file.close();

	}
	else
		std::cout << "Unable to open empty matrix file" << std::endl;
}

