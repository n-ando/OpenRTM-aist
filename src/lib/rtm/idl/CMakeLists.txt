cmake_minimum_required (VERSION 3.0.2)

project (${RTCSKEL_PROJECT_NAME}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(${PROJECT_NAME}_IDLS
	BasicDataType.idl
	DataPort.idl
	DataPort_OpenRTM.idl
	ExtendedDataTypes.idl
	InterfaceDataTypes.idl
	Manager.idl
	OpenRTM.idl
	RTC.idl
	SDOPackage.idl
	SharedMemory.idl
	ExtendedFsmService.idl)

if(CORBA MATCHES "TAO")
	set(${PROJECT_NAME}_IDLS ${${PROJECT_NAME}_IDLS} DataPortUDP.idl)
endif()

# .idl -> .cpp
openrtm_idl_compile_all(${PROJECT_NAME} "${${PROJECT_NAME}_IDLS}" "-I${PROJECT_SOURCE_DIR}")

# .cpp -> .o .so
link_directories(${ORB_LINK_DIR})
include_directories(
	${RTM_INCLUDE_DIR}
	${ORB_INCLUDE_DIR})

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_IDLSKEL})
openrtm_gencode_set_compile_props(${PROJECT_NAME})

add_library(IDL_OBJLIB OBJECT ${${PROJECT_NAME}_IDLGEN})
openrtm_gencode_set_compile_props(IDL_OBJLIB)

# install .idl .h .so
if(UNIX)
	install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
					ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
					RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
					COMPONENT openrtm)
endif()
install(FILES ${${PROJECT_NAME}_IDLS} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl COMPONENT idl)
install(FILES ${${PROJECT_NAME}_HDR} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/idl COMPONENT headers)

add_subdirectory(device_interfaces)
