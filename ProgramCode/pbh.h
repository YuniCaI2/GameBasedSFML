//
// Created by cai on 25-4-3.
//

#ifndef PBH_H
#define PBH_H
#include <iostream>
#include <ostream>
#include <string>
#include<vector>
#include<SFML/Graphics.hpp>
#include<unordered_map>

namespace pbh {
    using ActionID = uint32_t;
    using ItemID = uint32_t;
    constexpr float PI = 3.1415926535897932384626433832795f;
    constexpr int patchHeight = 100 / 2;
    constexpr int patchWidth = 100 / 2;
    constexpr int sceneH = 800 / 2;
    constexpr int sceneW = 800 / 2;
    constexpr int scenePosX = 400 / 2;
    constexpr int scenePosY = 300 / 2;


    //DeBugFunc
    inline void DeBug(const std::string& info) {
        std::cout << info << std::endl;
    }

    inline void DeBug(const std::string& info, auto x , auto y) {
        std::cout << info << "Pos:" << x << ", " << y << std::endl;
    }

    struct gameObjectSpirit {
        sf::Texture texture;
        sf::Sprite sprite;
    };

    struct PlayerAttribute {
        uint32_t maxHealth = 3;
        uint32_t currentHealth = 3;
        uint32_t moveNum = 1;
        uint32_t attackNum = 1;
        uint32_t moveStride = 1;
        uint32_t maxItem = 3;
        uint32_t currentItemNum = 0;
    };

    struct enemyAttribute {
        uint32_t maxHealth;
        uint32_t currentHealth;
    };



    struct SceneLayout {
    };

    enum chessType {
        Pawn,//小兵
        Knight,//骑士
        Bishop,//相
        Rook,//车
        Queen
    };

    enum class EnemyType {
        Pawn,//小兵
        Knight,//骑士
        Bishop,//相
        Rook,//车
    };
    //敌人类型和武器类型一一对应

    enum SceneType {
        Shop,
        Fight,
        Main,
        Stop
    };

    enum class WeaponType {
        Pawn,   //小兵
        Knight, //骑士
        Bishop, // 相
        Rook,   //车
    };

    enum class ItemType {
        Normal,
        Attack,
        Move
    };

    inline std::unordered_map<ItemType, std::string> ItemTexTable = {
        {ItemType::Normal, "../resource/main/queen_1.png"},
        {ItemType::Move, "../resource/main/queen_2.png"}
    };

    inline std::unordered_map<EnemyType, std::pair<std::string, std::string>> enemyTexPathTable = {
        {EnemyType::Pawn, {"../resource/GameObject/Enemy/Pawn.png","../resource/GameObject/Enemy/PawnSelected.png"}},
        {EnemyType::Knight, {"../resource/GameObject/Enemy/Knight.png","../resource/GameObject/Enemy/KnightSelected.png"}},
        {EnemyType::Bishop, {"../resource/GameObject/Enemy/Bishop.png","../resource/GameObject/Enemy/BishopSelected.png"}},
        {EnemyType::Rook, {"../resource/GameObject/Enemy/Rook.png","../resource/GameObject/Enemy/RookSelected.png"}},
    };

    template<typename T>
    inline bool checkVector(const std::vector<T>& arr) {
        auto last = arr[0];
        for(int i = 1; i < arr.size(); i++) {
            if(last == arr[i]) {
                return false;
            }
        }
        return true;
    }

}

#endif //PBH_H
