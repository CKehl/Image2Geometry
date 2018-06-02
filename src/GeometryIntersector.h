/*
 * GeometryIntersector.h
 *
 *  Created on: Jul 24, 2015
 *      Author: christian
 */

#ifndef GEOMETRYINTERSECTOR_H_
#define GEOMETRYINTERSECTOR_H_

#include <vector>
#include <assert.h>
#include <osg/Version>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osg/ref_ptr>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/IntersectVisitor>
#include <osgUtil/LineSegmentIntersector>
#include <osgDB/ReadFile>
#include <osgViewer/View>
#include "ImagingPrimitives.h"

struct MyReadCallback : public osgUtil::IntersectionVisitor::ReadCallback
{
#if((OSG_VERSION_MAJOR >= 3) && (OSG_VERSION_MINOR >=3))
    virtual osg::ref_ptr<osg::Node> readNodeFile(const std::string& filename)
#else
	virtual osg::Node* readNodeFile(const std::string& filename)
#endif
    {
#ifdef DEBUG_1
    	std::cout << "Reading new node file ..." << std::endl;
#endif
        return osgDB::readNodeFile(filename);
    }
};

#define VOID_INTERSECTION osg::Vec3(DBL_MAX,DBL_MAX,DBL_MAX)

class GeometryIntersector {
public:
	GeometryIntersector();
	virtual ~GeometryIntersector();

	inline void SetScene(osg::Node* scene) { _scene = scene; }
	inline void SetCameraModel(CameraConfiguration* camera_model) { _camera_model = camera_model; }
	inline void addImagePoint(osg::Vec2 point) { _imagePoints.push_back(point); }
	inline void clearImagePoints(void) { _imagePoints.clear(); }
	inline std::vector<osg::Vec3> GetGeometryPoints(void) { return _geometryPoints; }
	inline osg::Vec3 GetGeometryPoint(int index) { return _geometryPoints.at(index); }
	inline uint GetNumberGeometryPoints(void) { return _geometryPoints.size(); }
	inline uint GetNumberImagePoints(void) { return _imagePoints.size(); }
	inline osgUtil::IntersectorGroup::Intersectors GetIntersectors(void) { return _intersectorGroup->getIntersectors(); }
	void ComputeIntersections(osgViewer::View* _v, osg::Camera* _c);
	void setupIntersector(void);
	void Raycasting(void);

protected:
	std::vector<osg::Vec2> _imagePoints;
	std::vector<osg::Vec3> _geometryPoints;
	CameraConfiguration* _camera_model;
	osg::ref_ptr<osgUtil::IntersectorGroup> _intersectorGroup;
	osg::Node* _scene;
};

#endif /* GEOMETRYINTERSECTOR_H_ */
