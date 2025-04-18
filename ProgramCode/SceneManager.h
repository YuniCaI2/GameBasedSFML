//
// Created by cai on 25-4-7.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>

#include "Player.h"
#include "Scene.h"


namespace Game {
    enum class CurScene{
        Fight,
        Shop,
        Main
    };

    class SceneManager {
        SceneManager();
    public:
        static SceneManager* getInstance();
        void SwitchToFightScene();//切换到关卡战斗画面
        void SwitchToMainScene();//切换到开始页面
        void SwitchToShopScene();//切换到商店页面
        std::shared_ptr<Scene> getCurrentScene();
        void setShopScene(const std::shared_ptr<Scene>& shopScene);
        void setMainScene(const std::shared_ptr<Scene>& mainScene);
        void setFightScene(const std::shared_ptr<Scene>& fightScene);

        Player* getPlayer();
    private:
        std::shared_ptr<Scene> shopScene;
        std::shared_ptr<Scene> mainScene;
        std::shared_ptr<Scene> fightScene;
        CurScene currentScene{CurScene::Main};
        Player player;

    };
}


#endif //SCENEMANAGER_H
