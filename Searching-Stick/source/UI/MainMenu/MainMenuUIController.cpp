#include "UI/MainMenu/MainMenuUIController.h"
#include "Main/GameService.h"
#include "Graphics/GraphicService.h"
#include "Sound/SoundService.h"
#include "Event/EventService.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"


namespace UI
{
    namespace MainMenu
    {
        using namespace Global;
        using namespace Main;
        using namespace UIElement;
        using namespace Sound;
        using namespace Gameplay;
        using namespace Collection;
        using namespace Graphics;

        MainMenuUIController::MainMenuUIController()
        {
            createImage();
            createButtons();
        }

        MainMenuUIController::~MainMenuUIController()
        {
            destroy();
        }

        void MainMenuUIController::initialize()
        {
            initializeBackgroundImage();
            initializeButtons();
            registerButtonCallback();
        }

        void MainMenuUIController::createImage()
        {
            background_image = new ImageView();
        }

        void MainMenuUIController::createButtons()
        {
            linear_search_button = new ButtonView();
            binary_search_button = new ButtonView();
            quit_button = new ButtonView();
        }

        void MainMenuUIController::initializeBackgroundImage()
        {
            GraphicService* graphic_service = ServiceLocator::getInstance()->getGraphicService();

            background_image->initialize(Config::background_texture_path, graphic_service->getReferenceResolution().x, graphic_service->getReferenceResolution().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);
        }

        void MainMenuUIController::initializeButtons()
        {
            linear_search_button->initialize("Linear Search Button", Config::linear_search_button_texture_path, button_width, button_height, sf::Vector2f(0, linear_search_button_y_position));
            binary_search_button->initialize("Binary Search Button", Config::binary_search_button_texture_path, button_width, button_height, sf::Vector2f(0, binary_search_button_y_position));
            quit_button->initialize("Quit Button", Config::quit_button_texture_path, button_width, button_height, sf::Vector2f(0, quit_button_y_position));

            linear_search_button->setCentreAlinged();
            binary_search_button->setCentreAlinged();
            quit_button->setCentreAlinged();
        }

        void MainMenuUIController::registerButtonCallback()
        {
            linear_search_button->registerCallbackFuntion(std::bind(&MainMenuUIController::linearSearchButtonCallback, this));
            quit_button->registerCallbackFuntion(std::bind(&MainMenuUIController::quitButtonCallback, this));
        }

        void MainMenuUIController::linearSearchButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::GAMEPLAY);
            ServiceLocator::getInstance()->getGameplayService()->searchElement(Gameplay::Collection::SearchType::LINEAR_SEARCH);
        }

        void MainMenuUIController::quitButtonCallback()
        {
            ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->close();
        }

        void MainMenuUIController::update()
        {
            background_image->update();
            linear_search_button->update();
            binary_search_button->update();
            quit_button->update();
        }

        void MainMenuUIController::render()
        {
            background_image->render();
            linear_search_button->render();
            binary_search_button->render();
            quit_button->render();
        }

        void MainMenuUIController::show()
        {
            background_image->show();
            linear_search_button->show();
            binary_search_button->show();
            quit_button->show();
        }

        void MainMenuUIController::destroy()
        {
            delete (linear_search_button);
            delete (binary_search_button);
            delete (quit_button);
            delete (background_image);
        }
    }
}