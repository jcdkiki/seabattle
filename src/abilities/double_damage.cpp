#include "double_damage.hpp"
#include "ability_registration.hpp"
#include "renderer/game_renderer.hpp"

namespace seabattle {
    void DoubleDamage::use()
    {
        user.double_damage_flag = true;
    }

    void DoubleDamage::renderBy(GameRenderer &renderer) const { renderer.handle(*this); }
    static AbilityRegistration<DoubleDamage> reg;
}
