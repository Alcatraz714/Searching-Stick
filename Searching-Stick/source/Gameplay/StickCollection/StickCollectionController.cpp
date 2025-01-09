#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include <iostream>
#include <random>

namespace Gameplay {
	namespace Collection {

		using namespace UI::UIElement;
		using namespace Global;
		using namespace Graphics;

		void Gameplay::Collection::StickCollectionContoller::processSearchThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThreads();
			}
		}

		void StickCollectionContoller::joinThreads()
		{
			search_thread.join();
		}

		void Gameplay::Collection::StickCollectionContoller::processLinearSearch()
		{
			Sound::SoundService* sound_service = Global::ServiceLocator::getInstance()->getSoundService();
			for (int i = 0; i < sticks.size(); i++)
			{


				number_of_array_access += 1;		// keeps track of the number of sticks array is accessed
				number_of_comparisons++;				// keeps track of the number of comparisons made between target stick and another stick

				sound_service->playSound(Sound::SoundType::COMPARE_SFX);				// play the comparision sound

				if (sticks[i] == stick_to_search)			// condition to check if the current stick is the target stick
				{
					// if the target stick is found, this line of code sets the fill colour of the target's stick view
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;			// sets the pointer to null; meaning the search is completed.
					return;
				}
				else
				{
					// sets the fill color of the current stick's view to the processing_element_color; meaning the stick is still being checked
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);

					//pauses the thread for a small duration to show the searching operation
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

					// sets the fill color of the current stick's view back to the default element_color after the pause.
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}

			}
		}

		void Gameplay::Collection::StickCollectionContoller::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();


			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i); //calc height

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float Gameplay::Collection::StickCollectionContoller::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			// Calculate total spacing as 10% of the total space
			float total_spacing = collection_model->space_percentage * total_space;

			// Calculate the space between each stick
			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			// Calculate the remaining space for the rectangles
			float remaining_space = total_space - total_spacing;

			// Calculate the width of each rectangle
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		void Gameplay::Collection::StickCollectionContoller::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);
				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void Gameplay::Collection::StickCollectionContoller::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void Gameplay::Collection::StickCollectionContoller::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
				sticks.push_back(new Stick(i));
		}

		float Gameplay::Collection::StickCollectionContoller::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void Gameplay::Collection::StickCollectionContoller::destroy()
		{
			if (search_thread.joinable()) search_thread.join();

			for (int i = 0; i < sticks.size(); i++) delete(sticks[i]);
			sticks.clear();

			delete (collection_view);
			delete (collection_model);
		}

		Gameplay::Collection::StickCollectionContoller::StickCollectionContoller()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		Gameplay::Collection::StickCollectionContoller::~StickCollectionContoller()
		{
			destroy();
		}

		void Gameplay::Collection::StickCollectionContoller::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}

		void Gameplay::Collection::StickCollectionContoller::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
		}

		void Gameplay::Collection::StickCollectionContoller::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}

		void Gameplay::Collection::StickCollectionContoller::initialize()
		{

			initializeSticks();
			reset();
		}

		void Gameplay::Collection::StickCollectionContoller::update()
		{

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->update();
		}

		void Gameplay::Collection::StickCollectionContoller::render()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->render();
		}

		void Gameplay::Collection::StickCollectionContoller::reset()
		{
			current_operation_delay = 0;
			shuffleSticks();
			updateSticksPosition();
			resetSticksColor();
			resetSearchStick();
			resetVariables();
		}

		void Gameplay::Collection::StickCollectionContoller::searchElement(SearchType search_type)
		{
			this->search_type = search_type;

			switch (search_type)
			{
			case Gameplay::Collection::SearchType::LINEAR_SEARCH:
				current_operation_delay = collection_model->linear_search_delay;
				search_thread = std::thread(&StickCollectionContoller::processLinearSearch, this);
				//processLinearSearch(); - direct one frame method
				break;
			}
		}

		SearchType Gameplay::Collection::StickCollectionContoller::getSearchType()
		{
			return search_type;
		}

		int Gameplay::Collection::StickCollectionContoller::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}

		int Gameplay::Collection::StickCollectionContoller::getNumberOfArrayAccess()
		{
			return number_of_array_access;
		}

		int StickCollectionContoller::getDelayMilliseconds()
		{
			return 0;
		}

		int Gameplay::Collection::StickCollectionContoller::getNumberOfSticks()
		{
			return collection_model->number_of_elements;
		}
	}
}