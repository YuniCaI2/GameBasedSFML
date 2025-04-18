#include <SFML/Graphics.hpp>

#include "HoverManager.h"
#include "pbh.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"

class AppInstance {
public:

private:
};


int main() {

    // 主循环
    auto testScene = std::make_shared<Game::Scene>();
    testScene->setSprite("../resource/img.png");
    Game::SceneManager::getInstance()->setFightScene(testScene);
    Game::SceneManager::getInstance()->SwitchToFightScene();
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
