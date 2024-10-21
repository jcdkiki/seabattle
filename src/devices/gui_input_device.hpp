#ifndef SEABATTLE_DEVICES_GUI_INPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_GUI_INPUT_DEVICE_HPP_

#include "messaging/message_generator.hpp"

namespace seabattle {
    class GUIInputDevice : public MessageGenerator {
    public:
        void update();
    };
}

#endif
