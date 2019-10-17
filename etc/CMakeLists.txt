cmake_minimum_required (VERSION 3.5.1)



install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rtc.conf.sample DESTINATION ${INSTALL_RTM_ETC_DIR} COMPONENT ext)

if(CORBA STREQUAL "TAO")
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/tao_udp/svc.conf DESTINATION ${INSTALL_RTM_ETC_DIR}/tao_udp COMPONENT ext)
endif()
