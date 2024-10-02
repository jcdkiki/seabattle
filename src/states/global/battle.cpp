#include "states/global/battle.h"

#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <GL/gl.h>
#include <stdexcept>

#include "states/global/welcome.h"

namespace seabattle {
    BattleState::BattleState(GlobalState &global)
        : global(global),
          cursor(0, 0)
    {
        global.message.setString("Good job");
        global.title.setString(
            "Fight!!!\n"
            "WASD - move cursor | Enter - attack | Esc - exit"
        );
    }

    void BattleState::onKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::A:
                cursor.x--;
                break;
            case sf::Keyboard::D:
                cursor.x++;
                break;
            case sf::Keyboard::S:
                cursor.y++;
                break;
            case sf::Keyboard::W:
                cursor.y--;
                break;
            case sf::Keyboard::Enter:
                try {
                    global.field.attack(global.ship_manager, cursor);
                } catch (std::invalid_argument &e) {
                    global.message.setString(std::string("Error: ") + e.what());
                }
                break;
            case sf::Keyboard::Escape:
                global.substate = std::make_unique<WelcomeState>(global);
                return;
            default:
                break;
        }
    }

    void BattleState::render()
    {
        vec2 screen_coord = Field::field_position
            + vec2(cursor.x * Field::cell_size.x, cursor.y * Field::cell_size.y);

        glLoadIdentity();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        
        glVertex2i(screen_coord.x, screen_coord.y);
        glVertex2i(screen_coord.x + Field::cell_size.x, screen_coord.y + Field::cell_size.y);
        glVertex2i(screen_coord.x, screen_coord.y + Field::cell_size.y);
        glVertex2i(screen_coord.x + Field::cell_size.x, screen_coord.y);
        
        glEnd();
    }
}
