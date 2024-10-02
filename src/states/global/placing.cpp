#include "states/global/placing.h"
#include "field.h"
#include "ship.h"
#include "states/global.h"
#include "states/global/battle.h"
#include <GL/gl.h>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <string>

namespace seabattle {
    PlacingState::PlacingState(GlobalState &global)
        : global(global),
          orientation(Ship::Orientation::HORIZONTAL),
          position(0, 0),
          size(1)
    {
        global.message.setString("Great. Now place your ships.");
        global.title.setString("WASD - move ship | Q/E - change ship size | R - rotate ship\n"
                               "Enter - place ship | Shift+Enter - finish");
    
        ship_count_text.setFont(global.font);
        ship_count_text.setCharacterSize(16);
        ship_count_text.setPosition(10, 50);
    }

    void PlacingState::onKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::R:
                orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
                break;
            case sf::Keyboard::E:
                size++;
                break;
            case sf::Keyboard::Q:
                size--;
                break;
            case sf::Keyboard::A:
                position.x--;
                break;
            case sf::Keyboard::D:
                position.x++;
                break;
            case sf::Keyboard::S:
                position.y++;
                break;
            case sf::Keyboard::W:
                position.y--;
                break;
            case sf::Keyboard::Enter:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    global.field.coverInFog();
                    global.substate = std::make_unique<BattleState>(global);
                    return;
                }

                try {
                    global.field.createShip(global.ship_manager, position, size, orientation, true);
                } catch (std::invalid_argument &e) {
                    global.message.setString(std::string("Error: ") + e.what());
                }
                break;
            default:
                break;
        }
    }

    void PlacingState::render()
    {
        vec2 delta = (orientation == Ship::Orientation::HORIZONTAL) ? vec2(1, 0) : vec2(0, 1);
        vec2 cur_position = position;

        glLoadIdentity();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        for (int i = 0; i < size; i++) {
            vec2 screen_coord = Field::field_position
                + vec2(cur_position.x * Field::cell_size.x, cur_position.y * Field::cell_size.y);
            
            glVertex2i(screen_coord.x, screen_coord.y);
            glVertex2i(screen_coord.x + Field::cell_size.x, screen_coord.y + Field::cell_size.y);
            glVertex2i(screen_coord.x, screen_coord.y + Field::cell_size.y);
            glVertex2i(screen_coord.x + Field::cell_size.x, screen_coord.y);

            cur_position += delta;
        }
        glEnd();

        std::string ship_count_str;
        for (int i = 1; i <= Ship::MAX_SIZE; i++) {
            ship_count_str += 
                std::to_string(i) + ": " +
                std::to_string(global.ship_manager.getAvailibleShipsCount(i)) + " left  |  ";
        }
        ship_count_text.setString(ship_count_str);

        global.window.pushGLStates();
        global.window.draw(ship_count_text);
        global.window.popGLStates();
    }
}
