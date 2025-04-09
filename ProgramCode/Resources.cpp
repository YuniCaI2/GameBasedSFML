//
// Created by cai on 25-4-3.
//

#include "Resources.h"

#include <iostream>

Game::Resources * Game::Resources::getInstance() {
    static auto* res = new Resources();
    return res;
}

Game::Resources& Game::Resources::registerTexture(const std::string &texName, const std::string &texPath) {
    sf::Texture texture;
    if(texture.loadFromFile(texPath)) {
        std::cout << "Loading texture " << texName << " from " << texPath << std::endl;
        throw std::runtime_error("Texture load failed");
    }
    textures[texName] = texture;
    return *this;
}

sf::Texture & Game::Resources::getTexture(const std::string &texName) {
    return textures[texName];
}

