//
// Created by cai on 25-4-7.
//

#include "AttributeModifyItem.h"

void Game::AttributeModifyItem::registerModifyFunction(const std::function<void(pbh::PlayerAttribute &)>& func) {
     modifyFunction = func;
}

decltype(auto) Game::AttributeModifyItem::getModifyFunction() {
    return modifyFunction;
}
