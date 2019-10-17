cmake_minimum_required (VERSION 3.5.1)

find_package(Boost COMPONENTS filesystem)
if(Boost_FOUND)
	add_subdirectory(nameservice_file)
endif(Boost_FOUND)
