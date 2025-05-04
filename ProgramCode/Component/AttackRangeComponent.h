//
// Created by 51092 on 25-5-3.
//

#ifndef ATTACKRANGECOMPONENT_H
#define ATTACKRANGECOMPONENT_H
#include "Component.h"


namespace Game {
    class AttackRangeComponent :public Component{
    public:
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;

        std::vector<sf::RectangleShape> getRectangles() const;
    private:
        sf::RectangleShape block;
        std::vector<sf::RectangleShape> rectangles;
    };
}


#endif //ATTACKRANGECOMPONENT_H
