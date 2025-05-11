//
// Created by 51092 on 25-5-8.
//

#include "EnemyAI.h"
#include "GameObject.h"
#include "Component/EnemyAttackComponent.h"
#include "Component/EnemyStatsComponent.h"
#include "Component/PlayerStatsComponent.h"
#include <random>
#include <algorithm>
#include <limits>
#include <iostream>

Game::EnemyAI * Game::EnemyAI::getInstance() {
    static auto* instance = new EnemyAI();
    return instance;
}

std::tuple<int, int, int> Game::EnemyAI::getAction(std::vector<GameObject *> enemies, GameObject *player) {
    // 清空之前的数据
    enemyDatas.clear();

    // 只提取需要的数据，而不是整个对象拷贝
    for (int i = 0; i < enemies.size(); i++) {
        auto* enemyStats = enemies[i]->getComponent<EnemyStatsComponent>();
        if (enemyStats) {
            EnemyData data;
            data.position = enemies[i]->relativePosition;
            data.health = enemyStats->getCurrentHealth();
            data.type = enemyStats->getEnemyType();
            data.alive = enemyStats->isAlive();
            data.originalIndex = i; // 保存原始索引以便稍后引用

            enemyDatas.push_back(data);
        }
    }

    // 提取玩家数据
    auto* playerStats = player->getComponent<PlayerStatsComponent>();
    if (playerStats) {
        playerData.position = player->relativePosition;
        playerData.health = playerStats->getCurrentHealth();
    }

    // 如果没有敌人，返回无效行动
    if (enemyDatas.empty()) {
        return std::make_tuple(-1, -1, -1);
    }

    // 优先检查是否有敌人可以直接攻击玩家
    for (const auto& enemy : enemyDatas) {
        if (!enemy.alive) continue;

        // 检查是否可以直接攻击玩家
        if (canAttackPlayer(enemy)) {
            std::cerr << "发现可以直接攻击玩家的敌人，选择直接攻击" << std::endl;
            return std::make_tuple(enemy.originalIndex, playerData.position.x, playerData.position.y);
        }
    }

    // 使用极大极小算法寻找最佳行动
    bestEnemyIndex = -1;
    bestMove = sf::Vector2i(-1, -1);

    // 初始alpha和beta值
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    // 调用极大极小算法
    minimax(maxDepth, true, alpha, beta);

    // 如果找到了有效行动，返回该行动
    if (bestEnemyIndex != -1 && bestMove.x != -1 && bestMove.y != -1) {
        for (const auto& data : enemyDatas) {
            if (data.originalIndex == bestEnemyIndex) {
                return std::make_tuple(data.originalIndex, bestMove.x, bestMove.y);
            }
        }
    }

    // 如果没找到有效行动，随机选择一个敌人和其可能的移动
    std::mt19937 gen(std::time(nullptr));
    std::uniform_int_distribution<> distEnemy(0, enemyDatas.size() - 1);
    int randomIndex = distEnemy(gen);

    auto& randomEnemy = enemyDatas[randomIndex];
    auto possibleMoves = getMovablePositions(randomEnemy);

    if (!possibleMoves.empty()) {
        std::uniform_int_distribution<> distMove(0, possibleMoves.size() - 1);
        int randomMoveIndex = distMove(gen);
        return std::make_tuple(randomEnemy.originalIndex, possibleMoves[randomMoveIndex].x, possibleMoves[randomMoveIndex].y);
    }

    // 如果还是没有找到行动，返回无效行动
    return std::make_tuple(-1, -1, -1);
}

std::tuple<pbh::EnemyType, int, int> Game::EnemyAI::generateEnemy() {
    std::mt19937 gen(std::time(nullptr));
    std::uniform_int_distribution<> distPosition(0, 7);
    std::uniform_int_distribution<> distType(0, 3);
    pbh::EnemyType enemyType = static_cast<pbh::EnemyType>(distType(gen));
    auto rt = std::make_tuple(enemyType, distPosition(gen), 0);
    std::cerr << "Enemy generated:" << std::get<1>(rt)  << "," << std::get<2>(rt) << std::endl;
    return rt;
}

int Game::EnemyAI::minimax(int depth, bool isMaximizing, int alpha, int beta) {
    // 终止条件：达到最大深度或游戏结束
    if (depth == 0) {
        return evaluateBoard();
    }

    if (isMaximizing) { // 敌人的回合（最大化分数）
        int maxScore = std::numeric_limits<int>::min();

        // 遍历所有敌人
        for (int i = 0; i < enemyDatas.size(); i++) {
            // 跳过已死亡的敌人
            if (!enemyDatas[i].alive) {
                continue;
            }

            auto originalPosition = enemyDatas[i].position;

            // 优先考虑攻击玩家的移动
            if (canAttackPlayer(enemyDatas[i])) {
                // 直接选择攻击玩家的行动
                if (depth == maxDepth) {
                    bestEnemyIndex = enemyDatas[i].originalIndex;
                    bestMove = playerData.position;
                }

                // 临时应用移动（假设攻击玩家）
                enemyDatas[i].position = playerData.position;

                // 递归评估此移动
                int score = minimax(depth - 1, false, alpha, beta) + 500; // 给予额外奖励

                // 撤消移动
                enemyDatas[i].position = originalPosition;

                if (score > maxScore) {
                    maxScore = score;
                }

                // Alpha-Beta剪枝
                alpha = std::max(alpha, maxScore);
                if (beta <= alpha) {
                    return maxScore; // 提前返回，优先考虑攻击玩家
                }
            }

            // 获取可移动位置
            auto possibleMoves = getMovablePositions(enemyDatas[i]);

            // 遍历当前敌人的所有可能移动
            for (const auto& move : possibleMoves) {
                // 临时应用移动
                enemyDatas[i].position = move;

                // 检查移动后是否可以攻击玩家
                int moveScore = 0;
                if (canAttackPlayerFromPosition(move, enemyDatas[i].type)) {
                    moveScore = 300; // 移动后可以攻击玩家，给予额外奖励
                }

                // 递归评估此移动
                int score = minimax(depth - 1, false, alpha, beta) + moveScore;

                // 撤消移动
                enemyDatas[i].position = originalPosition;

                // 更新最高分数和最佳移动
                if (score > maxScore) {
                    maxScore = score;
                    if (depth == maxDepth) { // 只在顶层更新最佳行动
                        bestEnemyIndex = enemyDatas[i].originalIndex;
                        bestMove = move;
                    }
                }

                // Alpha-Beta剪枝
                alpha = std::max(alpha, maxScore);
                if (beta <= alpha) {
                    break;
                }
            }
        }

        return maxScore;
    } else { // 玩家的回合（最小化分数）
        int minScore = std::numeric_limits<int>::max();

        // 获取玩家可能的移动（这里简化为周围8个格子）
        sf::Vector2i playerPos = playerData.position;
        std::vector<sf::Vector2i> playerMoves;

        // 简化的玩家移动，这里假设玩家可以移动到周围一格
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int nx = playerPos.x + dx;
                int ny = playerPos.y + dy;

                // 检查是否在棋盘内
                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                    playerMoves.push_back(sf::Vector2i(nx, ny));
                }
            }
        }

        auto originalPlayerPos = playerData.position;

        // 遍历玩家的所有可能移动
        for (const auto& move : playerMoves) {
            // 检查是否有敌人在这个位置
            bool enemyInPosition = false;
            for (const auto& enemy : enemyDatas) {
                if (enemy.alive && enemy.position == move) {
                    enemyInPosition = true;
                    break;
                }
            }

            // 如果位置被敌人占据，玩家不能移动到那里
            if (enemyInPosition) continue;

            // 临时应用移动
            playerData.position = move;

            // 递归评估此移动
            int score = minimax(depth - 1, true, alpha, beta);

            // 撤消移动
            playerData.position = originalPlayerPos;

            // 更新最低分数
            minScore = std::min(minScore, score);

            // Alpha-Beta剪枝
            beta = std::min(beta, minScore);
            if (beta <= alpha) {
                break;
            }
        }

        return minScore;
    }
}

int Game::EnemyAI::evaluateBoard() {
    int score = 0;

    // 评估每个敌人的状态
    for (const auto& enemy : enemyDatas) {
        if (!enemy.alive) continue;

        // 根据敌人类型和生命值增加分数
        score += enemy.health * 10;

        // 根据敌人类型给予不同的权重
        switch (enemy.type) {
            case pbh::EnemyType::Rook:
                score += 40;
                break;
            case pbh::EnemyType::Bishop:
                score += 30;
                break;
            case pbh::EnemyType::Knight:
                score += 30;
                break;
            case pbh::EnemyType::Pawn:
                score += 10;
                break;
        }

        // 如果敌人已经在玩家位置（可以攻击玩家）
        if (isPositionEqualToPlayer(enemy.position)) {
            score += 500; // 大幅提高权重
        }

        // 如果敌人可以攻击玩家，增加分数
        if (canAttackPlayer(enemy)) {
            score += 300;
        }

        // 检查移动一步后是否可以攻击玩家
        auto possibleMoves = getMovablePositions(enemy);
        for (const auto& move : possibleMoves) {
            if (canAttackPlayerFromPosition(move, enemy.type)) {
                score += 100; // 移动一步后可以攻击玩家
                break;
            }
        }

        // 如果敌人距离玩家更近，增加分数
        int distance = manhattanDistance(enemy.position, playerData.position);
        score += (10 - std::min(distance, 10)) * 5; // 距离越近，得分越高
    }

    // 考虑玩家的生命值
    score -= playerData.health * 30; // 玩家生命值越高，敌人评分越低

    return score;
}

// 检查位置是否与玩家位置相同
bool Game::EnemyAI::isPositionEqualToPlayer(const sf::Vector2i& position) {
    return position == playerData.position;
}

// 检查敌人是否可以从当前位置攻击玩家
bool Game::EnemyAI::canAttackPlayer(const EnemyData& enemy) {
    auto attackRange = getAttackRange(enemy.position, enemy.type);
    return std::find(attackRange.begin(), attackRange.end(), playerData.position) != attackRange.end();
}

// 检查从指定位置是否可以攻击玩家
bool Game::EnemyAI::canAttackPlayerFromPosition(const sf::Vector2i& position, pbh::EnemyType type) {
    auto attackRange = getAttackRange(position, type);
    return std::find(attackRange.begin(), attackRange.end(), playerData.position) != attackRange.end();
}

// 获取可移动位置（排除已被其他敌人占据的位置）
std::vector<sf::Vector2i> Game::EnemyAI::getMovablePositions(const EnemyData& enemy) {
    auto positions = getAttackRange(enemy.position, enemy.type);

    // 移除已被其他敌人占据的位置
    positions.erase(
        std::remove_if(positions.begin(), positions.end(),
            [this](const sf::Vector2i& pos) {
                // 检查位置是否被其他敌人占据
                for (const auto& e : this->enemyDatas) {
                    if (e.alive && e.position == pos) {
                        return true; // 移除此位置
                    }
                }
                return false;
            }
        ),
        positions.end()
    );

    return positions;
}

std::vector<sf::Vector2i> Game::EnemyAI::getPossibleMoves(const EnemyData& enemy) {
    // 分开处理移动和攻击
    auto positions = getAttackRange(enemy.position, enemy.type);

    // 特殊处理：攻击玩家
    // 如果玩家在攻击范围内，优先返回玩家位置
    if (std::find(positions.begin(), positions.end(), playerData.position) != positions.end()) {
        std::vector<sf::Vector2i> attackPlayer = {playerData.position};
        return attackPlayer;
    }

    // 否则返回可移动位置（排除被其他敌人占据的位置）
    return getMovablePositions(enemy);
}

int Game::EnemyAI::manhattanDistance(const sf::Vector2i& pos1, const sf::Vector2i& pos2) {
    return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

std::vector<sf::Vector2i> Game::EnemyAI::getAttackRange(const sf::Vector2i& position, pbh::EnemyType type) {
    std::vector<sf::Vector2i> range;
    std::vector<sf::Vector2i> knightPositions;
    std::vector<sf::Vector2i> bishopPositions;
    std::vector<sf::Vector2i> rookPositions;

    // 更改函数名以更清晰表达其意图
    auto isOutOfBounds = [](sf::Vector2i n) {
        if (n.x >= 0 && n.x < 8 && n.y >= 0 && n.y < 8) {
            return false; // 位置在棋盘内
        } else {
            return true;  // 位置在棋盘外
        }
    };

    switch (type) {
        case pbh::EnemyType::Pawn:
            range.clear();
            // 注意：兵只能向前移动，这里假设"向前"是y增加的方向
            range.push_back(position + sf::Vector2i(1, 1));
            range.push_back(position + sf::Vector2i(-1, 1));
            break;
        case pbh::EnemyType::Knight:
            range.clear();
            knightPositions = {
                {-1, -2}, {1, -2}, {2, -1}, {2, 1},
                {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}
            };
            for (auto& p : knightPositions) {
                range.push_back(position + p);
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
                    sf::Vector2i temp = position + k * p;
                    if (!isOutOfBounds(temp)) {
                        range.push_back(temp);

                        // 检查是否碰到了玩家或敌人，如果是则停止在该方向上继续移动
                        bool hitSomething = false;

                        // 检查是否碰到玩家
                        if (temp == playerData.position) {
                            hitSomething = true;
                        }

                        // 检查是否碰到其他敌人
                        for (const auto& enemy : enemyDatas) {
                            if (enemy.alive && enemy.position == temp) {
                                hitSomething = true;
                                break;
                            }
                        }

                        if (hitSomething) {
                            break; // 停止在这个方向上继续移动
                        }
                    } else {
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
                    sf::Vector2i temp = position + k * p;
                    if (!isOutOfBounds(temp)) {
                        range.push_back(temp);

                        // 检查是否碰到了玩家或敌人，如果是则停止在该方向上继续移动
                        bool hitSomething = false;

                        // 检查是否碰到玩家
                        if (temp == playerData.position) {
                            hitSomething = true;
                        }

                        // 检查是否碰到其他敌人
                        for (const auto& enemy : enemyDatas) {
                            if (enemy.alive && enemy.position == temp) {
                                hitSomething = true;
                                break;
                            }
                        }

                        if (hitSomething) {
                            break; // 停止在这个方向上继续移动
                        }
                    } else {
                        break;
                    }
                    k++;
                }
            }
            break;
        default:
            std::cerr << "Unknown enemy type" << std::endl;
            break;
    }

    // 移除超出棋盘范围的位置
    auto it = std::remove_if(range.begin(), range.end(), isOutOfBounds);
    range.erase(it, range.end());
    return range;
}