#include "../include/testbase.h"

namespace testbase
{
	logger TestLogger::log = logger::get_logger<TestLogger>("TestLogger");

	void add_ship( area& a, const ship& s, const bool success)
	{
		BOOST_REQUIRE_EQUAL( a.add_ship(s), success );
	}

	void destroy_ship(area& a, ship& s)
	{
		const unumber amount_of_ships{a.count_alive()};
		const std::unique_ptr<std::vector<point>> targets{point::points_on_distance(s.get_p1(), s.get_p2())};
		for(const point& p : *targets)
			BOOST_REQUIRE( area::shoot(a, p) ); 
		BOOST_REQUIRE_EQUAL( a.count_alive(), amount_of_ships - 1 );
	};
}