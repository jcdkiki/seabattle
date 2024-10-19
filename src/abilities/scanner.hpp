#ifndef SEABATTLE_ABILITIES_SCANNER_HPP_
#define SEABATTLE_ABILITIES_SCANNER_HPP_

#include "ability.hpp"

namespace seabattle {
    class Scanner : public Ability {
    public:
        void use(Player &user);
        const char *getName();
    };
}

#endif
