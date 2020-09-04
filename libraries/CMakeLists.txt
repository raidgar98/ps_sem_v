# project(libraries)
# cmake_minimum_required(3.16)

find_package(Boost 1.70 REQUIRED COMPONENTS filesystem date_time stacktrace_backtrace stacktrace_addr2line stacktrace_noop stacktrace_basic)

add_library(types 
	dummy.cpp
)

target_include_directories(types PRIVATE include ${BOOST_INCLUDE_DIRS} )
target_link_libraries(types ${Boost_LIBRARIES} )

MACRO(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	FOREACH(child ${children})
		IF(IS_DIRECTORY ${curdir}/${child} AND EXISTS ${curdir}/${child}/CMakeLists.txt)
			LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()
	SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(ss ${SUBDIRS})
	message(${ss})
	add_subdirectory(${ss})
endforeach()
