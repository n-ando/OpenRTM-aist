cmake_minimum_required (VERSION 3.0.2)
set(target ConfigSample)
project (${target}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


set(srcs ConfigSample.cpp ConfigSample.h)
ComponentBuild(ConfigSample "${srcs}" ConfigSampleComp.cpp "" "")


install(FILES configsample.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
