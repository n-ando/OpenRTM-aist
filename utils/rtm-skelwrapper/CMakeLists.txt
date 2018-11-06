cmake_minimum_required (VERSION 2.6)


if(UNIX)
	install(FILES rtm-skelwrapper DESTINATION ${INSTALL_RTM_BIN_DIR})
elseif(MSVC)
	configure_file(rtm-skelwrapper ${PROJECT_BINARY_DIR}/rtm-skelwrapper.py COPYONLY)
	install(FILES ${PROJECT_BINARY_DIR}/rtm-skelwrapper.py DESTINATION ${INSTALL_RTM_BIN_DIR})
endif(UNIX)

install(FILES skel_wrapper.py DESTINATION ${INSTALL_RTM_BIN_DIR})