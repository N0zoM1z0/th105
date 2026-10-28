// Complete manual JP1.06a AliceObject update hypothesis, 004fcab0.
#include "characters/AliceObjectUpdate.hpp"
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
#define MOTION reinterpret_cast<AliceUpdateMotionView*>(reinterpret_cast<unsigned char*>(this)+4)
#define WAVE(n) reinterpret_cast<AliceUpdateOwnerView*>(OWNER)->dispatch_character_wave_handle(n)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define TURN_TO_OWNER() do {B(0x33c)=255;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;}while(0)
#define RETIRE() do { --I(0x330); return; } while(0)
#define MOVE() do {F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}while(0)
#define FINISH() do {if(advance_frame()) --I(0x330);return;}while(0)
void AliceObjectUpdateView::update_action_state() {
switch(S(0x13c)) {
case 800: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)>6) {F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;}
    else {
        if(S(0x140)==0) {
            if(emit_repeated(0,0,4)) RETIRE();
            if(I(0x180)!=0) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(S(0x13e)+7)};spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);return;}
            if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);MOVE();
        }
        if(S(0x140)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    }FINISH();


}
case 801: {
 {
    short phase=S(0x13e);
    if(phase<=6) {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && phase<=5) select_sequence(6);
        void *owner=OWNER;action=FIELD(owner,short,0x13c);
        if(action<=399 || action>=410) {if(S(0x13e)<=4) {select_sequence(5);TURN_TO_OWNER();}}
        else if(((action==404 && FIELD(owner,short,0x13e)==8) || (action==405 && FIELD(owner,short,0x13e)==8) || (action==406 && FIELD(owner,short,0x13e)==8)) && S(0x13e)<=4) {select_sequence(5);TURN_TO_OWNER();}
        switch(S(0x13e)) {
        case 0:F(0x370)+=F(0xf4);F(0x374)+=F(0xf8);F(0xf4)*=0.75;F(0xf8)=static_cast<float>(0.75*F(0xf8));if(I(0x144)>=10) select_sequence(2);goto alice_801_owner_position;
        case 2:goto alice_801_owner_position;
        case 3:
            if(I(0x144)%3==0 && S(0x364)<=6) {
                WAVE(0);++S(0x364);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);
                if(PARAM[2]==1.0f) {if(F(0x378)<20.0f) F(0x378)=20.0f;if(F(0x378)>60.0f) F(0x378)=60.0f;}else {if(F(0x378)<-20.0f) F(0x378)=-20.0f;if(F(0x378)>20.0f) F(0x378)=20.0f;}
                float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+F(0x378)-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(S(0x364)%7);
                spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[2]=static_cast<float>(static_cast<double>(S(0x364)%7)+7.0);
                spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(0);
            }
            if(I(0x144)>=30) next_sequence_block();
alice_801_owner_position: {
                float *parameters=PARAM;double x=static_cast<double>(F(0x370))+parameters[0];double facing=C(0x104);void *owner=OWNER;F(0xec)=static_cast<float>(x*facing+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(static_cast<double>(parameters[1])+F(0x374)+FIELD(owner,float,0xf0));break;
            }
        case 5:if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
        case 6:
            if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
        }
    }
    phase=S(0x13e);
    if(phase>=7 && phase<=12) {
        short action=FIELD(OWNER,short,0x13c);if(((action>49 && action<150) || S(0x174)<=-500) && phase<=9) {select_sequence(6);return;}
        if(action!=402 && phase<=9) {select_sequence(5);TURN_TO_OWNER();}
        switch(S(0x13e)) {
        case 7:
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==7) {F(0xf4)=27.5f;F(0xf8)=0.0f;}if(I(0x144)>=4) {next_sequence_block();return;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));break;
        case 8:case 9:
            F(0xf4)-=4.0;if(F(0xf4)<4.0f) F(0xf4)=4.0f;
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==9) {float packet[3]={0.0f,0.0f,10.0f};spawn_parented(801,static_cast<float>(static_cast<double>(45*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);}
            if(S(0x13e)==9 && I(0x144)>=40) {select_sequence(5);TURN_TO_OWNER();}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));break;
        case 10:
            if(!RELATED) RETIRE();if(FIELD(RELATED,short,0x13e)==9) {if(I(0x180)!=0) {if(S(0x364)<7) ++S(0x364);else {S(0x364)=0;I(0x180)=0;}}void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(45*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);}
            else {B(0x184)=0;F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.01f)) RETIRE();}break;
        case 11: {
            F(0x12c)+=15.0;if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
            if(FIELD(related,signed char,0x184)>0) {F(0x120)+=static_cast<double>(0.3f);if(F(0x120)>3.0f) F(0x120)=3.0f;}else {F(0x120)*=static_cast<double>(0.65f);if(!(F(0x120)>0.01f)) RETIRE();}break;
        }
        case 12: {
            if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x120)=static_cast<float>(lookup_orientation_sine(3*I(0x144))*6.0);F(0x11c)=F(0x120);if(B(0x113)<9) RETIRE();B(0x113)-=9;break;
        }
        }
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {TURN_TO_OWNER();}return;
}


}
case 802: {
 {
    short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && S(0x13e)<=5) select_sequence(6);
    action=FIELD(OWNER,short,0x13c);if((action<=399 || action>=410) && S(0x13e)<=4) {select_sequence(5);TURN_TO_OWNER();}
    void *owner=OWNER;action=FIELD(owner,short,0x13c);if(((action==404 && FIELD(owner,short,0x13e)==8) || (action==406 && FIELD(owner,short,0x13e)==8)) && S(0x13e)<=4) {select_sequence(5);TURN_TO_OWNER();}
    switch(S(0x13e)) {
    case 0:F(0x370)+=F(0xf4);F(0x374)+=F(0xf8);F(0xf4)*=0.75;F(0xf8)=static_cast<float>(0.75*F(0xf8));if(I(0x144)>=10) select_sequence(1);goto alice_802_owner_position;
    case 1:if(FIELD(OWNER,short,0x13e)>=5) next_sequence_block();goto alice_802_owner_position;
    case 2:goto alice_802_owner_position;
    case 3:
        if(I(0x144)%3==0 && S(0x364)<=12) {
            WAVE(I(0x144)%3);++S(0x364);void *target=FIELD(OWNER,void*,0x170);float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(F(0x378)<-20.0f) F(0x378)=-20.0f;if(F(0x378)>20.0f) F(0x378)=20.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+F(0x378)-10.0);packet[1]=17.5f;packet[2]=static_cast<float>(S(0x364)%7);spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[2]=static_cast<float>(static_cast<double>(S(0x364)%7)+7.0);spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(0);
        }
        if(I(0x144)>=40) next_sequence_block();
alice_802_owner_position: {float *parameters=PARAM;double x=static_cast<double>(F(0x370))+parameters[0];double facing=C(0x104);void *owner=OWNER;F(0xec)=static_cast<float>(x*facing+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(static_cast<double>(parameters[1])+F(0x374)+FIELD(owner,float,0xf0));break;}
    case 5:if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
    case 6:
        if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {TURN_TO_OWNER();}return;
}


}
case 803: {
 {
    short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && S(0x13e)<=4) select_sequence(5);
    action=FIELD(OWNER,short,0x13c);if((action<=399 || action>=410) && S(0x13e)<=3) {select_sequence(4);TURN_TO_OWNER();}
    switch(S(0x13e)) {
    case 0:
        if(I(0x144)>60 || absolute_scalar_float(FIELD(TARGET,float,0xec)-F(0xec))<300.0f) ++S(0x366);
        if(S(0x366)>0) {F(0xf4)-=4.0;if(F(0xf4)<0.0f) {F(0xf4)=0.0f;next_sequence_block();return;}}MOVE();break;
    case 2:
        if(I(0x144)%3==0 && S(0x364)<=7) {
            WAVE(I(0x144)%3);++S(0x364);if(F(0x378)<-20.0f) F(0x378)=-20.0f;if(F(0x378)>20.0f) F(0x378)=20.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(60))-30.0);packet[1]=30.0f;packet[2]=static_cast<float>(S(0x364)%7);spawn_unparented(804,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[2]+=7.0;spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(0);
        }if(I(0x144)>=30) next_sequence_block();break;
    case 4:if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
    case 5:
        if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 6:if(update_flight_state(5)) return;break;
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) {TURN_TO_OWNER();}return;
}


}
case 804: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)>6) {float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<0.5f) parameters[1]=0.5f;MOTION->set_components(parameters[0],parameters[1]);MOVE();F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=S(0x364)) RETIRE();B(0x113)-=B(0x364);}
    else {
        if(S(0x140)==0) {
            float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<0.5f) parameters[1]=0.5f;if(emit_repeated(0,0,3)) RETIRE();if(I(0x144)>=30) {next_sequence_frame();return;}
            if(I(0x180)!=0) {next_sequence_frame();PARAM[1]=0.5f;for(int count=4;count!=0;--count) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(30))+10.0);packet[2]=static_cast<float>(S(0x13e)+7);spawn_unparented(804,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;}
            if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);MOVE();
        }
        if(S(0x140)==1) {float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<0.5f) parameters[1]=0.5f;MOTION->set_components(parameters[0],parameters[1]);MOVE();F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    }FINISH();


}
case 805: {
 {
    short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && S(0x13e)<=5) select_sequence(6);
    short phase=S(0x13e);if(phase!=6 && phase!=7 && (S(0x174)<-500 || FIELD(OWNER,short,0x174)<=0)) select_sequence(6);
    switch(S(0x13e)) {
    case 0: {
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<0.0f) {parameters[1]=0.0f;next_sequence_block();return;}MOVE();double currentY=F(0xf0);if(!(stage_surface_height()<=currentY)) F(0xf0)=stage_surface_height();break;
    }
    case 1: {
        if(I(0x144)>=60) {next_sequence_block();return;}void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==410 || action==411 || action==412 || action==414 || action==415 || action==416) && FIELD(owner,short,0x13e)==1) {next_sequence_block();S(0x366)=1;return;}break;
    }
    case 3:
        if(S(0x366)==1) {
            if(I(0x144)==0) {WAVE(1);++S(0x364);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(F(0x378)<-80.0f) F(0x378)=-80.0f;if(F(0x378)>80.0f) F(0x378)=80.0f;float packet[3]={F(0x378),0.0f,0.0f};spawn_parented(807,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);}
            if(I(0x144)>=90) next_sequence_block();
        }else {
            if(I(0x144)%3==0 && S(0x364)<=7) {WAVE(0);++S(0x364);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(F(0x378)<-80.0f) F(0x378)=-80.0f;if(F(0x378)>80.0f) F(0x378)=80.0f;
                float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+F(0x378)-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(S(0x364)%7);spawn_unparented(806,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[2]=static_cast<float>(static_cast<double>(S(0x364)%7)+7.0);spawn_unparented(806,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);
            }if(I(0x144)>=30) next_sequence_block();
        }break;
    case 5:if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
    case 6:
        if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 7: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)==609 && FIELD(owner,short,0x13e)==1 && RELATED) {void *related=RELATED;short action=FIELD(related,short,0x13c);if((action==805 && FIELD(related,short,0x13e)==8) || action==859) {set_action(859);select_sequence(4);B(0x184)=1;S(0x364)=0;return;}}
        if(update_flight_state(6)) return;break;
    }
    case 8: {
        void *owner=OWNER;if(FIELD(owner,short,0x174)<=0 || FIELD(TARGET,short,0x174)<=0) {--FIELD(owner,short,0x7a6);FIELD(OWNER,unsigned char,S(0x388)+0x7d1)=0;select_sequence(6);return;}
        int index=S(0x388);if(FIELD(owner,unsigned char,index+0x7d1)!=0) {next_sequence_block();FIELD(OWNER,unsigned char,S(0x388)+0x7d1)=0;return;}
        FIELD(owner,float,4*index+0x7b0)=F(0xec);FIELD(owner,float,4*S(0x388)+0x7c0)=F(0xf0);short action=FIELD(owner,short,0x13c);
        if(action==560 && FIELD(owner,short,0x13e)==1) {--FIELD(owner,short,0x7a6);set_action(825);select_sequence(1);I(0x144)=0;return;}
        if(action==609 && FIELD(owner,short,0x13e)==1) {--FIELD(owner,short,0x7a6);set_action(859);select_sequence(1);S(0x364)=0;B(0x184)=1;I(0x144)=0;return;}break;
    }
    case 10:if(I(0x144)>=60) {select_sequence(5);return;}break;
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {
        void *owner=OWNER;unsigned char level=FIELD(owner,unsigned char,0x607);int maximum=1;if(level==2 || FIELD(owner,unsigned char,0x60f)==2) maximum=2;if(level==3 || FIELD(owner,unsigned char,0x60f)==3) maximum=2;if(level==4 || FIELD(owner,unsigned char,0x60f)==4) maximum=3;
        short index=FIELD(owner,short,0x7a6);if(index<=maximum) {S(0x388)=index;++FIELD(OWNER,short,0x7a6);owner=OWNER;FIELD(owner,float,4*S(0x388)+0x7b0)=F(0xec);FIELD(owner,float,4*S(0x388)+0x7c0)=F(0xf0);select_sequence(8);}
    }return;
}


}
case 806: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)<=6) {
        if(S(0x140)==0) {if(emit_repeated(0,0,4)) RETIRE();if(I(0x180)!=0 || I(0x144)>60) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(S(0x13e)+7)};spawn_unparented(806,F(0xec),F(0xf0),B(0x104),1,packet,3);return;}
            if(!(F(0xec)<=1380.0f && F(0xec)>=-100.0f && F(0xf0)<=1000.0f && F(0xf0)>=-160.0f)) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}
        if(S(0x140)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}
    }else {F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;}FINISH();


}
case 807: {
 {
    if(I(0x180)==5) RETIRE();short action=FIELD(OWNER,short,0x13c);
    if(action>49 && action<150 && S(0x140)<=1) {for(float index=0.0f;index<12.0f;index+=1.0) emit_effect(201,static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x12c))*(index*130.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x12c))*130.0+F(0xf0)),B(0x104),1);RETIRE();}
    short frame=S(0x140);if(frame<=1 && (!RELATED || FIELD(RELATED,short,0x13e)==6)) {select_frame(2);return;}
    if(frame==0 && I(0x144)>=20) {F(0x120)+=static_cast<double>(0.15f);if(F(0x120)>=2.0f) {B(0x184)=4;F(0x120)=2.0f;next_sequence_frame();}}
    if(S(0x140)==1) {advance_six(0);if(I(0x180)!=0 && ++S(0x364)>=7) {S(0x364)=0;I(0x180)=0;}}
    if(S(0x140)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.9f);if(S(0x142)>=60) RETIRE();}FINISH();
}


}
case 810: {

    if(S(0x13e)<=2 && (emit_repeated(0,1,3) || S(0x174)<=-750)) select_sequence(3);
    if(S(0x13e)==0) {MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[0]-=2.0;parameters[1]-=1.0;if(parameters[1]<0.0f) {parameters[1]=0.0f;next_sequence_block();return;}MOVE();if(F(0xf0)<0.0f) F(0xf0)=0.0f;}
    if(S(0x13e)==1) {
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);}if(I(0x144)%15==0) WAVE(4);advance_six(0);if(I(0x178)>0) {select_sequence(3);return;}
        if(I(0x180)!=0 && ++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)>=10*(FIELD(OWNER,signed char,0x604)+8) || C(0x184)<=0) {next_sequence_block();B(0x33c)=255;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}
    }
    if(S(0x13e)==2) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==3) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==4 && update_flight_state(3)) return;
    if(S(0x13e)==5) {
        F(0x12c)+=25.0;if(!RELATED) RETIRE();
        if(FIELD(RELATED,short,0x13e)==1) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>3.0f) F(0x11c)=2.5f;F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}
        else {if(B(0x113)<20) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;}
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) {TURN_TO_OWNER();}return;


}
case 811: {

    if(S(0x13e)==0) {
        if(emit_repeated(0,1,3) || S(0x174)<=-500) select_sequence(1);
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,3.0f};spawn_parented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);}advance_six(0);
        if(S(0x364)==0) {float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.0f) {parameters[1]=0.0f;S(0x364)=1;}MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}
        if(S(0x364)==1 && ++S(0x366)>=30) {if(FIELD(OWNER,signed char,0x608)>=3) {B(0x184)=1;I(0x180)=0;}S(0x364)=2;}
        if(S(0x364)==2) {
            void *owner=OWNER;float *parameters=PARAM;float dx=FIELD(owner,float,0xec)-F(0xec);parameters[0]=-atan2_degrees(static_cast<float>(FIELD(owner,float,0xf0)+100.0-F(0xf0)),dx);parameters[1]+=0.5;if(F(0x370)>20.0f) F(0x370)=20.0f;MOTION->set_components(parameters[0],parameters[1]);owner=OWNER;F(0xec)=F(0xf4)+F(0xec);float nextY=F(0xf8)+F(0xf0);F(0xf0)=nextY;if(absolute_scalar_float(FIELD(owner,float,0xec)-F(0xec))<20.0f && absolute_scalar_float(static_cast<float>(FIELD(owner,float,0xf0)+100.0-nextY))<20.0f) RETIRE();
        }
    }
    if(S(0x13e)==1) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==2 && update_flight_state(1)) return;
    if(S(0x13e)==3) {if(!RELATED) RETIRE();void *related=RELATED;if(FIELD(related,short,0x13e)==0) {F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>2.5f) F(0x11c)=2.0f;F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}else {if(B(0x113)<20) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;}F(0x12c)+=25.0;}FINISH();


}
case 815: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,1,4)) RETIRE();double nextY=static_cast<double>(F(0xf0))+F(0xf8);
        if(stage_surface_height()>=nextY || S(0x174)<0) {publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf0)=stage_surface_height();F(0xf8)=-F(0xf8);F(0xf4)*=static_cast<double>(0.2f);return;}
        if(!(F(0xec)<=1380.0f && F(0xec)>=-100.0f && F(0xf0)<=1000.0f && F(0xf0)>=-160.0f)) RETIRE();F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 1:F(0x12c)+=15.0;if(B(0x113)<=5) RETIRE();B(0x113)-=5;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 2:advance_six(0);F(0x11c)-=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    case 3:F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)<=20) {B(0x111)-=20;B(0x110)-=20;}else {if(B(0x113)<=20) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=20;}}break;
    case 4:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<30) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=30;B(0x110)-=30;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}break;
    }FINISH();


}
case 816: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0x12c)+=15.0;if(F(0x12c)>=360.0f) F(0x12c)=360.0f;if(emit_repeated(0,1,4)) RETIRE();
        if(F(0xf8)<0.0f) {
            double dySquared=square_float_value(static_cast<float>(FIELD(TARGET,float,0xf0)+100.0-F(0xf0)));
            if(square_float_value(FIELD(TARGET,float,0xec)-F(0xec))+dySquared<=2500.0) {publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf8)=static_cast<float>(-F(0xf8)*0.25);F(0xf4)*=static_cast<double>(0.2f);return;}
        }
        double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(stage_surface_height()>=nextY) {F(0xf0)=stage_surface_height();publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf8)=static_cast<float>(-F(0xf8)*0.25);F(0xf4)*=static_cast<double>(0.2f);return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xf8)-=1.0;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 1:F(0x12c)+=15.0;if(B(0x113)<=5) RETIRE();B(0x113)-=5;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 2:advance_six(0);F(0x11c)-=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    case 3:F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)<=20) {B(0x111)-=20;B(0x110)-=20;}else {if(B(0x113)<=20) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=20;}}break;
    case 4:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<30) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=30;B(0x110)-=30;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}break;
    case 5:if(I(0x144)%2==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,F(0xec),static_cast<float>(static_cast<double>(50*I(0x144))+F(0xf0)),B(0x104),1,packet,3);}if(I(0x144)==4) RETIRE();break;
    }FINISH();


}
case 817: {

    float groundImpactA[3],groundImpactB[3];const void *groundImpact;
    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==530 || action==531) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {select_sequence(6);F(0xf4)=0.0f;F(0xf8)=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(stage_surface_height()>=nextY) {F(0xf4)=0.0f;F(0xf8)=0.0f;next_sequence_block();F(0xf0)=stage_surface_height();return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 9: {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==530 || action==531) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {select_sequence(6);F(0xf4)=0.0f;F(0xf8)=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(stage_surface_height()>=nextY) {F(0xf4)=0.0f;F(0xf8)=0.0f;next_sequence_block();F(0xf0)=stage_surface_height();return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 1: {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==530 || action==531) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {select_sequence(6);F(0xf4)=0.0f;F(0xf8)=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();F(0xf4)=2.0f;F(0xf8)=0.0f;double currentY=F(0xf0);if(stage_surface_height()<currentY) {select_sequence(0);return;}
        if(FIELD(OWNER,signed char,0x60d)>=2 && S(0x364)==0) {void *target=TARGET;double dx=(FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104);if(dx<=200.0 && dx>=0.0 && F(0xf0)<static_cast<double>(FIELD(target,float,0xf0))) {
            S(0x364)=1;select_sequence(7);owner=OWNER;F(0xf4)=4.0f;F(0xf8)=static_cast<float>((static_cast<double>(FIELD(owner,signed char,0x60d))-2.0)*4.0+7.0);return;
        }}
        if((square_float_value(F(0xec)-FIELD(TARGET,float,0xec))<=2500.0 && square_float_value(F(0xf0)-FIELD(TARGET,float,0xf0))<=10000.0) || stage_surface_height()>static_cast<double>(F(0xf0)) || S(0x174)<0) {
            publish_battle_layout_scalar(10.0f);select_sequence(6);B(0x135)=0;groundImpactA[0]=0.0f;groundImpactA[1]=0.0f;groundImpactA[2]=2.0f;groundImpact=groundImpactA;goto alice_817_ground_impact;
        }
if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 10: {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==530 || action==531) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {select_sequence(6);F(0xf4)=0.0f;F(0xf8)=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();F(0xf4)=static_cast<float>(FIELD(OWNER,signed char,0x60d)+3.0);F(0xf8)=0.0f;double currentY=F(0xf0);if(stage_surface_height()<currentY) {select_sequence(0);return;}
        if(FIELD(OWNER,signed char,0x60d)>=2) {void *target=TARGET;double dx=(FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104);if(dx<=200.0 && dx>=0.0 && F(0xf0)>=static_cast<double>(FIELD(target,float,0xf0))) {
            select_sequence(8);emit_effect(1,F(0xec),F(0xf0),B(0x104),1);reinterpret_cast<AliceUpdateOwnerView*>(OWNER)->dispatch_indexed_event_member(1);F(0xf4)+=3.0;F(0xf8)=4.0f;return;
        }}
        if((square_float_value(F(0xec)-FIELD(TARGET,float,0xec))<=2500.0 && square_float_value(F(0xf0)-FIELD(TARGET,float,0xf0))<=10000.0) || stage_surface_height()>static_cast<double>(F(0xf0)) || S(0x174)<0) {
            publish_battle_layout_scalar(10.0f);select_sequence(6);B(0x135)=0;groundImpactB[0]=0.0f;groundImpactB[1]=0.0f;groundImpactB[2]=2.0f;groundImpact=groundImpactB;goto alice_817_ground_impact;
        }
if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 2:advance_six(0);F(0x11c)-=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    case 3:F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)<=20) {B(0x111)-=20;B(0x110)-=20;}else {if(B(0x113)<=20) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=20;}}break;
    case 4:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<30) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=30;B(0x110)-=30;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}break;
    case 5:if(I(0x144)%2==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,F(0xec),static_cast<float>(static_cast<double>(50*I(0x144))+F(0xf0)),B(0x104),1,packet,3);}if(I(0x144)==4) RETIRE();break;
    case 6:F(0x12c)+=15.0;if(B(0x113)<=5) RETIRE();B(0x113)-=5;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 7: {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action==530 || action==531) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {select_sequence(6);F(0xf4)=0.0f;F(0xf8)=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();F(0xf8)-=0.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(stage_surface_height()>=nextY) {select_sequence(1);F(0xf0)=stage_surface_height();F(0xf8)=0.0f;return;}
        if((square_float_value(F(0xec)-FIELD(TARGET,float,0xec))<=10000.0 && square_float_value(F(0xf0)-FIELD(TARGET,float,0xf0))<=10000.0) || S(0x174)<0) {publish_battle_layout_scalar(10.0f);select_sequence(6);B(0x135)=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf8)=12.0f;F(0xf4)=-10.0f;return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 8: {
        if(emit_repeated(0,3,5)) RETIRE();F(0xf8)-=0.5;double nextY=static_cast<double>(F(0xf8))+F(0xf0);
        if(stage_surface_height()>=nextY || (square_float_value(F(0xec)-FIELD(TARGET,float,0xec))<=2500.0 && square_float_value(F(0xf0)-FIELD(TARGET,float,0xf0))<=10000.0) || stage_surface_height()>static_cast<double>(F(0xf0)) || S(0x174)<0) {publish_battle_layout_scalar(10.0f);select_sequence(6);B(0x135)=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf8)=12.0f;F(0xf4)=-10.0f;return;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-160.0) RETIRE();F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    }FINISH();
alice_817_ground_impact:
    spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,groundImpact,3);WAVE(6);F(0xf0)=stage_surface_height();F(0xf8)=12.0f;F(0xf4)=-10.0f;return;


}
case 820: {

    B(0x17c)=2;if(S(0x13e)<=4 && (emit_repeated(0,1,3) || S(0x174)<=-500)) select_sequence(5);
    if(S(0x13e)==0) {F(0x12c)+=20.0;if(I(0x144)==18) {F(0xf8)=0.0f;F(0xf4)=0.0f;F(0x12c)=0.0f;next_sequence_block();B(0x33c)=1;return;}F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);if(F(0xf0)<0.0f) F(0xf0)=0.0f;}
    short phase=S(0x13e);if(phase==1 && I(0x144)>=static_cast<short>(static_cast<int>(PARAM[3]+20.0))) {next_sequence_block();return;}
    if(phase==2) {F(0x12c)+=40.0;if(I(0x144)>=9) {F(0x12c)=0.0f;next_sequence_block();return;}}
    if(S(0x13e)==3) {if(I(0x144)==0) {WAVE(7);float *parameters=PARAM;parameters[0]=45.0f;parameters[1]=55.0f;}float *parameters=PARAM;parameters[1]-=5.0;if(parameters[1]<-0.5f) {parameters[1]=-0.5f;B(0x184)=0;}MOTION->set_components(PARAM[0],PARAM[1]);advance_six(0);if(I(0x178)>0) {select_sequence(4);return;}if(I(0x144)>=90) {next_sequence_block();B(0x33c)=255;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}MOVE();}
    if(S(0x13e)==4) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==5) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==6 && update_flight_state(5)) return;FINISH();


}
case 821: {
 {
    B(0x17c)=6;short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && S(0x13e)<=1) select_sequence(3);
    if(S(0x13e)==0) {MOVE();}short phase=S(0x13e);
    if(phase>=1 && phase<=2) {F(0xf4)-=2.0;int collision=I(0x180);if(collision!=0) {void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>=545 && action<=549) FIELD(owner,int,0x180)=collision;}if(F(0xf4)<-0.5f) F(0xf4)=-0.5f;if(F(0xf4)<=0.0f && S(0x13e)==1) {B(0x184)=0;select_sequence(2);}MOVE();}
    if(S(0x13e)==2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==3) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==4) {F(0x11c)+=static_cast<double>(0.05f);F(0x120)*=static_cast<double>(0.8f);if(F(0x120)<=0.01f) RETIRE();F(0xf4)=10.0f;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*10.0+F(0xec));}
    if(S(0x13e)==5) {F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<30) RETIRE();B(0x113)-=30;}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) {F(0xf4)=25.0f;WAVE(12);float packet[3]={0.0f,0.0f,4.0f};spawn_unparented(821,static_cast<float>(static_cast<double>(130*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+4.0),B(0x104),B(0x33c),packet,3);}return;
}


}
case 825: {

    B(0x17c)=3;
    if(S(0x13e)<=2 && (emit_repeated(0,1,3) || S(0x174)<=-750)) select_sequence(3);
    if(S(0x13e)==0) {MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[0]-=2.0;parameters[1]-=1.0;if(parameters[1]<0.0f) {parameters[1]=0.0f;next_sequence_block();return;}MOVE();if(F(0xf0)<0.0f) F(0xf0)=0.0f;}
    if(S(0x13e)==1) {
        void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);MOTION->set_components(F(0x378),2.0f);
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(825,F(0xec),F(0xf0),B(0x104),1,packet,3);}if(I(0x144)%15==0) WAVE(4);advance_six(0);if(I(0x178)>0) {select_sequence(3);return;}
        if(I(0x180)!=0 && ++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)>=5*(FIELD(OWNER,signed char,0x607)+18) || C(0x184)<=0) {next_sequence_block();B(0x33c)=255;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}
        F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==2) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==3) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==4 && update_flight_state(3)) return;
    if(S(0x13e)==5) {
        F(0x12c)+=25.0;if(!RELATED) RETIRE();
        if(FIELD(RELATED,short,0x13e)==1) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>3.0f) F(0x11c)=2.5f;F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}
        else {if(B(0x113)<20) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;}
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) {TURN_TO_OWNER();}return;


}
case 827: {

    switch(S(0x13e)) {
    case 0:case 3: {
        if(emit_repeated(0,3,5)) RETIRE();float trail[3]={0.0f,0.0f,1.0f};spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,trail,3);advance_six(0);void *owner=OWNER;short count=FIELD(owner,short,0x7a6);
        if(count>0) {
            double dySquared=square_float_value(F(0xf0)-FIELD(owner,float,4*count+0x7bc));double distance=square_float_value(F(0xec)-FIELD(OWNER,float,4*FIELD(OWNER,short,0x7a6)+0x7ac))+dySquared;
            if(static_cast<double>(square_int_value(35))>=distance) {
                owner=OWNER;F(0xec)=FIELD(owner,float,4*FIELD(owner,short,0x7a6)+0x7ac);F(0xf0)=FIELD(owner,float,4*FIELD(owner,short,0x7a6)+0x7bc);FIELD(owner,unsigned char,FIELD(owner,short,0x7a6)+0x7d0)=1;
                owner=OWNER;count=FIELD(owner,short,0x7a6);int facing=C(0x104);float dx,dy;
                if(count==1) {void *target=TARGET;dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*facing);dy=static_cast<float>(FIELD(target,float,0xf0)-static_cast<double>(F(0xf0))+100.0);}
                else {dx=static_cast<float>((FIELD(owner,float,4*count+0x7a8)-static_cast<double>(F(0xec)))*facing);dy=FIELD(owner,float,4*count+0x7b8)-F(0xf0);}
                PARAM[0]=-atan2_degrees(dy,dx);--FIELD(OWNER,short,0x7a6);I(0x180)=0;B(0x184)=1;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(13);
            }
        }
        MOTION->set_components(PARAM[0],PARAM[1]);owner=OWNER;F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);
        if(FIELD(owner,short,0x7a6)<=0 && (F(0xec)<-100.0f || F(0xec)>1380.0f || F(0xf0)>1060.0f || !(F(0xf0)>=-260.0f))) RETIRE();break;
    }
    case 5:case 6: {
        if(emit_repeated(0,3,5)) RETIRE();float trail[3]={0.0f,0.0f,1.0f};spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,trail,3);advance_six(0);void *owner=OWNER;short count=FIELD(owner,short,0x7a6);
        if(count>0) {
            double dySquared=square_float_value(F(0xf0)-FIELD(owner,float,4*count+0x7bc));double distance=square_float_value(F(0xec)-FIELD(OWNER,float,4*FIELD(OWNER,short,0x7a6)+0x7ac))+dySquared;
            if(static_cast<double>(square_int_value(15))>=distance) {
                owner=OWNER;F(0xec)=FIELD(owner,float,4*FIELD(owner,short,0x7a6)+0x7ac);F(0xf0)=FIELD(owner,float,4*FIELD(owner,short,0x7a6)+0x7bc);FIELD(owner,unsigned char,FIELD(owner,short,0x7a6)+0x7d0)=1;
                owner=OWNER;count=FIELD(owner,short,0x7a6);int facing=C(0x104);float dx,dy;
                if(count==1) {void *target=TARGET;dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*facing);dy=static_cast<float>(FIELD(target,float,0xf0)-static_cast<double>(F(0xf0))+100.0);}
                else {dx=static_cast<float>((FIELD(owner,float,4*count+0x7a8)-static_cast<double>(F(0xec)))*facing);dy=FIELD(owner,float,4*count+0x7b8)-F(0xf0);}
                PARAM[0]=-atan2_degrees(dy,dx);--FIELD(OWNER,short,0x7a6);I(0x180)=0;B(0x184)=1;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(13);
            }
        }
        MOTION->set_components(PARAM[0],PARAM[1]);owner=OWNER;F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);
        if(FIELD(owner,short,0x7a6)<=0 && (F(0xec)<-100.0f || F(0xec)>1380.0f || F(0xf0)>1060.0f || !(F(0xf0)>=-260.0f))) RETIRE();break;
    }
    case 1:case 4:F(0x11c)*=static_cast<double>(0.98f);F(0x120)=F(0x11c);if(B(0x113)<=5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;break;
    case 2:F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0x370)-=static_cast<double>(0.2f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    }FINISH();


}
case 830: {

    if(S(0x13e)==0) {
        F(0x370)+=F(0x374);F(0x374)-=1.5;if(F(0x374)<0.0f) F(0x374)=0.0f;B(0x104)=FIELD(OWNER,unsigned char,0x104);void *owner=OWNER;
        F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[2]*120.0))*F(0x370)+FIELD(owner,float,0xec));
        double orbitY=lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[2]*120.0));owner=OWNER;float *parameters=PARAM;F(0xf0)=static_cast<float>(orbitY*F(0x370)*0.25+(FIELD(owner,float,0xf0)+100.0));B(0x33c)=static_cast<unsigned char>(2*(static_cast<int>(static_cast<double>(4*FIELD(owner,short,0x7ac))+parameters[2]*120.0)%360>180)-1);
        owner=OWNER;if(FIELD(owner,short,0x174)<=0) {next_sequence_block();F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
        short action=FIELD(owner,short,0x13c);if(action==565 && FIELD(owner,unsigned char,0x7d0)==1) {short count=FIELD(owner,short,0x7a4);if(PARAM[2]==static_cast<double>(count)) {FIELD(owner,short,0x7a4)=count-1;FIELD(OWNER,unsigned char,0x7d0)=0;set_action(831);select_sequence(0);I(0x144)=0;return;}}
        if(action==566 && FIELD(owner,unsigned char,0x7d0)==1) {--FIELD(owner,short,0x7a4);set_action(834);select_sequence(0);I(0x144)=0;return;}
    }
    if(S(0x13e)==1) {F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}FINISH();


}
case 831: {
 {
    void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150 && S(0x13e)<=3) {select_sequence(4);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
    if(S(0x13e)==0) {
        double dx=static_cast<double>(50*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec)-F(0xec);F(0x370)=static_cast<float>(dx*dx);double dy=FIELD(owner,float,0xf0)+115.0-F(0xf0);F(0x374)=static_cast<float>(dy*dy);F(0x378)=sqrt_float_value(F(0x374)+F(0x370));
        float *parameters=PARAM;parameters[0]=-atan2_degrees(static_cast<float>(FIELD(owner,float,0xf0)+115.0-F(0xf0)),static_cast<float>(static_cast<double>(50*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec)-F(0xec)));parameters[1]=static_cast<float>(F(0x378)*static_cast<double>(0.2f));if(parameters[1]>50.0f) parameters[1]=50.0f;MOTION->set_components(parameters[0],parameters[1]);C(0x104)=F(0xf4)>=0.0f?1:-1;
        if(I(0x144)>=16) {next_sequence_block();C(0x104)=FIELD(OWNER,signed char,0x104);owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(50*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+115.0);return;}F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==1) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(831,static_cast<float>(static_cast<double>(60*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(9);}owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(50*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+115.0);}
    short phase=S(0x13e);if(phase==1) {owner=OWNER;if(FIELD(owner,short,0x13c)!=565 || FIELD(owner,short,0x13e)>=3) {F(0x370)=0.0f;F(0x374)=0.0f;F(0x378)=0.0f;next_sequence_block();return;}}
    if(phase==3) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==4) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==5) {
        if(S(0x364)==0) {if(I(0x144)>=40) S(0x364)=1;else {if(RELATED) {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);}F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);}short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();if(action!=565 || S(0x13e)==3) S(0x364)=1;}
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(F(0x11c)<0.02f) RETIRE();}
    }
    if(S(0x13e)==6) {
        short action=FIELD(OWNER,short,0x13c);if(action<=49 || action>=150) {if(S(0x364)<=1 && action!=565) S(0x364)=2;}
        else if(S(0x364)<=1) {for(int index=0;index<30;++index) {double centerY=F(0xf0)+10.0;emit_effect(201,static_cast<float>(static_cast<double>(RF(20))+static_cast<double>(40*index*C(0x104))+F(0xec)),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1);}RETIRE();}
        if(S(0x364)==0) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}F(0x120)+=static_cast<double>(0.1f);if(F(0x120)>0.7f) {F(0x120)=0.7f;S(0x364)=1;B(0x184)=10;return;}}
        if(S(0x364)==1) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=2;}advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}}
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();}
    }FINISH();
}


}
case 834: {
 {
    void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150 && S(0x13e)<=3) {select_sequence(4);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
    if(S(0x13e)==0) {
        double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(3*FIELD(owner,short,0x7ac))+PARAM[2]*120.0));owner=OWNER;double desiredX=orbitX*20.0+static_cast<double>(75*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec);
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(3*FIELD(owner,short,0x7ac))+PARAM[2]*120.0))*80.0+(FIELD(OWNER,float,0xf0)+100.0));
        double dx=desiredX-F(0xec);F(0x370)=static_cast<float>(dx*dx);double dy=static_cast<double>(desiredY)-F(0xf0);F(0x374)=static_cast<float>(dy*dy);F(0x378)=sqrt_float_value(F(0x374)+F(0x370));
        float *parameters=PARAM;parameters[0]=-atan2_degrees(desiredY-F(0xf0),static_cast<float>(desiredX-F(0xec)));parameters[1]=static_cast<float>(F(0x378)*static_cast<double>(0.2f));if(parameters[1]>50.0f) parameters[1]=50.0f;MOTION->set_components(parameters[0],parameters[1]);C(0x104)=F(0xf4)>=0.0f?1:-1;
        if(I(0x144)>=16) {next_sequence_block();B(0x104)=FIELD(OWNER,unsigned char,0x104);F(0xec)=static_cast<float>(desiredX);F(0xf0)=desiredY;return;}F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==1) {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(834,static_cast<float>(static_cast<double>(60*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(9);}
        owner=OWNER;double desiredX=lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(3*FIELD(owner,short,0x7ac))+PARAM[2]*120.0))*20.0+static_cast<double>(75*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec);
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(3*FIELD(owner,short,0x7ac))+PARAM[2]*120.0))*80.0+(FIELD(OWNER,float,0xf0)+100.0));F(0xec)=static_cast<float>(desiredX);F(0xf0)=desiredY;
    }
    short phase=S(0x13e);if(phase==1) {owner=OWNER;if(FIELD(owner,short,0x13c)!=566 || FIELD(owner,short,0x13e)>=3) {F(0x370)=0.0f;F(0x374)=0.0f;F(0x378)=0.0f;next_sequence_block();return;}}
    if(phase==3) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==4) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==5) {
        if(S(0x364)==0) {if(I(0x144)>=40) S(0x364)=1;else {if(RELATED) {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);}F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);}short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();if(action!=566 || S(0x13e)==3) S(0x364)=1;}
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(F(0x11c)<0.02f) RETIRE();}
    }
    if(S(0x13e)==6) {
        short action=FIELD(OWNER,short,0x13c);if(action<=49 || action>=150) {if(S(0x364)<=1 && action!=566) S(0x364)=2;}
        else if(S(0x364)<=1) {for(int index=0;index<20;++index) {double centerY=F(0xf0)+10.0;emit_effect(201,static_cast<float>(static_cast<double>(RF(30))+static_cast<double>(60*index*C(0x104))+F(0xec)),static_cast<float>(centerY-static_cast<double>(RF(20))),B(0x104),1);}RETIRE();}
        if(S(0x364)==0) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}F(0x120)+=static_cast<double>(0.1f);if(F(0x120)>0.7f) {F(0x120)=0.7f;S(0x364)=1;B(0x184)=10;return;}}
        if(S(0x364)==1) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=2;}advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}}
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();}
    }FINISH();
}


}
case 849: {
 {
    short entryPhase=S(0x13e);switch(entryPhase) {
    case 1:case 2:case 3: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150 && entryPhase<=3) {select_sequence(4);return;}
        if(action!=301 && entryPhase<=2) {select_sequence(3);F(0x370)=0.0f;return;}
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && entryPhase==1) {F(0xf4)=30.0f;F(0xf8)=5.0f;}
        if(S(0x13e)<=2) {
            F(0xf4)-=3.0;if(F(0xf4)<=1.0f) F(0xf4)=1.0f;F(0xf8)-=0.5;if(F(0xf8)<0.5f) F(0xf8)=0.5f;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)+=F(0xf8);F(0xec)=static_cast<float>(static_cast<double>(30*C(0x104))+FIELD(owner,float,0xec)+F(0x370));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0+F(0x374));FIELD(owner,int,0x180)=I(0x180);
            if(S(0x13e)==2 && I(0x144)%2==0 && S(0x140)>=1) {F(0x378)=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={F(0x378),0.0f,5.0f};spawn_unparented(849,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*100.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*100.0+F(0xf0)),B(0x104),1,packet,3);}
        }
        if(S(0x13e)==3) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}break;
    }
    case 4:if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 5:F(0x11c)+=static_cast<double>(0.01f);F(0x120)*=static_cast<double>(0.8f);if(F(0x120)<=0.05f) RETIRE();MOTION->set_components(PARAM[0],15.0f);MOVE();break;
    case 6:case 7:case 8: {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && entryPhase<=7) {select_sequence(4);F(0x370)=0.0f;return;}if(action!=302 && entryPhase<=7) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        if(entryPhase==6) {
            if(!RELATED) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;F(0x374)=0.0f;return;}
            void *related=RELATED;float *parameters=PARAM;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0x370)+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf0)+F(0x374);F(0x370)=static_cast<float>(lookup_orientation_cosine_quantized_abs(parameters[0])*5.0+F(0x370));parameters=PARAM;F(0x374)=static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])*15.0+F(0x374));
        }
        if(S(0x13e)==7) {
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,9.0f};spawn_unparented(849,static_cast<float>((lookup_orientation_cosine_quantized_abs(PARAM[0])*5.0+135.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(PARAM[0])*15.0+F(0xf0)+3.0),B(0x104),1,packet,3);}
            if(!RELATED) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;F(0x374)=0.0f;return;}void *related=RELATED;F(0xec)=static_cast<float>(F(0x370)*static_cast<double>(C(0x104))+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf0)+F(0x374);
        }
        if(S(0x13e)==8) {
            short action=FIELD(OWNER,short,0x13c);if(((action>49 && action<150) || action!=302) && S(0x140)<=1) {select_frame(2);return;}
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {B(0x184)=1;I(0x180)=0;F(0xf4)=30.0f;F(0xf8)=0.0f;}
            F(0xf4)-=3.0;if(F(0xf4)<=0.5f) F(0xf4)=0.5f;void *owner=OWNER;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)=F(0xf8)+F(0x374);F(0xec)=static_cast<float>(static_cast<double>(110*C(0x104))+FIELD(owner,float,0xec)+F(0x370));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0+F(0x374));FIELD(owner,int,0x180)=I(0x180);if(S(0x140)==2 && S(0x142)==10) RETIRE();
        }break;
    }
    case 14:case 15:case 16: {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && entryPhase<=15) {select_sequence(4);F(0x370)=0.0f;return;}if(action!=307 && entryPhase<=15) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        if(entryPhase==14) {
            if(!RELATED) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;F(0x374)=0.0f;return;}
            void *related=RELATED;float *parameters=PARAM;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0x370)+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf0)+F(0x374);F(0x370)=static_cast<float>(lookup_orientation_cosine_quantized_abs(parameters[0])*5.0+F(0x370));parameters=PARAM;F(0x374)=static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])*15.0+F(0x374));
        }
        if(S(0x13e)==15) {
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,9.0f};spawn_unparented(849,static_cast<float>((lookup_orientation_cosine_quantized_abs(PARAM[0])*5.0+135.0)*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(PARAM[0])*15.0+F(0xf0)+3.0),B(0x104),1,packet,3);}
            if(!RELATED) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;F(0x374)=0.0f;return;}void *related=RELATED;F(0xec)=static_cast<float>(F(0x370)*static_cast<double>(C(0x104))+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf0)+F(0x374);
        }
        if(S(0x13e)==16) {
            short action=FIELD(OWNER,short,0x13c);if(((action>49 && action<150) || action!=307) && S(0x140)<=1) {select_frame(2);return;}
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {B(0x184)=1;I(0x180)=0;F(0xf4)=30.0f;F(0xf8)=0.0f;}
            F(0xf4)-=3.0;if(F(0xf4)<=0.5f) F(0xf4)=0.5f;void *owner=OWNER;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)=F(0xf8)+F(0x374);F(0xec)=static_cast<float>(static_cast<double>(50*C(0x104))+FIELD(owner,float,0xec)+F(0x370));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0+F(0x374));FIELD(owner,int,0x180)=I(0x180);if(S(0x140)==2 && S(0x142)==10) RETIRE();
        }break;
    }
    case 9:F(0x11c)+=static_cast<double>(0.05f);F(0x120)*=static_cast<double>(0.85f);if(B(0x113)<15) RETIRE();B(0x113)-=15;F(0xf4)=10.0f;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*10.0+F(0xec));break;
    case 10:if(update_flight_state(4)) return;break;
    case 11:case 12: {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) {select_sequence(4);F(0x12c)=0.0f;F(0x370)=0.0f;return;}
        if(action==304) {MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=4.0;if(parameters[1]<=1.0f) parameters[1]=1.0f;void *owner=OWNER;F(0x370)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0x370));F(0x374)=F(0xf8)+F(0x374);F(0xec)=static_cast<float>(static_cast<double>(30*C(0x104))+FIELD(owner,float,0xec)+F(0x370));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0+F(0x374));int collision=I(0x180);if(collision!=0) FIELD(owner,int,0x180)=collision;if(S(0x13e)!=12) break;if(I(0x144)>=3) B(0x184)=0;if(I(0x144)<10) break;}
        select_sequence(3);F(0x12c)=0.0f;F(0x370)=0.0f;F(0x374)=0.0f;return;
    }
    case 13:F(0x11c)+=static_cast<double>(0.05f);F(0x120)*=static_cast<double>(0.85f);if(B(0x113)<15) RETIRE();B(0x113)-=15;MOTION->set_components(PARAM[0],PARAM[1]);MOVE();break;
    case 17:case 18: {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && entryPhase<=18) {select_sequence(4);F(0x370)=0.0f;return;}if(action!=308 && entryPhase<=18) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        if(entryPhase==17) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {B(0x184)=0;I(0x180)=0;}void *owner=OWNER;F(0xec)=static_cast<float>((F(0x370)+25.0)*static_cast<double>(C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0+F(0x374));MOTION->set_components(PARAM[0],PARAM[1]);F(0x370)=F(0xf4)+F(0x370);F(0x374)=F(0xf8)+F(0x374);}
        if(S(0x13e)==18) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={45.0f,2.0f,13.0f};spawn_unparented(849,F(0xec),F(0xf0),B(0x104),1,packet,3);float *parameters=PARAM;parameters[0]=45.0f;parameters[1]=30.0f;}
            void *owner=OWNER;F(0xec)=static_cast<float>((F(0x370)+25.0)*static_cast<double>(C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0+F(0x374));MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=3.0;if(parameters[1]<0.5f) parameters[1]=0.5f;if(I(0x144)>=8) B(0x184)=0;F(0x370)=F(0xf4)+F(0x370);F(0x374)=F(0xf8)+F(0x374);if(I(0x144)>=26) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        }break;
    }
    case 24:case 25: {
        short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && entryPhase<=24) {select_sequence(4);F(0x370)=0.0f;return;}if(action!=309 && entryPhase<=24) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        if(entryPhase==24) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {B(0x184)=0;I(0x180)=0;}void *owner=OWNER;F(0xec)=static_cast<float>((F(0x370)+25.0)*static_cast<double>(C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0+F(0x374));MOTION->set_components(PARAM[0],PARAM[1]);F(0x370)=F(0xf4)+F(0x370);F(0x374)=F(0xf8)+F(0x374);}
        if(S(0x13e)==25) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={-45.0f,2.0f,13.0f};spawn_unparented(849,F(0xec),F(0xf0),B(0x104),1,packet,3);float *parameters=PARAM;parameters[0]=-45.0f;parameters[1]=30.0f;}
            void *owner=OWNER;F(0xec)=static_cast<float>((F(0x370)+30.0)*static_cast<double>(C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+120.0+F(0x374));MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=3.0;if(parameters[1]<0.5f) parameters[1]=0.5f;if(I(0x144)>=8) B(0x184)=0;F(0x370)=F(0xf4)+F(0x370);F(0x374)=F(0xf8)+F(0x374);if(I(0x144)>=18) {select_sequence(3);F(0x370)=0.0f;F(0x374)=0.0f;return;}
        }break;
    }
    case 19:case 20: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150) {select_sequence(4);return;}
        if(action!=408 && entryPhase<=20) {select_sequence(3);F(0x370)=0.0f;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && entryPhase==19) {F(0xf4)=30.0f;F(0xf8)=5.0f;}
        if(S(0x13e)<=20) {F(0xf4)-=3.0;if(F(0xf4)<=1.0f) F(0xf4)=1.0f;F(0xf8)-=0.5;if(F(0xf8)<0.5f) F(0xf8)=0.5f;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)+=F(0xf8);F(0xec)=static_cast<float>(static_cast<double>(30*C(0x104))+FIELD(owner,float,0xec)+F(0x370));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0+F(0x374));FIELD(owner,int,0x180)=I(0x180);
            if(S(0x13e)==20 && I(0x144)%2==0 && S(0x140)>=1) {F(0x378)=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={F(0x378),0.0f,5.0f};spawn_unparented(849,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*100.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*100.0+F(0xf0)),B(0x104),1,packet,3);}
        }break;
    }
    case 21:
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,22.0f};spawn_parented(849,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        {short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) {select_sequence(4);return;}if(action!=418) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;return;}}
        F(0xec)=static_cast<float>((lookup_orientation_cosine(10*(18-I(0x144)))*150.0+150.0)*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));F(0xf0)=static_cast<float>(lookup_orientation_sine(10*(18-I(0x144)))*25.0+(FIELD(OWNER,float,0xf0)+50.0));if(10*I(0x144)>=180) B(0x33c)=1;if(10*I(0x144)==170) {B(0x184)=1;I(0x180)=0;}if(10*I(0x144)==190) B(0x184)=0;if(I(0x180)!=0) FIELD(OWNER,int,0x180)=I(0x180);if(10*I(0x144)>=350) RETIRE();break;
    case 23:
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,22.0f};spawn_parented(849,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        {short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) {select_sequence(4);return;}if(action!=418) {select_sequence(3);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;return;}}
        F(0xec)=static_cast<float>((lookup_orientation_cosine(10*(I(0x144)+18))*150.0+150.0)*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));F(0xf0)=static_cast<float>(lookup_orientation_sine(10*(I(0x144)+18))*25.0+(FIELD(OWNER,float,0xf0)+50.0));if(10*I(0x144)>=180) B(0x33c)=255;if(10*I(0x144)==170) {B(0x184)=1;I(0x180)=0;}if(10*I(0x144)==190) B(0x184)=0;if(I(0x180)!=0) FIELD(OWNER,int,0x180)=I(0x180);if(10*I(0x144)>=350) RETIRE();break;
    case 22:
        if(!RELATED) {if(B(0x113)<30) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=30;B(0x112)-=30;B(0x111)-=30;}
        else {B(0x33c)=FIELD(RELATED,unsigned char,0x33c);void *related=RELATED;short phase=FIELD(related,short,0x13e);if(phase!=21 && phase!=23) RETIRE();F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}F(0x12c)+=25.0;break;
    }
    advance_frame();
    if(S(0x13e)==2 && S(0x140)>=1 && S(0x142)==0) {reinterpret_cast<AliceUpdateOwnerView*>(OWNER)->dispatch_indexed_event_member(27);B(0x184)=1;I(0x180)=0;}
    if(S(0x13e)==20 && S(0x140)>=1 && S(0x142)==0) {reinterpret_cast<AliceUpdateOwnerView*>(OWNER)->dispatch_indexed_event_member(27);B(0x184)=1;I(0x180)=0;}
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==21) select_sequence(3);
        if(I(0x144)==0) {
            if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) {if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;F(0x370)=0.0f;}
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==12) {reinterpret_cast<AliceUpdateOwnerView*>(OWNER)->dispatch_indexed_event_member(27);float packet[3]={PARAM[0],3.0f,13.0f};spawn_unparented(849,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        }
    }return;
}


}
case 850: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {F(0x12c)+=30.0;double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(stage_surface_height()>=nextY) {publish_battle_layout_scalar(10.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};F(0xf0)=stage_surface_height();spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(21);F(0xf8)=static_cast<float>(-F(0xf8)*0.5);F(0xf4)*=static_cast<double>(0.2f);return;}F(0xf8)-=1.0;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);}
    if(S(0x13e)==1) {F(0x12c)+=15.0;if(B(0x113)<=10) RETIRE();B(0x113)-=10;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);}
    if(S(0x13e)==2) {advance_six(0);F(0x11c)-=static_cast<double>(0.005f);F(0x120)=F(0x11c);if(B(0x113)<=5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;}
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)>25) {if(B(0x113)<=25) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=25;}else {B(0x111)-=25;B(0x110)-=25;}}}
    if(S(0x13e)==4) {F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<25) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=25;B(0x110)-=25;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}}
    if(S(0x13e)==5) {float *parameters=PARAM;F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);MOTION->set_components(parameters[0],parameters[1]);parameters=PARAM;parameters[1]-=1.5;if(parameters[1]<0.5f) parameters[1]=0.5f;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));if(B(0x113)<5) RETIRE();B(0x113)-=5;}FINISH();


}
case 851: {

    if(S(0x13e)<=1) {
        F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0x378)+F(0x370));F(0x378)-=1.0;if(F(0x378)<1.0f) F(0x378)=1.0f;S(0x36c)+=3;S(0x36a)+=4*C(0x104);if(S(0x36c)>=90) S(0x36c)=90;F(0x37c)+=3.0;
        double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(PARAM[3]+static_cast<double>(S(0x36a))));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)));float *parameters=PARAM;F(0xec)=static_cast<float>(elevationX*F(0x37c)*orbitX+F(0x370));
        double orbitY=lookup_orientation_sine_quantized_abs(static_cast<float>(parameters[3]+static_cast<double>(S(0x36a))));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)))*F(0x37c)*orbitY+F(0x374));
    }
    if(S(0x13e)==0) {B(0x184)=0;if(F(0x378)==1.0f) {next_sequence_block();B(0x33c)=1;B(0x184)=1;return;}}
    if(S(0x13e)==1) {
        if(I(0x144)==0) {float packet[4]={0.0f,0.0f,5.0f,0.0f};spawn_parented(851,F(0xec),F(0xf0),B(0x104),1,packet,4);}advance_six(0);if(I(0x180)!=0 && ++S(0x368)>=30) {S(0x368)=0;I(0x180)=0;B(0x184)=1;}
        if(I(0x144)>=120) {B(0x184)=0;next_sequence_block();B(0x33c)=255;F(0x370)=0.0f;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}
    }
    if(S(0x13e)==2) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==3) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==4 && update_flight_state(3)) return;
    if(S(0x13e)==5) {if(!RELATED) RETIRE();if(FIELD(RELATED,short,0x13e)==1) {if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}else {if(B(0x113)<30) RETIRE();F(0x11c)+=static_cast<double>(0.15f);F(0x120)=F(0x11c);B(0x113)-=30;}F(0x12c)+=25.0;}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) {TURN_TO_OWNER();}return;


}
case 852: {
 {
    void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150 && S(0x13e)<=3) {select_sequence(4);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
    if(S(0x13e)==0) {
        double dx=static_cast<double>(50*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec)-F(0xec);F(0x370)=static_cast<float>(dx*dx);double dy=FIELD(owner,float,0xf0)+115.0-F(0xf0);F(0x374)=static_cast<float>(dy*dy);F(0x378)=sqrt_float_value(F(0x374)+F(0x370));
        float *parameters=PARAM;parameters[0]=-atan2_degrees(static_cast<float>(FIELD(owner,float,0xf0)+115.0-F(0xf0)),static_cast<float>(static_cast<double>(50*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec)-F(0xec)));parameters[1]=static_cast<float>(F(0x378)*static_cast<double>(0.2f));if(parameters[1]>50.0f) parameters[1]=50.0f;MOTION->set_components(parameters[0],parameters[1]);C(0x104)=F(0xf4)>=0.0f?1:-1;
        if(I(0x144)>=16) {next_sequence_block();C(0x104)=FIELD(OWNER,signed char,0x104);owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(50*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+115.0);return;}F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==1) {if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(852,static_cast<float>(static_cast<double>(60*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(23);}owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(50*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+115.0);}
    short phase=S(0x13e);if(phase==1) {owner=OWNER;if(FIELD(owner,short,0x13c)!=602 || FIELD(owner,short,0x13e)>=3) {F(0x370)=0.0f;F(0x374)=0.0f;F(0x378)=0.0f;next_sequence_block();return;}}
    if(phase==3) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==4) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==5) {
        if(S(0x364)==0) {if(I(0x144)>=60) S(0x364)=1;else {if(RELATED) {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);}F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);}short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();if(action!=602 || S(0x13e)==3) S(0x364)=1;}
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(F(0x11c)<0.02f) RETIRE();}
    }
    if(S(0x13e)==6) {
        short action=FIELD(OWNER,short,0x13c);if(action<=49 || action>=150) {if(S(0x364)<=1 && action!=602) S(0x364)=2;}
        else if(S(0x364)<=1) RETIRE();
        if(S(0x364)==0) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}F(0x120)+=static_cast<double>(0.15f);if(F(0x120)>1.0f) {F(0x120)=1.0f;S(0x364)=1;B(0x184)=20;return;}}
        if(S(0x364)==1) {if(I(0x144)%2==0) {float packet[3]={0.0f,0.0f,7.0f};spawn_parented(852,static_cast<float>(static_cast<double>(RF(960))*C(0x104)+F(0xec)),F(0xf0),B(0x104),1,packet,3);}if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=2;}advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}}
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();}
    }
    if(S(0x13e)==7) {F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);F(0x12c)+=30.0;if(RELATED) F(0xf0)=FIELD(RELATED,float,0xf0);short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;F(0xec)=static_cast<float>(static_cast<double>(25*C(0x104))+F(0xec));if(F(0xec)>1380.0f || F(0xec)<-100.0f) RETIRE();}FINISH();
}


}
case 853: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {F(0x12c)+=30.0;double nextY=static_cast<double>(F(0xf0))+F(0xf8);if(!(stage_surface_height()<nextY)) {publish_battle_layout_scalar(10.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};F(0xf0)=stage_surface_height();spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(25);F(0xf8)=static_cast<float>(-F(0xf8)*0.5);F(0xf4)*=static_cast<double>(0.2f);return;}F(0xf8)-=2.0;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);}
    if(S(0x13e)==1) {F(0x12c)+=15.0;if(B(0x113)<=10) RETIRE();B(0x113)-=10;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);}
    if(S(0x13e)==2) {advance_six(0);F(0x11c)-=static_cast<double>(0.005f);F(0x120)=F(0x11c);}
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.3f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)>25) {if(B(0x113)<=25) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=25;}else {B(0x111)-=25;B(0x110)-=25;}}}
    if(S(0x13e)==4) {F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<25) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=25;B(0x110)-=25;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}}
    if(S(0x13e)==5) {float *parameters=PARAM;F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);MOTION->set_components(parameters[0],parameters[1]);parameters=PARAM;parameters[1]-=1.5;if(parameters[1]<0.5f) {parameters[1]=0.5f;if(B(0x113)<5) RETIRE();B(0x113)-=5;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));}if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);return;


}
case 854: {

    if(S(0x13e)<=1) {
        if(PARAM[3]>359.0f) {
            F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0x378)+F(0x370));F(0x378)-=2.0;if(F(0x378)<2.0f) F(0x378)=2.0f;S(0x36c)+=3;S(0x36a)-=4*C(0x104);if(S(0x36c)>=90) S(0x36c)=90;
            double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(PARAM[3]+static_cast<double>(S(0x36a))));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)));float *parameters=PARAM;F(0xec)=static_cast<float>(elevationX*200.0*orbitX+F(0x370));double orbitY=lookup_orientation_sine_quantized_abs(static_cast<float>(parameters[3]+static_cast<double>(S(0x36a))));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)))*200.0*orbitY+F(0x374));
        }
        else {
            F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0x378)+F(0x370));F(0x378)-=2.0;if(F(0x378)<2.0f) F(0x378)=2.0f;S(0x36c)+=3;S(0x36a)+=4*C(0x104);if(S(0x36c)>=90) S(0x36c)=90;
            double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(PARAM[3]+static_cast<double>(S(0x36a))));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)));float *parameters=PARAM;F(0xec)=static_cast<float>(elevationX*100.0*orbitX+F(0x370));double orbitY=lookup_orientation_sine_quantized_abs(static_cast<float>(parameters[3]+static_cast<double>(S(0x36a))));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)))*100.0*orbitY+F(0x374));
        }
    }
    if(S(0x13e)==0) {B(0x184)=0;if(F(0x378)<=2.0f) {next_sequence_block();B(0x33c)=1;B(0x184)=1;return;}}
    if(S(0x13e)==1) {
        if(I(0x144)==0) {float packet[4]={0.0f,0.0f,PARAM[3]>=360.0f?6.0f:5.0f,0.0f};spawn_parented(854,F(0xec),F(0xf0),B(0x104),1,packet,4);}advance_six(0);if(I(0x180)!=0 && ++S(0x368)>=30) {S(0x368)=0;I(0x180)=0;B(0x184)=1;}
        if(I(0x144)>=120) {B(0x184)=0;next_sequence_block();B(0x33c)=255;F(0x370)=0.0f;if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=-1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=1;return;}
    }
    if(S(0x13e)==2) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==3) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==4 && update_flight_state(3)) return;
    if(S(0x13e)==5 || S(0x13e)==6) {if(!RELATED) RETIRE();if(FIELD(RELATED,short,0x13e)==1) {if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}else {if(B(0x113)<30) RETIRE();F(0x11c)+=static_cast<double>(0.15f);F(0x120)=F(0x11c);B(0x113)-=30;}F(0x12c)+=25.0;}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) {TURN_TO_OWNER();}return;


}
case 855: {
 {
    void *owner=OWNER;short action=FIELD(owner,short,0x13c);if(action>49 && action<150 && S(0x13e)<=3) {select_sequence(4);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
    if(S(0x13e)==0) {
        double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[3]*60.0));owner=OWNER;float desiredX=static_cast<float>(orbitX*(F(0x380)*0.25+20.0)+static_cast<double>(75*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec));
        double desiredY=(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[3]*60.0))*(F(0x380)+80.0)+(FIELD(OWNER,float,0xf0)+100.0));
        double dx=desiredX-F(0xec);F(0x370)=static_cast<float>(dx*dx);double dy=desiredY-F(0xf0);F(0x374)=static_cast<float>(dy*dy);F(0x378)=sqrt_float_value(F(0x374)+F(0x370));
        float *parameters=PARAM;parameters[0]=-atan2_degrees(static_cast<float>(desiredY-F(0xf0)),static_cast<float>(desiredX-F(0xec)));parameters[1]=static_cast<float>(F(0x378)*static_cast<double>(0.2f));if(parameters[1]>50.0f) parameters[1]=50.0f;MOTION->set_components(parameters[0],parameters[1]);C(0x104)=F(0xf4)>=0.0f?1:-1;
        if(I(0x144)>=16) {next_sequence_block();B(0x104)=FIELD(OWNER,unsigned char,0x104);F(0xec)=static_cast<float>(desiredX);F(0xf0)=static_cast<float>(desiredY);return;}F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==1) {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(855,static_cast<float>(static_cast<double>(60*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(27);}
        owner=OWNER;double desiredX=lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[3]*60.0))*(F(0x380)*0.25+20.0)+static_cast<double>(75*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec);
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*FIELD(owner,short,0x7ac))+PARAM[3]*60.0))*(F(0x380)+80.0)+(FIELD(OWNER,float,0xf0)+100.0));F(0x380)+=2.0;F(0xec)=static_cast<float>(desiredX);F(0xf0)=desiredY;
    }
    short phase=S(0x13e);if(phase==1) {owner=OWNER;if(FIELD(owner,short,0x13c)!=605 || FIELD(owner,short,0x13e)>=3) {F(0x370)=0.0f;F(0x374)=0.0f;F(0x378)=0.0f;next_sequence_block();return;}}
    if(phase==3) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==4) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==5) {
        if(S(0x364)==0) {if(I(0x144)>=90) S(0x364)=1;else {if(RELATED) {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);}F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);}short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();if(action!=605 || S(0x13e)==3) S(0x364)=1;}
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(F(0x11c)<0.02f) RETIRE();}
    }
    if(S(0x13e)==6) {
        short action=FIELD(OWNER,short,0x13c);if(action<=49 || action>=150) {if(S(0x364)<=1 && action!=605) S(0x364)=2;}
        else if(S(0x364)<=1) RETIRE();
        if(S(0x364)==0) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}F(0x120)+=static_cast<double>(0.1f);if(F(0x120)>0.5f) {F(0x120)=0.5f;S(0x364)=1;B(0x184)=10;return;}}
        if(S(0x364)==1) {if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=2;}advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}}
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();}
    }FINISH();
}


}
case 856: {
 {
    short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150 && S(0x13e)<=5) select_sequence(6);
    if(S(0x13e)==0) {MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=1.0;if(parameters[1]<=0.0f) {parameters[1]=0.0f;next_sequence_block();return;}MOVE();}
    short phase=S(0x13e);if(phase==1 && I(0x144)>=10) {next_sequence_block();return;}
    if(phase==3) {if(I(0x144)==0) {WAVE(29);float packet[4]={static_cast<float>(static_cast<double>(-8*(static_cast<int>(PARAM[3])%4))+60.0),0.0f,8.0f,PARAM[3]};spawn_parented(856,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,4);}if(I(0x144)>=120) next_sequence_block();}
    if(S(0x13e)==5) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==6) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==7 && update_flight_state(6)) return;
    if(S(0x13e)==8) {
        F(0x12c)+=F(0x370);F(0x370)*=static_cast<double>(0.9f);if(I(0x180)==5 || !RELATED) RETIRE();short phase=FIELD(RELATED,short,0x13e);if(phase==6 || phase==5) RETIRE();if(phase==4) {select_frame(2);return;}
        if(S(0x140)==0 && I(0x144)>=10) {F(0x120)+=static_cast<double>(0.15f);if(F(0x120)>=2.0f) {B(0x184)=4;F(0x120)=2.0f;next_sequence_frame();}}
        if(S(0x140)==1) {F(0x120)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+2.0);advance_six(0);if(I(0x180)!=0 && ++S(0x364)>=7) {S(0x364)=0;I(0x180)=0;}}
        if(S(0x140)==2) {F(0x120)*=static_cast<double>(0.8f);if(S(0x142)>=20) RETIRE();}
    }
    if(S(0x13e)==9) {if(!RELATED) RETIRE();if(S(0x364)==0) {void *related=RELATED;F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)%2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);if(FIELD(related,short,0x140)==2) S(0x364)=1;}if(S(0x364)==1) {F(0x120)*=static_cast<double>(0.9f);if(S(0x142)>=60) RETIRE();}}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {TURN_TO_OWNER();}return;
}


}
case 857: {

    if(US(0x13e)<=1) {
        if(FIELD(OWNER,short,0x174)<=0) {select_sequence(5);return;}
        if(S(0x13e)==0) {float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<0.0f) {parameters[1]=0.0f;next_sequence_block();return;}}
        if(S(0x13e)==1) {
            if(I(0x144)==10) {WAVE(30);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x370)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);float packet[3]={0.0f,0.0f,3.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[0]=F(0x370);packet[1]=0.0f;packet[2]=2.0f;spawn_parented(857,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),-1,packet,3);}
            if(I(0x144)==20) {WAVE(30);float packet[3]={static_cast<float>(F(0x370)-90.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),-1,packet,3);}
            if(I(0x144)==30) {WAVE(30);float packet[3]={static_cast<float>(F(0x370)-180.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),-1,packet,3);}
            if(I(0x144)==40) {WAVE(30);float packet[3]={static_cast<float>(F(0x370)-270.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),-1,packet,3);}
            if(I(0x144)>=150) {select_sequence(8);F(0x370)=0.0f;return;}
        }MOTION->set_components(PARAM[0],PARAM[1]);MOVE();
    }
    if(S(0x13e)==2) {
        if(!RELATED) RETIRE();
        if(S(0x364)==0) {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(40*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);if(FIELD(related,short,0x13e)!=1) S(0x364)=2;
            if(S(0x364)==0) {F(0x120)+=static_cast<double>(0.05f);if(F(0x120)>=1.0f) {F(0x120)=1.0f;B(0x184)=1;S(0x364)=1;}if(!RELATED || FIELD(RELATED,short,0x13e)!=1) S(0x364)=2;}
        }
        if(S(0x364)==1) {advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=5) {I(0x180)=0;B(0x184)=1;S(0x366)=0;}if(!RELATED || FIELD(RELATED,short,0x13e)!=1) S(0x364)=2;}
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x110)-=8;B(0x111)-=8;}
    }
    if(S(0x13e)==3) {
        if(S(0x364)==0) {
            F(0x11c)=static_cast<float>((1.0-F(0x370))*0.75+0.25);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.95f);
            if(F(0x370)<=0.75f) {if(I(0x180)==0) B(0x184)=1;advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=5) {I(0x180)=0;B(0x184)=1;S(0x366)=0;}}
            if(I(0x144)%15==0) {float packet[3]={0.0f,0.0f,4.0f};spawn_parented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            if(!RELATED) S(0x364)=1;else {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(40*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)%2)*static_cast<double>(0.1f)+1.0);F(0x120)=F(0x11c);short phase=FIELD(related,short,0x13e);if(phase==5 || phase==6 || phase==8) S(0x364)=1;}
        }
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.97f);F(0x120)=F(0x11c);if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x110)-=8;B(0x111)-=8;}
    }
    if(S(0x13e)==4) {if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<8) RETIRE();B(0x113)-=8;}
    if(S(0x13e)==5) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;}
    if(S(0x13e)==6) {if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}
    if(S(0x13e)==7 && update_flight_state(5)) return;
    if(S(0x13e)==8) {if(FIELD(OWNER,short,0x174)<=0) {select_sequence(5);return;}if(I(0x144)>=30) {select_sequence(6);return;}}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {TURN_TO_OWNER();}return;


}
case 858: {
 {
    short entryPhase=S(0x13e);
    if(entryPhase!=15 && entryPhase<=19) {short action=FIELD(OWNER,short,0x13c);if(action>=50 && action<=149) {select_sequence(15);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}}
    if(entryPhase!=15 && entryPhase!=16 && entryPhase<=19) {void *owner=OWNER;if(FIELD(owner,short,0x13c)!=608 || FIELD(owner,short,0x13e)>1) {F(0x12c)=0.0f;select_sequence(16);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}}
    switch(entryPhase) {
    case 0:case 1: {
        if(FIELD(OWNER,int,0x6b4)>0 && B(0x104)==255) {C(0x104)=1;F(0xf4)=-F(0xf4);}if(FIELD(OWNER,int,0x6b4)<0 && B(0x104)==1) {C(0x104)=-1;F(0xf4)=-F(0xf4);}
        void *owner=OWNER;if(FIELD(owner,int,0x6b4)*C(0x104)<=0) {F(0xf4)-=2.0;if(F(0xf4)<0.0f) F(0xf4)=0.0f;}else {F(0xf4)+=2.0;if(F(0xf4)>10.0f) F(0xf4)=10.0f;}
        if(FIELD(owner,int,0x6b8)<0) {F(0xf8)+=2.0;if(F(0xf8)>10.0f) F(0xf8)=10.0f;}if(FIELD(owner,int,0x6b8)>0) {F(0xf8)-=2.0;if(F(0xf8)<-10.0f) F(0xf8)=-10.0f;}
        if(FIELD(owner,int,0x6b8)==0) {if(F(0xf8)<=0.0f) {F(0xf8)+=2.0;if(F(0xf8)>0.0f) F(0xf8)=0.0f;}else {F(0xf8)-=2.0;if(F(0xf8)<0.0f) F(0xf8)=0.0f;}}
        if(S(0x13e)==0 && F(0xf4)>5.0f) select_sequence(1);if(S(0x13e)==1 && F(0xf4)<5.0f) select_sequence(0);
        owner=OWNER;int primary=FIELD(owner,int,0x6bc);if(primary!=0 && primary<4) {
            int horizontal=FIELD(owner,int,0x6b4);int vertical=FIELD(owner,int,0x6b8);if(horizontal==0 && vertical==0) {S(0x364)=0;B(0x184)=1;select_sequence(2);return;}
            int direction=horizontal*C(0x104);if(direction>0 && vertical==0) {S(0x364)=0;B(0x184)=1;select_sequence(3);return;}
            if((direction>0 && vertical>0) || (direction==0 && vertical>0)) {S(0x364)=0;B(0x184)=1;select_sequence(6);return;}
            if(direction==0 && vertical<0) {S(0x364)=0;B(0x184)=4;F(0xf4)=0.0f;F(0xf8)=0.0f;select_sequence(9);return;}
        }
        if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}
        MOVE();goto alice_858_clamp;
    }
    case 2: {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && entryPhase==2) {F(0xf4)=30.0f;F(0xf8)=2.0f;}F(0xf4)-=3.0;if(F(0xf4)<=1.0f) F(0xf4)=1.0f;F(0xf8)-=0.5;if(F(0xf8)<0.5f) F(0xf8)=0.5f;
        if(S(0x140)>=2 && I(0x144)%2==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={F(0x378),0.0f,21.0f};spawn_unparented(858,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*100.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*100.0+F(0xf0)),B(0x104),1,packet,3);}
        void *owner=OWNER;int primary=FIELD(owner,int,0x6bc);
        if(primary!=0 && primary<4 && I(0x180)!=0) {int direction=FIELD(owner,int,0x6b4)*C(0x104);int vertical=FIELD(owner,int,0x6b8);if(direction>0 && vertical==0) {S(0x364)=0;B(0x184)=1;select_sequence(3);return;}if((direction>0 && vertical>0) || (direction==0 && vertical>0)) {S(0x364)=0;B(0x184)=1;select_sequence(6);return;}if(direction==0 && vertical<0) {S(0x364)=0;B(0x184)=4;F(0xf4)=0.0f;F(0xf8)=0.0f;select_sequence(9);return;}}
        if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);goto alice_858_clamp;
    }
    case 3:case 4:case 5: {
        if(entryPhase==4 && I(0x144)>=16) {next_sequence_block();return;}if(entryPhase>=4) {F(0xf4)-=3.0;if(F(0xf4)<=0.5f) F(0xf4)=0.5f;}
        void *owner=OWNER;if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}MOVE();goto alice_858_clamp;
    }
    case 6:
        F(0x12c)+=40.0;F(0xf4)-=1.0;if(F(0xf4)<0.0f) F(0xf4)=0.0f;if(F(0xf8)<=0.0f) {F(0xf8)+=1.0;if(F(0xf8)>0.0f) F(0xf8)=0.0f;}else {F(0xf8)-=1.0;if(F(0xf8)<0.0f) F(0xf8)=0.0f;}
        if(I(0x144)>=9) {F(0x12c)=0.0f;next_sequence_block();WAVE(7);float packet[3]={45.0f,25.0f,22.0f};spawn_unparented(858,static_cast<float>(static_cast<double>(105*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)-105.0),B(0x104),1,packet,3);float *parameters=PARAM;parameters[0]=45.0f;parameters[1]=35.0f;B(0x184)=1;I(0x180)=0;return;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);goto alice_858_clamp;
    case 7: {
        float *parameters=PARAM;parameters[1]-=2.0;if(parameters[1]<-0.5f) {parameters[1]=-0.5f;B(0x184)=0;}MOTION->set_components(PARAM[0],PARAM[1]);if(I(0x144)>=20) {next_sequence_block();return;}
        void *owner=OWNER;if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}MOVE();goto alice_858_clamp;
    }
    case 8: {
        float *parameters=PARAM;parameters[1]-=5.0;if(parameters[1]<-0.5f) {parameters[1]=-0.5f;B(0x184)=0;}MOTION->set_components(PARAM[0],PARAM[1]);if(I(0x144)>=30) {select_sequence(0);return;}
        void *owner=OWNER;if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}MOVE();goto alice_858_clamp;
    }
    case 9:
        F(0xf4)-=1.0;if(F(0xf4)<0.0f) F(0xf4)=0.0f;if(F(0xf8)<=0.0f) {F(0xf8)+=1.0;if(F(0xf8)>0.0f) F(0xf8)=0.0f;}else {F(0xf8)-=1.0;if(F(0xf8)<0.0f) F(0xf8)=0.0f;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);goto alice_858_clamp;
    case 10: {
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,23.0f};spawn_parented(858,F(0xec),F(0xf0),B(0x104),1,packet,3);}if(I(0x144)%15==0) WAVE(4);if(I(0x180)!=0 && ++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)>=45) {select_sequence(0);if(F(0xec)-FIELD(OWNER,float,0xec)>0.0f) C(0x104)=1;if(F(0xec)-FIELD(OWNER,float,0xec)<0.0f) C(0x104)=-1;return;}
        void *owner=OWNER;F(0xf8)*=static_cast<double>(0.95f);if(FIELD(owner,int,0x6c0)!=0 && FIELD(owner,int,0x6c0)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(11);return;}if(FIELD(owner,int,0x6c4)!=0 && FIELD(owner,int,0x6c4)<4 && I(0x180)!=0) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);
    }
alice_858_clamp:
        if(F(0xf0)<=0.0f) F(0xf0)=0.0f;if(F(0xec)>1260.0f) F(0xec)=1260.0f;if(F(0xec)<20.0f) F(0xec)=20.0f;break;
    case 11:F(0xf4)=0.0f;F(0xf8)=0.0f;S(0x364)=0;break;
    case 12:
        if(I(0x144)%3==0 && S(0x364)<=6) {WAVE(0);++S(0x364);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));F(0x378)=-atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);if(F(0x378)<-30.0f) F(0x378)=-30.0f;if(F(0x378)>30.0f) F(0x378)=30.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+F(0x378)-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(static_cast<double>(S(0x364)%7)+26.0);spawn_unparented(858,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);packet[2]=static_cast<float>(static_cast<double>(S(0x364)%7)+7.0);spawn_unparented(800,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);WAVE(0);
        }
        if(I(0x144)>=18 && FIELD(OWNER,int,0x6c4)!=0 && FIELD(OWNER,int,0x6c4)<4) {S(0x364)=0;B(0x184)=0;select_sequence(13);return;}if(I(0x144)>=40) select_sequence(0);break;
    case 13: {
        S(0x364)=0;void *owner=OWNER;if(FIELD(owner,int,0x6b4)*C(0x104)<=0) F(0xf4)=0.0f;else {F(0xf4)+=1.0;if(F(0xf4)>2.0f) F(0xf4)=2.0f;}
        if(FIELD(owner,int,0x6b8)<0) {F(0xf8)+=1.0;if(F(0xf8)>2.0f) F(0xf8)=2.0f;}if(FIELD(owner,int,0x6b8)>0) {F(0xf8)-=1.0;if(F(0xf8)<-2.0f) F(0xf8)=-2.0f;}if(FIELD(owner,int,0x6b8)==0) F(0xf8)=0.0f;MOVE();break;
    }
    case 14: {
        void *owner=OWNER;int direction=C(0x104)*FIELD(owner,int,0x6b4);if(direction>0) {F(0xf4)+=1.0;if(F(0xf4)>2.0f) F(0xf4)=2.0f;}else if(direction<0) {F(0xf4)-=1.0;if(F(0xf4)<-2.0f) F(0xf4)=-2.0f;}else F(0xf4)=0.0f;
        if(FIELD(owner,int,0x6b8)<0) {F(0xf8)+=1.0;if(F(0xf8)>2.0f) F(0xf8)=2.0f;}if(FIELD(owner,int,0x6b8)>0) {F(0xf8)-=1.0;if(F(0xf8)<-2.0f) F(0xf8)=-2.0f;}if(FIELD(owner,int,0x6b8)==0) F(0xf8)=0.0f;
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==14) {WAVE(9);float packet[3]={0.0f,0.0f,33.0f};spawn_parented(858,static_cast<float>(static_cast<double>(20*C(0x104))+F(0xec)),static_cast<float>(F(0xf0)+5.0),B(0x104),1,packet,3);}if(I(0x144)>=60) select_sequence(0);MOVE();break;
    }
    case 15:if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0x12c)+=15.0;if(B(0x113)<20) RETIRE();B(0x113)-=20;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 16:if(update_owner_tracking_and_proximity()) return;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
    case 20:if(update_flight_state(15)) return;break;
    case 21:F(0x11c)+=static_cast<double>(0.01f);F(0x120)*=static_cast<double>(0.8f);if(F(0x120)<=0.05f) RETIRE();MOTION->set_components(PARAM[0],15.0f);MOVE();break;
    case 22:F(0x11c)+=static_cast<double>(0.05f);F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();MOVE();break;
    case 23: {
        F(0x12c)+=25.0;if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
        if(FIELD(related,short,0x13e)==10) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>3.0f) F(0x11c)=2.5f;F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}else {if(B(0x113)<20) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;}MOVE();break;
    }
    case 24:if(!RELATED) RETIRE();{void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);short phase=FIELD(related,short,0x13e);if(phase==15 || phase==16) RETIRE();}break;
    case 26:case 27:case 28:case 29:case 30:case 31:case 32:
        if(S(0x140)==0) {if(emit_repeated(0,0,4)) RETIRE();if(I(0x180)!=0) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(S(0x13e)+7)};spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);return;}if(F(0xec)>1380.0f || F(0xec)<-100.0f || F(0xf0)>1000.0f || F(0xf0)<-160.0f) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}
        if(S(0x140)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}break;
    case 33:
        if(RELATED) {if(S(0x364)==0) {if(FIELD(RELATED,short,0x13e)!=14) S(0x364)=1;if(I(0x144)>=45) S(0x364)=1;else {void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(related,float,0xec));F(0xf0)=static_cast<float>(FIELD(related,float,0xf0)+5.0);F(0x11c)=static_cast<float>(static_cast<double>(I(0x144)&2)*static_cast<double>(0.2f)+1.0);F(0x120)=F(0x11c);}short action=FIELD(OWNER,short,0x13c);if(action>49 && action<150) RETIRE();}}else S(0x364)=1;
        if(S(0x364)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(!(F(0x11c)>=0.02f)) RETIRE();}break;
    case 34:
        if(RELATED) {
            if(S(0x364)<=1 && FIELD(RELATED,short,0x364)==1) S(0x364)=2;
            if(S(0x364)==0) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x120)+=static_cast<double>(0.1f);if(F(0x120)>0.75f) {F(0x120)=0.75f;S(0x364)=1;B(0x184)=10;return;}}
            if(S(0x364)==1) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=2;advance_six(0);if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}}
        }else S(0x364)=2;
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=static_cast<double>(0.85f);if(F(0x120)<=0.01f) RETIRE();}break;
    }
    advance_frame();
    if(I(0x144)==0) {if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) {select_sequence(0);return;}
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) {float packet[3]={0.0f,0.0f,22.0f};spawn_unparented(858,static_cast<float>(static_cast<double>(40*C(0x104))+F(0xec)),F(0xf0),B(0x104),1,packet,3);B(0x184)=1;I(0x180)=0;WAVE(29);F(0xf4)=40.0f;F(0xf8)=0.0f;}}
    if(I(0x144)==0) {if((S(0x142)==0 && S(0x140)==0 && S(0x13e)==6) || (S(0x142)==0 && S(0x140)==0 && S(0x13e)==9)) {select_sequence(0);return;}if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==10) {F(0xf8)=15.0f;S(0x364)=0;}}
    if(I(0x144)==0 && ((S(0x142)==0 && S(0x140)==0 && S(0x13e)==11) || (S(0x142)==0 && S(0x140)==0 && S(0x13e)==13) || (S(0x142)==0 && S(0x140)==0 && S(0x13e)==15))) {select_sequence(0);return;}
    if(S(0x13e)==2) {short frame=S(0x140);if(frame>=2 && frame<=6) {if(S(0x142)!=0) return;B(0x184)=1;if(I(0x180)!=0) S(0x364)=1;I(0x180)=0;}if(S(0x142)==0 && S(0x140)==8 && S(0x364)>0) I(0x180)=1;}return;
}


}
case 859: {
 {
    short entryPhase=S(0x13e);switch(entryPhase) {
    case 1:case 2: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=609 || FIELD(owner,short,0x13e)!=1) {select_sequence(3);return;}
        if(entryPhase==2) {advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x364)>4) {S(0x364)=0;B(0x184)=1;I(0x180)=0;}if(I(0x144)%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+5.0);packet[2]=6.0f;spawn_unparented(859,F(0xec),F(0xf0),B(0x104),-1,packet,3);}}break;
    }
    case 3:if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 4: {
        advance_six(0);advance_phase(0);void *owner=OWNER;if(FIELD(owner,short,0x13c)!=609 || FIELD(owner,short,0x13e)!=1) RETIRE();publish_bounds_descriptor(0,10,static_cast<int>(F(0x11c)*256.0),-10,static_cast<short>(static_cast<int>(F(0x12c))),0,0);if(update_flight_state(6)) return;if(I(0x180)!=0 && ++S(0x364)>4) {S(0x364)=0;B(0x184)=1;I(0x180)=0;}break;
    }
    case 5:
        if(S(0x364)!=0) {F(0x11c)*=static_cast<double>(0.98f);F(0x120)=F(0x11c);if(B(0x113)<6) RETIRE();B(0x113)-=6;B(0x110)-=6;B(0x111)-=6;}
        else if(RELATED && FIELD(RELATED,short,0x13e)==2) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}else S(0x364)=1;break;
    case 6:MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.95f);F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);if(B(0x113)<6) RETIRE();B(0x113)-=6;B(0x110)-=6;B(0x111)-=6;MOVE();break;
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(859,F(0xec),F(0xf0),B(0x104),-1,packet,3);}return;
}


}
case 900: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:
        if(FIELD(OWNER,short,0x174)<=0 || S(0x174)<-500) {select_sequence(2);return;}
        if(I(0x144)<60) {F(0xf8)*=static_cast<double>(0.9f);F(0xf4)=static_cast<float>(static_cast<double>(0.9f)*F(0xf4));F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)+=F(0xf8);break;}
        {next_sequence_block();WAVE(34);void *target=TARGET;float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));double aim=atan2_degrees(static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0)),dx);float *parameters=PARAM;parameters[0]=static_cast<float>(15.0-aim-static_cast<double>(RF(30)));parameters[1]=0.0f;if(parameters[0]>60.0f) parameters[0]=60.0f;if(parameters[0]<-60.0f) parameters[0]=-60.0f;}return;
    case 1: {
        if(FIELD(OWNER,short,0x174)<=0 || S(0x174)<-500) {select_sequence(2);return;}
        if(I(0x144)%3==0) {float packet[3]={0.0f,0.0f,6.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),-1,packet,3);}
        double nextY=static_cast<double>(F(0xf0))+F(0xf8);bool hit=stage_surface_height()>=nextY || S(0x174)<0;
        if(!hit) {double dySquared=square_float_value(static_cast<float>(FIELD(TARGET,float,0xf0)+100.0-F(0xf0)));hit=square_float_value(FIELD(TARGET,float,0xec)-F(0xec))+dySquared<=2500.0;}
        if(hit) {publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(6);F(0xf8)=static_cast<float>(static_cast<double>(RF(5))+8.0);F(0xf4)*=static_cast<double>(0.2f);return;}
        if(!(F(0xec)<=1580.0f && F(0xec)>=-300.0f && F(0xf0)<=1000.0f)) RETIRE();
        switch(g_match_identifier) {
        case 0:{turn_heading(0.0f,0.25f,100.0f);float *parameters=PARAM;parameters[1]+=static_cast<double>(0.3f);if(parameters[0]>90.0f) parameters[0]=90.0f;if(parameters[0]<-90.0f) parameters[0]=-90.0f;if(parameters[1]>=15.0f) parameters[1]=15.0f;break;}
        case 1:{turn_heading(0.0f,0.5f,100.0f);float *parameters=PARAM;parameters[1]+=static_cast<double>(0.3f);if(parameters[0]>90.0f) parameters[0]=90.0f;if(parameters[0]<-90.0f) parameters[0]=-90.0f;if(parameters[1]>=20.0f) parameters[1]=20.0f;break;}
        case 2:{turn_heading(0.0f,1.0f,100.0f);float *parameters=PARAM;parameters[1]+=static_cast<double>(0.4f);if(parameters[0]>90.0f) parameters[0]=90.0f;if(parameters[0]<-90.0f) parameters[0]=-90.0f;if(parameters[1]>=25.0f) parameters[1]=25.0f;break;}
        case 3:{turn_heading(0.0f,1.5f,100.0f);float *parameters=PARAM;parameters[1]+=0.5;if(parameters[0]>90.0f) parameters[0]=90.0f;if(parameters[0]<-90.0f) parameters[0]=-90.0f;if(parameters[1]>=30.0f) parameters[1]=30.0f;break;}
        }MOTION->set_components(PARAM[0],PARAM[1]);F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    }
    case 2:F(0x12c)+=15.0;if(B(0x113)<=5) RETIRE();B(0x113)-=5;F(0xf8)-=0.5;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);break;
    case 3:advance_six(0);advance_phase(0);F(0x11c)-=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;break;
    case 4:F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);if(I(0x144)>0) {if(B(0x110)>20) {if(B(0x113)<=20) RETIRE();B(0x111)=0;B(0x110)=0;B(0x113)-=20;}else {B(0x111)-=20;B(0x110)-=20;}}break;
    case 5:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(I(0x144)>=0) {if(B(0x110)<30) {B(0x111)=0;B(0x110)=0;}else {B(0x111)-=30;B(0x110)-=30;}if(B(0x113)<25) RETIRE();B(0x113)-=25;}break;
    case 6:F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    }FINISH();


}
case 901: {

    if(S(0x13e)==0) {
        if(S(0x174)<=-500 || FIELD(OWNER,short,0x174)<=0) select_sequence(1);
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,PARAM[3]==0.0f?3.0f:4.0f};spawn_parented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);}advance_six(0);if(I(0x180)!=0 && ++S(0x368)>=3) {S(0x368)=0;B(0x184)=1;I(0x180)=0;}
        if(S(0x364)==0) {float *parameters=PARAM;parameters[1]-=static_cast<double>(0.1f);if(parameters[1]<1.0f) {parameters[1]=1.0f;S(0x364)=1;}MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}
        if(S(0x364)==1) {if(++S(0x366)>=30) {B(0x184)=1;I(0x180)=0;S(0x364)=2;}MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}
        if(S(0x364)==2) {void *owner=OWNER;float *parameters=PARAM;float dx=FIELD(owner,float,0xec)-F(0xec);parameters[0]=-atan2_degrees(static_cast<float>(FIELD(owner,float,0xf0)+100.0-F(0xf0)),dx);parameters[1]+=0.25;if(F(0x370)>6.0f) F(0x370)=6.0f;MOTION->set_components(parameters[0],parameters[1]);owner=OWNER;F(0xec)=F(0xf4)+F(0xec);float nextY=F(0xf8)+F(0xf0);F(0xf0)=nextY;double dySquared=square_float_value(static_cast<float>(FIELD(owner,float,0xf0)+100.0-nextY));if(square_float_value(FIELD(OWNER,float,0xec)-F(0xec))+dySquared<=400.0) RETIRE();}
    }
    if(S(0x13e)==1) {if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==2 && update_flight_state(1)) return;
    short phase=S(0x13e);if(phase==3 || phase==4) {
        if(RELATED) {void *related=RELATED;if(FIELD(related,short,0x13e)==0) {F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>2.5f) F(0x11c)=2.0f;F(0x120)=F(0x11c);if(B(0x113)>225) B(0x113)=255;else B(0x113)+=30;}else {if(B(0x113)<10) RETIRE();F(0x11c)+=static_cast<double>(0.1f);B(0x113)-=10;}}
        else {if(B(0x113)<15) RETIRE();F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);B(0x113)-=15;}F(0x12c)+=25.0;
    }FINISH();


}
case 902: {
 {
    short phase=S(0x13e);if(phase<=3 && FIELD(OWNER,short,0x174)<=0) {select_sequence(4);return;}
    switch(phase) {
    case 0:case 1: {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);MOTION->set_components(parameters[0],parameters[1]);F(0x12c)+=25.0;F(0xec)=F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;}
    case 2: {
        if(I(0x144)>=400) {next_sequence_block();return;}
        float dx=F(0xec)-F(0x370);float dy=F(0xf0)-F(0x374);float radius=sqrt_float_value(dy*dy+dx*dx);F(0xf4)=static_cast<float>((dx-dy*static_cast<double>(C(0x104))*3.0)/radius);F(0xf8)=static_cast<float>((dy-dx*static_cast<double>(C(0x104))*-3.0)/radius);float angle=static_cast<float>(90.0-atan2_degrees(F(0xf8),static_cast<float>(static_cast<double>(C(0x104))*F(0xf4))));PARAM[0]=angle;F(0x12c)=angle;
        if(I(0x144)%2==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(90))+PARAM[0]-45.0);float packet[3]={F(0x378),0.0f,5.0f};spawn_unparented(902,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*100.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*100.0+F(0xf0)),B(0x104),1,packet,3);}
        switch(g_match_identifier) {
        case 0:if(I(0x144)%6==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(20))+PARAM[0]-10.0);float packet[3];packet[0]=F(0x378);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(S(0x368)%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*50.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*50.0+F(0xf0)),B(0x104),1,packet,3);++S(0x368);WAVE(0);}break;
        case 1:if(I(0x144)%6==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(20))+PARAM[0]-10.0);float packet[3];packet[0]=F(0x378);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(S(0x368)%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*50.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*50.0+F(0xf0)),B(0x104),1,packet,3);++S(0x368);WAVE(0);}break;
        case 2:if(I(0x144)%6==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(20))+PARAM[0]-10.0);float packet[3];packet[0]=F(0x378);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(S(0x368)%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*50.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*50.0+F(0xf0)),B(0x104),1,packet,3);++S(0x368);WAVE(0);}break;
        case 3:if(I(0x144)%6==0) {F(0x378)=static_cast<float>(static_cast<double>(RF(20))+PARAM[0]-10.0);float packet[3];packet[0]=F(0x378);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(S(0x368)%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x378))*50.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x378))*50.0+F(0xf0)),B(0x104),1,packet,3);++S(0x368);WAVE(0);}break;
        }
        if(I(0x180)!=0 && ++S(0x364)>=5) {S(0x364)=0;B(0x184)=1;I(0x180)=0;}F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);break;
    }
    case 3: {float dx=F(0xec)-F(0x370);float dy=F(0xf0)-F(0x374);float radius=sqrt_float_value(dy*dy+dx*dx);F(0xf4)=static_cast<float>((dx-static_cast<double>(C(0x104))*dy*3.0)/radius);F(0xf8)=static_cast<float>((dy-dx*static_cast<double>(C(0x104))*-3.0)/radius);float angle=static_cast<float>(90.0-atan2_degrees(F(0xf8),static_cast<float>(static_cast<double>(C(0x104))*F(0xf4))));PARAM[0]=angle;F(0x12c)=angle;if(B(0x113)<5) RETIRE();B(0x113)-=5;break;}
    case 4:if(F(0xf4)>5.0f) F(0xf4)=5.0f;if(F(0xf4)<-5.0f) F(0xf4)=-5.0f;if(F(0xf8)>5.0f) F(0xf8)=5.0f;if(F(0xf8)<-5.0f) F(0xf8)=-5.0f;F(0xf8)-=0.5;F(0xec)=F(0xf4)+F(0xec);F(0xf0)+=F(0xf8);F(0x12c)+=15.0;if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 5:F(0x11c)+=static_cast<double>(0.01f);F(0x120)*=static_cast<double>(0.8f);if(F(0x120)<=0.05f) RETIRE();MOTION->set_components(PARAM[0],15.0f);MOVE();break;
    }FINISH();
}


}
case 903: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();
    if(S(0x13e)>6) {F(0x11c)*=static_cast<double>(0.9f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;}
    else {if(S(0x140)==0) {if(collision!=0 || I(0x144)>=60) {next_sequence_frame();return;}if(F(0xec)>1380.0f || F(0xec)<-100.0f || F(0xf0)>1000.0f || F(0xf0)<-160.0f) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}if(S(0x140)==1) {F(0x11c)*=static_cast<double>(0.85f);F(0x120)=F(0x11c);if(B(0x113)<=20) RETIRE();B(0x113)-=20;}}FINISH();
}


}
case 980: {
update_ping_pong_motion();FINISH();


}
case 998: {

    if(S(0x13e)==0) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action>153 && action<158) {F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+60.0);}
        action=FIELD(owner,short,0x13c);if(action>149 && action<154) {F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);}
        if(FIELD(owner,short,0x13c)==158) {F(0xec)=static_cast<float>(static_cast<double>(60*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}
        action=FIELD(owner,short,0x13c);if(action<150 || action>158) {next_sequence_block();FIELD(OWNER,unsigned char,0x751)=0;}
    }
    if(S(0x13e)==1) {if(B(0x113)<10) RETIRE();B(0x111)-=10;B(0x110)-=10;B(0x113)-=10;}FINISH();


}
case 999: {
 {
    short phase=S(0x13e);switch(phase) {
    case 0: {F(0xf8)-=static_cast<double>(0.3f);float nextY=F(0xf8)+F(0xf0);if(!(stage_surface_height()<nextY)) {FIELD(OWNER,short,0x78c)=1;F(0xf0)=stage_surface_height();F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x100)=0.0f;select_sequence(1);return;}break;}
    case 2:if(FIELD(OWNER,short,0x78e)==1) {next_sequence_block();B(0x104)=1;return;}break;
    case 3:case 4:if(phase>=4) F(0xf8)-=F(0x100);break;
    }
    F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)+=F(0xf8);if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) {F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}return;
}

}
default:advance_frame();return;
}
}
}
