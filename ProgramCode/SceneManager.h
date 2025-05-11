//
// Created by cai on 25-4-7.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>

#include "Scene.h"


namespace Game {
    enum class CurScene{
        Fight,
        Shop,
        Main,
        Stop
    };

    class SceneManager {
        SceneManager();
    public:
        static SceneManager* getInstance();
        void SwitchToFightScene();//切换到关卡战斗画面
        void SwitchToMainScene();//切换到开始页面
        void SwitchToShopScene();//切换到商店页面
        void SwitchToStopScene();
        std::shared_ptr<Scene> getCurrentScene();
        void setShopScene(const std::shared_ptr<Scene>& shopScene);
        void setMainScene(const std::shared_ptr<Scene>& mainScene);
        void setFightScene(const std::shared_ptr<Scene>& fightScene);
        void setStopScene(const std::shared_ptr<Scene>& stopScene);
    private:
        std::shared_ptr<Scene> shopScene;
        std::shared_ptr<Scene> mainScene;
        std::shared_ptr<Scene> fightScene;
        std::shared_ptr<Scene> stopScene;
        CurScene currentScene{CurScene::Main};

    };
}


#endif //SCENEMANAGER_H
