#pragma once

// Boost
#include <boost/core/demangle.hpp>


class abstract_visitor
{
public:
	// default visitor (do nothing)
	template<typename T>
	void visit(T * ptr) {  }
};

template<class minimum_visitor = abstract_visitor>
class Visitable
{
public:

	virtual void accept( minimum_visitor* v )
	{
		v->visit( this );
	}
};