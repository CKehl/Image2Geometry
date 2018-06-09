set(PROGRAM Image2Geometry)

set(KERNEL_O "")

set(SHADERS shaderGamma.vert shaderGamma.frag)

set(HFILES
	./AccurateMatcher.h
	./BoundRenderScene.h
	./DATtoOCV.h
	./DCSiftDescriptorExtractor.h
	./DiscriminativeColorDescriptor.h
	./std_typedefs.h
	./GeometryIntersector.h
	./HueDescriptor.h
	./ImageFileDescriptor.h
	./ImagingPrimitives.h
	./main.h
	./OCVtoDAT.h
	./OneWayRobustMatcher.h
	./opencv_includes.h
    ./OpenCVOSGGlue.h
    ./ReaderEXIF.h
	./RobustMatcher.h
	./Rotations.h
	./screenview.h
	./SensorReader.h
	./SyntheticScene.h
	./WriterCVMatch.h
	./WriterPT2.h
	./WriterPTS.h
	${ADDITIONAL_HEADERS}
)

set(SOURCES
	./AccurateMatcher.cpp 
	./BoundRenderScene.cpp 
	./DATtoOCV.cpp 
	./DCSiftDescriptorExtractor.cpp 
	./DiscriminativeColorDescriptor.cpp 
	./GeometryIntersector.cpp 
	./HueDescriptor.cpp 
	./ImageFileDescriptor.cpp 
	./ImagingPrimitives.cpp 
	./main_multiImages.cpp 
	./OCVtoDAT.cpp 
	./OneWayRobustMatcher.cpp 
    ./OpenCVOSGGlue.cpp 
    ./ReaderEXIF.cpp 
	./RobustMatcher.cpp 
	./Rotations.cpp 
	./screenview.cpp 
	./SensorReader.cpp 
	./SyntheticScene.cpp 
	./WriterCVMatch.cpp 
	./WriterPT2.cpp 
	./WriterPTS.cpp 
	${ADDITIONAL_SOURCES}
)


include_directories(${INCLUDE_DIRS} ${CMAKE_INCLUDE_PATH})
link_directories(${Image2Geometry_SOURCE_DIR} ${ADDITIONAL_LIBRARY_PATHS} ${CMAKE_BINARY_DIR})

if(CUDA_FOUND)
  if(CUDA_USE_CUDA_BUILD MATCHES ON)
    message("CUDA FOUND")
    list(APPEND SOURCES ${CUDA_SOURCES})
    #CUDA_ADD_LIBRARY(${LIB_NAME} ${SOURCES})
    CUDA_ADD_EXECUTABLE(${PROGRAM} ${SOURCES})
  else(CUDA_USE_CUDA_BUILD MATCHES ON)
    #add_library(${LIB_NAME} ${SOURCES})
    add_executable(${PROGRAM} ${SOURCES})
  endif(CUDA_USE_CUDA_BUILD MATCHES ON)
else(CUDA_FOUND)
  #add_library(${LIB_NAME} ${SOURCES})
  add_executable(${PROGRAM} ${SOURCES})
endif(CUDA_FOUND)

#target_link_libraries(${LIB_NAME} ${LIBRARIES})
target_link_libraries(${PROGRAM} ${LIBRARIES})

#install(FILES ${HFILES} DESTINATION include/<LIBRARY NAME>)
install(TARGETS ${PROGRAM} RUNTIME DESTINATION bin)
install(FILES ${KERNEL_O} DESTINATION lib)
install(FILES ${SHADERS} DESTINATION bin)
install(DIRECTORY ../w2c DESTINATION bin)
#install(TARGETS ${LIB_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)