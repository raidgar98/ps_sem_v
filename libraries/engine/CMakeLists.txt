project(engine)
include("${CUSTOM_CMAKE_SCRIPTS_DIR}/create_library.cmake")

create_library(round_manager types)
create_library(point types)
create_library(ship point logger visitor)
create_library(area ship)
create_library(player area)
create_library(engine network_actions)
