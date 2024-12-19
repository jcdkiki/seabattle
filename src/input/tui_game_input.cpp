#include "tui_game_input.hpp"
#include "input/input_messages.hpp"

#include <cctype>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

namespace seabattle {
    TUIGameInput::TUIGameInput()
    {
        fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    }

    static InputMessage *char2message(char c)
    {
        switch (c) {
        case 'w': return new MoveCursorMessage(vec2(0, -1));
        case 's': return new MoveCursorMessage(vec2(0, 1));
        case 'a': return new MoveCursorMessage(vec2(-1, 0));
        case 'd': return new MoveCursorMessage(vec2(1, 0));
        case 'e': return new PrimaryActionMessage();
        case 'r': return new SecondaryActionMessage();
        case 'f': return new TertiaryActionMessage();
        case 'q': return new QuitMessage();
        case 'S': return new SaveMessage();
        case 'L': return new LoadMessage();
        default: return nullptr;
        }
    }

    InputMessage *TUIGameInput::pollMessage()
    {
        char c = getc(stdin);
        
        if (c == 't') {
            asm("int $3"); // dirty hack to make a gdb breakpoint
            return nullptr;
        }

        return char2message(c);
    }
}
