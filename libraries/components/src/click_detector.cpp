#include "../include/click_detector.h"

bool click_detection_visitor::detect_collision(const pixel_coord &p1, const pixel_coord &p2) const
{
	const floating ship_width{ get_config<paint_config>()->get_cell_width() };
	const floating ship_height{ get_config<paint_config>()->get_cell_height() };
	const sf::Rect<floating> ship{p1, { std::abs(p2.x - p1.x) + ship_width, std::abs(p2.y - p1.y) + ship_height }};
	return ship.contains( click );
}

click_detection_visitor::click_detection_visitor( paint_config& cfg )
	:geometry_visitor{ cfg } {}

bool click_detection_visitor::visit(ship *obj)
{
	require(obj);
	if(detect_collision(get_point_position(obj->get_p1()), get_point_position(obj->get_p2())))
	{
		for(const point& p : *point::points_on_distance(obj->get_p1(), obj->get_p2()))
		{
			const pixel_coord _p = get_point_position(p);
			if( detect_collision( _p, _p ) )
			{
				Log<click_detection_visitor>::get_logger().info("click detected!");
				this->ship_callback(obj, p, _p);
			}
		}
	}
	return false;
}

bool click_detection_visitor::visit(area *obj)
{
	require(obj);

	const paint_config* cfg = get_config<paint_config>();
	return detect_collision( cfg->begin, pixel_coord{ cfg->begin.x + cfg->area_width, cfg->begin.y + cfg->area_height } );
}

