cmake_minimum_required(VERSION 3.14.5)
project(cornerDetector)

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakemodules )

find_package( OpenCV 4.1.0 REQUIRED )
find_package( Boost 1.70 REQUIRED COMPONENTS unit_test_framework )
find_package( Eigen3 3.3 REQUIRED )

add_library(cornerDetector cornerDetector.cpp)
target_include_directories(cornerDetector PRIVATE
  .
  ${EIGEN3_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
)  
target_link_libraries(cornerDetector
	${OpenCV_LIBS}
)

add_executable(test1 test/checkEigenvalues.cpp)
target_include_directories(test1 PRIVATE
	.
	${OpenCV_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)
target_link_libraries(test1
	cornerDetector
	${OpenCV_LIBS}
	${Boost_LIBRARIES}
)

add_executable(test2 test/checkHarrisResponse.cpp)
target_include_directories(test2 PRIVATE
	.
	${OpenCV_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)
target_link_libraries(test2
	cornerDetector
	${OpenCV_LIBS}
	${Boost_LIBRARIES}
)
