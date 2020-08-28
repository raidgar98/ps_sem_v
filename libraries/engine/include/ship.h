#pragma once

// Boost
#include <boost/container/flat_set.hpp>

// Project includes
#include "../include/point.h"
#include "../../logger/include/logger.h"
#include "../../patterns/include/visitor.hpp"

class ship : 
	public Visitable<ship>,
	private Log<ship>
{
public:

	ship(const point& p1, const point& p2);
	number length() const;
	bool is_alive() const;
	number hits_left() const;

	bool hit(const point& p);
	static bool collision(const ship& sh1, const ship& sh2);

	const point& get_p1() const { return p1; }
	const point& get_p2() const { return p2; }

private:

	point p1;
	point p2;

	boost::container::flat_set<point> hits;

	void _apply_hit(const point& p);

	enum centric_type
	{
		None = 0,
		X,
		Y
	};

	static centric_type _ship_centricion( const ship&, const ship& );

};