#define BOOST_TEST_CASE

// Boost
#include <boost/test/unit_test.hpp>

// Project
#include "../include/testbase.h"
#include "../../libraries/engine/include/area.h"

BOOST_AUTO_TEST_SUITE(area_tests)

BOOST_AUTO_TEST_CASE(area_test_1)
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 3;

	area a1{ width, height, max_ships };

	const auto add_ship = [&](const ship& s, const bool success) { BOOST_REQUIRE_EQUAL( a1.add_ship( s ), success ); };

	add_ship( ship{ point{ 1, 1 }, point{ 1, 5 } }, true);
	add_ship( ship{ point{ 1, 1 }, point{ 1, 5 } }, false);
	add_ship( ship{ point{ 1, 1 }, point{ 1, 15 } }, false);
	add_ship( ship{ point{ 1, 1 }, point{ 15, 1 } }, false);
	add_ship( ship{ point{ 2, 2 }, point{ 5, 2 } }, true);
	add_ship( ship{ point{ 3, 3 }, point{ 3, 9 } }, true);
	add_ship( ship{ point{ 9, 9 }, point{ 9, 10 } }, false);
}

BOOST_AUTO_TEST_SUITE_END()