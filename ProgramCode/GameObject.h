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

        void AddComponent(Component* component);
        void setGlobalPosition(int x, int y);
        void setRelativePosition(int x, int y);

        template<typename T>
        inline T * getComponent() {
            for (auto &component: components) {
                if (dynamic_cast<T *>(component)) {
                    return dynamic_cast<T *>(component);
                }
            }
            return nullptr;
        }

        void update();

        void initial();

        virtual ~GameObject() = default;

    private:
        std::vector<Component* > components;
    };
}


#endif //GAMEOBJECT_H
