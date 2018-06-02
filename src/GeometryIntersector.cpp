/*
 * GeometryIntersector.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: christian
 */

#include "GeometryIntersector.h"

GeometryIntersector::GeometryIntersector() :_imagePoints(std::vector<osg::Vec2>()),
											_geometryPoints(std::vector<osg::Vec3>()),
											_camera_model(NULL),
											_intersectorGroup(new osgUtil::IntersectorGroup()),
											_scene(NULL) {
	// TODO Auto-generated constructor stub

}

GeometryIntersector::~GeometryIntersector() {
	// TODO Auto-generated destructor stub
}

void GeometryIntersector::setupIntersector(void)
{
	//_intersectorGroup = new osgUtil::IntersectorGroup();

	/*
	//osg::Vec3 _fp = osg::Vec3(0.5*_camera_model->GetCx()/1000.0, 0.5*_camera_model->GetCy()/1000.0, -_camera_model->GetFocalLength()/1000.0);
	osg::Vec3 _fp = osg::Vec3(0, 0, -_camera_model->GetFocalLength()/1000.0);
#ifdef DEBUG_1
	std::cout << "Fp: " << "("<<_fp.x()<<","<<_fp.y()<<","<<_fp.z()<<")" << std::endl;;
#endif
	double ray_len = 10000.0; //metres
	osg::Vec3 dir, endpoint;
	double x,y;
#ifdef DEBUG_1
	std::cout << "2D fieldsize: " << _imagePoints.size() << std::endl;
#endif
	for(uint i = 0; i < (_imagePoints.size()); i++)
	{
#ifdef DEBUG_1
		std::cout << "Ray " << i << ": ";
#endif
		x = ((_imagePoints.at(i).x()/_camera_model->GetSX()) * _camera_model->GetCx()/1000.0) - (0.5*_camera_model->GetCx()/1000.0);
		y = ((_imagePoints.at(i).y()/_camera_model->GetSY()) * _camera_model->GetCy()/1000.0) - (0.5*_camera_model->GetCy()/1000.0);
		dir = osg::Vec3(x,y,0) - _fp;
		dir.normalize();
		endpoint = _fp + dir*ray_len;
#ifdef DEBUG_1
		std::cout << "Endpoint " << "("<<endpoint.x()<<","<<endpoint.y()<<","<<endpoint.z()<<")" << " ... ";
#endif
		_intersectorGroup->addIntersector( new osgUtil::LineSegmentIntersector(_fp, endpoint) );
#ifdef DEBUG_1
		std::cout << "Line Intersection added." << std::endl;
#endif
	}
	*/
	double x,y;
	for(uint i = 0; i < (_imagePoints.size()); i++)
	{
		x = _imagePoints.at(i).x();
		y = _imagePoints.at(i).y();
		_intersectorGroup->addIntersector( new osgUtil::LineSegmentIntersector( osgUtil::Intersector::WINDOW, x,y ) );
#ifdef DEBUG_1
		std::cout << "Line Intersection added." << std::endl;
#endif
	}

	assert(_scene!=NULL);
}

void GeometryIntersector::Raycasting(void)
{
	osgUtil::IntersectionVisitor intersectVisitor( _intersectorGroup.get() );
#ifdef DEBUG_1
	std::cout << "Setting up intersector ... " << std::endl;
#endif
	//_world->accept(intersectVisitor);
	reinterpret_cast<osg::Camera*>(_scene)->accept(intersectVisitor);
	if(_intersectorGroup->containsIntersections())
	{
		osgUtil::IntersectorGroup::Intersectors& intersectors = _intersectorGroup->getIntersectors();
#ifdef DEBUG_1
		std::cout << "Found " << intersectors.size() << " intersections." << std::endl;
		uint item_number = 0;
#endif
		for(osgUtil::IntersectorGroup::Intersectors::iterator _iterator = intersectors.begin(); _iterator != intersectors.end(); ++_iterator)
		{
#ifdef DEBUG_1
			std::cout << "Accessing intersection point " << item_number << " - ";
#endif
			osgUtil::LineSegmentIntersector* lsi = dynamic_cast<osgUtil::LineSegmentIntersector*>(_iterator->get());
			if( (lsi!=NULL) && (lsi->getIntersections().empty()==false) )
			{
#ifdef DEBUG_1
				std::cout << "Intersection." << std::endl;
#endif
				const osgUtil::LineSegmentIntersector::Intersection& intersection = lsi->getFirstIntersection();
				_geometryPoints.push_back(intersection.getWorldIntersectPoint());
			}
			else
			{
#ifdef DEBUG_1
				std::cout << "No Intersection." << std::endl;
#endif
				_geometryPoints.push_back(VOID_INTERSECTION);
			}
#ifdef DEBUG_1
			item_number++;
#endif
		}
	}
}

void GeometryIntersector::ComputeIntersections(osgViewer::View* _v, osg::Camera* _c)
{
	_geometryPoints.clear();
	osgUtil::LineSegmentIntersector::Intersections intersections;
	for(uint i = 0; i < (_imagePoints.size()); i++)
	{
		if(i==0)
		{
		osg::Matrixf cmat = _c->getViewMatrix();
		float* data = (float*)(cmat.ptr());
		printf("[%f,%f,%f,%f]\n",data[0],data[1],data[2],data[3]);
		printf("[%f,%f,%f,%f]\n",data[4],data[5],data[6],data[7]);
		printf("[%f,%f,%f,%f]\n",data[8],data[9],data[10],data[11]);
		printf("[%f,%f,%f,%f]\n",data[12],data[13],data[14],data[15]);
		}
#ifdef DEBUG_1
		std::cout << "Accessing intersection point " << i << " - ";
#endif
		_v->computeIntersections(const_cast<const osg::Camera*>(_c), osgUtil::Intersector::WINDOW, _imagePoints.at(i).x(), _imagePoints.at(i).y(), intersections);
		if(intersections.empty() == false)
		{
#ifdef DEBUG_1
			std::cout << "Intersection." << std::endl;
#endif
			_geometryPoints.push_back(intersections.begin()->getWorldIntersectPoint());
		}
		else
		{
#ifdef DEBUG_1
			std::cout << "No Intersection." << std::endl;
#endif
			_geometryPoints.push_back(VOID_INTERSECTION);
		}
	}


}
