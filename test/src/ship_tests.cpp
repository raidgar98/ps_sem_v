#define BOOST_TEST_CASE

// Boost
#include <boost/test/unit_test.hpp>

// Project
#include "../include/testbase.h"
#include "../../libraries/engine/include/ship.h"

BOOST_AUTO_TEST_SUITE(ship_tests)

BOOST_AUTO_TEST_CASE(ship_test_1)
{
	constexpr unumber ship_length = 10;
	ship s1{point{0, 0}, point{ship_length, 0}};

	const auto shoot = [&](const point &p, const bool _hit) -> void { BOOST_REQUIRE_EQUAL(s1.hit(p), _hit); };
	const auto check_left_hits = [&](const number length) -> void { BOOST_REQUIRE_EQUAL(s1.hits_left(), length); };
	const auto check_alive = [&]() -> void { BOOST_REQUIRE(s1.is_alive()); };
	const auto check_death = [&]() -> void { BOOST_REQUIRE(not s1.is_alive()); };

	check_left_hits(ship_length);
	check_alive();

	shoot(point{0, 0}, true);
	check_left_hits( ship_length - 1);
	check_alive();

	shoot(point{0, 1}, true);
	check_left_hits(ship_length - 2);
	check_alive();

	shoot(point{0, 1}, false);
	check_left_hits(ship_length - 2);
	check_alive();

	for(unumber i = 2; i <= ship_length - 1; i++)
	{
		shoot(point{0, i}, true);
		check_left_hits(ship_length - i - 1);
		check_alive();

		shoot(point{0, i}, false);
		check_left_hits(ship_length - i - 1);
		check_alive();
	}

	shoot(point{0, ship_length}, true);
	check_left_hits(0);
	check_death();
}

BOOST_AUTO_TEST_SUITE_END()