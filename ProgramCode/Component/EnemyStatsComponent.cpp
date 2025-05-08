#include "EnemyStatsComponent.h"

#include "../GUIManager.h"

namespace Game {

    std::wstring enemyTypeToWstring(pbh::EnemyType enemyType) {
        switch (enemyType) {
            case pbh::EnemyType::Pawn:
                return L"Pawn";
            case pbh::EnemyType::Knight:
                return L"Knight";
            case pbh::EnemyType::Bishop:
                return L"Bishop";
            default:
                return L"Rook";
        }
    }

    EnemyStatsComponent::EnemyStatsComponent() {

    }

    void EnemyStatsComponent::setMaxHealth(int maxHealth) {
        this->maxHealth = maxHealth;
    }

    void EnemyStatsComponent::setCurrentHealth(int currentHealth) {
        this->currentHealth = currentHealth;
    }

    void EnemyStatsComponent::setMoveNum(int moveNum) {
        this->moveNum = moveNum;
    }

    void EnemyStatsComponent::setCurrentMoveNum(int currentMoveNum) {
        //空接口，这是玩家的状态，理论上敌人都不用设置移动次数这个设定
        //只有血量和类型需要关注
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
        // 响应悬停
        if (gameObject->isHovered && !gameObject->isClicked) {
            std::wstring text = L"敌人类型：" + enemyTypeToWstring(enemyType) + L"\n";
            text += L"剩余血量：" + std::to_wstring(currentHealth);

            GUIManager::getInstance()->writeText(text);
        }
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
