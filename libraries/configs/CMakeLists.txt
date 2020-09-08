project(components CXX)

# SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
set(
	SFML_LIBRARIES_TO_LINK
	sfml-graphics
	sfml-audio
	sfml-window
	sfml-system
)

MACRO(create_library libname)
	add_library(${libname} STATIC src/${libname}.cpp)
	target_include_directories( ${libname} PUBLIC ${BOOST_INCLUDE_DIRS} include )

	set(variadic ${ARGN})
	list(LENGTH variadic var_length)

	if(var_length GREATER 0)
		target_link_libraries( ${libname} ${variadic} )
	endif()

ENDMACRO()

create_library( config types )
create_library( paint_config config ${SFML_LIBRARIES_TO_LINK} )
