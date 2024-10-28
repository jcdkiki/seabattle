#include "game.hpp"
#include <unistd.h> // for usleep()

namespace sb = seabattle;

#if defined(SEABATTLE_TUI_MODE)
    #include "io/tui_game_input.hpp"
    #include "io/tui_game_renderer.hpp"
    typedef sb::TUIGameRenderer Renderer;
    typedef sb::TUIGameInput Input;
#elif defined(SEABATTLE_TUI_GUI_MODE)
    #include "io/tui_game_input.hpp"
    #include "io/gui_game_renderer.hpp"
    typedef sb::TUIGameInput Input;
    typedef sb::GUIGameRenderer Renderer;
#elif defined(SEABATTLE_GUI_MODE)
    #include "io/gui_game_input.hpp"
    #include "io/gui_game_renderer.hpp"
    typedef sb::GUIGameRenderer Renderer;
    typedef sb::GUIGameInput Input;
#else
    #error "Unknown mode"
#endif

int main(int argc, char **argv)
{
    Renderer renderer;
    sb::Game game(renderer);

    Input input;
    while (game.isRunning()) {
        input >> game;
        renderer.update();
        usleep(10000);
    }
};
