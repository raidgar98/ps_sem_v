project(engine)

MACRO(create_library libname)
	add_library(${libname} src/${libname})
	target_include_directories( ${libname} PUBLIC include )

	set(variadic ${ARGN})
	list(LENGTH variadic var_length)

	if(var_length GREATER 0)
		target_link_libraries( ${libname} ${variadic} )
	endif()

ENDMACRO()

create_library(point)
create_library(ship point)
create_library(area ship point)
create_library(engine area)
