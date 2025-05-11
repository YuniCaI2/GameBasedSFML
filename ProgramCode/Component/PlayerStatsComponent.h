//
// Created by 51092 on 25-4-26.
//

#ifndef PLAYERSTATSCOMPONENT_H
#define PLAYERSTATSCOMPONENT_H

#include "StatsComponent.h"
#include "../Item.h"

namespace Game {
    class PlayerStatsComponent : public StatsComponent {
    public:
        PlayerStatsComponent(int maxHealth = 5, int maxMoveNum = 1, int maxAttackNum = 2);
        void setMaxHealth(int maxHealth) override;
        void setCurrentHealth(int currentHealth) override;
        void setMoveNum(int moveNum) override;
        void setCurrentMoveNum(int currentMoveNum) override;
        void setAttackNum(int attackNum) override;
        void setCurrentAttackNum(int attackNum);
        void turnStart() override;//这个函数的目的是在每回合开始前角色或者敌方单位进行设置
        int getMaxHealth() const override;
        int getAttackNum() const override;
        int getCurrentHealth() const override;
        int getMoveNum() const override;
        void update(GameObject *gameObject) override;
        bool isAlive() const override;
        void initial(GameObject *gameObject) override;
        void addKill();
        int getKillNum() const;
        int setKillNum(int killNum);
        int getSumKillNum();
        void addItem(Item item);
        std::vector<Item> getItems();

    private:
        int maxHealth;
        int currentHealth;
        int currentMoveNum;
        int currentAttackNum;
        int maxMoveNum;
        int maxAttackNum;
        int killNum{0};
        int sumKillNum{0};
        std::vector<Item> items;
    };
}



#endif //PLAYERSTATSCOMPONENT_H
