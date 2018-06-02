/*
 * SyntheticScene.h
 *
 *  Created on: Aug 13, 2015
 *      Author: christian
 */

#ifndef SYNTHETICSCENE_H_
#define SYNTHETICSCENE_H_

#include <osg/GL>
#include <osg/GLExtensions>
#include <osg/GL2Extensions>
#include <osg/GLObjects>
#include <osg/CoordinateSystemNode>
#include <osg/ref_ptr>
#include <osg/Array>
#include <osg/ImageUtils>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/GraphicsContext>
#include <osg/Texture2D>
#include <osg/FrameBufferObject>
#include <osgDB/WriteFile>
#include <osg/Referenced>
#include <osg/Vec3>
#include <osg/Image>
#include <osg/State>
#include <string>
#include <time.h>
//#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <assert.h>

#include "screenview.h"
#include "GeometryIntersector.h"
#include "OpenCVOSGGlue.h"
#include "ImagingPrimitives.h"

class SyntheticScene {
public:
	SyntheticScene();
	virtual ~SyntheticScene();

	inline void Initialize(void) {
		_init();
	}
	inline void close(void)
	{
		_viewer.setSceneData(NULL);
		_viewer.setDone(true);
	}
	inline void SetCameraConfiguration(CameraConfiguration* camera) { _cam = camera; }
	inline void SetCameraMatrix(osg::Matrixd camera_matrix) { _camera_matrix = camera_matrix; }
	inline void SetScene(osg::Node* scene) { _scene = scene; }
	void NextFrame(void);
	inline cv::Mat GetFrameCV(void)
	{
		NextFrame();
		cv::Mat result;
		if(_callback != NULL)
		{
			osg::Image* data = _callback->getImage(_gc.get());
			if(data==NULL)
				data = _callback->getImage(_viewer.getCamera()->getGraphicsContext());
			while(data==NULL)
			//while(1)
			{
				//sleep(1);
				NextFrame();
				data = _callback->getImage(_gc.get());
				if(data==NULL)
					data = _callback->getImage(_viewer.getCamera()->getGraphicsContext());
			}
			result = OpenCV_OSG_Glue::convertImage( reinterpret_cast<osg::Image*> ( data->clone ( osg::CopyOp::DEEP_COPY_ALL ) ) );
		}
		else
			result = cv::Mat();
		return result;
	}
	inline int GetCurrentWidth()
	{
		if(_cam!=NULL)
			return _cam->GetSX();
		return 0;
	}

	inline int GetCurrentHeight()
	{
		if(_cam!=NULL)
			return _cam->GetSY();
		return 0;
	}

	inline void setBackgroundColour(osg::Vec4f colourVec) {
		_backgroundColour = colourVec;
	}

	inline osg::Vec4f getBackgroundColour() {
		return _backgroundColour;
	}

	void RaycastIntersections(void);
	/*
	 * Adds a point (in image space coordinates) to be casted in 3D scene
	 */
	inline void add_point_to_cast(osg::Vec2 point_to_cast)
	{
		_intersector->addImagePoint(point_to_cast);
#ifdef DEBUG_1
		std::cout << "Added image point " << _intersector->GetNumberImagePoints()-1 << "." << std::endl;
#endif
	}

	inline void clear_points_to_cast(void)
	{
		_intersector->clearImagePoints();
	}

	/*
	 * Get full vector of casting results
	 */
	inline std::vector<osg::Vec3> GetIntersections(void)
	{
		return _intersector->GetGeometryPoints();
	}

	/*
	 * get specific casting result
	 */
	inline osg::Vec3 GetIntersection(uint index)
	{
		return _intersector->GetGeometryPoint(index);
	}

	inline uint GetNumberOfIntersections(void) { return _intersector->GetNumberGeometryPoints(); }

protected:
	osgViewer::Viewer _viewer;
	osg::ref_ptr<osg::Camera> _camera;
	osg::Matrixd _camera_matrix;
	osg::ref_ptr<osg::Node> _scene;
	osg::ref_ptr<osg::GraphicsContext::Traits> _traits;
	osg::ref_ptr<osg::GraphicsContext> _gc;
	CameraConfiguration* _cam;
	WindowCaptureCallback* _callback;
	std::string _filepath;
	GeometryIntersector* _intersector;
	osg::ref_ptr<osg::MatrixTransform> _transformer;
	osg::Matrixd pre_transform;
	osg::Matrixd transformation;
	osg::Matrixd lookat_matrix;
	osg::Vec4f _backgroundColour;

private:
	void _init(void);
};



#endif /* SYNTHETICSCENE_H_ */
