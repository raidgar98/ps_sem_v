#pragma once

//Project includes
#include "geometry_visitor.h"

// Project includes
#include "../../engine/include/ship.h"

class click_detection_visitor : public Log<click_detection_visitor>,
								public geometry_visitor,
								public visits<ship>
{
public:
	const pixel_coord click;
	virtual bool visit(ship *obj) override
	{
		require(obj);
		return detect_collision(get_point_position(obj->get_p1()), get_point_position(obj->get_p2()));
	}

private:
	bool detect_collision(const pixel_coord &p1, const pixel_coord &p2) const;
};