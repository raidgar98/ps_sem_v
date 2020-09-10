cmake_minimum_required(VERSION 3.1)

MACRO(attach_sfml)
	find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

	set(variadic ${ARGN})
	set(
		SFML_LIBRARIES_TO_LINK
		sfml-graphics
		sfml-audio
		sfml-window
		sfml-system
		${variadic}
	)

ENDMACRO()

MACRO(attach_boost)

	set(variadic ${ARGN})
	find_package(Boost 1.70 REQUIRED COMPONENTS ${variadic} )

ENDMACRO()