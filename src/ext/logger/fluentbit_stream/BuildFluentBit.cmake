# setting FLB variables
set(FLB_PROJECT fluent-bit_project)
set(FLUENTBIT_ROOT
    ${CMAKE_CURRENT_BINARY_DIR}/${FLB_PROJECT}-prefix)
set(FLB_SOURCE_DIR ${FLUENTBIT_ROOT}/src/${FLB_PROJECT})
set(FLB_BINARY_DIR ${FLUENTBIT_ROOT}/src/${FLB_PROJECT}-build)
set(FLB_LIBRARY_DIR ${FLB_BINARY_DIR}/lib)
set(FLB_INCLUDR_DIR ${FLB_SOURCE_DIR}/include
                    ${FLB_SOURCE_DIR}/lib/avro/src
                    ${FLB_SOURCE_DIR}/lib/c-ares-809d5e84/include
                    ${FLB_SOURCE_DIR}/lib/chunkio/include
                    ${FLB_SOURCE_DIR}/lib/cmetrics/include
                    ${FLB_SOURCE_DIR}/lib/flb_libco
                    ${FLB_SOURCE_DIR}/lib/jansson-fd3e9e3/src
                    ${FLB_SOURCE_DIR}/lib/jemalloc-5.2.1/include
                    ${FLB_SOURCE_DIR}/lib/jsmn
                    ${FLB_SOURCE_DIR}/lib/libbacktrace-ca0de05
                    ${FLB_SOURCE_DIR}/lib/luajit-2.1.0-1e66d0f/src
                    ${FLB_SOURCE_DIR}/lib/mbedtls-2.27.0/include
                    ${FLB_SOURCE_DIR}/lib/miniz
                    ${FLB_SOURCE_DIR}/lib/monkey/include
                    ${FLB_SOURCE_DIR}/lib/mpack-amalgamation-1.0/src
                    ${FLB_SOURCE_DIR}/lib/msgpack-c/include
                    ${FLB_SOURCE_DIR}/lib/onigmo
                    ${FLB_SOURCE_DIR}/lib/rbtree
                    ${FLB_SOURCE_DIR}/lib/snappy-fef67ac
                    ${FLB_SOURCE_DIR}/lib/sqlite-amalgamation-3330000
                    ${FLB_SOURCE_DIR}/lib/tutf8e/include
                    ${FLB_SOURCE_DIR}/lib/xxHash-0.8.0
                    ${FLB_BINARY_DIR}/include
                    ${FLB_BINARY_DIR}/lib/c-ares-809d5e84)
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

