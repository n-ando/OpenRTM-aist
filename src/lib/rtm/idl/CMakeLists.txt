cmake_minimum_required (VERSION 2.6)


project (RTCSkel)







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
	ExtendedDataTypes
	InterfaceDataTypes
	Manager
	OpenRTM
	RTC
	SDOPackage
	SharedMemory
	ExtendedFsmService
	)


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

add_library(RTCSkel STATIC ${ALL_IDL_SRCS} )

if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)

endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(RTCSkel ALL_IDL_TGT)


install(FILES ${ALL_IDL_FILES} ${ALL_IDL_HEADERS} DESTINATION include/rtm/idl)
 


