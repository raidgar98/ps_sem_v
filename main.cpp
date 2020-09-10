// STL
#include <future>
#include <atomic>

// SFML
#include <SFML/Graphics.hpp>

// Project Includes
#include "libraries/components/include/board_view.h"

auto& get_logger() { struct main_function : public Log<main_function> {}; return  main_function::get_logger(); }

int main()
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 4;

	const std::vector<ship> ship_collection_1{
		{ship{point{0, 0}, point{0, 10}},
		 ship{point{1, 0}, point{1, 10}},
		 ship{point{3, 4}, point{6, 4}},
		 ship{point{10, 0}, point{10, 10}}}};

	const std::vector<ship> ship_collection_2{
		{ship{point{3, 0}, point{3, 10}},
		 ship{point{7, 0}, point{7, 10}}}};

	const std::vector<player> init_correct_areas{
		{player{area{width, height, max_ships, ship_collection_1}},
		 player{area{width, height, max_ships, ship_collection_2}}}};

	paint_config config;
	config.ship_cols = width + 1;
	config.ship_rows = height + 1;
	config.begin = pixel_coord(10.0f, 10.0f);

	engine eng{init_correct_areas};

	result_collection_t results;
	paint_visitor pvisit{results, config};
	click_detection_visitor cdvisit{config};

	std::atomic_bool is_click_handled;
	is_click_handled.store(false);

	board_view bv{pvisit, cdvisit, eng};

	sf::RenderWindow window(sf::VideoMode(config.area_width + 100, config.area_height + 100), "Ship game");

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

					bv.handle_click();

					is_click_handled.store(false);
				});
			}
		}

		std::future<void> ret{std::async(std::launch::async, [&]() -> void {
			
			bv.render();
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

	return 0;
}