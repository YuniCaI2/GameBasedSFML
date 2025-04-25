#include <SFML/Graphics.hpp>

#include "HoverManager.h"
#include "pbh.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"
#include "./Component/PlayerMoveComponent.h"
#include "./Component/PlayerRenderComponent.h"

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
        }

        void initialSceneManager() {
            //初始化战斗场景
            {
                testScene->setSprite("../resource/img.png");
                testScene->addObject(Player);
                Game::SceneManager::getInstance()->setFightScene(testScene);
                Game::SceneManager::getInstance()->SwitchToFightScene();
            }
            //初始化主页面
            {

            }
            //初始化商店页面
        }

        void initialPlayer() {
            Player = new GameObject();
            Player->setRelativePosition(100, 100);
            Player->AddComponent(componentsPool[ComponentType::PlayerRender]);
            Player->AddComponent(componentsPool[ComponentType::PlayerMove]);
        }

        void initialComponent() {
            componentsPool[ComponentType::PlayerMove] = new Game::PlayerMoveComponent();
            componentsPool[ComponentType::PlayerRender] = new Game::PlayerRenderComponent();
        }

        void clearGameObject() {
            for (auto& ptr : componentsPool) {
                delete ptr.second;
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
        GameObject* Player; // 测试使用
        auto testScene = std::make_shared<Game::Scene>();
        std::vector<GameObject*> gameObjects;
    };
}




int main() {

    // 主循环

    //initial Test
    Game::AppInstance app;
    app.initial();

    while (Window::getWindow().isOpen()) {
        // 处理事件
        sf::Event event;
        while (Window::getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window::getWindow().close();
            }
        }
        // 清屏

        Window::getWindow().clear(sf::Color::Black);
        Game::HoverManager::getInstance()->getHoverObject();
        Game::RenderEngine::getInstance()->RenderScene(*Game::SceneManager::getInstance()->getCurrentScene());
        Window::getWindow().display();

    }
    return 0;
}
