//
// Created by cai on 25-4-17.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window/Event.hpp>


namespace Game {
    class InputManager {
    private:
        InputManager(){};
        sf::Event event;
    public:
        static InputManager* getInstance();
        void HandleInput();
    };
}



#endif //INPUTMANAGER_H
