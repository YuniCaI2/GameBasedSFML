//
// Created by cai on 25-4-17.
//

#include "HoverManager.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Window.h"

Game::HoverManager * Game::HoverManager::getInstance() {
    static auto* instance = new HoverManager();
    return instance;
}

void Game::HoverManager::registerHoverObject(GameObject *gameObject) {
    hoverObjects.push_back(gameObject);
}

void Game::HoverManager::unregisterHoverObject(GameObject *gameObject) {
    auto it = std::remove(hoverObjects.begin(), hoverObjects.end(), gameObject);
    hoverObjects.erase(it, hoverObjects.end());
}

Game::GameObject * Game::HoverManager::getHoverObject() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(Window::getWindow());
    for(const auto& i : hoverObjects) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Window::getWindow());
        auto relativeX = mousePos.x - i->globalPosition.x;
        auto relativeY = mousePos.y - i->globalPosition.y;
        if(relativeX > 0 && relativeX <= pbh::patchWidth && relativeY > 0 && relativeY <= pbh::patchHeight) {
            return i;
        }
    }
    // pbh::DeBug("Hover :", mousePos.x, mousePos.y);

    return nullptr;
}

Game::GameObject * Game::HoverManager::getLickObject(sf::Event event) {
    auto hoverObject = getHoverObject();
    if(hoverObject != nullptr) {
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                pbh::DeBug("Hover mouse button pressed", event.mouseButton.x, event.mouseButton.y);

                return hoverObject;

            }
        }
    }
    return nullptr;
}
