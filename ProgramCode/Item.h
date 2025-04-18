//
// Created by cai on 25-4-7.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "pbh.h"

enum ItemType {
    AttributeModifier, // 属性修改
    AttackModeChange, // 攻击方式改变
    SpecialAbility // 特殊能力
};

namespace Game {
    class Item {
        std::string name;
        std::string description;
    public:

        [[nodiscard]] std::string getName() const;
        [[nodiscard]] std::string getDescription() const;

        virtual ItemType getItemType() const = 0;
        virtual ~Item() = default;
    };
}


#endif //ITEM_H
