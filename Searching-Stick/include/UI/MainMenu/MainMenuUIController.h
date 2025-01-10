#pragma once
#include <SFML/Graphics.hpp>
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/ImageView.h"
#include "UI/UIElement/ButtonView.h"

namespace UI
{
	namespace MainMenu
	{
		class MainMenuUIController : public Interface::IUIController
		{
		private:
			const float button_width = 350.f;
			const float button_height = 140.f;

			const float linear_search_button_y_position = 400.f;
			const float binary_search_button_y_position = 600.f;
			const float quit_button_y_position = 800.f;

			const float background_alpha = 85.f;

			UIElement::ImageView* background_image;

			UIElement::ButtonView* linear_search_button;
			UIElement::ButtonView* binary_search_button;
			UIElement::ButtonView* quit_button;

			void createImage();
			void createButtons();
			void initializeBackgroundImage();
			void initializeButtons();
			void registerButtonCallback();

			void linearSearchButtonCallback();
			void binarySearchButtonCallback();
			void quitButtonCallback();

			void destroy();

		public:
			MainMenuUIController();
			~MainMenuUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}