cmake_minimum_required (VERSION 3.0.2)

project (LogicalTimeTriggeredEC
	VERSION ${RTM_VERSION}
	LANGUAGES C CXX)



set(idl_name LogicalTimeTriggeredEC)





set(${idl_name}_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(${idl_name}_SKEL ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.h)
set(${idl_name}_STUB ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.h)


add_custom_command(
		OUTPUT ${idl_name}Skel.cpp ${idl_name}Stub.cpp
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_SOURCE_DIR}/src/lib/rtm/idl ${CMAKE_CURRENT_SOURCE_DIR}/${idl_name}.idl
		COMMAND python ${SKELWRAPPER_COMMAND} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp ${idl_name}Stub.cpp)




link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${${idl_name}_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})


set(target LogicalTimeTriggeredEC)

set(srcs LogicalTimeTriggeredEC.cpp LogicalTimeTriggeredEC.h ${${idl_name}_SKEL})


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${srcs})
	target_link_libraries(${target} ${libs})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	add_dependencies(${target} ${idl_name}_TGT)

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
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
	add_dependencies(${target} ${idl_name}_TGT)
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/ec
				COMPONENT ext)
endif()


set_source_files_properties(${${idl_name}_SKEL} PROPERTIES GENERATED 1)




if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)



