#pragma once

//Project includes
#include "geometry_visitor.h"

// Project includes
#include "../../engine/include/ship.h"
#include "../../engine/include/area.h"

class click_detection_visitor : 
	public Log<click_detection_visitor>,
	public geometry_visitor,
	public visits<ship>,
	public visits<area>	
{
public:

	pixel_coord click;
	std::function<void(ship*, const point&, const pixel_coord&)> ship_callback;

	explicit click_detection_visitor( paint_config& );
	virtual bool visit(ship *obj) override;
	virtual bool visit(area *obj) override;

protected:

	bool detect_collision(const pixel_coord &p1, const pixel_coord &p2) const;
};