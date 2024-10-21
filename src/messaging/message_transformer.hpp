#ifndef SEABATTLE_MESSAGING_MESSAGE_TRANSFORMER_HPP_
#define SEABATTLE_MESSAGING_MESSAGE_TRANSFORMER_HPP_

#include "message_generator.hpp"
#include "message_reciever.hpp"

namespace seabattle {
    class MessageTransformer : public StaticMessageReciever, public StaticMessageGenerator {};
}

#endif
