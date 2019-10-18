cmake_minimum_required (VERSION 3.5.1)

add_subdirectory(logical_time)

if(UNIX)
	add_subdirectory(rtpreempt)
endif(UNIX)
