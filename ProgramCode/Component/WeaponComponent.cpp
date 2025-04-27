//
// Created by 51092 on 25-4-26.
//

#include "WeaponComponent.h"
#include "../InputManager.h"


std::unordered_map<Game::WeaponType, int> Game::WeaponComponent::weaponsDamageTable = {
    {WeaponType::Pawn, 2},
    {WeaponType::Knight, 1},
    {WeaponType::Bishop, 1},
    {WeaponType::Rook, 1}
};

Game::WeaponComponent::WeaponComponent() {
    weaponsNum[WeaponType::Pawn] = 1;
    weaponsNum[WeaponType::Knight] = 1;
    weaponsNum[WeaponType::Bishop] = 1;
    weaponsNum[WeaponType::Rook] = 1;
    //初始化对象使其为1

    //默认为Pawn
    selectedWeapon = WeaponType::Pawn;
    attackDamage = weaponsDamageTable[selectedWeapon];
}

void Game::WeaponComponent::update(GameObject *gameObject) {
    auto inputManager = InputManager::getInstance();
    this->gameObject = gameObject;

}
