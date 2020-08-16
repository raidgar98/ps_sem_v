#define BOOST_TEST_MAIN

// Project
#include "../include/testbase.h"

BOOST_AUTO_TEST_SUITE(point_tests)

BOOST_AUTO_TEST_CASE(point_test_1)
{
	const point p1;
	const point p2{0, 0};
	const point p3{1, 2};

	BOOST_REQUIRE_EQUAL(p1, p2);
	BOOST_REQUIRE_EQUAL(p3.x, 1);
	BOOST_REQUIRE_EQUAL(p3.y, 2);
}

BOOST_AUTO_TEST_CASE(point_centric_test)
{
	const point p1{1, 2};
	const point p2{3, 4};
	const point p3{1, 4};

	BOOST_REQUIRE(not point::centric(p1, p2));
	BOOST_REQUIRE(point::centric(p1, p3));
	BOOST_REQUIRE(point::centric(p2, p3));
}

BOOST_AUTO_TEST_CASE(point_distance_test)
{
	const point p1{0, 0};
	const point p2{1, 1};
	const point p3{2, 2};
	const point p4{2, 3};
	const point p5{3, 2};

	BOOST_REQUIRE_EQUAL(point::distance(p1, p2), point::distance(p2, p3));
	BOOST_REQUIRE_EQUAL(2.0 * point::distance(p1, p2), point::distance(p1, p3));
	BOOST_REQUIRE_EQUAL(point::distance(p3, p3), 0.0);
	BOOST_REQUIRE_EQUAL(point::distance(p3, p4), 1.0);
	BOOST_REQUIRE_EQUAL(point::distance(p3, p5), 1.0);
}

BOOST_AUTO_TEST_CASE(point_order_test)
{
	const point r00{ 0, 0 };
	const point r11{ 1, 1 };
	const point r12{ 1, 2 };
	const point r21{ 2, 1 };
	const point r22{ 2, 2 };

	const auto swap = [](point p1, point p2, const bool _swap)
	{
		const point pat1 = p1;
		const point pat2 = p2;
		point::order(p1, p2);
		BOOST_REQUIRE_EQUAL( pat1 == p1, !_swap );
		BOOST_REQUIRE_EQUAL( pat2 == p2, !_swap );
	};

	swap( point{ 1, 0 }, point{ 0, 0 }, true );
	swap( point{ 0, 0 }, point{ 1, 0 }, false);

	swap( point{ 0, 0 }, point{ 0, 1 }, false );
	swap( point{ 0, 1 }, point{ 0, 0 }, true );

	swap( point{ 1, 1 }, point{ 2, 0 }, false );
	swap( point{ 1, 99 }, point{ 2, 0 }, false );
	swap( point{ 2, 0 }, point{ 1, 99 }, true );

	swap( point{ 1, 1 }, point{ 1, 0 }, true );
	swap( point{ 1, 0 }, point{ 1, 1 }, false );
}

BOOST_AUTO_TEST_CASE(point_area_test)
{
	// area 10 x 10
	point a1{0, 0};
	point a2{10, 5};

	// help function
	const auto shot = [&](const point &p, const bool kill) { BOOST_REQUIRE_EQUAL(kill, point::in_area(a1, a2, p)); };

	// shots
	shot(point{0, 0}, true);
	shot(point{10, 5}, true);
	shot(point{5, 5}, true);
	shot(point{0, 5}, true);
	shot(point{0, 10}, false);
	shot(point{10, 0}, true);
	shot(point{11, 0}, false);
	shot(point{0, 6}, false);
	shot(point{11, 11}, false);
	shot(point{0, 1}, true);
	shot(point{1, 0}, true);

	// move a bit testing field
	a1 = point{5, 6};
	a2 = point{10, 10};

	// continue shooting
	shot(point{1,1}, false);
	shot(point{5,5}, false);
	shot(point{4,4}, false);
	shot(point{6,6}, true);
	shot(point{4,6}, false);
	shot(point{5,5}, false);
	shot(point{5,6}, true);

}

BOOST_AUTO_TEST_SUITE_END()