#include <SFML/Graphics.hpp>

int main() {
    // 创建主窗口：1000x800
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Window Layout");

    // 定义场景矩形：600x600
    sf::RectangleShape scene(sf::Vector2f(600.f, 600.f));
    scene.setFillColor(sf::Color::Blue); // 场景填充蓝色，便于可视化

    // 计算场景位置
    // 水平居中：(1000 - 600) / 2 = 200
    // 垂直靠下：800 - 600 = 200
    scene.setPosition(200.f, 200.f); // 设置位置 (x=200, y=200)

    // 主循环
    while (window.isOpen()) {
        // 处理事件
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 清屏
        window.clear(sf::Color::Black); // 主窗口背景为黑色

        // 绘制场景
        window.draw(scene);

        // 显示
        window.display();
    }

    return 0;
}