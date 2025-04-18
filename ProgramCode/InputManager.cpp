//
// Created by cai on 25-4-17.
//

#include "InputManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Window.h"

Game::InputManager * Game::InputManager::getInstance() {
    static auto* instance = new Game::InputManager();
    return instance;
}

void Game::InputManager::HandleInput() {
    while(Window::getWindow().pollEvent(event)) {

    }
}

