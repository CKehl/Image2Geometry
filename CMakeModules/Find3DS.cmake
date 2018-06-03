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
pkg_check_modules(3DS 3ds)

find_path(3DS_INCLUDE_DIR
  NAMES lib3ds.h
  PATHS /usr/local/include 
	/usr/local/include/lib3ds 
	/usr/include 
	/usr/include/lib3ds
	$ENV{LIB3DS_INCLUDE_DIR} 
	$ENV{LIB3DS_HOME}/include 
  #HINTS ${PC_FLANN_INCLUDEDIR} ${PC_FLANN_INCLUDE_DIRS}
)

find_library(3DS_LIBRARY 
  NAMES 3ds
  PATHS /usr/local/lib 
	/usr/lib
	/usr/lib64
	$ENV{LIB3DS_LIBRARY_PATH}
	$ENV{LIB3DS_HOME}/lib
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
IF(3DS_FOUND)
  set(LIB3DS_INCLUDE_DIRS ${3DS_INCLUDE_DIR})
  set(LIB3DS_LIBRARIES ${3DS_LIBRARY})
  set(LIB3DS_INCLUDE_DIR ${3DS_INCLUDE_DIR})
  set(LIB3DS_LIBRARY ${3DS_LIBRARY})
ENDIF(3DS_FOUND)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIB3ds DEFAULT_MSG
    3DS_LIBRARY 3DS_INCLUDE_DIR)

mark_as_advanced(3DS_LIBRARY 3DS_INCLUDE_DIR)

