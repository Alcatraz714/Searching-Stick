#pragma once
#include <SFML/Graphics.hpp>

namespace Global
{
	class Config
	{
	public:
		static const sf::String outscal_logo_texture_path;
		static const sf::String background_texture_path;

		static const sf::String linear_search_button_texture_path;
		static const sf::String binary_search_button_texture_path;
		static const sf::String quit_button_texture_path;
		static const sf::String menu_button_large_texture_path;

		static const sf::String bubble_bobble_font_path;
		static const sf::String DS_DIGIB_font_path;

		static const sf::String button_click_sound_path;
		static const sf::String compare_sfx_path;
	};
}