#pragma once

// Boost
#include <boost/thread/sync_queue.hpp>

// Project includes
#include "geometry_visitor.h"
#include "../../logger/include/logger.h"

// Project includes
#include "../../engine/include/point.h"
#include "../../engine/include/ship.h"
#include "../../engine/include/area.h"

template<typename T>
using threadsafe_collection_type = boost::concurrent::sync_queue<T>;
using result_collection_t = threadsafe_collection_type< std::shared_ptr<sf::RectangleShape> >;

struct paint_visitor: 
	protected Log<paint_visitor>,
	public configurable,
	public visits<area>,
	public visits<ship>
{	
	paint_visitor( result_collection_t& res, paint_config& );

	// by default warn, if no overload for object detected
	template<class T>
	void paint(const T&) 
	{
		Log<paint_visitor>::get_logger().warn("Painting for: `" + boost::typeindex::type_id<T>().pretty_name() + "` is not defined."); 
	}

	void paint(const area&);
	void paint(const ship&);

	// override visitors for all supported paints
	virtual void visit(ship* obj) override { require(obj); paint( *obj ); }
	virtual void visit(area* obj) override { require(obj); paint( *obj ); }

protected:

	result_collection_t& results;
	pixel_coord get_point_position(const point&) const;
};

