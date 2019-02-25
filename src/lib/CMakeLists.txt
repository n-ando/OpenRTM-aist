cmake_minimum_required (VERSION 3.0.2)

add_subdirectory(rtm)
add_subdirectory(coil)

set(RTM_INCLUDE_DIR ${RTM_INCLUDE_DIR}  PARENT_SCOPE)
set(DATATYPE_FACTORIES ${DATATYPE_FACTORIES} PARENT_SCOPE)