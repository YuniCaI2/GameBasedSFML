//
// Created by cai on 25-4-3.
//

#include "GameObject.h"
#include "Component.h"


void Game::GameObject::AddComponent(std::unique_ptr<Component> &&component) {
    components.push_back(std::move(component));
}

template<typename T>
const T * Game::GameObject::getComponent() {
    for (auto& component : components) {
        if (dynamic_cast<T*>(component.get())) {
            return dynamic_cast<T*>(component.get());
        }
    }
    return nullptr;
}

void Game::GameObject::update() {
    for(auto& component : components) {
        component->update();
    }
}

void Game::GameObject::initial() {
}