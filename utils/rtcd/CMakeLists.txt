cmake_minimum_required (VERSION 2.6)
project (rtcd)


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})

if(VXWORKS)
	add_executable(rtcd rtcd_vxorks.cpp)
else(VXWORKS)
	add_executable(rtcd rtcd.cpp)
endif(VXWORKS)


add_dependencies(rtcd rtm)


target_link_libraries(rtcd rtm ${ORB_LIBRARIES} coil RTCSkel)
