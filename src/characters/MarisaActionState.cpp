#include "characters/MarisaActionState.hpp"
// Complete unselected JP1.06a candidate. See MARISA_ACTION_STATE_2026_10_28.md.
// Coverage is not semantic or byte-exact acceptance.
namespace th105 {
#define F(o) at<float>(o)
#define I(o) at<int>(o)
#define S(o) at<short>(o)
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
void MarisaActionStateView::dispatch_action_state_vslot28() {
    S(0x7a0)=0;S(0x7a2)=106;
    if(S(0x7a6)>0){
        if((action_id_13c>=600 && action_id_13c!=615) || (action_id_13c==615 && !frame_index_140)){
            S(0x7a6)=0;S(0x7a8)=0;S(0x7a4)=0;F(0x7ac)=0.0f;F(0x7b0)=0.0f;
        }
        --S(0x7a6);--S(0x7a8);
        if(S(0x174)<=0 || peer()->at<short>(0x174)<=0){S(0x7a6)=0;S(0x7a8)=0;S(0x7a4)=0;}
        if(action_id_13c>=50 && action_id_13c<=149){S(0x7a8)=0;S(0x7a4)=0;}
        if(S(0x7a8)<=0){S(0x7a8)=0;S(0x7a4)=0;}
        if(!S(0x7a4)){
            if(F(0x7b0)>3.0f){F(0x7b0)=static_cast<float>(F(0x7b0)-static_cast<double>(0.1f));if(F(0x7b0)<3.0f)F(0x7b0)=3.0f;}
            if(F(0x7b0)<3.0f){F(0x7b0)=static_cast<float>(F(0x7b0)+static_cast<double>(0.1f));if(F(0x7b0)>3.0f)F(0x7b0)=3.0f;}
        }
        if(S(0x7a4)>=1 && S(0x7a4)<=7){
            // Native 4A38CD/38FF compares the adjusted value with 3, then stores 12.
            if(F(0x7b0)>12.0f){F(0x7b0)=static_cast<float>(F(0x7b0)-static_cast<double>(0.1f));if(F(0x7b0)<3.0f)F(0x7b0)=12.0f;}
            if(F(0x7b0)<12.0f){F(0x7b0)=static_cast<float>(F(0x7b0)+static_cast<double>(0.1f));if(F(0x7b0)>3.0f)F(0x7b0)=12.0f;}
            if(S(0x7a8)%5==0 && S(0x7a4)==1 && S(0x7a8)>0)S(0x7a4)=static_cast<short>(marisa_random(4)+2);
        }
        if(S(0x7a4)==8){
            if(F(0x7b0)>0.5f){F(0x7b0)=static_cast<float>(F(0x7b0)-static_cast<double>(0.1f));if(F(0x7b0)<0.5f)F(0x7b0)=0.5f;}
            if(F(0x7b0)<0.5f){F(0x7b0)=static_cast<float>(F(0x7b0)+static_cast<double>(0.1f));if(F(0x7b0)>0.5f)F(0x7b0)=0.5f;}
        }
        F(0x7ac)-=F(0x7b0);
    }else{S(0x7a6)=0;S(0x7a8)=0;S(0x7a4)=0;F(0x7ac)=0.0f;F(0x7b0)=0.0f;}
    if(action_id_13c==720){
        if(sequence_index_13e==1){
            F(0x740)=static_cast<float>(F(0x740)+4.0);if(F(0x740)>=120.0)F(0x740)=120.0f;
            if(F(0x744)>3.0f){F(0x744)=static_cast<float>(F(0x744)-static_cast<double>(0.1f));if(F(0x744)<=3.0f)F(0x744)=3.0f;}
            if(F(0x744)<3.0f){F(0x744)=static_cast<float>(F(0x744)+static_cast<double>(0.1f));if(F(0x744)>=3.0f)F(0x744)=3.0f;}
            F(0x73c)+=F(0x744);
        }
        if(sequence_index_13e>=2 && sequence_index_13e<=5){
            if(F(0x744)>3.0f){F(0x744)=static_cast<float>(F(0x744)-static_cast<double>(0.1f));if(F(0x744)<=3.0f)F(0x744)=3.0f;}
            if(F(0x744)<3.0f){F(0x744)=static_cast<float>(F(0x744)+static_cast<double>(0.1f));if(F(0x744)>=3.0f)F(0x744)=3.0f;}
            F(0x73c)+=F(0x744);
        }
        if(sequence_index_13e==6){
            // Native compares against 12 before adjustment, then clamps to 11.
            if(F(0x744)>12.0f){F(0x744)=static_cast<float>(F(0x744)-static_cast<double>(0.1f));if(F(0x744)<=11.0f)F(0x744)=11.0f;}
            if(F(0x744)<12.0f){F(0x744)=static_cast<float>(F(0x744)+static_cast<double>(0.1f));if(F(0x744)>=11.0f)F(0x744)=11.0f;}
            F(0x73c)+=F(0x744);
        }
        if(sequence_index_13e==7){
            if(F(0x744)>0.5f){F(0x744)=static_cast<float>(F(0x744)-static_cast<double>(0.1f));if(F(0x744)<=0.5f)F(0x744)=0.5f;}
            if(F(0x744)<0.5f){F(0x744)=static_cast<float>(F(0x744)+static_cast<double>(0.1f));if(F(0x744)>=0.5f)F(0x744)=0.5f;}
            F(0x73c)+=F(0x744);
        }
    }
    if(action_id_13c>149 && action_id_13c<159 && !B(0x751)){
        B(0x751)=1;
        if(action_id_13c>149 && action_id_13c<154)spawn_offset(998,57,94.0,0,0);
        if(action_id_13c>153 && action_id_13c<158)spawn_offset(998,57,60.0,0,0);
        if(action_id_13c==158)spawn_offset(998,57,100.0,0,0);
    }
    if(S(0x186) || peer()->at<short>(0x48c))return;
    switch(action_id_13c){
#include "MarisaLowCases.inc"
#include "MarisaFlightCase.inc"
#include "MarisaLowTail.inc"
#include "MarisaMidNormalCases.inc"
#include "MarisaMidShotCases.inc"
#include "MarisaMidSkillCases.inc"
#include "MarisaHighSkillCases.inc"
#include "MarisaSpellCases.inc"
#include "MarisaSpecialCases.inc"
    default:common_update();return;
    }
}
#undef C
#undef B
#undef S
#undef I
#undef F
}
