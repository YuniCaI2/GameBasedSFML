//
// Created by 51092 on 25-5-11.
//

#ifndef BOXCOMPONENT_H
#define BOXCOMPONENT_H
#include "Component.h"
#include "RenderComponent.h"
#include <functional>
#include "../Item.h"

namespace Game {
    class Item;
    class BoxComponent: public RenderComponent{
        //这个组件的作用用来承载游戏属性增益卡牌(Queen)
    public:
        virtual void initial(GameObject *gameObject) override;
        virtual void update(GameObject *gameObject) override;

        virtual void setHoverTexture(const std::string& texturePath) override;
        virtual void setDefaultTexture(const std::string& texturePath) override;
        virtual sf::Sprite& getSprite() override;
        virtual sf::Vector2i getBoundBox() override;

        //独有方法——设置函数回调
        virtual void setOnClick(const std::function<void()>& onClick);
        void setItem(pbh::ItemType itemType);

    private:
        sf::Sprite defaultSprite;
        sf::Sprite hoverSprite;
        std::function<void()> onClick;
        Item item;
        sf::Vector2i BoundBox;
        pbh::ItemType itemType;

    };
}



#endif //BOXCOMPONENT_H
