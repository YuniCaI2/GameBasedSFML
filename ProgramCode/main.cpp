#include <SFML/Graphics.hpp>

#include "pbh.h"
#include "RenderEngine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"
#include "./Component/PlayerMoveComponent.h"
#include "./Component/PlayerRenderComponent.h"
#include <unordered_map>

#include "EnemyAI.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "Component/AttackRangeComponent.h"
#include "Component/EnemyAttackComponent.h"
#include "Component/EnemyRenderComponent.h"
#include "Component/EnemyStatsComponent.h"
#include "Component/PlayerAttackComponent.h"
#include "Component/PlayerStatsComponent.h"
#include "Component/WeaponComponent.h"

namespace Game {
    //注册组件
    //准确来说这里有点多余，当时我想着复用组件的
    //但是啊，我搞错了，敌人会随时死亡和清除，这样组件的必须和游戏对象的生命周期牢牢绑定
    //所以这个枚举类是设计失误的产物
    enum class ComponentType {
        PlayerMove,
        PlayerRender,
        PlayerStats,
        Weapon,
        AttackRange,
        PlayerAttack
    };


    class AppInstance {
    public:
        void initial() {
            initialComponent();
            initialPlayer();
            initialSceneManager();
            Game::GUIManager::getInstance()->init(player);

            //register
            for (auto &g: gameObjects) {
                Game::InputManager::getInstance()->registerGameObject(g);
            }
        }

        void initialSceneManager() {
            //初始化战斗场景
            {
                testScene = std::make_shared<Game::Scene>();
                testScene->setSprite("../resource/img.png")
                        .setSceneType(pbh::Fight); //设置场景背景
                testScene->setPlayer(player);

                //生成敌人
                Game::SceneManager::getInstance()->setFightScene(testScene);
                Game::SceneManager::getInstance()->SwitchToFightScene();
                auto [type, x, y] = Game::EnemyAI::getInstance()->generateEnemy();
                SceneManager::getInstance()->getCurrentScene()->addEnemy(createEnemy(type, x, y));
            }
            //初始化主页面
            {
            }
            //初始化商店页面
        }

        void initialPlayer() {
            auto *Player = new GameObject();
            gameObjects.push_back(Player);
            //为玩家对象添加组件，可以仔细看看添加组件和获得组件的方法，用到了Cpp的RTTI，运行时多态实现
            Player->setRelativePosition(4, 7);
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerRender]));
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerMove]));
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerStats]));
            Player->AddComponent(std::move(componentsPool[ComponentType::Weapon]));
            Player->AddComponent(std::move(componentsPool[ComponentType::AttackRange]));
            Player->AddComponent(std::move(componentsPool[ComponentType::PlayerAttack]));
            Player->initial();
            player = Player;
        }


        void initialComponent() {
            //这里还是初始化玩家的组件，因为怪物的生成还是依靠工厂函数实现了
            //初始化玩家移动组件
            componentsPool[ComponentType::PlayerMove].reset(new PlayerMoveComponent());
            //初始化渲染组件
            auto playRender = std::make_unique<Game::PlayerRenderComponent>();
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

            //初始化攻击
            auto playerAttack = std::make_unique<PlayerAttackComponent>();
            componentsPool[ComponentType::PlayerAttack].reset(playerAttack.release());
        }

        //生成敌人的工厂函数
        GameObject *createEnemy(pbh::EnemyType enemyType, int x, int y) {
            //初始化敌人的组件
            //状态
            auto enemyStats = std::make_unique<EnemyStatsComponent>();
            enemyStats->initialEnemyType(enemyType);
            //渲染模块
            auto enemyRender = std::make_unique<EnemyRenderComponent>();
            //敌人攻击模块
            auto enemyAttack = std::make_unique<EnemyAttackComponent>();

            //敌人实例的创建
            GameObject *enemy = new GameObject();
            enemy->setRelativePosition(x, y);


            //载入组件
            enemy->AddComponent(std::move(enemyStats));
            enemy->AddComponent(std::move(enemyRender));
            enemy->AddComponent(std::move(enemyAttack));
            enemy->initial();

            //自动塞到整体游戏的对象池，便于统一管理内存
            gameObjects.push_back(enemy);

            return enemy;
        }

        //主循环
        void run() {
            while (Window::getWindow().isOpen()) {
                sf::Event event;
                Game::InputManager::getInstance()->update(); //刷新按键状态不得已操作
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
            if (!player->getComponent<PlayerStatsComponent>()->isAlive()) {
                std::wstring text = L"玩家已经死了";
                Game::GUIManager::getInstance()->writeText(text);
                return;
            }

            for (auto &gameObject: gameObjects) {
                gameObject->update();
            }

            if (Game::SceneManager::getInstance()->getCurrentScene()->getSceneType() == pbh::SceneType::Fight) {
                auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();

                auto playerStats = player->getComponent<PlayerStatsComponent>();
                if (round) {
                    auto clickedObject = Game::InputManager::getInstance()->getClickedObject();
                    //攻击行为
                    if (clickedObject != nullptr && clickedObject != player) {
                        // 这里设计出了点问题，这应该写在攻击组件内，这里渗透出来了，这是错误的
                        // 先获取到点击的对象
                        auto attackComponent = player->getComponent<PlayerAttackComponent>();
                        if (playerStats->getAttackNum() <= 0) {
                            // 判断是否有能力攻击，这应该写在组件中,因为没有能力攻击也是一种攻击失败
                            std::wstring text = L"你没有攻击次数了";
                            Game::GUIManager::getInstance()->writeText(text);
                            clickedObject->isClicked = false; //关闭点击的高亮
                        } else {
                            auto f = attackComponent->Attack(clickedObject);
                            if (f == true) {
                                // 是否成功攻击到单位
                                std::wstring text = L"攻击成功";
                                Game::GUIManager::getInstance()->writeText(text);
                                std::cerr << "Attack !" << std::endl;
                                playerStats->setCurrentAttackNum(playerStats->getAttackNum() - 1); // 攻击成功减少攻击次数
                            }
                        }
                    }
                    if (playerStats->getMoveNum() <= 0 && playerStats->getAttackNum() <= 0) {
                        round = false;
                        std::wstring text = L"敌方回合";
                        Game::GUIManager::getInstance()->writeText(text);
                    }
                    if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::P)) {
                        std::wstring text = L"玩家跳过，敌方回合";
                        Game::GUIManager::getInstance()->writeText(text);
                        round = false;
                    }
                    removeDeadEnemies();
                } else {
                    //DeBug--------------------------------------------------------------------------
                    if (pbh::checkVector(gameObjects) == false) {
                        std::cerr << "向量发生了重复" << std::endl;
                        for (auto &gameObject: gameObjects) {
                            std::cerr << gameObject << std::endl;
                        }
                        exit(-1);
                    }
                    //--------------------------------------------------------------------------------


                    auto AI = Game::EnemyAI::getInstance();
                    auto [index, x, y] = AI->getAction(currentScene->getEnemies(), player);
                    if (index != -1 && index < currentScene->getEnemies().size()) {
                        auto enemy = currentScene->getEnemies()[index];
                        auto enemyAttack = enemy->getComponent<EnemyAttackComponent>();
                        enemyAttack->moveTo(x, y);
                        auto playerPositions = player->relativePosition;
                        if (playerPositions.x == x && playerPositions.y == y) {
                            enemyAttack->Attack(player);
                            auto enemyStats = enemy->getComponent<EnemyStatsComponent>();
                            enemyStats->setCurrentHealth(0);
                        }
                    }


                    std::wstring text = L"玩家回合！";
                    Game::GUIManager::getInstance()->writeText(text);
                    playerStats->turnStart();

                    removeDeadEnemies();
                    roundNum++;
                    round = true;
                    if (roundNum % 3 == 0) {
                        auto [type, x, y] = AI->generateEnemy();
                        Game::SceneManager::getInstance()->getCurrentScene()->addEnemy(createEnemy(type, x, y));
                        Game::InputManager::getInstance()->registerGameObject(
                            SceneManager::getInstance()->getCurrentScene()->getEnemies().back());
                        //增加敌人
                        //并且注册
                    }
                }
            }

            GUIManager::getInstance()->update();
        }

        // 在AppInstance::removeDeadEnemies()中修改
        void removeDeadEnemies() {
            // 1. 首先收集所有要删除的敌人指针
            auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
            std::vector<GameObject *> deadEnemies;

            for (auto *enemy: currentScene->getEnemies()) {
                auto stats = enemy->getComponent<EnemyStatsComponent>();
                if (stats && !stats->isAlive()) {
                    deadEnemies.push_back(enemy);
                }
            }

            // 2. 从场景中移除
            currentScene->clearDeadEnemies();

            // 3. 从gameObjects中安全移除并删除对象
            for (auto *deadEnemy: deadEnemies) {
                // 注销死亡敌人
                Game::InputManager::getInstance()->unregisterGameObject(deadEnemy);

                // 从gameObjects移除
                auto it = std::find(gameObjects.begin(), gameObjects.end(), deadEnemy);
                if (it != gameObjects.end()) {
                    // 删除对象
                    delete *it;
                    // 将指针置空，防止访问已释放的内存
                    *it = nullptr;
                    // 从向量中移除空指针
                    gameObjects.erase(it);
                }
            }
        }

        void clearGameObject() {
            for (auto &ptr: gameObjects) {
                if (ptr != nullptr)
                    delete ptr;
            }
        }

        void clear() {
            clearGameObject();
        }

    private:
        bool round{1}; //这里的1代表的是玩家回合。0代表的是敌方回合
        std::unordered_map<ComponentType, std::unique_ptr<Component> > componentsPool;
        std::shared_ptr<Scene> testScene;
        std::vector<GameObject *> gameObjects;
        GameObject *player{};
        int roundNum{1};
    };
}


int main() {
    // 主循环

    //initial Test
    Game::AppInstance app;
    app.initial();
    app.run();
    app.clear(); // 释放资源
    return 0;
}
