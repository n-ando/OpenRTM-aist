cmake_minimum_required (VERSION 2.6)

add_subdirectory(sdo)


if(SSL_ENABLE)
	add_subdirectory(ssl)
endif(SSL_ENABLE)