//
// Created by cai on 25-4-25.
//

#ifndef ATTACHCOMPONENT_H
#define ATTACHCOMPONENT_H


namespace Game {
    class GameObject;
}

namespace Game {
    class AttackComponent {
    public:
        virtual bool Attack(GameObject* hitObject) = 0;//返回是否攻击到对方

    protected:
        int damage;
    };
}


#endif //ATTACHCOMPONENT_H
