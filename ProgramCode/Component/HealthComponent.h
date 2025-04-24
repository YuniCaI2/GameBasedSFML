//
// Created by 51092 on 25-4-24.
//

#ifndef HEALTH_H
#define HEALTH_H
#include "Component.h"


namespace Game {
    class HealthComponent : public Component{
    public:
        HealthComponent(int maxHealth, int currentHealth);
        ~HealthComponent() override = default;
        void setHealth(int health);
        void setMaxHealth(int maxHealth);
        int& getCurrentHealth();
        int getMaxHealth() const;
        void update(GameObject* gameObject) override;
    private:
        int health;
        int maxHealth;
    };


}



#endif //HEALTH_H
