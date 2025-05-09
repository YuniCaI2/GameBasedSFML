//
// Created by cai on 25-4-3.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pbh.h"

namespace Game {
    class Component;

    class GameObject {
    public:
        sf::Vector2i globalPosition;
        sf::Vector2i relativePosition;
        bool isHovered{false};
        bool isClicked{false};

        void AddComponent(std::unique_ptr<Component>&& component);
        void setGlobalPosition(int x, int y);
        void setRelativePosition(int x, int y);

        template<typename T>
        inline T * getComponent() {
            for (auto &component: components) {
                auto componentData = component.get();
                if (dynamic_cast<T *>(componentData)) {
                    return dynamic_cast<T *>(componentData);
                }
            }
            return nullptr;
        }

        void update();

        void initial();


        virtual ~GameObject() = default;

    private:
        std::vector<std::unique_ptr<Component>> components;
        //这里使用智能指针，代替裸指针是为了将GameObject对象的生命周期和组件的生命周期绑定，
        //先前使用裸指针很难管理敌人对象，因为敌人对象被攻击后就被清理掉，单独将组件放到组件池很难管理
        //我有两种解决方案，一个可以使用对象ID管理，但是使用对象ID，还要制作一个对象ID管理系统，很难使用，一个使用智能指针RAII，让他自己管理
        //但是这里有个问题是，其实在大型游戏中的话需要将这里设置成共享指针可能会好一点，因为这样可以使用享元模式复用一些资源，比如说同种敌人复用有个贴图组件
        //这样可以提高利用率，也避免了贴图加载带来的卡顿，但是我这里没有使用这个是因为我的游戏是回合制且体量不大
    };
}


#endif //GAMEOBJECT_H
