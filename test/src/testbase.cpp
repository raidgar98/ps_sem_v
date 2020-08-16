#include "../include/testbase.h"

namespace testbase
{
	logger TestLogger::log = logger::get_logger<TestLogger>("TestLogger");

	void add_ship( area& a, const ship& s, const bool success)
	{
		BOOST_REQUIRE_EQUAL( a.add_ship(s), success );
	}
}