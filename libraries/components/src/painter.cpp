#include "../include/painter.h"

paint_visitor::paint_visitor(result_collection_t &res, paint_config &cnfig)
	: geometry_visitor{cnfig}, results{res} {}

void paint_visitor::paint(const area &obj)
{
	get_logger().info("Painting area started");
	const paint_config *cfg = get_config<paint_config>();
	sf::RectangleShape *board = new sf::RectangleShape{};

	board->setPosition({cfg->begin.x, cfg->begin.y});
	board->setSize({cfg->area_width, cfg->area_height});
	board->setFillColor(cfg->area_color);
	board->setOutlineColor(cfg->area_outline_color);
	board->setOutlineThickness(cfg->outline_width);

	results.wait_push(std::make_shared<sf::RectangleShape>(*board));
	const floating cell_width{cfg->get_cell_width()};
	const floating cell_height{cfg->get_cell_height()};
	const auto [_width, _height, _max_ships] = obj.get_params();
	const floating margin = 2.0f * cfg->margin;

	for(unumber i = 0; i <= _width; i++)
	{
		const pixel_coord start = get_point_position(point{ i, 0 });
		sf::RectangleShape *grid_x = new sf::RectangleShape{};
		grid_x->setPosition( start );
		grid_x->setSize( pixel_coord{ cell_width, cfg->area_height - margin } );
		grid_x->setFillColor( sf::Color::Transparent );
		grid_x->setOutlineColor(sf::Color::Black);
		grid_x->setOutlineThickness(cfg->padding);
		results.wait_push(std::shared_ptr<sf::RectangleShape>{grid_x});
	}

	for(unumber i = 0; i <= _height; i++)
	{
		const pixel_coord start = get_point_position(point{ 0, i });
		sf::RectangleShape *grid_y = new sf::RectangleShape{};
		grid_y->setPosition( start );
		grid_y->setSize( pixel_coord{ cfg->area_width - margin, cell_height } );
		grid_y->setFillColor( sf::Color::Transparent );
		grid_y->setOutlineColor(sf::Color::Black);
		grid_y->setOutlineThickness(cfg->padding);
		results.wait_push(std::shared_ptr<sf::RectangleShape>{grid_y});
	}

	results.wait_push(std::shared_ptr<sf::RectangleShape>(cfg->end_element));
	get_logger().info("Painting area finished");
}

void paint_visitor::paint(const ship &obj)
{
	get_logger().info("Painting ship started");
	const paint_config *cfg = get_config<paint_config>();
	std::unique_ptr<std::vector<point>> points_to_paint{point::points_on_distance(obj.get_p1(), obj.get_p2())};
	const floating cell_width{cfg->get_cell_width()};
	const floating cell_height{cfg->get_cell_height()};
	const sf::Color ship_color{cfg->get_ship_color()};

	for (point &p : *points_to_paint)
	{
		// get_logger().info("Painting ship in progress...");
		results.wait_push(construct_cell(
			p,
			pixel_coord{cell_width, cell_height},
			(obj.segment_alive(p) ? ship_color : sf::Color::Red),
			cfg->ship_outline_color));
		results.wait_push(std::shared_ptr<sf::RectangleShape>(cfg->end_element));
	}
	get_logger().info("Painting ship finished");
}

void paint_visitor::paint(const player &obj)
{
	get_logger().info("Painting palyer started");

	const paint_config *cfg = get_config<paint_config>();
	const player::player_tries_collection_t &points_to_paint{obj.get_player_tries()};
	const floating cell_width{cfg->get_cell_width()};
	const floating cell_height{cfg->get_cell_height()};

	for(const player_try& p : points_to_paint)
	{
		results.wait_push(construct_cell(
			p.shoot_try,
			pixel_coord{cell_width, cell_height},
			(p.positive ? cfg->cell_hitted : cfg->cell_missed ),
			cfg->ship_outline_color
		));
		results.wait_push(std::shared_ptr<sf::RectangleShape>(cfg->end_element));
	}

	get_logger().info("Painting player finished");
}

std::shared_ptr<sf::RectangleShape> paint_visitor::construct_cell(const point &p, const sf::Vector2f &size, const sf::Color &fill_color, const sf::Color &outline_color) const
{
	const pixel_coord coord{get_point_position(p)};
	sf::RectangleShape *cell = new sf::RectangleShape{};

	cell->setPosition({coord.x, coord.y});
	cell->setSize(size);
	cell->setFillColor(fill_color);
	cell->setOutlineColor(outline_color);
	cell->setOutlineThickness(get_config<paint_config>()->outline_width);

	return std::shared_ptr<sf::RectangleShape>{cell};
}