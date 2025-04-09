//
// Created by cai on 25-4-7.
//

#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include <vector>

#include "GameObject.h"


namespace Game {
    class RenderEngine {
        RenderEngine() = default;
    public:
        static RenderEngine* getInstance();
    };
}


#endif //RENDERENGINE_H
