# - Find TIFF library
# Find the native TIFF includes and library
# This module defines
#  TIFF_INCLUDE_DIR, where to find tiff.h, etc.
#  TIFF_LIBRARIES, libraries to link against to use TIFF.
#  TIFF_FOUND, If false, do not try to use TIFF.
# also defined, but not for general use are
#  TIFF_LIBRARY, where to find the TIFF library.

#=============================================================================
# Copyright 2002-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

SET(TIFF_LIBRARY_NAMES "")
FIND_PATH(TIFF_INCLUDE_DIR tiff.h)

SET(TIFF_NAMES ${TIFF_NAMES} tiff libtiff tiff3 libtiff3)
FIND_LIBRARY(TIFF_LIBRARY NAMES ${TIFF_NAMES} )
GET_FILENAME_COMPONENT(TIFF_LIBRARY_DIR ${TIFF_LIBRARY} PATH)# CACHE FILEPATH "Directory to TIFF library")
#GET_FILENAME_COMPONENT(TIFF_LIBRARY_NAME ${TIFF_LIBRARY} NAME)
SET( TIFF_LIBRARY_NAME tiff )

# handle the QUIETLY and REQUIRED arguments and set TIFF_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TIFF  DEFAULT_MSG  TIFF_LIBRARY  TIFF_INCLUDE_DIR)

SET(TIFF_FOUND FALSE)
IF(TIFF_LIBRARY AND TIFF_INCLUDE_DIR)
    SET(TIFF_FOUND TRUE)
ENDIF(TIFF_LIBRARY AND TIFF_INCLUDE_DIR)

IF(TIFF_FOUND)
  SET( TIFF_LIBRARIES ${TIFF_LIBRARY} )
  SET( TIFF_LIBRARY_DIRS ${TIFF_LIBRARY_DIR} )
  # Add include directories needed to use TIFF.
  INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})
  # Add link directories needed to use TIFF.
  LINK_DIRECTORIES(${TIFF_LIBRARY_DIRS})
ENDIF(TIFF_FOUND)

MARK_AS_ADVANCED(TIFF_INCLUDE_DIR TIFF_LIBRARY TIFF_LIBRARY_DIR)