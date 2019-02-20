cmake_minimum_required (VERSION 3.0.2)

project (FastRTPSTransport
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

add_definitions(${ORB_C_FLAGS_LIST})

if(WIN32)
	add_definitions(-DNOGDI)
	add_definitions(-DTRANSPORT_PLUGIN)
endif()


set(target FastRTPSTransport)

set(srcs FastRTPSTransport.cpp FastRTPSTransport.h FastRTPSInPort.cpp FastRTPSInPort.h FastRTPSOutPort.cpp FastRTPSOutPort.h FastRTPSManager.cpp FastRTPSManager.h FastRTPSMessageInfo.cpp FastRTPSMessageInfo.h CORBACdrData.cpp CORBACdrData.h CORBACdrDataPubSubTypes.cpp CORBACdrDataPubSubTypes.h)


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${srcs})
	target_link_libraries(${target} ${libs} fastcdr fastrtps)
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)


	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION} fastcdr fastrtps)
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
endif()


install(FILES FastRTPSMessageInfo.h DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)



if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)

