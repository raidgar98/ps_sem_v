#include "../include/engine.h"

engine::engine(const players_container_t& _players)
	:	players{ 
			_players.begin(), 
			_players.end() 
		}, // deep copy
		manager{ 
			players,
			[]( const players_container_t& vec ) -> bool 
			{
				return std::count_if(vec.begin(), vec.end(), [](const area &_a) { return _a.count_alive() >= 1; }) == 1;
			}
		}, 
		current_player{
			manager.begin()
		}
{
	require( players.size() > 0 );
	require( not manager.is_win(players) );
	const auto [ width, height, max_ships ] = players[0].get_params();

	for(const area& a : players)
	{
		const auto [ _width, _height, _max_ships ] = a.get_params();
		require( width == _width );
		require( height == _height );
		require( max_ships == _max_ships );
	}
}

bool engine::shoot(const point& _p)
{
	if( shoot_performed ) return false;
	shoot_performed = true;
	area::shoot( *current_player, _p );
	return true;
}

bool engine::win() const
{
	return manager.is_win( players );
}

bool engine::next_turn()
{
	if( not shoot_performed ) return false;
	current_player++;
	return current_player != manager.end();
}

const area& engine::current() const
{
	return current_player.get();
}

area& engine::current()
{
	return *current_player;
}