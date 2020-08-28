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

using render_collection_t = threadsafe_collection_type<Visitable<>>;
using result_collection_t = threadsafe_collection_type<sf::Drawable>;

struct paint_visitor: 
	protected Log<paint_visitor>,
	public abstract_visitor
{	
	paint_visitor( render_collection_t& input, result_collection_t& output, const paint_config& = paint_config() );

	// one visitor for all paints
	template<class T>
	void visit(const T* obj) { require(obj); paint( *obj ); }

	// painting methodes
	template<class T>
	void paint(const T&) 
	{
		log.warn("Painting for: `" + boost::typeindex::type_id<T>().pretty_name() + "` not defined."); 
	}

private:

	paint_config config;

	pixel_coord get_point_position(const point& sh) const;
};