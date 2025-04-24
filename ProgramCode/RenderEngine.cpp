//
// Created by cai on 25-4-7.
//

#include "RenderEngine.h"
#include "Window.h"
#include "Component/RenderComponent.h"

Game::RenderEngine*  Game::RenderEngine::getInstance() {
    static auto* instance = new RenderEngine();
    return instance;
}

void Game::RenderEngine::RenderScene(const Game::Scene &scene) {
    auto objects = scene.getObjects();
    for(const auto& object : objects) {
        object->update();
        auto renderComponent = object->getComponent<Game::RenderComponent>();
        if(renderComponent) {
            auto& sprite = renderComponent->getSprite();
            Window::getWindow().draw(sprite);
        }
    }
}


void Game::RenderEngine::Display() {

    Window::getWindow().display();

}


