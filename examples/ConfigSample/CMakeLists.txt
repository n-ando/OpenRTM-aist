cmake_minimum_required (VERSION 2.6)
project (ConfigSample)


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})




set(srcs ConfigSampleComp.cpp ConfigSample.cpp ConfigSample.h)

if(VXWORKS)
	if(RTP)
		set(libs rtm ${ORB_LIBRARIES} coil RTCSkel)
	else(RTP)
		set(srcs ${srcs} ${CMAKE_SOURCE_DIR}/rtm/DataFlowComponentBase.cpp)
		set(libs RTCSkel)	
	endif(RTP)
endif(VXWORKS)

add_executable(ConfigSample ${srcs})
target_link_libraries(ConfigSample ${libs})
add_dependencies(ConfigSample rtm)
