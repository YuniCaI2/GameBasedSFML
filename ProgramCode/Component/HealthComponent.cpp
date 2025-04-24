//
// Created by 51092 on 25-4-24.
//

#include "HealthComponent.h"

Game::HealthComponent::HealthComponent(int maxHealth, int currentHealth) {
    this->health = currentHealth;
    this->maxHealth = maxHealth;
}

void Game::HealthComponent::setHealth(int health) {
    this->health = health;
}

void Game::HealthComponent::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
}

int & Game::HealthComponent::getCurrentHealth() {
    return health;
}

int Game::HealthComponent::getMaxHealth() const {
    return maxHealth;
}

void Game::HealthComponent::update(GameObject *gameObject) {

}
