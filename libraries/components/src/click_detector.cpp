#include "../include/click_detector.h"

bool click_detection_visitor::detect_collision(const pixel_coord &p1, const pixel_coord &p2) const
{
	const paint_config *cfg{get_config<paint_config>()};
	const floating ship_width{cfg->get_cell_width()};
	const floating ship_height{cfg->get_cell_height()};
	const sf::Rect<floating> ship{
		{p1.x + cfg->margin, p1.y + cfg->margin},
		{std::abs(p2.x - p1.x) + ship_width - cfg->margin, std::abs(p2.y - p1.y) + ship_height - cfg->margin}};
	return ship.contains(click);
}

click_detection_visitor::click_detection_visitor(paint_config &cfg)
	: geometry_visitor{cfg} {}

bool click_detection_visitor::visit(ship *obj)
{
	require(obj);
	if (detect_collision(get_point_position(obj->get_p1()), get_point_position(obj->get_p2())))
	{
		for (const point &p : *point::points_on_distance(obj->get_p1(), obj->get_p2()))
		{
			const pixel_coord _p = get_point_position(p);
			if (detect_collision(_p, _p))
			{
				get_logger().info("click on ship detected!");
				return this->ship_callback(obj, p, _p);
			}
		}
	}
	return false;
}

bool click_detection_visitor::visit(player *obj)
{
	const paint_config *cfg{get_config<paint_config>()};
	const number x = (-0.5f) + (this->click.x - cfg->begin.x - cfg->margin) / cfg->get_cell_width();
	const number y = (-0.5f) + (this->click.y - cfg->begin.y - cfg->margin) / cfg->get_cell_height();
	const auto [_width, _height, __] = obj->get_area().get_params();
	if (
		(x < 0 or y < 0) or
		(x > _width or y > _height)
	) return false;
	const point ret{
		static_cast<unumber>(x),
		static_cast<unumber>(y)
	};
	return this->ship_callback(nullptr, ret, get_point_position(ret));
}

bool click_detection_visitor::visit(area *obj)
{
	require(obj);

	const paint_config *cfg = get_config<paint_config>();
	return detect_collision(
		pixel_coord{cfg->begin.x + cfg->margin, cfg->begin.y + cfg->margin}, 
		pixel_coord{cfg->begin.x + cfg->area_width - cfg->margin, cfg->begin.y + cfg->area_height - cfg->margin}
	);
}
