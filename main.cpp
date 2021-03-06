// STL
#include <future>
#include <atomic>

// SFML
#include <SFML/Graphics.hpp>

// Project Includes
#include "libraries/components/include/board_view.h"
#include "libraries/network/include/network.h"

auto& get_logger() { struct main_function : public Log<main_function> {}; return  main_function::get_logger(); }

int main()
{
	network_response_queue::set( new network_response_queue::value_type() );
	network_request_queue::set( new network_request_queue::value_type() );
	network net;

	get_logger() << "setted up test objects";
	auto _ = net.start_networking();
	get_logger() << "networking started";

	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 4;

	paint_config config;
	config.ship_cols = width + 1;
	config.ship_rows = height + 1;
	config.max_ships = max_ships;
	config.begin = pixel_coord(10.0f, 10.0f);

	sf::RenderWindow window(sf::VideoMode(config.area_width + 100, config.area_height + 100), "Ship game");
	sf::Font fnt; require( fnt.loadFromFile( "/opt/idea/jbr/lib/fonts/FiraCode-Retina.ttf" ) );
	sf::Text loading_caption{ sf::String( L"Loading. Please Wait..." ), fnt };
	loading_caption.setPosition({ 100.0f, 100.0f });

	window.clear();
	window.draw( loading_caption );
	window.display();

	result_collection_t results;
	paint_visitor pvisit{results, config};
	click_detection_visitor cdvisit{config};

	std::vector<base_view*> views{{
		new board_view{&config, pvisit, cdvisit}
	}};

	std::atomic_bool is_click_handled;
	is_click_handled.store(false);

	window.setFramerateLimit(20);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (
				event.type == sf::Event::MouseButtonPressed and 
				event.mouseButton.button == sf::Mouse::Button::Left and 
				not is_click_handled.load()
			)
			{
				is_click_handled.store(true);
				std::future<void> _ = std::async(std::launch::async, [&]() -> void {
					
					cdvisit.click = window.mapPixelToCoords(
						sf::Vector2i{
							event.mouseButton.x, 
							event.mouseButton.y
						}
					);

					for(base_view* bv : views)
						if( bv->handle_click() ) break;

					is_click_handled.store(false);
				});
			}
		}

		std::future<void> ret{std::async(std::launch::async, [&]() -> void {
			
			for(base_view* bv : views)
				bv->render();

			results.push(nullptr); // finished render
		})};

		window.clear();
		int i = 0;
		while(i < 2)
		{
			std::shared_ptr<sf::RectangleShape> shape;
			results.wait_pull(shape);

			if (shape == nullptr) i += 1;
			else
			{
				i = 0;
				window.draw(*shape);
			}
		}
		window.display();
	}

	net.stop_networking();
	return 0;
}