# Directory containing class headers.
SET(VTK_WIDGETS_HEADER_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.8")

# Classes in vtkWidgets.
SET(VTK_WIDGETS_CLASSES
  "vtk3DWidget"
  "vtkAbstractWidget"
  "vtkAffineRepresentation"
  "vtkAffineRepresentation2D"
  "vtkAffineWidget"
  "vtkAngleRepresentation"
  "vtkAngleRepresentation2D"
  "vtkAngleRepresentation3D"
  "vtkAngleWidget"
  "vtkAxesTransformWidget"
  "vtkAxesTransformRepresentation"
  "vtkBalloonRepresentation"
  "vtkBalloonWidget"
  "vtkBezierContourLineInterpolator"
  "vtkBiDimensionalRepresentation"
  "vtkBiDimensionalRepresentation2D"
  "vtkBiDimensionalWidget"
  "vtkBorderRepresentation"
  "vtkBorderWidget"
  "vtkBoundedPlanePointPlacer"
  "vtkBoxRepresentation"
  "vtkBoxWidget"
  "vtkBoxWidget2"
  "vtkButtonRepresentation"
  "vtkButtonWidget"
  "vtkCameraRepresentation"
  "vtkCameraWidget"
  "vtkCaptionRepresentation"
  "vtkCaptionWidget"
  "vtkCenteredSliderRepresentation"
  "vtkCenteredSliderWidget"
  "vtkContinuousValueWidget"
  "vtkContinuousValueWidgetRepresentation"
  "vtkContourLineInterpolator"
  "vtkContourRepresentation"
  "vtkFocalPlaneContourRepresentation"
  "vtkContourWidget"
  "vtkCheckerboardRepresentation"
  "vtkCheckerboardWidget"
  "vtkConstrainedPointHandleRepresentation"
  "vtkDijkstraImageContourLineInterpolator"
  "vtkDistanceWidget"
  "vtkDistanceRepresentation"
  "vtkDistanceRepresentation2D"
  "vtkDistanceRepresentation3D"
  "vtkEllipsoidTensorProbeRepresentation"
  "vtkEvent"
  "vtkFocalPlanePointPlacer"
  "vtkHandleRepresentation"
  "vtkHandleWidget"
  "vtkHoverWidget"
  "vtkImageActorPointPlacer"
  "vtkImageOrthoPlanes"
  "vtkImagePlaneWidget"
  "vtkImageTracerWidget"
  "vtkImplicitPlaneRepresentation"
  "vtkImplicitPlaneWidget"
  "vtkImplicitPlaneWidget2"
  "vtkLinearContourLineInterpolator"
  "vtkLineRepresentation"
  "vtkLineWidget"
  "vtkLineWidget2"
  "vtkLogoRepresentation"
  "vtkLogoWidget"
  "vtkOrientationMarkerWidget"
  "vtkOrientedGlyphContourRepresentation"
  "vtkOrientedGlyphFocalPlaneContourRepresentation"
  "vtkParallelopipedRepresentation"
  "vtkParallelopipedWidget"
  "vtkClosedSurfacePointPlacer"
  "vtkPlaneWidget"
  "vtkPlaybackRepresentation"
  "vtkPlaybackWidget"
  "vtkPointHandleRepresentation2D"
  "vtkPointHandleRepresentation3D"
  "vtkPointPlacer"
  "vtkPointWidget"
  "vtkPolyDataSourceWidget"
  "vtkPolyDataPointPlacer"
  "vtkAbstractPolygonalHandleRepresentation3D"
  "vtkPolygonalHandleRepresentation3D"
  "vtkOrientedPolygonalHandleRepresentation3D"
  "vtkPolygonalSurfacePointPlacer"
  "vtkPolyDataContourLineInterpolator"
  "vtkPolygonalSurfaceContourLineInterpolator"
  "vtkProp3DButtonRepresentation"
  "vtkRectilinearWipeRepresentation"
  "vtkRectilinearWipeWidget"
  "vtkScalarBarRepresentation"
  "vtkScalarBarWidget"
  "vtkSeedRepresentation"
  "vtkSeedWidget"
  "vtkSliderRepresentation"
  "vtkSliderRepresentation2D"
  "vtkSliderRepresentation3D"
  "vtkSliderWidget"
  "vtkSphereHandleRepresentation"
  "vtkSphereRepresentation"
  "vtkSphereWidget"
  "vtkSphereWidget2"
  "vtkSplineRepresentation"
  "vtkSplineWidget"
  "vtkSplineWidget2"
  "vtkTensorProbeWidget"
  "vtkTensorProbeRepresentation"
  "vtkTerrainDataPointPlacer"
  "vtkTerrainContourLineInterpolator"
  "vtkTextRepresentation"
  "vtkTexturedButtonRepresentation"
  "vtkTexturedButtonRepresentation2D"
  "vtkTextWidget"
  "vtkWidgetCallbackMapper"
  "vtkWidgetEvent"
  "vtkWidgetEventTranslator"
  "vtkWidgetRepresentation"
  "vtkWidgetSet"
  "vtkXYPlotWidget")

# Abstract classes in vtkWidgets.
SET(VTK_WIDGETS_CLASSES_ABSTRACT
  "vtk3DWidget"
  "vtkAbstractWidget"
  "vtkAffineRepresentation"
  "vtkAngleRepresentation"
  "vtkBiDimensionalRepresentation"
  "vtkButtonRepresentation"
  "vtkContinuousValueWidget"
  "vtkContinuousValueWidgetRepresentation"
  "vtkContourLineInterpolator"
  "vtkContourRepresentation"
  "vtkFocalPlaneContourRepresentation"
  "vtkDistanceRepresentation"
  "vtkHandleRepresentation"
  "vtkPolyDataSourceWidget"
  "vtkAbstractPolygonalHandleRepresentation3D"
  "vtkPolyDataContourLineInterpolator"
  "vtkSliderRepresentation"
  "vtkTensorProbeRepresentation"
  "vtkWidgetRepresentation")

# Wrap-exclude classes in vtkWidgets.
SET(VTK_WIDGETS_CLASSES_WRAP_EXCLUDE)

# Wrap-special classes in vtkWidgets.
SET(VTK_WIDGETS_CLASSES_WRAP_SPECIAL)

# Wrappable non-class headers for vtkWidgets.
SET(VTK_WIDGETS_WRAP_HEADERS)

# Set convenient variables to test each class.
FOREACH(class ${VTK_WIDGETS_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_WIDGETS_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_WIDGETS_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_WIDGETS_CLASSES_WRAP_SPECIAL})
  SET(VTK_CLASS_WRAP_SPECIAL_${class} 1)
ENDFOREACH(class)
