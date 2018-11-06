cmake_minimum_required (VERSION 2.6)

project (SSLTransport)


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
set(SSL_LIBRARIES libssl libcrypto)


link_directories(${ORB_LINK_DIR} ${SSL_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		${${idl_name}_DIR}
		${SSL_INCLUDE_DIR}
		)

ADD_DEFINITIONS(${ORB_C_FLAGS_LIST})


set(target SSLTransport)

set(srcs SSLTransport.cpp )


set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${SSL_LIBRARIES} ${ORBSSL_LIBRARIES})


add_library(${target} SHARED ${srcs})
target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})
add_dependencies(${target} ${RTM_PROJECT_NAME})
set_target_properties(${target} PROPERTIES PREFIX "")


if(WIN32)
	install(TARGETS ${target} RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR})
else(WIN32)
	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/ssl)
endif(WIN32)
