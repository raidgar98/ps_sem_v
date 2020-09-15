cmake_minimum_required(VERSION 3.1)
include( "${CUSTOM_CMAKE_SCRIPTS_DIR}/get_all_directories.cmake" )

add_library(types 
	dummy.cpp
)

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(cpprestsdk/Release/include)

foreach(ss ${SUBDIRS})
	add_subdirectory(${ss})
endforeach()
