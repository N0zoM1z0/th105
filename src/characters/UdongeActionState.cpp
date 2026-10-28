#include "characters/UdongeActionState.hpp"
// Complete-label unselected JP1.06a candidate; see UDONGE_ACTION_STATE_2026_10_28.md.
// Coverage and compilation are not semantic or byte-exact acceptance.
namespace th105 {
#define F(o) at<float>(o)
#define I(o) at<int>(o)
#define S(o) at<short>(o)
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
void UdongeActionStateView::dispatch_action_state_vslot28() {
    S(0x7a0)=0;S(0x7a2)=95;
    if(S(0x7ae)>0 && !S(0x48c))--S(0x7ae);
    if(S(0x7ac)>0){
        ++S(0x4ac);if(!S(0x48c))--S(0x7ac);
        if(F(0x7a8)>=0.5f){F(0x7a8)=static_cast<float>(F(0x7a8)-static_cast<double>(0.05f));if(F(0x7a8)<=0.5f)F(0x7a8)=0.5f;}
    }else{
        if(F(0x7a8)<1.0f){F(0x7a8)=static_cast<float>(F(0x7a8)+static_cast<double>(0.05f));if(F(0x7a8)>1.0f)F(0x7a8)=1.0f;}
    }
    if(action_id_13c>149 && action_id_13c<159 && !B(0x751)){
        B(0x751)=1;float p[3];p[0]=0.0f;p[2]=0.0f;
        if(action_id_13c>149 && action_id_13c<154){p[1]=0.0f;spawn_offset(998,20,130.0,p,3);p[1]=1.0f;spawn_offset(998,60,130.0,p,3);}
        if(action_id_13c>153 && action_id_13c<158){p[1]=0.0f;spawn_offset(998,30,80.0,p,3);p[1]=1.0f;spawn_offset(998,70,80.0,p,3);}
        if(action_id_13c==158){p[1]=0.0f;spawn_offset(998,30,150.0,p,3);p[1]=1.0f;spawn_offset(998,70,150.0,p,3);}
    }
    if(F(0x7b4)!=0.0f){
        if(F(0x7b4)>4.0f)F(0x7b4)=4.0f;
        F(0x4bc)=static_cast<float>((F(0x7b4)*static_cast<double>(0.05f)+static_cast<double>(1.05f))*F(0x4bc));
        F(0x4c0)=static_cast<float>((static_cast<double>(0.975f)-F(0x7b4)*static_cast<double>(0.025f))*F(0x4c0));
        if(I(0x7b8)%30==0){float p[3]={0.0f,0.0f,4.0f};spawn_offset(859,0,100.0,p,3);}
        if(F(0x7b4)>1.0f && I(0x7b8)%45==0){
            float p[3]={0.0f,0.0f,5.0f};int direction=B(0x104);
            float y=static_cast<float>(static_cast<float>(udonge_random(100))+F(0xf0)-50.0);
            float x=static_cast<float>(static_cast<float>(udonge_random(200))+F(0xec)-100.0);
            spawn(859,x,y,direction,1,p,3);
        }
        if(F(0x7b4)>2.0f && I(0x7b8)%40==0){
            float p[3]={0.0f,0.0f,5.0f};int direction=B(0x104);
            float y=static_cast<float>(static_cast<float>(udonge_random(100))+F(0xf0)-50.0);
            float x=static_cast<float>(static_cast<float>(udonge_random(200))+F(0xec)-100.0);
            spawn(859,x,y,direction,1,p,3);
        }
        ++I(0x7b8);
    }else I(0x7b8)=0;
    if(S(0x174)>0){B(0x113)=static_cast<unsigned char>(S(0x7a6)*F(0x7a8));if(S(0x7a6)<=235)S(0x7a6)=static_cast<short>(S(0x7a6)+20);else S(0x7a6)=255;}
    if(S(0x186) || peer()->at<short>(0x48c))return;
    // Complete action inventory candidate; exact comparison remains required.
    switch(action_id_13c){
#include "UdongeLowCases.inc"
#include "UdongeFlightCase.inc"
#include "UdongeLowTail.inc"
#include "UdongeMidNormalCases.inc"
#include "UdongeMidShotCases.inc"
#include "UdongeMidSkillCases.inc"
#include "UdongeHighSkillCases.inc"
#include "UdongeSpellCases.inc"
#include "UdongeSpecialCases.inc"
    default:common_update();return;
    }
}
#undef C
#undef B
#undef S
#undef I
#undef F
}
