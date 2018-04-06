cmake_minimum_required (VERSION 2.6)


set(target rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER})

project (${target})







macro(idl_compile idl_name)

	set(ALL_IDL_FILES ${ALL_IDL_FILES} ../${idl_name}.idl)
	add_custom_command(
		OUTPUT ${idl_name}Skel.cpp
		#COMMAND mkdir -p include/rtm/idl
		#COMMAND cd include/rtm/idl
		#COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/ext/${idl_name}.idl
		COMMAND ${IDL_COMPILE_COMMAND} ${IDLCOMMAND_FLAGS} -I${PROJECT_SOURCE_DIR}/.. -I${PROJECT_SOURCE_DIR}/../../idl ${PROJECT_SOURCE_DIR}/../${idl_name}.idl
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
	CameraCommonInterface
	)




foreach(idl ${idls})
	idl_compile(${idl})
endforeach(idl)



link_directories(${ORB_LINK_DIR})
include_directories(
		${ORB_INCLUDE_DIR}
		${PROJECT_BINARY_DIR}
		)
add_definitions(${ORB_C_FLAGS_LIST})




link_directories(${ORB_LINK_DIR})
include_directories(${ORB_INCLUDE_DIR})
ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})



#set(ALL_IDL_SRCS ${ALL_IDL_SRCS} PARENT_SCOPE)

set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)





if(VXWORKS)
	add_library(${target} SHARED ${ALL_IDL_SRCS})
	install(TARGETS ${RTM_PROJECT_NAME} ARCHIVE DESTINATION lib)
else(VXWORKS)
	add_library(${target} SHARED ${ALL_IDL_SRCS})
	set_target_properties(${target} PROPERTIES DEBUG_POSTFIX d)
	target_link_libraries(${target} ${ORB_LIBRARIES} ${RTCSKEL_PROJECT_NAME})
	if(UNIX)
		install(TARGETS ${target} LIBRARY DESTINATION lib)
	elseif(WIN32)
		install(TARGETS ${target} RUNTIME DESTINATION bin)
	endif()
endif(VXWORKS)





if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)

endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${target} ALL_IDL_TGT)
add_dependencies(${target} ${RTCSKEL_PROJECT_NAME})


install(FILES ${ALL_IDL_FILES} ${ALL_IDL_HEADERS} DESTINATION include/rtm/idl)
 


