cmake_minimum_required (VERSION 3.5.1)

add_subdirectory(sdo)
add_subdirectory(local_service)
add_subdirectory(ec)
add_subdirectory(logger)

add_subdirectory(transport)

if(VXWORKS)
	if(RTP)
	else(RTP)
		add_subdirectory(interrupt_task)
	endif(RTP)
endif(VXWORKS)

if(SSL_ENABLE)
	add_subdirectory(ssl)
endif(SSL_ENABLE)