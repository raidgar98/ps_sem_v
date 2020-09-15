#pragma once

// STL
#include <functional>

// Boost
#include <boost/thread/sync_queue.hpp>

// submodules
#define _TURN_OFF_PLATFORM_STRING
#include "../../cpprestsdk/Release/include/cpprest/json.h"

// Project includes
#include "../../patterns/include/singleton.hpp"

using retrive_response_function_t = std::function<web::json::value(const web::json::value& v)>;

template<typename T>
struct network_action
{
	T data;
};

struct network_command : public network_action<retrive_response_function_t>
{
	enum DEST{ TO_SEND, TO_RECIVE };
	DEST destination;

	uint64_t id;
	bool ignore_result = false;
	network_command(retrive_response_function_t data, const DEST _D) : network_command{data, __id++, _D} {}

protected:

	network_command( retrive_response_function_t data, const uint64_t _id, const DEST _D) : network_action{data}, id{_id}, destination{_D} {}

private:
	inline static uint64_t __id{ 0ul };
};

struct network_result : public network_action<web::json::value>
{
	enum ORIG{ SEND_RESPONSE, RECEIVED };
	ORIG origin;

	uint64_t id;

	network_result( const web::json::value data, const uint64_t id, const ORIG _O)
		:network_action{data}, id{id}, origin{_O} {}
};

using sync_queue_network_req = boost::concurrent::sync_queue<network_command>;
class network_request_queue :
	public singleton<sync_queue_network_req, network_request_queue>
{};

using sync_queue_network_resp = boost::concurrent::sync_queue<network_result>;
class network_response_queue :
	public singleton<sync_queue_network_resp, network_response_queue>
{};