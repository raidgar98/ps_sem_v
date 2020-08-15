#pragma once

// Boost
#include <boost/core/demangle.hpp>


class visitor
{
	template<typename T>
	void visit(T* ptr) {  }
};

template<typename T>
class visitable : public T
{
public:

	void accept( visitor* v )
	{
		v->visit( this );
	}
};