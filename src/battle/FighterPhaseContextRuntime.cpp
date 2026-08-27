#include "FighterPhaseContext.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

extern signed char g_fighter_phase_order_flag;

struct FighterPhaseSubobjectView {
    virtual void slot_00() = 0;
    virtual void slot_01() = 0;
    virtual void slot_02() = 0;
    virtual void slot_03() = 0;
    virtual void slot_04() = 0;
    virtual void phase_05(int value) = 0;
    virtual void phase_06() = 0;
};

struct FighterPhaseRenderStateView {
    void render_45aa00();
};

struct FighterPhaseFinalizeView {
    void phase_4653f0();
};

struct FighterPhaseObjectView {
    virtual void slot_00() = 0;
    virtual void slot_01() = 0;
    virtual void slot_02() = 0;
    virtual void slot_03() = 0;
    virtual void slot_04() = 0;
    virtual void slot_05() = 0;
    virtual void slot_06() = 0;
    virtual void slot_07() = 0;
    virtual void slot_08() = 0;
    virtual void slot_09() = 0;
    virtual void slot_0a() = 0;
    virtual void phase_vslot_0b() = 0;
    virtual void phase_vslot_0c() = 0;

    short action_13c() const
    {
        return *reinterpret_cast<const short *>(
            reinterpret_cast<const unsigned char *>(this) + 0x13c);
    }

    FighterPhaseSubobjectView *subobject_658()
    {
        return *reinterpret_cast<FighterPhaseSubobjectView **>(
            reinterpret_cast<unsigned char *>(this) + 0x658);
    }

    FighterPhaseRenderStateView *render_state_674()
    {
        return reinterpret_cast<FighterPhaseRenderStateView *>(
            reinterpret_cast<unsigned char *>(this) + 0x674);
    }

    FighterPhaseFinalizeView *finalize_state_3d0()
    {
        return reinterpret_cast<FighterPhaseFinalizeView *>(
            reinterpret_cast<unsigned char *>(this) + 0x3d0);
    }
};

void FighterPhaseContext::phase_463820()
{
    if (fighters_038[1]->action_13c() >= 300) {
        if (fighters_038[0]->action_13c() < 300)
            g_fighter_phase_order_flag = 1;
    } else {
        if (fighters_038[0]->action_13c() >= 300)
            g_fighter_phase_order_flag = 0;
    }

    g_render_mode_manager.set_gate_states(1, 1);
    g_render_mode_manager.set_state_23(8);

    fighters_038[1 - g_fighter_phase_order_flag]->phase_vslot_0b();
    fighters_038[g_fighter_phase_order_flag]->phase_vslot_0b();

    g_render_mode_manager.set_gate_states(0, 0);
    for (unsigned i = 2; i < fighters_038.size(); ++i)
        fighters_038[i]->phase_vslot_0b();
}

void FighterPhaseContext::phase_463970()
{
    for (unsigned i = 0; i < fighters_038.size(); ++i)
        fighters_038[i]->subobject_658()->phase_06();
    for (unsigned i = 0; i < fighters_038.size(); ++i)
        fighters_038[i]->phase_vslot_0c();
}

void FighterPhaseContext::phase_463a00(int value)
{
    for (unsigned i = 0; i < fighters_038.size(); ++i)
        fighters_038[i]->subobject_658()->phase_05(value);
}

void FighterPhaseContext::phase_463a60()
{
    for (unsigned i = 0; i < fighters_038.size(); ++i)
        fighters_038[i]->render_state_674()->render_45aa00();
}

void FighterPhaseContext::phase_463ab0()
{
    for (unsigned i = 0; i < fighters_038.size(); ++i)
        fighters_038[i]->finalize_state_3d0()->phase_4653f0();
}

} // namespace th105
