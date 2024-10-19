#ifndef SEABATTLE_PLAYER_HPP_
#define SEABATTLE_PLAYER_HPP_

#include "vec2.hpp"
#include "field.hpp"
#include "ability_manager.hpp"

namespace seabattle {
    class Player {
        Field &enemy_field;
        vec2 cursor;
        bool double_damage_flag;
        AbilityManager abilities;

    public:
        Player(Field& enemy_field)
        : enemy_field(enemy_field), abilities(),
          cursor(vec2(0, 0)), double_damage_flag(false)
        {}
        
        inline void setDoubleDamageFlag() { double_damage_flag = true; }
        inline void moveCursor(vec2 offset) { cursor += offset; }
        inline void setCursor(vec2 cursor) { this->cursor = cursor; }
        inline vec2 getCursor() const { return cursor; }
        inline Field &getEnemyField() { return enemy_field; }

        void attack(bool hidden);
        void attack(vec2 cursor, bool hidden);

        void useAbility();
        void createAbility();
    };
}

#endif
