cmake_minimum_required (VERSION 3.0.2)


project (ShortToDoubleSerializer
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


link_directories(${ORB_LINK_DIR})
add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})
if(WIN32)
	add_definitions(-DRTM_SKEL_IMPORT_SYMBOL)
endif()


set(target ShortToDoubleSerializer)

set(srcs ShortToDoubleSerializer.cpp)
set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${DATATYPE_FACTORIES})

add_library(${target} SHARED ${srcs})
openrtm_common_set_compile_props(${target})
openrtm_include_rtm(${target})
target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION})

install(TARGETS ${target} LIBRARY
			DESTINATION ${INSTALL_RTM_EXAMPLE_SHAREDLIB_DIR}
			ARCHIVE DESTINATION ${INSTALL_RTM_EXAMPLE_SHAREDLIB_DIR}
			RUNTIME DESTINATION ${INSTALL_RTM_EXAMPLE_SHAREDLIB_DIR}
			COMPONENT examples)


if(VXWORKS)
	if(RTP)
		set_target_properties(${target} PROPERTIES SUFFIX ".vxe")
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)




set(srcs ConsoleInShort.cpp ConsoleInShort.h)
examples_build(ConsoleInShort SRCS "${srcs}" MAIN ConsoleInShortComp.cpp)


set(srcs ConsoleOutDouble.cpp ConsoleOutDouble.h)
examples_build(ConsoleOutDouble SRCS "${srcs}" MAIN ConsoleOutDoubleComp.cpp)


install(FILES rtc.serializer.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
