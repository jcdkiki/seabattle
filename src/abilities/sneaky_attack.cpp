#include "sneaky_attack.hpp"
#include "ability_registration.hpp"
#include <cmath>

namespace seabattle {
    void SneakyAttack::use()
    {
        std::vector<Ship*> good_ships;
        for (Ship &ship : ships) {
            if (!ship.isDestroyed())
                good_ships.push_back(&ship);
        }

        Ship &ship = *good_ships[rand() % good_ships.size()];
        
        std::vector<size_t> good_segments;
        for (size_t i = 0; i < ship.getSize(); i++) {
            if (ship[i] != Ship::SegmentState::DESTROYED) {
                good_segments.push_back(i);
            }
        }

        size_t segment = good_segments[rand() % good_segments.size()];
        ship.damageSegment(segment);
    }

    static AbilityRegistration<SneakyAttack> reg("Sneaky Attack");    
}
