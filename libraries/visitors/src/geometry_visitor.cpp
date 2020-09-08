#include "../include/geometry_visitor.h"

// STL
#include <cmath>

pixel_coord geometry_visitor::get_point_position(const point &p) const
{
	const paint_config *cfg = get_config<paint_config>();
	const pixel_coord top_left{
		cfg->begin.x + cfg->margin + cfg->padding,
		cfg->begin.y + cfg->margin + cfg->padding
	};

	if (p == point{0, 0}) return top_left;
	else return pixel_coord{
		round(top_left.x + (cfg->get_cell_width() * p.x) + (cfg->padding * (p.x == 0ul ? 0.0f : 1.0f) * (p.x == 0ul ? 0.0f : p.x)), 2l),
		round(top_left.y + (cfg->get_cell_height() * p.y) + (cfg->padding * (p.y == 0ul ? 0.0f : 1.0f) * (p.y == 0ul ? 0.0f : p.y)), 2l)
	};
}

geometry_visitor::geometry_visitor(paint_config &cnfig)
{
	_config = &cnfig;
}

constexpr floating geometry_visitor::round(const floating n, const number digits)
{
	const long long int ret = std::pow<floating, number>( 10.0f, digits ) * n;
	return static_cast<floating>(ret) / static_cast<floating>(std::pow<floating, number>( 10.0f, digits ));
};