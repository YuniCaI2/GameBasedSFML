#include <SFML/Graphics.hpp>

#include "pbh.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"
#include "./Component/PlayerMoveComponent.h"
#include "./Component/PlayerRenderComponent.h"
#include <unordered_map>
#include "InputManager.h"

namespace Game {
    enum class ComponentType {
        PlayerMove,
        PlayerRender,
    };


    class AppInstance {

    public:

        void initial() {
            initialComponent();
            initialPlayer();
            initialSceneManager();

            //register
            InputManager::getInstance()->registerGameObject(player);
        }

        void initialSceneManager() {
            //初始化战斗场景
            {
                testScene = std::make_shared<Game::Scene>();
                testScene->setSprite("../resource/img.png");
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
            Player->AddComponent(componentsPool[ComponentType::PlayerRender]);
            Player->AddComponent(componentsPool[ComponentType::PlayerMove]);
            Player->update();
            player = Player;
        }

        void initialComponent() {
            componentsPool[ComponentType::PlayerMove] = new Game::PlayerMoveComponent();
            //
            auto* playRender = new Game::PlayerRenderComponent();
            playRender->setDefaultTexture("../resource/GameObject/KingPlayer.png");
            componentsPool[ComponentType::PlayerRender] = playRender;
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
                RenderEngine::getInstance()->RenderScene(*SceneManager::getInstance()->getCurrentScene());
                RenderEngine::getInstance()->Display();
            }
        }

        void logical() {
            for(auto& gameObject : gameObjects) {
                gameObject->update();
            }
        }

        void clearGameObject() {
            for (auto& ptr : gameObjects) {
                delete ptr;
            }
        }

        void clearComponent() {
            for (auto& component : componentsPool) {
                delete component.second;
            }
            componentsPool.clear();
        }

        void clear() {
            clearGameObject();
            clearComponent();
        }

    private:
        std::unordered_map<ComponentType,Component*> componentsPool;
        std::shared_ptr<Scene> testScene;
        std::vector<GameObject*> gameObjects;
        GameObject* player;
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
