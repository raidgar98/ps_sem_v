#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Project includes
#include "../../types.hpp"

using pixel_number = floating;
using pixel_coord = sf::Vector2<floating>;

struct paint_config
{
	enum{
		FIXED,
		RANDOM
	} ship_color_type = paint_config::RANDOM;
	sf::Color ship_color;
	sf::Color ship_outline_color = sf::Color::Cyan;

	sf::Color area_color = sf::Color::White;
	sf::Color area_outline_color = sf::Color::Black;

	pixel_coord begin{ 100.0, 100.0 };

	pixel_number area_width{ 250.0 };
	pixel_number area_height{ 250.0 };

	pixel_number margin{ 5.0 };
	pixel_number padding{ 1.0 };
	pixel_number outline_width{ 0.25 };

	pixel_number ship_rows{ 20.0 };
	pixel_number ship_cols{ 20.0 };

	constexpr pixel_number get_cell_width() const;
	constexpr pixel_number get_cell_height() const;

	sf::Color get_ship_color() const;
};