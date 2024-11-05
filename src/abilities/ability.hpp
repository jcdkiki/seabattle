#ifndef SEABATTLE_ABILITY_HPP_
#define SEABATTLE_ABILITY_HPP_

namespace seabattle {
    class Ability {;
    public:
        virtual void use() = 0;
        virtual ~Ability() {}
    };
}

#endif
