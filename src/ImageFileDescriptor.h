/*
 * ImageFileDescriptor.h
 *
 *  Created on: Jul 1, 2015
 *      Author: christian
 */

#ifndef IMAGEFILEDESCRIPTOR_H_
#define IMAGEFILEDESCRIPTOR_H_

#include <string>

class ImageFileDescriptor {
public:
	inline ImageFileDescriptor() : matrix_file(""), image_file(""), exif_file(""), declination_file(""), ptsfile(""), pt2file(""), cvfile(""), temp_file(""), result_matrix_file("") {}
	virtual inline ~ImageFileDescriptor() {}

	std::string matrix_file;
	std::string image_file;
	std::string exif_file;
	std::string declination_file;
	std::string ptsfile;
	std::string pt2file;
	std::string cvfile;
	std::string temp_file; //ONLY the current temp
	std::string result_matrix_file;
};

#endif /* IMAGEFILEDESCRIPTOR_H_ */
