#include <SFML/Graphics.hpp>

#include "pbh.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"
#include "./Component/PlayerMoveComponent.h"
#include "./Component/PlayerRenderComponent.h"
#include <unordered_map>

#include "GUIManager.h"
#include "InputManager.h"
#include "Component/AttackRangeComponent.h"
#include "Component/PlayerStatsComponent.h"
#include "Component/WeaponComponent.h"

namespace Game {
    //注册组件
    enum class ComponentType {
        PlayerMove,
        PlayerRender,
        PlayerStats,
        Weapon,
        AttackRange
    };


    class AppInstance {

    public:

        void initial() {
            initialComponent();
            initialPlayer();
            initialSceneManager();
            Game::GUIManager::getInstance()->init(player);

            //register
            InputManager::getInstance()->registerGameObject(player);
        }

        void initialSceneManager() {
            //初始化战斗场景
            {
                testScene = std::make_shared<Game::Scene>();
                testScene->setSprite("../resource/img.png");//设置场景背景
                testScene->setPlayer(player);
                Game::SceneManager::getInstance()->setFightScene(testScene);
                Game::SceneManager::getInstance()->SwitchToFightScene();
            }
            //初始化主页面
            {

            }
            //初始化商店页面
        }

        void initialPlayer() {
            auto* Player = new GameObject();
            gameObjects.push_back(Player);
            Player->setRelativePosition(4, 7);
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerRender]));
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerMove]));
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerStats]));
            Player->AddComponent(std::move(componentsPool[ComponentType::Weapon]));
            Player->AddComponent(std::move(componentsPool[ComponentType::AttackRange]));
            Player->initial();
            player = Player;
        }

        void initialComponent() {
            //初始化玩家移动组件
            componentsPool[ComponentType::PlayerMove].reset(new PlayerMoveComponent());
            //初始化渲染组件
            auto playRender =std::make_unique<Game::PlayerRenderComponent>();
            playRender->setDefaultTexture("../resource/GameObject/KingPlayer.png");
            playRender->setHoverTexture("../resource/GameObject/KingPlayerSelected.png");
            componentsPool[ComponentType::PlayerRender].reset(playRender.release());

            //初始化玩家属性组件
            auto playerStats = std::make_unique<Game::PlayerStatsComponent>();
            componentsPool[ComponentType::PlayerStats].reset(playerStats.release());

            //初始化武器组件
            auto playerWeapon = std::make_unique<WeaponComponent>();
            componentsPool[ComponentType::Weapon].reset(playerWeapon.release());

            //初始化攻击范围显示
            auto playerAttackRange = std::make_unique<AttackRangeComponent>();
            componentsPool[ComponentType::AttackRange].reset(playerAttackRange.release());
        }

        //主循环
        void run() {
            while (Window::getWindow().isOpen()) {
                sf::Event event;
                Game::InputManager::getInstance()->update();//刷新按键状态不得已操作
                while (Window::getWindow().pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        Window::getWindow().close();
                    }
                    Game::InputManager::getInstance()->processEvent(event);
                }
                logical();

                RenderEngine::getInstance()->Clear();
                GUIManager::getInstance()->draw();
                RenderEngine::getInstance()->RenderScene(*SceneManager::getInstance()->getCurrentScene());
                RenderEngine::getInstance()->Display();
            }
        }

        void logical() {
            for(auto& gameObject : gameObjects) {
                gameObject->update();
            }
            GUIManager::getInstance()->update();
        }

        void clearGameObject() {
            for (auto& ptr : gameObjects) {
                delete ptr;
            }
        }

        void clear() {
            clearGameObject();
        }

    private:
        std::unordered_map<ComponentType,std::unique_ptr<Component>> componentsPool;
        std::shared_ptr<Scene> testScene;
        std::vector<GameObject*> gameObjects;
        GameObject* player{};
    };
}




int main() {

    // 主循环

    //initial Test
    Game::AppInstance app;
    app.initial();
    app.run();
    app.clear();    // 释放资源
    return 0;
}
