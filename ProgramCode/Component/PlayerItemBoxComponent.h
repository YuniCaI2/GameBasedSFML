//
// Created by 51092 on 25-5-11.
//

#ifndef PLAYERITEMBOXCOMPONENT_H
#define PLAYERITEMBOXCOMPONENT_H
#include "Component.h"


namespace Game {
    class PlayerItemBoxComponent :public Component{
    public:
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;


    };
}



#endif //PLAYERITEMBOXCOMPONENT_H
