#include "ai_controller.hpp"

#include <ostream>
#include <istream>

namespace seabattle {
    static vec2 directions[] = {
        { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }
    };

    vec2 AIController::doRandomAttack()
    {
        vec2 size = field_ptr->getSize();

        while (true) {
            vec2 pos(rand() % size.x, rand() % size.y);
            
            bool fog_or_empty_around = true;
            bbox2 region = field_ptr->getBoundingBox().intersection(bbox2(pos - vec2(1, 1), pos + vec2(1, 1)));
            for (int y = region.min.y; y < region.max.y; y++) {
                for (int x = region.min.x; x < region.max.x; x++) {
                    const Field::Cell &cell = (*field_ptr)[vec2(x, y)];
                    if (!cell.has_fog && cell.ship_segment) {
                        fog_or_empty_around = false;
                    }
                }
            }

            if ((*field_ptr)[pos].has_fog && fog_or_empty_around) {
                current_attack = pos;
                return pos;
            }
        }
    }

    void AIController::seeRandomAttack(Field::AttackResult res)
    {
        if (res == Field::AttackResult::SHIP_DAMAGED)
            state = SECOND_ATTACK;
        else if (res == Field::AttackResult::SHIP_DESTROYED)
            state = FIND_ORIENTATION;
    }

    vec2 AIController::doSecondAttack()
    {
        return current_attack;
    }

    void AIController::seeSecondAttack(Field::AttackResult res)
    {
        if (res == Field::SHIP_DESTROYED)
            state = RANDOM_ATTACK;
        else if (res == Field::SHIP_DAMAGED) {
            state = FIND_ORIENTATION;
            direction = 0;
        }
    }

    vec2 AIController::doFindOrientation()
    {
        return current_attack + directions[direction];
    }

    void AIController::seeFindOrientation(Field::AttackResult res)
    {
        if (res == Field::SHIP_DESTROYED)
            state = RANDOM_ATTACK;
        else if (res == Field::SHIP_DAMAGED) {
            current_attack += directions[direction];
            state = DESTROY_SHIP;
        }
        else
            direction++;
    }

    vec2 AIController::doDestroyShip()
    {
        return current_attack;
    }

    void AIController::advance()
    {
        if (*(*field_ptr)[current_attack].ship_segment != Ship::SegmentState::DESTROYED)
            return;

        current_attack += directions[direction];
        if (!field_ptr->getBoundingBox().contains(current_attack)) {
            current_attack -= directions[direction];
            return changeDirection();
        }
    }

    void AIController::changeDirection()
    {
        direction = 3 - direction; // inserve it
        while (!(*field_ptr)[current_attack].has_fog) {
            current_attack += directions[direction];
        }
    }

    void AIController::seeDestroyShip(Field::AttackResult res)
    {
        if (res == Field::SHIP_DESTROYED)
            state = RANDOM_ATTACK;
        else if (res == Field::SHIP_DAMAGED)
            advance();
        else
            changeDirection();
    }

    vec2 AIController::choose()
    {
        if (field_ptr == nullptr) {
            throw std::runtime_error("AI Controller doesn't have target field");
        }

        switch (state) {
            case RANDOM_ATTACK: return doRandomAttack();
            case SECOND_ATTACK: return doSecondAttack();
            case FIND_ORIENTATION: return doFindOrientation();
            case DESTROY_SHIP: return doDestroyShip();
        }
    }

    void AIController::see(Field::AttackResult res)
    {
        if (field_ptr == nullptr) {
            throw std::runtime_error("AI Controller doesn't have target field");
        }

        switch (state) {
            case RANDOM_ATTACK: seeRandomAttack(res); return;
            case SECOND_ATTACK: seeSecondAttack(res); return;
            case FIND_ORIENTATION: seeFindOrientation(res); return;
            case DESTROY_SHIP: seeDestroyShip(res); return;
        }
    }

    std::ostream &operator<<(std::ostream &os, AIController &ai)
    {
        os << (int)ai.state << ' ' << ai.current_attack.x << ' '
           << ai.current_attack.y << ' ' << ai.direction;
        return os;
    }

    std::istream &operator>>(std::istream &is, AIController &ai)
    {
        ai = AIController();
        int state;
        is >> state >> ai.current_attack.x >> ai.current_attack.y >> ai.direction;
        ai.state = static_cast<AIController::State>(state);
        return is;
    }
}
