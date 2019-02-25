cmake_minimum_required (VERSION 3.0.2)


set(srcs SeqIn.cpp SeqIn.h)
ComponentBuild(SeqIn "${srcs}" SeqInComp.cpp "" "")


set(srcs SeqOut.cpp SeqOut.h)
ComponentBuild(SeqOut "${srcs}" SeqOutComp.cpp "" "")
