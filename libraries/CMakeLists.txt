# project(libraries)
# cmake_minimum_required(3.16)

add_library(types 

	dummy.cpp

)

FUNCTION(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	FOREACH(child ${children})
	IF(IS_DIRECTORY ${curdir}/${child} AND EXISTS ${curdir}/${child}/CMakeLists.txt)
		message(${child})
		LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()
	SET(${result} ${dirlist})
ENDFUNCTION()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
	add_subdirectory(${subdir})
endforeach(subdir ${SUBDIRS})
