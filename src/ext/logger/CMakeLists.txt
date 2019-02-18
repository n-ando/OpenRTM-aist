cmake_minimum_required (VERSION 3.0.2)

if(UNIX)
	set(FLUENTBIT_ENABLE ${FLUENTBIT_ENABLE} CACHE BOOL "set FLUENTBIT_ENABLE")
	if(FLUENTBIT_ENABLE)
		add_subdirectory(fluentbit_stream)
	endif(FLUENTBIT_ENABLE)
endif(UNIX)

