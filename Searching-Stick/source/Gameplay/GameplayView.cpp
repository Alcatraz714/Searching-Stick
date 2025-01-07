#include "Gameplay/GameplayView.h"
#include "Gameplay/GameplayController.h"
#include "Global/ServiceLocator.h"
#include "Global/Config.h"

namespace Gameplay
{
	using namespace UI::UIElement;
	using namespace Global;

	GameplayView::GameplayView() { background_image = new ImageView(); }

	GameplayView::~GameplayView() { delete (background_image); }

	void GameplayView::initialize(GameplayController* gameplay_controller)
	{
		this->gameplay_controller = gameplay_controller;
		initializeBackgroundImage();
	}

	void GameplayView::initializeBackgroundImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::background_texture_path,
			game_window->getSize().x,
			game_window->getSize().y,
			sf::Vector2f(0, 0));

		background_image->setImageAlpha(background_alpha);
	}


	void GameplayView::update() { background_image->update(); }

	void GameplayView::render() { background_image->render(); }
}