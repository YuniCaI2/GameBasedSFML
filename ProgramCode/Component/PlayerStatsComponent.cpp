//
// Created by 51092 on 25-4-26.
//

#include "PlayerStatsComponent.h"

Game::PlayerStatsComponent::PlayerStatsComponent(int maxHealth, int maxMoveNum, int maxAttackNum) {
    this->maxHealth = maxHealth;
    this->currentHealth = maxHealth;
    this->maxAttackNum = maxAttackNum;
    this->maxMoveNum = maxMoveNum;
    this->currentAttackNum = maxAttackNum;
    this->currentMoveNum = maxMoveNum;
}

void Game::PlayerStatsComponent::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;

}

void Game::PlayerStatsComponent::setCurrentHealth(int currentHealth) {
    this->currentHealth = currentHealth;
}

void Game::PlayerStatsComponent::setMoveNum(int moveNum) {
    this->maxMoveNum = moveNum;
}

void Game::PlayerStatsComponent::setCurrentMoveNum(int currentMoveNum) {
    this->currentMoveNum = currentMoveNum;
}

void Game::PlayerStatsComponent::setAttackNum(int attackNum) {
    this->maxAttackNum = attackNum;
}

void Game::PlayerStatsComponent::setCurrentAttackNum(int attackNum) {
    this->currentAttackNum =attackNum;
}

int Game::PlayerStatsComponent::getMaxHealth() const {
    return maxHealth;
}

int Game::PlayerStatsComponent::getAttackNum() const {
    return currentAttackNum;
}

int Game::PlayerStatsComponent::getCurrentHealth() const {
    return currentHealth;
}

int Game::PlayerStatsComponent::getMoveNum() const {
    return currentMoveNum;
}


void Game::PlayerStatsComponent::update(GameObject *gameObject) {

}

bool Game::PlayerStatsComponent::isAlive() const {
    if (currentHealth <= 0) {
        return false;
    }
    return true;
}


void Game::PlayerStatsComponent::turnStart() {
    for (auto& i : items) {
        maxAttackNum += i.addAttackNum;
        maxMoveNum += i.addMoveAttribute;
    }
    currentMoveNum = maxMoveNum;
    currentAttackNum = maxAttackNum;
}

void Game::PlayerStatsComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    maxHealth = 5;
    maxAttackNum = 2;
    maxMoveNum = 1;
}

void Game::PlayerStatsComponent::addKill() {
    killNum++;
}

int Game::PlayerStatsComponent::getKillNum() const {
    return killNum;
}

int Game::PlayerStatsComponent::setKillNum(int killNum) {
    return this->killNum = killNum;
}

void Game::PlayerStatsComponent::addItem(Item item) {
    items.push_back(item);
}

std::vector<Game::Item> Game::PlayerStatsComponent::getItems() {
    return items;
}
