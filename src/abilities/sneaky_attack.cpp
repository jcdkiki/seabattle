#include "sneaky_attack.hpp"
#include "ability_registration.hpp"
#include "renderer/game_renderer.hpp"
#include <cmath>

namespace seabattle {
    void SneakyAttack::use()
    {
        struct Segment {
            Ship &ship;
            size_t index;
        };

        std::vector<Segment> good_segments;
        for (Ship &ship : ships) {
            for (size_t i = 0; i < ship.getSize(); i++) {
                if (ship[i] != Ship::SegmentState::DESTROYED) {
                    good_segments.push_back({ ship, i });
                }
            }
        }

        if (good_segments.empty()) {
            return;
        }

        Segment &segment = good_segments[rand() % good_segments.size()];
        segment.ship.damageSegment(segment.index);
    }

    void SneakyAttack::renderBy(GameRenderer &renderer) const { renderer.handle(*this); }
    static AbilityRegistration<SneakyAttack> reg;    
}
