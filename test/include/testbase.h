#pragma once

// Boost
#include <boost/test/unit_test.hpp>

// Project includes
#include "../../libraries/engine/include/point.h"
#include "../../libraries/engine/include/ship.h"
#include "../../libraries/engine/include/area.h"
#include "../../libraries/logger/include/logger.h"

namespace testbase
{

	class TestLogger
	{
	public:
		static logger log;
	};

	void add_ship( area&, const ship&, const bool );

} // namespace testbase

#define lout testbase::TestLogger::log