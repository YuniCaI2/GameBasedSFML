//
// Created by cai on 25-4-7.
//

#ifndef ATTRIBUTEMODIFYITEM_H
#define ATTRIBUTEMODIFYITEM_H
#include <functional>

#include "Item.h"


namespace Game {
    class AttributeModifyItem : public Item {
        std::function<void(pbh::PlayerAttribute&)> modifyFunction;
    public:
        using Item::Item;
        void registerModifyFunction(const std::function<void(pbh::PlayerAttribute&)>& func);
        decltype(auto) getModifyFunction();
    };
}



#endif //ATTRIBUTEMODIFYITEM_H
