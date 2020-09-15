#include "../include/init_visitor.h"

bool init_visitor::visit(area * obj)
{
	const auto [width, height, max_ships] = obj->get_params();
	std::vector<ship> ships_to_add; ships_to_add.reserve(max_ships);

	for(int i = 0; i < max_ships; i++)
	{
		ships_to_add.emplace_back( construct_ship( width, height, ships_to_add ) );
		obj->add_ship(ships_to_add.back());
	}

	return true;
}

// Monte carlo, but works. I hope...
ship init_visitor::construct_ship( const unumber max_x, const unumber max_y, const std::vector<ship>& ships ) const
{
	ship * ret = nullptr;
	point p1, p2;

	const auto not_collide = [&](const ship& _sh) -> bool
	{
		for(const ship& sh : ships)
			if( ship::collision( _sh, sh ) ) return true;
		return false;
	};

	do
	{
		if(ret) delete ret;

		const bool coin{ flip_coin() };

		p1 = point{ rng(0ul, max_x), rng(0ul, max_y) };
		p2 = point{
			( coin ? p1.x : rng(0ul, max_x) ),
			( (not coin) ? p1.y : rng(0ul, max_y) )
		};
	} while( p1 == p2 || not_collide( ship{ p1, p2 } ) );
	

	return ship{ p1, p2 };
}