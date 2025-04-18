//
// Created by cai on 25-4-3.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "GameObject.h"
#include "pbh.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

#include "./Enemy.h"

namespace Game {
    class Scene {
    public:
        Scene& setPlayer(Player* player);
        Scene& setLevel(uint8_t level);
        Scene& setName(const std::string& name);
        Scene& setSprite(const std::string& spritePath);
        Scene& addEnemy(const std::shared_ptr<Enemy>& enemy);
        Scene& addObject(const std::shared_ptr<GameObject>& object);

        pbh::SceneType getSceneType() const;
        sf::Sprite getSprite() const;
        std::vector<std::shared_ptr<GameObject>> getObjects() const;
    private:
        pbh::SceneType sceneType{};
        uint8_t level;
        std::string name;
        sf::Texture textureData;
        sf::Sprite sprite;
        std::vector<std::shared_ptr<GameObject>> objects;
        std::vector<std::shared_ptr<Enemy>> enemies;
        Player* playerPtr;//这里为了保证玩家的唯一性

    };
}


#endif //SCENE_H
