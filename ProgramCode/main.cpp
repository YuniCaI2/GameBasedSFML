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
#include "Component/BoxComponent.h"
#include "Component/ButtonComponent.h"
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
            // for (auto &g: gameObjects) {
            //     Game::InputManager::getInstance()->registerGameObject(g);
            // }
        }

        void initialSceneManager() {
            //初始化战斗场景
            {
                fightScene = std::make_shared<Game::Scene>();
                fightScene->setSprite("../resource/img.png")
                        .setSceneType(pbh::Fight); //设置场景背景
                fightScene->setPlayer(player);
                //生成敌人
                auto [type, x, y] = Game::EnemyAI::getInstance()->generateEnemy();
                fightScene->addEnemy(createEnemy(type, x, y));

                Game::SceneManager::getInstance()->setFightScene(fightScene);
                Game::SceneManager::getInstance()->SwitchToFightScene();
            }
            //初始化暂停页面
            {
                stopScene = std::make_shared<Game::Scene>();
                stopScene->setSceneType(pbh::SceneType::Stop);
                stopScene->setSprite("../resource/store/stop1.png");
                auto buttonObject1 = new GameObject();
                auto buttonObject2 = new GameObject();
                auto buttonComponent1 = std::make_unique<Game::ButtonComponent>();
                auto buttonComponent2 = std::make_unique<Game::ButtonComponent>();
                buttonComponent1->setHoverTexture("../resource/store/exit0.png");
                buttonComponent1->setDefaultTexture("../resource/store/exit1.png");
                buttonComponent2->setHoverTexture("../resource/store/continue0.png");
                buttonComponent2->setDefaultTexture("../resource/store/continue1.png");
                auto CallBackFunc2 = [this]() {
                    SceneManager::getInstance()->SwitchToFightScene();
                };
                auto CallBackFunc1 = [this]() {
                    Window::getWindow().close();
                };
                buttonComponent1->setOnClick(CallBackFunc1);
                buttonComponent2->setOnClick(CallBackFunc2);
                buttonObject1->AddComponent(std::move(buttonComponent1));
                buttonObject1->setGlobalPosition(pbh::scenePosX + 80, pbh::scenePosY + 220);
                buttonObject2->AddComponent(std::move(buttonComponent2));
                buttonObject2->setGlobalPosition(pbh::scenePosX + 80 + 140, pbh::scenePosY + 220);
                stopScene->addObject(buttonObject1);
                stopScene->addObject(buttonObject2);

                Game::SceneManager::getInstance()->setStopScene(stopScene);
            }
            //初始化商店页面
            {
                shopScene = std::make_shared<Game::Scene>();
                shopScene->setSprite("../resource/store/store.png")
                        .setSceneType(pbh::SceneType::Shop);
                auto BoxObject1 = new GameObject();
                auto BoxObject2 = new GameObject();
                auto BoxComponent1 = std::make_unique<Game::BoxComponent>();
                BoxComponent1->setItem(pbh::ItemType::Normal);
                auto CallBackFunc1 = [this]() {
                    auto stats = player->getComponent<PlayerStatsComponent>();
                    Item item;
                    item.setType(pbh::ItemType::Normal);
                    stats->addItem(item);
                    Game::SceneManager::getInstance()->SwitchToFightScene();
                };
                BoxComponent1->setOnClick(CallBackFunc1);
                auto BoxComponent2 = std::make_unique<Game::BoxComponent>();
                BoxComponent2->setItem(pbh::ItemType::Move);
                auto CallBackFunc2 = [this]() {
                    auto stats = player->getComponent<PlayerStatsComponent>();
                    Item item;
                    item.setType(pbh::ItemType::Move);
                    stats->addItem(item);
                    Game::SceneManager::getInstance()->SwitchToFightScene();
                };
                BoxComponent2->setOnClick(CallBackFunc2);
                BoxObject1->AddComponent(std::move(BoxComponent1));
                BoxObject2->AddComponent(std::move(BoxComponent2));
                BoxObject1->setGlobalPosition(pbh::scenePosX + 25, pbh::scenePosY + 170);
                BoxObject2->setGlobalPosition(pbh::scenePosX + 125 + 25, pbh::scenePosY + 170);
                shopScene->addObject(BoxObject1);
                shopScene->addObject(BoxObject2);
                SceneManager::getInstance()->setShopScene(shopScene);
            }
            //初始化主页面
            {
                mainScene = std::make_shared<Game::Scene>();
                mainScene->setSprite("../resource/main/begin2.png")
                        .setSceneType(pbh::SceneType::Main);
                auto buttonObject = new GameObject();
                auto buttonComponent = std::make_unique<Game::ButtonComponent>();
                buttonComponent->setHoverTexture("../resource/main/mainButtonHover.png");
                buttonComponent->setDefaultTexture("../resource/main/mainButtonDefault.png");
                //设置按钮回调
                auto CallBackFunc = [this]() {
                    SceneManager::getInstance()->SwitchToFightScene();
                };
                buttonComponent->setOnClick(CallBackFunc);
                buttonObject->AddComponent(std::move(buttonComponent));
                buttonObject->setGlobalPosition(pbh::scenePosX + 125, pbh::scenePosY + 270);
                //扔到对象池统一释放
                gameObjects.push_back(buttonObject);
                mainScene->addObject(buttonObject);

                SceneManager::getInstance()->setMainScene(mainScene);
                SceneManager::getInstance()->SwitchToMainScene();
            }
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
                //主页不需要渲染GUI
                if (SceneManager::getInstance()->getCurrentScene()->getSceneType() != pbh::SceneType::Main)
                    GUIManager::getInstance()->draw();

                RenderEngine::getInstance()->RenderScene(*SceneManager::getInstance()->getCurrentScene());
                RenderEngine::getInstance()->Display();
            }
        }

        void logical() {
            if (!player->getComponent<PlayerStatsComponent>()->isAlive()) {
                std::wstring text = L"玩家已经死了\n,可以选择退出.\n 按下Esc";
                Game::GUIManager::getInstance()->writeText(text);
                return;
            }

            // for (auto &gameObject: gameObjects) {
            //     gameObject->update();
            // }
            if (SceneManager::getInstance()->getCurrentScene()->getSceneType() == pbh::SceneType::Shop) {
                if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::Escape)) {
                    SceneManager::getInstance()->SwitchToStopScene();
                }
                auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
                for (auto &gameObject: currentScene->getObjects()) {
                    gameObject->update();
                }
            }

            if (SceneManager::getInstance()->getCurrentScene()->getSceneType() == pbh::SceneType::Stop) {
                auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
                for (auto &gameObject: currentScene->getObjects()) {
                    gameObject->update();
                }
            }

            if (Game::SceneManager::getInstance()->getCurrentScene()->getSceneType() == pbh::SceneType::Main) {
                auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
                for (auto &gameObject: currentScene->getObjects()) {
                    gameObject->update();
                }
            }

            if (Game::SceneManager::getInstance()->getCurrentScene()->getSceneType() == pbh::SceneType::Fight) {
                //首先判断是否暂停
                if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::Escape)) {
                    SceneManager::getInstance()->SwitchToStopScene();
                }
                auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
                for (auto &gameObject: currentScene->getObjects()) {
                    gameObject->update();
                }

                auto playerStats = player->getComponent<PlayerStatsComponent>();

                //判断是否去商店
                if (playerStats->getKillNum() == 10 && playerStats->getItems().size() < 4) {
                    SceneManager::getInstance()->SwitchToShopScene();
                    playerStats->setKillNum(0);
                }

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
                            }
                        }
                    }
                    if (playerStats->getMoveNum() <= 0 && playerStats->getAttackNum() <= 0) {
                        round = false;
                        std::wstring text = L"敌方回合";
                        Game::GUIManager::getInstance()->writeText(text);
                    }
                    if (InputManager::getInstance()->isKeyPressed(sf::Keyboard::Space)) {
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
                    if (roundNum % 2 == 0) {
                        for (int i = 0; i < 1; i++) {
                            auto [type, x, y] = AI->generateEnemy();
                            Game::SceneManager::getInstance()->getCurrentScene()->addEnemy(createEnemy(type, x, y));
                            Game::InputManager::getInstance()->registerGameObject(
                            SceneManager::getInstance()->getCurrentScene()->getEnemies().back());
                        }
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

        // void removeDeadEnemies() {
        //     // 直接使用check函数，但在clearDeadEnemies()之前
        //     auto check = [](GameObject* enemy) {
        //         auto stats = enemy->getComponent<EnemyStatsComponent>();
        //         return stats && !stats->isAlive();
        //     };
        //
        //
        //
        //     // 从场景中移除
        //     auto currentScene = Game::SceneManager::getInstance()->getCurrentScene();
        //     currentScene->clearDeadEnemies();
        //
        //
        //     // 标记要删除的对象
        //     auto its = std::remove_if(gameObjects.begin(), gameObjects.end(), check);
        //
        //     // 注销要删除的对象
        //     for (auto it = its; it != gameObjects.end(); ++it) {
        //         Game::InputManager::getInstance()->unregisterGameObject(*it);
        //     }
        //
        //     // 删除对象并释放内存
        //     for (auto it = its; it != gameObjects.end(); ++it) {
        //         delete *it;
        //         *it = nullptr;
        //     }
        //
        //     // 从容器中移除
        //     gameObjects.erase(its, gameObjects.end());
        // }
        //
        //
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
        std::shared_ptr<Scene> fightScene;
        std::shared_ptr<Scene> shopScene;
        std::shared_ptr<Scene> mainScene;
        std::shared_ptr<Scene> stopScene;
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
