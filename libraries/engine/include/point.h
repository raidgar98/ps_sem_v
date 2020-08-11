#pragma once

using number = unsigned long int;

struct point
{
	number x;
	number y;

	static number distance(const point& p1, const point& p2);
	static bool centric(const point& p1, const point& p2);
	
	friend inline bool operator<(const point& p1, const point& p2)
	{
		return ( p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x );
	}

	friend inline bool operator==(const point& p1, const point& p2)
	{
		return ( p1.x == p2.x && p1.y == p2.y );
	}
};

