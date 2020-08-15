#include "../include/area.h"

// STL
#include <cassert>


area::area(const unumber x_dim, const unumber y_dim, const unumber max_ship_count)
	:x_dim{ x_dim }, y_dim{ y_dim }, max_ships{ max_ship_count } 
{
	assert( x_dim > 0 );
	assert( y_dim > 0 );
	assert( max_ship_count > 0 );
}

bool area::add_ship(const ship &s)
{
	for (const auto &sh : ships)
		if (ship::collision(sh, s))
			return false;

	ships.push_back(s);
	return true;
}

const std::vector<ship> &area::get_ships() const
{
	return ships;
}

bool area::shoot(area &a, const point &p)
{
	for (ship &s : a.ships)
		if (s.hit(p))
			return true;
	return false;
}

unumber area::count_alive() const
{
	return std::count_if(ships.begin(), ships.end(), [](const ship &s) { return s.is_alive(); });
}