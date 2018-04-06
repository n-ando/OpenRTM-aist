cmake_minimum_required (VERSION 2.6)




set(OPENRTM_CFLAGS ${ORB_C_FLAGS_LIST})
set(OPENRTM_LIBRARIES optimized;RTC${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;coil${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;advapi32;optimized;ws2_32;optimized;mswsock;optimized;rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER};optimized;rtmManipulator${RTM_SHORT_VERSION}_${RTM_VC_VER};debug;RTC${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;coil${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;advapi32;debug;ws2_32;debug;mswsock;debug;rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER}d;debug;rtmManipulator${RTM_SHORT_VERSION}_${RTM_VC_VER}d;${ORB_LIBRARIES})

if(VXWORKS)
elseif(UNIX)
elseif(MSVC)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/OpenRTMFind_win.cmake.in ${PROJECT_BINARY_DIR}/OpenRTMFind.cmake @ONLY)
endif(VXWORKS)