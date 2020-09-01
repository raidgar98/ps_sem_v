// STL
#include <future>

// SFML
#include <SFML/Graphics.hpp>

// Project Includes
#include "libraries/components/include/painter.h"
#include "libraries/components/include/click_detector.h"
#include "libraries/engine/include/engine.h"
#include "libraries/engine/include/area.h"

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
		ship{point{7,0}, point{7, 10}}}};

	const std::vector<area> init_correct_areas{
		{area{width, height, max_ships, ship_collection_1},
		area{width, height, max_ships, ship_collection_2}}};

	paint_config config;
	config.ship_cols = width + 1;
	config.ship_rows = height + 1;
	config.begin = pixel_coord( 10.0f, 10.0f );

	engine eng{ init_correct_areas };

	result_collection_t results;
	paint_visitor pvisit{ results, config };
	click_detection_visitor cdvisit{ config };
	cdvisit.ship_callback = [&](ship* s, const point& p, const pixel_coord& pc)
	{
		if(area::shoot( eng.current(), p )) 
		{
			Log<engine>::get_logger() << "shot success";
			eng.next_turn();
		}
		else
		{
			Log<engine>::get_logger() << "shot failed";
		}
	};

	sf::RenderWindow window(sf::VideoMode(config.area_width + 100, config.area_height + 100), "Ship game");

	// sf::CircleShape shape(100.f);
	// shape.setFillColor(sf::Color::Green);
	window.setFramerateLimit(20);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if( event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left )
			{
				std::future<void> _ = std::async( std::launch::async, [&]()->void
				{
					cdvisit.click = window.mapPixelToCoords( sf::Vector2i{event.mouseButton.x,event.mouseButton.y} );
					eng.current().accept( &cdvisit );
				});
			}
		}

		const unumber end_count = 1 + [&]() -> unumber { 
			unumber ret = 0;
			for(const auto& v : eng.current().get_ships())
				ret += v.length();
			return ret;
		}();

		std::future<void> ret{ std::async( std::launch::async, [&]() -> void {
			eng.current().accept( &pvisit );
		})};

		window.clear();

		for(int i = 0; i < end_count;)
		{
			std::shared_ptr<sf::RectangleShape> shape;
			results.wait_pull(shape);

			if(shape == nullptr) i+=1;
			else window.draw(*shape);
		}
		window.display();
	}

	return 0;
}