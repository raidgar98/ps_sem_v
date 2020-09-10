project(components CXX)
include("${CUSTOM_CMAKE_SCRIPTS_DIR}/create_library.cmake")
include("${CUSTOM_CMAKE_SCRIPTS_DIR}/attach_package.cmake")

# Boost
attach_boost(thread)

# SFML
attach_sfml()

create_library( geometry_visitor paint_config visitor point )
create_library( paint_visitor

	${Boost_THREAD_LIBRARY}

	paint_config
	geometry_visitor

	ship
	area
	player

)

create_library( click_visitor geometry_visitor ship area player )