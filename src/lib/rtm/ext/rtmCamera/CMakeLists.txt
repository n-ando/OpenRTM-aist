cmake_minimum_required (VERSION 3.0.2)

if(WIN32)
	set(target rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER})
else(WIN32)
	set(target rtmCamera)
endif(WIN32)

project (${target}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)







macro(idl_compile idl_name)

	set(ALL_IDL_FILES ${ALL_IDL_FILES} ../${idl_name}.idl)
	add_custom_command(
		OUTPUT ${idl_name}Skel.cpp
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR}/.. -I${PROJECT_SOURCE_DIR}/../../idl ${PROJECT_SOURCE_DIR}/../${idl_name}.idl
		COMMAND python -B ${SKELWRAPPER_COMMAND} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)
	

	add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp)
	set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Skel.cpp)
	set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Skel.h)

	set(ALL_IDL_HEADERS ${ALL_IDL_HEADERS} ${PROJECT_BINARY_DIR}/${idl_name}Skel.h)
	set(ALL_IDL_HEADERS ${ALL_IDL_HEADERS} ${PROJECT_BINARY_DIR}/${idl_name}Stub.h)

	if(NOT TARGET ALL_IDL_TGT)
		add_custom_target(ALL_IDL_TGT)
	endif(NOT TARGET ALL_IDL_TGT)
	add_dependencies(ALL_IDL_TGT ${idl_name}_TGT)
endmacro()



set(idls
	CameraCommonInterface
	)




foreach(idl ${idls})
	idl_compile(${idl})
endforeach(idl)



link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${PROJECT_BINARY_DIR}
		)
add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})

set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)






if(VXWORKS)
	add_library(${target} SHARED ${ALL_IDL_SRCS})
	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_BIN_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)
else(VXWORKS)
	if(WIN32)
		add_library(${target}_objlib OBJECT ${ALL_IDL_SRCS} rtmCameraFactory.cpp)
	else(WIN32)
		add_library(${target}_objlib OBJECT ${ALL_IDL_SRCS})
	endif(WIN32)
	set_property(TARGET ${target}_objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
	add_dependencies(${target}_objlib ${RTCSKEL_PROJECT_NAME})

	add_library(${target}-static STATIC $<TARGET_OBJECTS:${target}_objlib>)
	add_dependencies(${target}-static ${RTCSKEL_PROJECT_NAME})
	add_dependencies(${target}-static ${target}_objlib)

	if(WIN32)
		set(DEF_FILE_NAME  ${target}.def)

		set_source_files_properties(${ALL_IDL_SRCS_RTM} PROPERTIES GENERATED 1)
		add_custom_command(TARGET ${target}-static 
			POST_BUILD
			COMMAND python -B ${MAKE_DEF_COMMAND} $<TARGET_FILE:${target}-static> ${target} ${RTM_SHORT_VERSION} ${DEF_FILE_NAME}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		)

		add_dependencies(${target}_objlib ${RTM_PROJECT_NAME})
	endif(WIN32)


	add_library(${target} SHARED $<TARGET_OBJECTS:${target}_objlib> ${CMAKE_CURRENT_BINARY_DIR}/${DEF_FILE_NAME})
	set_target_properties(${target} PROPERTIES DEBUG_POSTFIX d)
	if(WIN32)
		target_link_libraries(${target} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTM_LINKER_OPTION} ${RTM_PROJECT_NAME})
	else(WIN32)
		target_link_libraries(${target} ${ORB_LIBRARIES})
	endif(WIN32)
	add_dependencies(${target} ${target}_objlib)


	if(UNIX)
		install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)

		set_target_properties(${target}-static PROPERTIES DEBUG_POSTFIX d)
		set_target_properties(${target}-static PROPERTIES OUTPUT_NAME ${target} CLEAN_DIRECT_OUTPUT 1)
		install(TARGETS ${target}-static LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)
	elseif(WIN32)
		set_source_files_properties(${DEF_FILE_NAME} PROPERTIES GENERATED 1)
		add_dependencies(${target} ${target}-static)
		install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_LIB_DIR}
						COMPONENT ext)

		install(TARGETS ${target}-static LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_LIB_DIR}
						COMPONENT ext)
	endif()
endif(VXWORKS)





if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)

endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${target} ALL_IDL_TGT)
add_dependencies(${target} ${RTCSKEL_PROJECT_NAME})


install(FILES ${ALL_IDL_FILES} ${ALL_IDL_HEADERS} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)

foreach(idl ${idls})
	if(CORBA STREQUAL "ORBexpress")
		set(SKEL_STUB_HEADER_FILES ${SKEL_STUB_HEADER_FILES} ${PROJECT_BINARY_DIR}/${idl}.h ${PROJECT_BINARY_DIR}/${idl}_c.h)
		set(SKEL_STUB_SOURCE_FILES ${SKEL_STUB_SOURCE_FILES} ${PROJECT_BINARY_DIR}/${idl}.cc ${PROJECT_BINARY_DIR}/${idl}_c.cc)
	elseif(CORBA STREQUAL "omniORB")
		set(SKEL_STUB_HEADER_FILES ${SKEL_STUB_HEADER_FILES} ${PROJECT_BINARY_DIR}/${idl}.hh)
		set(SKEL_STUB_SOURCE_FILES ${SKEL_STUB_SOURCE_FILES} ${PROJECT_BINARY_DIR}/${idl}SK.cc ${PROJECT_BINARY_DIR}/${idl}DynSK.cc)
	elseif(CORBA STREQUAL "TAO")
		set(SKEL_STUB_HEADER_FILES ${SKEL_STUB_HEADER_FILES} ${PROJECT_BINARY_DIR}/${idl}S.h ${PROJECT_BINARY_DIR}/${idl}C.h ${PROJECT_BINARY_DIR}/${idl}C.inl)
		set(SKEL_STUB_SOURCE_FILES ${SKEL_STUB_SOURCE_FILES} ${PROJECT_BINARY_DIR}/${idl}S.cpp ${PROJECT_BINARY_DIR}/${idl}C.cpp)
	endif()
endforeach(idl)

install(FILES ${SKEL_STUB_HEADER_FILES} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)

