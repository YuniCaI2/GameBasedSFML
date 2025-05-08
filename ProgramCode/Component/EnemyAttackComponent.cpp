//
// Created by 51092 on 25-5-8.
//

#include "EnemyAttackComponent.h"

#include "EnemyStatsComponent.h"
#include "PlayerStatsComponent.h"
#include "../GUIManager.h"

bool Game::EnemyAttackComponent::Attack(GameObject *hitObject) {
    auto playerStats = hitObject->getComponent<PlayerStatsComponent>();
    auto attackRange = getAttackRange();
    auto playerPosition = hitObject->relativePosition;
    auto p = gameObject->relativePosition;
        if (playerPosition == p) {
            playerStats->setCurrentHealth(playerStats->getCurrentHealth() - 1);
            std::wstring text = L"敌人对你发动攻击\n，且成功了";
            Game::GUIManager::getInstance()->writeText(text);
            return true;
        }
    return false;
}

void Game::EnemyAttackComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    enemyType = gameObject->getComponent<EnemyStatsComponent>()->getEnemyType();
}

void Game::EnemyAttackComponent::update(GameObject *gameObject) {
}

bool Game::EnemyAttackComponent::moveTo(int x, int y) {
    auto ranges = getAttackRange();

    //检测是否能移动
    for (auto& range : ranges) {
        if (x == range.x && y == range.y) {
            gameObject->setRelativePosition(x,y);
            return true;
        }
    }
    return false;
}


std::vector<sf::Vector2i> Game::EnemyAttackComponent::getAttackRange() {
    std::vector<sf::Vector2i> range;
    std::vector<sf::Vector2i> knightPositions;
    std::vector<sf::Vector2i> bishopPositions;
    std::vector<sf::Vector2i> rookPositions;
    auto checkFunc = [](sf::Vector2i n) {
        if (n.x >= 0 && n.x < 8 && n.y >= 0 && n.y < 8 ) {
            return false;
        }else {
            return true;
        }
    }; //用来检测是否越界

    switch (enemyType) {
        case pbh::EnemyType::Pawn:
            range.clear();
            range.push_back(gameObject->relativePosition + sf::Vector2i(1, 1));
            range.push_back(gameObject->relativePosition + sf::Vector2i(-1, 1));
            break;
        case pbh::EnemyType::Knight:
            range.clear();
            knightPositions = {
                {-1, -2}, {1, -2}, {2, -1}, {2, 1},
                {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}
            };
            for (auto& p : knightPositions) {
                range.push_back(gameObject->relativePosition + p);
            }
            break;
        case pbh::EnemyType::Bishop:
            range.clear();
            bishopPositions = {
                {1,1}, {1, -1}, {-1, -1}, {-1, 1}
            };
            for (auto& p : bishopPositions) {
                int k = 1;
                while (true) {
                    sf::Vector2i temp = gameObject->relativePosition + k * p;
                    if (! checkFunc(temp)) {
                        range.push_back(temp);
                    }else {
                        break;
                    }
                    k++;
                }
            }
            break;
        case pbh::EnemyType::Rook:
            range.clear();
            rookPositions = {
                {1,0}, {-1, 0}, {0, 1}, {0, -1}
            };
            for (auto& p : rookPositions) {
                int k = 1;
                while (true) {
                    sf::Vector2i temp = gameObject->relativePosition + k * p;
                    if (! checkFunc(temp)) {
                        range.push_back(temp);
                    }else {
                        break;
                    }
                    k++;
                }
            }
            break;
        default:
            std::cerr << "Nothing" << std::endl;
            exit(-1);
            break;

    }
    auto it = std::remove_if(range.begin(), range.end(), checkFunc);
    range.erase(it, range.end());
    return range;
}
