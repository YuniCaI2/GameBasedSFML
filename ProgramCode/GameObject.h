//
// Created by cai on 25-4-3.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML/Graphics/Sprite.hpp>
#include "pbh.h"

namespace Game {
    class GameObject {
    public:
        sf::Vector2i globalPosition;
        sf::Vector2i relativePosition;

        void setTexture(const std::shared_ptr<pbh::gameObjectSpirit>& spirit);
        sf::Sprite getSprite() const;
        GameObject() = default;
        virtual ~GameObject() = default;
    protected:
        std::shared_ptr<pbh::gameObjectSpirit> gameObjectSpirit;


    };
}


#endif //GAMEOBJECT_H
