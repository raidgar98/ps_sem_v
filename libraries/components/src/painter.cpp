#include "../include/painter.hpp"

paint_visitor::paint_visitor(result_collection_t &res, paint_config &cnfig)
	: geometry_visitor{cnfig}, results{res} {}

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
		const pixel_coord coord{ get_point_position(p) };
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