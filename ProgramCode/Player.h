//
// Created by cai on 25-4-3.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <unordered_map>
#include <vector>
#include "GameObject.h"
#include "Item.h"


namespace Game {
    class Player : public GameObject{
    public:
        pbh::PlayerAttribute playerAttribute;
        std::vector<Item*> items;
        void setItem(Item* item);
        std::unordered_map<pbh::chessType, uint32_t> chessNum;


        Player();

        ~Player() override = default;
    };
}



#endif //PLAYER_H
