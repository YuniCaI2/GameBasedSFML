//
// Created by cai on 25-4-3.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "pbh.h"

namespace Game {
    class GameObject {
    public:
        pbh::Vector2 position;
        pbh::Texture texture;
        void setTexture(const pbh::Texture& texture);

        GameObject() = default;
        virtual ~GameObject() = default;


    };
}


#endif //GAMEOBJECT_H
