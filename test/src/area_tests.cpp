#define BOOST_TEST_CASE

// Boost
// #include <boost/test/unit_test.hpp>

// Project
#include "../include/testbase.h"

BOOST_AUTO_TEST_SUITE(area_tests)

BOOST_AUTO_TEST_CASE(area_test_1)
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 3;

	area a1{width, height, max_ships};

	const auto add_ship = [&](const ship &s, const bool success) { testbase::add_ship(a1, s, success); }; // { BOOST_REQUIRE_EQUAL( a1.add_ship( s ), success ); };

	add_ship(ship{point{1, 1}, point{1, 5}}, true);
	add_ship(ship{point{1, 1}, point{1, 5}}, false);
	add_ship(ship{point{1, 1}, point{1, 15}}, false);
	add_ship(ship{point{1, 1}, point{15, 1}}, false);
	add_ship(ship{point{2, 2}, point{5, 2}}, true);
	add_ship(ship{point{3, 3}, point{3, 9}}, true);
	add_ship(ship{point{9, 9}, point{9, 10}}, false);
}

BOOST_AUTO_TEST_CASE(area_test_2)
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 3;

	area a{width, height, max_ships};

	const ship sh1{point{0, 0}, point{5, 0}};
	const ship sh2{point{0, 2}, point{2, 2}};
	const ship sh3{point{0, 4}, point{9, 4}};

	const std::unique_ptr<std::vector<point>> sp1{point::points_on_distance(sh1.get_p1(), sh1.get_p2())};
	const std::unique_ptr<std::vector<point>> sp2{point::points_on_distance(sh2.get_p1(), sh2.get_p2())};
	const std::unique_ptr<std::vector<point>> sp3{point::points_on_distance(sh3.get_p1(), sh3.get_p2())};

	BOOST_REQUIRE_EQUAL(a.count_alive(), 0);
	testbase::add_ship(a, sh1, true);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 1);
	testbase::add_ship(a, sh2, true);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 2);
	testbase::add_ship(a, sh3, true);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 3);

	const auto destroy_ship = [&](const std::vector<point> &targets) { for(const point& p : targets) BOOST_REQUIRE( area::shoot(a, p) ); };

	destroy_ship(*sp1);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 2);

	destroy_ship(*sp2);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 1);

	destroy_ship(*sp3);
	BOOST_REQUIRE_EQUAL(a.count_alive(), 0);
}

BOOST_AUTO_TEST_SUITE_END()