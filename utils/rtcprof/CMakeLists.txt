cmake_minimum_required (VERSION 2.6)
project (rtcprof)


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})







set(srcs rtcprof.cpp)


if(VXWORKS)
	if(RTP)
		set(libs rtm ${ORB_LIBRARIES} coil RTCSkel)
	else(RTP)
		set(srcs ${srcs} ${CMAKE_SOURCE_DIR}/rtm/DataFlowComponentBase.cpp)
		set(libs RTCSkel)	
	endif(RTP)
endif(VXWORKS)

add_executable(rtcprof ${srcs})
target_link_libraries(rtcprof ${libs})
add_dependencies(rtcprof rtm)

