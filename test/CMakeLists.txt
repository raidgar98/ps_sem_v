
file(GLOB tests_sources
	"src/*.cpp"
)

# find_package(doctest REQUIRED)

add_executable(tests ${tests_sources})
# target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries( tests doctest )

# target_link_libraries(test PRIVATE doctest::doctest)

target_include_directories( tests PUBLIC include )
