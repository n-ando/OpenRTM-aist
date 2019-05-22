cmake_minimum_required (VERSION 3.0.2)

add_subdirectory(rtcd)
add_subdirectory(rtcprof)
add_subdirectory(cmake)
add_subdirectory(rtm-skelwrapper)

if(VXWORKS)
else()
	if(Boost_FOUND)
		add_subdirectory(rtcsh)
	endif()
endif()

if(UNIX)
	add_subdirectory(rtm-naming)
	add_subdirectory(rtm-config)
endif()
