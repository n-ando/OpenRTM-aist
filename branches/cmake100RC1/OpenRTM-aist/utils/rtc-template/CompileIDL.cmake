include (MakeOrbSourceNames)

###############################################################################
# Compile an IDL file using an IDL compiler based on the ORB setting.
#
# _idlFile:     Input IDL file
# _sourceFiles: Variable to store created source files in
# _headerFiles: Variable to store created header files in
# _orb:         ORB to compile with
macro (COMPILE_IDL _idlFile _sourceFiles _headerFiles)
    MAKE_SOURCE_NAMES (${_sourceFiles} ${_headerFiles} ${_idlFile})
    add_custom_command (OUTPUT ${${_sourceFiles}} ${${_headerFiles}}
        COMMAND ${IDLC} ${IDL_FLAGS} -I${RTM_PREFIX}/include/rtm/idl ${CMAKE_CURRENT_SOURCE_DIR}/${_idlFile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${_idlFile}
        VERBATIM)
endmacro (COMPILE_IDL)


###############################################################################
# Wrap an IDL file's output
#
# _idlFile:     Input IDL file
macro (WRAP_SOURCES _idlFile)
    include (FindPythonInterp)
    if (NOT PYTHONINTERP_FOUND)
        message (FATAL_ERROR "No Python interpreter found. Cannot continue.")
    endif (NOT PYTHONINTERP_FOUND)

    get_filename_component (_idlName ${_idlFile} NAME_WE)
    set (_skelCpp "${CMAKE_CURRENT_BINARY_DIR}/${_idlName}Skel.cpp")
    set (_stubCpp "${CMAKE_CURRENT_BINARY_DIR}/${_idlName}Stub.cpp")

    add_custom_command (OUTPUT ${_skelCpp} ${_stubCpp}
        COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/build/makewrapper.py ${CMAKE_CURRENT_SOURCE_DIR}/${_idlFile} ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${ARGN}
        VERBATIM)
endmacro (WRAP_SOURCES)
