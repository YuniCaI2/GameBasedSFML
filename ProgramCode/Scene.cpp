//
// Created by cai on 25-4-3.
//

#include "Scene.h"


Game::Scene & Game::Scene::setPlayer(Player* player) {
    this->playerPtr = player;
    return *this;
}

Game::Scene & Game::Scene::setLevel(uint8_t level) {
    this->level = level;
    return *this;
}

Game::Scene & Game::Scene::setName(const std::string& name) {
    this->name = name;
    return *this;
}

Game::Scene & Game::Scene::setSprite(const std::string& spritePath) {
    if(! textureData.loadFromFile(spritePath)) {
        std::cerr << "Failed to load sprite texture" << std::endl;
        exit(-1);
    }
    sprite.setTexture(textureData);
    auto curSize = textureData.getSize();
    auto scaleX =  pbh::sceneW / static_cast<float>(curSize.x);
    auto scaleY = pbh::sceneH / static_cast<float>(curSize.y);
    pbh::DeBug("Size:", scaleX, scaleY);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(pbh::scenePosX, pbh::scenePosY);

    return *this;
}

Game::Scene & Game::Scene::addEnemy(const std::shared_ptr<Enemy> &enemy) {
    enemies.push_back(enemy);
    objects.push_back(enemy);
    return *this;
}

Game::Scene & Game::Scene::addObject(const std::shared_ptr<GameObject> &object) {
    this->objects.push_back(object);
    return *this;
}

pbh::SceneType Game::Scene::getSceneType()  const{
    return sceneType;
}

sf::Sprite Game::Scene::getSprite() const {
    return sprite;
}

std::vector<std::shared_ptr<Game::GameObject>> Game::Scene::getObjects() const {
    return objects;
}
