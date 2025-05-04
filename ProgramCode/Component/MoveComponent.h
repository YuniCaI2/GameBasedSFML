//
// Created by cai on 25-4-25.
//

#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H
#include "Component.h"

namespace Game {
    class MoveComponent : public Component {
    public:
        virtual void moveTo(int x, int y) = 0;
    protected:


    };
}


#endif //MOVECOMPONENT_H
