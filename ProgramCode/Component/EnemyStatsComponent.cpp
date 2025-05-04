#include "EnemyStatsComponent.h"

namespace Game {

    void EnemyStatsComponent::setMaxHealth(int maxHealth) {
        this->maxHealth = maxHealth;
    }

    void EnemyStatsComponent::setCurrentHealth(int currentHealth) {
        this->currentHealth = currentHealth;
    }

    void EnemyStatsComponent::setMoveNum(int moveNum) {
        this->moveNum = moveNum;
    }

    void EnemyStatsComponent::setAttackNum(int attackNum) {
        //空接口
    }

    void EnemyStatsComponent::turnStart() {
        this->moveNum = 1;
    }

    int EnemyStatsComponent::getMaxHealth() const {
        return maxHealth;
    }

    int EnemyStatsComponent::getAttackNum() const {
        //空接口
        //因为敌人的移动比较特别
        return 0;
    }

    int EnemyStatsComponent::getCurrentHealth() const {
        return currentHealth;
    }

    int EnemyStatsComponent::getMoveNum() const {
        return moveNum;
    }

    void EnemyStatsComponent::update(GameObject *gameObject) {
        //不知道要写什么，这个组件是个容器，我认为它是个单向的
    }

    bool EnemyStatsComponent::isAlive() const {
        return currentHealth > 0;
    }

    void EnemyStatsComponent::initial(GameObject *gameObject) {
        this->gameObject = gameObject;
        maxHealth = 3;//这里是默认的血量
        moveNum = 1;
        currentHealth = maxHealth;
    }

    void EnemyStatsComponent::initialEnemyType(pbh::EnemyType enemyType) {
        this->enemyType = enemyType;
        maxHealth = enemyHealthTable[enemyType];
        currentHealth = maxHealth;
    }

    pbh::EnemyType EnemyStatsComponent::getEnemyType() const {
        return enemyType;
    }

    std::unordered_map<pbh::EnemyType, int> EnemyStatsComponent::enemyHealthTable = {
        {pbh::EnemyType::Bishop, 3},
        {pbh::EnemyType::Knight, 3},
        {pbh::EnemyType::Pawn, 3},
        {pbh::EnemyType::Rook, 3},
    };
}
