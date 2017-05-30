# VxWorks 6.6 settings
#
# for J3 Main ECU
#
SET (VX_TOOL_FAMILY gnu)
SET (VX_TOOL        sfgnu)


set(RTP ${RTP} CACHE BOOL "set RTP")

if(RTP)
	set(RTP_C_FLAGS -mrtp)
endif()



set(VX_CPU_FAMILY ${VX_CPU_FAMILY} CACHE STRING "set VX_CPU_FAMILY ")

if(NOT VX_CPU_FAMILY)
	set(VX_CPU_FAMILY ppc)
endif()

if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	SET (VX_CPU PPC32)
elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
	SET (VX_CPU SIMPENTIUM)
elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
	SET (VX_CPU SIMLINUX)
endif()




#message(STATUS "test")
#message(STATUS ${VX_CPU_FAMILY})

#SET (VX_CPU_FAMILY  ppc)
#SET (VX_CPU         PPC32)
SET (VX_CPU_CARD    ADS8572)
SET (VX_CPU_VARIANT _ppc85XX_e500v2)


if(NOT VX_VERSION)
	SET (VX_VERSION     vxworks-6.9)
endif()

if("${VX_VERSION}" STREQUAL "vxworks-6.9")
	SET (GNU_VERSION 4.3.3)
	ADD_DEFINITIONS (-DVXWORKS_69)
else()
	SET (GNU_VERSION 4.1.2)	
	ADD_DEFINITIONS (-DVXWORKS_66)
endif()

# ホストOSの判定
FIND_PROGRAM (UNAME uname)
MARK_AS_ADVANCED (UNAME)
EXECUTE_PROCESS (COMMAND ${UNAME} OUTPUT_VARIABLE VXWORKS_HOST_OS)

IF (VXWORKS_HOST_OS MATCHES "SunOS")
  SET (WIND_HOST_TYPE sun4-solaris2)
  SET (WIND_HOME /usr/local/vw/workbench3.0)
ELSEIF (VXWORKS_HOST_OS MATCHES "Linux")
  SET (WIND_HOST_TYPE x86-linux2)
  IF (NOT EXISTS "$ENV{WIND_HOME}")
    MESSAGE (STATUS "WIND_HOME=$ENV{WIND_HOME}")
    MESSAGE (FATAL_ERROR "Please provide valid WIND_HOME environment variable.")
  ENDIF (NOT EXISTS "$ENV{WIND_HOME}")
  SET (WIND_HOME "$ENV{WIND_HOME}")
ENDIF (VXWORKS_HOST_OS MATCHES "SunOS")

# Path Settings
SET (WIND_BASE ${WIND_HOME}/${VX_VERSION})
SET (WIND_GNU_BASE ${WIND_HOME}/gnu/${GNU_VERSION}-${VX_VERSION}/${WIND_HOST_TYPE})
SET (VX_VW_BASE ${WIND_BASE}/target)

# environment variables required by compiler
SET (WIND_ENV "WIND_HOME=${WIND_HOME} WIND_HOST_TYPE=${WIND_HOST_TYPE} WIND_BASE=${WIND_BASE}")

################################################################################

SET (VXWORKS ON)
SET (VXWORKS_MAJOR 6)
SET (VXWORKS_MINOR 6)

SET (CMAKE_SYSTEM_NAME VxWorks)
SET (CMAKE_SYSTEM_VERSION ${VX_VERSION})
SET (CMAKE_SYSTEM_PROCESSOR ${VX_CPU_FAMILY})

INCLUDE (CMakeForceCompiler)

if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccppc GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++ppc GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldppc CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arppc CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_GNU_BASE}/bin/nmppc CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_GNU_BASE}/bin/stripppc CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_GNU_BASE}/bin/objcopyppc CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_GNU_BASE}/bin/objdumpppc CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibppc CACHE FILEPATH "vxworks ranlib")
elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccpentium GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++pentium GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldpentium CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arpentium CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_GNU_BASE}/bin/nmpentium CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_GNU_BASE}/bin/strippentium CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_GNU_BASE}/bin/objcopypentium CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_GNU_BASE}/bin/objdumppentium CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibpentium CACHE FILEPATH "vxworks ranlib")
elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccpentium GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++pentium GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldpentium CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arpentium CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_GNU_BASE}/bin/nmpentium CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_GNU_BASE}/bin/strippentium CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_GNU_BASE}/bin/objcopypentium CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_GNU_BASE}/bin/objdumppentium CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibpentium CACHE FILEPATH "vxworks ranlib")
endif()



SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
SET (CMAKE_EXE_LINKER_FLAGS_INIT -r)





FIND_PROGRAM (SH sh REQUIRED)
SET (MUNCH ${WIND_BASE}/host/${WIND_HOST_TYPE}/bin/munch CACHE FILEPATH "munch")

SET (CMAKE_C_COMPILE_OBJECT
  "${WIND_ENV} <CMAKE_C_COMPILER> <DEFINES> <FLAGS> -o <OBJECT> -c <SOURCE>")
SET (CMAKE_CXX_COMPILE_OBJECT
  "${WIND_ENV} <CMAKE_CXX_COMPILER> <DEFINES> <FLAGS> -o <OBJECT> -c <SOURCE>")


#set(LINKER_FLAGS "-mhard-float -fno-implicit-fp -mstrict-align -mregnames -D_WRS_HARDWARE_FP -mrtp -fno-strict-aliasing -fasm -Wall" )


#set(LINKER_FLAGS "-mhard-float -fno-implicit-fp -mstrict-align -mregnames -fno-strict-aliasing -fasm -Wall" )

if("${VX_CPU_FAMILY}" STREQUAL "ppc")


	SET (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2  -fstrength-reduce -fno-builtin"  CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELEASE "-O2  -fstrength-reduce -fno-builtin" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

	SET (CC_ARCH_SPEC "-mhard-float -fno-implicit-fp -mstrict-align -mregnames -D_WRS_HARDWARE_FP")

elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")

	SET (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2  -fno-defer-pop"  CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELEASE "-O2  -fno-defer-pop" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

	SET (CC_ARCH_SPEC "-mtune=i486 -march=i486")


elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")

	SET (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2  -fno-defer-pop"  CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELEASE "-O2  -fno-defer-pop" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

	SET (CC_ARCH_SPEC "-mtune=i486 -march=i486")

endif()

if(RTP)
	#set(CMAKE_EXE_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -fno-strict-aliasing -fasm -Wall" )
	set(CMAKE_EXE_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -fno-strict-aliasing -lstdc++ -fasm -D_WRS_HARDWARE_FP -Wall" )
else(RTP)
	set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -Wl,-X -T ${WIND_BASE}/target/h/tool/gnu/ldscripts/link.OUT " )
endif()


SET (CMAKE_C_LINK_EXECUTABLE
	  "${CMAKE_C_COMPILER} ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
SET (CMAKE_CXX_LINK_EXECUTABLE
	  "${CMAKE_CXX_COMPILER} ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")


#if(RTP)
#	set(CMAKE_EXE_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -fno-strict-aliasing -fasm -Wall" )
#else(RTP)
#	set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -Wl,-X" )
#endif()

#SET (CMAKE_C_FLAGS_DEBUG "-O -g1" CACHE STRING "")
#SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

#SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O -g1 -DNDEBUG"  CACHE STRING "")
#SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

#SET (CMAKE_C_FLAGS_RELEASE "-O -g1 -DNDEBUG" CACHE STRING "")
#SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

if(RTP)
INCLUDE_DIRECTORIES (
  ${VX_VW_BASE}/usr/h
  ${VX_VW_BASE}/usr/h/wrn/coreip)
else(RTP)
INCLUDE_DIRECTORIES (
  ${VX_VW_BASE}/h
  ${VX_VW_BASE}/h/wrn/coreip)
message(STATUS ${VX_VW_BASE}/h/wrn/coreip)
endif()


SET (VSB_DIR ${WIND_BASE}/target/lib)
SET (VSB_CONFIG_FILE ${VSB_DIR}/h/config/vsbConfig.h)






SET (VXWORKS_C_FLAGS_LIST
#  -D_VX_CPU=_VX_${VX_CPU}
#  -D_VX_CPU_FAMILY=_VX_${VX_CPU}
#  -D_VX_TOOL_FAMILY=${VX_TOOL_FAMILY}
#  -D_VX_TOOL=${VX_TOOL}
  -DCPU=${VX_CPU}
  -DVX_CPU_CARD=${VX_CPU_CARD}
#  -DCPU_FAMILY=_${CPU_FAMILY}
  -DTOOL_FAMILY=${VX_TOOL_FAMILY}
  -DTOOL=${VX_TOOL}
  -D_WRS_KERNEL
  -DCPU_VARIANT=${VX_CPU_VARIANT}
#  -D_VSB_CONFIG_FILE="${VSB_CONFIG_FILE}"
  -DVXWORKS_MAJOR=${VXWORKS_MAJOR}
  -DVXWORKS_MINOR=${VXWORKS_MINOR}
  -DVXWORKS
#  ${CC_ARCH_SPEC}
#  -ansi
#  -mrtp
  )


ADD_DEFINITIONS (${VXWORKS_C_FLAGS_LIST})







if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	if(RTP)
		SET (CPU_C_FLAGS_LIST
		  ${RTP_C_FLAGS}
		  -mregnames
		  -msoft-float
		  )
	else(RTP)
		SET (CPU_C_FLAGS_LIST
		  -mlongcall
		  -fstrength-reduce
		  -fno-builtin
		  -te500v2
		  -mcpu=8548
		  -mfloat-gprs=double
		  -mspe=yes
		  -mabi=spe
		  -mstrict-align
		  -fno-implicit-fp
		  ${RTP_C_FLAGS}
		  )
	endif()
elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
	SET (CPU_C_FLAGS_LIST
	  -mtune=i486
	  -march=i486
	  -ansi
	  ${RTP_C_FLAGS}
	  )
elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
	SET (CPU_C_FLAGS_LIST
	  -mtune=i486
	  -march=i486
	  -ansi
	  ${RTP_C_FLAGS}
	  )
endif()

ADD_DEFINITIONS (${CPU_C_FLAGS_LIST})



if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	if(RTP)
		set(COMMON_DIR sfcommon)
	else(RTP)
		set(COMMON_DIR common)
	endif()
elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
	set(COMMON_DIR common)
elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
	set(COMMON_DIR common)
endif()

#link_directories(${WIND_BASE}/target/lib/usr/lib/${VX_CPU_FAMILY}/${CPU}/common)

if(RTP)
	if("${VX_VERSION}" STREQUAL "vxworks-6.9")
		link_directories(${WIND_BASE}/target/lib/usr/lib/${VX_CPU_FAMILY}/${VX_CPU}/${COMMON_DIR})
	else()
		link_directories(${WIND_BASE}/target/usr/lib/${VX_CPU_FAMILY}/${VX_CPU}/${COMMON_DIR})
	endif()
else(RTP)
	link_directories(${WIND_BASE}/target/lib/${VX_CPU_FAMILY}/${VX_CPU}/${COMMON_DIR})
endif()
#link_directories(${WIND_BASE}/target/usr/lib/${VX_CPU_FAMILY}/${VX_CPU}/common)
#link_directories(${WIND_BASE}/target/lib/${VX_CPU_FAMILY}/${VX_CPU}/e500v2common)
#link_directories(${WIND_BASE}/target/usr/lib/simpentium/SIMPENTIUM/common)


MARK_AS_ADVANCED (CMAKE_LINKER CMAKE_AR CMAKE_NM CMAKE_STRIP
  CMAKE_OBJCOPY CMAKE_OBJDUMP CMAKE_RANLIB CMAKE_C_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELEASE SH MUNCH)
