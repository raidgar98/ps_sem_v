#pragma once

// Project includes
#include "../../logger/include/logger.h"
#include "../../patterns/include/visitor.hpp"
#include "../../visitors/include/paint_visitor.h"


class base_view :
	private Log<base_view>,
	protected configurable
{
	using Log<base_view>::get_logger;
public:

	void render( const paint_config* cnf = nullptr ) { __process(cnf); }

	// returns true, if click happend on this component
	virtual bool handle_click() { return false; }
	virtual ~base_view() {}

protected:

	// this method, when called, should use paint_visitor to render objects. 
	// Implementation should be thread safe
	// if cnf == nullptr, rendering process should use already choosen config in paint visitor
	virtual void __process( const paint_config* cnf = nullptr ) = 0;
	base_view(const paint_config* cfg, paint_visitor&);

	paint_visitor& _painter;
};