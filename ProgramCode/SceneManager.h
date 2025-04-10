//
// Created by cai on 25-4-7.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>

#include "Player.h"
#include "Scene.h"


namespace Game {
    class SceneManager {
        SceneManager();
    public:
        static SceneManager* getInstance();
        void SwitchToFightScene();//切换到关卡战斗画面
        void SwitchToMainScene();//切换到开始页面
        void SwitchToShopScene();//切换到商店页面

        Player* getPlayer();
    private:

        Player player;

    };
}


#endif //SCENEMANAGER_H
