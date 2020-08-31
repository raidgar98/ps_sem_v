#include "../include/painter.hpp"

constexpr floating round(const floating n, const number digits = 2ul)
{
	const long long int ret = std::pow<floating, number>( 10.0f, digits ) * n;
	return static_cast<floating>(ret) / std::pow<floating, number>( 10.0f, digits );
};

paint_visitor::paint_visitor(result_collection_t &res, paint_config &cnfig)
	: results{res} 
	{
		_config = &cnfig;
	}

void paint_visitor::paint(const area &obj)
{
	Log<paint_visitor>::get_logger().info("Painting area started");
	const paint_config* cfg = get_config<paint_config>();
	sf::RectangleShape* board = new sf::RectangleShape{};

	board->setPosition({cfg->begin.x, cfg->begin.y});
	board->setSize({ cfg->area_width, cfg->area_height });
	board->setFillColor( cfg->area_color );
	board->setOutlineColor( cfg->area_outline_color );
	board->setOutlineThickness( cfg->outline_width );

	Log<paint_visitor>::get_logger().info("Painting area finished");
	results.wait_push( std::make_shared<sf::RectangleShape>( *board ) );
	results.wait_push( std::shared_ptr<sf::RectangleShape>( cfg->end_element) );
}

void paint_visitor::paint(const ship &obj)
{
	Log<paint_visitor>::get_logger().info("Painting ship started");
	const paint_config* cfg = get_config<paint_config>();
	std::unique_ptr<std::vector<point>> points_to_paint{point::points_on_distance(obj.get_p1(), obj.get_p2())};
	const float cell_width{cfg->get_cell_width()};
	const float cell_height{cfg->get_cell_height()};
	const sf::Color ship_color{cfg->get_ship_color()};
	
	for (point &p : *points_to_paint)
	{
		const pixel_coord coord{get_point_position(p)};
		sf::RectangleShape* cell = new sf::RectangleShape{};
		cell->setPosition({coord.x, coord.y});
		cell->setSize({cell_width, cell_height});
		cell->setFillColor(ship_color);
		cell->setOutlineColor(cfg->ship_outline_color);
		cell->setOutlineThickness( cfg->outline_width );

		// Log<paint_visitor>::get_logger().info("Painting ship in progress...");
		results.wait_push( std::make_shared<sf::RectangleShape>( *cell ) );
		results.wait_push( std::shared_ptr<sf::RectangleShape>( cfg->end_element) );
	}
	Log<paint_visitor>::get_logger().info("Painting ship finished");
}

pixel_coord paint_visitor::get_point_position(const point &p) const
{
	const paint_config* cfg = get_config<paint_config>();
	const pixel_coord top_left{
		cfg->begin.x + cfg->margin + cfg->padding,
		cfg->begin.y + cfg->margin + cfg->padding
	};

	if (p == point{0, 0}) return top_left;
	else return pixel_coord{
			round( top_left.x + (cfg->get_cell_width() * p.x) + (cfg->padding * ( p.x == 0ul ? 0.0f : 1.0f ) * ( p.x == 0ul ? 0.0f : p.x )), 2l ),
			round( top_left.y + (cfg->get_cell_height() * p.y) + (cfg->padding * ( p.y == 0ul ? 0.0f : 1.0f ) * ( p.y == 0ul ? 0.0f : p.y )), 2l )
		};
}