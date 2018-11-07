cmake_minimum_required (VERSION 2.6)

file(GLOB IDL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.idl")
foreach(file_path ${IDL_FILES})
	install(FILES ${file_path} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl/device_interfaces)
endforeach()


