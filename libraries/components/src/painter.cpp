#include "../include/painter.hpp"

constexpr floating round(const floating n, const number digits = 2ul)
{
	const long long int ret = std::pow<floating, number>( 10.0f, digits ) * n;
	return static_cast<floating>(ret) / std::pow<floating, number>( 10.0f, digits );
};

paint_visitor::paint_visitor(result_collection_t &res, const paint_config &cfg)
	: results{res}, config{cfg} {}

void paint_visitor::paint(const area &obj)
{
	Log<paint_visitor>::get_logger().info("Painting area started");

	sf::RectangleShape* board = new sf::RectangleShape{};
	board->setPosition({config.begin.x, config.begin.y});
	board->setSize({ config.area_width, config.area_height });
	board->setFillColor( config.area_color );
	board->setOutlineColor( config.area_outline_color );
	board->setOutlineThickness( config.outline_width );

	Log<paint_visitor>::get_logger().info("Painting area finished");
	results.wait_push( std::make_shared<sf::RectangleShape>( *board ) );
	results.wait_push( std::shared_ptr<sf::RectangleShape>( config.end_element) );
}

void paint_visitor::paint(const ship &obj)
{
	Log<paint_visitor>::get_logger().info("Painting ship started");
	Log<paint_visitor>::get_logger() << obj;
	std::unique_ptr<std::vector<point>> points_to_paint{point::points_on_distance(obj.get_p1(), obj.get_p2())};
	const float cell_width{config.get_cell_width()};
	const float cell_height{config.get_cell_height()};
	const sf::Color ship_color{config.get_ship_color()};
	
	for (point &p : *points_to_paint)
	{
		const pixel_coord coord{get_point_position(p)};
		sf::RectangleShape* cell = new sf::RectangleShape{};
		cell->setPosition({coord.x, coord.y});
		cell->setSize({cell_width, cell_height});
		cell->setFillColor(ship_color);
		cell->setOutlineColor(config.ship_outline_color);
		cell->setOutlineThickness( config.outline_width );

		Log<paint_visitor>::get_logger().info("Painting ship in progress...");
		results.wait_push( std::make_shared<sf::RectangleShape>( *cell ) );
		results.wait_push( std::shared_ptr<sf::RectangleShape>( config.end_element) );
	}
	Log<paint_visitor>::get_logger().info("Painting ship finished");
}

pixel_coord paint_visitor::get_point_position(const point &p) const
{
	const pixel_coord top_left{
		config.begin.x + config.margin + config.padding,
		config.begin.y + config.margin + config.padding
	};

	if (p == point{0, 0})
		return top_left;
	else
	{
		const floating padding_factor_x = ( p.x == 0ul ? 0.0f : 1.0f );
		const floating padding_factor_y = ( p.y == 0ul ? 0.0f : 1.0f );

		const floating padding_count_x = ( p.x == 0ul ? 0.0f : p.x );
		const floating padding_count_y = ( p.y == 0ul ? 0.0f : p.y );

		return pixel_coord{
			round( top_left.x + (config.get_cell_width() * p.x) + (config.padding * padding_factor_x * padding_count_x) ),
			round( top_left.y + (config.get_cell_height() * p.y) + (config.padding * padding_factor_y * padding_count_y) )
		};
	}
}