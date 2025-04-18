//
// Created by cai on 25-4-17.
//

#include "Window.h"
#include <SFML/Graphics.hpp>
Window::Window() {
}

sf::RenderWindow& Window::getWindow(){
    static sf::RenderWindow window(sf::VideoMode(1600 / 2, 1100 / 2), "SFML RenderWindow");
    return window;
}
