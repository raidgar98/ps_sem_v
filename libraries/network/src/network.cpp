#include "../include/network.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental;

void network::send(network_command job) noexcept
{
	client.reset(new http_client{uri{"http://localhost:" + std::to_string(__service_port)}});
	http_request req;
	req.set_method(methods::POST);
	req.set_body(job.data(web::json::value::null()));
	client->request(req).then([&](http_response resp) -> void {
							// require(resp.status_code() == 200, ("invalid status code. Expcted 200, " + std::to_string(resp.status_code()) + " received.").c_str());
							resp.extract_json().then([&](pplx::task<json::value> task)
							{
								network_response_queue::value_type& que = network_response_queue::get();
								if(not job.ignore_result) que.push(network_result{task.get(), job.id, network_result::ORIG::SEND_RESPONSE});
							}).wait();
						}).wait();
	
	client.reset(nullptr);
}

void network::recive(network_command job) noexcept
{
	server.reset(new listener::http_listener{uri{"http://0.0.0.0:" + std::to_string(__service_port)}});
	server->support(methods::POST, [&, job](http_request req) -> void {
		req.extract_json(true) .then([&](pplx::task<json::value> task)
		{
			network_response_queue::value_type& que = network_response_queue::get();
			const auto gathered_data = task.get();
			if(not job.ignore_result) que.push(network_result{gathered_data, job.id, network_result::ORIG::RECEIVED});

			if(!job.data(gathered_data).is_null())
			{
				req.reply(200, job.data(gathered_data)).wait();
			}
		}).wait();
		server->close();
	});
	server->open();
}

std::future<void> network::start_networking()
{
	_run.store(true);
	return std::async(std::launch::async, [&]() {
		while (_run.load())
		{
			network_request_queue::value_type &que = network_request_queue::get();
			network_command comm = que.pull();

			if(comm.destination == network_command::TO_SEND) auto _ = std::async(std::launch::async, [=]() { send(comm); });
			else if(comm.destination == network_command::TO_RECIVE) auto _ = std::async(std::launch::async, [=]() { recive(comm); });
			else require(false, "undefined behaivour");
		}
	});
}

void network::stop_networking()
{
	_run.store(false);
}