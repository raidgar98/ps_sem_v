#include "../include/board_view.h"

board_view::board_view(paint_visitor& pv, click_detection_visitor& cdv, engine& _eng)
	:base_view{ pv }, _clicker{cdv}, eng{_eng}
{
	setup_engine();
	setup_paint_visitor();
	setup_click_visitor();
}

bool board_view::handle_click()
{
	if (eng.current().get_area().accept(&_clicker))
	{
		bool _hit = false;
		for (ship &sh : eng.next().get_area().get_ships())
		{
			_hit = sh.accept(&_clicker);
			if (_hit)
				break;
		}

		if (not _hit)
		{
			_hit = eng.current().accept(&_clicker);
		}

		if (_hit) eng.next_turn();

		return true;
	}else return false;
}

void board_view::__process( const paint_config* cnf )
{
	if(cnf != nullptr) _painter.set_config(cnf);
	eng.current().get_area().accept(&_painter);
	eng.current().accept(&_painter);
	if(cnf != nullptr) _painter.set_config(get_config<paint_config>());
}

void board_view::setup_click_visitor()
{
	this->_clicker.ship_callback = [&](ship *s, const point &p, const pixel_coord &pc) {
		get_logger() << p;
		if (eng.shoot(p))
		{
			get_logger() << "shot success";
			return true;
		}
		else
		{
			get_logger() << "shot failed";
			return false;
		}
	};
}

void board_view::setup_paint_visitor()
{

}

void board_view::setup_engine()
{

}

