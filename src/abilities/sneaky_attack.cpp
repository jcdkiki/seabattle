#include "sneaky_attack.hpp"

#include <cmath>
#include <queue>
#include "player.hpp"
#include <iostream>

namespace seabattle {
    void SneakyAttack::use(Player &user)
    {
        Field& field = user.getEnemyField();
        vec2 size = field.getSize();
        vec2 start = vec2(abs(rand()) % size.x, abs(rand()) % size.y);

        std::queue<vec2> q;
        std::vector<bool> visited(size.x * size.y);
        q.push(start);

        while (!q.empty()) {
            vec2 cur = q.front();
            q.pop();

            if (!field.getBoundingBox().contains(cur) || visited[cur.x + cur.y*size.x]) {
                continue;
            }
            visited[cur.x + cur.y*size.x] = true;

            const Ship::SegmentView segment = field[cur].ship_segment;
            if (segment && *segment != Ship::SegmentState::DESTROYED) {
                std::cout << "Sneaky attack was performed successfuly" << std::endl;
                user.attack(cur, true);
                return;
            }

            q.push(cur + vec2(1, 0));
            q.push(cur + vec2(-1, 0));
            q.push(cur + vec2(0, 1));
            q.push(cur + vec2(0, -1));
        }

        std::cout << "All ships are already destroyed" << std::endl;
    }

    const char *SneakyAttack::getName()
    {
        return "Sneaky Attack";
    }

    static SneakyAttack *createInstance() { return new SneakyAttack(); }
    static bool is_registered = AbilityFactory::getInstance().registerAbility((AbilityFactory::GeneratorFn)createInstance);
}
