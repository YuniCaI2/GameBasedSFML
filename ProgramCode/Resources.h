//
// Created by cai on 25-4-3.
//

#ifndef RESOURCES_H
#define RESOURCES_H
#include <unordered_map>
#include <vector>
#include <SFML/Graphics/Texture.hpp>


namespace Game {
    class Resources {
        Resources() = default;
    public:
        static Resources* getInstance();
        std::unordered_map<std::string,sf::Texture> textures;
        Resources& registerTexture(const std::string& texName, const std::string& texPath);
        sf::Texture& getTexture(const std::string& texName);
    };
}



#endif //RESOURCES_H
