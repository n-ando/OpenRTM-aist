cmake_minimum_required (VERSION 2.6)
set(target rtcsh)
project (${target})


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})

add_executable(${target} rtcsh.cpp)


add_dependencies(${target} ${RTM_PROJECT_NAME})


set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})


target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})


if(VXWORKS)
	if(RTP)
		set_target_properties(${target} PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)

if(WIN32)
	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
				ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
				RUNTIME DESTINATION ${INSTALL_RTM_LIB_DIR})
else(WIN32)
	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
				ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
				RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR})
endif(WIN32)
