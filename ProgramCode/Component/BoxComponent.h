//
// Created by 51092 on 25-5-11.
//

#ifndef BOXCOMPONENT_H
#define BOXCOMPONENT_H
#include "Component.h"
#include "RenderComponent.h"

namespace Game {
    class BoxComponent: public RenderComponent{
        //这个组件的作用用来承载游戏属性增益卡牌(Queen)
    public:
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;

        void setHoverTexture(const std::string& texturePath) override;
        void setDefaultTexture(const std::string& texturePath) override;
        sf::Sprite& getSprite() override;

        //独有方法——因为卡牌会有属性增益,需要给其做属性说明
    private:
        sf::Texture defaultTexture;
        sf::Texture hoverTexture;
        sf::Sprite defaultSprite;
        sf::Sprite hoverSprite;
    };
}



#endif //BOXCOMPONENT_H
