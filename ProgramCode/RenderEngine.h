//
// Created by cai on 25-4-7.
//

#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include <vector>
#include <SFML/Window/Window.hpp>

#include "GameObject.h"
#include "Scene.h"


namespace Game {
    class RenderEngine {
        RenderEngine() = default;
    public:
        static RenderEngine* getInstance();
        void Clear();
        void RenderScene(Game::Scene& scene);
        void Display();

    };
}


#endif //RENDERENGINE_H
