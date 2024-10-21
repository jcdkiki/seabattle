#include "double_damage.hpp"
#include "messaging/render_messages.hpp"

namespace seabattle {
    void DoubleDamage::use()
    {
        user.double_damage_flag = true;
        emplace<LogMessage>("You were blessed with Double Damage");
    }

    static bool is_registered  = AbilityRegistry::self().add("Double damage", [](Player &user, Player &target) { return std::make_unique<DoubleDamage>(user); });
}
