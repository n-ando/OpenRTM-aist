# Find omniORB
#
# Adapted from the Orocos project's FindOmniORB.cmake

# Variables that will be set
# OMNIORB4_FOUND        - TRUE when omniORB was found
# OMNIORB4_INCLUDE_DIR  - Directories to include to use omniORB
# OMNIORB4_LIBRARIES    - Files to link against to use omniORB
# OMNIORB4_IDL_COMPILER - Path to the omniidl executable
#
# Variables that may be set by the user
# OMNIORB4_DIR          - (optional) Suggested installation directory to search
#
# OMNIORB4_DIR can be used to make it simpler to find the various include
# directories and compiled libraries when omniORB was not installed in the
# usual/well-known directories (e.g. because you made an in tree-source
# compilation or because you installed it in an "unusual" directory).
# Just set OMNIORB4_DIR it to your specific installation directory
#

find_path (OMNIORB4_INCLUDE_DIR omniORB4/CORBA.h
    PATHS ${OMNIORB4_DIR}/include /usr/include /usr/local/include)

# For the list of required libraries for omniORB see
# http://www.omniorb-support.com/pipermail/omniorb-list/2005-May/026666.html
# Basically, look at
#  - omniORB-4.0.5/README.*
#  - omniORB-4.0.5/readmes/*
# Platfrom dependencies might (only?) happen for Win32/VC++ (sigh):
# "Because of a bug in VC++, unless you require the dynamic interfaces, it
#  is suggested that you use a smaller stub library called msvcstub.lib."

set (OMNIORB4_DEFAULT_LIB_PATH /usr/lib /usr/local/lib)

if (WIN32)
	set (OMNIORB4_LIB_DIR_WIN32 ${OMNIORB4_DIR}/lib/x86_win32)
	set (OMNIORB4_BIN_DIR_WIN32 ${OMNIORB4_DIR}/bin/x86_win32)
	if (BUILD_SHARED_LIBS)
		set (OMNIORB4_LIB_EXT 12_rt)
		set (OMNITHREAD_LIB_EXT 33_rt)
	endif (BUILD_SHARED_LIBS)
endif (WIN32)

find_library (OMNIORB4_LIBRARY_omniORB4 omniORB4${OMNIORB4_LIB_EXT}
	PATHS ${OMNIORB4_DIR}/lib
	${OMNIORB4_LIB_DIR_WIN32}
	${OMNIORB4_DEFAULT_LIB_PATH})

find_library (OMNIORB4_LIBRARY_omnithread omnithread${OMNITHREAD_LIB_EXT}
	PATHS ${OMNIORB4_DIR}/lib
	${OMNIORB4_LIB_DIR_WIN32}
	${OMNIORB4_DEFAULT_LIB_PATH})

find_library (OMNIORB4_LIBRARY_COS4 COS4${OMNIORB4_LIB_EXT}
	PATHS ${OMNIORB4_DIR}/lib
	${OMNIORB4_LIB_DIR_WIN32}
	${OMNIORB4_DEFAULT_LIB_PATH})

find_library (OMNIORB4_LIBRARY_COSDynamic4 COSDynamic4${OMNIORB4_LIB_EXT}
	PATHS ${OMNIORB4_DIR}/lib
	${OMNIORB4_LIB_DIR_WIN32}
	${OMNIORB4_DEFAULT_LIB_PATH})

find_library (OMNIORB4_LIBRARY_Dynamic4 omniDynamic4${OMNIORB4_LIB_EXT}
	PATHS ${OMNIORB4_DIR}/lib
	${OMNIORB4_LIB_DIR_WIN32}
	${OMNIORB4_DEFAULT_LIB_PATH})

find_program (OMNIORB4_IDL_COMPILER
	NAMES omniidl PATHS ${OMNIORB4_DIR}/bin ${OMNIORB4_BIN_DIR_WIN32}
	/usr/bin /usr/local/bin
	DOC "The path to omniidl")

if (OMNIORB4_INCLUDE_DIR AND OMNIORB4_LIBRARY_omniORB4 AND OMNIORB4_LIBRARY_omnithread AND OMNIORB4_IDL_COMPILER)
	set (OMNIORB4_FOUND TRUE)

	mark_as_advanced (OMNIORB4_LIBRARY_omniORB4)
	mark_as_advanced (OMNIORB4_LIBRARY_omnithread)
	mark_as_advanced (OMNIORB4_LIBRARY_COS4)
	mark_as_advanced (OMNIORB4_LIBRARY_COSDynamic4)
	mark_as_advanced (OMNIORB4_LIBRARY_Dynamic4)
	list (APPEND OMNIORB4_LIBRARIES
		${OMNIORB4_LIBRARY_omniORB4}
		${OMNIORB4_LIBRARY_Dynamic4}
		${OMNIORB4_LIBRARY_omnithread})
	if (OMNIORB4_LIBRARY_COS4)
		list (APPEND OMNIORB4_LIBRARIES
			${OMNIORB4_LIBRARY_COS4}            # mandatory on FC2 and graal
			${OMNIORB4_LIBRARY_COSDynamic4})    # mandatory on FC2 and graal
	endif (OMNIORB4_LIBRARY_COS4)
endif (OMNIORB4_INCLUDE_DIR AND OMNIORB4_LIBRARY_omniORB4 AND OMNIORB4_LIBRARY_omnithread AND OMNIORB4_IDL_COMPILER)

if (NOT OMNIORB4_FOUND)
	set (OMNIORB4_DIR "" CACHE PATH "Root of the omniORB install tree.")
endif (OMNIORB4_FOUND)

