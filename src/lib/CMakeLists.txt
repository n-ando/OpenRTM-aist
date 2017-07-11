cmake_minimum_required (VERSION 2.6)


if(CORBA MATCHES "ORBexpress")
	if(NOT IDL_COMPILE_COMMAND)
		set(IDL_COMPILE_COMMAND ${ORB_ROOT}/host/x86_linux_2.6/bin/idl2cpp)
	endif()
	SET(IDLCOMMAND_FLAGS -m -a -ex -fhh -fxcc -fc_c -fs -q -dOE_IDL -I${ORB_ROOT}/idl )
elseif(CORBA MATCHES "omniORB")
	if(NOT IDL_COMPILE_COMMAND)
		set(IDL_COMPILE_COMMAND ${ORB_ROOT}/build/bin/omniidl)
	endif()
	SET(IDLCOMMAND_FLAGS -bcxx -Wba -nf)
endif()

if(UNIX)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper)
elseif(VXWORKS)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper)
elseif(MSVC)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper.py)
endif()




add_subdirectory(coil)
add_subdirectory(rtm)
add_subdirectory(examples)
add_subdirectory(utils)

