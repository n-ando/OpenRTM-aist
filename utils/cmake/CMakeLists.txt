cmake_minimum_required (VERSION 3.0.2)




if(CORBA STREQUAL "ORBexpress")
elseif(CORBA STREQUAL "omniORB")
	set(OMNIORB_VERSION "${OMNI_VERSION1}.${OMNI_VERSION2}.${OMNI_MINOR}")
elseif(CORBA STREQUAL "TAO")
endif()




if(WIN32)
	set(rtmCamera rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER})
	set(rtmManipulator rtmManipulator${RTM_SHORT_VERSION}_${RTM_VC_VER})
	set(OPENRTM_LIBRARIES "optimized;${RTM_PROJECT_NAME};debug;${RTM_PROJECT_NAME}d;optimized;${COIL_PROJECT_NAME};debug;${COIL_PROJECT_NAME}d;${RTM_LINKER_OPTION};optimized;${rtmCamera};debug;${rtmCamera}d;optimized;${rtmManipulator};debug;${rtmManipulator}d")
	foreach(data_type ${DATATYPE_FACTORIES})
		set(OPENRTM_LIBRARIES ${OPENRTM_LIBRARIES};optimized;${data_type};debug;${data_type}d)
	endforeach()
else(WIN32)
	set(OPENRTM_LIBRARIES "${RTM_PROJECT_NAME};${COIL_PROJECT_NAME};${ORB_LIBRARIES};rtmCamera;rtmManipulator")
endif(WIN32)




if(VXWORKS)
elseif(UNIX)
	if(CORBA STREQUAL "ORBexpress")
	elseif(CORBA STREQUAL "omniORB")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_omniORB_Linux.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
		install(FILES ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_CMAKE_DIR} COMPONENT cmakefiles)
	elseif(CORBA STREQUAL "TAO")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_TAO_Linux.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
		install(FILES ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_CMAKE_DIR} COMPONENT cmakefiles)
	endif()
	
elseif(MSVC)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig.cmake.in ${PROJECT_BINARY_DIR}/OpenRTMConfig.cmake @ONLY)
	install(FILES  ${PROJECT_BINARY_DIR}/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_CMAKE_DIR} COMPONENT cmakefiles)
	if(CORBA STREQUAL "ORBexpress")
	elseif(CORBA STREQUAL "omniORB")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_omniORB.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
		install(FILES  ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_BIN_DIR} COMPONENT cmakefiles)
	elseif(CORBA STREQUAL "TAO")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_TAO.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
		install(FILES  ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_BIN_DIR} COMPONENT cmakefiles)
	endif()
endif()

