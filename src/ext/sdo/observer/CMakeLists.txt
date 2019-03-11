cmake_minimum_required (VERSION 3.0.2)

project (ComponentObserverConsumer
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(target ComponentObserverConsumer)

set(idl_name ComponentObserver)



set(${idl_name}_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(${idl_name}_SKEL ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Skel.h)
set(${idl_name}_STUB ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.cpp ${CMAKE_CURRENT_BINARY_DIR}/${idl_name}Stub.h)


add_custom_command(
		OUTPUT ${idl_name}Skel.cpp ${idl_name}Stub.cpp
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR} -I${CMAKE_SOURCE_DIR}/src/lib/rtm/idl ${CMAKE_CURRENT_SOURCE_DIR}/${idl_name}.idl
		COMMAND python -B ${SKELWRAPPER_COMMAND} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp ${idl_name}Stub.cpp)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${idl_name}.idl DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo/observer COMPONENT idl)


include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${PROJECT_BINARY_DIR}
		)

add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})


set(srcs ${${idl_name}_STUB} ${target}.cpp ${target}.h)

set_source_files_properties(${${idl_name}_STUB} PROPERTIES GENERATED 1)


add_library(${target} STATIC ${srcs})


install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			COMPONENT ext)

add_dependencies(${target} ${idl_name}_TGT)
add_dependencies(${target} ALL_IDL_TGT)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/ComponentObserverStub.cpp PROPERTIES GENERATED 1)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/ComponentObserverStub.h PROPERTIES GENERATED 1)
