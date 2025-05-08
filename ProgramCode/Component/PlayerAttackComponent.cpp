//
// Created by 51092 on 25-5-5.
//

#include "PlayerAttackComponent.h"

#include "AttackRangeComponent.h"
#include "EnemyStatsComponent.h"
#include "PlayerStatsComponent.h"
#include "WeaponComponent.h"
#include "../GUIManager.h"

bool Game::PlayerAttackComponent::Attack(GameObject *hitObject) {
    const auto attackRangePositions = gameObject->getComponent<AttackRangeComponent>()->getAttackRangePositions();
    auto playerStats = gameObject->getComponent<PlayerStatsComponent>();
    auto hitObjectPosition = hitObject->relativePosition;
    if (gameObject->isClicked) {
        if (hitObject->isClicked) {
            for (const auto& p : attackRangePositions) {
                if (p == hitObjectPosition) {
                    auto stats = hitObject->getComponent<EnemyStatsComponent>();
                    stats->setCurrentHealth(stats->getCurrentHealth() - 1);//扣血
                    hitObject->isClicked = false;
                    return true;
                }
            }
            std::wstring text;
            text = L"敌人不在攻击范围内！";
            hitObject->isClicked = false;
            Game::GUIManager::getInstance()->writeText(text);
            return false;
        }
    }else {
        std::wstring text;
        text = L"请选中自己\n再发动攻击哦";
        Game::GUIManager::getInstance()->writeText(text);
        hitObject->isClicked = false;
        return false;
    }
}

void Game::PlayerAttackComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
}

void Game::PlayerAttackComponent::update(GameObject *gameObject) {

}
