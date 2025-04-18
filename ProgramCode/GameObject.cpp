//
// Created by cai on 25-4-3.
//

#include "GameObject.h"




void Game::GameObject::setTexture(const std::shared_ptr<pbh::gameObjectSpirit>& spirit) {
    this->gameObjectSpirit = spirit;
}

sf::Sprite Game::GameObject::getSprite() const {
    return gameObjectSpirit->sprite;
}


