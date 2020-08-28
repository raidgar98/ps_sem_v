project(engine)

MACRO(create_library libname)
	add_library(${libname} STATIC src/${libname}.cpp)
	target_include_directories( ${libname} PUBLIC include )
	# target_sources(${liname} PUBLIC src/${libname}.cpp)

	set(variadic ${ARGN})
	list(LENGTH variadic var_length)

	if(var_length GREATER 0)
		target_link_libraries( ${libname} ${variadic} )
	endif()

ENDMACRO()

create_library(round_manager types)
create_library(point types)
create_library(ship point logger visitor)
create_library(area ship)
create_library(engine area)
