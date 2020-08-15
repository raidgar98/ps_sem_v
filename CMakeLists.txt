# minimum cmake version
cmake_minimum_required(VERSION 3.16)

# project name and language
project("Programowanie Systemowe Semestr 5" CXX)

# prevent build in source
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, remove CMakeFiles and CMakeCache.txt")
endif()

# use c++17 standard
set(CMAKE_CXX_STANDARD 17)

# all warnings treat as errors
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

# set binary name
set(EXECUTABLE_NAME main)

# start processing libraries
add_subdirectory(libraries)

# start processing tests
add_subdirectory(test)

# add executable
add_executable( ${EXECUTABLE_NAME} main.cpp )

# setup SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
set(
	SFML_LIBRARIES_TO_LINK
	sfml-graphics
	sfml-audio
	sfml-window
	sfml-system
)

# link required libraries to main program
target_link_libraries( ${EXECUTABLE_NAME}

	${SFML_LIBRARIES_TO_LINK}

	point
)

