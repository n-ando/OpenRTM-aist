cmake_minimum_required (VERSION 3.0.2)

project (AutoTest
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(idl_name AutoTestService)

set(${idl_name}_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(${idl_name}_SKEL ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.h)
set(${idl_name}_STUB ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.h)


add_custom_command(
		OUTPUT ${idl_name}Skel.cpp ${idl_name}Stub.cpp
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_SOURCE_DIR}/rtm/idl ${CMAKE_CURRENT_SOURCE_DIR}/${idl_name}.idl
		COMMAND python ${SKELWRAPPER_COMMAND} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp ${idl_name}Stub.cpp)

set_source_files_properties(${${idl_name}_STUB} PROPERTIES GENERATED 1)
set_source_files_properties(${${idl_name}_SKEL} PROPERTIES GENERATED 1)

include_directories(${${idl_name}_DIR})

set(srcs AutoTestIn.cpp AutoTestIn.h AutoTestServiceSVC_impl.cpp AutoTestServiceSVC_impl.h ${${idl_name}_SKEL})
ComponentBuild(AutoTestIn "${srcs}" AutoTestInComp.cpp ${idl_name}_TGT "")


set(srcs AutoTestOut.cpp AutoTestOut.h ${${idl_name}_STUB})
ComponentBuild(AutoTestOut "${srcs}" AutoTestOutComp.cpp ${idl_name}_TGT "")
