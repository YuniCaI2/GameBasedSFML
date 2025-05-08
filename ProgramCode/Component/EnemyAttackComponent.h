//
// Created by 51092 on 25-5-8.
//

#ifndef ENEMYATTACKCOMPONENT_H
#define ENEMYATTACKCOMPONENT_H
#include "AttackComponent.h"
#include "../pbh.h"
#include <SFML/Graphics.hpp>

#include "MoveComponent.h"

//敌人攻击和移动是一体的
namespace Game {
    class EnemyAttackComponent : public AttackComponent{
    public:
        bool Attack(GameObject* hitObject) override;
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;
        bool moveTo(int x, int y);
        std::vector<sf::Vector2i> getAttackRange();
    private:
        GameObject* gameObject{nullptr};
        pbh::EnemyType enemyType{pbh::EnemyType::Pawn};

    };
}



#endif //ENEMYATTACKCOMPONENT_H
