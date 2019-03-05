cmake_minimum_required (VERSION 3.0.2)

project (SSLTransport
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


set(OPENSSL_ROOT ${OPENSSL_ROOT} CACHE PATH "set OPENSSL_ROOT")


if(NOT OPENSSL_ROOT)
	if(UNIX)
		set(ORB_ROOT "/usr")
	else(UNIX)
		message(FATAL_ERROR "Please set OPENSSL_ROOT.")
	endif(UNIX)
endif()

set(SSL_INCLUDE_DIR ${OPENSSL_ROOT}/include)
set(SSL_LINK_DIR ${OPENSSL_ROOT}/lib)

if(WIN32)
	set(SSL_LIBRARIES libssl libcrypto)
else(WIN32)
	set(SSL_LIBRARIES ssl crypto)
endif(WIN32)


link_directories(${ORB_LINK_DIR} ${SSL_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${${idl_name}_DIR}
		${SSL_INCLUDE_DIR}
		)

add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})


set(target SSLTransport)

set(srcs SSLTransport.cpp )


set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${SSL_LIBRARIES} ${ORBSSL_LIBRARIES})


add_library(${target} SHARED ${srcs})
target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
add_dependencies(${target} ${RTM_PROJECT_NAME})
set_target_properties(${target} PROPERTIES PREFIX "")


install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl
			ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl
			RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl
			COMPONENT ext)

if(WIN32)
	file(GLOB OPENSSL_DLLS1 "${OPENSSL_ROOT}/bin/libcrypto*.dll")
	file(GLOB OPENSSL_DLLS2 "${OPENSSL_ROOT}/bin/libssl*.dll")

	foreach(library ${OPENSSL_DLLS1};${OPENSSL_DLLS2})
		install(PROGRAMS ${library} DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl COMPONENT ssllibs)
	endforeach()
	install(PROGRAMS ${OPENSSL_ROOT}/bin/openssl.exe DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl COMPONENT ssllibs)
	
else(WIN32)
endif(WIN32)
