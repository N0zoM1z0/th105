#pragma once

#include "GameMode.hpp"

namespace th105 {

struct FighterPhaseInitRequest {
    unsigned slot;
    MatchSetup::Side *side;
};

struct IntListView {
    void push_back(const int &value);
};

struct FighterPhaseContextRuntimeView {
    void begin_slot_4641f0(unsigned slot);
    void reset_slot_state_465040();
    void queue_init_request_466db0(const FighterPhaseInitRequest *request);
    void initialize_slot_sync_4642f0(unsigned slot, MatchSetup::Side *side);
    void initialize_slot_464270(
        unsigned slot, MatchSetup::Side *side, bool asynchronous);
};

} // namespace th105
