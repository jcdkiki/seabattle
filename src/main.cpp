#include "game.hpp"
#include "tui_input_device.hpp"
#include "tui_output_device.hpp"

namespace sb = seabattle;

int main()
{
    sb::TUIInputDevice input;
    sb::TUIOutputDevice output;
    sb::Game game;

    while (game.isRunning()) {
        input.update();
        
        while (const sb::Message *msg = input.popMessage()) {
            game.handleMessage(msg);
        }

        while (const sb::Message *msg = game.popMessage()) {
            output.handleMessage(msg);
        }

        output.update();
    }
};
