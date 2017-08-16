cmake_minimum_required (VERSION 2.6)


add_subdirectory(rtcd)
add_subdirectory(rtcprof)


if(CORBA MATCHES "ORBexpress")
	if(RTP)
	else(RTP)
		add_subdirectory(Names)
	endif(RTP)
endif()
