//
// Created by 51092 on 25-5-9.
//

#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H
#include <functional>

#include "RenderComponent.h"


namespace Game {
    class ButtonComponent : public RenderComponent{
    public:
        void initial(GameObject *gameObject) override;
        void update(GameObject *gameObject) override;

        void setHoverTexture(const std::string& texturePath) override;
        void setDefaultTexture(const std::string& texturePath) override;
        sf::Sprite& getSprite() override;
        sf::Vector2i getBoundBox() override;

        //独有方法——设置函数回调
        void setOnClick(const std::function<void()>& onClick);

    private:
        sf::Texture defaultTexture;
        sf::Texture hoverTexture;
        sf::Sprite defaultSprite;
        sf::Sprite hoverSprite;
        std::function<void()> onClick;
        sf::Vector2i BoundBox;
    };

}


#endif //BUTTONCOMPONENT_H
