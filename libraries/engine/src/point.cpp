#include "../include/point.h"

#include <cmath>
#include <iostream>

floating point::distance(const point& p1, const point& p2)
{
	auto pow = std::pow<double, double>;
	const number a_1{ p1.x - p2.x };
	const number b_1{ p1.y - p2.y };
	return std::sqrt(pow(a_1 , 2.0) + pow(b_1, 2.0));
}

bool point::centric(const point& p1, const point& p2)
{
	return (p1.x == p2.x) || (p1.y == p2.y);
}

bool point::in_area(const point& p1, const point& p2, const point& shot)
{
	point a1{p1}, a2{p2};
	point::order(a1, a2);

	if( shot.x - a1.x > a1.x - a2.x) return false;
	if( shot.y - a1.y > a1.y - a2.y) return false;
	return true;
}

// sort given points, so p1 is closer to {0;0}
void point::order(point& p1, point& p2)
{
	if(p2 < p1)
	{
		point p3 = p1;
		p1 = p2;
		p2 = p3;
	}
}