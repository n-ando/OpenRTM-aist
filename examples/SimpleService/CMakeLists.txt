cmake_minimum_required (VERSION 3.0.2)

project (SimpleService
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(${PROJECT_NAME}_IDLS MyService.idl)

openrtm_idl_compile_all(MyService
	"${${PROJECT_NAME}_IDLS}"
	"-I${CMAKE_CURRENT_SOURCE_DIR};-I${CMAKE_SOURCE_DIR}/src/lib/rtm/idl")

examples_build(MyServiceConsumer
	SRCS MyServiceConsumer.cpp
	GENSRCS ${MyService_IDLSTUB}
	MAIN MyServiceConsumerComp.cpp
	INCLUDE ${CMAKE_CURRENT_BINARY_DIR}
	DEPS MyService_IDLTGT)

examples_build(MyServiceProvider
	SRCS MyServiceProvider.cpp MyServiceSVC_impl.cpp
	GENSRCS ${MyService_IDLSKEL}
	MAIN MyServiceProviderComp.cpp
	INCLUDE ${CMAKE_CURRENT_BINARY_DIR}
	DEPS MyService_IDLTGT)
