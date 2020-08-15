#pragma once

#include "../../libraries/logger/include/logger.h"

class TestLogger
{
public:
	static logger log;
};

#define lout TestLogger::log