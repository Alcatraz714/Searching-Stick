#pragma once

namespace Gameplay
{
    class GameplayView;

    class GameplayController
    {
    private:

        GameplayView* gameplay_view;

        void destroy();

    public:
        GameplayController();
        ~GameplayController();

        // Lifecycle methods
        void initialize();
        void update();
        void render();

        // Functions
        void reset();
    };
}