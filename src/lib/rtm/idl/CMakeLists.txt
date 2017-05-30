cmake_minimum_required (VERSION 2.6)








set(IDL_COMPILE_COMMAND ${ORB_ROOT}/host/x86_linux_2.6/bin/idl2cpp)


macro(idl_compile idl_name)

	if(UNIX)
		set(skelwrapper_commend ${OPENRTM_DIRS}/utils/rtm-skelwrapper/rtm-skelwrapper)
	elseif(VXWORKS)
		set(skelwrapper_commend ${OPENRTM_DIRS}/utils/rtm-skelwrapper/rtm-skelwrapper)
	elseif(MSVC)
		set(skelwrapper_commend ${OPENRTM_DIRS}/utils/rtm-skelwrapper/rtm-skelwrapper.py)
	endif()
	add_custom_command(
		OUTPUT ${idl_name}Skel.cpp
		#COMMAND mkdir -p include/rtm/idl
		#COMMAND cd include/rtm/idl
		COMMAND ${IDL_COMPILE_COMMAND}  -m -a -ex -fhh -fxcc -fc_c -fs -q -dOE_IDL -I${PROJECT_SOURCE_DIR}/idl -I${ORB_ROOT}/idl ${PROJECT_SOURCE_DIR}/idl/${idl_name}.idl
		COMMAND python ${skelwrapper_commend} --include-dir="" --skel-suffix=Skel --stub-suffix=Stub --idl-file=${idl_name}.idl
		#WORKING_DIRECTORY ${CURRENT_BINARY_DIR}/include/rtm/idl
		WORKING_DIRECTORY ${CURRENT_BINARY_DIR}
	)
	

	add_custom_target(${idl_name}_TGT DEPENDS ${idl_name}Skel.cpp)
	set(ALL_IDL_SRCS ${ALL_IDL_SRCS} idl/${idl_name}Skel.cpp)

	if(NOT TARGET ALL_IDL_TGT)
		add_custom_target(ALL_IDL_TGT)
	endif(NOT TARGET ALL_IDL_TGT)
	add_dependencies(ALL_IDL_TGT ${idl_name}_TGT)
	#include_directories(${PROJECT_BINARY_DIR}/idl)
endmacro()



set(idls
	BasicDataType
	DataPort
	ExtendedDataTypes
	InterfaceDataTypes
	Manager
	OpenRTM
	RTC
	SDOPackage
	)


foreach(idl ${idls})
	idl_compile(${idl})
endforeach(idl)









set(ALL_IDL_SRCS ${ALL_IDL_SRCS} PARENT_SCOPE)





