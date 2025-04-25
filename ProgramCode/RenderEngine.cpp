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

void Game::RenderEngine::Clear() {
    Window::getWindow().clear(sf::Color::Black);
}


void Game::RenderEngine::RenderScene(Game::Scene &scene) {
    Window::getWindow().draw(scene.getSprite());
    auto objects = scene.getObjects();
    for(auto& object : objects) {
        object->update();
        auto* renderComponent = object->getComponent<Game::RenderComponent>();
        if(renderComponent) {
            auto& sprite = renderComponent->getSprite();
            Window::getWindow().draw(sprite);
        }
    }
}


void Game::RenderEngine::Display() {

    Window::getWindow().display();

}


