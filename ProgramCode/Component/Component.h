//
// Created by 51092 on 25-4-24.
//

#ifndef COMPONET_H
#define COMPONET_H
#include "../GameObject.h"


namespace Game {
    class Component {
    public:
        virtual void initial(GameObject* gameObject) = 0;
        virtual void update(GameObject* gameObject) = 0;
        virtual ~Component() = default;

    protected:
        GameObject* gameObject;
    };
}



#endif //COMPONET_H
