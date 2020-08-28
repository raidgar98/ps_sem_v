#include "../include/point.h"

#include <cmath>
#include <iostream>

floating point::distance(const point &p1, const point &p2)
{
	auto pow = std::pow<float, float>;
	const number a_1 = p1.x - p2.x;
	const number b_1 = p1.y - p2.y;
	return std::sqrt(pow(a_1, 2.0) + pow(b_1, 2.0));
}

bool point::centric(const point &p1, const point &p2)
{
	return (p1.x == p2.x) || (p1.y == p2.y);
}

bool point::in_area(const point &p1, const point &p2, const point& shot)
{
	return point::in_area( p1, p2, static_cast<floating>(shot.x), static_cast<floating>(shot.y) );
}

bool point::in_area(const point &p1, const point &p2, const floating x, const floating y)
{
	point a1{p1}, a2{p2};
	point::order(a1, a2);

	return (
		( x >= a1.x ) and
		( x <= a2.x ) and
		( y >= std::min(a1.y, a2.y) ) and
		( y <= std::max(a1.y, a2.y) )
	);
}

// sort given points, so p1 is closer to {0;0}
void point::order(point &p1, point &p2)
{
	const point p3 = std::min(p1, p2);
	if (p3 == p2) std::swap(p1, p2);
}

point point::transposition() const
{
	return point{ y, x };
}

std::vector<point>* point::points_on_distance(const point& pp1, const point& pp2)
{
	point p1{pp1}, p2{pp2};
	point::order(p1, p2);

	std::vector<point>* ret = new std::vector<point>();
	ret->reserve( point::distance(p1, p2) );

	const unumber max_y = std::max(p1.y, p2.y);
	const unumber min_y = std::min(p1.y, p2.y);

	for(unumber i = p1.x; i <= p2.x; i++)
		for(unumber j = min_y; j <= max_y; j++)
			ret->emplace_back( i, j );

	return ret;
}