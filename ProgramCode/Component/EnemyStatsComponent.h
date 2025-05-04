#pragma once
#include "../pbh.h"
#include "StatsComponent.h"
#include <unordered_map>
namespace Game{

    //敌人属性的组件基类
    class EnemyStatsComponent : public StatsComponent{
    public:
        void setMaxHealth(int maxHealth) override;
        void setCurrentHealth(int currentHealth) override;
        void setMoveNum(int moveNum) override;
        void setAttackNum(int attackNum) override;
        void turnStart() override;
        int getMaxHealth() const override;
        int getAttackNum() const override;
        int getCurrentHealth() const override;
        int getMoveNum() const override;
        void update(GameObject *gameObject) override;
        bool isAlive() const override;
        void initial(GameObject *gameObject) override;
        
        void initialEnemyType(pbh::EnemyType enemyType);
        pbh::EnemyType getEnemyType() const;

    protected:
        static std::unordered_map<pbh::EnemyType, int> enemyHealthTable;
        pbh::EnemyType enemyType{pbh::EnemyType::Pawn};
        int maxHealth{3};
        int currentHealth{3};
        int moveNum{1};

    };
    //敌人的攻击逻辑和玩家的攻击逻辑是不同的
    /*
        敌人攻击伤害默认始终为1，
        移动就是攻击
        不需要单独设置武器类
    */
}
