cmake_minimum_required (VERSION 2.6)
project (rtm)







option (ARTLINUX "ARTLinux is avaiable" OFF)
option (HAVE_DLFCN_H "Define to 1 if you have the <dlfcn.h> header file." ON)
option (HAVE_INTTYPES_H "Define to 1 if you have the <inttypes.h> header file." ON)
option (HAVE_MEMORY_H "Define to 1 if you have the <memory.h> header file." ON)
option (HAVE_NLIST_H "Define to 1 if you have the <nlist.h> header file." ON)
option (HAVE_STDINT_H "Define to 1 if you have the <stdlib.h> header file." ON)
option (HAVE_STRINGS_H "Define to 1 if you have the <strings.h> header file." ON)
option (HAVE_STRING_H "Define to 1 if you have the <string.h> header file." ON)
option (HAVE_SYS_STAT_H "Define to 1 if you have the <sys/stat.h> header file." ON)
option (HAVE_SYS_TYPES_H "Define to 1 if you have the <sys/types.h> header file." ON)
option (HAVE_UNAME "Define to 1 if you have the `uname' function." ON)
option (HAVE_UNISTD_H "Define to 1 if you have the <unistd.h> header file." ON)
option (ORB_IS_MICO "ORB is MICO" OFF)
option (ORB_IS_OMNIORB "ORB is omniORB" OFF)
option (ORB_IS_ORBEXPRESS "ORB is ORBexpresds" OFF)
option (ORB_IS_ORBACUS "ORB is ORBacus" OFF)
option (ORB_IS_ORBIT2 "ORB is ORBit2" OFF)
option (ORB_IS_ORBIX "ORB is Orbix" OFF)
option (ORB_IS_RTORB "ORB is RtORB" OFF)
option (ORB_IS_TAO "ORB is TAO" OFF)
option (RTM_PACKAGE "Name of package" OFF)
option (RTM_PACKAGE_BUGREPORT "Define to the address where bug reports for this package should be sent." OFF)
option (RTM_PACKAGE_NAME "Define to the full name of this package." OFF)
option (RTM_PACKAGE_STRING "Define to the full name and version of this package." OFF)
option (RTM_PACKAGE_TARNAME "Define to the one symbol short name of this package." OFF)
option (RTM_PACKAGE_URL "Define to the home page for this package." OFF)
option (RTM_PACKAGE_VERSION "Define to the version of this package." OFF)
option (PYTHON_WRAPPER " Python wrapper is enable" OFF)
option (RTC_CORBA_CXXMAPPING11 "CORBA C++ mapping is ver1.1" OFF)
option (RTC_SOCK_DATAPORT "Socket DataPort is enable" OFF)
option (RTM_GCC2 "RTM is compiled with gcc2" OFF)
option (RTM_OMNIORB_40 "omniORB version is 4.0" OFF)
option (RTM_OMNIORB_41 "omniORB version is 4.1" OFF)
option (RTM_OMNIORB_42 "omniORB version is 4.2" OFF)
option (RTM_OS_CYGWIN "OS is Cygwin" OFF)
option (RTM_OS_DARWIN "OS is Max OS X" OFF)
option (RTM_OS_FREEBSD "OS is FreeBSD" OFF)
option (RTM_OS_HPUX "OS is HP-UX" OFF)
option (RTM_OS_IRIX "OS is IRIX" OFF)
option (RTM_OS_LINUX "OS is Linux" OFF)
option (RTM_OS_VXWORKS "OS is VxWorks" OFF)
option (RTM_OS_OSF1 "OS is OSF1" OFF)
option (RTM_OS_QNX "OS is QNX" OFF)
option (RTM_OS_SUNOS "OS is SunOS" OFF)
option (RTM_RTDSC "RDTSC is enable" OFF)
option (WITH_DMALLOC "Define if using the dmalloc debugging malloc package" OFF)
option (_REENTRANT "Multi Thread Support" ON)



set(LT_OBJDIR .libs/ CACHE STRING "Define to the sub-directory in which libtool stores uninstalled libraries.")
set(RTM_MAJOR_VERSION 1 CACHE STRING "RTM major version")
set(RTM_MINOR_VERSION 2 CACHE STRING "RTM minor version")
set(RTM_REVISION_NUM 0 CACHE STRING "RTM revision numver")
set(RTM_SHORT_VERSION 120 CACHE STRING "RTM short version")
set(RTM_VERSION 1.2.0 CACHE STRING "RTM version")
set(STDC_HEADERS 1 CACHE STRING "Define to 1 if you have the ANSI C header files.")
set(OSVERSION 69 CACHE STRING "OS version.")







set(CORBA ${CORBA} CACHE PATH "set CORBA ")

if(NOT CORBA)
	message(FATAL_ERROR "Please set CORBA.")
endif()



set(ORB_ROOT ${ORB_ROOT} CACHE STRING "set ORB_ROOT")


if(NOT ORB_ROOT)
	message(FATAL_ERROR "Please set ORB_ROOT.")
endif()



if(CORBA MATCHES "ORBexpress")
	if(RTP)
		set(ORB_LINK_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_Rp/config_rt_fast/lib)
		set(ORB_INCLUDE_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_Rp/config_rt_fast/include)
		link_directories(${ORB_LINK_DIR})
		include_directories(${ORB_INCLUDE_DIR})
		set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEudp OEorb)

	else(RTP)
		set(ORB_LINK_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/lib ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/lib)
		set(ORB_INCLUDE_DIR ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/include)
		set(ORB_INCLUDE_DIR ${ORB_INCLUDE_DIR} ${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/include)


		
		link_directories(${ORB_LINK_DIR})
		include_directories(${ORB_INCLUDE_DIR})
		#include_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/include)
	
		set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEudp OEorb)
		
	endif()
	SET (ORB_C_FLAGS_LIST
		-Wpointer-arith -Wwrite-strings -Waggregate-return -Wredundant-decls -Wno-unused -Wshadow -Wundef -Wold-style-cast -fno-implement-inlines -fvolatile  -ansi -msoft-float
	)
	ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})
	set (ORB_IS_ORBEXPRESS ON)
	set (ORB_IS_ORBEXPRESS ON PARENT_SCOPE)
elseif(CORBA MATCHES "omniORB")
	if(RTP)
		set(ORB_LINK_DIR ${ORB_ROOT}/lib/${CPU_TYPE}_vxWorks_RTP_${VXWORKS_MAJOR}.${VXWORKS_MINOR})
	else(RTP)
		set(ORB_LINK_DIR ${ORB_ROOT}/lib/${CPU_TYPE}_vxWorks_kernel_${VXWORKS_MAJOR}.${VXWORKS_MINOR})
	endif()
	link_directories(${ORB_LINK_DIR})
	set(ORB_INCLUDE_DIR ${ORB_ROOT}/include)
	
	include_directories(${ORB_INCLUDE_DIR})
	set(ORB_LIBRARIES omniDynamic4 omniORB4 omnithread)
	SET (ORB_C_FLAGS_LIST
		-D__vxWorks__
		-D__x86__
	)
	ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})
	set (ORB_IS_OMNIORB ON)
	set (ORB_IS_OMNIORB ON PARENT_SCOPE)
endif()

set(ORB_C_FLAGS_LIST ${ORB_C_FLAGS_LIST} PARENT_SCOPE)
set(ORB_LINK_DIR ${ORB_LINK_DIR} PARENT_SCOPE)
set(ORB_INCLUDE_DIR ${ORB_INCLUDE_DIR} PARENT_SCOPE)
set(ORB_LIBRARIES ${ORB_LIBRARIES} PARENT_SCOPE)


#ADD_DEFINITIONS(-DRTC_CORBA_CXXMAPPING11)

set (RTC_CORBA_CXXMAPPING11 ON)




#ADD_DEFINITIONS(-DCORBA_ANY_SHARED_PTR_OPERATORS -DINCLUDE_CORBA_CORBALOC)



if(VXWORKS)
	set(COIL_OS_DIR "vxworks")
	set (RTM_OS_VXWORKS ON)
elseif(UNIX)
	set(COIL_OS_DIR "posix")
	set (RTM_OS_LINUX ON)
elseif(WIN32)
	set(COIL_OS_DIR "win32")
endif()



configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_rtc.h.in ${PROJECT_BINARY_DIR}/config_rtc.h)


set(OPENRTM_NAME OpenRTM-aist-1.2.0 CACHE STRING "RTM name.")
set(OPENRTM_VERSION 1.2.0 CACHE STRING "RTM version.")
set(CORBA_NAME omniORB CACHE STRING "CORBA name.")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${PROJECT_BINARY_DIR}/version.h)


set(RTM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/coil/common
		${PROJECT_BINARY_DIR}/idl
		${CMAKE_SOURCE_DIR}/coil/${COIL_OS_DIR}
		${PROJECT_BINARY_DIR}/..)

include_directories(
		${RTM_INCLUDE_DIR}
		)


set(RTM_INCLUDE_DIR ${RTM_INCLUDE_DIR}  PARENT_SCOPE)



set(rtm_srcs
	ConfigAdmin.cpp
	ModuleManager.cpp
	CorbaNaming.cpp
	NVUtil.cpp
	ManagerActionListener.cpp
	LocalServiceAdmin.cpp
	Factory.cpp
	PublisherPeriodic.cpp
	ECFactory.cpp
	OutPortCorbaCdrConsumer.cpp
	PeriodicExecutionContext.cpp
	InPortPushConnector.cpp
	CORBA_IORUtil.cpp
	ManagerServant.cpp
	OpenHRPExecutionContext.cpp
	RTObjectStateMachine.cpp
	InPortProvider.cpp
	PortConnectListener.cpp
	DefaultPeriodicTask.cpp
	NamingManager.cpp
	OutPortCorbaCdrProvider.cpp
	InPortDirectProvider.cpp
	PortBase.cpp
	OutPortProvider.cpp
	ExecutionContextProfile.cpp
	PublisherFlush.cpp
	OutPortPushConnector.cpp
	CorbaPort.cpp
	SdoConfiguration.cpp
	RTObject.cpp
	DataFlowComponentBase.cpp
	ManagerConfig.cpp
	SystemLogger.cpp
	ExecutionContextWorker.cpp
	ExecutionContextBase.cpp
	ExtTrigExecutionContext.cpp
	InPortBase.cpp
	SdoOrganization.cpp
	PortAdmin.cpp
	InPortPullConnector.cpp
	ConfigurationListener.cpp
	OutPortPullConnector.cpp
	LogstreamFile.cpp
	RTCUtil.cpp
	CdrRingBuffer.cpp
	InPortCorbaCdrProvider.cpp
	ConnectorListener.cpp
	PeriodicECSharedComposite.cpp
	PublisherNew.cpp
	ComponentActionListener.cpp
	InPortDirectConsumer.cpp
	OutPortBase.cpp
	Manager.cpp
	InPortCorbaCdrConsumer.cpp
	FactoryInit.cpp
	SdoServiceAdmin.cpp
	InPortConnector.cpp
	OutPortConnector.cpp
	NumberingPolicy.cpp
)

#message(STATUS ${ALL_IDL_SRCS})

#message(STATUS ${ORB_LIBRARIES})

#add_executable(rtm rtcd.cpp TestRTC.cpp ${rtm_srcs} ${ALL_IDL_SRCS})
#add_library(rtm STATIC ${rtm_srcs} ${ALL_IDL_SRCS} )
add_library(rtm STATIC ${rtm_srcs})




add_dependencies(rtm coil)
#add_dependencies(rtm ALL_IDL_TGT)



add_subdirectory(idl)
add_dependencies(rtm RTCSkel)





#target_link_libraries(rtm ${ORB_LIBRARIES} coil)




