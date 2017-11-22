cmake_minimum_required (VERSION 2.6)

project (OpenRTM_aist)






set(CORBA ${CORBA} CACHE STRING "set CORBA ")

if(NOT CORBA)
	message(FATAL_ERROR "Please set CORBA.")
endif()



set(ORB_ROOT ${ORB_ROOT} CACHE PATH "set ORB_ROOT")


if(NOT ORB_ROOT)
	
	if(CORBA MATCHES "omniORB")
		if(UNIX)
			set(ORB_ROOT "/usr")
		else(UNIX)
			message(FATAL_ERROR "Please set ORB_ROOT.")
		endif(UNIX)
	else()
		message(FATAL_ERROR "Please set ORB_ROOT.")
	endif()
endif()


if(CORBA MATCHES "ORBexpress")
	if(NOT IDL_COMPILE_COMMAND)
		set(IDL_COMPILE_COMMAND ${ORB_ROOT}/host/x86_linux_2.6/bin/idl2cpp)
	endif()
	SET(IDLCOMMAND_FLAGS -m -a -ex -fhh -fxcc -fc_c -fs -q -dOE_IDL -I${ORB_ROOT}/idl )
elseif(CORBA MATCHES "omniORB")
	if(NOT IDL_COMPILE_COMMAND)
		if(VXWORKS)
			set(IDL_COMPILE_COMMAND ${ORB_ROOT}/build/bin/omniidl)
		elseif(UNIX)
			set(IDL_COMPILE_COMMAND ${ORB_ROOT}/bin/omniidl)
		elseif(MSVC)
			set(IDL_COMPILE_COMMAND ${ORB_ROOT}/bin/x86_win32/omniidl)
		endif(VXWORKS)
	endif()
	SET(IDLCOMMAND_FLAGS -bcxx -Wba -nf -Wbshortcut)
	#SET(IDLCOMMAND_FLAGS -bcxx -Wba -nf)
elseif(CORBA MATCHES "TAO")
	if(NOT IDL_COMPILE_COMMAND)
		if(VXWORKS)
			message(FATAL_ERROR "Please set IDL_COMPILE_COMMAND.")
		elseif(UNIX)
			set(IDL_COMPILE_COMMAND ${ORB_ROOT}/bin/tao_idl)
		elseif(MSVC)
			set(IDL_COMPILE_COMMAND ${ORB_ROOT}/bin/tao_idl)
		endif(VXWORKS)
	endif()
	if(UNIX)
		SET(IDLCOMMAND_FLAGS -as -DTAO_IDL -I${ORB_ROOT}/include)
	elseif(VXWORKS)
		SET(IDLCOMMAND_FLAGS -as -DTAO_IDL -I${ORB_ROOT}/TAO)
	elseif(MSVC)
		SET(IDLCOMMAND_FLAGS -as -DTAO_IDL -I${ORB_ROOT}/TAO)
	endif()
endif()

if(UNIX)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper)
elseif(VXWORKS)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper)
elseif(MSVC)
	set(SKELWRAPPER_COMMAND ${CMAKE_SOURCE_DIR}/utils/rtm-skelwrapper/rtm-skelwrapper)
endif()








if(VXWORKS)
	if("${VX_CPU_FAMILY}" STREQUAL "ppc")
		SET (CPU_TYPE powerpc)
	elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
		SET (CPU_TYPE simpentium)
	elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
		SET (CPU_TYPE simlinux)
	endif()
endif(VXWORKS)



if(CORBA MATCHES "ORBexpress")
	set(CORBA_NAME "ORBexpress" CACHE STRING "CORBA name.")
	if(RTP)
		set(OE_TARGET gcc_4.1.2_Rp)
		set(OE_TYPE config_rt_fast)
		set(ORB_LINK_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/${OE_TYPE}/lib)
		set(ORB_INCLUDE_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/${OE_TYPE}/include)

		set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEorb)

	else(RTP)
		set(OE_TARGET gcc_4.1.2_ExLcRi)
		#set(OE_TARGET gcc_4.1.2_Lc)
		#set(OE_TYPE config_rt_fast)
		set(OE_TYPE config_rt_full)
		#set(OE_TYPE config_rt_minimum)
		#set(OE_TYPE config_rt_small)
		set(ORB_LINK_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/config_rt_full/lib ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/${OE_TYPE}/OENames_2.1.6/lib)
		set(ORB_INCLUDE_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/${OE_TYPE}/include)
		set(ORB_INCLUDE_DIR ${ORB_INCLUDE_DIR} ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/${OE_TARGET}/${OE_TYPE}/OENames_2.1.6/include)


		
		
		#include_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/include)
		set(ORB_LIBRARIES OEnames OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEorb)
		#set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEudp OEorb OEnames)
		
	endif()
	SET (ORB_C_FLAGS_LIST
		 -DCORBA_ANY_SHARED_PTR_OPERATORS -DINCLUDE_CORBA_CORBALOC
#		-Wpointer-arith -Wwrite-strings -Waggregate-return -Wredundant-decls -Wno-unused -Wshadow -Wundef -Wold-style-cast -fno-implement-inlines -fvolatile  -ansi -msoft-float
	)
	if("${VX_CPU_FAMILY}" STREQUAL "ppc")
		set(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST} -D__powerpc__)
	else()
		set(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST} -D__x86__)
	endif()
	ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})
elseif(CORBA MATCHES "omniORB")
	set(CORBA_NAME "omniORB" CACHE STRING "CORBA name.")
	if(VXWORKS)
		if("${VX_CPU_FAMILY}" STREQUAL "ppc")
			SET (ORB_C_FLAGS_LIST
				-D__vxWorks__
				-D__powerpc__
			)
		else()
			SET (ORB_C_FLAGS_LIST
				-D__vxWorks__
				-D__x86__
			)
		endif()
		if(RTP)
			set(ORB_LINK_DIR ${ORB_ROOT}/lib/${CPU_TYPE}_vxWorks_RTP_${VXWORKS_MAJOR}.${VXWORKS_MINOR})
		else(RTP)
			set(ORB_LINK_DIR ${ORB_ROOT}/lib/${CPU_TYPE}_vxWorks_kernel_${VXWORKS_MAJOR}.${VXWORKS_MINOR})
		endif()
		set(ORB_LIBRARIES omniDynamic4 omniORB4 omnithread)
	elseif(UNIX)
		if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "ARM")
			SET (ORB_C_FLAGS_LIST
				-D__arm__
			)
		else()
			SET (ORB_C_FLAGS_LIST
				-D__x86__
			)
		endif()
		set(ORB_LINK_DIR ${ORB_ROOT}/lib)
		set(ORB_LIBRARIES omniDynamic4 omniORB4 omnithread)
	elseif(MSVC)
		if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
			SET (ORB_C_FLAGS_LIST
				-D__WIN32__
				-D__arm__
			)
			set(ORB_LINK_DIR ${ORB_ROOT}/lib/ARM_win32)
		else()
			SET (ORB_C_FLAGS_LIST
				-D__WIN32__
				-D__x86__
			)
			set(ORB_LINK_DIR ${ORB_ROOT}/lib/x86_win32)
		endif()
		set(ORB_LIBRARIES optimized;omniDynamic${OMNI_VERSION}${OMNI_MINOR}_rt;optimized;omniORB${OMNI_VERSION}${OMNI_MINOR}_rt;omnithread${OMNITHREAD_VERSION}_rt;debug;omniDynamic${OMNI_VERSION}${OMNI_MINOR}_rtd;debug;omniORB${OMNI_VERSION}${OMNI_MINOR}_rtd;debug;omnithread${OMNITHREAD_VERSION}_rtd)
	endif(VXWORKS)

	set(ORB_INCLUDE_DIR ${ORB_ROOT}/include)
	

	
	ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})
elseif(CORBA MATCHES "TAO")
	set(CORBA_NAME "TAO" CACHE STRING "CORBA name.")
	
	if(VXWORKS)
		if("${VX_CPU_FAMILY}" STREQUAL "ppc")
			SET(ORB_C_FLAGS_LIST -D__powerpc__)
		else()
			SET(ORB_C_FLAGS_LIST -D__x86__)
		endif()
		SET(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST} -DACE_VXWORKS=0x690 -DACE_HAS_PTHREADS -DACE_HAS_AIO_CALLS -DACE_LACKS_ISBLANK)

		set(ORB_LINK_DIR ${ORB_ROOT}/lib)
		set(ORB_LIBRARIES   TAO_AnyTypeCode TAO_PortableServer TAO_Svc_Utils TAO_CosNaming   TAO_AnyTypeCode TAO_DynamicInterface TAO_PI TAO_Utils TAO_PortableServer TAO_DiffServPolicy TAO_DynamicInterface  TAO ACE)
		set(ORB_INCLUDE_DIR ${ORB_ROOT} ${ORB_ROOT}/TAO ${ORB_ROOT}/TAO/orbsvcs)
	elseif(UNIX)
		set(ORB_LINK_DIR ${ORB_ROOT}/lib)
		set(ORB_LIBRARIES ACE TAO TAO_AnyTypeCode TAO_PortableServer TAO_Svc_Utils TAO_CosNaming TAO_IORTable TAO_CodecFactory TAO_PI TAO_Utils)
		set(ORB_INCLUDE_DIR ${ORB_ROOT}/include)
	elseif(MSVC)
		set(ORB_LINK_DIR ${ORB_ROOT}/lib)
		set(ORB_LIBRARIES optimized;ACE;optimized;TAO;optimized;TAO_AnyTypeCode;optimized;TAO_PortableServer;optimized;TAO_Svc_Utils;optimized;TAO_CosNaming;optimized;TAO_IORTable;optimized;TAO_CodecFactory;optimized;TAO_PI;optimized;TAO_Utils;debug;ACEd;debug;TAOd;debug;TAO_AnyTypeCoded;debug;TAO_PortableServerd;debug;TAO_Svc_Utilsd;debug;TAO_CosNamingd;debug;TAO_IORTabled;debug;TAO_CodecFactoryd;debug;TAO_PId;debug;TAO_Utilsd;iphlpapi)
		set(ORB_INCLUDE_DIR ${ORB_ROOT} ${ORB_ROOT}/TAO ${ORB_ROOT}/TAO/orbsvcs)
		SET(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST} -D_WINSOCKAPI_ -DWITH_ACE)
	endif()
	
	ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})
endif()


if(VXWORKS)

	set(ORB_LIBRARIES_PATH)
	FOREACH(NAME ${ORB_LIBRARIES})
		SET(ORB_LIB ORB_${NAME}_LIBRARY)
		LIST(APPEND ORB_LIBVARS ${ORB_LIB})
		FIND_LIBRARY(${ORB_LIB} ${NAME}
			PATHS ${ORB_LINK_DIR}
			CMAKE_FIND_ROOT_PATH_BOTH)
		if(${ORB_LIB})
			LIST(APPEND ORB_LIBRARIES_PATH ${${ORB_LIB}})
		endif(${ORB_LIB})
	ENDFOREACH(NAME)

	set(ORB_LIBRARIES ${ORB_LIBRARIES_PATH})
else(VXWORKS)
endif(VXWORKS)


set(ORB_INCLUDE_DIR ${ORB_INCLUDE_DIR})
set(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST})






set(RTM_MAJOR_VERSION 1 CACHE STRING "RTM major version")
set(RTM_MINOR_VERSION 2 CACHE STRING "RTM minor version")
set(RTM_REVISION_NUM 0 CACHE STRING "RTM revision numver")
set(RTM_SHORT_VERSION 120 CACHE STRING "RTM short version")
set(RTM_VERSION 1.2.0 CACHE STRING "RTM version")






if(VXWORKS)
	set(COIL_OS_DIR "vxworks")
	set (RTM_OS_VXWORKS ON)
elseif(UNIX)
	set(COIL_OS_DIR "posix")
	set (RTM_OS_LINUX ON)
	ADD_DEFINITIONS(-fPIC)
	set(RTM_LINKER_OPTION -luuid -ldl -export-dynamic -lrt)
elseif(WIN32)
	set(COIL_OS_DIR "win32")
	set(RTM_LINKER_OPTION advapi32.lib;ws2_32.lib;mswsock.lib;rpcrt4.lib;optimized;msvcrt.lib;optimized;msvcmrt.lib;debug;msvcmrtd.lib;debug;msvcrtd.lib)
	ADD_DEFINITIONS(-DLIBRARY_EXPORTS)
endif()

set(OPENRTM_NAME OpenRTM-aist-1.2.0 CACHE STRING "RTM name.")
set(OPENRTM_VERSION 1.2.0 CACHE STRING "RTM version.")

set(COIL_PROJECT_NAME coil${RTM_MAJOR_VERSION}${RTM_MINOR_VERSION}${RTM_REVISION_NUM})
set(RTM_PROJECT_NAME RTC${RTM_MAJOR_VERSION}${RTM_MINOR_VERSION}${RTM_REVISION_NUM})
set(RTCSKEL_PROJECT_NAME RTCSkel)

if(MSVC)
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008")
		set(RTM_VC_VER "vc9")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 10 2010")
		set(RTM_VC_VER "vc10")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 10 2010 Win64")
		set(RTM_VC_VER "vc10")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 11 2012")
		set(RTM_VC_VER "vc11")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 11 2012 Win64")
		set(RTM_VC_VER "vc11")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 2013")
		set(RTM_VC_VER "vc12")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 2013 Win64")
		set(RTM_VC_VER "vc12")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 14 2015")
		set(RTM_VC_VER "vc14")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 14 2015 Win64")
		set(RTM_VC_VER "vc14")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017")
		set(RTM_VC_VER "vc141")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017 Win64")
		set(RTM_VC_VER "vc141")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 11 2012 ARM")
		set(RTM_VC_VER "vc11")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 2013 ARM")
		set(RTM_VC_VER "vc12")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 14 2015 ARM")
		set(RTM_VC_VER "vc14")
	endif()
	if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017 ARM")
		set(RTM_VC_VER "vc141")
	endif()
	set(COIL_PROJECT_NAME ${COIL_PROJECT_NAME}_${RTM_VC_VER})
	set(RTM_PROJECT_NAME ${RTM_PROJECT_NAME}_${RTM_VC_VER})
endif()


if(WIN32)
	set(MAKE_DEF_COMMAND ${CMAKE_SOURCE_DIR}/build/makedeffile.py)
endif(WIN32)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(utils)

if(WIN32)
	install(FILES ${CMAKE_SOURCE_DIR}/win32/OpenRTM-aist/bin/rtm-naming.bat DESTINATION bin)
endif(WIN32)
