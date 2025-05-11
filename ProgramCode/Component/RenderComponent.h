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
        virtual void setHoverTexture(const std::string& texturePath) = 0;
        virtual void setDefaultTexture(const std::string& texturePath) = 0;
        virtual sf::Vector2i getBoundBox() = 0;
        virtual sf::Sprite& getSprite() = 0;
    };
}



#endif //RENDERCOMPONENT_H
