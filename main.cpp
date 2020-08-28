// STL
#include <future>

// SFML
#include <SFML/Graphics.hpp>

// Project Includes
#include "libraries/components/include/painter.hpp"
#include "libraries/engine/include/engine.h"
#include "libraries/engine/include/area.h"

int main()
{
	constexpr unumber width = 10;
	constexpr unumber height = 10;
	constexpr unumber max_ships = 2;

	const std::vector<ship> ship_collection_1{
		{ship{point{1, 1}, point{5, 1}},
		ship{point{1, 4}, point{5, 4}}}};

	const std::vector<ship> ship_collection_2{
		{ship{point{1, 6}, point{5, 6}},
		ship{point{1, 8}, point{5, 8}}}};

	const std::vector<area> init_correct_areas{
		{area{width, height, max_ships, ship_collection_1},
		area{width, height, max_ships, ship_collection_2}}};

	paint_config config;
	config.ship_cols = width + 1;
	config.ship_rows = height + 1;

	result_collection_t results;
	paint_visitor pvisit{ results, config };

	engine eng{ init_correct_areas };

	sf::RenderWindow window(sf::VideoMode(config.area_width + 100, config.area_height + 100), "Ship game");

	// sf::CircleShape shape(100.f);
	// shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		const unumber end_count = 1 + [&]() -> unumber { 
			unumber ret = 0;
			for(const auto& v : eng.current().get_ships())
				ret += v.length();
			return ret;
		}();

		std::future<void> ret{ std::async( std::launch::async, [&]() -> void {
			eng.current().accept( &pvisit );
		})};

		for(int i = 0; i < end_count;)
		{
			std::shared_ptr<sf::RectangleShape> shape;
			results.wait_pull(shape);

			if(shape == nullptr)
			{
				i+=1;
				Log<engine>::get_logger() << std::to_string(i) + " / " + std::to_string(end_count);
			}
			else
			{
				window.draw(*shape);
				// window.display();
			}
		}
		window.display();

	}

	return 0;
}