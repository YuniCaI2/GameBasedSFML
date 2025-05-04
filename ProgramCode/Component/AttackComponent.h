//
// Created by cai on 25-4-25.
//

#ifndef ATTACHCOMPONENT_H
#define ATTACHCOMPONENT_H
#include "Component.h"


namespace Game {
    class GameObject;
}

namespace Game {
    class AttackComponent: public Component{
    public:
        virtual bool Attack(GameObject* hitObject) = 0;//返回是否攻击到对方
    };
}


#endif //ATTACHCOMPONENT_H
