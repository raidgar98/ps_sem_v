#include "../include/board_view.h"

board_view::board_view(const paint_config* cfg, paint_visitor& pv, click_detection_visitor& cdv)
	:base_view{ cfg, pv }, _clicker{cdv}
{
	setup_engine(2ul);
	setup_paint_visitor();
	setup_click_visitor();
}

bool board_view::handle_click()
{
	if (eng->current().get_area().accept(&_clicker))
	{
		bool _hit = false;
		for (ship &sh : eng->next().get_area().get_ships())
		{
			_hit = sh.accept(&_clicker);
			if (_hit)
				break;
		}

		if (not _hit)
		{
			_hit = eng->current().accept(&_clicker);
		}

		if (_hit) eng->next_turn();

		return true;
	}else return false;
}

void board_view::__process( const paint_config* cnf )
{
	if(cnf != nullptr) _painter.set_config(cnf);
	eng->current().get_area().accept(&_painter);
	eng->current().accept(&_painter);
	if(cnf != nullptr) _painter.set_config(get_config<paint_config>());
}

void board_view::setup_click_visitor()
{
	this->_clicker.ship_callback = [&](ship *s, const point &p, const pixel_coord &pc) {
		get_logger() << p;
		if (eng->shoot(p))
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

void board_view::setup_engine(const unumber player_count)
{
	eng.reset(nullptr);
	const paint_config *cfg{ get_config<paint_config>() };
	init_visitor init;
	std::vector<player> players; players.reserve(player_count);

	for(int i = 0; i < player_count; i++)
	{
		area a{ 
			static_cast<unumber>(cfg->ship_rows) - 1ul, 
			static_cast<unumber>(cfg->ship_cols - 1ul), 
			cfg->max_ships
		};
		a.accept(&init);
		players.emplace_back( a );

		if(i >= 1)
		{
			players.back().is_online = true;
		}
	}

	eng = std::make_unique<engine>( players );
}
