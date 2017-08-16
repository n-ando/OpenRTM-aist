cmake_minimum_required (VERSION 2.6)
set(target rtcprof)
project (${target})


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})







set(srcs rtcprof.cpp)


#if(VXWORKS)
#	if(RTP)
#		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
#	else(RTP)
#		set(srcs ${srcs} ${CMAKE_SOURCE_DIR}/rtm/DataFlowComponentBase.cpp)
#		set(libs ${RTCSKEL_PROJECT_NAME})	
#	endif(RTP)
#endif(VXWORKS)

set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})

add_executable(${target} ${srcs})
target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
add_dependencies(${target} ${RTM_PROJECT_NAME})


if(VXWORKS)
	if(RTP)
		set_target_properties(${target} PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)


install(TARGETS ${target} RUNTIME DESTINATION bin)
