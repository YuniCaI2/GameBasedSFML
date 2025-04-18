//
// Created by cai on 25-4-17.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "pbh.h"


namespace Game {
    class Enemy : public GameObject {
    public:
        virtual std::shared_ptr<Enemy> clone();

    protected:
        pbh::enemyAttribute enemyAttribute;
    };
}





#endif //ENEMY_H
