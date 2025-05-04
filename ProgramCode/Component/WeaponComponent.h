//
// Created by 51092 on 25-4-26.
//

#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H
#include "Component.h"
#include <unordered_map>
#include "../pbh.h"

namespace Game {

    class WeaponComponent : public Component{
    public:
        WeaponComponent();
        void initial(GameObject *gameObject) override;
        int getWeaponNum(pbh::WeaponType weaponType);
        pbh::WeaponType getSelectedWeapon() const;
        void update(GameObject *gameObject) override;

        static std::unordered_map<pbh::WeaponType, int> weaponsDamageTable;

    private:
        int attackDamage;
        pbh::WeaponType selectedWeapon;
        std::unordered_map<pbh::WeaponType, int> weaponsNum;



    };

}


#endif //WEAPONCOMPONENT_H
