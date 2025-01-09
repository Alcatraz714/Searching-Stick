#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Gameplay/GameplayService.h"
#include "Sound/SoundService.h"
#include "Main/GameService.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"

namespace UI
{
    namespace GameplayUI
    {
        using namespace Main;
        using namespace Sound;
        using namespace UIElement;
        using namespace Global;
        using namespace Gameplay;
        using namespace Collection;

        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
            updateSearchTypeText();
        }

        void GameplayUIController::createButton()
        {
            menu_button = new ButtonView();
        }

        void GameplayUIController::createTexts()
        {
            search_type_text = new TextView();
            number_of_comparisons_text = new TextView();
            number_of_array_access_text = new TextView();

            num_sticks_text = new TextView();
            delay_text = new TextView();
            time_complexity_text = new TextView();

        }

        void GameplayUIController::initializeButton()
        {
            menu_button->initialize("Menu Button",
            Config::menu_button_large_texture_path,
            menu_button_width, menu_button_height,
            sf::Vector2f(menu_button_x_position, menu_button_y_position));

            registerButtonCallback();
        }

        void GameplayUIController::initializeTexts()
        {
            search_type_text->initialize("Search Type  :  Linear Search", sf::Vector2f(search_type_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_comparisons_text->initialize("Comparisons  :  0", sf::Vector2f(comparisons_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_array_access_text->initialize("Array Access  :  0", sf::Vector2f(array_access_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);


            num_sticks_text->initialize("Number of Sticks  :  0", sf::Vector2f(num_sticks_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);


            delay_text->initialize("Delay  :  0 ms", sf::Vector2f(delay_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);


            time_complexity_text->initialize("Time Complexity  :  O(n)", sf::Vector2f(time_complexity_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);
        }

        void GameplayUIController::update()
        {
            menu_button->update();
            updateSearchTypeText();
            updateComparisonsText();
            updateArrayAccessText();

            updateNumberOfSticksText();
            updateDelayText();
            updateTimeComplexityText();

        }

        void GameplayUIController::render()
        {
            menu_button->render();
            search_type_text->render();
            number_of_comparisons_text->render();
            number_of_array_access_text->render();

            num_sticks_text->render();
            delay_text->render();
            time_complexity_text->render();
        }

        void GameplayUIController::show()
        {
            menu_button->show();
            search_type_text->show();
            number_of_comparisons_text->show();
            number_of_array_access_text->show();

            num_sticks_text->show();
            delay_text->show();
            time_complexity_text->show();
        }

        void GameplayUIController::updateSearchTypeText()
        {
            Gameplay::Collection::SearchType new_search_type = ServiceLocator::getInstance()->getGameplayService()->getCurrentSearchType();


            switch (new_search_type)
            {
            case::Gameplay::Collection::SearchType::LINEAR_SEARCH:
                search_type_text->setText("Linear Search");
                break;

                /*case::Gameplay::SearchType::BINARY_SEARCH:
                    search_type_text->setText("Binary Search");
                    break;*/
            }
            search_type_text->update();

        }

        void GameplayUIController::updateComparisonsText()
        {
            int number_of_comparisons = ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparisons();;
            sf::String comparisons_string = "Comparisons  :  " + std::to_string(number_of_comparisons);

            number_of_comparisons_text->setText(comparisons_string);
            number_of_comparisons_text->update();
        }

        void GameplayUIController::updateArrayAccessText()
        {
            int number_of_array_access = ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess();;
            sf::String array_access_string = "Array Access  :  " + std::to_string(number_of_array_access);

            number_of_array_access_text->setText(array_access_string);
            number_of_array_access_text->update();
        }

        void GameplayUIController::updateNumberOfSticksText()
        {
            int num_sticks = ServiceLocator::getInstance()->getGameplayService()->getNumberOfSticks();
            sf::String sticks_string = "Number of Sticks  :  " + std::to_string(num_sticks);

            num_sticks_text->setText(sticks_string);
            num_sticks_text->update();
        }

        void GameplayUIController::updateDelayText()
        {
            int delay_in_milliseconds = ServiceLocator::getInstance()->getGameplayService()->getDelayMilliseconds();
            sf::String delay_string = "Delay (ms)  :  " + std::to_string(delay_in_milliseconds);

            delay_text->setText(delay_string);
            delay_text->update();
        }

        void GameplayUIController::updateTimeComplexityText()
        {
            sf::String time_complexity = ServiceLocator::getInstance()->getGameplayService()->getTimeComplexity();
            sf::String time_complexity_string = "Time Complexity  :  " + time_complexity;

            time_complexity_text->setText(time_complexity_string);
            time_complexity_text->update();
        }

        void GameplayUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getGameplayService()->reset();
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void GameplayUIController::registerButtonCallback()
        {
            menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
        }

        void GameplayUIController::destroy()
        {
            delete (menu_button);
            delete (search_type_text);
            delete (number_of_comparisons_text);
            delete (number_of_array_access_text);
        }
    }
}