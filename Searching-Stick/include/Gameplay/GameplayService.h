#pragma once
#include <SFML/System/String.hpp>

namespace Gameplay
{
	class GameplayController;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

	public:
		GameplayService();
		~GameplayService();

		// Lifecycle methods
		void initialize();
		void update();
		void render();

		// Functions
		void reset();
	};
}