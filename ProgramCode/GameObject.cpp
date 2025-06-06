//
// Created by cai on 25-4-3.
//

#include "GameObject.h"

#include "GUIManager.h"
#include "Component/Component.h"
#include "Component/EnemyStatsComponent.h"


void Game::GameObject::AddComponent(std::unique_ptr<Component>&& component) {
    components.push_back(std::move(component));
}

void Game::GameObject::setGlobalPosition(int x, int y) {
    //这个函数不会在游戏对象的坐标上进行修改
    this->globalPosition.x = x;
    this->globalPosition.y = y;
    this->relativePosition.x = (x - pbh::scenePosX) / pbh::patchWidth;
    this->relativePosition.y = (y - pbh::scenePosY) / pbh::patchHeight;
    //Warning: 这个函数不在游戏交互中的场景中调用，这在设计按钮对象时使用
}

void Game::GameObject::setRelativePosition(int x, int y) {
    this->relativePosition.x = x;
    this->relativePosition.y = y;
    this->globalPosition.x = this->relativePosition.x * pbh::patchWidth + pbh::scenePosX;
    this->globalPosition.y = this->relativePosition.y * pbh::patchHeight + pbh::scenePosY;
    // pbh::DeBug("GameObject globalPosition:", globalPosition.x, globalPosition.y);
}


void Game::GameObject::update() {
    if(components.empty()) {
        return;
    }
    for(auto& component : components) {
        component->update(this);
    }
}

void Game::GameObject::initial() {
    for(auto& component : components) {
        component->initial(this);
    }
}

