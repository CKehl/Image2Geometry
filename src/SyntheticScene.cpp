/*
 * SyntheticScene.cpp
 *
 *  Created on: Aug 13, 2015
 *      Author: christian
 */

#include "SyntheticScene.h"

SyntheticScene::SyntheticScene() :  _viewer(osgViewer::Viewer()),
									_camera(NULL),
									_camera_matrix(osg::Matrixd::identity()),
									_scene(NULL),
									_traits(NULL),
									_gc(NULL),
									_cam(NULL),
									_callback(NULL),
									_filepath(""),
									_intersector(new GeometryIntersector()),
									_transformer(NULL),
									pre_transform(osg::Matrixd::identity()),
									transformation(osg::Matrixd::identity()),
									lookat_matrix(osg::Matrixd::identity()),
									_backgroundColour(osg::Vec4f(0.25f, 0.25f, 0.25f, 1.0f))
{
	// TODO Auto-generated constructor stub
	_camera = new osg::Camera();

	_traits = new osg::GraphicsContext::Traits();
	_transformer = new osg::MatrixTransform();
}

SyntheticScene::~SyntheticScene() {
	// TODO Auto-generated destructor stub
	close();
}

void SyntheticScene::_init()
{
	//osg::ref_ptr<osg::GraphicsContext> pbuffer;
	_traits->x = 0;
	_traits->y = 0;
	_traits->width = _cam->GetSX();
	_traits->height = _cam->GetSY();
	_traits->red = 8;
	_traits->green = 8;
	_traits->blue = 8;
	_traits->alpha = 8;
	_traits->depth = 8;
	_traits->windowDecoration = false;
	_traits->pbuffer = true;
	_traits->doubleBuffer = true;
	_traits->sharedContext = 0x0;

	_gc = osg::GraphicsContext::createGraphicsContext(_traits.get());
#ifdef DEBUG
	if(_gc.valid())
		std::cout << "Graphics Context successfully created." << std::endl;
	else
		std::cout << "Graphics Context creation unsuccessful." << std::endl;
#endif


	_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	_viewer.setCameraManipulator(0x0);

	_transformer->addChild(_scene.get());
	_viewer.setSceneData(_transformer.get());

	if(_gc.valid())
	{
		_viewer.getCamera()->setGraphicsContext(_gc.get());
		//_camera->setGraphicsContext(_gc.get());
		_viewer.getCamera()->setViewport(0,0,_cam->GetSX(),_cam->GetSY());
		//_camera->setViewport(0,0,_cam->GetSX(),_cam->GetSY());
		_viewer.getCamera()->setClearColor(_backgroundColour);
		//_camera->setClearColor(osg::Vec4f(0.25f, 0.25f, 0.25f, 1.0f));
		_viewer.getCamera()->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//_camera->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		_viewer.getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		//_camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		_viewer.getCamera()->setDrawBuffer(GL_BACK);
		//_camera->setDrawBuffer(GL_BACK);
		_viewer.getCamera()->setReadBuffer(GL_BACK);
		//_camera->setReadBuffer(GL_BACK);
		//_camera->setProjectionMatrix(osg::Matrixd::perspective(osg::RadiansToDegrees(_cam->GetFoV()), _cam->GetAspectRatio(), 0.1, 150.0));

		_callback = new WindowCaptureCallback(WindowCaptureCallback::DOUBLE_PBO, WindowCaptureCallback::START_FRAME, GL_BACK);
		//_camera->setFinalDrawCallback(_callback);
		_viewer.getCamera()->setFinalDrawCallback(_callback);
		//_viewer.getCamera()->getFinalDrawCallback()

		//_viewer.addSlave(_camera.get(), osg::Matrixd(), osg::Matrixd());
		_viewer.realize();

		_viewer.getCamera()->setProjectionMatrix(osg::Matrixd::perspective(osg::RadiansToDegrees(_cam->GetFoV()), _cam->GetAspectRatio(), 0.05, 150.0));
#ifndef SILENT
		std::cout << _cam->GetFoV() << ", " << osg::RadiansToDegrees(_cam->GetFoV()) << " | " << _cam->GetAspectRatio() << std::endl;
#endif
		lookat_matrix = osg::Matrixd::lookAt(osg::Vec3d(0.0, 0.0, -1.0), osg::Vec3d(0.0, 0.0, 1.0), osg::Vec3d(0.0, 1.0, 0.0));
		_viewer.getCamera()->setViewMatrix(lookat_matrix);
		//_viewer.setCameraManipulator(0x0);
	}

	pre_transform = osg::Matrixd::scale(1,1,-1);

	//_viewer.frame();
}

void SyntheticScene::NextFrame(void)
{
	if(!_viewer.done())
	{
		osg::Matrixd inverse_cam = osg::Matrixd::inverse(_camera_matrix);
		transformation = inverse_cam * pre_transform;
		_viewer.getCamera()->setViewMatrix(transformation);
		_viewer.frame();
		_viewer.frame();
	}
	else
		std::cout << "Viewer or Camera invalid." << std::endl;
}

void SyntheticScene::RaycastIntersections(void)
{
#ifdef DEBUG_1
	std::cout << "Casting Rays ..." << std::endl;
#endif
	_intersector->ComputeIntersections(&_viewer,_viewer.getCamera());
}



