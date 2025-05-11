//
// Created by cai on 25-4-7.
//

#include "RenderEngine.h"
#include "Window.h"
#include "Component/AttackComponent.h"
#include "Component/AttackRangeComponent.h"
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

        auto* renderComponent = object->getComponent<Game::RenderComponent>();
        if (object->isClicked) {
            auto* attackRange = object->getComponent<AttackRangeComponent>();
            if (attackRange) {
                const auto attackRects = attackRange->getRectangles();
                for (const auto& rect : attackRects) {
                    Window::getWindow().draw(rect);
                }
            }
        }
        if(renderComponent) {
            auto& sprite = renderComponent->getSprite();
            // std::cout << "Render" << std::endl;
            Window::getWindow().draw(sprite);
        }
    }
}


void Game::RenderEngine::Display() {

    Window::getWindow().display();

}


