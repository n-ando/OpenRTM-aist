cmake_minimum_required (VERSION 2.6)

project (Composite)


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})


set(target CompositeComp)

set(srcs Composite.cpp)
set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})




add_executable(${target} ${srcs})
target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
add_dependencies(${target} ${RTM_PROJECT_NAME})

install(TARGETS ${target} RUNTIME DESTINATION examples)


if(VXWORKS)
	if(RTP)
		set_target_properties(${target} PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)








set(target Controller)

set(srcs Controller.cpp Controller.h)
set(standalone_srcs ControllerComp.cpp ${srcs})

if(VXWORKS AND NOT RTP)
	set(standalone_srcs ${standalone_srcs} ${CMAKE_SOURCE_DIR}/src/lib/rtm/DataFlowComponentBase.cpp)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${standalone_srcs})
	target_link_libraries(${target} ${libs})
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} RUNTIME DESTINATION examples)
else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)

	add_executable(${target}Comp ${standalone_srcs})
	target_link_libraries(${target}Comp ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target}Comp ${RTM_PROJECT_NAME})

	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")

	install(TARGETS ${target}Comp RUNTIME DESTINATION examples)
	if(WIN32)
		install(TARGETS ${target} RUNTIME DESTINATION examples)
	else(WIN32)
		install(TARGETS ${target} LIBRARY DESTINATION examples)
	endif(WIN32)
endif()


if(VXWORKS)
	if(RTP)
		set_target_properties(${target}Comp PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)



set(target Motor)

set(srcs Motor.cpp Motor.h)
set(standalone_srcs MotorComp.cpp ${srcs})

if(VXWORKS AND NOT RTP)
	set(standalone_srcs ${standalone_srcs} ${CMAKE_SOURCE_DIR}/src/lib/rtm/DataFlowComponentBase.cpp)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${standalone_srcs})
	target_link_libraries(${target} ${libs})
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} RUNTIME DESTINATION examples)
else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)

	add_executable(${target}Comp ${standalone_srcs})
	target_link_libraries(${target}Comp ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target}Comp ${RTM_PROJECT_NAME})

	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")

	install(TARGETS ${target}Comp RUNTIME DESTINATION examples)
	if(WIN32)
		install(TARGETS ${target} RUNTIME DESTINATION examples)
	else(WIN32)
		install(TARGETS ${target} LIBRARY DESTINATION examples)
	endif(WIN32)
endif()


if(VXWORKS)
	if(RTP)
		set_target_properties(${target}Comp PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)



set(target Sensor)

set(srcs Sensor.cpp Sensor.h)
set(standalone_srcs SensorComp.cpp ${srcs})

if(VXWORKS AND NOT RTP)
	set(standalone_srcs ${standalone_srcs} ${CMAKE_SOURCE_DIR}/src/lib/rtm/DataFlowComponentBase.cpp)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${standalone_srcs})
	target_link_libraries(${target} ${libs})
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} RUNTIME DESTINATION examples)
else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)

	add_executable(${target}Comp ${standalone_srcs})
	target_link_libraries(${target}Comp ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target}Comp ${RTM_PROJECT_NAME})

	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")

	install(TARGETS ${target}Comp RUNTIME DESTINATION examples)
	if(WIN32)
		install(TARGETS ${target} RUNTIME DESTINATION examples)
	else(WIN32)
		install(TARGETS ${target} LIBRARY DESTINATION examples)
	endif(WIN32)
endif()


if(VXWORKS)
	if(RTP)
		set_target_properties(${target}Comp PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)
