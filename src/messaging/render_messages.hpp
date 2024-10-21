#ifndef SEABATTLE_MESSAGING_RENDER_MESSAGES_HPP_
#define SEABATTLE_MESSAGING_RENDER_MESSAGES_HPP_

#include "message.hpp"
#include "field.hpp"

namespace seabattle {
    struct RenderFieldMessage : public Message {
        enum Location {
            LEFT,
            RIGHT
        };
        
        Location location;
        const Field &field;
        bbox2 cursor;

        RenderFieldMessage(Location location, const Field &field, bbox2 cursor) : location(location), field(field), cursor(cursor) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<RenderFieldMessage>(*this); }
    };

    struct RenderFieldPreviewMessage : public Message {
        vec2 size;
        
        RenderFieldPreviewMessage(vec2 size) : size(size) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<RenderFieldPreviewMessage>(*this); }
    };

    struct LogMessage : public Message {
        std::string text;

        LogMessage(std::string text) : text(text) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<LogMessage>(*this); }
    };
}

#endif
