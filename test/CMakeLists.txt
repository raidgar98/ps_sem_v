project(tests CXX)
enable_testing()

file(GLOB tests_sources
	"src/*.cpp"
)

find_package(Boost 1.70 REQUIRED COMPONENTS unit_test_framework)

add_executable(tests ${tests_sources})
# add_dependencies(tests point_lib)

target_include_directories(tests PRIVATE 
	${BOOST_INCLUDE_DIRS}
)

target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries( tests 

	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 

	point
	ship
	area

	logger
)

add_test(NAME all_tests COMMAND tests)
