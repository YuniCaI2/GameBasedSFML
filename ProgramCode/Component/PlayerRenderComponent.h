//
// Created by cai on 25-4-25.
//

#ifndef PLAYERRENDERCOMPONENT_H
#define PLAYERRENDERCOMPONENT_H
#include "RenderComponent.h"


namespace Game {
    class PlayerRenderComponent: public RenderComponent{
    public:
        void setDefaultTexture(const std::string &texturePath) override;
        void setHoverTexture(const std::string &texturePath) override;
        void update(GameObject *gameObject) override;
        void initial(GameObject *gameObject) override;
        sf::Vector2i getBoundBox() override;
        sf::Sprite& getSprite() override;
    private:
        sf::Texture defaultTexture;
        sf::Texture hoverTexture;
        sf::Sprite defaultSprite;
        sf::Sprite hoverSprite;
        sf::Vector2i BoundBox;
    };

}


#endif //PLAYERRENDERCOMPONENT_H
