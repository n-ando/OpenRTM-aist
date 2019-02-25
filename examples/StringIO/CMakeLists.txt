cmake_minimum_required (VERSION 3.0.2)

project (StringIO
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)



set(srcs StringIn.cpp StringIn.h)
ComponentBuild(StringIn "${srcs}" StringInComp.cpp "" "")


set(srcs StringOut.cpp StringOut.h)
ComponentBuild(StringOut "${srcs}" StringOutComp.cpp "" "")
