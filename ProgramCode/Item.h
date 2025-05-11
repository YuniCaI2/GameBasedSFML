//
// Created by 51092 on 25-5-11.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include"pbh.h"
namespace Game {
    struct Item {
        sf::Texture texture;

        std::wstring name;
        std::wstring description;
        pbh::ItemType type;

        int addMoveAttribute{0};
        int addAttackNum{0};
        int addAttack{0};

        void setType(pbh::ItemType type) {
            switch (type) {
                case pbh::ItemType::Normal:
                    addAttackNum++;
                    addMoveAttribute++;
                    name = L"普通皇后";
                    description = L"增加1攻击次数\n增加1移动次数";
                    texture.loadFromFile(pbh::ItemTexTable[pbh::ItemType::Normal]);
                    this->type = pbh::ItemType::Normal;
                    break;
                case pbh::ItemType::Move:
                    addMoveAttribute += 2;
                    name = L"狂暴皇后";
                    description = L"增加两点移动次数";
                    texture.loadFromFile(pbh::ItemTexTable[pbh::ItemType::Move]);
                    this->type = pbh::ItemType::Move;
                    break;
                default:
                    break;
            }
        }
    };
}

#endif //ITEM_H
