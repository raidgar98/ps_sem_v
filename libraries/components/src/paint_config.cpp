#include "../include/paint_config.h"

// STL
#include <random>
#include <limits>

constexpr pixel_number paint_config::get_cell_width() const
{
	const pixel_number width_without_margins{ area_width - (2.0 * margin) };
	const pixel_number width_without_padding{ width_without_margins - ( ( ship_cols - 1.0 ) * padding ) };
	const pixel_number cell_width{ width_without_padding / ship_cols };
	return cell_width;
}

constexpr pixel_number paint_config::get_cell_height() const
{
	const pixel_number height_without_margins{ area_height - (2.0 * margin) };
	const pixel_number height_without_padding{ height_without_margins - ( ( ship_rows - 1.0 ) * padding ) };
	const pixel_number cell_height{ height_without_padding / ship_rows };
	return cell_height;
}

sf::Color paint_config::get_ship_color() const
{
	using color_number = sf::Uint8;
	switch( ship_color_type )
	{
		case RANDOM:
		{
			std::random_device random_engine;
			std::uniform_int_distribution< color_number > range{
				std::numeric_limits<color_number>::min(), 
				std::numeric_limits<color_number>::max()
			};
			return sf::Color( range(random_engine), range(random_engine), range(random_engine) );
		}
		default: return ship_color;
	}

}