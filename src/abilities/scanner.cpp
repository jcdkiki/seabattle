#include "scanner.hpp"
#include "ability_registration.hpp"
#include "renderer/game_renderer.hpp"

namespace seabattle {
    void Scanner::use()
    {
        bbox2 region(position, position + vec2(2, 2));
        region = region.intersection(field.getBoundingBox());

        for (int y = region.min.y; y < region.max.y; y++) {
            for (int x = region.min.x; x < region.max.x; x++) {
                if (field[vec2(x, y)].ship_segment && field[vec2(x, y)].has_fog) {
                    is_found = true;
                    return;
                }
            }
        }

        is_found = false;
    }

    void Scanner::renderBy(GameRenderer &renderer) const { renderer.handle(*this); }
    static AbilityRegistration<Scanner> reg;    
}
