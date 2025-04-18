//
// Created by cai on 25-4-7.
//

#include "RenderEngine.h"

#include <__ranges/rend.h>

#include "Window.h"

Game::RenderEngine*  Game::RenderEngine::getInstance() {
    static auto* instance = new RenderEngine();
    return instance;
}

void Game::RenderEngine::RenderScene(const Game::Scene &scene) {
    for(const auto &object : scene.getObjects()) {
        Window::getWindow().draw(object->getSprite());
    }
    Window::getWindow().draw(scene.getSprite());
}

void Game::RenderEngine::Display() {

    Window::getWindow().display();
}


