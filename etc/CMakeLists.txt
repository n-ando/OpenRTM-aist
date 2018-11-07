cmake_minimum_required (VERSION 2.6)



install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rtc.conf.sample DESTINATION ${INSTALL_RTM_ETC_DIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/tao_udp/svc.conf DESTINATION ${INSTALL_RTM_ETC_DIR}/tao_udp)
