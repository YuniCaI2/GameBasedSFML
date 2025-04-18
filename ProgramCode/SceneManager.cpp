//
// Created by cai on 25-4-7.
//

#include "SceneManager.h"

Game::SceneManager::SceneManager() {

}


Game::SceneManager * Game::SceneManager::getInstance() {
    static auto sceneManager = new Game::SceneManager();
    return sceneManager;
}

void Game::SceneManager::SwitchToFightScene(){
    currentScene = CurScene::Fight;
}

void Game::SceneManager::SwitchToMainScene(){
    currentScene = CurScene::Main;
}

void Game::SceneManager::SwitchToShopScene() {
    currentScene = CurScene::Shop;
}

std::shared_ptr<Game::Scene> Game::SceneManager::getCurrentScene(){
    switch (currentScene) {
        case CurScene::Fight:
            return fightScene;
        case CurScene::Main:
            return mainScene;
        case CurScene::Shop:
            return shopScene;
        default:
            std::cerr << "Scene not found!" << std::endl;
    }
}

void Game::SceneManager::setShopScene(const std::shared_ptr<Scene>& shopScene) {
}

void Game::SceneManager::setMainScene(const std::shared_ptr<Scene>& mainScene) {
}

void Game::SceneManager::setFightScene(const std::shared_ptr<Scene>& fightScene) {
    this->fightScene = fightScene;
}

Game::Player * Game::SceneManager::getPlayer() {
    return &player;
}

