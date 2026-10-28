#include "characters/SuikaActionState.hpp"
// Complete-label unselected JP1.06a candidate; see SUIKA_ACTION_STATE_2026_10_28.md.
// Coverage and compilation are not semantic or byte-exact acceptance.
namespace th105 {
#define F(o) at<float>(o)
#define I(o) at<int>(o)
#define S(o) at<short>(o)
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
void SuikaActionStateView::dispatch_action_state_vslot28() {
    S(0x7a0)=0;S(0x7a2)=80;
    if(S(0x7a4)>0){--S(0x7a4);if(peer()->at<short>(0x174)<=0 || S(0x174)<=0)S(0x7a4)=0;peer()->counter(2,30);}
    if(S(0x7a6)>0){--S(0x7a6);if(peer()->at<short>(0x174)<=0 || S(0x174)<=0)S(0x7a6)=0;F(0x4c0)=static_cast<float>(F(0x4c0)*0.5);}
    if(S(0x186) || peer()->at<short>(0x48c))return;
    switch(action_id_13c){
#include "SuikaLowCases.inc"
#include "SuikaFlightCase.inc"
#include "SuikaLowTail.inc"
#include "SuikaMidNormalCases.inc"
#include "SuikaMidShotCases.inc"
#include "SuikaMidSkillCases.inc"
#include "SuikaHighSkillCases.inc"
#include "SuikaSpellCases.inc"
#include "SuikaSpecialCases.inc"
    default:common_update();return;
    }
}
#undef C
#undef B
#undef S
#undef I
#undef F
}
