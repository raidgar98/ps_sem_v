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

	enum shoot_type
	{
		CORRECT,
		MISS,
		ERROR
	};

	player(const area&);

	area& get_area();

	const area& get_area() const;
	const player_tries_collection_t& get_player_tries() const;

	shoot_type shoot(player&, const point&);

	virtual bool accept(visits<player>*);
};