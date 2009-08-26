###############################################################################
# Create Stub and Skel file names from an IDL file name
macro (GET_SKEL_CPP_NAME _result _idlFile)
    get_filename_component (_nameComp ${_idlFile} NAME_WE)
    set (${_result} ${_nameComp}Skel.cpp)
endmacro (GET_SKEL_CPP_NAME)


macro (GET_SKEL_H_NAME _result _idlFile)
    get_filename_component (_nameComp ${_idlFile} NAME_WE)
    set (${_result} ${_nameComp}Skel.h)
endmacro (GET_SKEL_H_NAME)


macro (GET_STUB_CPP_NAME _result _idlFile)
    get_filename_component (_nameComp ${_idlFile} NAME_WE)
    set (${_result} ${_nameComp}Stub.cpp)
endmacro (GET_STUB_CPP_NAME)


macro (GET_STUB_H_NAME _result _idlFile)
    get_filename_component (_nameComp ${_idlFile} NAME_WE)
    set (${_result} ${_nameComp}Stub.h)
endmacro (GET_STUB_H_NAME)


###############################################################################
# Turn a list of IDL sources into their generated equivalents based on ORB type.
macro (MAKE_SOURCE_NAMES _sourceFiles _headerFiles)
    # Lower the ORB name to avoid case issues
    string (TOLOWER ${ORB} _orbLower)
    if (${_orbLower} STREQUAL "tao")
        MAKE_TAO_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    elseif (${_orbLower} STREQUAL "omniorb")
        MAKE_OMNIORB_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    elseif (${_orbLower} STREQUAL "mico")
        MAKE_MICO_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    elseif (${_orbLower} STREQUAL "orbix")
        MAKE_ORBIX_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    elseif (${_orbLower} STREQUAL "orbacus")
        MAKE_ORBACUS_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    elseif (${_orbLower} STREQUAL "orbit2")
        MAKE_ORBIT_SOURCES (${_sourceFiles} ${_headerFiles} ${ARGN})
    else (${_orbLower} STREQUAL "tao")
        message (FATAL_ERROR "Unknown ORB type, cannot create source names: ${ORB}")
    endif (${_orbLower} STREQUAL "tao")
endmacro (MAKE_SOURCE_NAMES)


# Make a list of TAO-compatible sources
macro (MAKE_TAO_SOURCES _sources _headers)
endmacro (MAKE_TAO_SOURCES)


# Make a list of OmniORB-compatible sources
macro (MAKE_OMNIORB_SOURCES _sources _headers)
    set (${_sources})
    set (${_headers})
    foreach (_idlFile ${ARGN})
        get_filename_component (_idlName ${_idlFile} NAME_WE)
        set (_headerFile ${CMAKE_CURRENT_BINARY_DIR}/${_idlName}.hh)
        set (_skFile ${CMAKE_CURRENT_BINARY_DIR}/${_idlName}SK.cc)
        set (_dynskFile ${CMAKE_CURRENT_BINARY_DIR}/${_idlName}DynSK.cc)
        list (APPEND ${_sources} ${_skFile} ${_dynskFile})
        list (APPEND ${_headers} ${_headerFile})
    endforeach (_idlFile)
endmacro (MAKE_OMNIORB_SOURCES)


# Make a list of MICO-compatible sources
macro (MAKE_MICO_SOURCES _sources _headers)
endmacro (MAKE_MICO_SOURCES)


# Make a list of ORBIX-compatible sources
macro (MAKE_ORBIX_SOURCES _sources _headers)
endmacro (MAKE_ORBIX_SOURCES)


# Make a list of Orbacus-compatible sources
macro (MAKE_ORBACUS_SOURCES _sources _headers)
endmacro (MAKE_ORBACUS_SOURCES)


# Make a list of Orbit2-compatible sources
macro (MAKE_ORBIT_SOURCES _sources _headers)
endmacro (MAKE_ORBIT_SOURCES)
