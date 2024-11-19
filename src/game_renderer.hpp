#ifndef SEABATTLE_GAME_RENDERER_HPP_
#define SEABATTLE_GAME_RENDERER_HPP_

#include "abilities/double_damage.hpp"
#include "abilities/sneaky_attack.hpp"
#include "abilities/scanner.hpp"

#include "field.hpp"
#include <string_view>

#

namespace seabattle {
    class GameRenderer {
    public:
        virtual void operator<<(const Field &field) = 0;
        virtual void operator<<(bbox2 cursor) = 0;
        virtual void operator<<(std::string_view text) = 0;

        virtual void operator<<(const DoubleDamage &ability) = 0;
        virtual void operator<<(const SneakyAttack &ability) = 0;
        virtual void operator<<(const Scanner &ability) = 0;

        virtual void update() = 0;

        inline void operator<<(const Player::RenderAbilityMessage &msg)
        {
            msg.info.render(*this, msg.ability);
        }
    };
}

#endif
