#ifndef SEABATTLE_SETUP_AI_STATE_HPP_
#define SEABATTLE_SETUP_AI_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class SetupAIState : public GameState {
    public:
        static constexpr const char *name = "SetupAI";

        void primaryAction();
        
        SetupAIState(Game &game);
        std::string_view getName() const;
    };
}

#endif
