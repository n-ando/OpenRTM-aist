cmake_minimum_required (VERSION 2.6)

add_subdirectory(logical_time)

if(UNIX)
	add_subdirectory(rtpreempt)
endif(UNIX)


if(ARTLINUX)
	add_subdirectory(artlinux)
endif(ARTLINUX)
