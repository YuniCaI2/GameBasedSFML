//
// Created by cai on 25-4-3.
//

#ifndef PBH_H
#define PBH_H
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <sys/types.h>

namespace pbh {
    using Vector2 = sf::Vector2f;
    using ActionID = uint32_t;
    using ItemID = uint32_t;
    struct Texture {
        std::string texName = " ";
        int width = -1, height = -1;
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

    enum chessType {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen
    };



}

#endif //PBH_H
