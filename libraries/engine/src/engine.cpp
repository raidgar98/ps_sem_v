#include "../include/engine.h"

// Project includes
#include "../../network/include/network_actions.hpp"

engine::engine(const players_container_t &_players)
	: players{
		  _players.begin(),
		  _players.end()}, // deep copy
	  manager{players, [](const players_container_t &vec) -> bool {
				  return std::count_if(vec.begin(), vec.end(), [](const player &_a) { return _a.get_area().count_alive() >= 1; }) == 1;
			  }},
	  current_player{manager.begin()}
{
	require(players.size() > 0);
	require(not manager.is_win(players));
	const auto [width, height, max_ships] = players[0].get_area().get_params();

	for (const player &a : players)
	{
		const auto [_width, _height, _max_ships] = a.get_area().get_params();
		require(width == _width);
		require(height == _height);
		require(max_ships == _max_ships);
		require(a.get_player_tries().size() == 0);
	}
}

bool engine::shoot(const point &_p)
{

	if (shoot_performed)
		return false;

	// online mode
	if ((*(current_player).next()).is_online or (*(current_player)).is_online )
	{
		if( not (*current_player).is_shoot_possible(_p))
		{
			get_logger() << "shot is not possible";
			return false;
		}
		std::thread th{ handle_shoot( *(current_player).next() ) };

		web::json::value to_send = web::json::value::object();
		to_send["x"] = web::json::value::number(_p.x);
		to_send["y"] = web::json::value::number(_p.y);

		network_command command{
			[&to_send](const web::json::value &) -> web::json::value {
				get_logger() << "Sending: " + to_send.serialize();
				return to_send;
			},
			network_command::TO_SEND};
		const auto id = command.id;
		network_request_queue::get().push(command);
		network_result val = network_response_queue::get().pull();
		while(id != val.id) val = network_response_queue::get().pull();
		th.join();
		const player::shoot_type st = static_cast<player::shoot_type>(val.data.as_object().at("shoot_type").as_integer());
		if (st != player::shoot_type::ERROR)
		{
			shoot_performed = true;
			(*current_player).accept_shoot( _p, st == player::shoot_type::CORRECT );
			return true;
		}
		return false;
	}

	// offline mode
	player::shoot_type result = (*current_player).shoot((*(current_player).next()), _p);
	if (result == player::shoot_type::ERROR)
		return false;
	else
	{
		shoot_performed = true;
		return true;
	}
}

std::thread engine::handle_shoot(player& pl)
{
	return std::thread([&]() {
		network_command command{
			[&](const web::json::value &incoming) -> web::json::value {
				get_logger() << "Got: " + incoming.serialize();

				point _p{
					incoming.as_object().at("x").as_number().to_uint64(),
					incoming.as_object().at("y").as_number().to_uint64()
				};

				web::json::value response = web::json::value::object();
				response["shoot_type"] = web::json::value::number( static_cast<int>( 
					( pl.get_area().shoot(_p) ? player::shoot_type::CORRECT : player::shoot_type::MISS )
				) );

				get_logger() << "Sending: " + response.serialize();
				return response;
			},
			network_command::TO_RECIVE
		};
		const auto id = command.id;
		network_request_queue::get().push(command);
	});
}

bool engine::win() const
{
	return manager.is_win(players);
}

bool engine::next_turn()
{
	if (not shoot_performed)
		return false;
	shoot_performed = false;
	current_player++;
	return current_player != manager.end();
}

const player &engine::current() const
{
	return current_player.get();
}

player &engine::current()
{
	return *current_player;
}

player &engine::next()
{
	return *(current_player.next());
}