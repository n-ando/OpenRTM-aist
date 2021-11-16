cmake_minimum_required (VERSION 3.5.1)

set(FLUENTBIT_ROOT ${FLUENTBIT_ROOT} CACHE PATH "set FLUENTBIT_ROOT")
if(NOT FLUENTBIT_ROOT)
	message(STATUS "FLUENTBIT_ROOT is empty.")
	message(STATUS "fluent-bit is checked out from original repository.")

	include(BuildFluentBit.cmake)

	message(STATUS "FLUENTBIT_ROOT = " ${FLUENTBIT_ROOT})
	message(STATUS "FLB_BINARY_DIR = " ${FLB_BINARY_DIR})
	message(STATUS "FLB_SOURCE_DIR = " ${FLB_SOURCE_DIR})
	message(STATUS "libfluent-bit.so: " ${FLB_LIBRARY_DIR}/libfluent-bit.so)

else()
	set(FLB_INCLUDR_DIR ${FLUENTBIT_ROOT}/include)
	set(FLB_LIBRARY_DIR ${FLUENTBIT_ROOT}/lib/fluent-bit)
endif()

project (FluentBit
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

link_directories(${ORB_LINK_DIR} ${FLB_LIBRARY_DIR})
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
	if(FLB_PROJECT)
		add_dependencies(${target} ${FLB_PROJECT})
	endif()
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	openrtm_set_link_props_shared(${target})

	target_include_directories(${target}
			SYSTEM PRIVATE
			${FLB_INCLUDR_DIR}
	)
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


