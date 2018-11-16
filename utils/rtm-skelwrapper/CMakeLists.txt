cmake_minimum_required (VERSION 2.6)


if(UNIX)
	install(FILES rtm-skelwrapper DESTINATION ${INSTALL_RTM_BIN_DIR} COMPONENT utils)
	install(FILES skel_wrapper.py DESTINATION ${INSTALL_RTM_SCRIPT_DIR} COMPONENT utils)
elseif(MSVC)
	configure_file(rtm-skelwrapper ${PROJECT_BINARY_DIR}/rtm-skelwrapper.py COPYONLY)
	install(FILES ${PROJECT_BINARY_DIR}/rtm-skelwrapper.py DESTINATION ${INSTALL_RTM_SCRIPT_DIR} COMPONENT utils)
endif(UNIX)


