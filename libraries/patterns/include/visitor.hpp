#pragma once

// DOUBLE CRTP COMBO !!! 
// Where is your Java and C# now?

// STL
#include <cassert>
#include <memory>

// Boost
#include <boost/core/demangle.hpp>

// Project includes
#include "../../logger/include/logger.h"

template<typename T>
class visits : private Log< visits<T> >
{
public:
	// default visitor (throw error)
	virtual bool visit(T * ptr) 
	{ 
		Log<visits<T>>::get_logger().error("Empty visit, by: `" + boost::typeindex::type_id<T>().pretty_name() + "`." );
		assert(false);
	}
};

template<class T >
class Visitable : private Log< Visitable < T > >
{
public:

	virtual bool accept( visits<T>* v )
	{
		Log< Visitable < T > >::get_logger().info( "Accepted: `" + boost::typeindex::type_id<T>().pretty_name() + "`." );
		return v->visit( dynamic_cast<T*>(this) );
	}
};