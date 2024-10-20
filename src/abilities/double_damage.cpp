#include "double_damage.hpp"
#include "messages.hpp"

namespace seabattle {
    void DoubleDamage::use()
    {
        double_damage_flag = true;
        emplace<LogMessage>("You were blessed with Double Damage");
    }

    static bool is_registered  = AbilityRegistry::self().add("Double damage", [](Player &user, Player &target) { return std::make_unique<DoubleDamage>(user); });
}
