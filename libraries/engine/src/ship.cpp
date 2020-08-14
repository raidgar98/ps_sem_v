#include "ship.h"

#include <cassert>

#define or ||
#define and &&

ship::ship(const point &pp1, const point &pp2)
	: p1{pp1}, p2{pp2}
{
	assert(point::centric(pp1, pp2));
	if(pp1 < pp2)
	{
		this->p1 = pp2;
		this->p2 = pp1;
	}
	hits.reserve(length());
}

number ship::length() const
{
	return point::distance(p1, p2);
}

bool ship::is_alive() const
{
	return hits.size() < length();
}

number ship::hits_left() const
{
	return length() - hits.size();
}

bool ship::hit(const point& p)
{
	if(!point::centric(p1, p)) return false;
	if( point::in_area(p1, p2, p) and [&](){ for(const point& _p : hits) {if(_p == p) return false; } return true; } ) _apply_hit(p); return;
}

void ship::_apply_hit(const point& p)
{

}