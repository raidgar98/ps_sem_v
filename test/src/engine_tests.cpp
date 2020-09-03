#define BOOST_TEST_CASE

// Project includes
#include "../include/testbase.h"

BOOST_AUTO_TEST_SUITE(engine_tests)

BOOST_AUTO_TEST_CASE(engine_test_1)
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 2;

	const std::vector<ship> ship_collection_1{
		{ship{point{1, 1}, point{5, 1}},
		ship{point{1, 4}, point{5, 4}}}};
	const std::vector<ship> ship_collection_2{
		{ship{point{1, 6}, point{5, 6}},
		ship{point{1, 8}, point{5, 8}}}};

	const std::vector<player> init_bad_areas_1{
		{player{area{width, height, max_ships, ship_collection_1}},
		player{area{width, height, max_ships + 1, ship_collection_2}}}};
	const std::vector<player> init_bad_areas_2{
		{player{area{width, height, max_ships, ship_collection_1}},
		player{area{width, height + 1, max_ships, ship_collection_2}}}};
	const std::vector<player> init_bad_areas_3{
		{player{area{width + 1, height, max_ships, ship_collection_1}},
		player{area{width, height, max_ships, ship_collection_2}}}};
	const std::vector<player> init_correct_areas{
		{player{area{width, height, max_ships, ship_collection_1}},
		player{area{width, height, max_ships, ship_collection_2}}}};

	CHECK_ASSERTION(engine{init_bad_areas_1}, requirements_not_satisfied);
	CHECK_ASSERTION(engine{init_bad_areas_2}, requirements_not_satisfied);
	CHECK_ASSERTION(engine{init_bad_areas_3}, requirements_not_satisfied);
	BOOST_REQUIRE_NO_THROW(engine{init_correct_areas});
}

BOOST_AUTO_TEST_SUITE_END()