#include "scanner.hpp"
#include <iostream>

#include "player.hpp"

namespace seabattle {
    void Scanner::use(Player &user)
    {
        const Field &field = user.getEnemyField();
        vec2 cursor = user.getCursor();

        bbox2 region(cursor, cursor + vec2(2, 2));
        region = region.intersection(field.getBoundingBox());

        for (int y = region.min.y; y < region.max.y; y++) {
            for (int x = region.min.x; x < region.max.x; x++) {
                if (field[vec2(x, y)].ship_segment) {
                    std::cout << "Ship found!!" << std::endl;
                    return;
                }
            }
        }

        std::cout << "Not found :(" << std::endl;
    }

    const char *Scanner::getName()
    {
        return "Scanner";
    }

    static Scanner *createInstance() { return new Scanner(); }
    static bool is_registered = AbilityFactory::getInstance().registerAbility((AbilityFactory::GeneratorFn)createInstance);
}
