#pragma once

// STL
#include <atomic>

// SFML
#include <SFML/Graphics.hpp>

// Project Includes
#include "base_view.hpp"
#include "../../visitors/include/click_visitor.h"
#include "../../engine/include/engine.h"
#include "../../engine/include/area.h"


class board_view : 
	private Log<board_view>,
	public base_view
{
	using Log<board_view>::get_logger;
public:

	board_view(paint_visitor&, click_detection_visitor&, engine&);

	// returns true, if click happend on this component
	bool handle_click();

protected:

	virtual void __process( const paint_config* cnf = nullptr ) override;
	click_detection_visitor& _clicker;
	engine& eng;

private:

	void setup_click_visitor();
	void setup_paint_visitor();
	void setup_engine();

};