#include "FighterInputRuntime.hpp"
#include "FighterInputSnapshotResetRuntime.hpp"
#include "Collision.hpp"
#include <deque>
#include <stddef.h>
namespace th105 {
struct ScriptedInputView {
#define SLOT(n) virtual void slot_##n();
 SLOT(00) SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18) SLOT(1c)
 SLOT(20) SLOT(24) SLOT(28) SLOT(2c) SLOT(30) SLOT(34) SLOT(38) SLOT(3c)
 SLOT(40) SLOT(44) SLOT(48) SLOT(4c) SLOT(50)
#undef SLOT
 virtual void bound_policy();
 virtual void cpu_policy();
 virtual void alternate_policy();
 unsigned char pad_004[0x100];
 signed char facing_104;
 unsigned char pad_105[0x37];
 short action_13c;
 unsigned char pad_13e[0x572];
 void *binding_6b0;
 int horizontal_6b4,vertical_6b8;
 int buttons_6bc[6];
 FighterInputSnapshotValues snapshot_6d4;
 int edge_6f4[6];
 signed char timer_70c;
 std::deque<short> history_710;
 unsigned state_724;
 unsigned state_728;
 signed char mode_72c;
 void sample();
 void select_scripted();
 void update();
};
extern int g_match_identifier;
int __cdecl selector_random_roll(int);
typedef char FacingOffset[offsetof(ScriptedInputView,facing_104)==0x104?1:-1];
typedef char ActionOffset[offsetof(ScriptedInputView,action_13c)==0x13c?1:-1];
typedef char BindingOffset[offsetof(ScriptedInputView,binding_6b0)==0x6b0?1:-1];
typedef char TimerOffset[offsetof(ScriptedInputView,timer_70c)==0x70c?1:-1];
typedef char HistoryOffset[offsetof(ScriptedInputView,history_710)==0x710?1:-1];
typedef char ModeOffset[offsetof(ScriptedInputView,mode_72c)==0x72c?1:-1];
void ScriptedInputView::update()
{
    if(binding_6b0) {
        reinterpret_cast<FighterInputRuntimeView *>(this)->update_input_4631c0();
        short packed=buttons_6bc[5]==1;
        packed=(packed<<1)|(buttons_6bc[4]==1);
        packed=(packed<<1)|(buttons_6bc[3]==1);
        packed=(packed<<1)|(buttons_6bc[2]==1);
        packed=(packed<<1)|(buttons_6bc[1]==1);
        packed=(packed<<1)|(buttons_6bc[0]==1);
        packed=(packed<<1)|(vertical_6b8>0);
        packed=(packed<<1)|(vertical_6b8<0);
        packed=(packed<<1)|(horizontal_6b4*facing_104>0);
        packed=(packed<<1)|(horizontal_6b4*facing_104<0);
        if(action_13c>=300 &&
            (buttons_6bc[0]==1 || buttons_6bc[1]==1 || buttons_6bc[2]==1 ||
             buttons_6bc[3]==1 || buttons_6bc[4]==1 || buttons_6bc[5]==1)) {
            snapshot_6d4.horizontal=horizontal_6b4;
            timer_70c=10;
            snapshot_6d4.vertical=vertical_6b8;
            snapshot_6d4.buttons[0]=buttons_6bc[0]==1;
            snapshot_6d4.buttons[1]=buttons_6bc[1]==1;
            snapshot_6d4.buttons[2]=buttons_6bc[2]==1;
            snapshot_6d4.buttons[3]=buttons_6bc[3]==1;
            snapshot_6d4.buttons[4]=buttons_6bc[4]==1;
            snapshot_6d4.buttons[5]=buttons_6bc[5]==1;
        } else if(action_13c<300 || timer_70c<=0) {
            snapshot_6d4.horizontal=0;
            snapshot_6d4.vertical=0;
            snapshot_6d4.buttons[0]=0;
            snapshot_6d4.buttons[1]=0;
            snapshot_6d4.buttons[2]=0;
            snapshot_6d4.buttons[3]=0;
            snapshot_6d4.buttons[4]=0;
            snapshot_6d4.buttons[5]=0;
            timer_70c=0;
        }
        if(timer_70c!=0)--timer_70c;
        history_710.push_back(packed);
        history_710.pop_front();
        bound_policy();
        return;
    }
    switch(mode_72c) {
    case 2: alternate_policy();break;
    case 3: reinterpret_cast<Fighter *>(this)->update_cpu_input_4633e0();break;
    default: cpu_policy();break;
    }
    switch(g_match_identifier) {
    case 0: if (static_cast<unsigned>(selector_random_roll(100)) >= 90) return; break;
    case 1: if (static_cast<unsigned>(selector_random_roll(100)) >= 50) return; break;
    case 2: if (static_cast<unsigned>(selector_random_roll(100)) >= 25) return; break;
    default: return;
    }
    edge_6f4[0]=0;buttons_6bc[0]=0;
    edge_6f4[1]=0;buttons_6bc[1]=0;
    edge_6f4[2]=0;buttons_6bc[2]=0;
    edge_6f4[3]=0;buttons_6bc[3]=0;
    edge_6f4[4]=0;buttons_6bc[4]=0;
    edge_6f4[5]=0;buttons_6bc[5]=0;
    state_728=0;
}
}
