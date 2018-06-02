/*
 * main.cpp
 *
 *  Created on: 17 maart 2015
 *      Author: christian
 */

#ifndef IMAGINGPRIMITIVES_H_
#define IMAGINGPRIMITIVES_H_

#include <string>
#include <time.h>
#include <iostream>
#include <map>
#include "std_typedefs.h"
#include <math.h>

class CameraConfiguration
{
protected:
	// in mm
	double _focal_length;
	// distortion
	double _k1, _k2;
	// in mm (CCD)
	double _cx, _cy;
	// image center
	double _x0, _y0;
	// Image resolution
	uint _sx, _sy;
public:
	inline CameraConfiguration() {}
	inline ~CameraConfiguration() {}

	inline void SetFocalLength(double focal_length) { _focal_length = focal_length; }
	inline void SetK1(double k1) { _k1 = k1; }
	inline void SetK2(double k2) { _k2 = k2; }
	inline void SetCx(double cx) { _cx = cx; }
	inline void SetCy(double cy) { _cy = cy; }
	inline void SetX0(double x0) { _x0 = x0; }
	inline void SetY0(double y0) { _y0 = y0; }
	inline void SetSX(uint sx) { _sx = sx; }
	inline void SetSY(uint sy) { _sy = sy; }

	inline double GetFocalLength() { return _focal_length; }
	inline double GetFoV() { return (2.0*atan(_cy/(2.0*_focal_length))); }
	inline double GetAspectRatio() { return _cx/_cy; }
	inline double GetK1() { return _k1; }
	inline double GetK2() { return _k2; }
	inline double GetCx() { return _cx; }
	inline double GetCy() { return _cy; }
	inline double GetX0() { return _x0; }
	inline double GetY0() { return _y0; }
	inline uint GetSX() { return _sx; }
	inline uint GetSY() { return _sy; }

	inline friend std::ostream& operator<< (std::ostream& os, const CameraConfiguration& rhs)
	{
		os << "{Camera: "<< rhs._focal_length << "mm," << rhs._cx << "mm," << rhs._cy << "mm," << rhs._sx << "px," << rhs._sy << "px" <<"}";
		return os;
	}
};

class EXIFdescriptor
{
public:
	inline EXIFdescriptor() : _imagefile(""), _epoch(0), _use_flash(false), _focal_length(1.0), _image_width(0), _image_height(0), _exposure(0.0f), _aperture(0), _iso(0), _ccd_width(0.0f), _ccd_height(0.0f) {}
	inline ~EXIFdescriptor() {}

	inline std::string GetImageFile() { return _imagefile; }
	inline clock_t GetTimestamp() { return _epoch; }
	inline bool FlashUsed() { return _use_flash; }
	inline float GetFocalLength() { return _focal_length; }
	inline uint GetImageWidth() { return _image_width; }
	inline uint GetImageHeight() { return _image_height; }
	inline float GetExposure() { return _exposure; }
	inline float GetAperture() { return _aperture; }
	inline uint GetIsoLevel() { return _iso; }
	inline float GetCCDWidth() { return _ccd_width; }
	inline float GetCCDHeight() { return _ccd_height; }

	inline void SetImagefile(std::string imagefile) { _imagefile = imagefile; }
	inline void SetTimestamp(clock_t timestamp) { _epoch = timestamp; }
	inline void EnableFlash() { _use_flash = true; }
	inline void DisableFlash() { _use_flash = false; }
	inline void SetFocalLength(float focal_length) { _focal_length = focal_length; }
	inline void SetImageWidth (uint image_width) { _image_width = image_width; }
	inline void SetImageHeight (uint image_height) { _image_height = image_height; }
	inline void SetExposure(float exposure) { _exposure = exposure; }
	inline void SetAperture(float aperture) { _aperture = aperture; }
	inline void SetISOLevel(uint iso_level) { _iso = iso_level; }
	inline void SetCCDWidth(float ccd_width) { _ccd_width = ccd_width; }
	inline void SetCCDHeight(float ccd_height) { _ccd_height = ccd_height; }

	inline friend std::ostream& operator<< (std::ostream& os, const EXIFdescriptor& rhs)
	{
		os << "{EXIF: "<< rhs._focal_length << "mm," << rhs._ccd_width << "mm," << rhs._ccd_height <<"mm}";
		return os;
	}

protected:
	std::string _imagefile;
	clock_t _epoch;
	bool _use_flash;
	// in mm
	float _focal_length;
	uint _image_width;
	uint _image_height;
	float _exposure;
	float _aperture;
	uint _iso;
	// CCD measurements in mm
	float _ccd_width;
	float _ccd_height;
};

class TextureReference
{
public:
	inline TextureReference() : _tex_unit(0) {}
	inline TextureReference(const TextureReference& other) : _tex_unit(other._tex_unit) {}
	inline TextureReference(uchar texture_unit) : _tex_unit(texture_unit) {}
	TextureReference& operator=(TextureReference rhs) {swap(rhs); return *this;}
	inline void swap(TextureReference& s)
	{
		std::swap(_tex_unit, s._tex_unit);
	}
	inline virtual ~TextureReference() {}
	inline void SetTextureUnit(uchar tex_unit) { _tex_unit = tex_unit; }
	inline uchar GetTextureUnit(void) { return _tex_unit; }

	inline friend std::ostream& operator<< (std::ostream& os, const TextureReference& rhs)
	{
		os << "TextureReference - tu: " << rhs._tex_unit;
		return os;
	}

protected:
	uchar _tex_unit;
};

typedef std::pair<uchar, std::string> TextureEntry;
typedef std::map<uchar, std::string> TextureDictionary;

/*
 * Temporary solution: typecast for feature vectors (2D image features)
 */
/*
typedef struct _feature
{
	double x,y;
} Feature;

typedef std::vector<Feature> FeatureList;
*/
#endif /* IMAGINGPRIMITIVES_H_ */
