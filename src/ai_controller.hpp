#ifndef SEABATTLE_AI_CONTROLLER_HPP_
#define SEABATTLE_AI_CONTROLLER_HPP_

#include "field.hpp"

namespace seabattle {
    class AIController {
        Field *field_ptr;

        enum State {
            RANDOM_ATTACK,
            SECOND_ATTACK,
            FIND_ORIENTATION,
            DESTROY_SHIP
        };

        State state;

        vec2 current_attack;
        int direction;

        vec2 doRandomAttack();
        vec2 doSecondAttack();
        vec2 doFindOrientation();
        vec2 doDestroyShip();

        void advance();
        void changeDirection();

        void seeRandomAttack(Field::AttackResult res);
        void seeSecondAttack(Field::AttackResult res);
        void seeFindOrientation(Field::AttackResult res);
        void seeDestroyShip(Field::AttackResult res);

    public:
        explicit AIController(Field *field = nullptr)
            : field_ptr(field), state(RANDOM_ATTACK)
        {}

        vec2 choose();
        void see(Field::AttackResult res);
        inline void setField(Field *field) { field_ptr = field; }

        friend std::ostream &operator<<(std::ostream &os, AIController &ai);
        friend std::istream &operator>>(std::istream &is, AIController &ai);
    };
};

#endif
