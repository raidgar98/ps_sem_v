include("${CUSTOM_CMAKE_SCRIPTS_DIR}/create_library.cmake")
include("${CUSTOM_CMAKE_SCRIPTS_DIR}/attach_package.cmake")

attach_boost(thread)

create_library(network_actions singleton ${Boost_THREAD_LIBRARY} cpprest)
create_library(network network_actions logger )