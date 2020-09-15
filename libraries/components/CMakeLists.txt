include("${CUSTOM_CMAKE_SCRIPTS_DIR}/create_library.cmake")
include("${CUSTOM_CMAKE_SCRIPTS_DIR}/attach_package.cmake")

attach_sfml()

create_library( base_view logger paint_visitor )
create_library( board_view base_view engine ${SFML_LIBRARIES_TO_LINK} click_visitor init_visitor )
