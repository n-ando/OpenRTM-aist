cmake_minimum_required (VERSION 2.6)
set(target rtcd)
project (${target})


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})

if(VXWORKS)
	add_executable(${target} rtcd_vxorks.cpp)
#	add_executable(${target} rtcd_vxorks.cpp ConsoleIn.cpp ConsoleIn.h)
#	add_executable(${target} hello_s.cxx hello_s.h server.cpp hello.cxx hello.h)
else(VXWORKS)
	add_executable(${target} rtcd.cpp)
endif(VXWORKS)


add_dependencies(${target} ${RTM_PROJECT_NAME})


if(VXWORKS)
	set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
else(VXWORKS)
	set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
endif(VXWORKS)

target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})

#target_link_libraries(${target} ${ORB_LIBRARIES})



if(VXWORKS)
	if(RTP)
		set_target_properties(${target} PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)


install(TARGETS ${target} RUNTIME DESTINATION bin)
