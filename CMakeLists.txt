cmake_minimum_required(VERSION 3.14.5)
project(corner_detector)

find_package( OpenCV 4.10 REQUIRED )
find_package( Boost 1.70 REQUIRED COMPONENTS unit_test_framework )
find_pacakge( Eigen3 3.3 REQUIRED )

include_directories(
  .
  $ENV{HOME}/cots/eigen/eigen-eigen-323c052e1731
  ${OpenCV_INCLUDE_DIRS}   
  ${Boost_INCLUDE_DIRS}
)

add_library(corner_detector corner_detector.cpp)
target_include_directories(corner_detector PRIVATE 
target_link_libraries(corner_detector ${OpenCV_LIBS})

add_executable(test1 test/check_eigenvalues.cpp)
target_link_libraries(test1 corner_detector ${OpenCV_LIBS} ${Boost_LIBRARIES})
