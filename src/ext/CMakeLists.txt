cmake_minimum_required (VERSION 2.6)

add_subdirectory(sdo)


if(VXWORKS)
	if(RTP)
	else(RTP)
		add_subdirectory(interrupt_task)
	endif(RTP)
endif(VXWORKS)