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
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen
    };

    enum SceneType {
        Draw,
        Fight,
        Main
    };


}

#endif //PBH_H
