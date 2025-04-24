//
// Created by 51092 on 25-4-24.
//

#include "RenderComponent.h"
#include "../GameObject.h"

namespace Game {
    void RenderComponent::setTexture(const std::string& texturePath) {
        // 加载默认纹理
        if (!texture.loadFromFile(texturePath)) {
            // 纹理加载失败处理
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }

        // 设置默认精灵的纹理
        defaultSprite.setTexture(texture);
    }

    void RenderComponent::setHoverTexture(const std::string& texturePath) {
        // 加载悬停状态的纹理
        if (!hoverSpriteTexture.loadFromFile(texturePath)) {
            // 纹理加载失败处理
            throw std::runtime_error("Failed to load hover texture: " + texturePath);
        }

        // 设置悬停精灵的纹理
        hoverSprite.setTexture(hoverSpriteTexture);
    }

    void RenderComponent::update(GameObject* gameObject) {
        this->gameObject = gameObject;
    }

    sf::Sprite & RenderComponent::getSprite() const{
        // 获取关联的GameObject的位置
        auto position = gameObject->globalPosition;

        // 根据鼠标悬停状态选择要渲染的精灵
        sf::Sprite& currentSprite = gameObject->isHovered ? hoverSprite : defaultSprite;

        // 设置精灵位置
        currentSprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));

        return currentSprite;
    }
}
