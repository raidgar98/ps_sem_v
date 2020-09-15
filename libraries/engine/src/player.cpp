#include "../include/player.h"

player::player(const area &a, const bool _online) : board{a}, is_online{_online} {}

area &player::get_area() { return board; }

const area &player::get_area() const { return board; }

const player::player_tries_collection_t &player::get_player_tries() const { return player_tries; }

player::shoot_type player::shoot(player& pl, const point & p)
{
	if( is_shoot_possible(p) ) return shoot_type::ERROR;
	return accept_shoot( p, pl.board.shoot(p) );
}

bool player::is_shoot_possible(const point& p) const
{
	return player_tries.find( player_try{ p, true } ) == player_tries.end();
}

player::shoot_type player::accept_shoot(const point& p, const bool success)
{
	player_tries.insert( player_try{ p, success } );
	return success ? shoot_type::CORRECT : shoot_type::MISS;
}

bool player::accept(visits<player>* v)
{
	return v->visit( this );
}