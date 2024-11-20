#include "tui_game_input.hpp"

#include <iostream>
#include <unistd.h>

namespace seabattle {
    inline InputMessage char2message(char c)
    {
        switch (c) {
        case 'w':
            return InputMessage(InputMessage::CURSOR_UP);
        case 's':
            return InputMessage(InputMessage::CURSOR_DOWN);
        case 'a':
            return InputMessage(InputMessage::CURSOR_LEFT);
        case 'd':
            return InputMessage(InputMessage::CURSOR_RIGHT);
        case 'e':
            return InputMessage(InputMessage::PRIMARY_ACTION);
        case 'r':
            return InputMessage(InputMessage::SECONDARY_ACTION);
        case 'q':
            return InputMessage(InputMessage::QUIT);
        default:
            return InputMessage(InputMessage::INVALID);   
        }
    }

    void TUIGameInput::handle()
    {
        struct timeval tv;
        fd_set fds;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
        
        if (!FD_ISSET(0, &fds)) {
            return;
        }
        
        std::string cmd;
        std::getline(std::cin, cmd);

        const char *cur = cmd.c_str();
        while (*cur != '\0') {
            long int cnt = 1;
            
            if (isdigit(*cur)) {
                char *end;
                cnt = strtol(cur, &end, 10);
                cur = end;
            }

            if (*cur == '#') {
                while (*cur != '\n' && *cur != '\0') cur++;
                continue;
            }

            if (*cur == 't') {
                asm("int $3"); // dirty hack to make a gdb breakpoint
                cur++;
                continue;
            }

            for (long int i = 0; i < cnt; i++) {
                InputMessage msg = char2message(*cur);
                if (msg.kind != InputMessage::INVALID) {
                    game.handle(msg);
                }
            }
            cur++;
        }
    }
}
