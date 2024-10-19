#include "double_damage.hpp"
#include "ability.hpp"

#include "player.hpp"

namespace seabattle {
    void DoubleDamage::use(Player &user)
    {
        user.setDoubleDamageFlag();
    }

    const char *DoubleDamage::getName()
    {
        return "Double Damage";
    }

    static DoubleDamage *createInstance() { return new DoubleDamage(); }
    static bool is_registered = AbilityFactory::getInstance().registerAbility((AbilityFactory::GeneratorFn)createInstance);
}
