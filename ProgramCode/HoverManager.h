//
// Created by cai on 25-4-17.
//

#ifndef HOVERMANAGER_H
#define HOVERMANAGER_H
#include "GameObject.h"


namespace Game {
    class HoverManager {
    public:
        static HoverManager* getInstance();
        void registerHoverObject(GameObject* gameObject);
        void unregisterHoverObject(GameObject* gameObject);
        GameObject* getHoverObject();
        GameObject* getLickObject(sf::Event event);
        sf::Vector2i getMousePos();
    private:
        HoverManager(){};
        std::vector<GameObject*> hoverObjects;
    };
}


#endif //HOVERMANAGER_H
