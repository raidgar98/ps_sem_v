#pragma once

// Project includes
#include "round_manager.hpp"
#include "area.h"

class engine : Log<engine>
{
public:

	engine(const unumber width, const unumber height, const unumber max_ships, const unumber players);
	bool shoot(const point&);
	bool win() const;
	void next_turn();

private:

	area* current_player{ nullptr };
	std::vector<area> players;

};