#pragma once

#include "BattleManagerVirtuals.hpp"

namespace th105 {

// Current CBattleManagerArcade constructor publishes vtable 0x006C154C after
// CBattleManager construction. The fields below are exposed through accessors
// because only their current offsets, not the intervening derived layout, are
// yet proved.
struct CBattleManagerArcade : CBattleManager {
    virtual void prepare_battle_setup_472110(MatchSetup *setup);
    virtual void transition_slot_34(int value);
    virtual int run_info_phase_pipeline_472f10();

    void prepare_arcade_transition_473050();
    void finalize_arcade_round_473110();

    __forceinline int &transition_resource_5bc()
    {
        return *reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(this) + 0x5bc);
    }

    __forceinline unsigned char &fade_transition_pending_5c4()
    {
        return *(reinterpret_cast<unsigned char *>(this) + 0x5c4);
    }
};

} // namespace th105
