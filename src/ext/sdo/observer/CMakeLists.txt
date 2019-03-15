cmake_minimum_required (VERSION 3.0.2)

project (ComponentObserverConsumer
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(${PROJECT_NAME}_IDLS ComponentObserver.idl)
set(${PROJECT_NAME}_SRCS ${PROJECT_NAME}.cpp)

openrtm_idl_compile_all(${PROJECT_NAME}
	"${${PROJECT_NAME}_IDLS}"
	"-I${CMAKE_CURRENT_SOURCE_DIR};-I${CMAKE_SOURCE_DIR}/src/lib/rtm/idl")

include_directories(${RTM_INCLUDE_DIR})
include_directories(SYSTEM
	${RTM_INCLUDE_GENDIR}
	${ORB_INCLUDE_DIR}
	${PROJECT_BINARY_DIR})

add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})

add_library(${PROJECT_NAME}_objlib OBJECT ${${PROJECT_NAME}_SRCS})
openrtm_common_set_compile_props(${PROJECT_NAME}_objlib)
add_dependencies(${PROJECT_NAME}_objlib ${PROJECT_NAME}_IDLTGT)
add_dependencies(${PROJECT_NAME}_objlib ${RTCSKEL_PROJECT_NAME}_IDLTGT)

add_library(${PROJECT_NAME}_idl_objlib OBJECT ${${PROJECT_NAME}_IDLSTUB})
openrtm_gencode_set_compile_props(${PROJECT_NAME}_idl_objlib)
add_dependencies(${PROJECT_NAME}_idl_objlib ${PROJECT_NAME}_IDLTGT)
add_dependencies(${PROJECT_NAME}_idl_objlib ${RTCSKEL_PROJECT_NAME}_IDLTGT)
add_library(${PROJECT_NAME} SHARED
	$<TARGET_OBJECTS:${PROJECT_NAME}_objlib>
	$<TARGET_OBJECTS:${PROJECT_NAME}_idl_objlib>)
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs} ${RTM_LINKER_OPTION})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

install(FILES ${${PROJECT_NAME}_IDLS} DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo/observer COMPONENT idl)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/sdo
			COMPONENT ext)
