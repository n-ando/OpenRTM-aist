cmake_minimum_required (VERSION 2.6)


project (${RTCSKEL_PROJECT_NAME})







macro(idl_compile idl_name)

	set(ALL_IDL_FILES ${ALL_IDL_FILES} ${idl_name}.idl)
	add_custom_command(
		OUTPUT ${idl_name}Skel.cpp
		#COMMAND mkdir -p include/rtm/idl
		#COMMAND cd include/rtm/idl
		#COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/${idl_name}.idl
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/${idl_name}.idl
		COMMAND python ${SKELWRAPPER_COMMAND} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		#WORKING_DIRECTORY ${CURRENT_BINARY_DIR}/include/rtm/idl
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)
	

	add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} idl/${idl_name}Skel.cpp)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} idl/${idl_name}SKel.h)
	set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Skel.cpp)
	set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Skel.h)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Stub.cpp)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}Stub.h)

	set(ALL_IDL_HEADERS ${ALL_IDL_HEADERS} ${PROJECT_BINARY_DIR}/${idl_name}Skel.h)
	set(ALL_IDL_HEADERS ${ALL_IDL_HEADERS} ${PROJECT_BINARY_DIR}/${idl_name}Stub.h)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}_c.cc)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}_c.h)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}.cc)
	#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${idl_name}.h)

	if(NOT TARGET ALL_IDL_TGT)
		add_custom_target(ALL_IDL_TGT)
	endif(NOT TARGET ALL_IDL_TGT)
	add_dependencies(ALL_IDL_TGT ${idl_name}_TGT)
	#include_directories(${PROJECT_BINARY_DIR}/idl)
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


if(OBSERVER_ENABLE)
configure_file(${CMAKE_SOURCE_DIR}/src/ext/sdo/observer/ComponentObserver.idl ${CMAKE_CURRENT_SOURCE_DIR}/ComponentObserver.idl COPYONLY)
set(idls ${idls} ComponentObserver)
endif(OBSERVER_ENABLE)


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
ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})





#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} PARENT_SCOPE)






set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
add_library(${RTCSKEL_PROJECT_NAME} STATIC ${ALL_IDL_SRCS} )

if(NOT TARGET ALL_IDL_TGT)
	add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)

add_dependencies(${RTCSKEL_PROJECT_NAME} ALL_IDL_TGT)


install(FILES ${ALL_IDL_FILES} ${ALL_IDL_HEADERS} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl)
 


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


install(FILES ${SKEL_STUB_HEADER_FILES} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl)



if(WIN32)
	set(SKEL_IDL_SRCS ${SKEL_STUB_SOURCE_FILES} PARENT_SCOPE)
	#set(SKEL_IDL_DIR ${PROJECT_BINARY_DIR} PARENT_SCOPE)
else(WIN32)
endif(WIN32)