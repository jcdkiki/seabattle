#ifndef SEABATTLE_ABILITY_HPP_
#define SEABATTLE_ABILITY_HPP_

namespace seabattle {
    class GameRenderer;

    class Ability {
    public:
        virtual void use() = 0;
        virtual void renderBy(GameRenderer &renderer) const = 0;
        virtual ~Ability() {}
    };
}

#endif
