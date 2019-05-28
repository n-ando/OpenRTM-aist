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


if(NOT VX_VERSION)
	SET (VX_VERSION     vxworks-6.9)
endif()

if("${VX_VERSION}" STREQUAL "vxworks-6.9")
	SET (GNU_VERSION 4.3.3)
	SET (VXWORKS_VERSION_FLAG -DVXWORKS_69)
	SET (WIND_UTIL_PATH ${WIND_HOME}/utilities-1.0/x86-linux2/bin)
	SET (VXWORKS_MAJOR 6)
	SET (VXWORKS_MINOR 9)
else()
	SET (GNU_VERSION 4.1.2)	
	SET (VXWORKS_VERSION_FLAG -DVXWORKS_66)
	SET (WIND_UTIL_PATH ${WIND_HOME}/workbench-3.0/x86-linux2/bin)
	SET (VXWORKS_MAJOR 6)
	SET (VXWORKS_MINOR 6)
endif()



# Path Settings
SET (WIND_BASE ${WIND_HOME}/${VX_VERSION})
SET (WIND_GNU_BASE ${WIND_HOME}/gnu/${GNU_VERSION}-${VX_VERSION}/${WIND_HOST_TYPE})
SET (VX_VW_BASE ${WIND_BASE}/target)

# environment variables required by compiler
SET (WIND_ENV "WIND_HOME=${WIND_HOME} WIND_HOST_TYPE=${WIND_HOST_TYPE} WIND_BASE=${WIND_BASE}")

################################################################################

SET (VXWORKS ON)


SET (CMAKE_SYSTEM_NAME VxWorks)
SET (CMAKE_SYSTEM_VERSION ${VX_VERSION})
SET (CMAKE_SYSTEM_PROCESSOR ${VX_CPU_FAMILY})

INCLUDE (CMakeForceCompiler)

if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccppc GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++ppc GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldppc CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arppc CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_UTIL_PATH}/nmppc CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_UTIL_PATH}/stripppc CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_UTIL_PATH}/objcopyppc CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_UTIL_PATH}/objdumpppc CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibppc CACHE FILEPATH "vxworks ranlib")
	SET (CPU_TYPE powerpc)
elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccpentium GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++pentium GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldpentium CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arpentium CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_UTIL_PATH}/nmpentium CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_UTIL_PATH}/strippentium CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_UTIL_PATH}/objcopypentium CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_UTIL_PATH}/objdumppentium CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibpentium CACHE FILEPATH "vxworks ranlib")
	SET (CPU_TYPE simpentium)
elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")
	CMAKE_FORCE_C_COMPILER(${WIND_GNU_BASE}/bin/ccpentium GNU)
	CMAKE_FORCE_CXX_COMPILER(${WIND_GNU_BASE}/bin/c++pentium GNU)
	SET (CMAKE_LINKER ${WIND_GNU_BASE}/bin/ldpentium CACHE FILEPATH "vxworks linker")
	SET (CMAKE_AR ${WIND_GNU_BASE}/bin/arpentium CACHE FILEPATH "vxworks ar")
	SET (CMAKE_NM ${WIND_UTIL_PATH}/nmpentium CACHE FILEPATH "vxworks nm")
	SET (CMAKE_STRIP ${WIND_UTIL_PATH}/strippentium CACHE FILEPATH "vxworks strip")
	SET (CMAKE_OBJCOPY ${WIND_UTIL_PATH}/objcopypentium CACHE FILEPATH "vxworks objcopy")
	SET (CMAKE_OBJDUMP ${WIND_UTIL_PATH}/objdumppentium CACHE FILEPATH "vxworks objdump")
	SET (CMAKE_RANLIB ${WIND_GNU_BASE}/bin/ranlibpentium CACHE FILEPATH "vxworks ranlib")
	SET (CPU_TYPE simlinux)
endif()




SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
SET (CMAKE_EXE_LINKER_FLAGS_INIT -r)


SET (VSB_DIR ${WIND_BASE}/target/lib)
SET (VSB_CONFIG_FILE ${VSB_DIR}/h/config/vsbConfig.h)



FIND_PROGRAM (SH sh REQUIRED)





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

	SET (CC_ARCH_SPEC "-fno-implicit-fp -mstrict-align")
	SET (NM_FLAG ppc)

elseif("${VX_CPU_FAMILY}" STREQUAL "simpentium")

	SET (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2  -fno-defer-pop"  CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELEASE "-O2  -fno-defer-pop" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

	SET (CC_ARCH_SPEC "-mtune=i486 -march=i486")
	SET (NM_FLAG pentium)


elseif("${VX_CPU_FAMILY}" STREQUAL "simlinux")

	SET (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2  -fno-defer-pop"  CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "")

	SET (CMAKE_C_FLAGS_RELEASE "-O2  -fno-defer-pop" CACHE STRING "")
	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} CACHE STRING "")

	SET (CC_ARCH_SPEC "-mtune=i486 -march=i486")
	SET (NM_FLAG pentium)

endif()

if(RTP)
	#set(CMAKE_EXE_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -fno-strict-aliasing -fasm -Wall" )
	set(CMAKE_EXE_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -Xbind-lazy -non-static -fno-strict-aliasing -lstdc++ -fasm -D_WRS_HARDWARE_FP -Wall" )
	set(CMAKE_SHARED_LINKER_FLAGS "${CC_ARCH_SPEC} ${RTP_C_FLAGS} -D__SO_PICABIRTP__ -D__SO64_LARGE__ -shared -lstdc++ -fasm" )
else(RTP)
	if("${VX_VERSION}" STREQUAL "vxworks-6.9")
		set(CMAKE_PARTICALIMAGE_LINKER_FLAGS "-nostdlib -Wl,-X " )
		set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -Wl,-X -T ${WIND_BASE}/target/h/tool/gnu/ldscripts/link.OUT " )
	endif()
endif()


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
#message(STATUS ${VX_VW_BASE}/h/wrn/coreip)
endif()









SET (VXWORKS_C_FLAGS_LIST
  -DCPU=${VX_CPU}  -DVX_CPU_CARD=${VX_CPU_CARD} -DTOOL_FAMILY=${VX_TOOL_FAMILY} -DTOOL=${VX_TOOL} -DCPU_VARIANT=${VX_CPU_VARIANT} -DVXWORKS_MAJOR=${VXWORKS_MAJOR} -DVXWORKS_MINOR=${VXWORKS_MINOR} -DVXWORKS ${VXWORKS_VERSION_FLAG} -D__OSVERSION__=${VXWORKS_MAJOR}${VXWORKS_MINOR} )


#  -D_VX_CPU=_VX_${VX_CPU}
#  -D_VX_CPU_FAMILY=_VX_${VX_CPU}
#  -D_VX_TOOL_FAMILY=${VX_TOOL_FAMILY}
#  -D_VX_TOOL=${VX_TOOL}
#  -DCPU_FAMILY=_${CPU_FAMILY}
#  -D_VSB_CONFIG_FILE="${VSB_CONFIG_FILE}"
#  -D_WRS_KERNEL
#  ${CC_ARCH_SPEC}
#  -ansi
#  -mrtp

if(RTP)
	ADD_DEFINITIONS (${VXWORKS_C_FLAGS_LIST} -Xbind-lazy -non-static)
else(RTP)
	ADD_DEFINITIONS (${VXWORKS_C_FLAGS_LIST})
endif(RTP)







if("${VX_CPU_FAMILY}" STREQUAL "ppc")
	if(RTP)
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
	else(RTP)
		SET (CPU_C_FLAGS_LIST
		  ${RTP_C_FLAGS}
		  -D_WRS_KERNEL
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
	  -D_WRS_KERNEL
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


if(RTP)
	SET (CMAKE_C_LINK_EXECUTABLE
		  "${CMAKE_C_COMPILER} ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
	SET (CMAKE_C_CREATE_SHARED_LIBRARY
		  "${CMAKE_C_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
	SET (CMAKE_CXX_LINK_EXECUTABLE
		  "${CMAKE_CXX_COMPILER} ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
	SET (CMAKE_CXX_CREATE_SHARED_LIBRARY
		  "${CMAKE_CXX_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
else(RTP)
	if("${VX_VERSION}" STREQUAL "vxworks-6.9")
		SET (MUNCH ${WIND_BASE}/host/resource/hutils/tcl/munch.tcl CACHE FILEPATH "munch")
		SET (TCLSH ${WIND_HOME}/workbench-3.3/foundation/x86-linux2/bin/tclsh CACHE FILEPATH "tclsh")
		SET (TAGS ${VSB_DIR}/tags/${VX_CPU_FAMILY}/${VX_CPU}/common/dkm.tags CACHE FILEPATH "tags")
		string(REPLACE ";" " " VXWORKS_C_FLAGS_LIST_STR "${VXWORKS_C_FLAGS_LIST}")
		SET (RUN_MUNCH_SCRIPT ${CMAKE_SOURCE_DIR}/build/cmake/run_munch_69.sh)
		SET (CMAKE_C_LINK_EXECUTABLE
		  "${CMAKE_C_COMPILER} ${CMAKE_PARTICALIMAGE_LINKER_FLAGS} -o <TARGET>_partialImage.o <OBJECTS> <LINK_LIBRARIES>"
		  "sh ${RUN_MUNCH_SCRIPT} ${CMAKE_NM} <TARGET>_partialImage.o ${TCLSH} ${MUNCH} ${NM_FLAG} ${TAGS} ctdt.c"
		  "${CMAKE_C_COMPILER} ${CC_ARCH_SPEC} -nostdlib -fno-builtin  -fdollars-in-identifiers -Wall ${VXWORKS_C_FLAGS_LIST_STR} -o ctdt.o -c ctdt.c"
		  "${CMAKE_C_COMPILER} ${CMAKE_EXE_LINKER_FLAGS} -o <TARGET>  <TARGET>_partialImage.o ctdt.o <LINK_LIBRARIES> -lstdc++"
		)
		SET (CMAKE_CXX_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})
	else()
#		SET (TCLSH ${WIND_HOME}/workbench-3.0/foundation/4.1.1/x86-linux2/bin/tclsh CACHE FILEPATH "tclsh")
		SET (MUNCH ${WIND_BASE}/host/${WIND_HOST_TYPE}/bin/munch CACHE FILEPATH "munch")
		string(REPLACE ";" " " VXWORKS_C_FLAGS_LIST_STR "${VXWORKS_C_FLAGS_LIST};${CPU_C_FLAGS_LIST}")
		SET (RUN_MUNCH_SCRIPT ${CMAKE_SOURCE_DIR}/build/cmake/run_munch.sh)
		SET (CMAKE_C_LINK_EXECUTABLE
		  "${CMAKE_LINKER}  <LINK_FLAGS> <CMAKE_CXX_LINK_FLAGS> -warn-common -S <OBJECTS> -o <TARGET>_partialImage.o  <LINK_LIBRARIES>"
		  "sh ${RUN_MUNCH_SCRIPT} ${CMAKE_NM} <TARGET>_partialImage.o ${MUNCH} ctdt.c"
		  "${CMAKE_C_COMPILER} ${VXWORKS_C_FLAGS_LIST_STR} -o ctdt.o -c ctdt.c"
		  "${CMAKE_LINKER} <LINK_FLAGS> <CMAKE_CXX_LINK_FLAGS> -S -warn-common -o <TARGET> <TARGET>_partialImage.o ctdt.o "
		)
	endif()
	

	SET (CMAKE_CXX_LINK_EXECUTABLE ${CMAKE_C_LINK_EXECUTABLE})
endif(RTP)



MARK_AS_ADVANCED (CMAKE_LINKER CMAKE_AR CMAKE_NM CMAKE_STRIP
  CMAKE_OBJCOPY CMAKE_OBJDUMP CMAKE_RANLIB CMAKE_C_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELEASE SH MUNCH)
