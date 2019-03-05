cmake_minimum_required (VERSION 3.0.2)
set(target HelloRTWorld)
project (${target}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


set(srcs HelloRTWorld.cpp HelloRTWorld.h)
ComponentBuild(HelloRTWorld "${srcs}" HelloRTWorldComp.cpp "" "")
