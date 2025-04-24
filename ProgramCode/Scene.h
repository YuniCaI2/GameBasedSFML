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

    };
}


#endif //SCENE_H
