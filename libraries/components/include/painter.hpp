#pragma once

// Boost
#include <boost/thread/sync_queue.hpp>

// Project includes
#include "paint_config.h"
#include "../../logger/include/logger.h"
#include "../../patterns/include/visitor.hpp"

// Project includes
#include "../../engine/include/point.h"
#include "../../engine/include/ship.h"
#include "../../engine/include/area.h"

template<typename T>
using threadsafe_collection_type = boost::concurrent::sync_queue<T>;
using result_collection_t = threadsafe_collection_type< std::shared_ptr<sf::RectangleShape> >;

struct paint_visitor: 
	protected Log<paint_visitor>,
	public visits<area>,
	public visits<ship>
{	
	paint_visitor( result_collection_t& res, const paint_config& = paint_config() );

	// by default warn, if no overload for object detected
	template<class T>
	void paint(const T&) 
	{
		Log<paint_visitor>::get_logger().warn("Painting for: `" + boost::typeindex::type_id<T>().pretty_name() + "` is not defined."); 
	}

	void paint(const area&);
	void paint(const ship&);

	// override visitors for all supported paints
	virtual void visit(ship* obj) override { require(obj); paint( *obj ); results.wait_push( std::shared_ptr<sf::RectangleShape>( config.end_element) ); }
	virtual void visit(area* obj) override { require(obj); paint( *obj ); results.wait_push( std::shared_ptr<sf::RectangleShape>( config.end_element) ); }

protected:

	result_collection_t& results;
	paint_config config;
	pixel_coord get_point_position(const point&) const;
};

