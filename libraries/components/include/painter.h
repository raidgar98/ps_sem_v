#pragma once

// Boost
#include <boost/thread/sync_queue.hpp>

// Project includes
#include "geometry_visitor.h"

// Project includes
#include "../../engine/include/ship.h"
#include "../../engine/include/area.h"
#include "../../engine/include/player.h"

template<typename T>
using threadsafe_collection_type = boost::concurrent::sync_queue<T>;
using result_collection_t = threadsafe_collection_type< std::shared_ptr<sf::RectangleShape> >;

struct paint_visitor: 
	private Log<paint_visitor>,
	public geometry_visitor,
	public visits<area>,
	public visits<ship>,
	public visits<player>
{	
	using Log<paint_visitor>::get_logger;

	paint_visitor( result_collection_t& res, paint_config& );

	// by default warn, if no overload for object detected
	template<class T>
	void paint(const T&) 
	{
		get_logger().warn("Painting for: `" + boost::typeindex::type_id<T>().pretty_name() + "` is not defined."); 
	}

	// override visitors for all supported paints
	virtual bool visit(ship* obj) override { require(obj); paint( *obj ); return true; }
	virtual bool visit(area* obj) override { require(obj); paint( *obj ); return true; }
	virtual bool visit(player* obj) override { require(obj); paint( *obj ); return true; }

protected:

	result_collection_t& results;

	std::shared_ptr<sf::RectangleShape> construct_cell( const point&, const sf::Vector2f&, const sf::Color&, const sf::Color& ) const;

	void paint(const area&);
	void paint(const ship&);
	void paint(const player&);

};

