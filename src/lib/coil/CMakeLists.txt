cmake_minimum_required (VERSION 2.6)
project (coil)









set(coil_srcs
	common/coil/Allocator.cpp
	common/coil/ClockManager.cpp
	common/coil/PeriodicTask.cpp
	common/coil/Properties.cpp
	common/coil/TimeMeasure.cpp
	common/coil/TimeValue.cpp
	common/coil/Timer.cpp
	common/coil/crc.cpp
	common/coil/stringutil.cpp
	vxworks/coil/Condition.cpp
	vxworks/coil/DynamicLib.cpp
	vxworks/coil/Mutex.cpp
#	vxworks/coil/Routing.cpp
	vxworks/coil/Process.cpp
	vxworks/coil/Signal.cpp
	vxworks/coil/Task.cpp
	vxworks/coil/Time.cpp
	vxworks/coil/UUID.cpp


)


include_directories(
		${PROJECT_SOURCE_DIR}/common 
		${PROJECT_SOURCE_DIR}/vxworks
		)
message(STATUS ${CMAKE_INCLUDE_DIRECTORIES_BEFORE})

add_library(coil STATIC ${coil_srcs} )
#add_executable(coil  ${coil_srcs} )



