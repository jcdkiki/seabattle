#include "states/global/welcome.h"
#include "ship_manager.h"
#include "states/global/placing.h"
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>


namespace seabattle {
    WelcomeState::WelcomeState(GlobalState &global)
        : global(global),
          field_size(0, 0),
          is_width_done(false)
    {
        global.title.setString(
            "Create new field\n"
            "WASD - change field size | Enter - continue | Esc - exit"
        );
        
        field_size_text.setFont(global.font);
        field_size_text.setCharacterSize(16);
        field_size_text.setPosition(10, 50);
    }

    void WelcomeState::onKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::Enter:
                try {
                    global.field = Field(field_size);
                    global.ship_manager = ShipManager();
                } catch (std::invalid_argument &e) {
                    global.message.setString(std::string("Error: ") + e.what());
                    return;
                }
                global.substate = std::make_unique<PlacingState>(global);
                break;
            case sf::Keyboard::W:
                field_size.y++;
                break;
            case sf::Keyboard::S:
                field_size.y--;
                break;
            case sf::Keyboard::A:
                field_size.x--;
                break;
            case sf::Keyboard::D:
                field_size.x++;
                break;
            case sf::Keyboard::Escape:
                global.window.close();
                break;
            default:
                break;
        }
    }

    void WelcomeState::render()
    {
        field_size_text.setString("Field size: " + std::to_string(field_size.x) + " x " + std::to_string(field_size.y));
        global.window.pushGLStates();
        global.window.draw(field_size_text);
        global.window.popGLStates();
    }
}
