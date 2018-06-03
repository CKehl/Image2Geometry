# - Try to find Lib3DS
# Once done, this will define
#
#  LIB3DS_FOUND - system has Magick++
#  LIB3DS_INCLUDE_DIRS - the Magick++ include directories
#  LIB3DS_LIBRARIES - link these to use Magick++

#include(LibFindMacros)

# Dependencies
# libfind_package(Magick++ Magick)

# Use pkg-config to get hints about paths
#libfind_pkg_check_modules(LIB3DS_PKGCONF LIB3DS)

find_package(PkgConfig)
pkg_check_modules(LIB3DS 3ds)

find_path(LIB3DS_INCLUDE_DIR
  NAMES lib3ds.h
  PATHS /usr/local/include 
	/usr/local/include/lib3ds 
	/usr/include 
	/usr/include/lib3ds
	$ENV{LIB3DS_INCLUDE_DIR} 
	$ENV{LIB3DS_HOME}/include 
  #HINTS ${PC_FLANN_INCLUDEDIR} ${PC_FLANN_INCLUDE_DIRS}
)

find_library(LIB3DS_LIBRARY 
  NAMES 3ds
  PATHS /usr/local/lib 
	/usr/lib
	/usr/lib64
	$ENV{LIB3DS_LIBRARY_PATH}
	$ENV{LIB3DS_HOME}/lib
    #HINTS ${PC_FLANN_LIBDIR} ${PC_FLANN_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
IF(LIB3DS_FOUND)
  set(LIB3DS_INCLUDE_DIRS ${LIB3DS_INCLUDE_DIR})
  set(LIB3DS_LIBRARIES ${LIB3DS_LIBRARY})
ENDIF(LIB3DS_FOUND)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIB3ds DEFAULT_MSG
    LIB3DS_LIBRARY LIB3DS_INCLUDE_DIR)

mark_as_advanced(LIB3DS_LIBRARY LIB3DS_INCLUDE_DIR)

