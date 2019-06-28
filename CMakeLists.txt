cmake_minimum_required(VERSION 3.14.5)
project(corner_detector)

find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS unit_test_framework )

include_directories(
  .
  $ENV{HOME}/cots/eigen/eigen-eigen-323c052e1731
  ${OpenCV_INCLUDE_DIRS}   
  ${Boost_INCLUDE_DIRS}
)

add_library(corner_detector corner_detector.cpp)
target_link_libraries(corner_detector ${OpenCV_LIBS})

add_executable(test1 test/check_eigenvalues.cpp)
target_link_libraries(test1 corner_detector ${OpenCV_LIBS} ${Boost_LIBRARIES})
