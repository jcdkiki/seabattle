#include "scanner.hpp"
#include "ability_registration.hpp"

namespace seabattle {
    void Scanner::use()
    {
        bbox2 region(position, position + vec2(2, 2));
        region = region.intersection(field.getBoundingBox());

        for (int y = region.min.y; y < region.max.y; y++) {
            for (int x = region.min.x; x < region.max.x; x++) {
                if (field[vec2(x, y)].ship_segment) {
                    return;
                }
            }
        }
    }

    static AbilityRegistration<Scanner> reg("Scanner");    
}
