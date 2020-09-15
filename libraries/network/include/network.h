#pragma once

// STL
#include <memory>
#include <future>
#include <atomic>

// submodules
#define _TURN_OFF_PLATFORM_STRING
#include "../../cpprestsdk/Release/include/cpprest/http_listener.h"
#include "../../cpprestsdk/Release/include/cpprest/http_client.h"

// Project includes
#include "../../logger/include/logger.h"
#include "network_actions.hpp"

class network : 
	private Log<network>
{
	inline static uint16_t __service_port{ 12'000 };

	std::unique_ptr<web::http::client::http_client> client;
	std::unique_ptr<web::http::experimental::listener::http_listener> server;

	std::atomic_bool _run = ATOMIC_BOOL_LOCK_FREE;

protected:

	void send(network_command job) noexcept;
	void recive(network_command job) noexcept;

public:

	std::future<void> start_networking();
	void stop_networking();
};