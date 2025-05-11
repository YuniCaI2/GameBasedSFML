//
// Created by cai on 25-4-7.
//

#include "SceneManager.h"

#include "InputManager.h"

Game::SceneManager::SceneManager() {

}


Game::SceneManager * Game::SceneManager::getInstance() {
    static auto sceneManager = new Game::SceneManager();
    return sceneManager;
}

void Game::SceneManager::SwitchToFightScene(){
    currentScene = CurScene::Fight;
    InputManager::getInstance()->unregisterScene();
    InputManager::getInstance()->registerScene(fightScene);
}

void Game::SceneManager::SwitchToMainScene(){
    currentScene = CurScene::Main;
    InputManager::getInstance()->unregisterScene();
    InputManager::getInstance()->registerScene(mainScene);
}

void Game::SceneManager::SwitchToShopScene() {
    currentScene = CurScene::Shop;
    InputManager::getInstance()->unregisterScene();
    InputManager::getInstance()->registerScene(shopScene);
}

void Game::SceneManager::SwitchToStopScene() {
    currentScene = CurScene::Stop;
    InputManager::getInstance()->unregisterScene();
    InputManager::getInstance()->registerScene(stopScene);
}

void Game::SceneManager::setStopScene(const std::shared_ptr<Scene> &stopScene) {
    this->stopScene = stopScene;
}

std::shared_ptr<Game::Scene> Game::SceneManager::getCurrentScene(){
    switch (currentScene) {
        case CurScene::Fight:
            return fightScene;
        case CurScene::Main:
            return mainScene;
        case CurScene::Shop:
            return shopScene;
        case CurScene::Stop:
            return stopScene;
        default:
            std::cerr << "Scene not found!" << std::endl;
            return nullptr;
    }
}

void Game::SceneManager::setShopScene(const std::shared_ptr<Scene>& shopScene) {
    this->shopScene = shopScene;
}

void Game::SceneManager::setMainScene(const std::shared_ptr<Scene>& mainScene) {
    this->mainScene = mainScene;
}

void Game::SceneManager::setFightScene(const std::shared_ptr<Scene>& fightScene) {
    this->fightScene = fightScene;
}

