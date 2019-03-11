cmake_minimum_required (VERSION 3.0.2)


project (${RTCSKEL_PROJECT_NAME}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)







macro(idl_compile idl_name)

	set(ALL_IDL_FILES ${ALL_IDL_FILES} ${idl_name}.idl)
	add_custom_command(
		OUTPUT ${idl_name}Skel.cpp
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/${idl_name}.idl
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
	BasicDataType
	DataPort
	DataPort_OpenRTM
	ExtendedDataTypes
	InterfaceDataTypes
	Manager
	OpenRTM
	RTC
	SDOPackage
	SharedMemory
	ExtendedFsmService
	)


if(CORBA MATCHES "TAO")
	set(idls ${idls} DataPortUDP)
endif()

foreach(idl ${idls})
	idl_compile(${idl})
endforeach(idl)


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)
add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})





#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} PARENT_SCOPE)






set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
add_library(${RTCSKEL_PROJECT_NAME} STATIC ${ALL_IDL_SRCS} )

if(UNIX)
	install(TARGETS ${RTCSKEL_PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
					ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
					RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
					COMPONENT openrtm)
endif(UNIX)

if(NOT TARGET ALL_IDL_TGT)
	add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)

add_dependencies(${RTCSKEL_PROJECT_NAME} ALL_IDL_TGT)


install(FILES ${ALL_IDL_FILES} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl COMPONENT idl)
install(FILES ${ALL_IDL_HEADERS} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl COMPONENT headers)
 


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


install(FILES ${SKEL_STUB_HEADER_FILES} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl COMPONENT headers)



set(SKEL_IDL_SRCS ${SKEL_STUB_SOURCE_FILES} PARENT_SCOPE)


add_subdirectory(device_interfaces)