//
// Created by 51092 on 25-5-9.
//

#include "ButtonComponent.h"

void Game::ButtonComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
}

void Game::ButtonComponent::update(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);

    //触发点击回调
    if (gameObject->isClicked) {
        if (onClick) {
            onClick();
        }
        gameObject->isClicked = false;
    }
}

void Game::ButtonComponent::setHoverTexture(const std::string &texturePath) {
    if (! hoverTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load default texture" << std::endl;
        exit(-1);
    }
    hoverSprite.setTexture(hoverTexture);

    BoundBox.x = hoverTexture.getSize().x;
    BoundBox.y = hoverTexture.getSize().y;
    //因为按钮的大小和贴图一致，这里不选择调整大小了
}

void Game::ButtonComponent::setDefaultTexture(const std::string &texturePath) {
    if (! defaultTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load default texture" << std::endl;
        exit(-1);
    }
    defaultSprite.setTexture(defaultTexture);
}

sf::Sprite & Game::ButtonComponent::getSprite() {
    if (gameObject->isClicked || gameObject->isHovered) {
        return hoverSprite;
    } else {
        return defaultSprite;
    }
}

sf::Vector2i Game::ButtonComponent::getBoundBox() {
    return BoundBox;
}

void Game::ButtonComponent::setOnClick(const std::function<void()>& onClick) {
    this->onClick = onClick;
}
