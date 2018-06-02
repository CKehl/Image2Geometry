/*
 * ReaderEXIF.cpp
 *
 *  Created on: 19 maart 2015
 *      Author: christian
 */

#include "ReaderEXIF.h"
//typedef boost::tokenizer<boost::char_separator<char>> tok;

int ReaderEXIF::read()
{
#ifdef DEBUG
	std::cout << "Read EXIF file ..." << std::endl;
#endif
	int result = 0;
	std::string line;
	std::ifstream file(_filename.c_str());
	std::vector<std::string> strs;

	uint line_num = 0;

	if(file.is_open()==true)
	{

		//while(! ptsfile.eof())
		std::getline(file,line);
		while(file.good()==true)
		{
			if(line_num == 0)
			{

				boost::split(strs, line, boost::is_any_of(":"));

				boost::trim_right(strs.at(0));
				_result.SetImagefile( strs.at(0) );
			}
			else if( (line_num > 0) && (line_num < 2) )
			{

			}
			else
			{
				boost::split(strs, line, boost::is_any_of(":"));

				boost::trim_right(strs.at(1));
				boost::trim_left(strs.at(1));
				if( strs.at(0).find("Date Time") != strs.at(0).npos )
				{

				}
				else if( strs.at(0).find("Flash") != strs.at(0).npos )
				{
					int flashlight = atoi(strs.at(1).c_str());
					if(flashlight == 0)
					{
						_result.DisableFlash();
					}
					else
					{
						_result.EnableFlash();
					}
				}
				else if( strs.at(0).find("Focal Length") != strs.at(0).npos )
				{
					std::vector<std::string> rationals;
					boost::split(rationals, strs.at(1), boost::is_any_of("/"));

					float flength = float(atoi(rationals.at(0).c_str()))/float(atoi(rationals.at(1).c_str()));
					_result.SetFocalLength(flength);
				}
				else if( strs.at(0).find("Image Length") != strs.at(0).npos )
				{
					_result.SetImageHeight(uint(atoi(strs.at(1).c_str())));
				}
				else if( strs.at(0).find("Image Width") != strs.at(0).npos )
				{
					_result.SetImageWidth(uint(atoi(strs.at(1).c_str())));
				}
				else if( strs.at(0).find("Exposure Time") != strs.at(0).npos )
				{
					_result.SetExposure(atof(strs.at(1).c_str()));
				}
				else if( strs.at(0).find("Aperture") != strs.at(0).npos )
				{
					_result.SetAperture(atof(strs.at(1).c_str()));
				}
				else if( strs.at(0).find("ISO level") != strs.at(0).npos )
				{
					_result.SetISOLevel(uint(atoi(strs.at(1).c_str())));
				}
				else if( strs.at(0).find("CCD width") != strs.at(0).npos )
				{
					_result.SetCCDWidth(atof(strs.at(1).c_str()));
				}
				else if( strs.at(0).find("CCD height") != strs.at(0).npos )
				{
					_result.SetCCDHeight(atof(strs.at(1).c_str()));
				}
			}

			strs.clear();
			line_num++;

			std::getline(file,line);
			if(file.eof()==true)
				break;
		}
#ifdef DEBUG
		std::cout << "EXIF file processed." << std::endl;
#endif
		file.close();
		result = 0;
	}
	else
	{
#ifdef DEBUG
		std::cout << "Unable to open EXIF file" << std::endl;
#endif
		result = -1;
	}
	return result;
}
