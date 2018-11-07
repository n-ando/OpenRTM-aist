cmake_minimum_required (VERSION 2.6)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/coil-config.in ${PROJECT_BINARY_DIR}/coil-config @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/coil-config DESTINATION ${INSTALL_RTM_BIN_DIR})



set(INSTALL_COIL_DIR ${INSTALL_RTM_LIB_DIR}/coil-${RTM_MAJOR_VERSION}.${RTM_MINOR_VERSION})
set(CXXFLAGS -Wall -fPIC -O2)

set(LIBS -lpthread ${RTM_LINKER_OPTION} -l${COIL_PROJECT_NAME})

set(PACKAGE coil)
set(COIL_DESCRIPTION Common Operating-system Infrastructure Layer)
set(COIL_LIBS ${COIL_PROJECT_NAME})
set(COIL_VERSION ${RTM_VERSION})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libcoil_cmake.pc.in ${PROJECT_BINARY_DIR}/libcoil.pc @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/libcoil.pc DESTINATION ${INSTALL_RTM_LIB_DIR}/pkgconfig)
