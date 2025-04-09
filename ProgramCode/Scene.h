//
// Created by cai on 25-4-3.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "GameObject.h"

namespace Game {
    class Scene {
    public:
        std::vector<GameObject*> gameObjects;
    };
}



#endif //SCENE_H
