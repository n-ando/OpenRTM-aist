cmake_minimum_required (VERSION 2.6)



set(target interrupt_task)

project (${target})

add_executable(${target} ${target}.cpp)

set_target_properties(${target} PROPERTIES SUFFIX ".out")