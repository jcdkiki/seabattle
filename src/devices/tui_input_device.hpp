#ifndef SEABATTLE_DEVICES_TUI_INPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_TUI_INPUT_DEVICE_HPP_

#include "messaging.hpp"

namespace seabattle {
    class TUIInputDevice : public MessageGenerator {
    public:
        void update();
    };
}

#endif
