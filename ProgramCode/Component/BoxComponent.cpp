//
// Created by 51092 on 25-5-11.
//

#include "BoxComponent.h"
#include "../GUIManager.h"

void Game::BoxComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
}

void Game::BoxComponent::update(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    if (gameObject->isHovered && !gameObject->isClicked) {
        std::wstring text;
        text += item.name;
        text += L"\n";
        text += item.description;
        Game::GUIManager::getInstance()->writeText(text);
    }

    if (gameObject->isClicked) {
        if (onClick) {
            onClick();
        }
        gameObject->isClicked = false;
    }
}

void Game::BoxComponent::setHoverTexture(const std::string &texturePath) {
    hoverSprite.setTexture(item.texture);
}

void Game::BoxComponent::setDefaultTexture(const std::string &texturePath) {
    defaultSprite.setTexture(item.texture);
}

sf::Sprite & Game::BoxComponent::getSprite() {
        return defaultSprite;
}

sf::Vector2i Game::BoxComponent::getBoundBox() {
    return BoundBox;
}

void Game::BoxComponent::setOnClick(const std::function<void()> &onClick) {
    this->onClick = onClick;
}

void Game::BoxComponent::setItem(pbh::ItemType itemType) {
    item.setType(itemType);
    this->itemType = itemType;
    BoundBox.x = item.texture.getSize().x;
    BoundBox.y = item.texture.getSize().y;
    setHoverTexture("");
    setDefaultTexture("");
}
