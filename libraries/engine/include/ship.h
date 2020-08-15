#pragma once

// Boost
#include <boost/container/flat_set.hpp>

// Project includes
#include "../include/point.h"
#include "../../logger/include/logger.h"

class ship : Log<ship>
{
public:

	ship(const point& p1, const point& p2);
	number length() const;
	bool is_alive() const;
	number hits_left() const;

	bool hit(const point& p);
	static bool collision(const ship& sh1, const ship& sh2);

private:

	point p1;
	point p2;

	boost::container::flat_set<point> hits;

	void _apply_hit(const point& p);

};