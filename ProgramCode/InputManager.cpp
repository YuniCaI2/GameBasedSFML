//
// Created by cai on 25-4-17.
//

#include "InputManager.h"
#include "HoverManager.h"



Game::InputManager * Game::InputManager::getInstance() {
    static auto* instance = new Game::InputManager();
    return instance;
}

void Game::InputManager::registerGameObject(GameObject *gameObject) {
    gameObjects.push_back(gameObject);
    HoverManager::getInstance()->registerHoverObject(gameObject);
}

void Game::InputManager::unregisterGameObject(GameObject *gameObject) {
    auto it = std::remove(gameObjects.begin(), gameObjects.end(), gameObject);
    gameObjects.erase(it, gameObjects.end());
    HoverManager::getInstance()->unregisterHoverObject(gameObject);
}

void Game::InputManager::processEvent(sf::Event& event) {

    //刷新悬停状态
    for(auto& gameObject : gameObjects) {
        gameObject->isHovered = false;
    }
    clickedObject = nullptr;
    hoverObject = nullptr;

    //处理事件
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            clickedObject = HoverManager::getInstance()->getLickObject(event);
            if (clickedObject != nullptr) {
                clickedObject->isClicked = 1 - clickedObject->isClicked;//切换状态
            }
        }
    } else if (event.type == sf::Event::MouseMoved) {
        hoverObject = HoverManager::getInstance()->getHoverObject();
        if (hoverObject != nullptr) {
            hoverObject->isHovered = true;
        }
    } else if (event.type == sf::Event::KeyPressed) {
        keyStates[event.key.code] = true;
    } else if (event.type == sf::Event::KeyReleased) {
        keyStates[event.key.code] = false;
    }
}

void Game::InputManager::update() {
    //记录上一轮信息
    lastKeyStates = keyStates;
}

bool Game::InputManager::isKeyPressed(sf::Keyboard::Key key) const {
    auto currentIt = keyStates.find(key);
    auto lastIt = lastKeyStates.find(key);
    // 只在按键状态从未按下变为按下时返回true
    return (currentIt != keyStates.end() && currentIt->second) &&
           (lastIt == lastKeyStates.end() || !lastIt->second);
}

Game::GameObject * Game::InputManager::getClickedObject() {
    return clickedObject;
}

Game::GameObject * Game::InputManager::getHoverObject() {
    return hoverObject;
}

sf::Vector2i Game::InputManager::getMousePos() {
    return  HoverManager::getInstance()->getMousePos();
}


