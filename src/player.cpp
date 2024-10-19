#include "player.hpp"
#include "ability_manager.hpp"

#include <iostream>

namespace seabattle {
    void Player::attack(vec2 cursor, bool hidden)
    {
        bool ok = enemy_field.attack(cursor, hidden);
        if (double_damage_flag) {
            ok |= enemy_field.attack(cursor, hidden);
            double_damage_flag = false;
        }

        if (ok && enemy_field[cursor].ship_segment && enemy_field[cursor].ship_segment.getShip().isDestroyed()) {
            Ability &ability = abilities.addRandomAbility(*this);
            std::cout << "New ability: " << ability.getName() << std::endl;
        }
    }
    
    void Player::attack(bool hidden)
    {
        attack(cursor, hidden);
    }

    void Player::useAbility()
    {
        if (abilities.isEmpty()) {
            std::cout << "Player has no abilities" << std::endl;
            return;
        }

        Ability &ability = abilities.getAbility();
        std::cout << "Used ability: " << ability.getName() << std::endl; 
        ability.use(*this);
        abilities.popAbility();
    }

    void Player::createAbility()
    {
        
    }
}
