#pragma once
#include <SFML/System/String.hpp>
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionController.h"

namespace Gameplay
{
	using namespace Collection;
	class GameplayController;
	enum class SearchType;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		StickCollectionContoller* collection_controller;

	public:
		GameplayService();
		~GameplayService();
		// Lifecycle Methods
		void initialize();
		void update();
		void render();

		// Functions
		void reset();
		void searchElement(Collection::SearchType search_type);
		// Stick
		Collection::SearchType getCurrentSearchType();
		int getNumberOfSticks();
	};
}