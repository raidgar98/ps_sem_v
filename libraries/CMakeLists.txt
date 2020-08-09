# project(libraries)
# cmake_minimum_required(3.16)

add_library(types 

	dummy.cpp

)

MACRO(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	FOREACH(child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()
	SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${MY_CURRENT_DIR})

foreach(subdir ${SUBDIRS})
	add_subdirectory(subdir)
endforeach(subdir ${SUBDIRS})
