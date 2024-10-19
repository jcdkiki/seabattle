#ifndef SEABATTLE_TUI_OUTPUT_DEVICE_HPP_
#define SEABATTLE_TUI_OUTPUT_DEVICE_HPP_

#include "messages.hpp"
#include "messaging.hpp"
#include "field.hpp"

#include <iostream>

namespace seabattle {
    class TUIOutputDevice : public MessageReciever {
    public:
        void update() {}
        
        void drawField(const Field &field, bbox2 cursor)
        {
            vec2 size = field.getSize();
            for (int y = 0; y < size.y; y++) {
                for (int x = 0; x < size.x; x++) {
                    if (cursor.contains(vec2(x, y))) {
                        std::cout << "\033[31;1;4m";
                    }

                    const Field::Cell &cell = field[vec2(x, y)];
                    char c;
                    if (cell.has_fog) {
                        c = '#';
                    }
                    else if (cell.ship_segment) {
                        switch (*cell.ship_segment) {
                            case Ship::SegmentState::FULL:      c = '$'; break;
                            case Ship::SegmentState::DAMAGED:   c = '?'; break;
                            case Ship::SegmentState::DESTROYED: c = 'X'; break;
                            default:                            c = ' '; break;
                        }
                    }
                    else {
                        c = '.';
                    }

                    std::cout << c << ' ';

                    if (cursor.contains(vec2(x, y))) {
                        std::cout << "\033[0m";
                    }
                }
                std::cout << std::endl;
            }
        }

        bool handleLogMessage(const LogMessage &msg)
        {
            std::cout << msg.text << std::endl;
            return true;
        }

        bool handleRenderFieldMessage(const RenderFieldMessage &msg)
        {
            if (msg.location == RenderFieldMessage::LEFT) {
                std::cout << "LEFT FIELD:" << std::endl;
            }
            else {
                std::cout << "RIGHT FIELD:" << std::endl;
            }

            drawField(msg.field, msg.cursor);
            return true;
        }

        void handleDefault(const Message &msg) {}

        TUIOutputDevice()
        {
            registerHandler<LogMessage>((HandlerMethod)&TUIOutputDevice::handleLogMessage);
            registerHandler<RenderFieldMessage>((HandlerMethod)&TUIOutputDevice::handleRenderFieldMessage);
        }
    };
}

#endif
