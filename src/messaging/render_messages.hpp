#ifndef SEABATTLE_MESSAGING_RENDER_MESSAGES_HPP_
#define SEABATTLE_MESSAGING_RENDER_MESSAGES_HPP_

#include "message.hpp"
#include "field.hpp"

namespace seabattle {
    struct RenderFieldMessage : public Message {
        const Field &field;
        bbox2 cursor;

        RenderFieldMessage(const Field &field, bbox2 cursor) : field(field), cursor(cursor) {}
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

    struct RenderCursorMessage : public Message {
        vec2 position;
        RenderCursorMessage(vec2 position) : position(position) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<RenderCursorMessage>(*this); }
    };
}

#endif
