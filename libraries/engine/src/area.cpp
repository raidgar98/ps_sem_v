#include "../include/area.h"

// STL


area::area(const unumber x_dim, const unumber y_dim, const unumber max_ship_count, const std::vector<ship>& _ships)
	: x_dim{x_dim}, y_dim{y_dim}, max_ships{max_ship_count}
{
	require(x_dim > 0);
	require(y_dim > 0);
	require(max_ship_count > 0);
	for(const ship& s : _ships)
		add_ship( s );
}

bool area::add_ship(const ship &s)
{
	if (ships.size() == max_ships)
	{
		get_logger().warn("failed adding ship because of limit");
		return false;
	}
	if (std::max(s.get_p1().x, s.get_p2().x) > x_dim)
	{
		get_logger().warn("failed adding ship because, ship is too wide in x dimension");
		return false;
	}
	if (std::max(s.get_p1().y, s.get_p2().y) > y_dim)
	{
		get_logger().warn("failed adding ship because, ship is too wide in y dimension");
		return false;
	}

	for (const auto &sh : ships)
		if (ship::collision(sh, s))
		{
			get_logger().warn("failed adding ship. Detected collision with existing one");
			return false;
		}

	ships.push_back(s);
	return true;
}

const std::vector<ship> &area::get_ships() const
{
	return ships;
}

std::vector<ship> &area::get_ships()
{
	return ships;
}

bool area::shoot(const point &p)
{
	for (ship &s : ships)
		if (s.hit(p))
			return true;
	return false;
}

unumber area::count_alive() const
{
	return std::count_if(ships.begin(), ships.end(), [](const ship &s) { return s.is_alive(); });
}

bool area::accept( visits<area>* v )
{
	require(v);
	return v->visit(this);
}

void area::for_each_ship(std::function<void(ship&)> fn)
{
	for(ship& sh : ships)
		fn(sh);
}