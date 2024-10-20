#include "game.hpp"
#include "devices/tui_input_device.hpp"
#include "devices/tui_output_device.hpp"
#include "devices/gui_input_device.hpp"
#include "devices/gui_output_device.hpp"
#include <cstddef>
#include <iostream>

namespace sb = seabattle;

template<typename Input, typename Output>
struct GameLoop {
    Input input;
    Output output;
    sb::Game game;

    void mainLoop()
    {
        while (game.isRunning()) {
            game.update(input, output);
        } 
    }
};

int main(int argc, char **argv)
{
    static const char usage_str[] = "usage: seabattle { tt, gg, tg }";

    sb::MessageGenerator *input = nullptr;
    sb::MessageReciever *output = nullptr;

    if (argc != 2) {
        std::cerr << usage_str << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "tt") == 0)
        GameLoop<sb::TUIInputDevice, sb::TUIOutputDevice>().mainLoop();
    else if (strcmp(argv[1], "tg") == 0)
        GameLoop<sb::TUIInputDevice, sb::GUIOutputDevice>().mainLoop();
    else if (strcmp(argv[1], "gg") == 0)
        GameLoop<sb::GUIInputDevice, sb::GUIOutputDevice>().mainLoop();
    else {
        std::cerr << usage_str << std::endl;
        return 1;
    }
};
