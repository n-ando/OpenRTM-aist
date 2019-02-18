cmake_minimum_required (VERSION 2.6)


set(ROS_ENABLE ${ROS_ENABLE} CACHE BOOL "set ROS_ENABLE")

if(ROS_ENABLE)
	add_subdirectory(ROSTransport)
endif(ROS_ENABLE)