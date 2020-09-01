#include "ship.h"

// STL

#include <tuple>
#include <array>

ship::ship(const point &pp1, const point &pp2)
	: p1{pp1}, p2{pp2}
{
	require( pp1 != pp2 );
	require(point::centric(pp1, pp2));
	point::order(p1, p2);
	hits.reserve(length());

	Log<ship>::get_logger().dbg("Ship with size: " + std::to_string(hits.capacity()) + ", created");
}

number ship::length() const
{
	// const unumber y_max = std::max(1ul, (std::max(p1.y, p2.y) - std::min(p1.y, p2.y))); // + to ret
	return point::distance(p1, p2) + 1ul;
}

bool ship::is_alive() const
{
	return hits_left() > 0;
}

number ship::hits_left() const
{
	return length() - hits.size();
}

bool ship::hit(const point &p)
{
	if (not(point::centric(p1, p) or point::centric(p2, p)))
		return false;
	if (point::in_area(p1, p2, p) and segment_alive(p))
	{
		_apply_hit(p);
		Log<ship>::get_logger().dbg("Ship hit ( " + std::to_string(p.x) + " , " + std::to_string(p.y) + " )");
		return true;
	}
	else
		return false;
}

bool ship::segment_alive(const point& p) const
{
	return hits.find(p) == hits.end();
}

void ship::_apply_hit(const point &p)
{
	hits.insert(p);
}

ship::centric_type ship::_ship_centricion( const ship& s1, const ship& s2)
{
	if( 
		( s1.p1.x == s1.p2.x ) and
		( s1.p2.x == s2.p1.x ) and
		( s2.p1.x == s2.p2.x )
	) return centric_type::X;
	else if(
		( s1.p1.y == s1.p2.y ) and
		( s1.p2.y == s2.p1.y ) and
		( s2.p1.y == s2.p2.y )
	) return centric_type::Y;
	else return centric_type::None;
}

bool ship::collision(const ship &sh1, const ship &sh2)
{
	// Most basi case ( centric in one of axis )
	// X case
	const auto centric = _ship_centricion(sh1, sh2);
	if( centric != None )
	{
		Log<ship>::get_logger() << "Centric!";
		return	point::in_area( sh1.p1, sh1.p2, sh2.p1 ) or 
				point::in_area( sh1.p1, sh1.p2, sh2.p2 ) or 
				point::in_area(sh2.p1, sh2.p2, sh1.p1) or 
				point::in_area(sh2.p1, sh2.p2, sh1.p2);
	}

	// Calculating curves
	using vec = const std::array<floating, 2>;
	using vvec = const std::array<vec, 2>;
	constexpr floating b = 1.0;

	const auto determitant = [](const vvec& matrix) -> floating { return (matrix[0][0] * matrix[1][1])-(matrix[0][1] * matrix[1][0]); };

	const auto curve = [&](const point& p1, const point& p2) -> std::tuple<floating, floating, floating> {

		const floating _W = determitant(vvec{
			vec{ static_cast<floating>(p1.x), b},
			vec{ static_cast<floating>(p2.x), b}
		});

		const floating _W_a = determitant(vvec{
			vec{ static_cast<floating>(p1.y), b },
			vec{ static_cast<floating>(p2.y), b }
		});

		const floating _W_b = determitant(vvec{
			vec{ static_cast<floating>(p1.x), static_cast<floating>(p1.y) },
			vec{ static_cast<floating>(p2.x), static_cast<floating>(p2.y) }
		});

		return { _W_a / _W, _W_b / _W, _W };
	};

	auto [a1, c1, _w_1] = curve( sh1.p1, sh1.p2 );
	auto [a2, c2, _w_2] = curve( sh2.p1, sh2.p2 );


	if( _w_1 == _w_2 and _w_1 == 0.0)
	{
		// If both are straight, rotate them by 90 degree, and calculate them as straight lines
		// Probably never enter this case
		auto tmp = curve(sh1.p1.transposition(), sh1.p2.transposition());
		a1 = std::get<0>(tmp);
		c1 = std::get<1>(tmp);
		_w_1 = std::get<2>(tmp);

		tmp = curve(sh2.p1.transposition(), sh2.p2.transposition());
		a2 = std::get<0>(tmp);
		c2 = std::get<1>(tmp);
		_w_2 = std::get<2>(tmp);
	}
	else if( _w_1 == 0.0 )
	{
		const point pp{ sh1.p1.x, sh2.p1.y };
		return point::in_area( sh1.p1, sh1.p2, pp ) and point::in_area( sh2.p1, sh2.p2, pp);
	}else if( _w_2 == 0.0)
	{
		const point pp{ sh2.p1.x, sh1.p1.y };
		return point::in_area( sh1.p1, sh1.p2, pp ) and point::in_area( sh2.p1, sh2.p2, pp);
	}

	// Checking are curves crossing
	const floating W = determitant(vvec{
		vec{ a1, b },
		vec{ a2, b }
	});

	const floating W_x = determitant(vvec{
		vec{ c1, b },
		vec{ c2, b }
	});

	const floating W_y = determitant(vvec{
		vec{ a1, c1 },
		vec{ a2, c2 }
	});

	const floating x = W_x / W;
	const floating y = W_y / W;

	const bool r1 =  ( W == 0.0 ) and  ( W_x == 0.0 ) and ( W_y == 0.0 );
	const bool r2 = W != 0.0 and (
			point::in_area( sh1.p1, sh1.p2, x, y ) or 
			point::in_area( sh2.p1, sh2.p2, x, y ) 
		);

	return ( r1 ) or ( r2 );
}