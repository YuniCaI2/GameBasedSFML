//
// Created by cai on 25-4-3.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pbh.h"

namespace Game {
    class Component;

    class GameObject {
    public:
        sf::Vector2i globalPosition;
        sf::Vector2i relativePosition;
        bool isHovered{false};
        bool isClicked{false};

        GameObject() = default;

        void AddComponent(std::unique_ptr<Component>&& component);

        template<typename T>
        const T* getComponent();

        void update();
        void initial();

        virtual ~GameObject() = default;
    private:
        std::vector<std::unique_ptr<Component>> components;



    };
}


#endif //GAMEOBJECT_H
