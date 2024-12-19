#include "game.hpp"
#include "input_pipe.hpp"
#include "render_pipe.hpp"

namespace sb = seabattle;

#if defined(SEABATTLE_TUI_MODE)
    #include "input/tui_game_input.hpp"
    #include "renderer/tui_game_renderer.hpp"
    typedef sb::TUIGameRenderer Renderer;
    typedef sb::TUIGameInput Input;
#elif defined(SEABATTLE_TUI_GUI_MODE)
    #include "input/tui_game_input.hpp"
    #include "renderer/gui_game_renderer.hpp"
    typedef sb::TUIGameInput Input;
    typedef sb::GUIGameRenderer Renderer;
#elif defined(SEABATTLE_GUI_MODE)
    #include "input/gui_game_input.hpp"
    #include "renderer/gui_game_renderer.hpp"
    typedef sb::GUIGameRenderer Renderer;
    typedef sb::GUIGameInput Input;
#else
    #error "Unknown mode"
#endif

int main(int argc, char **argv)
{
    sb::Game game;
    sb::InputPipe<Input> input_pipe(game);
    sb::RenderPipe<Renderer> render_pipe(game);
    
    while (game.isRunning()) {
        input_pipe.pipeMessages();
        render_pipe.pipeMessages();
    }
};
