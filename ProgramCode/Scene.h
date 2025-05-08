//
// Created by cai on 25-4-3.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "GameObject.h"
#include "pbh.h"
#include <SFML/Graphics.hpp>


namespace Game {
    class Scene {
    public:
        Scene& setLevel(uint8_t level);
        Scene& setName(const std::string& name);
        Scene& setSprite(const std::string& spritePath);
        Scene& addObject(GameObject* object);
        Scene& setPlayer(GameObject* player);
        Scene& addEnemy(GameObject* enemy);
        Scene& setEnemies(const std::vector<GameObject*>& enemies);
        Scene& setSceneType(pbh::SceneType sceneType);
        pbh::SceneType getSceneType();
        sf::Sprite getSprite();
        std::vector<GameObject*> getObjects();
    private:
        pbh::SceneType sceneType{pbh::Fight};
        uint8_t level;
        std::string name;
        sf::Texture textureData;
        sf::Sprite sprite;
        std::vector<GameObject*> objects;
        GameObject* player;
        std::vector<GameObject*> enemies;

    };
}


#endif //SCENE_H
