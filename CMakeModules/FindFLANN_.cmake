###############################################################################
# Find Flann
#
# This sets the following variables:
# FLANN_FOUND - True if FLANN was found.
# FLANN_INCLUDE_DIRS - Directories containing the FLANN include files.
# FLANN_LIBRARIES - Libraries needed to use FLANN.
# FLANN_DEFINITIONS - Compiler flags for FLANN.

#find_package(PkgConfig)
#pkg_check_modules(PC_FLANN flann)
#set(FLANN_DEFINITIONS ${PC_FLANN_CFLAGS_OTHER})
#
#find_path(FLANN_INCLUDE_DIR flann/flann.hpp
#    HINTS ${PC_FLANN_INCLUDEDIR} ${PC_FLANN_INCLUDE_DIRS})
#
#find_library(FLANN_LIBRARY flann
#    HINTS ${PC_FLANN_LIBDIR} ${PC_FLANN_LIBRARY_DIRS})
#
#set(FLANN_INCLUDE_DIRS ${FLANN_INCLUDE_DIR})
#set(FLANN_LIBRARIES ${FLANN_LIBRARY})
#
#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Flann DEFAULT_MSG
#    FLANN_LIBRARY FLANN_INCLUDE_DIR)
#
#mark_as_advanced(FLANN_LIBRARY FLANN_INCLUDE_DIR)
find_package(PkgConfig)

if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_FLANN flann)
endif(PKG_CONFIG_FOUND)

find_path(FLANN_INCLUDE_DIRS flann/flann.hpp flann/flann.h
  HINTS ${PC_FLANN_INCLUDEDIR} ${PC_FLANN_INCLUDE_DIRS} "${FLANN_ROOT}" "$ENV{FLANN_ROOT}" /usr/local/ /usr/
  PATH_SUFFIXES include)

#find_path(FLANN_INCLUDE_DIRS flann/flann.hpp
#  HINTS ${PC_FLANN_INCLUDEDIR} ${PC_FLANN_INCLUDE_DIRS} "${FLANN_ROOT}" "$ENV{FLANN_ROOT}" /usr/local/ /usr/
#  PATH_SUFFIXES include)

find_library(FLANN_LIBRARY
  NAMES flann
  HINTS ${PC_FLANN_LIBDIR} ${PC_FLANN_LIBRARY_DIRS} "${FLANN_ROOT}" "$ENV{FLANN_ROOT}" /usr/local/ /usr/
  PATH_SUFFIXES lib)

find_library(FLANN_LIBRARY_DEBUG
  NAMES flannd
  HINTS ${PC_FLANN_LIBDIR} ${PC_FLANN_LIBRARY_DIRS} "${FLANN_ROOT}" "$ENV{FLANN_ROOT}"
  PATH_SUFFIXES lib)
if(NOT FLANN_LIBRARY_DEBUG)
  set(FLANN_LIBRARY_DEBUG ${FLANN_LIBRARY})
endif(NOT FLANN_LIBRARY_DEBUG)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Flann DEFAULT_MSG FLANN_LIBRARY FLANN_INCLUDE_DIRS)
if(FLANN_FOUND)
  get_filename_component(FLANN_LIBRARY_PATH ${FLANN_LIBRARY} PATH)
  get_filename_component(FLANN_LIBRARY_DEBUG_PATH ${FLANN_LIBRARY_DEBUG} PATH)
  set(FLANN_LIBRARY_DIRS ${FLANN_LIBRARY_PATH} ${FLANN_LIBRARY_DEBUG_PATH})
  set(FLANN_LIBRARIES optimized ${FLANN_LIBRARY} debug ${FLANN_LIBRARY_DEBUG})

  mark_as_advanced(FLANN_LIBRARY FLANN_INCLUDE_DIRS)
endif(FLANN_FOUND)

