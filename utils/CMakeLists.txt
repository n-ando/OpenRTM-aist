cmake_minimum_required (VERSION 2.6)


add_subdirectory(rtcd)
add_subdirectory(rtcprof)
add_subdirectory(cmake)
add_subdirectory(rtm-skelwrapper)



if(VXWORKS)
else(VXWORKS)
	if(Boost_FOUND)
		add_subdirectory(rtcsh)
	endif(Boost_FOUND)
endif(VXWORKS)

if(UNIX)
	add_subdirectory(rtm-naming)
endif(UNIX)

if(CORBA MATCHES "ORBexpress")
	if(RTP)
	else(RTP)
		add_subdirectory(Names)
	endif(RTP)
endif()
