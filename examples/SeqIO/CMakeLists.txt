cmake_minimum_required (VERSION 3.5.1)


set(srcs SeqIn.cpp SeqIn.h)
examples_build(SeqIn SRCS "${srcs}" MAIN SeqInComp.cpp)


set(srcs SeqOut.cpp SeqOut.h)
examples_build(SeqOut SRCS "${srcs}" MAIN SeqOutComp.cpp)
