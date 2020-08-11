#include <engine/include/point.h>

#include <cmath>

number point::distance(const point& p1, const point& p2)
{
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

bool point::centric(const point& p1, const point& p2)
{
	return (p1.x == p2.x) || (p1.y == p2.y);
}
