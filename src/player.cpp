#include "player.hpp"
#include "abilities/ability.hpp"
#include "ability_manager.hpp"
#include <memory>
#include <ostream>
#include <istream>
#include <unordered_map>

namespace seabattle {
    std::shared_ptr<Ability> Player::useAbility(Player &target)
    {
        AbilityManager::AbilityData data = abilities.top();
        std::shared_ptr<Ability> ability(data.info.generator(*this, target));
        ability->use(); // can throw
        abilities.pop();
        return std::move(ability);
    }

    Field::AttackResult Player::attack(Player &target)
    {
        Field::AttackResult res1 = target.field.attack(cursor, false);
        Field::AttackResult res2 = Field::AttackResult::NOTHING;
        if (double_damage_flag) {
            res2 = target.field.attack(cursor, false);
            double_damage_flag = false;
        }

        if (res1 == Field::AttackResult::SHIP_DESTROYED || res2 == Field::AttackResult::SHIP_DESTROYED) {
            abilities.addRandomAbility();
        }

        if (res2 != Field::AttackResult::NOTHING) {
            return res2;
        }
        return res1;
    }

    std::ostream &operator<<(std::ostream &os, Player &player)
    {
        os << player.ships << '\n';

        // FIELD
        vec2 size = player.field.getSize();
        os << size.x << ' ' << size.y << '\n';
        
        std::unordered_map<Ship*, size_t> ships_map;
        {
            size_t i = 0;
            for (Ship &ship : player.ships) {
                ships_map[&ship] = i++;
            }
        }

        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                const Field::Cell &cell = player.field[vec2(x, y)];
                if (cell.has_fog) {
                    os << "fog ";
                }
                if (cell.marked) {
                    os << "marked ";
                }
                if (cell.ship_segment) {
                    os << "ship " << ships_map[&cell.ship_segment.getShip()] << ' '
                       << cell.ship_segment.getIndex() << ' ';
                }
                os << "| ";

            }
            os << '\n';
        }

        // CURSOR AND DOUBLE DAMAGE
        os << player.cursor.x << ' ' << player.cursor.y << '\n';
        os << player.double_damage_flag << '\n';
        
        // ABILITIES
        os << player.abilities.count() << '\n';
        for (const AbilityManager::AbilityData& ability : player.abilities) {
            os << ability.name << '\n';
        }

        return os;
    }

    std::istream &operator>>(std::istream &is, Player &player)
    {
        player = Player();
        is >> player.ships;

        vec2 size;
        is >> size.x >> size.y;
        player.field = Field(size);

        std::unordered_map<size_t, Ship*> ships_map;
        {
            size_t i = 0;
            for (Ship &ship : player.ships) {
                ships_map[i++] = &ship;
            }
        }

        std::string str;
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                Field::Cell &cell = player.field[vec2(x, y)];
                
                cell.has_fog = false;
                cell.marked = false;
                cell.ship_segment = Ship::SegmentView();

                is >> str;
                while (str != "|") {
                    if (str == "fog") {
                        cell.has_fog = true;
                    }
                    else if (str == "marked") {
                        cell.marked = true;
                    }
                    else if (str == "ship") {
                        size_t ship_index, segment_index;
                        is >> ship_index >> segment_index;
                        cell.ship_segment = Ship::SegmentView(ships_map[ship_index], segment_index);
                    }
                    is >> str;
                }
            }
        }

        // CURSOR AND DOUBLE DAMAGE
        is >> player.cursor.x >> player.cursor.y;
        is >> player.double_damage_flag;
        
        // ABILITIES
        ssize_t count;
        is >> count >> std::ws;
        while (count--) {
            std::getline(is, str);
            player.abilities.addAbility(str);
        }

        return is;
    }
}
