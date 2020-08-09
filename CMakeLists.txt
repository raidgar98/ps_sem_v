project("Programowanie Systemowe Semestr 5" CXX)
set(CMAKE_BUILD_TYPE Release)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_NAME main)
# set(SFML_STATIC_LIBRARIES TRUE)
# set(SFML_STATIC_STD_LIB)
# set(SFML_USE_STATIC_STD_LIBS)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --static")
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_executable( ${EXECUTABLE_NAME} main.cpp )

# setup SFML
# find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
set(
	SFML_LIBRARIES_TO_LINK
	sfml-graphics
	sfml-audio
	sfml-window
	sfml-system
)
# if(SFML_FOUND)
# 	include_directories(${SFML_INCLUDE_DIR})
# 	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
# endif()

# include_directories(libraries)

target_link_libraries( ${EXECUTABLE_NAME}
	${SFML_LIBRARIES_TO_LINK}
)

# include_directories(test)