// Complete manual JP1.06a SuikaObject update hypothesis, 005b0460.
#include "characters/SuikaObjectUpdate.hpp"
namespace th105 {
#define FIELD(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) FIELD(this,float,o)
#define I(o) FIELD(this,int,o)
#define S(o) FIELD(this,short,o)
#define US(o) FIELD(this,unsigned short,o)
#define B(o) FIELD(this,unsigned char,o)
#define C(o) FIELD(this,signed char,o)
#define PARAM FIELD(this,float*,0x340)
#define OWNER FIELD(this,void*,0x348)
#define RELATED FIELD(this,void*,0x34c)
#define TARGET FIELD(this,void*,0x170)
#define MOTION reinterpret_cast<SuikaUpdateMotionView*>(reinterpret_cast<unsigned char*>(this)+4)
#define WAVE(n) reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->dispatch_character_wave_handle(n)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define RETIRE() do { --I(0x330); return; } while(0)
#define MOVE() do {F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}while(0)
#define FINISH() do {if(advance_frame()) --I(0x330);return;}while(0)
void SuikaObjectUpdateView::update_action_state() {
void *entryOwner=OWNER;int *entryOwnerMode=&FIELD(entryOwner,int,0x4b8);
switch(S(0x13c)) {
case 800: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(emit_repeated(0,0,5)) RETIRE();F(0x12c)+=5.0;F(0xf8)-=1.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);
        if(stage_surface_height()>=nextY && F(0xf8)<0.0f) {F(0xf8)=-F(0xf8);if(F(0xf8)>30.0f) F(0xf8)=30.0f;}advance_phase(3);advance_six(0);
        if(I(0x180)!=0) {float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=2.0f;spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();}
    }
    if(S(0x13e)==1) {F(0x11c)-=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=8) RETIRE();B(0x113)-=8;B(0x112)-=8;B(0x111)-=8;}
    if(S(0x13e)==2) {F(0x11c)+=static_cast<double>(0.06f);F(0x120)=F(0x11c);if(B(0x113)<=12) RETIRE();B(0x113)-=12;B(0x112)-=12;B(0x111)-=12;}
    if(S(0x13e)==3) {
        if(emit_repeated(0,2,3)) RETIRE();if(I(0x180)!=0) {
            WAVE(4);float packet[3]={0.0f,0.0f,4.0f};spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=5.0f;
            for(int count=6;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(10))+5.0);spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);}packet[2]=6.0f;spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
    }
    if(S(0x13e)==4) {F(0x11c)*=static_cast<double>(0.95f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;}
    if(S(0x13e)==5) {float *parameters=PARAM;F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);F(0x12c)=F(0x370)+F(0x12c);parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<=8) RETIRE();B(0x113)-=8;B(0x110)-=8;B(0x111)-=8;}
    if(S(0x13e)==6) {F(0x11c)+=static_cast<double>(0.15f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(S(0x13e)==7) {F(0x11c)+=static_cast<double>(0.15f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;}
    if(!(F(0xec)<=1380.0f) || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();


}
case 801: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(emit_repeated(1,3,5)) RETIRE();float speed=2.5f;if(F(0xf4)>2.5f) speed=static_cast<float>(F(0xf4)-1.0);F(0xf4)=speed;F(0xf8)-=static_cast<double>(0.6f);
        float packet[3]={RF(360),10.0f,4.0f};spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
        if(I(0x144)>=30) {WAVE(5);float burst[3];int angle=0;do {burst[0]=static_cast<float>(angle);burst[1]=17.0f;burst[2]=1.0f;spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,burst,3);angle+=20;}while(angle<360);burst[2]=3.0f;spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,burst,3);RETIRE();}
    }
    if(S(0x13e)==1) {if(emit_repeated(0,1,0)) RETIRE();float *parameters=PARAM;if(parameters[1]>2.0f) parameters[1]-=1.0;MOTION->set_components(parameters[0],parameters[1]);if(C(0x184)<=0 || I(0x144)>=60) {B(0x184)=0;F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(F(0x11c)<=0.01f) RETIRE();}}
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.3f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(S(0x13e)==4) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.95f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);return;


}
case 810: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {if(emit_repeated(1,3,5)) RETIRE();if(I(0x144)%5==0) {float packet[4]={0.0f,0.0f,1.0f,0.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=2.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,4);}if(PARAM[3]<=static_cast<double>(I(0x144))) RETIRE();}
    if(S(0x13e)==1) {F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(S(0x13e)==2) {F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;}
    if(S(0x13e)==3) {PARAM[1]*=static_cast<double>(0.95f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;MOTION->set_components(PARAM[0],PARAM[1]);}
    if(S(0x13e)==4) {if(emit_repeated(1,3,5)) RETIRE();if(I(0x144)%5==0) {float packet[4]={0.0f,0.0f,5.0f,0.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=2.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,4);}if(PARAM[3]<=static_cast<double>(I(0x144))) RETIRE();}
    if(S(0x13e)==5) {F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();


}
case 811: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();
    if(S(0x13e)==0) {
        if(collision==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)==4 && US(0x364)<5) {++US(0x364);I(0x180)=0;++B(0x184);}
        if(I(0x144)==6 && FIELD(OWNER,signed char,0x605)>=4) {float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(811,static_cast<float>(static_cast<double>(100*C(0x104))+F(0xec)),F(0xf0),B(0x104),1,packet,3);}
    }
    if(S(0x13e)==1) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<10) RETIRE();B(0x113)-=10;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));}
    if(S(0x13e)==2) {F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=30) RETIRE();B(0x113)-=30;B(0x110)-=30;B(0x111)-=30;}
    if(S(0x13e)==3) {
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)==4 && US(0x364)<5) {++US(0x364);I(0x180)=0;++B(0x184);}
        if(I(0x144)==6 && FIELD(OWNER,signed char,0x605)>=4) {float packet[3]={0.0f,0.0f,4.0f};spawn_unparented(811,static_cast<float>(static_cast<double>(100*C(0x104))+F(0xec)),F(0xf0),B(0x104),1,packet,3);}
    }
    if(S(0x13e)==4) {
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)==4 && US(0x364)<5) {++US(0x364);I(0x180)=0;++B(0x184);}
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && ((S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) || (S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) || (S(0x142)==0 && S(0x140)==0 && S(0x13e)==5))) --I(0x330);return;
}


}
case 812: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();
    if(US(0x13e)<=1) {if(emit_repeated(0,2,0)) RETIRE();if(F(0xf8)>3.0f) F(0x370)=-0.1f;if(F(0xf8)<-3.0f) F(0x370)=0.1f;F(0xf8)=F(0x370)+F(0xf8);if(S(0x174)<0) goto suika_812_impact;collision=I(0x180);if(collision!=0) goto suika_812_impact;}
    unsigned short phase=US(0x13e);
    if(phase==2 || phase==3) {
        unsigned short action=FIELD(OWNER,unsigned short,0x13c);if(action>49 && action<150) {for(int count=2;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);RETIRE();}
        if(S(0x174)<0 || collision!=0) goto suika_812_impact;
        if(phase==2) {F(0xf8)-=static_cast<double>(0.3f);double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()>=nextY) {F(0xf0)=stage_surface_height();next_sequence_block();F(0xf8)=0.0f;F(0xf4)=static_cast<float>(static_cast<double>(RF(4))+6.0);return;}}
        if(S(0x13e)==3) {
            double currentY=F(0xf0);if(stage_surface_height()>currentY || S(0x174)<0 || I(0x180)!=0) {
suika_812_impact:
                select_sequence(4);F(0xf4)=-4.0f;F(0xf8)=10.0f;F(0x100)=0.3f;B(0x184)=0;return;
            }
            currentY=F(0xf0);if(stage_surface_height()<currentY) {select_sequence(2);return;}
        }
    }
    phase=US(0x13e);if(phase==4 || phase==5) {F(0xf8)-=0.5;if(F(0xf8)<0.0f) {double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()>=nextY) {F(0xf0)=stage_surface_height();F(0xf4)=0.0f;F(0xf8)=0.0f;select_sequence(6);return;}}}
    if(S(0x13e)==7) {if(B(0x113)<=30) RETIRE();B(0x113)-=30;B(0x110)-=30;B(0x111)-=30;}
    MOVE();if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();FINISH();
}


}
case 813: {

    if(S(0x13e)==0) {
        if(emit_repeated(0,2,3)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==560 || action==561) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) RETIRE();
        F(0xf4)-=static_cast<double>(0.1f);if(F(0xf4)<3.0f) F(0xf4)=3.0f;F(0x12c)+=40.0;F(0xf8)-=static_cast<double>(0.3f);
        if(I(0x144)>=40) {F(0xf4)=0.0f;F(0xf8)=0.0f;S(0x366)=static_cast<short>(20*(FIELD(owner,signed char,0x607)+3));next_sequence_block();WAVE(15);F(0x11c)=0.0f;F(0x120)=0.0f;}
    }
    if(S(0x13e)==1) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==560 || action==561) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {I(0x144)=S(0x366)+1;return;}
        F(0x12c)+=40.0;
        if(I(0x144)>S(0x366)) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)<=0.0f) RETIRE();}
        else {
            if(F(0x11c)<1.0f) {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(813,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            F(0x370)+=0.25;if(F(0x370)>7.0f) F(0x370)=7.0f;void *target=TARGET;owner=OWNER;
            if(FIELD(target,float,0xec)>=static_cast<double>(F(0xec))) FIELD(owner,float,0x6ac)=static_cast<float>(FIELD(owner,float,0x6ac)-static_cast<double>(FIELD(target,signed char,0x104))*F(0x370));else FIELD(owner,float,0x6ac)=static_cast<float>(static_cast<double>(FIELD(target,signed char,0x104))*F(0x370)+FIELD(owner,float,0x6ac));
        }
    }
    if(S(0x13e)==2) {F(0x12c)+=40.0;F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==3) {F(0xf4)-=static_cast<double>(0.1f);if(F(0xf4)<3.0f) F(0xf4)=3.0f;F(0x12c)+=40.0;F(0xf8)-=static_cast<double>(0.3f);if(I(0x144)>=40) {F(0xf4)=0.0f;F(0xf8)=0.0f;next_sequence_block();WAVE(15);F(0x11c)=0.0f;F(0x120)=0.0f;}}
    if(S(0x13e)==4) {
        F(0x12c)+=40.0;
        if(I(0x144)>120 || C(0x184)<=0) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)<=0.0f) RETIRE();}
        else {
            if(F(0x11c)<1.0f) {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);}
            if(I(0x180)==6) {if(++S(0x364)<=4) {if(C(0x184)>0) I(0x180)=0;}else {I(0x180)=0;++B(0x184);S(0x364)=0;}}
            if(I(0x180)==4) I(0x180)=0;if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>=10) {I(0x180)=0;S(0x364)=0;}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(813,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            F(0x370)+=0.25;if(F(0x370)>7.0f) F(0x370)=7.0f;void *target=TARGET;void *owner=OWNER;
            if(FIELD(target,float,0xec)>=static_cast<double>(F(0xec))) FIELD(owner,float,0x6ac)=static_cast<float>(FIELD(owner,float,0x6ac)-static_cast<double>(FIELD(target,signed char,0x104))*F(0x370));else FIELD(owner,float,0x6ac)=static_cast<float>(static_cast<double>(FIELD(target,signed char,0x104))*F(0x370)+FIELD(owner,float,0x6ac));
        }
    }
    if(S(0x13e)==5) {F(0x12c)+=40.0;F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}MOVE();FINISH();


}
case 815: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0x12c)+=40.0;if(emit_repeated(1,2,2)) RETIRE();
        if(I(0x144)%3==0) {float packet[4]={0.0f,0.0f,5.0f,1.0f};spawn_unparented(815,static_cast<float>(static_cast<double>(RF(100))+F(0xec)-50.0),static_cast<float>(static_cast<double>(RF(100))+F(0xf0)-50.0),B(0x104),1,packet,4);}
        advance_six(5);
        if(I(0x180)==0) {double currentY=F(0xf0);if(stage_surface_height()<currentY) break;}
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,3.0f,1.0f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*60.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(20))+10.0);spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 1: {
        F(0x12c)+=40.0;if(emit_repeated(1,2,5)) RETIRE();
        advance_six(10);advance_phase(3);
        if(I(0x144)%3==0) {float packet[4]={0.0f,0.0f,5.0f,1.5f};spawn_unparented(815,static_cast<float>(static_cast<double>(RF(150))+F(0xec)-75.0),static_cast<float>(static_cast<double>(RF(150))+F(0xf0)-75.0),B(0x104),1,packet,4);}
        if(I(0x180)==0) {double currentY=F(0xf0);if(stage_surface_height()<currentY) break;}
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,3.0f,1.5f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<8.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*45.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(25))+10.0);spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 2: {
        F(0x12c)+=40.0;if(emit_repeated(1,3,5)) RETIRE();
        advance_six(0);advance_phase(10);
        if(I(0x144)%3==0) {float packet[4]={0.0f,0.0f,5.0f,2.0f};spawn_unparented(815,static_cast<float>(static_cast<double>(RF(200))+F(0xec)-100.0),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)-100.0),B(0x104),1,packet,4);}
        if(I(0x180)==0) {double currentY=F(0xf0);if(stage_surface_height()<currentY) break;}
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,3.0f,2.0f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<10.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*36.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(30))+10.0);spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 3:F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;break;
    case 4:PARAM[1]*=static_cast<double>(0.85f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;MOTION->set_components(PARAM[0],PARAM[1]);break;
    case 5:PARAM[1]*=static_cast<double>(0.85f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;F(0xf8)-=static_cast<double>(0.1f);break;
    case 6: {
        float *parameters=PARAM;parameters[1]-=0.25;if(parameters[1]<=1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);
        if(!(PARAM[1]>6.0f)) {if(B(0x111)>=15) {B(0x111)-=15;B(0x110)-=15;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<15) RETIRE();B(0x113)-=15;}}break;
    }
    case 7: {
        if(emit_repeated(0,2,5)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action!=505 && action!=506 && action!=507 && action!=508) RETIRE();F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(10*FIELD(owner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+50.0);packet[2]=10.0f;
            spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%8==0) {float packet[3]={RF(360),15.0f,11.0f};spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        owner=OWNER;if(I(0x144)>=15*(3-(FIELD(owner,unsigned char,0x608)>=4))) {float packet[3]={0.0f,0.0f,12.0f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=13.0f;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);next_sequence_block();return;}
        if(FIELD(OWNER,short,0x732)!=1) break;
        float packet[3];packet[1]=30.0f;packet[2]=0.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(packet[0]<0.0f) packet[0]=0.0f;if(packet[0]>60.0f) packet[0]=60.0f;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 8: {
        if(emit_repeated(0,2,5)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action!=505 && action!=506 && action!=507 && action!=508) RETIRE();F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(10*FIELD(owner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+75.0);packet[2]=10.0f;
            spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%4==0) {float packet[3]={RF(360),17.0f,11.0f};spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        owner=OWNER;if(I(0x144)>=20*(3-(FIELD(owner,unsigned char,0x608)>=4))) {float packet[3]={0.0f,0.0f,12.0f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=13.0f;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);next_sequence_block();return;}
        if(FIELD(OWNER,short,0x732)!=1) break;
        float packet[3];packet[1]=30.0f;packet[2]=1.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(packet[0]<0.0f) packet[0]=0.0f;if(packet[0]>60.0f) packet[0]=60.0f;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 9: {
        if(emit_repeated(0,2,5)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action!=505 && action!=506 && action!=507 && action!=508) RETIRE();F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(10*FIELD(owner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+100.0);packet[2]=10.0f;
            double centerY=F(0xf0)+200.0;double centerX=F(0xec)+200.0;spawn_parented(815,static_cast<float>(centerX-static_cast<double>(RF(400))),static_cast<float>(centerY-static_cast<double>(RF(400))),B(0x104),1,packet,3);
        }
        if(I(0x144)%2==0) {float packet[3]={RF(360),19.0f,11.0f};spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(FIELD(OWNER,short,0x732)!=1) break;
        float packet[3];packet[1]=30.0f;packet[2]=2.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(packet[0]<0.0f) packet[0]=0.0f;if(packet[0]>60.0f) packet[0]=60.0f;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 10: {
        if(!RELATED) RETIRE();float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);double x=lookup_orientation_cosine_quantized_abs(parameters[0]);parameters=PARAM;F(0xec)=static_cast<float>(x*parameters[1]+FIELD(RELATED,float,0xec));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])*PARAM[1]+FIELD(RELATED,float,0xf0));
        if(B(0x111)>=20) {B(0x111)-=20;B(0x110)-=20;}else {if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    }
    case 11: {
        if(!RELATED) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);void *related=RELATED;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)+=F(0xf8);F(0xec)=FIELD(related,float,0xec)+F(0x370);F(0xf0)=FIELD(related,float,0xf0)+F(0x374);F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.1f);
        if(B(0x111)>=30) {B(0x111)-=30;B(0x110)-=30;}else {if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    }
    case 12:F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x111)>=128) {B(0x111)+=128;B(0x110)+=128;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<80) RETIRE();B(0x113)-=80;}break;
    case 13:F(0x11c)+=0.5;F(0x120)=F(0x11c);if(B(0x111)>=30) {B(0x111)-=30;B(0x110)-=30;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<30) RETIRE();B(0x113)-=30;}break;
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1460.0 || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();


}
case 816: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(emit_repeated(0,0,3)) RETIRE();advance_six(5);advance_phase(3);
        if(S(0x364)==0) {
            if(I(0x180)!=0) {S(0x364)=1;F(0x11c)=3.0f;F(0x120)=3.0f;return;}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(816,static_cast<float>(static_cast<double>(RF(50))-25.0+F(0xec)),static_cast<float>(static_cast<double>(RF(50))-25.0+F(0xf0)),B(0x104),-1,packet,3);}
            if(I(0x144)>=90) {S(0x364)=1;F(0x11c)=3.0f;F(0x120)=3.0f;return;}
        }
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;}
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]*=static_cast<double>(0.96f);if(parameters[1]<0.5f) parameters[1]=0.5f;MOVE();
    }
    if(S(0x13e)==1) {if(B(0x113)<13) RETIRE();B(0x113)-=13;F(0x11c)*=static_cast<double>(0.94f);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.1f);F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);}
    if(S(0x13e)==2) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<10) RETIRE();B(0x113)-=10;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));}
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();FINISH();


}
case 817: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        float *parameters=PARAM;void *owner=OWNER;double orbitX=lookup_orientation_cosine_quantized_abs(parameters[0]);parameters=PARAM;float x=static_cast<float>(orbitX*FIELD(owner,float,0x73c)+FIELD(owner,float,0xec));owner=OWNER;F(0xec)=x;
        F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])*FIELD(owner,float,0x73c)+(FIELD(owner,float,0xf0)+100.0));
        if(I(0x144)%8==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(5))+5.0);packet[2]=1.0f;spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);}if(!(FIELD(OWNER,float,0x73c)>0.0f)) RETIRE();break;
    }
    case 1:case 2: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);
        if(I(0x144)>=2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 3:
        if(emit_repeated(0,0,4)) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);{float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;}
        if(I(0x144)>=60 || C(0x184)<=0) RETIRE();if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(5))+2.0);packet[2]=4.0f;spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);}MOVE();break;
    case 4: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);if(I(0x144)>=0) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}MOVE();break;
    }
    case 5: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)>10) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}else {if(B(0x113)>220) B(0x113)=255;else B(0x113)+=30;}MOVE();break;
    }
    }FINISH();


}
case 818: {

    if(S(0x13e)==0) {
        if(emit_repeated(0,2,3)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==565 || action==566) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) RETIRE();
        F(0xf4)-=static_cast<double>(0.1f);if(F(0xf4)<3.0f) F(0xf4)=3.0f;F(0x12c)+=40.0;F(0xf8)-=static_cast<double>(0.3f);
        if(I(0x144)>=40) {F(0xf4)=0.0f;F(0xf8)=0.0f;next_sequence_block();S(0x366)=60;WAVE(25);F(0x11c)=0.0f;F(0x120)=0.0f;}
    }
    if(S(0x13e)==1) {
        F(0x12c)+=40.0;int duration=S(0x366);
        if(I(0x144)<=duration) {
            void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==565 || action==566) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {I(0x144)=duration+1;return;}
            if(emit_repeated(0,2,3)) RETIRE();if(F(0x11c)<1.0f) {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(818,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            unsigned char level=FIELD(OWNER,unsigned char,0x60b);
            if(level>2) {
                if(level<=3) {if(I(0x144)%4==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(FIELD(OWNER,signed char,0x60b)*1.5+13.0);packet[2]=7.0f;spawn_unparented(818,F(0xec),F(0xf0),B(0x104),1,packet,3);}}
                else if(I(0x144)%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(FIELD(OWNER,signed char,0x60b)*1.5+13.0);packet[2]=7.0f;spawn_unparented(818,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            }else if(I(0x144)%5==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(FIELD(OWNER,signed char,0x60b)*1.5+13.0);packet[2]=7.0f;spawn_unparented(818,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        }else {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)<=0.0f) RETIRE();}
    }
    if(S(0x13e)==2) {F(0x12c)-=40.0;F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==3) {F(0xf4)-=static_cast<double>(0.1f);if(F(0xf4)<3.0f) F(0xf4)=3.0f;F(0x12c)+=40.0;F(0xf8)-=static_cast<double>(0.3f);if(I(0x144)>=40) {F(0xf4)=0.0f;F(0xf8)=0.0f;next_sequence_block();WAVE(15);F(0x11c)=0.0f;F(0x120)=0.0f;}}
    if(S(0x13e)==4) {
        F(0x12c)+=40.0;
        if(I(0x144)>120 || C(0x184)<=0) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)<=0.0f) RETIRE();}
        else {
            if(F(0x11c)<1.0f) {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);}
            if(I(0x180)==6) {if(++S(0x364)<=4) {if(C(0x184)>0) I(0x180)=0;}else {I(0x180)=0;++B(0x184);S(0x364)=0;}}
            if(I(0x180)==4) I(0x180)=0;if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>=10) {I(0x180)=0;S(0x364)=0;}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(818,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            F(0x370)+=0.25;if(F(0x370)>7.0f) F(0x370)=7.0f;void *target=TARGET;void *owner=OWNER;
            if(FIELD(target,float,0xec)>=static_cast<double>(F(0xec))) FIELD(owner,float,0x6ac)=static_cast<float>(FIELD(owner,float,0x6ac)-static_cast<double>(FIELD(target,signed char,0x104))*F(0x370));else FIELD(owner,float,0x6ac)=static_cast<float>(static_cast<double>(FIELD(target,signed char,0x104))*F(0x370)+FIELD(owner,float,0x6ac));
        }
    }
    if(S(0x13e)==5) {F(0x12c)+=40.0;F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==7) {if(C(0x184)<=0 || I(0x144)>=15) {next_sequence_block();return;}if(emit_repeated(0,0,3)) RETIRE();}
    if(S(0x13e)==8) {F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);F(0xf4)=0.0f;F(0xf8)=0.0f;B(0x184)=0;if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;}
    MOVE();FINISH();


}
case 821: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0x12c)-=2.0;if(emit_repeated(1,4,4)) RETIRE();advance_six(0);advance_phase(1);
        if(I(0x144)%5==0) {float packet[3]={RF(360),0.0f,2.0f};double centerY=F(0xf0)+100.0;double centerX=F(0xec)+100.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(centerY-static_cast<double>(RF(200))),B(0x104),1,packet,3);}
        F(0xf8)-=static_cast<double>(0.8f);double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
        WAVE(24);float packet[3];int count=7;
        do {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);}while(--count);
        do {packet[0]=static_cast<float>(static_cast<double>(count)+30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=4.0f;if(packet[0]<0.0f || packet[0]>180.0f) spawn_unparented(821,F(0xec),F(0xf0),B(0x104),-1,packet,3);else spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);count+=60;}while(count<360);
        packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);
        packet[0]=0.0f;packet[1]=0.0f;packet[2]=5.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-50.0f;packet[1]=12.0f;packet[2]=6.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-70.0f;packet[1]=13.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-110.0f;packet[1]=13.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-130.0f;packet[1]=12.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        if(FIELD(OWNER,signed char,0x60d)>=4) {packet[0]=-150.0f;packet[1]=11.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[0]=-30.0f;packet[1]=11.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();
    }
    case 1:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(I(0x144)>=3) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 2:case 7:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.1f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 3:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.2f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 4: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.05f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=0) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    }
    case 5:case 8:F(0x11c)+=F(0x370);F(0x370)-=static_cast<double>(0.2f);if(F(0x370)<=0.05f) F(0x370)=0.05f;F(0x120)=F(0x374)+F(0x120);F(0x374)-=static_cast<double>(0.1f);if(F(0x374)<=-0.025f) F(0x374)=-0.025f;if(I(0x144)>=10) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 6:
        if(emit_repeated(0,0,4)) RETIRE();advance_six(3);advance_phase(1);
        if(C(0x184)>0) {
            if(I(0x144)%10==0) {float packet[3]={RF(360),0.0f,7.0f};double centerY=F(0xf0)+20.0;double centerX=F(0xec)+20.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(40))),static_cast<float>(centerY-static_cast<double>(RF(40))),B(0x104),1,packet,3);}
            F(0xf8)-=0.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
            WAVE(24);float packet[3]={0.0f,0.0f,8.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(int count=4;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }else {
            float packet[3];for(int count=4;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(821,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }
    }FINISH();


}
case 848: {

    switch(S(0x13e)) {
    case 0: {
        if(S(0x140)<=15) position_relative_to_owner(0,0);void *owner=OWNER;if((FIELD(owner,short,0x13c)==302 && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)<8) || S(0x140)>=16) break;select_frame(16);return;
    }
    case 1:F(0x11c)*=static_cast<double>(0.95f);F(0x120)=F(0x11c);if(I(0x144)>=12) {if(B(0x113)<12) RETIRE();B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}break;
    case 2:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(I(0x144)>=12) {if(B(0x113)<12) RETIRE();B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}break;
    case 3: {
        if(S(0x140)<=15) position_relative_to_owner(0,0);void *owner=OWNER;if((FIELD(owner,short,0x13c)==302 && FIELD(owner,short,0x13e)==1) || S(0x140)>=16) break;select_frame(16);return;
    }
    case 4:F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x113)<15) RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x110)-=15;}break;
    case 5:position_relative_to_owner(0,0);{short action=FIELD(OWNER,short,0x13c);if(action!=321 && action!=322) RETIRE();}break;
    case 6:position_relative_to_owner(0,0);{short action=FIELD(OWNER,short,0x13c);if(action!=304 && action!=418) RETIRE();}break;
    }
    if(advance_frame()) RETIRE();if(S(0x140)==0 && S(0x142)==0 && I(0x144)==0) --I(0x330);return;


}
case 850: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(S(0x364)==0) {
            void *owner=entryOwner;
            if(FIELD(owner,short,0x13c)==600) {
                if(FIELD(owner,short,0x13e)==2) {
                    if(FIELD(owner,short,0x140)==0) {F(0xec)=static_cast<float>(static_cast<double>(44*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+127.0);}
                    if(FIELD(owner,short,0x140)==1) {F(0xec)=static_cast<float>(static_cast<double>(47*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+99.0);}
                    if(FIELD(owner,short,0x140)==2) {F(0xec)=static_cast<float>(static_cast<double>(20*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+60.0);}
                    if(FIELD(owner,short,0x140)==3) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(28*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+56.0);}
                    if(FIELD(owner,short,0x140)==4) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(54*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}
                    if(FIELD(owner,short,0x140)==5) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(43*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+141.0);}
                    if(FIELD(owner,short,0x140)==6) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(7*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+155.0);}
                    if(I(0x144)%3==0 && FIELD(owner,short,0x730)<=50) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(20))+80.0);packet[2]=1.0f;spawn_parented(850,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*960.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*960.0+F(0xf0)),B(0x104),-1,packet,3);}
                }
                owner=OWNER;if(FIELD(owner,short,0x13e)==3) {
                    if(FIELD(owner,short,0x140)==0) {F(0xec)=static_cast<float>(static_cast<double>(41*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+127.0);}
                    if(FIELD(owner,short,0x140)==1) {F(0xec)=static_cast<float>(static_cast<double>(80*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+89.0);}
                    if(FIELD(owner,short,0x140)==2) {
                        S(0x344)=0;S(0x364)=1;WAVE(51);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));float angle=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)-static_cast<double>(F(0xf0))+100.0),dx);float *parameters=PARAM;parameters[0]=angle;if(angle>=85.0f) parameters[0]=85.0f;if(parameters[0]<=-35.0f) parameters[0]=-35.0f;parameters[1]=50.0f;select_frame(1);
                    }
                }
            }else S(0x364)=2;
        }
        if(S(0x364)==1) {MOTION->set_components(PARAM[0],PARAM[1]);MOVE();double currentY=F(0xf0);if(stage_surface_height()>=currentY || C(0x184)<=0) {reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(10.0f);WAVE(52);RETIRE();}}
        if(S(0x364)==2) RETIRE();FINISH();
    }
    if(S(0x13e)==1) {
        if(RELATED) {
            if(S(0x364)==0) {
                double dySquared=square_float_value(F(0xf0)-FIELD(RELATED,float,0xf0));
                if(square_float_value(F(0xec)-FIELD(RELATED,float,0xec))+dySquared<=5625.0) {void *related=RELATED;F(0x370)=F(0xec)-FIELD(related,float,0xec);F(0x374)=F(0xf0)-FIELD(related,float,0xf0);S(0x364)=1;}
                if(I(0x144)>=60) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}MOVE();
            }
            if(S(0x364)==1) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec)+F(0x370);F(0xf0)=FIELD(related,float,0xf0)+F(0x374);}
        }else {
            S(0x344)=0;if(S(0x366)==0) {S(0x366)=1;float speed=static_cast<float>(RF(200)*static_cast<double>(0.1f));F(0xf4)=static_cast<float>(speed-10.0);F(0xf8)=static_cast<float>(RF(60)*static_cast<double>(0.1f)+4.0);}F(0xf8)-=static_cast<double>(0.2f);if(B(0x113)<5) RETIRE();B(0x113)-=5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);
        }
    }FINISH();


}
case 851: {

    if(I(0x180)==5) RETIRE();if(S(0x13e)==0) {if(FIELD(entryOwner,short,0x13c)!=601 || FIELD(entryOwner,short,0x13e)!=3 || FIELD(entryOwner,short,0x140)!=2) RETIRE();if(B(0x113)>245) {B(0x113)=255;B(0x111)=255;B(0x112)=255;}else {B(0x113)+=10;B(0x111)+=10;B(0x112)+=10;}position_relative_to_owner(0,0);}FINISH();


}
case 852: {

    if(I(0x180)==5) RETIRE();if(S(0x13e)==0) {F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;}FINISH();


}
case 853: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(S(0x364)==0) {
            FIELD(TARGET,short,0x4a8)=2;FIELD(TARGET,short,0x4ac)=2;
            void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==603) {
                if(FIELD(owner,short,0x13e)==4) {
                    if(FIELD(owner,short,0x140)==0) {F(0xec)=static_cast<float>(static_cast<double>(95*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+175.0);}
                    if(FIELD(owner,short,0x140)==1) {F(0xec)=static_cast<float>(static_cast<double>(110*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+75.0);}
                    if(FIELD(owner,short,0x140)==2) {F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+10.0);}
                    if(FIELD(owner,short,0x140)==3) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(10*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)-30.0);}
                    if(FIELD(owner,short,0x140)==4) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(115*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+80.0);}
                    if(FIELD(owner,short,0x140)==5) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(90*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+165.0);}
                    if(FIELD(owner,short,0x140)==6) {F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(15*C(0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+210.0);}
                    if(I(0x144)%3==0 && FIELD(owner,short,0x730)<=100) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(20))+80.0);packet[2]=1.0f;spawn_parented(853,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*960.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*960.0+F(0xf0)),B(0x104),1,packet,3);}
                }
                owner=OWNER;if(FIELD(owner,short,0x13e)==5) {
                    if(FIELD(owner,short,0x140)==0) {F(0xec)=static_cast<float>(static_cast<double>(41*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+127.0);}
                    if(FIELD(owner,short,0x140)==1) {F(0xec)=static_cast<float>(static_cast<double>(80*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+89.0);}
                    if(FIELD(owner,short,0x140)==2) {
                        S(0x364)=1;WAVE(51);
                    }
                }
            }else S(0x364)=2;
        }
        if(S(0x364)==1) {FIELD(TARGET,short,0x4a8)=2;FIELD(TARGET,short,0x4ac)=2;void *target=TARGET;F(0xec)=FIELD(target,float,0xec);F(0xf0)=static_cast<float>(FIELD(target,float,0xf0)+100.0);
            if(FIELD(target,short,0x13c)!=88) {forward_hit_quantity((*entryOwnerMode!=1 || FIELD(OWNER,short,0x4b2)!=0)?5000:6250,700,1,1);reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(10.0f);WAVE(52);RETIRE();}
        }
        if(S(0x364)==2) RETIRE();FINISH();
    }
    if(S(0x13e)==1) {
        if(RELATED) {
            if(S(0x364)==0) {
                double dySquared=square_float_value(F(0xf0)-FIELD(RELATED,float,0xf0));
                if(square_float_value(F(0xec)-FIELD(RELATED,float,0xec))+dySquared<=10000.0) {void *related=RELATED;F(0x370)=F(0xec)-FIELD(related,float,0xec);F(0x374)=F(0xf0)-FIELD(related,float,0xf0);S(0x364)=1;}
                if(I(0x144)>=60) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}MOVE();
            }
            if(S(0x364)==1) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec)+F(0x370);F(0xf0)=FIELD(related,float,0xf0)+F(0x374);}
        }else {
            S(0x344)=0;if(S(0x366)==0) {S(0x366)=1;float speed=static_cast<float>(RF(200)*static_cast<double>(0.1f));F(0xf4)=static_cast<float>(speed-10.0);F(0xf8)=static_cast<float>(RF(60)*static_cast<double>(0.1f)+4.0);}F(0xf8)-=static_cast<double>(0.2f);if(B(0x113)<5) RETIRE();B(0x113)-=5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);
        }
    }FINISH();


}
case 854: {

    if(I(0x180)==5) RETIRE();if(S(0x13e)==0) {if(FIELD(entryOwner,short,0x13c)!=604 || FIELD(entryOwner,short,0x13e)!=3 || FIELD(entryOwner,short,0x140)!=2) RETIRE();if(B(0x113)>245) B(0x113)=255;else B(0x113)+=10;position_relative_to_owner(0,0);}else if(S(0x13e)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}FINISH();


}
case 855: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:F(0x11c)+=static_cast<double>(0.6f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;break;
    case 1:
        F(0xf8)-=0.5;F(0x12c)=F(0x370)+F(0x12c);if(F(0xf8)<0.0f) {double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(stage_surface_height()>=nextY) F(0xf8)*=-0.75;}if(I(0x144)>=S(0x364)) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 2: {
        float *parameters=PARAM;parameters[1]*=static_cast<double>(0.95f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<4) RETIRE();B(0x113)-=4;F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.9f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));break;
    }
    case 3:
        if(S(0x142)==0) {
            if(C(0x184)<=0) {I(0x180)=0;B(0x184)=1;}float packet[3]={0.0f,0.0f,4.0f};spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*60.0-30.0);packet[1]=30.0f;packet[2]=2.0f;S(0x364)=(packet[0]<0.0f || packet[0]>180.0f)?-1:1;spawn_unparented(855,F(0xec),F(0xf0),B(0x104),B(0x364),packet,3);}
            for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))-120.0);packet[1]=static_cast<float>(static_cast<double>(RF(10))+10.0);packet[2]=1.0f;spawn_unparented(855,static_cast<float>(static_cast<double>(RF(300))+F(0xec)-150.0),F(0xf0),B(0x104),B(0x364),packet,3);}
        }
        if(F(0xec)>1480.0f || F(0xec)<-200.0) RETIRE();{double currentY=F(0xf0);if(stage_surface_height()!=currentY) RETIRE();}MOVE();break;
    case 4:F(0x11c)+=static_cast<double>(0.025f);F(0x120)*=static_cast<double>(0.99f);if(B(0x113)<6) RETIRE();B(0x113)-=6;break;
    case 5:
        MOTION->set_components(PARAM[0],PARAM[1]);if(FIELD(OWNER,short,0x174)<=0) RETIRE();if(I(0x144)%5==0) {float packet[4]={0.0f,0.0f,6.0f,0.0f};spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=7.0f;spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,4);}if(PARAM[3]<=static_cast<double>(I(0x144))) RETIRE();MOVE();break;
    case 6:F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;break;
    case 7:F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;break;
    case 8:PARAM[1]*=static_cast<double>(0.95f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;MOTION->set_components(PARAM[0],PARAM[1]);break;
    }FINISH();


}
case 856: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:advance_six(0);F(0x11c)+=static_cast<double>(0.3f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 1:
        advance_phase(0);turn_heading(0.0f,360.0f,100.0f);MOTION->set_components(PARAM[0],PARAM[1]);if(I(0x144)>=300) RETIRE();
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);float speed=static_cast<float>(RF(60)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+0.5);packet[2]=2.0f;F(0x370)=static_cast<float>(static_cast<double>(RF(50))+25.0);spawn_unparented(856,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*F(0x370)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*F(0x370)+F(0xf0)),B(0x104),1,packet,3);}MOVE();break;
    case 2:
        MOTION->set_components(PARAM[0],PARAM[1]);{float *parameters=PARAM;parameters[1]-=static_cast<double>(0.1f);if(parameters[1]<=0.0f) parameters[1]=0.0f;}
        if(S(0x364)==0) {if(B(0x113)>126) {B(0x113)=128;S(0x364)=1;}else B(0x113)+=2;}
        if(S(0x364)==1) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}MOVE();break;
    case 3: {
        float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<10) RETIRE();B(0x113)-=10;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)*0.25+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);break;
    }
    }FINISH();


}
case 857: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0x12c)-=2.0;advance_six(0);advance_phase(5);
        if(I(0x144)%5==0) {float packet[3]={RF(360),0.0f,2.0f};double centerY=F(0xf0)+100.0;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(centerY-static_cast<double>(RF(200))),B(0x104),1,packet,3);}
        F(0xf8)-=static_cast<double>(0.8f);double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
        WAVE(24);float packet[3];int count=7;
        do {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);}while(--count);
        do {packet[0]=static_cast<float>(static_cast<double>(count)+30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=4.0f;if(packet[0]<0.0f || packet[0]>180.0f) spawn_unparented(857,F(0xec),F(0xf0),B(0x104),-1,packet,3);else spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);count+=60;}while(count<360);
        packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);
        packet[0]=0.0f;packet[1]=0.0f;packet[2]=5.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[2]=9.0f;packet[0]=-80.0f;packet[1]=22.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-100.0f;packet[1]=22.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-60.0f;packet[1]=22.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-120.0f;packet[1]=22.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
    }
    case 1:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(I(0x144)>=3) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 2:case 7:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.1f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 3:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.2f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 4: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.05f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=0) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    }
    case 5:case 8:case 10:F(0x11c)+=F(0x370);F(0x370)-=static_cast<double>(0.2f);if(F(0x370)<=0.05f) F(0x370)=0.05f;F(0x120)=F(0x374)+F(0x120);F(0x374)-=static_cast<double>(0.1f);if(F(0x374)<=-0.025f) F(0x374)=-0.025f;if(I(0x144)>=10) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 6:
        advance_six(3);advance_phase(1);
        if(C(0x184)>0) {
            if(I(0x144)%10==0) {float packet[3]={RF(360),0.0f,7.0f};double centerY=F(0xf0)+20.0;double centerX=F(0xec)+20.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(40))),static_cast<float>(centerY-static_cast<double>(RF(40))),B(0x104),1,packet,3);}
            F(0xf8)-=0.25;double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
            WAVE(24);float packet[3]={0.0f,0.0f,8.0f};spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(int count=4;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }else {
            float packet[3];for(int count=4;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }
    case 9: {
        F(0x12c)-=2.0;advance_six(0);advance_phase(5);
        if(I(0x144)%5==0) {float packet[3]={RF(360),0.0f,2.0f};double centerY=F(0xf0)+100.0;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(centerY-static_cast<double>(RF(200))),B(0x104),1,packet,3);}
        F(0xf8)-=0.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
        WAVE(24);float packet[3];int count=7;
        do {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);}while(--count);
        do {packet[0]=static_cast<float>(static_cast<double>(count)+30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=4.0f;if(packet[0]<0.0f || packet[0]>180.0f) spawn_unparented(857,F(0xec),F(0xf0),B(0x104),-1,packet,3);else spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);count+=60;}while(count<360);
        packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(857,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);
        packet[0]=0.0f;packet[1]=0.0f;packet[2]=10.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-70.0f;packet[1]=10.0f;packet[2]=6.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-80.0f;packet[1]=11.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-100.0f;packet[1]=11.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-110.0f;packet[1]=10.0f;spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
    }
    }FINISH();


}
case 858: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.98f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));break;}
    case 1:F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(!(F(0x11c)>=0.5f)) {if(B(0x113)<50) RETIRE();B(0x113)-=50;B(0x111)-=50;B(0x110)-=50;}break;
    case 2:F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(!(F(0x11c)<=2.0f)) {if(B(0x113)<20) RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x110)-=20;}break;
    case 3:if(I(0x144)%3==0) {float packet[3]={RF(360),RF(5),0.0f};spawn_unparented(858,F(0xec),F(0xf0),B(0x104),1,packet,3);}if(I(0x144)>=36) RETIRE();{float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);MOTION->set_components(parameters[0],parameters[1]);}MOVE();break;
    case 4:if(B(0x113)<20) RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x110)-=20;MOTION->set_components(PARAM[0],PARAM[1]);MOVE();break;
    }FINISH();


}
case 900: {
 {
    unsigned short entryPhase=US(0x13e);switch(static_cast<short>(entryPhase)) {
    case 0:
        F(0x12c)+=40.0;if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=710 || FIELD(entryOwner,short,0x13e)>=2) S(0x364)=1;
        if(S(0x364)==0) {
            void *owner=OWNER;F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);
            if(F(0x11c)>=1.0f) {switch(g_match_identifier) {
                case 0: if(I(0x144)%20==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+20.0);packet[2]=2.0f;spawn_unparented(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}break;
                case 1: if(I(0x144)%10==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+20.0);packet[2]=2.0f;spawn_unparented(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}break;
                case 2: if(I(0x144)%4==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+20.0);packet[2]=2.0f;spawn_unparented(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}break;
                case 3: if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+20.0);packet[2]=2.0f;spawn_unparented(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}break;
            }}else {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=1;}}
            advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=15) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            F(0x370)+=static_cast<double>(0.05f);if(F(0x370)>8.0f) F(0x370)=8.0f;void *target=TARGET;owner=OWNER;
            if(FIELD(target,float,0xec)>=static_cast<double>(F(0xec))) FIELD(owner,float,0x6ac)=static_cast<float>(FIELD(owner,float,0x6ac)-static_cast<double>(FIELD(target,signed char,0x104))*F(0x370));else FIELD(owner,float,0x6ac)=static_cast<float>(static_cast<double>(FIELD(target,signed char,0x104))*F(0x370)+FIELD(owner,float,0x6ac));
        }else {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.0f)) RETIRE();}break;
    case 1:F(0xec)=FIELD(entryOwner,float,0xec);F(0xf0)=static_cast<float>(FIELD(entryOwner,float,0xf0)+100.0);F(0x12c)+=40.0;F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;break;
    case 2:
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && entryPhase==0) replace_secondary(990,15.0f,5,1,2);
        if(I(0x144)>=60 || I(0x180)!=0 || FIELD(OWNER,short,0x174)<=0) {next_sequence_block();F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
        {void *owner=OWNER;if(FIELD(owner,short,0x13c)==710 && FIELD(owner,short,0x13e)>=2) S(0x364)=1;}
        if(S(0x364)==1) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.98f);MOTION->set_components(parameters[0],parameters[1]);if(PARAM[1]<=0.1f) {next_sequence_block();F(0xf4)=0.0f;F(0xf8)=0.0f;return;}}break;
    case 3:F(0x11c)*=static_cast<double>(0.95f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    }MOVE();FINISH();
}


}
case 901: {
 {
    unsigned short entryPhase=US(0x13e);switch(static_cast<short>(entryPhase)) {
    case 0:
        F(0x12c)-=40.0;if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=711 || FIELD(entryOwner,short,0x13e)>=2) S(0x364)=1;
        if(S(0x364)==0) {
            void *owner=OWNER;F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);
            if(F(0x11c)>=1.0f) {switch(g_match_identifier) {
                case 0: if(I(0x144)%12==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(25))+15.0);packet[2]=2.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}break;
                case 1: if(I(0x144)%7==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(25))+15.0);packet[2]=2.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}break;
                case 2: if(I(0x144)%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(25))+15.0);packet[2]=2.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}break;
                case 3: {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(25))+15.0);packet[2]=2.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}break;
            }}else {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=1;}}
            advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=15) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
            if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            F(0x370)+=0.25;if(F(0x370)>5.0f) F(0x370)=5.0f;void *target=TARGET;owner=OWNER;
            if(FIELD(target,float,0xec)>=static_cast<double>(F(0xec))) FIELD(owner,float,0x6ac)=static_cast<float>(static_cast<double>(FIELD(target,signed char,0x104))*F(0x370)+FIELD(owner,float,0x6ac));else FIELD(owner,float,0x6ac)=static_cast<float>(FIELD(owner,float,0x6ac)-static_cast<double>(FIELD(target,signed char,0x104))*F(0x370));
        }else {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.0f)) RETIRE();}break;
    case 1:F(0xec)=FIELD(entryOwner,float,0xec);F(0xf0)=static_cast<float>(FIELD(entryOwner,float,0xf0)+100.0);F(0x12c)-=40.0;F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;break;
    case 2:
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && entryPhase==0) replace_secondary(990,15.0f,5,1,2);
        if(I(0x180)!=0 || FIELD(OWNER,short,0x174)<=0) {next_sequence_block();F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();break;
    case 3:F(0x11c)*=static_cast<double>(0.95f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    }MOVE();FINISH();
}


}
case 910: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0x12c)-=2.0;
        if(FIELD(entryOwner,short,0x174)<=0) {float packet[3];for(int count=5;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);}RETIRE();}
        advance_six(0);advance_phase(0);
        if(I(0x144)%10==0) {float packet[3]={RF(360),0.0f,2.0f};double centerY=F(0xf0)+100.0;double centerX=F(0xec)+100.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(centerY-static_cast<double>(RF(200))),B(0x104),1,packet,3);}
        F(0xf8)-=static_cast<double>(0.8f);double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
        WAVE(24);float packet[3];int count=4;
        do {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);}while(--count);
        do {packet[0]=static_cast<float>(static_cast<double>(count)+30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=4.0f;if(packet[0]<0.0f || packet[0]>180.0f) spawn_unparented(910,F(0xec),F(0xf0),B(0x104),-1,packet,3);else spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);count+=60;}while(count<180);
        packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+10.0);packet[2]=3.0f;double centerX=F(0xec)+100.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(200))),F(0xf0),B(0x104),1,packet,3);
        packet[0]=0.0f;packet[1]=0.0f;packet[2]=5.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
        if(g_match_identifier==1 || g_match_identifier==2 || g_match_identifier==3) {
        packet[0]=-50.0f;packet[1]=12.0f;packet[2]=6.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-70.0f;packet[1]=13.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-110.0f;packet[1]=13.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=-130.0f;packet[1]=12.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }RETIRE();
    }
    case 1:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(I(0x144)>=3) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 2:case 7:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.1f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 3:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.2f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=10) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 4: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.05f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=0) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    }
    case 5:case 8:F(0x11c)+=F(0x370);F(0x370)-=static_cast<double>(0.2f);if(F(0x370)<=0.05f) F(0x370)=0.05f;F(0x120)=F(0x374)+F(0x120);F(0x374)-=static_cast<double>(0.1f);if(F(0x374)<=-0.025f) F(0x374)=-0.025f;if(I(0x144)>=10) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 6:
        if(FIELD(entryOwner,short,0x174)>0) {
        advance_six(5);advance_phase(1);
        if(C(0x184)>0) {
            if(I(0x144)%10==0) {float packet[3]={RF(360),0.0f,7.0f};double centerY=F(0xf0)+20.0;double centerX=F(0xec)+20.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(40))),static_cast<float>(centerY-static_cast<double>(RF(40))),B(0x104),1,packet,3);}
            F(0xf8)-=0.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()<nextY || I(0x144)<2) {F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;}
            WAVE(24);float packet[3]={0.0f,0.0f,8.0f};spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(int count=3;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }else {
            float packet[3];for(int count=3;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }
        }else {
            float packet[3];for(int count=3;count!=0;--count) {packet[0]=-RF(180);packet[1]=static_cast<float>(static_cast<double>(RF(3))+5.0);packet[2]=3.0f;double centerY=F(0xf0)+10.0;double centerX=F(0xec)+10.0;spawn_unparented(910,static_cast<float>(centerX-static_cast<double>(RF(20))),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1,packet,3);}RETIRE();
        }
    case 9:
        if(FIELD(entryOwner,short,0x174)<=0 || F(0xec)<-100.0 || F(0xec)>1380.0f) RETIRE();MOTION->set_components(0.0f,PARAM[1]);
        if(I(0x144)%20==0) {float packet[3];switch(g_match_identifier) {
        case 0:packet[0]=-90.0f;packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+10.0);packet[2]=0.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);break;
        case 1:packet[0]=static_cast<float>(static_cast<double>(RF(6))-93.0);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+15.0);packet[2]=0.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);break;
        case 2:packet[0]=static_cast<float>(static_cast<double>(RF(10))-95.0);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+20.0);packet[2]=0.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);break;
        case 3:packet[0]=static_cast<float>(static_cast<double>(RF(10))-95.0);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+25.0);packet[2]=0.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);break;
        }WAVE(23);publish_battle_layout_scalar(3.0f);}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));break;
    }FINISH();


}
case 920: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {F(0x11c)+=static_cast<double>(0.6f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;}
    else if(S(0x13e)==2) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.95f);MOTION->set_components(parameters[0],parameters[1]);if(B(0x113)<4) RETIRE();B(0x113)-=4;F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.9f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));}FINISH();


}
case 921: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        switch(g_match_identifier) {case 1:turn_heading(0.0f,0.3f,100.0f);break;case 2:turn_heading(0.0f,0.6f,100.0f);break;case 3:turn_heading(0.0f,1.0f,100.0f);break;}
        if(FIELD(OWNER,short,0x174)<=0) RETIRE();if(I(0x144)%5==0) {float packet[4]={0.0f,0.0f,1.0f,0.0f};spawn_unparented(921,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=2.0f;spawn_unparented(921,F(0xec),F(0xf0),B(0x104),1,packet,4);}if(PARAM[3]<=static_cast<double>(I(0x144))) RETIRE();
    }
    if(S(0x13e)==1) {F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
    if(S(0x13e)==2) {F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;}
    if(S(0x13e)==3) {PARAM[1]*=static_cast<double>(0.95f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;MOTION->set_components(PARAM[0],PARAM[1]);}
    if(S(0x13e)==4) {advance_six(5);if(I(0x180)!=0) {next_sequence_block();F(0xf4)=0.0f;F(0xf8)=1.0f;}}
    if(S(0x13e)==5) {F(0x11c)*=static_cast<double>(0.92f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;}
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();


}
case 930: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]=static_cast<float>(static_cast<double>(0.95f)*parameters[1]);if(parameters[1]<1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=5) {if(B(0x113)<3) RETIRE();B(0x113)-=3;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 2: {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]=static_cast<float>(static_cast<double>(0.95f)*parameters[1]);if(parameters[1]<1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=5) {if(B(0x113)<3) RETIRE();B(0x113)-=3;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 1:
        if(S(0x364)==0) {if(B(0x113)>220) {B(0x113)=255;S(0x364)=1;}else B(0x113)+=35;}if(S(0x364)>=1) {if(B(0x113)<4) RETIRE();B(0x113)-=4;}
        F(0x11c)-=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.98f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);break;
    case 3:
        if(I(0x144)%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(7))+3.0);packet[2]=2.0f;spawn_unparented(930,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*(packet[1]*5.0)+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*(packet[1]*5.0)+F(0xf0)),B(0x104),1,packet,3);}
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.96f);if(I(0x144)>=45) RETIRE();MOVE();break;
    case 4:
        if(S(0x364)<=1 && FIELD(entryOwner,short,0x174)<=0) {F(0x11c)*=2.0;F(0x120)=static_cast<float>(2.0*F(0x120));S(0x364)=2;B(0x113)=255;B(0x184)=0;}
        if(S(0x364)==0) {F(0x11c)-=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(B(0x113)<252) B(0x113)+=3;else {B(0x113)=255;S(0x364)=1;B(0x184)=1;}}
        if(S(0x364)==1) {
            PARAM[1]=0.1f;turn_heading(0.0f,360.0f,100.0f);MOTION->set_components(PARAM[0],PARAM[1]);if(I(0x180)!=0) {F(0x11c)*=2.0;F(0x120)*=2.0;S(0x364)=2;B(0x184)=0;}
            unsigned short age=++US(0x366);switch(g_match_identifier) {
            case 0:if(age>=120) {S(0x364)=2;F(0x11c)*=2.0;F(0x120)=static_cast<float>(2.0*F(0x120));B(0x184)=0;}break;
            case 1:if(age>=180) {S(0x364)=2;F(0x11c)*=2.0;F(0x120)=static_cast<float>(2.0*F(0x120));B(0x184)=0;}break;
            case 2:if(age>=240) {S(0x364)=2;F(0x11c)*=2.0;F(0x120)=static_cast<float>(2.0*F(0x120));B(0x184)=0;}break;
            case 3:if(age>=300) {S(0x364)=2;F(0x11c)*=2.0;F(0x120)=static_cast<float>(2.0*F(0x120));B(0x184)=0;}break;
            }
        }
        if(S(0x364)==2) {F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}MOVE();break;
    }FINISH();


}
case 940: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1460.0 || F(0xf0)<-100.0) RETIRE();F(0x12c)+=40.0;
        if(S(0x364)!=0) {B(0x184)=0;if(B(0x113)<6) RETIRE();F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);B(0x113)-=6;B(0x111)-=5;B(0x110)-=5;break;}
        if(FIELD(entryOwner,short,0x174)<=0) {S(0x364)=1;return;}
        if(I(0x144)%4==0) {float packet[4]={0.0f,0.0f,5.0f,1.0f};spawn_unparented(940,static_cast<float>(static_cast<double>(RF(100))+F(0xec)-50.0),static_cast<float>(static_cast<double>(RF(100))+F(0xf0)-50.0),B(0x104),1,packet,4);}
        advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=10) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        double currentY=F(0xf0);
        if(stage_surface_height()<currentY && F(0xec)>=0.0f && F(0xec)<=1280.0f) break;
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,14.0f,90.0f};
        if(g_match_identifier==1) packet[3]=150.0f;
        spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=15.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=16.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*60.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(20))+10.0);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 1: {
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1460.0 || F(0xf0)<-100.0) RETIRE();F(0x12c)+=40.0;
        if(S(0x364)!=0) {B(0x184)=0;if(B(0x113)<6) RETIRE();F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);B(0x113)-=6;B(0x111)-=5;B(0x110)-=5;break;}
        if(FIELD(entryOwner,short,0x174)<=0) {S(0x364)=1;return;}
        if(I(0x144)%4==0) {float packet[4]={0.0f,0.0f,5.0f,1.0f};spawn_unparented(940,static_cast<float>(static_cast<double>(RF(200))+F(0xec)-100.0),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)-100.0),B(0x104),1,packet,4);}
        advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=10) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        double currentY=F(0xf0);
        if(stage_surface_height()<currentY && F(0xec)>=0.0f && F(0xec)<=1280.0f) break;
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,14.0f,180.0f};
        spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=15.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=16.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*60.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(20))+10.0);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 2: {
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1460.0 || F(0xf0)<-100.0) RETIRE();F(0x12c)+=40.0;
        if(S(0x364)!=0) {B(0x184)=0;if(B(0x113)<6) RETIRE();F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);B(0x113)-=6;B(0x111)-=5;B(0x110)-=5;break;}
        if(FIELD(entryOwner,short,0x174)<=0) {S(0x364)=1;return;}
        if(I(0x144)%4==0) {float packet[4]={0.0f,0.0f,5.0f,1.0f};spawn_unparented(940,static_cast<float>(static_cast<double>(RF(300))+F(0xec)-150.0),static_cast<float>(static_cast<double>(RF(300))+F(0xf0)-150.0),B(0x104),1,packet,4);}
        advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=10) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        double currentY=F(0xf0);
        if(!(stage_surface_height()>=currentY || F(0xec)<0.0f || F(0xec)>1280.0f)) break;
        reinterpret_cast<SuikaUpdateOwnerView*>(OWNER)->publish_battle_layout_scalar(4.0f);WAVE(12);float packet[4]={0.0f,0.0f,14.0f,210.0f};
        spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=15.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=16.0f;packet[3]=1.0f;spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);packet[2]=4.0f;
        for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*60.0-20.0);packet[1]=static_cast<float>(static_cast<double>(RF(20))+10.0);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,4);}RETIRE();
    }
    case 3:F(0x11c)+=static_cast<double>(0.4f);F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;break;
    case 4:PARAM[1]*=static_cast<double>(0.85f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;MOTION->set_components(PARAM[0],PARAM[1]);break;
    case 5:PARAM[1]*=static_cast<double>(0.85f);F(0x370)*=static_cast<double>(0.995f);F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;F(0xf8)-=static_cast<double>(0.1f);break;
    case 6: {
        float *parameters=PARAM;parameters[1]-=0.25;if(parameters[1]<=1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);
        if(!(PARAM[1]>6.0f)) {if(B(0x111)>=15) {B(0x111)-=15;B(0x110)-=15;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<15) RETIRE();B(0x113)-=15;}}break;
    }
    case 7: {
        if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=751) RETIRE();F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0xec)=static_cast<float>(FIELD(entryOwner,float,0xec)-static_cast<double>(10*FIELD(entryOwner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(entryOwner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+50.0);packet[2]=10.0f;spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(g_match_identifier!=0) {if(g_match_identifier==1 && I(0x144)%4==0) {float packet[3];for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(index*90.0+F(0x370));packet[1]=30.0f;packet[2]=17.0f;spawn_parented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}F(0x370)+=3.0;}}else if(I(0x144)%4==0) {float packet[3];for(float index=0.0f;index<3.0f;index+=1.0) {packet[0]=static_cast<float>(index*120.0+F(0x370));packet[1]=30.0f;packet[2]=17.0f;spawn_parented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}F(0x370)+=3.0;}
        if(I(0x144)%8==0) {float packet[3]={RF(360),15.0f,11.0f};spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        void *owner=OWNER;if(FIELD(owner,short,0x13e)!=2 || FIELD(owner,short,0x140)<1) break;
        float packet[3];packet[1]=7.0f;packet[2]=0.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 8: {
        if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=751) RETIRE();F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0xec)=static_cast<float>(FIELD(entryOwner,float,0xec)-static_cast<double>(10*FIELD(entryOwner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(entryOwner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(300))+200.0);packet[2]=10.0f;spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%4==0) {float packet[3];for(float index=0.0f;index<5.0f;index+=1.0) {packet[0]=static_cast<float>(index*72.0+F(0x370));packet[1]=30.0f;packet[2]=17.0f;spawn_parented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}F(0x370)+=3.0;}
        if(I(0x144)%8==0) {float packet[3]={RF(360),15.0f,11.0f};spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        void *owner=OWNER;if(FIELD(owner,short,0x13e)!=2 || FIELD(owner,short,0x140)<1) break;
        float packet[3];packet[1]=8.5f;packet[2]=1.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 9: {
        if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=751) RETIRE();F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);F(0xec)=static_cast<float>(FIELD(entryOwner,float,0xec)-static_cast<double>(10*FIELD(entryOwner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(entryOwner,float,0xf0)+250.0);
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+50.0);packet[2]=10.0f;spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%4==0) {float packet[3];for(float index=0.0f;index<6.0f;index+=1.0) {packet[0]=static_cast<float>(index*60.0+F(0x370));packet[1]=30.0f;packet[2]=17.0f;spawn_parented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(180.0-packet[0]))*(packet[1]*60.0)+F(0xf0)),B(0x104),1,packet,3);}F(0x370)+=3.0;}
        if(I(0x144)%8==0) {float packet[3]={RF(360),15.0f,11.0f};spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        void *owner=OWNER;if(FIELD(owner,short,0x13e)!=2 || FIELD(owner,short,0x140)<1) break;
        float packet[3];packet[1]=10.0f;packet[2]=2.0f;void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));packet[0]=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);spawn_unparented(940,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(17);RETIRE();
    }
    case 10: {
        if(!RELATED) RETIRE();float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);double x=lookup_orientation_cosine_quantized_abs(parameters[0]);parameters=PARAM;F(0xec)=static_cast<float>(x*parameters[1]+FIELD(RELATED,float,0xec));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])*PARAM[1]+FIELD(RELATED,float,0xf0));
        if(B(0x111)>=20) {B(0x111)-=20;B(0x110)-=20;}else {if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    }
    case 11: {
        if(!RELATED) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);void *related=RELATED;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)+=F(0xf8);F(0xec)=FIELD(related,float,0xec)+F(0x370);F(0xf0)=FIELD(related,float,0xf0)+F(0x374);F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.1f);
        if(B(0x111)>=30) {B(0x111)-=30;B(0x110)-=30;}else {if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    }
    case 12:F(0x11c)-=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x111)>=128) {B(0x111)+=128;B(0x110)+=128;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<80) RETIRE();B(0x113)-=80;}break;
    case 13:F(0x11c)+=0.5;F(0x120)=F(0x11c);if(B(0x111)>=30) {B(0x111)-=30;B(0x110)-=30;}else {B(0x111)=0;B(0x110)=0;if(B(0x113)<30) RETIRE();B(0x113)-=30;}break;
    case 14:
        if(FIELD(entryOwner,short,0x174)<=0) S(0x364)=1;
        if(S(0x364)==0) {
            if(F(0xf8)>0.0f) F(0xf8)=0.0f;F(0x11c)=static_cast<float>(F(0x370)+static_cast<double>(0.005f)+F(0x11c));F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.85f);
            publish_bounds_descriptor(static_cast<int>(-130.0*F(0x11c)),static_cast<int>(130.0*F(0x120)),static_cast<int>(F(0x11c)*130.0),static_cast<int>(F(0x120)*-130.0),0,0,0);advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;I(0x180)=0;B(0x184)=1;}if(PARAM[3]<=static_cast<double>(I(0x144))) S(0x364)=1;
        }else {B(0x184)=0;if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;}break;
    case 15:F(0x11c)+=0.75;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    case 16:
        if(S(0x364)!=0) {F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        else {F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.9f);if(B(0x113)<245) {B(0x113)=255;S(0x364)=1;}else B(0x113)+=10;}break;
    case 17:
        if(S(0x364)==0) {if(collision!=0 || FIELD(entryOwner,short,0x174)<=0 || !RELATED || I(0x144)>=55) {S(0x364)=1;F(0x11c)+=F(0x11c);F(0x120)=F(0x11c);F(0xf4)=0.0f;F(0xf8)=0.0f;B(0x184)=0;}}
        else {F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}break;
    case 18:
        F(0x12c)-=20.0;if(S(0x364)==0) {if(FIELD(entryOwner,short,0x174)<=0 || FIELD(entryOwner,short,0x13c)!=751) S(0x364)=2;F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>=1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);void *owner=OWNER;F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-static_cast<double>(10*FIELD(owner,signed char,0x104)));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+250.0);if(FIELD(owner,short,0x13e)==2 && FIELD(owner,short,0x140)>=1) S(0x364)=1;}
        if(S(0x364)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}if(S(0x364)==2) {F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<5) RETIRE();B(0x113)-=5;}break;
    }MOVE();FINISH();
}


}
case 980: {
update_ping_pong_motion();FINISH();


}
case 998: {

    F(0x12c)+=5.0;
    if(S(0x13e)==0) {
        void *owner=entryOwner;short action=FIELD(owner,short,0x13c);
        if(action>153 && action<158) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+60.0);}
        action=FIELD(owner,short,0x13c);if(action>149 && action<154) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+94.0);}
        if(FIELD(owner,short,0x13c)==158) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}
        action=FIELD(owner,short,0x13c);if(action<150 || action>158) {next_sequence_block();FIELD(OWNER,unsigned char,0x751)=0;}
    }
    if(S(0x13e)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}FINISH();


}
case 999: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]=static_cast<float>(static_cast<double>(0.95f)*parameters[1]);if(parameters[1]<1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=5) {if(B(0x113)<3) RETIRE();B(0x113)-=3;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);
    }
    if(S(0x13e)==1) {
        float *parameters=PARAM;F(0x12c)+=F(0x370);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);parameters[1]=static_cast<float>(static_cast<double>(0.95f)*parameters[1]);if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)=F(0x374)+F(0xf8);if(I(0x144)>=2) {if(B(0x113)<12) RETIRE();B(0x113)-=12;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);
    }
    FINISH();

}
default:advance_frame();return;
}
}
}
