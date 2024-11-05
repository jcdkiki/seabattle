#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "abilities/ability.hpp"
#include "game.hpp"
#include <typeinfo>
#include <map>

namespace seabattle {
    class GameInput {
    protected:
        std::map<std::type_info, std::function<void(GameInput &self, const Ability &ability)>> ability_handlers;
    public:
        void operator>>(Game &game);
    };
}

#endif // GAME_INPUT_H
