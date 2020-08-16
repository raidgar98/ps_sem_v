#pragma once

// STL
#include <iostream>
#include <vector>

// Project invludes
#include "../../types.hpp"

/*
	In this coordinate system top left corner is (0,0), if we go down, y increase, if right x increases. 
	It's behaved just like SCREEN coordinate system
*/
struct point
{

	// Property required
	unumber x;
	unumber y;

	explicit point(const unumber _x = 0ul, const unumber _y = 0ul) : x{_x}, y{_y} {}

	point transposition() const;
	static floating distance(const point& p1, const point& p2);
	static bool centric(const point& p1, const point& p2);
	static bool in_area(const point& p1, const point& p2, const point& shot);
	static bool in_area(const point &p1, const point &p2, const floating x, const floating y);
	static void order(point& p1, point& p2);

	static std::vector<point>* points_on_distance(const point&, const point&);
	
	friend inline bool operator<(const point& p1, const point& p2)
	{
		return ( p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x );
	}

	friend inline bool operator==(const point& p1, const point& p2)
	{
		return ( p1.x == p2.x && p1.y == p2.y );
	}

	friend inline bool operator!=(const point& p1, const point& p2)
	{
		return not (p1 == p2);
	}
};

inline std::ostream& operator<<(std::ostream& os, const point& p)
{
	return os << "( " << p.x << " ; " << p.y << " )";
}
