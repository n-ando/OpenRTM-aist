cmake_minimum_required (VERSION 2.6)



configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rtm-naming.in ${PROJECT_BINARY_DIR}/rtm-naming @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/rtm-naming DESTINATION ${INSTALL_RTM_BIN_DIR} COMPONENT utils)
