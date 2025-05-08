//
// Created by cai on 25-4-3.
//

#include "Scene.h"

#include "Component/EnemyStatsComponent.h"
#include "Component/StatsComponent.h"


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



Game::Scene & Game::Scene::addObject(GameObject* object) {
    this->objects.push_back(object);
    return *this;
}

Game::Scene & Game::Scene::setPlayer(GameObject *player) {
    this->objects.push_back(player);
    this->player = player;
    return *this;
}

Game::Scene & Game::Scene::addEnemy(GameObject *enemy) {
    this->enemies.push_back(enemy);
    this->objects.push_back(enemy);
    return *this;
}

Game::Scene & Game::Scene::setEnemies(const std::vector<GameObject *> &enemies) {
    this->enemies = enemies;
    this->objects.insert(objects.end(), enemies.begin(), enemies.end());
    return *this;
}

Game::Scene & Game::Scene::setSceneType(pbh::SceneType sceneType) {
    this->sceneType = sceneType;
    return *this;
}

pbh::SceneType Game::Scene::getSceneType(){
    return sceneType;
}

sf::Sprite Game::Scene::getSprite(){
    return sprite;
}

std::vector<Game::GameObject*> Game::Scene::getObjects(){
    return objects;
}

std::vector<Game::GameObject *> Game::Scene::getEnemies() {
    return enemies;
}

void Game::Scene::clearDeadEnemies() {
    auto check = [](GameObject* enemy) {
        auto stats = enemy->getComponent<EnemyStatsComponent>();
        if (stats == nullptr)
            return false;
        if (! stats->isAlive())
            std::cerr << "Checking enemy at " << enemy << std::endl;
        return (! stats->isAlive());
    };
    auto it = std::remove_if(enemies.begin(), enemies.end(), check); //删除敌人列表中的对象
    if (it == enemies.end()) {
        return;
    }
    // std::cerr << "Size enemies" << enemies.size() << std::endl;
    // std::cerr << "delete from enemies:" << it - enemies.begin() << std::endl;
    enemies.erase(it, enemies.end());
    auto it2 = std::remove_if(objects.begin(), objects.end(), check);//删除场景中游戏对象中的对象
    // std::cerr << "Size objects" << objects.size() << std::endl;
    // std::cerr << "delete from objects:" << it - objects.begin() << std::endl;
    objects.erase(it2, objects.end());
}
