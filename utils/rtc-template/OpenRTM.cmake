macro (LIST_TO_STRING _string _list)
    set (${_string})
    foreach (_item ${_list})
        set (${_string} "${${_string}} ${_item}")
    endforeach (_item)
endmacro (LIST_TO_STRING)

if (MSVC)
	set (RTC_VER "100")
	# No pkg-config, so assume that OpenRTM is installed
	# Find the root via the environment
	set (RTM_ROOT ENV{RTM_ROOT})
	if (NOT RTM_ROOT)
		# Not set in the environment, must search for it ourselves
		message (FATAL_ERROR "TODO: search for OpenRTM manually")
	endif (NOT RTM_ROOT)

	find_package (OmniORB4 REQUIRED)

	link_directories (${RTM_ROOT}/bin ${OMNIORB4_LIBRARY_DIR})
	include_directories (${RTM_ROOT} ${RTM_ROOT}/rtm/idl ${OMNIORB4_INCLUDE_DIR})
	set (RTM_CFLAGS "RTC_CORBA_CXXMAPPING11" "_WIN32_WINNT=0x0500")
	set (RTM_LDFLAGS)
	set (RTM_PKG_LIBRARIES RTC${RTC_VER} coil advapi32 ws2_32 mswsock ${OMNIORB4_LIBRARIES})

	set (RTM_PREFIX ${RTM_ROOT})
	set (IDLC ${OMNIORB4_IDL_COMPILER})
	set (IDL_FLAGS -bcxx -Wba -nf)
	set (ORB omniorb)
else (MSVC)
	# Use pkg-config to check that OpenRTM is installed
	include (FindPkgConfig)
	if (NOT PKG_CONFIG_FOUND)
		message (FATAL_ERROR "Could not find pkg-config")
	endif (NOT PKG_CONFIG_FOUND)

	pkg_check_modules (RTM_PKG REQUIRED libRTM)
	link_directories (${RTM_PKG_LIBRARY_DIRS})
	include_directories (${RTM_PKG_INCLUDE_DIRS})
	LIST_TO_STRING (RTM_CFLAGS "${RTM_PKG_CFLAGS_OTHER}")
	LIST_TO_STRING (RTM_LDFLAGS "${RTM_PKG_LDFLAGS_OTHER}")

	# Some other information that we need from pkg-config
	execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=rtm_prefix libRTM
		OUTPUT_VARIABLE RTM_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=rtm_idlc libRTM
		OUTPUT_VARIABLE IDLC OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=rtm_idlflags libRTM
		OUTPUT_VARIABLE IDL_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
	separate_arguments (IDL_FLAGS)
	execute_process (COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=rtm_orb libRTM
		OUTPUT_VARIABLE ORB OUTPUT_STRIP_TRAILING_WHITESPACE)
endif (MSVC)

set (WRAPPER_FLAGS --include-dir= --skel-suffix=Skel --stub-suffix=Stub)

include (CompileIDL)

macro (RUN_WRAPPER _idlFile)
    get_filename_component (_idlName ${_idlFile} NAME_WE)
    set (_skelCpp "${CMAKE_CURRENT_BINARY_DIR}/${_idlName}Skel.cpp")
    set (_stubCpp "${CMAKE_CURRENT_BINARY_DIR}/${_idlName}Stub.cpp")

    add_custom_command (OUTPUT ${_skelCpp} ${_stubCpp}
        COMMAND rtm-skelwrapper ${WRAPPER_FLAGS} --output-dir=${CMAKE_CURRENT_BINARY_DIR} --idl-file=${CMAKE_CURRENT_SOURCE_DIR}/${_idlFile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${ARGN}
        VERBATIM)
endmacro (RUN_WRAPPER)


# Call this macro to generate sources from IDL. _skelSrcs and _stubSrcs will be
# filled with the skeleton and stub source names, respectively.
macro (ADD_IDL _targetName _skelSrcs _stubSrcs)
    set (${_skelSrcs})
    set (${_stubSrcs})
    if ("${ARGC}" GREATER 3)
        set (_allGeneratedSrcs)
        foreach (_idlFile ${ARGN})
            set (_generatedSrcs)
            set (_generatedHdrs)
            COMPILE_IDL (${_idlFile} _generatedSrcs _generatedHdrs)
            RUN_WRAPPER (${_idlFile} ${_generatedSrcs})
            list (APPEND _allGeneratedSrcs ${_generatedSrcs})
            GET_SKEL_CPP_NAME (skelCPP ${_idlFile})
            list (APPEND ${_skelSrcs} ${skelCPP})
            GET_STUB_CPP_NAME (stubCPP ${_idlFile})
            list (APPEND ${_stubSrcs} ${stubCPP})
        endforeach (_idlFile)
        add_custom_target (${_targetName} ALL
            DEPENDS ${_allGeneratedSrcs}
            COMMENT "Compiling IDL files ${ARGN}")
        include_directories (${CMAKE_CURRENT_BINARY_DIR})
    endif ("${ARGC}" GREATER 3)
endmacro (ADD_IDL)
