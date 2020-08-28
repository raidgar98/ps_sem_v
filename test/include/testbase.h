#pragma once

// Boost
#include <boost/test/unit_test.hpp>

// Project includes
#include "../../libraries/engine/include/point.h"
#include "../../libraries/engine/include/ship.h"
#include "../../libraries/engine/include/area.h"
#include "../../libraries/engine/include/engine.h"
#include "../../libraries/logger/include/logger.h"

#define CHECK_ASSERTION_WITH_MESSAGE( Expression, Exception, RequiredMessage ) BOOST_REQUIRE_EXCEPTION( Expression, Exception, [](const Exception& e){ return (RequiredMessage == "" ? true : e.what() == RequiredMessage); } )
#define CHECK_ASSERTION( Expression, Exception ) CHECK_ASSERTION_WITH_MESSAGE( Expression, Exception, "" )

namespace testbase
{

	class TestLogger
	{
	public:
		static logger log;
	};

	void add_ship( area&, const ship&, const bool );
	void destroy_ship(area& a, ship& s);

} // namespace testbase

#define lout testbase::TestLogger::log