cmake_minimum_required (VERSION 3.0.2)

file(GLOB IDL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.idl")
foreach(file_path ${IDL_FILES})
	install(FILES ${file_path} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl/device_interfaces COMPONENT ext)
endforeach()


