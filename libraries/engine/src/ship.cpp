#include "ship.h"

#include <cassert>

ship::ship(const point &pp1, const point &pp2)
	: p1{pp1}, p2{pp2}
{
	assert(point::centric(pp1, pp2));
	point::order(p1, p2);
	hits.reserve(length());

	log.dbg("Ship with size: " + std::to_string( hits.capacity() ) + ", created");
}

number ship::length() const
{
	return point::distance(p1, p2);
}

bool ship::is_alive() const
{
	return static_cast<number>( hits.size() ) < length();
}

number ship::hits_left() const
{
	return length() - hits.size();
}

bool ship::hit(const point& p)
{
	if(not (point::centric(p1, p) or point::centric(p2, p))) return false;
	if( point::in_area(p1, p2, p) and hits.find(p) == hits.end() )
	{
		_apply_hit(p);
		log.dbg("Ship hit ( " + std::to_string(p.x) + " , " + std::to_string(p.y) + " )");
		return true;
	}
	else return false;
}

void ship::_apply_hit(const point& p)
{
	hits.insert( p );
}