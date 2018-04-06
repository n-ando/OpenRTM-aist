cmake_minimum_required (VERSION 2.6)
set(target rtcsh)
project (${target})


link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})

add_executable(${target} rtcsh.cpp)


add_dependencies(${target} ${RTM_PROJECT_NAME})


set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})


target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})


install(TARGETS ${target} RUNTIME DESTINATION bin)
