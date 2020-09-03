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
				return std::count_if(vec.begin(), vec.end(), [](const player &_a) { return _a.get_area().count_alive() >= 1; }) == 1;
			}
		}, 
		current_player{
			manager.begin()
		}
{
	require( players.size() > 0 );
	require( not manager.is_win(players) );
	const auto [ width, height, max_ships ] = players[0].get_area().get_params();

	for(const player& a : players)
	{
		const auto [ _width, _height, _max_ships ] = a.get_area().get_params();
		require( width == _width );
		require( height == _height );
		require( max_ships == _max_ships );
		require( a.get_player_tries().size() == 0 );
	}
}

bool engine::shoot(const point& _p)
{
	if( shoot_performed ) return false;
	player::shoot_type result = ( *current_player ).shoot( (*(current_player).next()), _p );
	if(result == player::shoot_type::ERROR) return false;
	else
	{
		shoot_performed = true;
		return true;
	}
}

bool engine::win() const
{
	return manager.is_win( players );
}

bool engine::next_turn()
{
	if( not shoot_performed ) return false;
	shoot_performed = false;
	current_player++;
	return current_player != manager.end();
}

const player& engine::current() const
{
	return current_player.get();
}

player& engine::current()
{
	return *current_player;
}

player& engine::next()
{
	return *(current_player.next());
}