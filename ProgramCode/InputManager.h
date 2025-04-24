//
// Created by cai on 25-4-17.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window/Event.hpp>
#include<unordered_map>

namespace Game {
    class GameObject;
    class InputManager {
    private:
        InputManager(){};
        std::vector<GameObject*> gameObjects;
        GameObject* clickedObject{nullptr};
        GameObject* hoverObject{nullptr};
        std::unordered_map<sf::Keyboard::Key, bool> keyStates;
    public:
        static InputManager* getInstance();
        void registerGameObject(GameObject* gameObject);
        void unregisterGameObject(GameObject* gameObject);
        void processEvent(sf::Event& event);
        void update();
        bool isKeyPressed(sf::Keyboard::Key key) const;
        GameObject* getClickedObject();
        GameObject* getHoverObject();
        sf::Vector2i getMousePos();

    };
}



#endif //INPUTMANAGER_H
