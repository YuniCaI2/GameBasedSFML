//
// Created by cai on 25-4-7.
//

#include "Item.h"

Game::Item::Item(std::string &&_name, std::string &&_description, pbh::Texture&& _texture) {
    name = std::move(_name);
    description = std::move(_description);
    texture = std::move(_texture);
}

Game::Item::Item(const std::string &_name, const std::string &_description, const pbh::Texture& _texture) {
    name = _name;
    description = _description;
    texture = _texture;
}

std::string Game::Item::getName() const {
    return name;
}

std::string Game::Item::getDescription() const {
    return description;
}
