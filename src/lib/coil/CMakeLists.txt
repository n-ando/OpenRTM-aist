cmake_minimum_required (VERSION 2.6)
project (coil)


if(VXWORKS)
	set(COIL_OS_DIR "vxworks")
elseif(UNIX)
	set(COIL_OS_DIR "posix")
elseif(WIN32)
	set(COIL_OS_DIR "win32")
endif()






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
	${COIL_OS_DIR}/coil/Affinity.cpp
	${COIL_OS_DIR}/coil/Condition.cpp
	${COIL_OS_DIR}/coil/DynamicLib.cpp
	${COIL_OS_DIR}/coil/Mutex.cpp
	${COIL_OS_DIR}/coil/Routing.cpp
	${COIL_OS_DIR}/coil/Process.cpp
	${COIL_OS_DIR}/coil/Signal.cpp
	${COIL_OS_DIR}/coil/Task.cpp
	${COIL_OS_DIR}/coil/Time.cpp
	${COIL_OS_DIR}/coil/UUID.cpp


)



include_directories(
		${PROJECT_SOURCE_DIR}/common 
		${PROJECT_SOURCE_DIR}/${COIL_OS_DIR}
		)
message(STATUS ${CMAKE_INCLUDE_DIRECTORIES_BEFORE})

add_library(coil STATIC ${coil_srcs} )
#add_executable(coil  ${coil_srcs} )



