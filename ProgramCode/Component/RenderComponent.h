//
// Created by 51092 on 25-4-24.
//

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H
#include "Component.h"
#include<SFML/Graphics.hpp>


namespace Game {
    class GameObject;
}

namespace sf {
    class Texture;
}

namespace Game {
    class RenderComponent : public Component{
    public:
        void setTexture(const std::string& texturePath);
        void setHoverTexture(const std::string& texturePath);
        void update(GameObject* gameObject) override;
        sf::Sprite& getSprite() const;

    protected:
        sf::Texture texture;
        sf::Sprite defaultSprite;
        sf::Texture hoverSpriteTexture;
        sf::Sprite hoverSprite;
        GameObject* gameObject{nullptr};

    };
}



#endif //RENDERCOMPONENT_H
