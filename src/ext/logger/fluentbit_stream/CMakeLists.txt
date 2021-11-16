cmake_minimum_required (VERSION 3.5.1)

set(FLUENTBIT_ROOT ${FLUENTBIT_ROOT} CACHE PATH "set FLUENTBIT_ROOT")
if(NOT FLUENTBIT_ROOT)
	message(STATUS "FLUENTBIT_ROOT is empty.")
    message(STATUS "fluent-bit is checked out from original repository.")

    # setting FLB variables
    set(FLB_PROJECT fluent-bit_project)
	set(FLUENTBIT_ROOT
        ${CMAKE_CURRENT_BINARY_DIR}/${FLB_PROJECT}-prefix)
    set(FLB_SOURCE_DIR ${FLUENTBIT_ROOT}/src/${FLB_PROJECT})
    set(FLB_BINARY_DIR ${FLUENTBIT_ROOT}/src/${FLB_PROJECT}-build)

    # Inporting fluent-bit as external project
    include(ExternalProject)
    ExternalProject_Add(
        ${FLB_PROJECT}
        PREFIX ${FLUENTBIT_ROOT}
        INSTALL_COMMAND echo do nothing
        # Git options
        GIT_REPOSITORY https://github.com/fluent/fluent-bit
        GIT_TAG v1.8.9
        # cmake options
        CMAKE_ARGS
            -DFLB_RELEASE=On
            -DFLB_TRACE=Off
            -DFLB_JEMALLOC=Off
            -DFLB_TLS=On
            -DFLB_SHARED_LIB=On
            -DFLB_EXAMPLES=Off
            -DFLB_HTTP_SERVER=On
            -DFLB_IN_SYSTEMD=On
            -DFLB_OUT_KAFKA=On
            -DCMAKE_BUILD_TYPE=Release
    )

    add_library(fluent-bit IMPORTED SHARED)
    set_target_properties(fluent-bit PROPERTIES
            IMPORTED_LOCATION ${FLB_BINARY_DIR}/lib/libfluent-bit.so)

    message(STATUS "FLUENTBIT_ROOT = " ${FLUENTBIT_ROOT})
    message(STATUS "FLB_BINARY_DIR = " ${FLB_BINARY_DIR})
    message(STATUS "FLB_SOURCE_DIR = " ${FLB_SOURCE_DIR})
    message(STSTUS "libfluent-bit.so: " ${FLB_BINARY_DIR}/lib/libfluent-bit.so)
endif()

project (FluentBit
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

link_directories(${ORB_LINK_DIR} ${FLB_BINARY_DIR}/lib)
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
    add_dependencies(${target} fluent-bit_project)
    openrtm_common_set_compile_props(${target})
    openrtm_include_rtm(${target})
    openrtm_set_link_props_shared(${target})
    target_include_directories(${target}
        PRIVATE
        ${FLB_SOURCE_DIR}/include
        ${FLB_SOURCE_DIR}/lib/avro/include
        ${FLB_SOURCE_DIR}/lib/c-ares-809d5e84/include
        ${FLB_SOURCE_DIR}/lib/chunkio/include
        ${FLB_SOURCE_DIR}/lib/cmetrics/include
        ${FLB_SOURCE_DIR}/lib/flb_libco
        ${FLB_SOURCE_DIR}/lib/jansson-fd3e9e3/include
        ${FLB_SOURCE_DIR}/lib/jemalloc-5.2.1/include
        ${FLB_SOURCE_DIR}/lib/jsmn/include
        ${FLB_SOURCE_DIR}/lib/libbacktrace-ca0de05/include
        ${FLB_SOURCE_DIR}/lib/luajit-2.1.0-1e66d0f/include
        ${FLB_SOURCE_DIR}/lib/mbedtls-2.27.0/include
        ${FLB_SOURCE_DIR}/lib/miniz/include
        ${FLB_SOURCE_DIR}/lib/monkey/include
        ${FLB_SOURCE_DIR}/lib/mpack-amalgamation-1.0/include
        ${FLB_SOURCE_DIR}/lib/msgpack-c/include
        ${FLB_SOURCE_DIR}/lib/onigmo/include
        ${FLB_SOURCE_DIR}/lib/rbtree/include
        ${FLB_SOURCE_DIR}/lib/snappy-fef67ac/include
        ${FLB_SOURCE_DIR}/lib/sqlite-amalgamation-3330000/include
        ${FLB_SOURCE_DIR}/lib/tutf8e/include
        ${FLB_SOURCE_DIR}/lib/xxHash-0.8.0/include
        ${FLB_BINARY_DIR}/include
        ${FLB_BINARY_DIR}/lib/c-ares-809d5e84)
	target_link_libraries(${target} PRIVATE 
                        ${libs}
                        ${RTM_LINKER_OPTION}
                        fluent-bit)
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


