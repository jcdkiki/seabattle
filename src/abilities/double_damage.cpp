#include "double_damage.hpp"

namespace seabattle {
    void DoubleDamage::use()
    {
        user.double_damage_flag = true;
    }

    static bool is_registered  = AbilityRegistry::self().add("Double damage", [](Player &user, Player &target) { return std::make_unique<DoubleDamage>(user); });
}
