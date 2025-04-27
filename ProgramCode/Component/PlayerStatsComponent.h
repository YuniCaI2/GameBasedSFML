//
// Created by 51092 on 25-4-26.
//

#ifndef PLAYERSTATSCOMPONENT_H
#define PLAYERSTATSCOMPONENT_H

#include "StatsComponent.h"

namespace Game {
    class PlayerStatsComponent : public StatsComponent {
    public:
        PlayerStatsComponent(int maxHealth = 5, int maxMoveNum = 1, int maxAttackNum = 1);
        void setMaxHealth(int maxHealth) override;
        void setCurrentHealth(int currentHealth) override;
        void setMoveNum(int moveNum) override;
        void setAttackNum(int attackNum) override;
        void turnStart() override;//这个函数的目的是在每回合开始前角色或者敌方单位进行设置
        int getMaxHealth() const override;
        int getAttackNum() const override;
        int getCurrentHealth() const override;
        int getMoveNum() const override;
        void update(GameObject *gameObject) override;
        bool isAlive() const override;

    private:
        int maxHealth;
        int currentHealth;
        int currentMoveNum;
        int currentAttackNum;
        int maxMoveNum;
        int maxAttackNum;
    };
}



#endif //PLAYERSTATSCOMPONENT_H
