#ifndef SEABATTLE_GAME_RENDERER_HPP_
#define SEABATTLE_GAME_RENDERER_HPP_

#include "abilities/double_damage.hpp"
#include "abilities/sneaky_attack.hpp"
#include "abilities/scanner.hpp"

#include "field.hpp"
#include <string_view>

namespace seabattle {
    class GameRenderer {
    public:
        virtual void handle(const Field &field) = 0;
        virtual void handle(bbox2 cursor) = 0;
        virtual void handle(std::string_view text) = 0;

        virtual void handle(const DoubleDamage &ability) = 0;
        virtual void handle(const SneakyAttack &ability) = 0;
        virtual void handle(const Scanner &ability) = 0;

        virtual void update() = 0;

        inline void handle(const std::shared_ptr<Ability> ability)
        {
            ability->renderBy(*this);
        }
    };
}

#endif
