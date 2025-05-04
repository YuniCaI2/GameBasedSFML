//
// Created by cai on 25-4-25.
//

#ifndef PLAYERMOVECOMPONENT_H
#define PLAYERMOVECOMPONENT_H
#include "MoveComponent.h"


namespace Game {
    class PlayerMoveComponent: public MoveComponent{
    public:
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;
        void moveTo(int x, int y) override;
    private:
    };
}



#endif //PLAYERMOVECOMPONENT_H
