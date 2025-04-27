//
// Created by 51092 on 25-4-26.
//

#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H
#include "Component.h"
#include <unordered_map>

namespace Game {
    enum class WeaponType {
        Pawn,   //小兵
        Knight, //骑士
        Bishop, // 相
        Rook,   //车
    };


    class WeaponComponent : public Component{
    public:
        WeaponComponent();
        void update(GameObject *gameObject) override;


        static std::unordered_map<WeaponType, int> weaponsDamageTable;
    private:
        int attackDamage;
        WeaponType selectedWeapon;
        std::unordered_map<WeaponType, int> weaponsNum;



    };

}


#endif //WEAPONCOMPONENT_H
