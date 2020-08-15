#define BOOST_TEST_CASE

// Boost
#include <boost/test/unit_test.hpp>

// Project
#include "../include/testbase.h"
#include "../../libraries/engine/include/ship.h"

BOOST_AUTO_TEST_SUITE(ship_tests)

BOOST_AUTO_TEST_CASE(ship_test_1)
{
	constexpr unumber ship_length = 11;
	constexpr unumber ship_max_x = 10;
	ship s1{point{0, 0}, point{ship_max_x, 0}};

	const auto shoot = [&](const point &p, const bool _hit) -> void { BOOST_REQUIRE_EQUAL(s1.hit(p), _hit); };
	const auto check_left_hits = [&](const number length) -> void { BOOST_REQUIRE_EQUAL(s1.hits_left(), length); };
	const auto check_alive = [&]() -> void { BOOST_REQUIRE(s1.is_alive()); };
	const auto check_death = [&]() -> void { BOOST_REQUIRE(not s1.is_alive()); };

	check_left_hits(ship_length);
	check_alive();

	shoot(point{0, 0}, true);
	check_left_hits(ship_length - 1);
	check_alive();

	shoot(point{1, 0}, true);
	check_left_hits(ship_length - 2);
	check_alive();

	shoot(point{1, 0}, false);
	check_left_hits(ship_length - 2);
	check_alive();

	for (unumber i = 2; i <= ship_max_x - 1; i++)
	{
		shoot(point{i, 0}, true);
		check_left_hits(ship_length - i - 1);
		check_alive();

		shoot(point{i, 0}, false);
		check_left_hits(ship_length - i - 1);
		check_alive();
	}

	shoot(point{ship_max_x, 0}, true);
	check_left_hits(0);
	check_death();
}

BOOST_AUTO_TEST_CASE(ship_collision_test)
{

	const ship sh0{point{0, 0}, point{1, 0}};
	const ship sh1{point{1, 1}, point{5, 1}};
	const ship sh2{point{2, 1}, point{6, 1}};
	const ship sh3{point{3, 0}, point{3, 10}};
	const ship sh4{point{5, 5}, point{5, 6}};

	const ship& reference = sh1;

	const auto check_collision = [&](const ship& sh, const bool should_collide) { BOOST_REQUIRE_EQUAL( ship::collision( reference, sh ), should_collide ); };

	check_collision( sh0, false );
	check_collision( sh1, true );
	check_collision( sh2, true );
	check_collision( sh3, true );
	check_collision( sh4, false );
}

BOOST_AUTO_TEST_SUITE_END()