#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "vtkWrapTcl" for configuration "Debug"
SET_PROPERTY(TARGET vtkWrapTcl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWrapTcl PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkWrapTcl"
  )

# Import target "vtkWrapTclInit" for configuration "Debug"
SET_PROPERTY(TARGET vtkWrapTclInit APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWrapTclInit PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkWrapTclInit"
  )

# Import target "vtkWrapPython" for configuration "Debug"
SET_PROPERTY(TARGET vtkWrapPython APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWrapPython PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkWrapPython"
  )

# Import target "vtkWrapPythonInit" for configuration "Debug"
SET_PROPERTY(TARGET vtkWrapPythonInit APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWrapPythonInit PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkWrapPythonInit"
  )

# Import target "vtkParseJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkParseJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkParseJava PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkParseJava"
  )

# Import target "vtkWrapJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkWrapJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWrapJava PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkWrapJava"
  )

# Import target "vtksys" for configuration "Debug"
SET_PROPERTY(TARGET vtksys APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtksys PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "dl"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtksys.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtksys.so.5.8"
  )

# Import target "vtkDICOMParser" for configuration "Debug"
SET_PROPERTY(TARGET vtkDICOMParser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkDICOMParser PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkDICOMParser.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkDICOMParser.so.5.8"
  )

# Import target "vtkproj4" for configuration "Debug"
SET_PROPERTY(TARGET vtkproj4 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkproj4 PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "m"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkproj4.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkproj4.so.5.8"
  )

# Import target "vtkverdict" for configuration "Debug"
SET_PROPERTY(TARGET vtkverdict APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkverdict PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkverdict.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkverdict.so.5.8"
  )

# Import target "vtkmetaio" for configuration "Debug"
SET_PROPERTY(TARGET vtkmetaio APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkmetaio PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/x86_64-linux-gnu/libz.so;vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkmetaio.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkmetaio.so.5.8"
  )

# Import target "vtkexoIIc" for configuration "Debug"
SET_PROPERTY(TARGET vtkexoIIc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkexoIIc PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "netcdf"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkexoIIc.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkexoIIc.so.5.8"
  )

# Import target "vtkalglib" for configuration "Debug"
SET_PROPERTY(TARGET vtkalglib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkalglib PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkalglib.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkalglib.so.5.8"
  )

# Import target "vtkEncodeString" for configuration "Debug"
SET_PROPERTY(TARGET vtkEncodeString APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkEncodeString PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkEncodeString"
  )

# Import target "VPIC" for configuration "Debug"
SET_PROPERTY(TARGET VPIC APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(VPIC PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtksys;/usr/lib/openmpi/lib/libmpi_cxx.so;/usr/lib/openmpi/lib/libmpi.so;/usr/lib/openmpi/lib/libopen-rte.so;/usr/lib/openmpi/lib/libopen-pal.so;/usr/lib/x86_64-linux-gnu/libdl.so;/usr/lib/x86_64-linux-gnu/libnsl.so;/usr/lib/x86_64-linux-gnu/libutil.so;/usr/lib/x86_64-linux-gnu/libm.so;/usr/lib/x86_64-linux-gnu/libdl.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libVPIC.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libVPIC.so.5.8"
  )

# Import target "Cosmo" for configuration "Debug"
SET_PROPERTY(TARGET Cosmo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(Cosmo PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtksys;vtkCommon;/usr/lib/openmpi/lib/libmpi_cxx.so;/usr/lib/openmpi/lib/libmpi.so;/usr/lib/openmpi/lib/libopen-rte.so;/usr/lib/openmpi/lib/libopen-pal.so;/usr/lib/x86_64-linux-gnu/libdl.so;/usr/lib/x86_64-linux-gnu/libnsl.so;/usr/lib/x86_64-linux-gnu/libutil.so;/usr/lib/x86_64-linux-gnu/libm.so;/usr/lib/x86_64-linux-gnu/libdl.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libCosmo.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libCosmo.so.5.8"
  )

# Import target "vtkftgl" for configuration "Debug"
SET_PROPERTY(TARGET vtkftgl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkftgl PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/x86_64-linux-gnu/libGL.so;/usr/lib/x86_64-linux-gnu/libfreetype.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkftgl.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkftgl.so.5.8"
  )

# Import target "vtkCommonTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkCommonTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkCommonTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtksys;-lm"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkCommonTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkCommonTCL.so.5.8"
  )

# Import target "vtkCommonPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkCommonPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkCommonPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkCommon;vtkPythonCore"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtksys;-lm"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkCommonPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkCommonPythonD.so.5.8"
  )

# Import target "vtkCommonJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkCommonJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkCommonJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkCommonJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkCommonJava.so.5.8"
  )

# Import target "vtkCommon" for configuration "Debug"
SET_PROPERTY(TARGET vtkCommon APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkCommon PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtksys;-lm"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkCommon.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkCommon.so.5.8"
  )

# Import target "vtkFilteringTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkFilteringTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkFilteringTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkFiltering;vtkCommonTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkFilteringTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkFilteringTCL.so.5.8"
  )

# Import target "vtkFilteringPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkFilteringPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkFilteringPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkFiltering;vtkPythonCore;vtkCommonPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkFilteringPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkFilteringPythonD.so.5.8"
  )

# Import target "vtkFilteringJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkFilteringJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkFilteringJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering;vtkCommonJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkFilteringJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkFilteringJava.so.5.8"
  )

# Import target "vtkFiltering" for configuration "Debug"
SET_PROPERTY(TARGET vtkFiltering APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkFiltering PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkFiltering.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkFiltering.so.5.8"
  )

# Import target "vtkImagingTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkImagingTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkImagingTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkImaging;vtkFilteringTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkImagingTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkImagingTCL.so.5.8"
  )

# Import target "vtkImagingPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkImagingPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkImagingPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkImaging;vtkPythonCore;vtkFilteringPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkImagingPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkImagingPythonD.so.5.8"
  )

# Import target "vtkImagingJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkImagingJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkImagingJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkImaging;vtkFilteringJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkImagingJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkImagingJava.so.5.8"
  )

# Import target "vtkImaging" for configuration "Debug"
SET_PROPERTY(TARGET vtkImaging APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkImaging PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkImaging.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkImaging.so.5.8"
  )

# Import target "vtkGraphicsTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkGraphicsTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGraphicsTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGraphics;vtkFilteringTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGraphicsTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGraphicsTCL.so.5.8"
  )

# Import target "vtkGraphicsPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkGraphicsPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGraphicsPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGraphics;vtkPythonCore;vtkFilteringPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGraphicsPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGraphicsPythonD.so.5.8"
  )

# Import target "vtkGraphicsJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkGraphicsJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGraphicsJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGraphics;vtkFilteringJava;/usr/lib/jvm/default-java/jre/lib/amd64/libjawt.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkGraphicsJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGraphicsJava.so.5.8"
  )

# Import target "vtkGraphics" for configuration "Debug"
SET_PROPERTY(TARGET vtkGraphics APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGraphics PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkverdict"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGraphics.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGraphics.so.5.8"
  )

# Import target "vtkGenericFilteringTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkGenericFilteringTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGenericFilteringTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGenericFiltering;vtkFilteringTCL;vtkGraphicsTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering;vtkGraphics"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGenericFilteringTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGenericFilteringTCL.so.5.8"
  )

# Import target "vtkGenericFilteringPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkGenericFilteringPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGenericFilteringPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGenericFiltering;vtkPythonCore;vtkFilteringPythonD;vtkGraphicsPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering;vtkGraphics"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGenericFilteringPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGenericFilteringPythonD.so.5.8"
  )

# Import target "vtkGenericFilteringJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkGenericFilteringJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGenericFilteringJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGenericFiltering;vtkFilteringJava;vtkGraphicsJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkGenericFilteringJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGenericFilteringJava.so.5.8"
  )

# Import target "vtkGenericFiltering" for configuration "Debug"
SET_PROPERTY(TARGET vtkGenericFiltering APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGenericFiltering PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering;vtkGraphics"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGenericFiltering.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGenericFiltering.so.5.8"
  )

# Import target "vtkIOTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkIOTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkIOTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkIO;vtkFilteringTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkIOTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkIOTCL.so.5.8"
  )

# Import target "vtkIOPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkIOPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkIOPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkIO;vtkPythonCore;vtkFilteringPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkIOPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkIOPythonD.so.5.8"
  )

# Import target "vtkIOJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkIOJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkIOJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/libpq.so;/usr/lib/x86_64-linux-gnu/libmysqlclient.so;/usr/lib/x86_64-linux-gnu/libz.so;vtkIO;vtkFilteringJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkIOJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkIOJava.so.5.8"
  )

# Import target "vtkIO" for configuration "Debug"
SET_PROPERTY(TARGET vtkIO APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkIO PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkDICOMParser;vtkmetaio;vtksys"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkFiltering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkIO.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkIO.so.5.8"
  )

# Import target "vtkRenderingTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkRenderingTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkRenderingTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkRendering;vtkGraphicsTCL;vtkImagingTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGraphics;vtkImaging"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkRenderingTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkRenderingTCL.so.5.8"
  )

# Import target "vtkRenderingPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkRenderingPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkRenderingPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkRendering;vtkPythonCore;vtkGraphicsPythonD;vtkImagingPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGraphics;vtkImaging"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkRenderingPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkRenderingPythonD.so.5.8"
  )

# Import target "vtkRenderingJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkRenderingJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkRenderingJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkGraphicsJava;vtkImagingJava;/usr/lib/jvm/default-java/jre/lib/amd64/libjawt.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkRenderingJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkRenderingJava.so.5.8"
  )

# Import target "vtkRendering" for configuration "Debug"
SET_PROPERTY(TARGET vtkRendering APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkRendering PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkIO;vtkftgl"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGraphics;vtkImaging"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkRendering.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkRendering.so.5.8"
  )

# Import target "vtkRenderingPythonTkWidgets" for configuration "Debug"
SET_PROPERTY(TARGET vtkRenderingPythonTkWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkRenderingPythonTkWidgets PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;/usr/lib/libtk8.5.so;/usr/lib/libtcl8.5.so;m;X11"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkRenderingPythonTkWidgets.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkRenderingPythonTkWidgets.so.5.8"
  )

# Import target "vtkVolumeRenderingTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkVolumeRenderingTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkVolumeRenderingTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkVolumeRendering;vtkRenderingTCL;vtkIOTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkVolumeRenderingTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkVolumeRenderingTCL.so.5.8"
  )

# Import target "vtkVolumeRenderingPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkVolumeRenderingPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkVolumeRenderingPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkVolumeRendering;vtkPythonCore;vtkRenderingPythonD;vtkIOPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkVolumeRenderingPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkVolumeRenderingPythonD.so.5.8"
  )

# Import target "vtkVolumeRenderingJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkVolumeRenderingJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkVolumeRenderingJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkVolumeRendering;vtkRenderingJava;vtkIOJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkVolumeRenderingJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkVolumeRenderingJava.so.5.8"
  )

# Import target "vtkVolumeRendering" for configuration "Debug"
SET_PROPERTY(TARGET vtkVolumeRendering APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkVolumeRendering PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkVolumeRendering.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkVolumeRendering.so.5.8"
  )

# Import target "vtkHybridTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkHybridTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkHybridTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkHybrid;vtkRenderingTCL;vtkIOTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkHybridTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkHybridTCL.so.5.8"
  )

# Import target "vtkHybridPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkHybridPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkHybridPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkHybrid;vtkPythonCore;vtkRenderingPythonD;vtkIOPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkHybridPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkHybridPythonD.so.5.8"
  )

# Import target "vtkHybridJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkHybridJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkHybridJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkHybrid;vtkRenderingJava;vtkIOJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkHybridJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkHybridJava.so.5.8"
  )

# Import target "vtkHybrid" for configuration "Debug"
SET_PROPERTY(TARGET vtkHybrid APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkHybrid PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkexoIIc;vtkftgl"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkHybrid.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkHybrid.so.5.8"
  )

# Import target "vtkWidgetsTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkWidgetsTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWidgetsTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkWidgets;vtkRenderingTCL;vtkHybridTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkHybrid;vtkVolumeRendering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkWidgetsTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkWidgetsTCL.so.5.8"
  )

# Import target "vtkWidgetsPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkWidgetsPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWidgetsPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkWidgets;vtkPythonCore;vtkRenderingPythonD;vtkHybridPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkHybrid;vtkVolumeRendering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkWidgetsPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkWidgetsPythonD.so.5.8"
  )

# Import target "vtkWidgetsJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkWidgetsJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWidgetsJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkRenderingJava;vtkHybridJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkWidgetsJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkWidgetsJava.so.5.8"
  )

# Import target "vtkWidgets" for configuration "Debug"
SET_PROPERTY(TARGET vtkWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkWidgets PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkHybrid;vtkVolumeRendering"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkWidgets.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkWidgets.so.5.8"
  )

# Import target "vtkParallelTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkParallelTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkParallelTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkParallel;vtkRenderingTCL;vtkIOTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkParallelTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkParallelTCL.so.5.8"
  )

# Import target "vtkParallelPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkParallelPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkParallelPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkParallel;vtkPythonCore;vtkRenderingPythonD;vtkIOPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkParallelPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkParallelPythonD.so.5.8"
  )

# Import target "vtkParallelJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkParallelJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkParallelJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkParallel;vtkRenderingJava;vtkIOJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkParallelJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkParallelJava.so.5.8"
  )

# Import target "vtkParallel" for configuration "Debug"
SET_PROPERTY(TARGET vtkParallel APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkParallel PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "VPIC;Cosmo;vtkexoIIc"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkRendering;vtkIO"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkParallel.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkParallel.so.5.8"
  )

# Import target "vtkInfovisTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkInfovisTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkInfovisTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkInfovis;vtkWidgetsTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkInfovisTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkInfovisTCL.so.5.8"
  )

# Import target "vtkInfovisPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkInfovisPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkInfovisPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkInfovis;vtkPythonCore;vtkWidgetsPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkInfovisPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkInfovisPythonD.so.5.8"
  )

# Import target "vtkInfovisJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkInfovisJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkInfovisJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkInfovis;vtkWidgetsJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkInfovisJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkInfovisJava.so.5.8"
  )

# Import target "vtkInfovis" for configuration "Debug"
SET_PROPERTY(TARGET vtkInfovis APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkInfovis PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkalglib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkParallel"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkInfovis.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkInfovis.so.5.8"
  )

# Import target "vtkGeovisTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkGeovisTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGeovisTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGeovis;vtkWidgetsTCL;vtkViewsTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGeovisTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGeovisTCL.so.5.8"
  )

# Import target "vtkGeovisPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkGeovisPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGeovisPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkGeovis;vtkPythonCore;vtkWidgetsPythonD;vtkViewsPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGeovisPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGeovisPythonD.so.5.8"
  )

# Import target "vtkGeovisJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkGeovisJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGeovisJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkGeovis;vtkWidgetsJava;vtkViewsJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkGeovisJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGeovisJava.so.5.8"
  )

# Import target "vtkGeovis" for configuration "Debug"
SET_PROPERTY(TARGET vtkGeovis APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkGeovis PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkproj4"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkWidgets;vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkGeovis.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkGeovis.so.5.8"
  )

# Import target "vtkViewsTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkViewsTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkViewsTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkViews;vtkInfovisTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkInfovis"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkViewsTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkViewsTCL.so.5.8"
  )

# Import target "vtkViewsPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkViewsPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkViewsPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkViews;vtkPythonCore;vtkInfovisPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkInfovis"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkViewsPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkViewsPythonD.so.5.8"
  )

# Import target "vtkViewsJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkViewsJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkViewsJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkViews;vtkInfovisJava"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkViewsJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkViewsJava.so.5.8"
  )

# Import target "vtkViews" for configuration "Debug"
SET_PROPERTY(TARGET vtkViews APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkViews PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkInfovis"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkViews.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkViews.so.5.8"
  )

# Import target "vtkQtChart" for configuration "Debug"
SET_PROPERTY(TARGET vtkQtChart APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkQtChart PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/x86_64-linux-gnu/libQtGui.so;/usr/lib/x86_64-linux-gnu/libQtSql.so;/usr/lib/x86_64-linux-gnu/libQtNetwork.so;/usr/lib/x86_64-linux-gnu/libQtCore.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkQtChart.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkQtChart.so.5.8"
  )

# Import target "QVTK" for configuration "Debug"
SET_PROPERTY(TARGET QVTK APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(QVTK PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib/x86_64-linux-gnu/libQtGui.so;/usr/lib/x86_64-linux-gnu/libQtSql.so;/usr/lib/x86_64-linux-gnu/libQtNetwork.so;/usr/lib/x86_64-linux-gnu/libQtCore.so;vtkRendering;vtkGraphics;vtkImaging;vtkCommon;vtkViews;vtkQtChart"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libQVTK.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libQVTK.so.5.8"
  )

# Import target "vtkChartsTCL" for configuration "Debug"
SET_PROPERTY(TARGET vtkChartsTCL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkChartsTCL PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkCharts;vtkViewsTCL"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkChartsTCL.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkChartsTCL.so.5.8"
  )

# Import target "vtkChartsPythonD" for configuration "Debug"
SET_PROPERTY(TARGET vtkChartsPythonD APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkChartsPythonD PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkCharts;vtkPythonCore;vtkViewsPythonD"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkChartsPythonD.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkChartsPythonD.so.5.8"
  )

# Import target "vtkChartsJava" for configuration "Debug"
SET_PROPERTY(TARGET vtkChartsJava APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkChartsJava PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCharts;vtkViewsJava;/usr/lib/jvm/default-java/jre/lib/amd64/libjawt.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/jni/libvtkChartsJava.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkChartsJava.so.5.8"
  )

# Import target "vtkCharts" for configuration "Debug"
SET_PROPERTY(TARGET vtkCharts APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkCharts PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkftgl"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkViews"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkCharts.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkCharts.so.5.8"
  )

# Import target "vtk" for configuration "Debug"
SET_PROPERTY(TARGET vtk APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtk PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtk"
  )

# Import target "pvtk" for configuration "Debug"
SET_PROPERTY(TARGET pvtk APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(pvtk PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/pvtk"
  )

# Import target "vtkPythonCore" for configuration "Debug"
SET_PROPERTY(TARGET vtkPythonCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(vtkPythonCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "vtkCommon"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libvtkPythonCore.so.5.8.0"
  IMPORTED_SONAME_DEBUG "libvtkPythonCore.so.5.8"
  )

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
