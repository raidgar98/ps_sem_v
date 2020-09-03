#include "../include/player.h"

player::player(const area &a) : board{a} {}

area &player::get_area() { return board; }

const area &player::get_area() const { return board; }

const player::player_tries_collection_t &player::get_player_tries() const { return player_tries; }

bool player::shoot(player& pl, const point & p)
{
	if( player_tries.find( player_try{ p, true } ) != player_tries.end() ) return false;
	const bool success = area::shoot( pl.board, p );
	player_tries.insert( player_try{ p, success } );
	return success;
}

bool player::accept(visits<player>* v)
{
	return v->visit( this );
}