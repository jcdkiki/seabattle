#ifndef SEABATTLE_ABILITIES_SCANNER_HPP_
#define SEABATTLE_ABILITIES_SCANNER_HPP_

#include "ability.hpp"
#include "player.hpp"

namespace seabattle {
    class Scanner : public Ability {
        Field &field;
        vec2 position;
        bool is_found;
    public:
        bool isFound() const { return is_found; }
        vec2 getPosition() const { return position; }

        Scanner(Player &user, Player &target) : field(target.field), position(target.cursor) {}
        void use();
    };
}

#endif
