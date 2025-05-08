//
// Created by 51092 on 25-5-5.
//

#ifndef PLAYERATTACKCOMPONENT_H
#define PLAYERATTACKCOMPONENT_H
#include "AttackComponent.h"


namespace Game {
    class PlayerAttackComponent : public AttackComponent{
    public:
        bool Attack(GameObject *hitObject) override;
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;
    private:
        GameObject* gameObject;
    };
}


#endif //PLAYERATTACKCOMPONENT_H
