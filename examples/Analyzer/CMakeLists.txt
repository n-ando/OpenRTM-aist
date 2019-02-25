cmake_minimum_required (VERSION 3.0.2)

project (Analyzer
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)


set(srcs Analyzer.cpp Analyzer.h)
ComponentBuild(Analyzer "${srcs}" AnalyzerComp.cpp "" "")



set(srcs Analyzer_test.cpp Analyzer_test.h)
ComponentBuild(Analyzer_test "${srcs}" Analyzer_testComp.cpp "" "")
