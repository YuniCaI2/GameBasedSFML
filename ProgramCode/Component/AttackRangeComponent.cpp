//
// Created by 51092 on 25-5-3.
//

#include "AttackRangeComponent.h"
#include "WeaponComponent.h"

sf::Vector2f relativeToGlobal(sf::Vector2i relativePosition) {
    sf::Vector2f globalPosition;
    globalPosition.x = relativePosition.x * pbh::patchWidth + pbh::scenePosX;
    globalPosition.y = relativePosition.y * pbh::patchHeight + pbh::scenePosY;

    return globalPosition;
}

void Game::AttackRangeComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;

    block.setSize(sf::Vector2f(50, 50));
    block.setFillColor(sf::Color(144, 238, 144, 102));
}

void Game::AttackRangeComponent::update(GameObject *gameObject) {
    auto weapon = gameObject->getComponent<WeaponComponent>();
    auto position = gameObject->relativePosition;
    auto currentWeapon = weapon->getSelectedWeapon();
    std::vector<sf::Vector2i> positions;

    // 清空之前的矩形
    rectangles.clear();
    AttackRangePositions.clear();

    // 将变量声明移到switch外部
    std::vector<sf::Vector2i> knightPositions;
    std::vector<sf::Vector2i> bishopPositions;
    std::vector<sf::Vector2i> rookPositions;

    switch (currentWeapon) {
        case pbh::WeaponType::Pawn:
            positions.clear();
            for (int i = 0; i < 2; ++i) {
                positions.push_back(position + sf::Vector2i(1, -1));
                positions.push_back(position + sf::Vector2i(-1, -1));
            }
            for (auto& p : positions) {
                if (p.x >= 0 && p.x <= 7 && p.y >= 0 && p.y <= 7) {
                    block.setPosition(relativeToGlobal(p));
                    AttackRangePositions.push_back(p);
                    rectangles.push_back(block);
                }
            }
            MatchEnemy = pbh::EnemyType::Pawn;
            break;
        case pbh::WeaponType::Knight:
            positions.clear();
            knightPositions = {
                {-1, -2}, {1, -2}, {2, -1}, {2, 1},
                {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}
            };
            for (auto& p : knightPositions) {
                positions.push_back(position + p);
            }
            for (auto& p : positions) {
                if (p.x >= 0 && p.x <= 7 && p.y >= 0 && p.y <= 7) {
                    AttackRangePositions.push_back(p);
                    block.setPosition(relativeToGlobal(p));
                    rectangles.push_back(block);
                }
            }
            MatchEnemy = pbh::EnemyType::Knight;
            break;
        case pbh::WeaponType::Bishop:
            positions.clear();
            bishopPositions = {
                {1,1}, {1, -1}, {-1, -1}, {-1, 1}
            };
            for (auto& p : bishopPositions) {
                int k = 1;
                while (true) {
                    sf::Vector2i temp = position + k * p;
                    if (temp.x >= 0 && temp.x <= 7 && temp.y >= 0 && temp.y <= 7) {
                        AttackRangePositions.push_back(temp);
                        block.setPosition(relativeToGlobal(temp));
                        rectangles.push_back(block);
                    }else {
                        break;
                    }
                    k++;
                }
            }
            MatchEnemy = pbh::EnemyType::Bishop;
            break;
        case pbh::WeaponType::Rook:
            positions.clear();
            rookPositions = {
                {1,0}, {-1, 0}, {0, 1}, {0, -1}
            };
            for (auto& p : rookPositions) {
                int k = 1;
                while (true) {
                    sf::Vector2i temp = position + k * p;
                    if (temp.x >= 0 && temp.x <= 7 && temp.y >= 0 && temp.y <= 7) {
                        AttackRangePositions.push_back(temp);
                        block.setPosition(relativeToGlobal(temp));
                        rectangles.push_back(block);
                    }else {
                        break;
                    }
                    k++;
                }
            }
            MatchEnemy = pbh::EnemyType::Rook;
            break;
        default:
            std::cerr << "Nothing" << std::endl;
            break;
    }
}

std::vector<sf::Vector2i> Game::AttackRangeComponent::getAttackRangePositions() const {
    return AttackRangePositions;
}

std::vector<sf::RectangleShape> Game::AttackRangeComponent::getRectangles() const {
    return rectangles;
}

pbh::EnemyType Game::AttackRangeComponent::getMatchEnemy() {
    return MatchEnemy;
}
