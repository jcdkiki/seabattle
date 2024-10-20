#include "scanner.hpp"
#include "messages.hpp"
#include <memory>

namespace seabattle {
    void Scanner::use()
    {
        bbox2 region(position, position + vec2(2, 2));
        region = region.intersection(field.getBoundingBox());

        for (int y = region.min.y; y < region.max.y; y++) {
            for (int x = region.min.x; x < region.max.x; x++) {
                if (field[vec2(x, y)].ship_segment) {
                    emplace<LogMessage>("Scanner found ship in this region");
                    emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, field, region);
                    return;
                }
            }
        }

        emplace<LogMessage>("Scanner didn't find anything :(((");
    }

    static bool is_registered  = AbilityRegistry::self().add("Scanner", [](Player &user, Player &target) { return std::make_unique<Scanner>(target); });
}
