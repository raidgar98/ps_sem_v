#pragma once

// Project includes
#include "area.h"

// STL
#include <set>

struct player_try
{
	point shoot_try;
	bool positive;

	inline friend bool operator<(const player_try& p1, const player_try& p2) { return p1.shoot_try < p2.shoot_try; }
};



class player : 
	public Log<player>,
	public Visitable<player>
{
public:
	using player_tries_collection_t = std::set<player_try>;
private:

	area board;
	player_tries_collection_t player_tries;

public:

	enum class shoot_type : int
	{
		CORRECT = 0,
		MISS = 1,
		ERROR = 2
	};

	player(const area&, const bool = false);

	area& get_area();

	const area& get_area() const;
	const player_tries_collection_t& get_player_tries() const;

	shoot_type shoot(player&, const point&);
	bool is_shoot_possible(const point&) const;
	shoot_type accept_shoot(const point&, const bool);

	virtual bool accept(visits<player>*);

	bool is_online = false;
};