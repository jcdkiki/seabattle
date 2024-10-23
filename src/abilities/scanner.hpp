#ifndef SEABATTLE_ABILITIES_SCANNER_HPP_
#define SEABATTLE_ABILITIES_SCANNER_HPP_

#include "ability.hpp"

namespace seabattle {
    class Scanner : public Ability {
        Field &field;
        vec2 position;
    public:
        Scanner(Player &target) : field(target.field), position(target.cursor) {}
        void use();
    };
}

#endif
