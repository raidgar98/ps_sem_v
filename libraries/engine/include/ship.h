#pragma once

// STL
#include <vector>

// Project includes
#include <point.h>

class ship
{

	ship(const point& p1, const point& p2);
	number length() const;
	bool is_alive() const;
	number hits_left() const;
	bool hit(const point& p);

private:

	point p1;
	point p2;

	std::vector<point> hits;

};