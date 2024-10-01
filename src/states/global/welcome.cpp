#include "states/global/welcome.h"
#include "states/global/placing.h"
#include <SFML/Window/Keyboard.hpp>


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

    bool WelcomeState::CreateField()
    {
        try {
            global.field = Field(field_size);
        } catch (std::exception &e) {
            global.message.setString(std::string("Error: ") + e.what());
            return false;
        }
        return true;
    }

    void WelcomeState::OnKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::Enter:
                if (this->CreateField()) {
                    global.substate = std::make_unique<PlacingState>(global);
                    return;
                }
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

    void WelcomeState::Render()
    {
        field_size_text.setString("Field size: " + std::to_string(field_size.x) + " x " + std::to_string(field_size.y));
        global.window.pushGLStates();
        global.window.draw(field_size_text);
        global.window.popGLStates();
    }
}
