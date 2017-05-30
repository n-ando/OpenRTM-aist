cmake_minimum_required (VERSION 2.6)
project (rtm)

set(ORB_ROOT ${ORB_ROOT} CACHE STRING "set ORB_ROOT")

add_subdirectory(idl)



if(RTP)
	link_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_Rp/config_rt_fast/lib)
	include_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_Rp/config_rt_fast/include)
	set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEudp OEorb )

else(RTP)

	link_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/lib)
	include_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/include)


	link_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/lib)
	include_directories(${ORB_ROOT}/target/ppc_8xx-vxworks_6.6/gcc_4.1.2_ExLcRi/config_rt_full/OENames_2.1.6/include)
	
	set(ORB_LIBRARIES OEtcp OEmirror OEbridge OEudp OEipmc OEshrmem OEudp OEorb )

endif()




#ADD_DEFINITIONS (-DORB_IS_ORBEXPRESS)
ADD_DEFINITIONS("-Wpointer-arith -Wwrite-strings -Waggregate-return -Wredundant-decls -Wno-unused -Wshadow -Wundef -Wold-style-cast -fno-implement-inlines -fvolatile  -ansi -msoft-float  ")

#ADD_DEFINITIONS(-DCORBA_ANY_SHARED_PTR_OPERATORS -DINCLUDE_CORBA_CORBALOC)




include_directories(
		${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/coil/common
		${CMAKE_SOURCE_DIR}/coil/vxworks
		${PROJECT_BINARY_DIR}/..
		)



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
)





add_executable(rtm rtcd.cpp TestRTC.cpp ${rtm_srcs} ${ALL_IDL_SRCS})
#add_library(rtm STATIC ${rtm_srcs} ${ALL_IDL_SRCS} )

set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)

if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)

endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(rtm coil)
add_dependencies(rtm ALL_IDL_TGT)





target_link_libraries(rtm ${ORB_LIBRARIES} coil)




