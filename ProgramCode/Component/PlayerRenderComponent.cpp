//
// Created by cai on 25-4-25.
//

#include "PlayerRenderComponent.h"


void Game::PlayerRenderComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    //这里和update的效果相同
}

sf::Vector2i Game::PlayerRenderComponent::getBoundBox() {
    return BoundBox;
}

void Game::PlayerRenderComponent::setDefaultTexture(const std::string &texturePath) {
    if(!defaultTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load default texture" << std::endl;
        exit(-1);
    }
    defaultSprite.setTexture(defaultTexture);
    auto curSize = defaultTexture.getSize();
    auto scaleX =  pbh::patchWidth / static_cast<float>(curSize.x);
    auto scaleY = pbh::patchHeight / static_cast<float>(curSize.y);
    // pbh::DeBug("Size:", scaleX, scaleY);
    defaultSprite.setScale(scaleX, scaleY);
    BoundBox.x = defaultTexture.getSize().x;
    BoundBox.y = defaultTexture.getSize().y;
}

void Game::PlayerRenderComponent::setHoverTexture(const std::string &texturePath) {
    if(!hoverTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load default texture" << std::endl;
        exit(-1);
    }
    hoverSprite.setTexture(hoverTexture);
    auto curSize = hoverTexture.getSize();
    auto scaleX =  pbh::patchWidth / static_cast<float>(curSize.x);
    auto scaleY = pbh::patchHeight / static_cast<float>(curSize.y);
    // pbh::DeBug("Size:", scaleX, scaleY);
    hoverSprite.setScale(scaleX, scaleY);
    BoundBox.x = hoverTexture.getSize().x;
    BoundBox.y = hoverTexture.getSize().y;
}

void Game::PlayerRenderComponent::update(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    // pbh::DeBug("Position:", gameObject->globalPosition.x, gameObject->globalPosition.y);
}

sf::Sprite & Game::PlayerRenderComponent::getSprite(){
    if(gameObject->isClicked || gameObject->isHovered) {
        return hoverSprite;
    }else {
        return defaultSprite;
    }
}
