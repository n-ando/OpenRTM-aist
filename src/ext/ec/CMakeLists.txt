cmake_minimum_required (VERSION 3.5.1)

if(NOT CORBA MATCHES "RtORB")
	add_subdirectory(logical_time)
endif()

if(UNIX)
	add_subdirectory(rtpreempt)
endif()
