#include "double_damage.hpp"
#include "abilities/ability_registration.hpp"

namespace seabattle {
    void DoubleDamage::use()
    {
        user.double_damage_flag = true;
    }

    static AbilityRegistration<DoubleDamage> reg("Double Damage");
}
