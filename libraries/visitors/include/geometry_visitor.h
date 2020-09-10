#pragma once

// Project includes
#include "../../engine/include/point.h"
#include "../../patterns/include/visitor.hpp"
#include "../../configs/include/paint_config.h"

class geometry_visitor :
	public configurable
{
protected:
	geometry_visitor(paint_config& cnfig);

public:

	pixel_coord get_point_position(const point &p) const;
	static constexpr floating round(const floating n, const number digits = 2ul);
};