#include "../include/painter.hpp"

paint_visitor::paint_visitor(const paint_config &cfg)
	: config{cfg} {}

template <>
void paint_visitor::paint<area>(const area &obj)
{
}

template <>
void paint_visitor::paint<ship>(const ship &obj)
{
	std::unique_ptr<std::vector<point>> points_to_paint{point::points_on_distance(obj.get_p1(), obj.get_p2())};
	const float cell_width{ config.get_cell_width() };
	const float cell_height{ config.get_cell_height() };
	const sf::Color ship_color{ config.get_ship_color() };

	for (point &p : *points_to_paint)
	{
		const pixel_coord coord{ get_point_position( p ) };
		sf::RectangleShape cell{ { coord.x, coord.y } };
		cell.setSize( { cell_width, cell_height } );
		cell.setFillColor(ship_color);
		cell.setOutlineColor( config.ship_outline_color );
	}
}

pixel_coord paint_visitor::get_point_position(const point &p) const
{
	const pixel_coord top_left{
		config.begin.x + config.margin,
		config.begin.y + config.margin};

	if (p == point{0, 0})
		return top_left;
	else
		return pixel_coord{
			top_left.x + (config.get_cell_width() * p.x) + (config.padding * 2.0 * (p.x - 1.0)),
			top_left.y + (config.get_cell_height() + p.y) + (config.padding * 2.0 * (p.y - 1.0))
		};
}