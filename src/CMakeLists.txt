cmake_minimum_required (VERSION 3.0.2)

add_subdirectory(lib)
add_subdirectory(ext)

set(RTM_INCLUDE_DIR ${RTM_INCLUDE_DIR}  PARENT_SCOPE)
