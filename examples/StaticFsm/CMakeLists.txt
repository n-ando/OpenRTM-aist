cmake_minimum_required (VERSION 3.0.2)

project (StaticFSM
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)



set(srcs Display.cpp Display.h)
ComponentBuild(Display "${srcs}" DisplayComp.cpp "" "")

set(srcs Inputbutton.cpp Inputbutton.h)
ComponentBuild(Inputbutton "${srcs}" InputbuttonComp.cpp "" "")

set(srcs Microwave.cpp Microwave.h MicrowaveFsm.cpp MicrowaveFsm.h)
ComponentBuild(Microwave "${srcs}" MicrowaveComp.cpp "" ${CMAKE_SOURCE_DIR}/src/lib/rtm/Macho.cpp)