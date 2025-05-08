//
// Created by 51092 on 25-5-5.
//

#include "EnemyRenderComponent.h"

#include "EnemyStatsComponent.h"

//其实这个渲染模块是设计有问题，其实可以复用的

std::unordered_map<pbh::EnemyType, std::pair<sf::Texture, sf::Texture>> Game::EnemyRenderComponent::textures;

void Game::EnemyRenderComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    //这里和update的效果相同
    enemyType = gameObject->getComponent<EnemyStatsComponent>()->getEnemyType();
    if (textures.find(enemyType) == textures.end()) {
        sf::Texture defaultTexture;
        sf::Texture hoverTexture;
        if (!defaultTexture.loadFromFile(pbh::enemyTexPathTable[enemyType].first)) {
            std::cerr << "Failed to load default texture" << std::endl;
            exit(-1);
        }
        if (!hoverTexture.loadFromFile(pbh::enemyTexPathTable[enemyType].second)) {
            std::cerr << "Failed to load default texture" << std::endl;
            exit(-1);
        }
        textures[enemyType] = std::make_pair(defaultTexture, hoverTexture);
        defaultSprite.setTexture(textures[enemyType].first);
        hoverSprite.setTexture(textures[enemyType].second);
        auto curSize = defaultTexture.getSize();
        auto scaleX =  pbh::patchWidth / static_cast<float>(curSize.x);
        auto scaleY = pbh::patchHeight / static_cast<float>(curSize.y);
        defaultSprite.setScale(scaleX, scaleY);
        hoverSprite.setScale(scaleX, scaleY);
    }else {
        defaultSprite.setTexture(textures[enemyType].first);
        hoverSprite.setTexture(textures[enemyType].second);
        auto curSize = textures[enemyType].first.getSize();
        auto scaleX =  pbh::patchWidth / static_cast<float>(curSize.x);
        auto scaleY = pbh::patchHeight / static_cast<float>(curSize.y);
        defaultSprite.setScale(scaleX, scaleY);
        hoverSprite.setScale(scaleX, scaleY);
    }
}

void Game::EnemyRenderComponent::setDefaultTexture(const std::string &texturePath) {
}

void Game::EnemyRenderComponent::setHoverTexture(const std::string &texturePath) {
}

void Game::EnemyRenderComponent::update(GameObject *gameObject) {
    this->gameObject = gameObject;
    defaultSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    hoverSprite.setPosition(gameObject->globalPosition.x, gameObject->globalPosition.y);
    // pbh::DeBug("Position:", gameObject->globalPosition.x, gameObject->globalPosition.y);
}

sf::Sprite & Game::EnemyRenderComponent::getSprite(){
    if(gameObject->isClicked || gameObject->isHovered) {
        return hoverSprite;
    }else {
        return defaultSprite;
    }
}
