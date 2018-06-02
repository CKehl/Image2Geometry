/*
 * BoundRenderScene.h
 *
 *  Created on: Jun 21, 2015
 *      Author: christian
 */

#ifndef BOUNDRENDERSCENE_H_
#define BOUNDRENDERSCENE_H_

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
#include <chrono>
#include <thread>
#include <assert.h>

#include "OpenCVOSGGlue.h"
#include "GeometryIntersector.h"

template<class T>
class ReferencedType: public T, public osg::Referenced
{
public:
	ReferencedType() { }
protected:
	~ReferencedType() { }
};
typedef ReferencedType<osg::Vec3> RefVec3;
typedef ReferencedType<osg::Vec4> RefVec4;

#include "ImagingPrimitives.h"

struct SnapshotCallback : public osg::Camera::DrawCallback
{
public:
	inline SnapshotCallback(std::string filepath) : _filepath(filepath), _output_to_file(false), _image(NULL)
	{
		if(filepath!="")
			_output_to_file = true;
		_image = new osg::Image();
	}

	inline virtual void operator() (osg::RenderInfo& renderInfo) const
	{
		osg::Camera* camera = renderInfo.getCurrentCamera();
		osg::Viewport* viewport = camera ? camera->getViewport() : 0;
		if(viewport)
		{
			glReadBuffer(camera->getDrawBuffer());
			_image->allocateImage(int(viewport->width()), int(viewport->height()), 1, GL_RGB, GL_UNSIGNED_BYTE);
			_image->readPixels(int(viewport->x()),int(viewport->y()),int(viewport->width()),int(viewport->height()), GL_RGB, GL_UNSIGNED_BYTE);
			if(_output_to_file)
			{
				osgDB::writeImageFile(*reinterpret_cast<osg::Image*>(_image->clone(osg::CopyOp::DEEP_COPY_ALL)), _filepath);
			}
		}
	}

	inline virtual void operator() (const osg::Camera& camera) const
	{
		osg::Viewport* viewport = camera.getViewport();
		if(viewport)
		{
			glReadBuffer(camera.getDrawBuffer());
			_image->allocateImage(int(viewport->width()), int(viewport->height()), 1, GL_RGB, GL_UNSIGNED_BYTE);
			_image->readPixels(int(viewport->x()),int(viewport->y()),int(viewport->width()),int(viewport->height()), GL_RGB, GL_UNSIGNED_BYTE);
			if(_output_to_file)
			{
				osgDB::writeImageFile(*reinterpret_cast<osg::Image*>(_image->clone(osg::CopyOp::DEEP_COPY_ALL)), _filepath);
			}
		}
	}

	inline osg::Image* GetImage(void)
	{
		return reinterpret_cast<osg::Image*>(_image->clone(osg::CopyOp::DEEP_COPY_ALL));
	}

protected:
	std::string _filepath;
	bool _output_to_file;
	mutable osg::ref_ptr<osg::Image> _image;
};

class RenderImageReady : public osg::Camera::DrawCallback
{
public:
	inline RenderImageReady() : _mutex(NULL), _image(NULL), _filepath(), _output_to_file(false) {  }
	inline RenderImageReady(OpenThreads::Mutex* mtx_obj, std::string filepath, int width, int height) : _mutex(mtx_obj), _filepath(filepath), _output_to_file(false), _initialized(false)
	{
		_image = new osg::Image();
		_image->allocateImage(width, height, 1, GL_RGB, GL_UNSIGNED_BYTE);
		if(filepath!="")
			_output_to_file = true;

	}
	inline virtual ~RenderImageReady() {  }
	inline virtual void WriteToFile(std::string path) { _filepath = path; _output_to_file = true; }
	inline virtual void WriteToMemory(void) { _filepath = ""; _output_to_file = false; }
	inline virtual void operator() (osg::RenderInfo& renderInfo) const
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(*_mutex);
		osg::Camera* camera = renderInfo.getCurrentCamera();
		osg::Viewport* viewport = camera ? camera->getViewport() : 0;

		if(viewport && _image.valid())
		{
			//if(!_initialized)
			//	_image->allocateImage(int(viewport->width()), int(viewport->height()), 1, GL_RGB, GL_UNSIGNED_BYTE);
			//_initialized=true;

			glReadBuffer(GL_BACK);
			_image->readPixels(int(viewport->x()),int(viewport->y()),int(viewport->width()),int(viewport->height()), GL_RGB, GL_UNSIGNED_BYTE);

			if(_output_to_file)
			{
#ifdef DEBUG
				std::cout << "Writing rendered image." << std::endl;
#endif
				osgDB::writeImageFile(*_image, _filepath);
			}
		}
		else
		{
#ifdef DEBUG
			std::cout << "error reading buffer" << std::endl;
#endif
		}

	}

	mutable OpenThreads::Mutex*  _mutex;
	mutable osg::ref_ptr<osg::Image> _image;

	std::string _filepath;
	bool _output_to_file;
	bool _initialized;
};

class BoundRenderScene {
public:
	BoundRenderScene();
	virtual ~BoundRenderScene();
	void NextFrame(void);
	inline OpenThreads::Mutex* GetMutexObject(void) { return &_mutex; }
	inline int GetCurrentWidth()
	{
		if(_camera_configuration!=NULL)
			return _camera_configuration->GetSX();
		return 0;
	}

	inline int GetCurrentHeight()
	{
		if(_camera_configuration!=NULL)
			return _camera_configuration->GetSY();
		return 0;
	}

	inline osg::Image* GetFrame(void)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		return _pbo.get();
	}

	inline void GetFrame(osg::Image* img)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);

		if(_frame.valid() && (img!=NULL) && img->valid())
		{
			glReadBuffer(GL_BACK);
			img->readPixels(0,0,_camera_configuration->GetSX(),_camera_configuration->GetSY(), GL_RGB,GL_UNSIGNED_BYTE);

			//assert(img->s() == _frame->s());
			//assert(img->t() == _frame->t());
			//assert(img->r() == _frame->r());
			//assert(img->getPixelFormat() == _frame->getPixelFormat());
			uint w = img->s(), h = img->t(), d = img->r(), c = uint(img->getPixelSizeInBits()/8);

			//if(_frame->isDataContiguous()==false)
			//	std::cout << "Input Data are not stored in a block." << std::endl;
			//else
			//	std::cout << "Input Data are stored in a block." << std::endl;
			//if(img->isDataContiguous()==false)
			//	std::cout << "Output Data are not stored in a block." << std::endl;
			//else
			//	std::cout << "Output Data are stored in a block." << std::endl;

			//memcpy(img->data(), const_cast<const unsigned char*>(frame->data()), w*h*d*c*sizeof(uchar));
			//img->copySubImage(0,0,0,const_cast<const osg::Image*>(_frame.get()));
			//osg::copyImage(const_cast<const osg::Image*>(_frame.get()), 0,0,0, w, h, d, img, 0,0,0);


			osgDB::writeImageFile(const_cast<const osg::Image&>(*img), "/tmp/testimg.png");
#ifdef DEBUG
			std::cout << "Data copied - (" << w << ", " << h << ", " << d << ", " << c << ")." << std::endl;
#endif

		}
	}

	inline cv::Mat GetFrameCV(void)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		cv::Mat result = OpenCV_OSG_Glue::convertImage(_pbo.get());
		return result;
	}

	inline void SetCameraConfiguration(CameraConfiguration* configuration) { _camera_configuration = configuration; }
	inline void SetCameraMatrix(osg::Matrixd camera_matrix) { _camera_matrix = camera_matrix; }
	inline void SetScene(osg::Node* scene) { _scene = scene; }
	inline void WriteFrameToFile(std::string path)
	{
		_filepath = path;
	}

	inline void Initialize(void) {
		if(!_initialized)
			_init();
		else
			_re_init();
	}
	inline void close(void) { _viewer.setDone(true); }

	void PrepareRaycastIntersection(void);
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
	osg::Camera* _camera;
	osg::Matrixd _camera_matrix;
	osg::ref_ptr<osg::Texture2D> _tex;
	osg::ref_ptr<osg::Texture2D> _tex_depth;
	osg::ref_ptr<osg::FrameBufferObject> _fbo;
	mutable osg::ref_ptr<osg::Image> _frame;
	mutable osg::ref_ptr<osg::Image> _pbo;
	mutable osg::ref_ptr<osg::Image> _frame_depth;
	mutable osg::ref_ptr<osg::Image> _pbo_depth;
	osg::ref_ptr<osg::Node> _scene;
	osg::ref_ptr<osg::GraphicsContext::Traits> _traits;
	osg::ref_ptr<osg::GraphicsContext> _gc;
	CameraConfiguration* _camera_configuration;
	//RenderImageReady* cb;
	osg::ref_ptr<SnapshotCallback> cb;
	std::string _filepath;
	GeometryIntersector* _intersector;
	osg::ref_ptr<osg::MatrixTransform> _transformer;

private:
	void _init(void);
	void _re_init(void);
	bool _initialized;
	mutable OpenThreads::Mutex  _mutex;

	osg::Matrixd pre_transform;
	osg::Matrixd transformation;
	osg::Matrixd lookat_matrix;
};

#endif /* BOUNDRENDERSCENE_H_ */
