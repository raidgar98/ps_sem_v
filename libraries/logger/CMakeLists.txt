project(logger CXX)

find_package(Boost 1.70 REQUIRED COMPONENTS filesystem date_time stacktrace_backtrace stacktrace_addr2line stacktrace_noop stacktrace_basic)

add_library(logger src/logger.cpp)
target_include_directories(logger PRIVATE include ${BOOST_INCLUDE_DIRS} ../rang/include)
target_link_libraries(logger
	${Boost_LIBRARIES}
)