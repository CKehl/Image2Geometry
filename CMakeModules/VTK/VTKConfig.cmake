#-----------------------------------------------------------------------------
#
# VTKConfig.cmake - VTK CMake configuration file for external projects.
#
# This file is configured by VTK and used by the UseVTK.cmake module
# to load VTK's settings for an external project.

# Compute the installation prefix from VTK_DIR.
SET(VTK_INSTALL_PREFIX "${VTK_DIR}")
GET_FILENAME_COMPONENT(VTK_INSTALL_PREFIX "${VTK_INSTALL_PREFIX}" PATH)
GET_FILENAME_COMPONENT(VTK_INSTALL_PREFIX "${VTK_INSTALL_PREFIX}" PATH)


# The set of VTK libraries
SET(VTK_LIBRARIES "vtkCommon;vtkFiltering;vtkImaging;vtkGraphics;vtkGenericFiltering;vtkIO;vtkRendering;vtkVolumeRendering;vtkHybrid;vtkWidgets;vtkParallel;vtkInfovis;vtkGeovis;vtkViews;vtkCharts")

# The VTK include file directories.
SET(VTK_INCLUDE_DIRS "${VTK_INSTALL_PREFIX}/include/vtk-5.8")

# The VTK library directories.
SET(VTK_LIBRARY_DIRS "${VTK_INSTALL_PREFIX}/lib/")

# The VTK binary executable directories.  Note that if
# VTK_CONFIGURATION_TYPES is set (see below) then these directories
# will be the parent directories under which there will be a directory
# of runtime binaries for each configuration type.
SET(VTK_EXECUTABLE_DIRS "${VTK_INSTALL_PREFIX}/bin")

# The VTK runtime library directories.  Note that if
# VTK_CONFIGURATION_TYPES is set (see below) then these directories
# will be the parent directories under which there will be a directory
# of runtime libraries for each configuration type.
SET(VTK_RUNTIME_LIBRARY_DIRS "${VTK_INSTALL_PREFIX}/lib/")

# The runtime library path variable name e.g. LD_LIBRARY_PATH,
# this environment variable should be set to VTK_RUNTIME_LIBRARY_DIRS
SET(VTK_RUNTIME_PATH_VAR_NAME "LD_LIBRARY_PATH")

# The C and C++ flags added by VTK to the cmake-configured flags.
SET(VTK_REQUIRED_C_FLAGS "")
SET(VTK_REQUIRED_CXX_FLAGS " -Wno-deprecated")
SET(VTK_REQUIRED_EXE_LINKER_FLAGS "")
SET(VTK_REQUIRED_SHARED_LINKER_FLAGS "")
SET(VTK_REQUIRED_MODULE_LINKER_FLAGS "")

# The VTK version number
SET(VTK_MAJOR_VERSION "5")
SET(VTK_MINOR_VERSION "8")
SET(VTK_BUILD_VERSION "0")

# The location of the UseVTK.cmake file.
SET(VTK_USE_FILE "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/UseVTK.cmake")

# The build settings file.
SET(VTK_BUILD_SETTINGS_FILE "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/VTKBuildSettings.cmake")

# The directory containing class list files for each kit.
SET(VTK_KITS_DIR "${VTK_INSTALL_PREFIX}/lib/vtk-5.8")

# The wrapping hints file.
SET(VTK_WRAP_HINTS "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/hints")

# CMake extension module directory and macro file.
SET(VTK_LOAD_CMAKE_EXTENSIONS_MACRO "/build/buildd/vtk-5.8.0/CMake/vtkLoadCMakeExtensions.cmake")
SET(VTK_CMAKE_DIR "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/CMake")
SET(VTK_CMAKE_EXTENSIONS_DIR "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/CMake")

# The list of available kits.
SET(VTK_KITS "COMMON;FILTERING;IO;GRAPHICS;GENERIC_FILTERING;IMAGING;RENDERING;VOLUMERENDERING;HYBRID;WIDGETS;PARALLEL;INFOVIS;GEOVIS;VIEWS;QVTK;CHARTS")

# The list of available languages.
SET(VTK_LANGUAGES "TCL;PYTHON;JAVA")

# VTK Configuration options.
SET(VTK_BUILD_SHARED_LIBS "ON")
SET(VTK_DEBUG_LEAKS "OFF")
SET(VTK_HAVE_VP1000 "")
SET(VTK_LEGACY_REMOVE "OFF")
SET(VTK_LEGACY_SILENT "OFF")
SET(VTK_OPENGL_HAS_OSMESA "OFF")
SET(VTK_USE_64BIT_IDS "ON")
SET(VTK_USE_ANSI_STDLIB "ON")
SET(VTK_USE_BOOST "ON")
SET(VTK_USE_QT "ON")
SET(VTK_USE_CARBON "OFF")
SET(VTK_USE_CG_SHADERS "OFF")
SET(VTK_USE_CHARTS "ON")
SET(VTK_USE_COCOA "OFF")
SET(VTK_USE_GEOVIS "ON")
SET(VTK_USE_GL2PS "ON")
SET(VTK_USE_GLSL_SHADERS "ON")
SET(VTK_USE_GNU_R "OFF")
SET(VTK_USE_GUISUPPORT "1")
SET(VTK_USE_INFOVIS "ON")
SET(VTK_USE_MANGLED_MESA "OFF")
SET(VTK_USE_MATLAB_MEX "OFF")
SET(VTK_USE_MATROX_IMAGING "OFF")
SET(VTK_USE_METAIO "ON")
SET(VTK_USE_MFC "")
SET(VTK_USE_MPI "ON")
SET(VTK_USE_MYSQL "ON")
SET(VTK_USE_N_WAY_ARRAYS "ON")
SET(VTK_USE_ODBC "OFF")
SET(VTK_USE_PARALLEL "ON")
SET(VTK_USE_PARALLEL_BGL "OFF")
SET(VTK_USE_POSTGRES "ON") 
SET(VTK_USE_QVTK "ON")
SET(VTK_USE_QVTK_OPENGL "")
SET(VTK_USE_RENDERING "ON")
SET(VTK_USE_TDX "OFF")
SET(VTK_USE_TEXT_ANALYSIS "OFF")
SET(VTK_USE_TK "ON")
SET(VTK_USE_TK "ON")
SET(VTK_USE_VIDEO_FOR_WINDOWS "")
SET(VTK_USE_VIEWS "ON")
SET(VTK_USE_VOLUMEPRO_1000 "OFF")
SET(VTK_USE_X "ON")
SET(VTK_WRAP_JAVA "ON")
SET(VTK_WRAP_PYTHON "ON")
SET(VTK_WRAP_TCL "ON")
SET(VTK_WRAP_PYTHON_SIP "OFF")

# The Hybrid and VolumeRendering kits are now switched with Rendering.
SET(VTK_USE_HYBRID "ON")
SET(VTK_USE_VOLUMERENDERING "ON")

# The MPI configuration
SET(VTK_MPIRUN_EXE "VTK_MPIRUN_EXE-NOTFOUND")
SET(VTK_MPI_CLIENT_POSTFLAGS "")
SET(VTK_MPI_CLIENT_PREFLAGS "")
SET(VTK_MPI_MAX_NUMPROCS "2")
SET(VTK_MPI_PRENUMPROC_FLAGS "")
SET(VTK_MPI_NUMPROC_FLAG "-np")
SET(VTK_MPI_POSTFLAGS "")
SET(VTK_MPI_PREFLAGS "")
SET(VTK_MPI_SERVER_POSTFLAGS "")
SET(VTK_MPI_SERVER_PREFLAGS "")
SET(VTK_MPI_INCLUDE_DIR "/usr/include/mpi")
SET(VTK_MPI_LIBRARIES "/usr/lib/openmpi/lib/libmpi_cxx.so;/usr/lib/openmpi/lib/libmpi.so;/usr/lib/openmpi/lib/libopen-rte.so;/usr/lib/openmpi/lib/libopen-pal.so;/usr/lib/x86_64-linux-gnu/libdl.so;/usr/lib/x86_64-linux-gnu/libnsl.so;/usr/lib/x86_64-linux-gnu/libutil.so;/usr/lib/x86_64-linux-gnu/libm.so;/usr/lib/x86_64-linux-gnu/libdl.so")

# The Tcl/Tk configuration.
SET(VTK_TCL_TK_STATIC "OFF")
SET(VTK_TCL_TK_COPY_SUPPORT_LIBRARY "OFF")
SET(VTK_TCL_SUPPORT_LIBRARY_PATH "")
SET(VTK_TK_SUPPORT_LIBRARY_PATH "")
SET(VTK_TCL_TK_MACROS_MODULE "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/CMake/vtkTclTkMacros.cmake")
SET(VTK_TCL_HOME "${VTK_INSTALL_PREFIX}/lib/")
SET(VTK_WRAP_TCL_EXE "${VTK_INSTALL_PREFIX}/bin/vtkWrapTcl")
SET(VTK_WRAP_TCL_INIT_EXE "${VTK_INSTALL_PREFIX}/bin/vtkWrapTclInit")
SET(VTK_TK_INTERNAL_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.8/TclTk/internals/tk8.5")
SET(VTK_TK_RESOURCES_DIR "")
SET(VTK_TCL_INCLUDE_DIR "/usr/include/tcl8.5")
SET(VTK_TCL_LIBRARY "/usr/lib/libtcl8.5.so")
SET(VTK_TK_INCLUDE_DIR "/usr/include/tcl8.5")
SET(VTK_TK_LIBRARY "/usr/lib/libtk8.5.so")

# The Java configuration.
SET(VTK_JAVA_JAR "${VTK_INSTALL_PREFIX}/share/java/vtk.jar")
SET(VTK_PARSE_JAVA_EXE "${VTK_INSTALL_PREFIX}/bin/vtkParseJava")
SET(VTK_WRAP_JAVA_EXE "${VTK_INSTALL_PREFIX}/bin/vtkWrapJava")
SET(VTK_JAVA_INCLUDE_DIR "/usr/lib/jvm/default-java/include;/usr/lib/jvm/default-java/include")
SET(VTK_JAVA_AWT_LIBRARY "/usr/lib/jvm/default-java/jre/lib/amd64/libjawt.so")
SET(VTK_JVM_LIBRARY "/usr/lib/jvm/default-java/jre/lib/amd64/server/libjvm.so")

# The Matlab configuration.
SET(VTK_MATLAB_ROOT_DIR "")
SET(VTK_MATLAB_INCLUDE_DIR "")
SET(VTK_MATLAB_LIB_DIR "")

# The Python configuration.
# If VTK_CONFIGURATION_TYPES is set (see below) then the VTK_PYTHONPATH_DIRS
# will have subdirectories for each configuration type.
SET(VTK_PYTHONPATH_DIRS "/usr/lib/python2.7/site-packages;/usr/lib/python2.7/site-packages")
SET(VTK_WRAP_PYTHON_EXE "${VTK_INSTALL_PREFIX}/bin/vtkWrapPython")
SET(VTK_WRAP_PYTHON_INIT_EXE "${VTK_INSTALL_PREFIX}/bin/vtkWrapPythonInit")
SET(VTK_PYTHON_INCLUDE_DIR "/usr/include/python2.7")
SET(VTK_PYTHON_LIBRARY "/usr/lib/libpython2.7.so")

# Other executables
SET(VTK_ENCODESTRING_EXE "${VTK_INSTALL_PREFIX}/bin/vtkEncodeString")

# The Doxygen configuration.
SET(VTK_DOXYGEN_HOME "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/doxygen")

# The VTK test script locations.
SET(VTK_HEADER_TESTING_PY "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/testing/HeaderTesting.py")
SET(VTK_FIND_STRING_TCL "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/testing/FindString.tcl")
SET(VTK_PRINT_SELF_CHECK_TCL "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/testing/PrintSelfCheck.tcl")
SET(VTK_RT_IMAGE_TEST_TCL "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/testing/rtImageTest.tcl")
SET(VTK_PRT_IMAGE_TEST_TCL "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/testing/prtImageTest.tcl")

# The names of utility libraries used by VTK.
SET(VTK_PNG_LIBRARIES      "/usr/lib/x86_64-linux-gnu/libpng.so;/usr/lib/x86_64-linux-gnu/libz.so")
SET(VTK_ZLIB_LIBRARIES     "/usr/lib/x86_64-linux-gnu/libz.so")
SET(VTK_JPEG_LIBRARIES     "/usr/lib/x86_64-linux-gnu/libjpeg.so")
SET(VTK_TIFF_LIBRARIES     "/usr/lib/x86_64-linux-gnu/libtiff.so")
SET(VTK_EXPAT_LIBRARIES    "/usr/lib/x86_64-linux-gnu/libexpat.so")
SET(VTK_FREETYPE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libfreetype.so")
SET(VTK_LIBXML2_LIBRARIES  "/usr/lib/x86_64-linux-gnu/libxml2.so")
SET(VTK_LIBPROJ4_LIBRARIES "vtkproj4")
SET(VTK_HDF5_LIBRARIES     "debug;/usr/lib/libhdf5.so;optimized;/usr/lib/libhdf5.so")

# The VTK Qt configuration.
IF(VTK_USE_QVTK)
  INCLUDE(${VTK_DIR}/VTKConfigQt.cmake)
ENDIF(VTK_USE_QVTK)

# Relative install paths in the VTK install tree
SET(VTK_INSTALL_BIN_DIR "/bin")
SET(VTK_INSTALL_INCLUDE_DIR "/include/vtk-5.8")
SET(VTK_INSTALL_LIB_DIR "/lib/")
SET(VTK_INSTALL_PACKAGE_DIR "/lib/vtk-5.8")

# A VTK install tree always provides one build configuration.  A VTK
# build tree may provide either one or multiple build configurations
# depending on the CMake generator used.  Since VTK can be used either
# from a build tree or an install tree it is useful for outside
# projects to know the configurations available.  If this
# VTKConfig.cmake is in a VTK install tree VTK_CONFIGURATION_TYPES
# will be empty and VTK_BUILD_TYPE will be set to the value of
# CMAKE_BUILD_TYPE used to build VTK.  If VTKConfig.cmake is in a VTK
# build tree then VTK_CONFIGURATION_TYPES and VTK_BUILD_TYPE will have
# values matching CMAKE_CONFIGURATION_TYPES and CMAKE_BUILD_TYPE for
# that build tree (only one will ever be set).
SET(VTK_CONFIGURATION_TYPES )
SET(VTK_BUILD_TYPE Debug)

# The VTK targets file.
IF(NOT VTK_INSTALL_EXPORT_NAME AND NOT TARGET vtkCommon
   AND EXISTS "${VTK_INSTALL_PREFIX}/lib/vtk-5.8/VTKTargets.cmake")
  INCLUDE("${VTK_INSTALL_PREFIX}/lib/vtk-5.8/VTKTargets.cmake")
ENDIF()

# The old, less clear name for VTK_RUNTIME_LIBRARY_DIRS.  Kept here
# for compatibility.
SET(VTK_RUNTIME_DIRS ${VTK_RUNTIME_LIBRARY_DIRS})

# The name of the encoders used by VTK
SET( VTK_USE_FFMPEG_ENCODER "ON" )
SET( VTK_USE_OGGTHEORA_ENCODER "OFF")


