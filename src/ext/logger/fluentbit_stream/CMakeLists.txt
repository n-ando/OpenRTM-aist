cmake_minimum_required (VERSION 3.5.1)

project (FluentBit
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)



set(FLUENTBIT_ROOT ${FLUENTBIT_ROOT} CACHE PATH "set FLUENTBIT_ROOT")


if(NOT FLUENTBIT_ROOT)
	message(FATAL_ERROR "Please set FLUENTBIT_ROOT.")
endif()



link_directories(${ORB_LINK_DIR} ${FLUENTBIT_ROOT}/lib ${FLUENTBIT_ROOT}/build/lib)
add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})
if(WIN32)
	add_definitions(-DRTM_SKEL_IMPORT_SYMBOL)
endif()
add_definitions(-Dtypeof=decltype)


set(target FluentBit)

set(srcs FluentBit.cpp FluentBit.h)


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_set_link_props_shared(${target})
	target_link_libraries(${target} ${libs} fluent-bit)

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				COMPONENT ext)
else()
	set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${DATATYPE_FACTORIES})

	add_library(${target} SHARED ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	openrtm_set_link_props_shared(${target})
	target_include_directories(${target} SYSTEM
	  PRIVATE
	  ${FLUENTBIT_ROOT}/include
	  ${FLUENTBIT_ROOT}/lib/avro/include
          ${FLUENTBIT_ROOT}/lib/c-ares-809d5e84/include
          ${FLUENTBIT_ROOT}/lib/chunkio/include
          ${FLUENTBIT_ROOT}/lib/cmetrics/include
          ${FLUENTBIT_ROOT}/lib/flb_libco/include
          ${FLUENTBIT_ROOT}/lib/jansson-fd3e9e3/include
          ${FLUENTBIT_ROOT}/lib/jemalloc-5.2.1/include
          ${FLUENTBIT_ROOT}/lib/jsmn/include
          ${FLUENTBIT_ROOT}/lib/libbacktrace-ca0de05/include
          ${FLUENTBIT_ROOT}/lib/luajit-2.1.0-1e66d0f/include
          ${FLUENTBIT_ROOT}/lib/mbedtls-2.27.0/include
          ${FLUENTBIT_ROOT}/lib/miniz/include
          ${FLUENTBIT_ROOT}/lib/monkey/include
          ${FLUENTBIT_ROOT}/lib/mpack-amalgamation-1.0/include
          ${FLUENTBIT_ROOT}/lib/msgpack-c/include
          ${FLUENTBIT_ROOT}/lib/onigmo/include
          ${FLUENTBIT_ROOT}/lib/rbtree/include
          ${FLUENTBIT_ROOT}/lib/snappy-fef67ac/include
          ${FLUENTBIT_ROOT}/lib/sqlite-amalgamation-3330000/include
          ${FLUENTBIT_ROOT}/lib/tutf8e/include
          ${FLUENTBIT_ROOT}/lib/xxHash-0.8.0/include
	  ${FLUENTBIT_ROOT}/build/lib/c-ares-809d5e84/
	  ${FLUENTBIT_ROOT}/lib/flb_libco)
	target_link_libraries(${target} PRIVATE ${libs} ${RTM_LINKER_OPTION} fluent-bit)
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/logger
				COMPONENT ext)
endif()






if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)


