cmake_minimum_required (VERSION 2.6)



set(INSTALL_INCLUDE_DIR include)
set(INSTALL_RTM_IDL_DIR ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl)
set(INSTALL_DATA_DIR openrtm-${RTM_MAJOR_VERSION}.${RTM_MINOR_VERSION})
set(INSTALL_RTM_IDL_DIR ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl)
set(INSTALL_RTC_DIR ${INSTALL_RTM_EXT_DIR}/rtc)
set(INSTALL_EC_DIR ${INSTALL_RTM_EXT_DIR}/ec)
set(INSTALL_RTM_DIR ${INSTALL_RTM_EXT_DIR}/rtm)
set(INSTALL_SVC_DIR ${INSTALL_RTM_EXT_DIR}/rtm)
set(PACKAGE OpenRTM-aist)
set(RTM_DESCRIPTION An OMG RTC compliant middleware for robots.)
set(RTM_LIBS ${RTM_PROJECT_NAME} ${COIL_PROJECT_NAME})

set(LIBS -lpthread ${RTM_LINKER_OPTION})
foreach(library ${ORB_LIBRARIES})
	set(LIBS ${LIBS} -l${library})
endforeach()
set(LIBS ${LIBS} -l${RTM_PROJECT_NAME} -l${COIL_PROJECT_NAME} -lrtmCamera -lrtmManipulator)



configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rtm-config.in ${PROJECT_BINARY_DIR}/rtm-config @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/rtm-config DESTINATION ${INSTALL_RTM_BIN_DIR})


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/openrtm-aist_cmake.pc.in ${PROJECT_BINARY_DIR}/openrtm-aist.pc @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/openrtm-aist.pc DESTINATION ${INSTALL_RTM_LIB_DIR}/pkgconfig)
