cmake_minimum_required (VERSION 2.6)




#set(OPENRTM_CFLAGS ${ORB_C_FLAGS_LIST})
#set(OPENRTM_LIBRARIES optimized;RTC${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;coil${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;advapi32;optimized;ws2_32;optimized;mswsock;optimized;rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;rtmManipulator${RTM_SHORT_VERSION}_${RTM_VC_VER};debug;RTC${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;coil${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;advapi32;debug;ws2_32;debug;mswsock;debug;rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;rtmManipulator${RTM_SHORT_VERSION}_${RTM_VC_VER}d;${ORB_LIBRARIES})

if(CORBA STREQUAL "ORBexpress")
elseif(CORBA STREQUAL "omniORB")
	set(OMNIORB_VERSION "${OMNI_VERSION1}.${OMNI_VERSION2}.${OMNI_MINOR}")
elseif(CORBA STREQUAL "TAO")
endif()

set(OPENRTM_LIBRARIES "optimized;${RTM_PROJECT_NAME};debug;${RTM_PROJECT_NAME}d;optimized;${COIL_PROJECT_NAME};debug;${COIL_PROJECT_NAME}d;${RTM_LINKER_OPTION}")




if(VXWORKS)
elseif(UNIX)
elseif(MSVC)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig.cmake.in ${PROJECT_BINARY_DIR}/OpenRTMConfig.cmake @ONLY)
	install(FILES  ${PROJECT_BINARY_DIR}/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_CMAKE_DIR})
	if(CORBA STREQUAL "ORBexpress")
	elseif(CORBA STREQUAL "omniORB")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_omniORB.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
	elseif(CORBA STREQUAL "TAO")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMConfig_TAO.cmake.in ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake @ONLY)
	endif()
	install(FILES  ${PROJECT_BINARY_DIR}/cmake/OpenRTMConfig.cmake DESTINATION ${INSTALL_RTM_BIN_DIR})
#	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMFind_win.cmake.in ${PROJECT_BINARY_DIR}/OpenRTMFind.cmake @ONLY)
endif()


