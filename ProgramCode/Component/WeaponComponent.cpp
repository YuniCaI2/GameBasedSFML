//
// Created by 51092 on 25-4-26.
//

#include "WeaponComponent.h"
#include "../InputManager.h"


std::unordered_map<pbh::WeaponType, int> Game::WeaponComponent::weaponsDamageTable = {
    {pbh::WeaponType::Pawn, 2},
    {pbh::WeaponType::Knight, 1},
    {pbh::WeaponType::Bishop, 1},
    {pbh::WeaponType::Rook, 1}
};


Game::WeaponComponent::WeaponComponent() {
    weaponsNum[pbh::WeaponType::Pawn] = 1;
    weaponsNum[pbh::WeaponType::Knight] = 1;
    weaponsNum[pbh::WeaponType::Bishop] = 1;
    weaponsNum[pbh::WeaponType::Rook] = 1;
    //初始化对象使其为1

    //默认为Pawn
    selectedWeapon = pbh::WeaponType::Pawn;
    attackDamage = weaponsDamageTable[selectedWeapon];
}

void Game::WeaponComponent::initial(GameObject *gameObject) {
    this->gameObject = gameObject;
    //内容和构造函数一致
    weaponsNum[pbh::WeaponType::Pawn] = 1;
    weaponsNum[pbh::WeaponType::Knight] = 1;
    weaponsNum[pbh::WeaponType::Bishop] = 1;
    weaponsNum[pbh::WeaponType::Rook] = 1;
    //初始化对象使其为1

    //默认为Pawn
    selectedWeapon = pbh::WeaponType::Pawn;
    attackDamage = weaponsDamageTable[selectedWeapon];
        
}

int Game::WeaponComponent::getWeaponNum(pbh::WeaponType weaponType) {
    return weaponsNum[weaponType];
}

pbh::WeaponType Game::WeaponComponent::getSelectedWeapon() const {
    return selectedWeapon;
}

void Game::WeaponComponent::update(GameObject *gameObject) {
    auto inputManager = InputManager::getInstance();
    this->gameObject = gameObject;
    if (inputManager->isKeyPressed(sf::Keyboard::Num1)) {
        selectedWeapon = pbh::WeaponType::Pawn;
    }
    if (inputManager->isKeyPressed(sf::Keyboard::Num2)) {
        selectedWeapon = pbh::WeaponType::Knight;
    }
    if (inputManager->isKeyPressed(sf::Keyboard::Num3)) {
        selectedWeapon = pbh::WeaponType::Bishop;
    }
    if (inputManager->isKeyPressed(sf::Keyboard::Num4)) {
        selectedWeapon = pbh::WeaponType::Rook;
    }
}
