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
        uint8_t level;
        std::string name;
        pbh::Texture map;
        std::vector<GameObject*> gameObjects;
    };
}



#endif //SCENE_H
