//
// Created by cai on 25-4-3.
//

#include "GameObject.h"
#include "Component/Component.h"


void Game::GameObject::AddComponent(Component* component) {
    components.push_back(component);
}

void Game::GameObject::setGlobalPosition(int x, int y) {
    //这个函数不会在游戏对象的坐标上进行修改
}

void Game::GameObject::setRelativePosition(int x, int y) {
    this->relativePosition.x = x;
    this->relativePosition.y = y;
    this->globalPosition.x = this->relativePosition.x * pbh::patchWidth + pbh::scenePosX;
    this->globalPosition.y = this->relativePosition.y * pbh::patchHeight + pbh::scenePosY;
}


void Game::GameObject::update() {
    for(auto& component : components) {
        component->update(this);
    }
}

void Game::GameObject::initial() {
}