//
// Created by 51092 on 25-4-26.
//

#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H
#include "Component.h"


namespace Game {
    class StatsComponent : public Component{
    public:
        virtual void setMaxHealth(int maxHealth) = 0;
        virtual int getMaxHealth() const = 0;
        virtual void setCurrentHealth(int currentHealth) = 0;
        virtual int getCurrentHealth() const = 0;
        virtual void setMoveNum(int moveNum) = 0;
        virtual int getMoveNum() const = 0;
        virtual void setAttackNum(int attackNum) = 0;
        virtual int getAttackNum() const = 0;
        virtual bool isAlive() const = 0;
        virtual void turnStart() = 0;
    };
}


#endif //STATSCOMPONENT_H
