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
        // 返回原始敌人数组中的索引
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
    auto possibleMoves = getPossibleMoves(randomEnemy);
    
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
            auto possibleMoves = getPossibleMoves(enemyDatas[i]);
            
            // 遍历当前敌人的所有可能移动
            for (const auto& move : possibleMoves) {
                // 临时应用移动
                enemyDatas[i].position = move;
                
                // 递归评估此移动
                int score = minimax(depth - 1, false, alpha, beta);
                
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
        
        // 如果敌人可以攻击玩家，增加分数
        if (willHitPlayer(enemy.position)) {
            score += 10000;
        }
        
        // 如果敌人距离玩家更近，增加分数
        int distance = manhattanDistance(enemy.position, playerData.position);
        score += (10 - std::min(distance, 10)) * 5; // 距离越近，得分越高
    }
    
    // 考虑玩家的生命值
    score -= playerData.health * 30; // 玩家生命值越高，敌人评分越低
    
    return score;
}

std::vector<sf::Vector2i> Game::EnemyAI::getPossibleMoves(const EnemyData& enemy) {
    return getAttackRange(enemy.position, enemy.type);
}

bool Game::EnemyAI::willHitPlayer(const sf::Vector2i& position) {
    return position == playerData.position;
}

int Game::EnemyAI::manhattanDistance(const sf::Vector2i& pos1, const sf::Vector2i& pos2) {
    return std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
}

std::vector<sf::Vector2i> Game::EnemyAI::getAttackRange(const sf::Vector2i& position, pbh::EnemyType type) {
    std::vector<sf::Vector2i> range;
    std::vector<sf::Vector2i> knightPositions;
    std::vector<sf::Vector2i> bishopPositions;
    std::vector<sf::Vector2i> rookPositions;
    
    auto checkFunc = [](sf::Vector2i n) {
        if (n.x >= 0 && n.x < 8 && n.y >= 0 && n.y < 8) {
            return false;
        } else {
            return true;
        }
    }; // 用来检测是否越界

    switch (type) {
        case pbh::EnemyType::Pawn:
            range.clear();
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
                    if (!checkFunc(temp)) {
                        range.push_back(temp);
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
                    if (!checkFunc(temp)) {
                        range.push_back(temp);
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
    
    auto it = std::remove_if(range.begin(), range.end(), checkFunc);
    range.erase(it, range.end());
    return range;
}



