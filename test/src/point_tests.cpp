#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../../libraries/engine/include/point.h"

BOOST_AUTO_TEST_SUITE( point_tests )

BOOST_AUTO_TEST_CASE( point_test_1 ) 
{
	const point p1;
	const point p2{0, 0};
	const point p3{1, 2};

	BOOST_REQUIRE_EQUAL( p1, p2 );
	BOOST_REQUIRE_EQUAL( p3.x, 1 );
	BOOST_REQUIRE_EQUAL( p3.y, 2 );
}

BOOST_AUTO_TEST_CASE( point_centric_test )
{
	const point p1{ 1, 2 };
	const point p2{ 3, 4 };
	const point p3{ 1, 4 };

	BOOST_REQUIRE( not point::centric(p1, p2) );
	BOOST_REQUIRE( point::centric(p1, p3) );
	BOOST_REQUIRE( point::centric(p2, p3) );
}

BOOST_AUTO_TEST_CASE( point_distance_test )
{
	const point p1{ 0, 0 };
	const point p2{ 1, 1 };
	const point p3{ 2, 2 };
	const point p4{ 2, 3 };
	const point p5{ 3, 2 };

	BOOST_REQUIRE_EQUAL( point::distance(p1, p2), point::distance(p2, p3) );
	BOOST_REQUIRE_EQUAL( 2.0 * point::distance(p1, p2), point::distance(p1, p3) );
	BOOST_REQUIRE_EQUAL( point::distance(p3, p3), 0.0 );
	BOOST_REQUIRE_EQUAL( point::distance(p3, p4), 1.0 );
	BOOST_REQUIRE_EQUAL( point::distance(p3, p5), 1.0 );
}

BOOST_AUTO_TEST_SUITE_END()