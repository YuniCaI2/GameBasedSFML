//
// Created by cai on 25-4-25.
//

#include "PlayerMoveComponent.h"

#include "PlayerStatsComponent.h"
#include "../InputManager.h"
#include "../GameObject.h"

void Game::PlayerMoveComponent::initial(GameObject *gameObject){
    this->gameObject = gameObject;
}

void Game::PlayerMoveComponent::update(GameObject *gameObject)//这里需要耦合了，没办法。。。 // 和属性组件内聚
{
    auto playerStats = gameObject->getComponent<Game::PlayerStatsComponent>();
    if (playerStats->isAlive() && playerStats->getMoveNum() > 0){
        auto inputManager = InputManager::getInstance();

        this->gameObject = gameObject;
        if (inputManager->isKeyPressed(sf::Keyboard::W)) {
            moveTo(gameObject->relativePosition.x, gameObject->relativePosition.y - 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::S)) {
            moveTo(gameObject->relativePosition.x, gameObject->relativePosition.y + 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::A)) {
            moveTo(gameObject->relativePosition.x - 1, gameObject->relativePosition.y);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::D)) {
            moveTo(gameObject->relativePosition.x + 1, gameObject->relativePosition.y);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::Q)) {
            moveTo(gameObject->relativePosition.x - 1, gameObject->relativePosition.y - 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::E)) {
            moveTo(gameObject->relativePosition.x + 1, gameObject->relativePosition.y - 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::Z)) {
            moveTo(gameObject->relativePosition.x - 1, gameObject->relativePosition.y + 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
        if (inputManager->isKeyPressed(sf::Keyboard::C)) {
            moveTo(gameObject->relativePosition.x + 1, gameObject->relativePosition.y + 1);
            playerStats->setCurrentMoveNum(playerStats->getMoveNum() - 1);
        }
    }
}

void Game::PlayerMoveComponent::moveTo(int x, int y) {
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7) {
        gameObject->relativePosition.x = x;
        gameObject->relativePosition.y = y;
        gameObject->globalPosition.x = gameObject->relativePosition.x * pbh::patchWidth + pbh::scenePosX;
        gameObject->globalPosition.y = gameObject->relativePosition.y * pbh::patchHeight + pbh::scenePosY;
        std::cout << "Move to: " << gameObject->relativePosition.x << ", " << gameObject->relativePosition.y << std::endl;
    }
}
