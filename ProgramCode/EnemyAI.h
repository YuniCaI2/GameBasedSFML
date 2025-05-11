//
// Created by 51092 on 25-5-8.
//

#ifndef ENEMYAI_H
#define ENEMYAI_H
#include<vector>

#include "pbh.h"
#include "GameObject.h"
//为了保证数据的隔离性，我这里就不直接存储外部的指针，此处只是用传值，输出等方式向外界输出变量
namespace Game {
    class GameObject;
    
    // 简化的敌人数据结构，只存储AI计算所需数据
    struct EnemyData {
        sf::Vector2i position;
        int health;
        pbh::EnemyType type;
        bool alive;
        int originalIndex; // 保存在原始敌人数组中的索引
    };
    
    // 简化的玩家数据结构
    struct PlayerData {
        sf::Vector2i position;
        int health;
    };
    
    class EnemyAI {
    private:
        EnemyAI(){};
    public:
        static EnemyAI* getInstance();
        //Index, x, y
        std::tuple<int, int, int> getAction(std::vector<GameObject*> enemies, GameObject* player);
        //敌人类型，x坐标和y坐标
        std::tuple<pbh::EnemyType, int, int> generateEnemy();
    private:
        // 极大极小算法核心函数
        int minimax(int depth, bool isMaximizing, int alpha, int beta);
        
        // 评估函数 - 评估当前局势对敌人的有利程度
        int evaluateBoard();
        
        // 获取特定敌人的所有可能移动位置
        std::vector<sf::Vector2i> getPossibleMoves(const EnemyData& enemy);
        
        // 判断移动是否会击中玩家
        bool willHitPlayer(const sf::Vector2i& position);
        
        // 曼哈顿距离计算
        int manhattanDistance(const sf::Vector2i& pos1, const sf::Vector2i& pos2);
        
        // 获取特定类型敌人的攻击范围
        std::vector<sf::Vector2i> getAttackRange(const sf::Vector2i& position, pbh::EnemyType type);
        
        int ActionCounter{1};
        int roundCounter{0}; //每次攻击一次增加1，这是为了在合适的时机刷新敌方单位

        std::vector<EnemyData> enemyDatas; // 替代原始的enemies向量
        PlayerData playerData; // 替代原始的player对象
        
        // 极大极小算法的临时变量
        int bestEnemyIndex;
        sf::Vector2i bestMove;
        int maxDepth{5}; // 搜索深度
    };
}

#endif //ENEMYAI_H
