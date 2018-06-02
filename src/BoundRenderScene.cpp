/*
 * BoundRenderScene.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: christian
 */

#include "BoundRenderScene.h"

//#define FBO 1

BoundRenderScene::BoundRenderScene() :  _viewer(osgViewer::Viewer()),
										_camera(NULL),
										_camera_matrix(osg::Matrixd::identity()),
										_tex(NULL),
										_tex_depth(NULL),
										_fbo(NULL),
										_frame(NULL),
										_pbo(NULL),
										_frame_depth(NULL),
										_pbo_depth(NULL),
										_scene(NULL),
										_traits(NULL),
										_gc(NULL),
										_camera_configuration(NULL),
										cb(NULL),
										_filepath(""),
										_intersector(new GeometryIntersector()),
										_transformer(NULL),
										_initialized(false)
{
	// TODO Auto-generated constructor stub
	_traits = new osg::GraphicsContext::Traits();
	_tex = new osg::Texture2D();
	_tex_depth = new osg::Texture2D();
	_fbo = new osg::FrameBufferObject();
	_frame = new osg::Image();
	_pbo = new osg::Image();
	_frame_depth = new osg::Image();
	_pbo_depth = new osg::Image();
	_transformer = new osg::MatrixTransform();


	//cb = new RenderImageReady(&_mutex,_filepath);

	//set up the viewer
	//_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	//_viewer.setUpThreading();
}

BoundRenderScene::~BoundRenderScene() {
	// TODO Auto-generated destructor stub
	_viewer.setDone(true);
	_viewer.setReleaseContextAtEndOfFrameHint(true);
	_gc->releaseContext();

#ifdef DEBUG
	std::cout << "BoundRenderScene deleted." << std::endl;
#endif
}

void BoundRenderScene::_re_init()
{
	_viewer.releaseGLObjects();
	unsigned int contextID = _viewer.getCamera()->getGraphicsContext()->getState()->getContextID();
	osg::discardAllGLObjects(contextID);
	_viewer.getCamera()->getGraphicsContext()->resized(0,0,_camera_configuration->GetSX(),_camera_configuration->GetSY());
	_viewer.getCamera()->setViewport(0,0,_camera_configuration->GetSX(),_camera_configuration->GetSY());
	_viewer.getCamera()->setProjectionMatrix(osg::Matrixd::perspective(osg::RadiansToDegrees(_camera_configuration->GetFoV()), _camera_configuration->GetAspectRatio(), 0.1, 150.0));
	_frame->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_RGB, GL_UNSIGNED_BYTE);
	_frame_depth->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	_tex->setTextureSize(_camera_configuration->GetSX(), _camera_configuration->GetSY());
	_tex_depth->setTextureSize(_camera_configuration->GetSX(), _camera_configuration->GetSY());
	//if(cb!=NULL)
	//	delete cb;
	cb = new SnapshotCallback(_filepath);
	_viewer.getCamera()->setFinalDrawCallback(cb);
	_viewer.realize();

	// Limit framerate
	_viewer.setRunMaxFrameRate(25);
}

void BoundRenderScene::_init(void)
{
	//if(_camera!=NULL)
	//	_viewer.setDone(true);

	_traits->x = 0;
	_traits->y = 0;
	_traits->width = _camera_configuration->GetSX();
	_traits->height = _camera_configuration->GetSY();
	_traits->red = 8;
	_traits->green = 8;
	_traits->blue = 8;
	_traits->alpha = 0;
	_traits->depth = 24;
	_traits->windowDecoration = false;
	_traits->pbuffer = true;
	_traits->vsync = true;
	_traits->doubleBuffer = true;
	//_traits->sharedContext = 0x0;
	_traits->sharedContext = 0;

#ifdef DEBUG
	std::cout << "Graphics traits initialized." << std::endl;
	std::cout << *_camera_configuration << std::endl;
#endif

	/*
	if(_gc.get()!=NULL)
	{
		bool release_success = _gc->releaseContext();
#ifdef DEBUG
		if(!release_success)
			std::cerr << "Error releasing Graphics Context.";
#endif
	}
	*/

	_gc = osg::GraphicsContext::createGraphicsContext(_traits.get());
	_viewer.getCamera()->setGraphicsContext(_gc.get());

	//_viewer.getCamera()->getDisplaySettings()->setMaxTexturePoolSize(_camera_configuration->GetSX()*_camera_configuration->GetSY()*4*sizeof(uchar));


	_pbo->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_RGB, GL_UNSIGNED_BYTE);
	//_pbo_depth->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);

	_viewer.getCamera()->getOrCreateStateSet();
	_viewer.getCamera()->setRenderTargetImplementation(osg::Camera::PIXEL_BUFFER);

	// GLExtension, taken over from osgscreencapture example
	//GLuint copy_pbo, read_pbo;
	//osg::GLBufferObject::Extensions* ext = osg::GLBufferObject::getExtensions(_gc->getState()->getContextID(), true);
	//ext->glGenBuffers(1, &copy_pbo);
	//ext->glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, copy_pbo);
	//ext->glBufferData(GL_PIXEL_PACK_BUFFER_ARB, _pbo->getTotalSizeInBytes(), 0, GL_STREAM_READ);
	//ext->glGenBuffers(1, &read_pbo);
	//ext->glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, read_pbo);
	//ext->glBufferData(GL_PIXEL_PACK_BUFFER_ARB, _pbo->getTotalSizeInBytes(), 0, GL_STREAM_READ);

	//Clear colour "black" for representing "no information" => background elimination in natural image, pls.
	_viewer.getCamera()->setClearColor(osg::Vec4f(0.25f, 0.25f, 0.25f, 1.0f));
	_viewer.getCamera()->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	_viewer.getCamera()->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	_viewer.getCamera()->setDrawBuffer(GL_BACK);
	_viewer.getCamera()->setReadBuffer(GL_BACK);
	_viewer.getCamera()->setViewport(0,0,_camera_configuration->GetSX(),_camera_configuration->GetSY());
	_viewer.getCamera()->setProjectionMatrix(osg::Matrixd::perspective(osg::RadiansToDegrees(_camera_configuration->GetFoV()), _camera_configuration->GetAspectRatio(), 0.1, 150.0));
	//looking in geo-coord system
	lookat_matrix = osg::Matrixd::lookAt(osg::Vec3d(0.0, 0.0, -1.0), osg::Vec3d(0.0, 0.0, 1.0), osg::Vec3d(0.0, 1.0, 0.0));
	_viewer.getCamera()->setViewMatrix(lookat_matrix);
	//_viewer.getCamera()->setViewMatrix(osg::Matrixd::lookAt(osg::Vec3d(0.0, 0.0, -1.0), osg::Vec3d(0.0, 0.0, 1.0), osg::Vec3d(-1.0, 0.0, 0.0)));
	//_viewer.getCamera()->setViewMatrix(osg::Matrixd::lookAt(osg::Vec3d(0.0, 0.0, 1.0), osg::Vec3d(0.0, 0.0, 1.0), osg::Vec3d(0.0, 1.0, 0.0)));
#ifdef DEBUG
	std::cout << "Camera set up." << std::endl;
#endif
	_viewer.getCamera()->attach(osg::Camera::COLOR_BUFFER, _pbo.get());


#ifdef FBO
	cb = new SnapshotCallback(_filepath);
	_viewer.getCamera()->setFinalDrawCallback( cb.get() );

	//_viewer.getCamera()->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	_frame->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_RGB, GL_UNSIGNED_BYTE);
	_tex->setTextureSize(_camera_configuration->GetSX(), _camera_configuration->GetSY());
	_tex->setInternalFormat(GL_RGB);
	_tex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	_tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	_tex->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	_tex->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	_tex->setResizeNonPowerOfTwoHint(false);
	_tex->setImage(0,_frame.get());

	//_frame_depth->allocateImage(_camera_configuration->GetSX(), _camera_configuration->GetSY(), 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	//_tex_depth->setTextureSize(_camera_configuration->GetSX(), _camera_configuration->GetSY());
	//_tex_depth->setInternalFormat(GL_DEPTH_COMPONENT);
	//_tex_depth->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	//_tex_depth->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	//_tex_depth->setResizeNonPowerOfTwoHint(false);
	//_tex->setImage(0,_frame_depth.get());

#ifdef DEBUG
	std::cout << "Texture(s) allocated." << std::endl;
#endif


	//_fbo->setAttachment(GL_COLOR_ATTACHMENT0_EXT, osg::FrameBufferAttachment(_tex.get()));
	//_fbo->setAttachment(GL_DEPTH_ATTACHMENT_EXT, osg::FrameBufferAttachment(new osg::RenderBuffer(_camera_configuration->GetSX(), _camera_configuration->GetSY(), GL_DEPTH_COMPONENT24)));
	_fbo->setAttachment(osg::Camera::COLOR_BUFFER, osg::FrameBufferAttachment(_tex.get()));
	_fbo->setAttachment(osg::Camera::DEPTH_BUFFER, osg::FrameBufferAttachment(new osg::RenderBuffer(_camera_configuration->GetSX(), _camera_configuration->GetSY(), GL_DEPTH_COMPONENT24)));
	//_fbo->setAttachment(osg::Camera::DEPTH_BUFFER, osg::FrameBufferAttachment(_tex_depth.get()));
	_viewer.getCamera()->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
	//_viewer.getCamera()->attach(osg::Camera::COLOR_BUFFER, _frame.get());
	//_viewer.getCamera()->attach(osg::Camera::DEPTH_BUFFER, _frame_depth.get());
#ifdef DEBUG
	std::cout << "FBO allocated." << std::endl;
#endif
#endif /* FBO */





#ifdef DEBUG
	std::cout << "View set up." << std::endl;
#endif

	_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	//_viewer.setUpThreading();
	_viewer.realize();



	_viewer.setDone(false);
#ifdef DEBUG
	std::cout << "View realized." << std::endl;
#endif


	//_viewer.setSceneData(_scene.get());
	//_transformer->setMatrix(osg::Matrixd::rotate(osg::DegreesToRadians(90.0), osg::Vec3(1,0,0)));
	_transformer->setMatrix(osg::Matrixd::identity());
	_transformer->addChild(_scene.get());
	_viewer.setSceneData(_transformer.get());
	_viewer.setCameraManipulator(0x0);


	//_scene->releaseGLObjects();
	//_viewer.releaseGLObjects();
	//unsigned int contextID = _viewer.getCamera()->getGraphicsContext()->getState()->getContextID();
	//osg::discardAllGLObjects(contextID);

	// non-mobile
	pre_transform = osg::Matrixd::scale(1,1,-1);

	//std::cout << "Camera Manipulator zeroed." << std::endl;
	_initialized = true;
}

void BoundRenderScene::NextFrame(void)
{
	//OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	if(_frame.valid() && !_viewer.done())
	{
		//osg::State::CheckForGLErrors
		_viewer.advance(0.0);
		osg::Matrixd inverse_cam = osg::Matrixd::inverse(_camera_matrix);
		transformation = inverse_cam * pre_transform;
#ifdef DEBUG
		//std::cout << "View matrix computed." << std::endl;
#endif
		_viewer.getCamera()->setViewMatrix(transformation);
#ifdef DEBUG
		//std::cout << "Matrix and Camera set." << std::endl;
		//std::cout << "Viewport: (" << _viewer.getCamera()->getViewport()->x() << ", " << _viewer.getCamera()->getViewport()->y() << ", " << _viewer.getCamera()->getViewport()->width() << ", " << _viewer.getCamera()->getViewport()->height() << ")" << std::endl;
#endif
		//_viewer.sync();
		_viewer.eventTraversal();
		_viewer.updateTraversal();
		_viewer.renderingTraversals();
		//_viewer.frame();
#ifdef DEBUG
		//std::cout << "Frame computed." << std::endl;
#endif
	}
	else
		std::cout << "Viewer or Camera invalid." << std::endl;
}

void BoundRenderScene::PrepareRaycastIntersection(void)
{


#ifdef DEBUG_1
	//std::cout << "Setting scene data ... " << std::endl;
#endif
	//osg::Camera* camera = _viewer.getCamera();
	//camera->addChild(_scene.get());
	//_intersector->SetScene(camera);
#ifdef DEBUG_1
	//std::cout << "Setting camera model ... " << std::endl;
#endif
	//_intersector->SetCameraModel(_camera_configuration);
#ifdef DEBUG_1
	//std::cout << "Setting up Ray intersector ... " << std::endl;
#endif
	//_intersector->setupIntersector();
}

void BoundRenderScene::RaycastIntersections(void)
{
#ifdef DEBUG_1
	std::cout << "Casting Rays ..." << std::endl;
#endif
	//_intersector->Raycasting();
	_intersector->ComputeIntersections(&_viewer,_viewer.getCamera());
}
