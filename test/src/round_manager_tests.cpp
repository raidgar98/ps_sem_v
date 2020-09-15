#define BOOST_TEST_CASE

// Project
#include "../include/testbase.h"
#include "../../libraries/engine/include/round_manager.hpp"

// STL
#include <queue>

BOOST_AUTO_TEST_SUITE(round_manager_tests)

BOOST_AUTO_TEST_CASE(round_manager_test_1)
{
	constexpr unumber area_width = 10;
	constexpr unumber area_heigt = 10;
	constexpr unumber max_ships = 2;

	const ship s11{point{1, 1}, point{5, 1}};
	const ship s12{point{1, 4}, point{5, 4}};

	const ship s21{point{1, 6}, point{5, 6}};
	const ship s22{point{1, 8}, point{5, 8}};

	std::vector<area> areas{{area{area_width, area_heigt, max_ships, {s11, s12}}, area{area_width, area_heigt, max_ships, {s21, s22}}}};
	round_manager<std::vector<area>> rm{areas, [](const std::vector<area> &vec) -> bool 
	{
		return std::count_if(vec.begin(), vec.end(), [](const area &_a) { return _a.count_alive() >= 1; }) == 1;
	}};

	std::unique_ptr<std::vector<point>> tgs_1{point::points_on_distance(s11.get_p1(), s11.get_p2())};
	std::unique_ptr<std::vector<point>> tgs_2{point::points_on_distance(s21.get_p1(), s21.get_p2())};
	std::unique_ptr<std::vector<point>> tgs_3{point::points_on_distance(s12.get_p1(), s12.get_p2())};
	std::unique_ptr<std::vector<point>> tgs_4{point::points_on_distance(s22.get_p1(), s22.get_p2())};

	std::queue<point> targets;

	for (int i = 0; i < tgs_1->size(); i++)
	{
		targets.push(tgs_1->at(i));
		targets.push(tgs_2->at(i));
		targets.push(tgs_3->at(i));
		targets.push(tgs_4->at(i));
	}

	for (auto it = rm.begin(); it != rm.end(); it++)
	{
		BOOST_REQUIRE( (*it).shoot( targets.front() ) );
		targets.pop();
		BOOST_REQUIRE_GT( targets.size(), 0 );
	}

	BOOST_REQUIRE_EQUAL( targets.size(), 1 );
}

BOOST_AUTO_TEST_SUITE_END()