cmake_minimum_required(VERSION 2.8.3)
project(feature_extraction)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  camera_info_manager
)

find_package(OpenCV REQUIRED)

find_package(Boost REQUIRED COMPONENTS thread)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Dependencies - PCL:
find_package(PCL REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS image_transport cv_bridge roscpp sensor_msgs
  DEPENDS OpenCV
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
add_executable( features src/republish.cpp )
target_link_libraries ( features ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )
