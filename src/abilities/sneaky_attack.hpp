#ifndef SEABATTLE_ABILITIES_SNEAKY_ATTACK_HPP_
#define SEABATTLE_ABILITIES_SNEAKY_ATTACK_HPP_

#include "ability.hpp"
#include "player.hpp"

namespace seabattle {
    class SneakyAttack : public Ability {
        ShipManager &ships;
    public:
        static constexpr const char *name = "Sneaky Attack";
        
        SneakyAttack(Player &user, Player &target) : ships(target.ships) {}
        void use();
        void renderBy(GameRenderer &renderer) const;
    };
}

#endif
