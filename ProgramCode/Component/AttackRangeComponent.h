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
        std::vector<sf::Vector2i> getAttackRangePositions() const;
        std::vector<sf::RectangleShape> getRectangles() const;
        pbh::EnemyType getMatchEnemy();
    private:
        sf::RectangleShape block;
        std::vector<sf::RectangleShape> rectangles;
        std::vector<sf::Vector2i> AttackRangePositions;
        pbh::EnemyType MatchEnemy{pbh::EnemyType::Pawn};
    };
}


#endif //ATTACKRANGECOMPONENT_H
