# minimum cmake version
cmake_minimum_required(VERSION 3.16)

# project name and language
project("Programowanie Systemowe Semestr 5" CXX)

# prevent build in source
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed, remove CMakeFiles and CMakeCache.txt")
endif()

# update submodules
find_program(GIT_PROGRAM git)
if(NOT GIT_PROGRAM)
	message(WARNING "git not found, make sure that submodules are updated")
else()
	message("git found, updating submodules")
	execute_process(COMMAND ${GIT_PROGRAM} submodule update --init --recursive WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )
endif()

# use c++17 standard
set(CMAKE_CXX_STANDARD 17)

# set binary name
set(EXECUTABLE_NAME main)

# start processing libraries
add_subdirectory(libraries)

# start processing tests
add_subdirectory(test)

# add executable
add_executable( ${EXECUTABLE_NAME} main.cpp )

# setup threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

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

	Threads::Threads

	${SFML_LIBRARIES_TO_LINK}

	painter
	engine
)

