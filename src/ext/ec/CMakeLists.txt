cmake_minimum_required (VERSION 3.0.2)

add_subdirectory(logical_time)

if(UNIX)
	add_subdirectory(rtpreempt)
endif(UNIX)


if(ARTLINUX)
	add_subdirectory(artlinux)
endif(ARTLINUX)
