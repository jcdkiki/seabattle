#ifndef SEABATTLE_SETUP_AI_STATE_HPP_
#define SEABATTLE_SETUP_AI_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class SetupAIState : public GameState {
    public:
        static constexpr const char *name = "SetupAI";

        SetupAIState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;
    };
}

#endif
