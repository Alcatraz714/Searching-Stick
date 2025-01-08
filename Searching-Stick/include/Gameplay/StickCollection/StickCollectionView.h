#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/ImageView.h"

namespace Gameplay
{
    namespace Collection
    {
        class StickCollectionController;

        class StickCollectionView
        {
        private:
            StickCollectionController* collection_controller;

        public:
            StickCollectionView();
            ~StickCollectionView();

            void initialize(StickCollectionController* collection_controller);
            void update();
            void render();
        };
    }
}