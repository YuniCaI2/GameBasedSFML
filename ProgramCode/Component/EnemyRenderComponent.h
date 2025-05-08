//
// Created by 51092 on 25-5-5.
//

#ifndef ENEMYRENDERCOMPONENT_H
#define ENEMYRENDERCOMPONENT_H
#include <unordered_map>

#include "RenderComponent.h"

namespace Game {
    class EnemyRenderComponent : public RenderComponent{
    public:
       void setDefaultTexture(const std::string &texturePath) override;
       void setHoverTexture(const std::string &texturePath) override;
       void update(GameObject *gameObject) override;
       void initial(GameObject *gameObject) override;
       sf::Sprite& getSprite() override;
    private:
        sf::Sprite defaultSprite;
        sf::Sprite hoverSprite;
        pbh::EnemyType enemyType{pbh::EnemyType::Pawn};
        static std::unordered_map<pbh::EnemyType,std::pair<sf::Texture, sf::Texture>> textures;
    };
}


#endif //ENEMYRENDERCOMPONENT_H
