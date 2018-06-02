/*
 * Circle.h
 *
 *  Created on: 2 jan. 2016
 *      Author: christian
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "opencv_includes.h"
#include <iostream>

class Circle {
public:
	inline Circle() : _radius(0.0f), _center(cv::Point2f()) {}
	inline Circle(const Circle& other) : _radius(other._radius), _center(other._center) {}
	inline Circle(float radius, cv::Point2f center) : _radius(radius), _center(center) {}
	Circle& operator=(Circle rhs) {swap(rhs); return *this;}
	inline void swap(Circle& s)
	{
		std::swap(_radius, s._radius);
		std::swap(_center, s._center);
	}
	inline virtual ~Circle() {}

	inline bool insideCircle(cv::Point2f point)
	{
		cv::Point2f dvec = point-_center;
		float d = (dvec.x*dvec.x)+(dvec.y*dvec.y);
		if(d<(_radius*_radius))
			return true;
		else
			return false;
	}

	inline friend std::ostream& operator<< (std::ostream& os, const Circle& rhs)
	{
		os << "{Circle - radius: " << rhs._radius << "; center: " << rhs._center << "}";
		return os;
	}

	inline cv::Point2f centerf(void)
	{
		return _center;
	}

	inline cv::Point centeri(void)
	{
		return cv::Point(int(_center.x), int(_center.y));
	}

	inline float radiusf(void)
	{
		return _radius;
	}

	inline int radiusi(void)
	{
		return int(_radius);
	}

protected:
	float _radius;
	cv::Point2f _center;
};

#endif /* CIRCLE_H_ */
