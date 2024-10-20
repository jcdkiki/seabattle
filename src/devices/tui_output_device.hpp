#ifndef SEABATTLE_DEVICES_TUI_OUTPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_TUI_OUTPUT_DEVICE_HPP_

#include "messaging.hpp"
#include "messages.hpp"
#include <cstdint>

namespace seabattle {
    class TUIOutputDevice : public MessageReciever {
        void drawField(const Field &field, bbox2 cursor);
    
        void handleLogMessage(std::unique_ptr<const LogMessage> msg);
        void handleRenderFieldMessage(std::unique_ptr<const RenderFieldMessage> msg);
        void handleRenderFieldPreviewMessage(std::unique_ptr<const RenderFieldPreviewMessage> msg);
    public:
        TUIOutputDevice();

        void update();
    };
}

#endif
