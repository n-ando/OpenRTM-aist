cmake_minimum_required (VERSION 3.0.2)

project (FileNameservice
	VERSION ${RTM_VERSION}
	LANGUAGES C CXX)








link_directories(${ORB_LINK_DIR}
		 ${Boost_LIBRARY_DIRS})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${Boost_INCLUDE_DIRS}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})


set(target FileNameservice)

set(srcs FileNameservice.cpp FileNameservice.h)


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${srcs})
	target_link_libraries(${target} ${libs})
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				COMPONENT ext)


else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)


	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/local_service
				COMPONENT ext)
endif()






if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)


