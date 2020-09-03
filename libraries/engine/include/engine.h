#pragma once

// Project includes
#include "round_manager.hpp"
#include "player.h"

class engine : Log<engine>
{
	using players_container_t = std::vector<player>;
	using ship_round_manager_t = round_manager<players_container_t>;
	using round_manager_iterator_t = ship_round_manager_t::round_iterator;

public:
	// takes ready players, with setted ships
	engine(const players_container_t &);

	// perform shoot
	bool shoot(const point &);

	// checks win
	bool win() const;

	// switches players, returns false if shoot wasn't performed or if win occurs
	bool next_turn();

	// returns current player
	const player& current() const;
	player& current();
	player& next();

protected:

	players_container_t players;
	ship_round_manager_t manager;
	round_manager_iterator_t current_player;

	bool shoot_performed = false;
};