//
// Created by cai on 25-4-17.
//

#ifndef WINDOW_H
#define WINDOW_H


namespace sf {
    class RenderWindow;
    class VideoMode;
}

class Window {
    Window();

public:
    static sf::RenderWindow& getWindow();
};



#endif //WINDOW_H
