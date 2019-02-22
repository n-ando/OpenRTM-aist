cmake_minimum_required (VERSION 2.6)


set(ROS_ENABLE ${ROS_ENABLE} CACHE BOOL "set ROS_ENABLE")

if(ROS_ENABLE)
	add_subdirectory(ROSTransport)
endif(ROS_ENABLE)


set(FASTRTPS_ENABLE ${FASTRTPS_ENABLE} CACHE BOOL "set FASTRTPS_ENABLE")
set(ROS2_ENABLE ${ROS2_ENABLE} CACHE BOOL "set ROS2_ENABLE")

if(FASTRTPS_ENABLE)
	add_subdirectory(FastRTPS)
	if(ROS2_ENABLE)
		add_subdirectory(ROS2Transport)
	endif(ROS2_ENABLE)
endif(FASTRTPS_ENABLE)






