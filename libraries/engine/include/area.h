#pragma once

// Project includes
#include "ship.h"

// STL
#include <vector>

class area : 
	private Log<area>,
	public Visitable<area>
{
	using Log<area>::get_logger;
public:

	area(const unumber x_dim, const unumber y_dim, const unumber max_ship_count = 5ul, const std::vector<ship>& _ships = {});
	unumber count_alive() const;
	bool add_ship(const ship&);
	const std::vector<ship>& get_ships() const;
	std::vector<ship>& get_ships();
	void for_each_ship(std::function<void(ship&)>);

	// returns x dimension, y dimension and maximum number of ships
	std::tuple<unumber, unumber, unumber> get_params() const { return {x_dim, y_dim, max_ships}; }

	static bool shoot(area&, const point&);
	virtual bool accept( visits<area>* v ) override;

private:

	std::vector<ship> ships;

	unumber x_dim;
	unumber y_dim;
	unumber max_ships;
};