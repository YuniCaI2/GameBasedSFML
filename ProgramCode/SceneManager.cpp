//
// Created by cai on 25-4-7.
//

#include "SceneManager.h"

Game::SceneManager::SceneManager() {
}

void Game::SceneManager::SwitchToFightScene() {
}

void Game::SceneManager::SwitchToMainScene() {
}

void Game::SceneManager::SwitchToShopScene() {
}

Game::Player * Game::SceneManager::getPlayer(){
    return &player;
}

Game::SceneManager * Game::SceneManager::getInstance() {
    static auto sceneManager = new Game::SceneManager();
    return sceneManager;
}

