// Complete manual JP1.06a PatchouliObject update hypothesis, 00520890.
#include "characters/PatchouliObjectUpdate.hpp"
namespace th105 {
#define FIELD(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) FIELD(this,float,o)
#define I(o) FIELD(this,int,o)
#define S(o) FIELD(this,short,o)
#define B(o) FIELD(this,unsigned char,o)
#define C(o) FIELD(this,signed char,o)
#define PARAM FIELD(this,float*,0x340)
#define OWNER FIELD(this,void*,0x348)
#define RELATED FIELD(this,void*,0x34c)
#define TARGET FIELD(this,void*,0x170)
#define MOTION reinterpret_cast<PatchouliUpdateMotionView*>(reinterpret_cast<unsigned char*>(this)+4)
#define WAVE(n) reinterpret_cast<PatchouliUpdateOwnerView*>(OWNER)->dispatch_character_wave_handle(n)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define RETIRE() do { --I(0x330); return; } while(0)
#define MOVE() do {F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}while(0)
#define FINISH() do {if(advance_frame()) --I(0x330);return;}while(0)
void PatchouliObjectUpdateView::update_action_state() {
switch(S(0x13c)) {
case 800: {

    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1240.0 || F(0xf0)<-240.0 || I(0x180)==5) RETIRE();
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0) replace_secondary(991,10.0f,10,1,2);
    switch(S(0x13e)) {
    case 0:
        if(S(0x140)<=1) {
            if(emit_repeated(0,0,5)) RETIRE();turn_heading(0.0f,0.5f,100.0f);
            float *parameters=PARAM;MOTION->set_components(parameters[0],static_cast<float>(S(0x364)*static_cast<double>(0.1f)+parameters[1]));
            F(0x11c)=static_cast<float>((MOTION->selector_random_range(0,4)-2)*0.05+1.0);F(0x120)=F(0x11c);
            advance_six(3);advance_phase(3);
            if(I(0x180)!=0 && S(0x140)==1) {
                F(0xf4)=0.0f;F(0xf8)=0.0f;select_frame(2);release_secondary();
                for(int count=6;count!=0;--count) {
                    float packet[3];packet[0]=RF(360);float speed=static_cast<float>(RF(70)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+8.0);packet[2]=1.0f;
                    spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
                }
                return;
            }
        }
        if(S(0x140)==2) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)*=0.99f;F(0x120)=0.99f*F(0x120);
            if(B(0x113)<10) {B(0x113)=0;RETIRE();}B(0x113)-=10;
        }
        S(0x364)+=2;MOVE();break;
    case 1: {
        float *parameters=PARAM;F(0x11c)*=0.95f;F(0x120)=0.95f*F(0x120);MOTION->set_components(parameters[0],parameters[1]);
        parameters=PARAM;parameters[1]-=0.25;if(parameters[1]<0.5f) parameters[1]=0.5f;
        if(B(0x113)<20) {B(0x113)=0;RETIRE();}B(0x113)-=20;MOVE();break;
    }
    case 2: {
        F(0x12c)+=12.5;if(advance_six(5)) B(0x184)=0;
        float *parameters=PARAM;parameters[1]-=0.75;if(parameters[1]<=2.0f) parameters[1]=2.0f;MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x180)!=0 && ++S(0x364)>=5) {S(0x364)=0;I(0x180)=0;}
        if(C(0x184)<=0) {
            F(0x11c)*=0.9f;F(0x120)=F(0x11c);if(B(0x113)<20) {B(0x113)=0;RETIRE();}B(0x113)-=20;
        }else {
            if(emit_repeated(0,0,5)) RETIRE();if(I(0x144)>=60) B(0x184)=0;
            if(I(0x144)%10==0) {float packet[3]={F(0x12c),0.2f,3.0f};spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        }
        MOVE();break;
    }
    case 3:
        F(0x11c)+=0.1f;F(0x120)=F(0x11c);F(0x12c)+=12.5;
        if(B(0x113)<20) {B(0x113)=0;RETIRE();}B(0x113)-=20;MOVE();break;
    }
    if(advance_frame()) RETIRE();
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 801: {

    if(I(0x180)==5) RETIRE();
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,0,4)) RETIRE();F(0x370)+=static_cast<double>(0.3f);turn_heading(0.0f,2.0f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]+F(0x370));advance_six(0);advance_phase(2);
        if(S(0x142)>=180 || I(0x180)!=0) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;select_sequence(3);float packet[3]={0.0f,0.0f,4.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }break;
    }
    case 2:F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.8f);goto patchouli_801_fade15;
    case 3:F(0x11c)-=static_cast<double>(0.02f);F(0x120)=F(0x11c);
patchouli_801_fade15:
        if(B(0x113)<15) RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x110)-=15;break;
    case 4:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<25) RETIRE();B(0x113)-=25;B(0x111)-=25;B(0x110)-=25;break;
    case 5: {
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]+F(0x370));
        double nextY=static_cast<double>(F(0xf8))+F(0xf0);
        if(I(0x180)!=0 || stage_surface_height()>=nextY) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;select_sequence(3);float packet[3]={0.0f,0.0f,4.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }break;
    }
    case 6:
        if(S(0x140)==0) {
            if(emit_repeated(0,0,4)) RETIRE();advance_six(3);
            if(I(0x180)!=0) {
                F(0xf4)=0.0f;F(0xf8)=0.0f;select_frame(1);F(0x11c)=2.0f;F(0x120)=2.0f;
                float packet[3];packet[2]=8.0f;
                for(int count=3;count!=0;--count) {packet[0]=RF(360);float speed=static_cast<float>(RF(20)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+4.0);spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
            }
        }
        if(S(0x140)==1) {F(0x11c)*=0.99f;F(0x120)=0.99f*F(0x120);if(B(0x113)<30) {B(0x113)=0;RETIRE();}B(0x113)-=30;}break;
    case 7:F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<30) RETIRE();B(0x113)-=30;B(0x111)-=30;B(0x112)-=30;break;
    case 8:
        F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.3f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;
        if(I(0x144)>=30) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 9:
        if(emit_repeated(0,3,5)) RETIRE();advance_six(0);F(0xf4)-=0.25;if(F(0xf4)<1.0f) F(0xf4)=1.0f;F(0xf8)+=static_cast<double>(0.2f);if(F(0xf8)>2.0f) F(0xf8)=2.0f;
        if(I(0x144)>=60 || C(0x184)<=0) RETIRE();if(I(0x180)!=0 && ++S(0x364)>=5) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(5))+5.0);packet[2]=10.0f;spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);}break;
    case 10: {
        float *parameters=PARAM;F(0x12c)=F(0x370)+F(0x12c);F(0x374)+=static_cast<double>(0.1f);F(0x370)*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);
        parameters[1]-=0.25;if(parameters[1]<0.0f) parameters[1]=0.0f;MOTION->set_components(parameters[0],parameters[1]);F(0xf8)+=F(0x374);
        if(I(0x144)>=10) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}break;
    }
    }
    MOVE();FINISH();


}
case 810: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(emit_repeated(0,3,5)) RETIRE();
        if(I(0x144)%6==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[2]=5.0f;
            spawn_unparented(810,static_cast<float>(static_cast<double>(RF(100))+F(0xec)-50.0),static_cast<float>(static_cast<double>(RF(100))+F(0xf0)-50.0),B(0x104),1,packet,3);
        }
        advance_six(0);advance_phase(10);
        if(I(0x180)!=0 || stage_surface_height()>=static_cast<double>(F(0xf0))) {
            WAVE(4);float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=3.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
    }
    if(S(0x13e)==1) {
        if(emit_repeated(0,3,5)) RETIRE();advance_six(0);advance_phase(3);
        if(I(0x180)!=0 || stage_surface_height()>=static_cast<double>(F(0xf0))) {
            WAVE(4);float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=3.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
    }
    if(S(0x13e)==2) {
        F(0x11c)-=static_cast<double>(0.01f);F(0x120)-=static_cast<double>(0.01f);
        if(I(0x144)>10) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;if(B(0x110)>20) {B(0x110)-=20;B(0x111)-=20;}}
    }
    if(S(0x13e)==3) {
        F(0x11c)=static_cast<float>(lookup_orientation_cosine(3*I(0x144))*static_cast<double>(0.1f)+F(0x11c));F(0x120)=F(0x11c);
        if(B(0x111)>10) {B(0x110)-=10;B(0x111)-=10;}
        if(I(0x144)>10) {if(B(0x113)<=15) RETIRE();B(0x113)-=15;}
    }
    if(S(0x13e)==5) {
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.92f);F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);
        if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;F(0xf8)+=static_cast<double>(0.1f);
    }
    if(S(0x13e)==6) {
        if(emit_repeated(0,3,5)) RETIRE();
        if(FIELD(OWNER,signed char,0x604)>3) {
            if(I(0x144)%5==0) {
                float packet[3];packet[0]=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6.0))*70.0-F(0x12c));packet[1]=15.0f;packet[2]=7.0f;
                spawn_unparented(810,F(0xec),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6.0))*50.0+F(0xf0)),static_cast<unsigned char>(-B(0x104)),1,packet,3);
                packet[0]=-packet[0]-F(0x12c);packet[1]=15.0f;packet[2]=7.0f;
                spawn_unparented(810,F(0xec),static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-static_cast<float>(I(0x144)))*6.0f)*50.0+F(0xf0)),static_cast<unsigned char>(-B(0x104)),1,packet,3);
            }
        }else if(I(0x144)%6==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[2]=5.0f;
            spawn_unparented(810,static_cast<float>(static_cast<double>(RF(100))+F(0xec)-50.0),static_cast<float>(static_cast<double>(RF(100))+F(0xf0)-50.0),B(0x104),1,packet,3);
        }
        advance_six(0);advance_phase(10);
        if(I(0x180)!=0 || stage_surface_height()>=static_cast<double>(F(0xf0))) {
            WAVE(4);float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=3.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
    }
    if(S(0x13e)==7) {
        float *parameters=PARAM;F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);MOTION->set_components(parameters[0],parameters[1]);PARAM[1]*=static_cast<double>(0.95f);
        if(I(0x144)>=15) {B(0x184)=0;if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);return;


}
case 811: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        int lower=static_cast<int>(F(0x11c)*-20.0);publish_bounds_descriptor(lower,static_cast<int>(F(0x11c)*20.0),static_cast<int>(F(0x11c)*20.0),lower,0,0,0);
        if(emit_repeated(0,0,2)) RETIRE();F(0xf4)-=0.25;if(F(0xf4)<1.0f) F(0xf4)=1.0f;F(0xf8)+=static_cast<double>(0.2f);if(F(0xf8)>4.0f) F(0xf8)=4.0f;
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);
        if(I(0x144)<45 && C(0x184)>0) {F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);}
        else {B(0x184)=0;if(B(0x111)>=10) {B(0x111)-=10;B(0x110)-=10;}else {if(B(0x113)<10) RETIRE();B(0x113)-=10;}}
        MOVE();
    }
    FINISH();


}
case 815: {

    if(S(0x13e)==0) {
        if(F(0xf8)>0.0f) {F(0xf8)-=2.0;if(F(0xf8)<0.0f) F(0xf8)=0.0f;}
        if(emit_repeated(0,0,0)) {next_sequence_block();B(0x184)=0;}
        if(I(0x144)%15==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(815,F(0xec),stage_surface_height(),B(0x104),1,packet,3);packet[2]=3.0f;spawn_unparented(815,F(0xec),stage_surface_height(),B(0x104),-1,packet,3);}
        advance_six(0);if(I(0x180)!=0 && C(0x184)>0 && ++S(0x366)>15) {S(0x366)=0;I(0x180)=0;}
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(I(0x144)>10*(FIELD(owner,signed char,0x605)+5) || ((action==520 || action==521) && FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0)) {next_sequence_block();B(0x184)=0;}
    }
    if(S(0x13e)==1) {F(0x11c)*=static_cast<double>(0.95f);F(0xf8)=-2.0f;if(B(0x113)<15) RETIRE();B(0x113)-=15;}
    if(S(0x13e)==2) {
        F(0x11c)+=static_cast<double>(0.05f);if(F(0x370)>0.0f) F(0x370)-=static_cast<double>(0.1f);
        if(!(F(0x370)>0.0f)) {F(0x370)=0.0f;if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        float scale=F(0x120)+F(0x370);F(0x120)=static_cast<float>(scale*static_cast<double>(0.98f));
    }
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.025f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==4) {
        if(emit_repeated(0,0,0)) RETIRE();F(0xf4)=0.0f;F(0xf8)=0.0f;
        if(I(0x144)%10==0) {float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(815,F(0xec),stage_surface_height(),B(0x104),-1,packet,3);}
        if(!(PARAM[1]>=static_cast<double>(I(0x144)))) {
            WAVE(5);float packet[3]={0.0f,0.0f,0.0f};spawn_unparented(815,F(0xec),static_cast<float>(stage_surface_height()-800.0),B(0x104),-1,packet,3);
            for(int count=6;count!=0;--count) {packet[0]=static_cast<float>(-60.0-static_cast<double>(RF(60)));packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=5.0f;spawn_unparented(815,F(0xec),stage_surface_height(),B(0x104),-1,packet,3);}RETIRE();
        }
    }
    if(S(0x13e)==5) {F(0xf4)*=static_cast<double>(0.95f);F(0xf8)-=static_cast<double>(0.35f);if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}
    MOVE();if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);return;


}
case 816: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        F(0xf4)=F(0x370);float wave=lookup_orientation_sine(2*I(0x144));F(0xf8)=wave+wave+F(0x374);F(0x370)*=static_cast<double>(0.98f);F(0x374)=static_cast<float>(static_cast<double>(0.98f)*F(0x374));
        if(S(0x140)==0) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);}
        if(S(0x140)==1 && ++S(0x36c)>=180) {
            WAVE(13);float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            if(FIELD(OWNER,signed char,0x60a)<2) RETIRE();

            for(float index=0.0f;index<6.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*60.0);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=5.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        if(S(0x174)<0) {WAVE(13);next_sequence_block();float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            F(0xf4)=0.0f;F(0xf8)=0.0f;return;
        }break;
    }
    case 1:case 4:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 2:if(I(0x144)>=20) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}F(0xf8)-=0.25;F(0xf4)*=static_cast<double>(0.98f);break;
    case 3: {
        F(0xf4)=F(0x370);float wave=lookup_orientation_sine(2*I(0x144));F(0xf8)=wave+wave+F(0x374);F(0x370)*=static_cast<double>(0.98f);F(0x374)=static_cast<float>(static_cast<double>(0.98f)*F(0x374));
        if(S(0x140)==0) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);}
        if(S(0x140)==1 && ++S(0x36c)>=180) {
            WAVE(13);float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }

            for(float index=0.0f;index<8.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*45.0);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=6.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        if(S(0x174)<0) {WAVE(13);next_sequence_block();float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            F(0xf4)=0.0f;F(0xf8)=0.0f;return;
        }break;
    }
    case 5: {
        if(S(0x140)==0) {if(emit_repeated(0,0,4)) RETIRE();if(FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0) {next_sequence_frame();return;}}
        if(S(0x140)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);if(parameters[1]<3.0f) parameters[1]=3.0f;
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || !(F(0xf0)>=-200.0f)) RETIRE();break;
    }
    case 6: {
        if(S(0x140)==0) {if(emit_repeated(0,0,4)) RETIRE();if(FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0) {next_sequence_frame();return;}}
        if(S(0x140)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);if(parameters[1]<6.0f) parameters[1]=6.0f;
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || !(F(0xf0)>=-200.0f)) RETIRE();break;
    }
    }
    F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);if(advance_frame()) --I(0x330);
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) {WAVE(13);
float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    }
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) {WAVE(13);
float packet[3];
            for(float index=0.0f;index<12.0f;index+=1.0) {
                packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=2.0f;
                spawn_unparented(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);
            }
        --I(0x330);
    }return;


}
case 820: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {F(0x11c)+=static_cast<double>(0.01f);F(0x120)+=static_cast<double>(0.01f);if(B(0x113)<=5) RETIRE();B(0x113)-=5;MOTION->set_components(PARAM[0],PARAM[1]);F(0xf8)*=0.25;}
    if(S(0x13e)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;if(F(0x370)<0.5f) F(0x370)=0.5f;F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.03f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==2) {
        advance_six(6);if(C(0x184)<=0 || I(0x144)>=60) {B(0x184)=0;next_sequence_block();float *parameters=PARAM;parameters[1]=2.0f;MOTION->set_components(parameters[0],2.0f);return;}
        float *parameters=PARAM;parameters[1]*=static_cast<double>(0.95f);if(parameters[1]<=2.0f) parameters[1]=2.0f;MOTION->set_components(parameters[0],parameters[1]);
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)!=0) return;
    if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) RETIRE();if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==4) --I(0x330);return;


}
case 821: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        position_relative_to_owner(100,110);F(0x12c)+=5.0;
        if(I(0x144)%5==0) {float packet[3]={RF(360),15.0f,2.0f};spawn_parented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%20==0) {float packet[3]={static_cast<float>(I(0x144)),0.0f,1.0f};spawn_parented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action!=545 && action!=546) {float packet[3]={0.2f,0.0f,4.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();}
        if(FIELD(owner,short,0x13e)==3) {float packet[3]={0.2f,0.0f,4.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();}
        if(FIELD(owner,short,0x13e)==2) {
            float packet[3]={0.2f,5.0f,4.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[0]=0.4f;packet[1]=7.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[0]=0.6f;packet[1]=9.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[0]=0.0f;packet[1]=100.0f;packet[2]=3.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(15);
            for(float index=0.0f;index<8.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*45.0);packet[1]=15.0f;packet[2]=7.0f;spawn_unparented(821,F(0xec),stage_surface_height(),B(0x104),packet[0]>180.0f?-1:1,packet,3);}RETIRE();
        }break;
    }
    case 1: {
        if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x12c)-=5.0;F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);
        if(B(0x113)<=245) B(0x113)+=10;if(!(F(0x11c)>=0.1f)) RETIRE();break;
    }
    case 2:MOTION->set_components(PARAM[0],PARAM[1]);if(B(0x113)<15) RETIRE();B(0x113)-=15;MOVE();break;
    case 3: {
        MOTION->set_components(PARAM[0],PARAM[1]);if(emit_repeated(0,3,7)) RETIRE();
        float packet[3]={RF(360),2.0f,5.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[0]=RF(360);packet[1]=1.0f;spawn_unparented(821,static_cast<float>(F(0xec)-static_cast<double>(50*C(0x104))),F(0xf0),B(0x104),1,packet,3);
        if(FIELD(OWNER,signed char,0x60b)>=3 && (I(0x180)==4 || I(0x180)==8)) {
            float burst[3]={0.0f,0.5f,6.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,burst,3);burst[0]=40.0f;burst[1]=15.0f;if(FIELD(OWNER,signed char,0x60b)>=4) burst[1]=30.0f;burst[2]=8.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,burst,3);
            for(float index=0.0f;index<3.0f;index+=1.0) {burst[1]=3.0f;burst[2]=9.0f;spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,burst,3);}
            for(float index=0.0f;index<8.0f;index+=1.0) {burst[0]=static_cast<float>(static_cast<double>(RF(20))+index*45.0);burst[1]=15.0f;burst[2]=7.0f;spawn_unparented(821,F(0xec),stage_surface_height(),B(0x104),burst[0]>180.0f?-1:1,burst,3);}RETIRE();
        }
        if(I(0x180)!=0) {
            float burst[3]={0.0f,0.5f,6.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,burst,3);
            for(float index=0.0f;index<8.0f;index+=1.0) {burst[0]=static_cast<float>(static_cast<double>(RF(20))+index*45.0);burst[1]=15.0f;burst[2]=7.0f;spawn_unparented(821,F(0xec),stage_surface_height(),B(0x104),burst[0]>180.0f?-1:1,burst,3);}RETIRE();
        }
        F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);break;
    }
    case 4: {
        MOTION->set_components(0.0f,PARAM[1]);float *parameters=PARAM;F(0x11c)=parameters[0]+F(0x11c);F(0x120)=F(0x11c);parameters[0]*=static_cast<double>(0.9f);parameters[1]=static_cast<float>(static_cast<double>(0.9f)*parameters[1]);if(B(0x113)<5) RETIRE();B(0x113)-=5;MOVE();break;
    }
    case 5:MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.98f);if(B(0x113)<5) RETIRE();B(0x113)-=5;MOVE();break;
    case 6: {
        float *parameters=PARAM;F(0x12c)+=20.0;F(0x11c)=parameters[1]+F(0x11c);F(0x120)=F(0x11c);parameters[1]*=static_cast<double>(0.9f);if(B(0x113)<10) RETIRE();B(0x113)-=10;MOVE();break;
    }
    case 7:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.95f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);if(I(0x144)>=10) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    case 8: {
        float *parameters=PARAM;F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*parameters[1]+F(0xec));parameters[1]*=static_cast<double>(0.85f);if(parameters[1]<0.5f) parameters[1]=0.5f;
        if(S(0x140)>=1) RETIRE();if(parameters[0]<=static_cast<double>(I(0x144))) {next_sequence_frame();return;}
        if(I(0x144)%15==0) {float packet[3]={0.0f,3.0f,9.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);}advance_six(0);advance_phase(0);break;
    }
    case 9: {
        float *parameters=PARAM;F(0x11c)=static_cast<float>(4.0-parameters[1]);F(0x120)=F(0x11c);parameters[1]*=static_cast<double>(0.95f);F(0x12c)-=27.0;if(I(0x144)>=5) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}break;
    }
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);return;


}
case 825: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,0,0)) S(0x364)=2;void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action!=560 && action!=561) || FIELD(owner,short,0x730)==2) S(0x364)=2;
        if(S(0x364)<=1) {owner=OWNER;F(0xec)=FIELD(owner,float,0xec)+F(0x370);F(0xf0)=FIELD(owner,float,0xf0)+F(0x374);}
        if(S(0x364)==0) {if(B(0x113)>235) {B(0x113)=255;S(0x364)=1;}else B(0x113)+=20;}
        if(S(0x364)==1) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        if(S(0x364)==2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}break;
    }
    case 1:F(0x11c)+=static_cast<double>(0.15f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 2: {
        if(emit_repeated(0,1,2)) RETIRE();void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action==560 || action==561) {
            if(FIELD(owner,short,0x730)==2) {float packet[3]={PARAM[0],0.0f,1.0f};spawn_unparented(825,F(0xec),F(0xf0),B(0x104),1,packet,3);next_sequence_block();B(0x113)=255;return;}
        }else S(0x364)=2;
        if(S(0x364)<=1) {owner=OWNER;F(0xec)=FIELD(owner,float,0xec)+F(0x370);F(0xf0)=FIELD(owner,float,0xf0)+F(0x374);}
        if(S(0x364)==0) {if(B(0x113)>235) B(0x113)=255;else B(0x113)+=20;}
        if(S(0x364)==1) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        if(S(0x364)==2) {if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    }
    case 3: {
        advance_six(0);if(emit_repeated(0,1,2)) RETIRE();
        if(C(0x184)>0) {float packet[3]={PARAM[0],0.0f,4.0f};spawn_unparented(825,F(0xec),F(0xf0),B(0x104),-1,packet,3);}
        else {F(0x120)*=static_cast<double>(0.9f);F(0x11c)+=static_cast<double>(0.1f);if(B(0x113)<15) RETIRE();B(0x113)-=15;PARAM[1]*=static_cast<double>(0.95f);}
        float *parameters=PARAM;MOTION->set_components(parameters[0],static_cast<float>((lookup_orientation_cosine_quantized_abs(parameters[0])*0.5+0.5)*parameters[1]));
        if(S(0x364)==0) {
            if(I(0x180)==1 || I(0x180)==7 || I(0x180)==2) {void *owner=OWNER;if(FIELD(owner,signed char,0x607)>=4) {FIELD(owner,short,0x7b0)=2;S(0x364)=1;}}
            if(S(0x364)==0 && FIELD(OWNER,short,0x7b0)!=0) {select_sequence(5);B(0x184)=0;I(0x180)=0;F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
        }
        MOVE();break;
    }
    case 4:F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 5:
        if(S(0x140)!=0) {MOTION->set_components(F(0x378),F(0x374));F(0x374)+=2.0;float packet[3]={F(0x378),0.0f,4.0f};spawn_unparented(825,F(0xec),F(0xf0),B(0x104),-1,packet,3);}else F(0x12c)+=35.0;
        MOVE();break;
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();if(advance_frame()) RETIRE();
    if(S(0x13e)==5 && S(0x142)==0 && S(0x140)==1) {
        void *target=FIELD(this,void*,0x170);float dx=static_cast<float>((FIELD(target,float,0xec)-static_cast<double>(F(0xec)))*C(0x104));float dy=static_cast<float>(FIELD(target,float,0xf0)+100.0-F(0xf0));
        F(0x378)=-atan2_degrees(dy,dx);F(0x12c)=F(0x378);F(0x374)=20.0f;B(0x184)=1;I(0x180)=0;
    }return;


}
case 826: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        F(0x12c)+=60.0;if(emit_repeated(0,1,5)) RETIRE();
        if(I(0x144)%5==0) {float packet[3]={F(0x12c),0.0f,2.0f};spawn_unparented(826,F(0xec),F(0xf0),B(0x104),-1,packet,3);}
        if(F(0xf0)<=0.0f && F(0xf8)<0.0f) F(0xf8)=-F(0xf8);advance_six(0);if(C(0x184)<=0) RETIRE();if(I(0x180)!=0) I(0x180)=0;MOVE();
    }else if(S(0x13e)==1) {if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x12c)=FIELD(related,float,0x12c);}
    else if(S(0x13e)==2) {F(0x12c)+=60.0;F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);if(B(0x112)<25) {if(B(0x113)<25) RETIRE();B(0x113)-=25;}else {B(0x112)-=25;B(0x111)-=25;}}
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);return;


}
case 827: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        F(0xf8)-=static_cast<double>(0.1f);if(F(0xf8)<=0.0f) F(0xf8)=0.0f;if(emit_repeated(0,0,5)) RETIRE();F(0x370)+=3.0;if(F(0x370)>90.0f) F(0x370)=90.0f;
        F(0x12c)=static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x370))*360.0+PARAM[0]);if(I(0x144)>=60) {F(0xf8)=0.0f;next_sequence_block();return;}
    }
    if(S(0x13e)==1) {
        MOTION->set_components(PARAM[0],PARAM[1]);FIELD(FIELD(this,void*,0x154),float,0xe8)=F(0xec);FIELD(FIELD(this,void*,0x154),float,0xec)=stage_surface_height();advance_six(0);
        double currentY=F(0xf0);if(stage_surface_height()>=currentY) {F(0xf8)=0.0f;F(0xf4)=0.0f;next_sequence_block();return;}
        if(emit_repeated(0,0,5)) RETIRE();float *parameters=PARAM;parameters[1]+=1.0;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);if(I(0x180)==6) {++B(0x184);I(0x180)=0;}
    }
    if(S(0x13e)==2) {FIELD(FIELD(this,void*,0x154),float,0xe8)=F(0xec);FIELD(FIELD(this,void*,0x154),float,0xec)=stage_surface_height();if(B(0x113)<5) RETIRE();B(0x113)-=5;}
    if(S(0x13e)==3) {if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=static_cast<float>(static_cast<double>(FIELD(related,signed char,0x104))*FIELD(related,float,0xf4)+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf8)+FIELD(related,float,0xf0);F(0x12c)=FIELD(related,float,0x12c);if(B(0x113)<5) RETIRE();B(0x113)-=5;}
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();


}
case 830: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(emit_repeated(0,1,5)) RETIRE();if(!(F(0xf0)<1300.0f)) {float *parameters=PARAM;if(parameters[3]<=0.0f) {next_sequence_block();F(0xf0)=1300.0f;F(0x12c)=0.0f;F(0xf8)=-20.0f;release_auxiliary();return;}parameters[3]-=1.0;}
    }
    if(S(0x13e)==1) {
        F(0xf8)-=0.75;if(emit_repeated(0,1,5)) RETIRE();advance_six(0);double nextY=static_cast<double>(F(0xf8))+F(0xf0);
        if(stage_surface_height()+50.0>=nextY || I(0x180)!=0) {
            WAVE(10);for(float index=0.0f;index<4.0f;index+=1.0) {float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(10))-(index*40.0+20.0)-5.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=5.0f;spawn_unparented(830,F(0xec),static_cast<float>(F(0xf0)-50.0),B(0x104),1,packet,3);}RETIRE();
        }
        if(static_cast<unsigned>(selector_random_roll(100))<=5) {float packet[3];packet[0]=0.0f;packet[1]=static_cast<float>(3.0-RF(60)*static_cast<double>(0.1f));packet[2]=4.0f;spawn_unparented(830,static_cast<float>(static_cast<double>(RF(100))+F(0xec)-50.0),static_cast<float>(static_cast<double>(RF(150))+F(0xf0)),B(0x104),1,packet,3);}
    }
    if(S(0x13e)==2) {
        F(0xf8)-=static_cast<double>(0.85f);F(0x12c)=F(0x370)+F(0x12c);F(0xf4)*=static_cast<double>(0.95f);
        if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending()) || C(0x184)<=0) {for(float index=0.0f;index<4.0f;index+=1.0) {float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(10))-(index*40.0+20.0)-5.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+10.0);packet[2]=5.0f;spawn_unparented(830,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();}
    }
    if(S(0x13e)==3) {F(0x11c)+=static_cast<double>(0.01f);F(0x120)+=static_cast<double>(0.01f);if(B(0x113)<=5) RETIRE();B(0x113)-=5;MOTION->set_components(PARAM[0],PARAM[1]);F(0xf8)*=0.25;}
    if(S(0x13e)==4) {float *parameters=PARAM;F(0x12c)=parameters[1]+F(0x12c);parameters[1]*=static_cast<double>(0.98f);F(0x11c)-=static_cast<double>(0.005f);F(0x120)-=static_cast<double>(0.005f);if(B(0x113)<=5) RETIRE();B(0x113)-=5;F(0xf8)-=static_cast<double>(0.05f);}
    if(S(0x13e)==5) {F(0xf4)=static_cast<float>(static_cast<double>(0.98f)*F(0xf4));if(B(0x113)<10) RETIRE();B(0x113)-=10;F(0xf8)-=0.5;F(0x12c)=F(0x370)+F(0x12c);if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) RETIRE();}
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);return;


}
case 831: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        void *secondary=FIELD(this,void*,0x154);if(FIELD(secondary,float,0xec)-200.0<=F(0xf0)) PARAM[1]*=0.5;if(FIELD(secondary,float,0xec)<=static_cast<double>(F(0xf0))) PARAM[1]=0.0f;
        if(PARAM[1]>10.0f) {float packet[3]={RF(360),1.0f,2.0f};double centerX=F(0xec)+100.0;spawn_unparented(831,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)+150.0),B(0x104),1,packet,3);}else B(0x184)=0;
        advance_six(0);advance_phase(0);
        if(I(0x144)<50) MOTION->set_components(PARAM[0],PARAM[1]);else {F(0x12c)-=F(0x370);F(0x370)+=static_cast<double>(0.01f);F(0xf8)-=static_cast<double>(0.05f);if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        MOVE();break;
    }
    case 3: {
        void *secondary=FIELD(this,void*,0x154);if(FIELD(secondary,float,0xec)-150.0<=F(0xf0)) PARAM[1]*=0.5;if(FIELD(secondary,float,0xec)<=static_cast<double>(F(0xf0))) PARAM[1]=0.0f;
        if(PARAM[1]>10.0f) {float packet[3]={RF(360),1.0f,2.0f};double centerX=F(0xec)+100.0;spawn_unparented(831,static_cast<float>(centerX-static_cast<double>(RF(200))),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)+150.0),B(0x104),1,packet,3);}else B(0x184)=0;
        advance_six(0);advance_phase(0);
        if(I(0x144)<50) MOTION->set_components(PARAM[0],PARAM[1]);else {F(0x12c)-=F(0x370);F(0x370)+=static_cast<double>(0.01f);F(0xf8)-=static_cast<double>(0.05f);if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        MOVE();break;
    }
    case 1: {
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);
        if(I(0x144)>=0) {if(B(0x113)<=5) RETIRE();B(0x113)-=5;}break;
    }
    case 2:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.995f);MOVE();F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.001f);F(0x120)=F(0x11c);
        if(I(0x144)>=0) {if(B(0x113)<=5) RETIRE();B(0x113)-=5;}break;
    }FINISH();


}
case 848: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);if((action!=301 && action!=696 && action!=418) || FIELD(owner,short,0x13e)!=0 || FIELD(owner,short,0x140)<1) RETIRE();F(0xec)=FIELD(owner,float,0xec);F(0xf0)=FIELD(owner,float,0xf0);break;
    }
    case 1: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=301 || FIELD(owner,short,0x13e)!=1 || FIELD(owner,short,0x140)<1) RETIRE();F(0xec)=FIELD(owner,float,0xec);F(0xf0)=FIELD(owner,float,0xf0);break;
    }
    case 5: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=307 || FIELD(owner,short,0x140)<5 || FIELD(owner,short,0x140)>12) RETIRE();FIELD(owner,int,0x180)=collision;
        if(I(0x180)!=0 && C(0x184)>0 && ++S(0x366)>=8) {S(0x366)=0;I(0x180)=0;}
        F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=3.0;if(parameters[1]<0.5f) parameters[1]=0.5f;
        owner=OWNER;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)=F(0xf8)+F(0x374);F(0xec)=FIELD(owner,float,0xec)+F(0x370);F(0xf0)=FIELD(owner,float,0xf0)+F(0x374);break;
    }
    case 6: {
        S(0x364)=1;void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action==305 && FIELD(owner,short,0x140)>=5 && FIELD(owner,short,0x140)<=12) {C(0x104)=FIELD(owner,signed char,0x104);owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(110*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+86.0);}
        else if(action==306 && FIELD(owner,short,0x140)>=2 && FIELD(owner,short,0x140)<=8) {C(0x104)=FIELD(owner,signed char,0x104);owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(63*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+53.0);}else RETIRE();break;
    }
    case 7: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=308) RETIRE();short phase=FIELD(owner,short,0x13e);short frame=FIELD(owner,short,0x140);
        if(!((phase==0 && frame>=3 && frame<=5) || (phase==1 && frame>=1 && frame<=3))) RETIRE();C(0x104)=FIELD(owner,signed char,0x104);owner=OWNER;F(0xec)=static_cast<float>(static_cast<double>(40*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+47.0);break;
    }
    case 8: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=408 || FIELD(owner,short,0x140)<4 || FIELD(owner,short,0x140)>12) RETIRE();
        F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=3.0;if(parameters[1]<0.5f) parameters[1]=0.5f;
        owner=OWNER;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)=F(0xf8)+F(0x374);F(0xec)=FIELD(owner,float,0xec)+F(0x370);F(0xf0)=FIELD(owner,float,0xf0)+F(0x374);if(FIELD(owner,short,0x186)>0) return;break;
    }
    case 9: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=320 || FIELD(owner,short,0x140)>11 || FIELD(owner,short,0x140)<1) RETIRE();position_relative_to_owner(122,133);if(FIELD(OWNER,short,0x186)>0) return;break;
    }
    case 10:F(0x12c)+=10.0;F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);if(I(0x144)>=10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}break;
    case 11:F(0x12c)-=10.0;F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;break;
    case 12: {
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=309) RETIRE();
        if(FIELD(owner,short,0x13e)<2) {FIELD(owner,int,0x180)=collision;if(I(0x144)>=3) {if(I(0x144)==3) B(0x184)=1;if(I(0x144)%5==0) {float packet[3]={0.0f,0.0f,13.0f};spawn_unparented(848,F(0xec),static_cast<float>(F(0xf0)+90.0),B(0x104),1,packet,3);}}}
        else {B(0x184)=0;float *parameters=PARAM;owner=OWNER;parameters[0]=90.0f;parameters[1]=15.0f;if(FIELD(owner,short,0x142)>=1) RETIRE();}
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;F(0x370)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0x370));F(0x374)=F(0xf8)+F(0x374);parameters[1]*=static_cast<double>(0.6f);position_relative_to_owner(static_cast<int>(F(0x370))+34,static_cast<int>(F(0x374))+122);break;
    }
    case 13:F(0xf4)=0.0f;F(0xf8)=0.0f;if(F(0x370)<0.5f) F(0x370)=0.5f;F(0x12c)=F(0x370)+F(0x12c);F(0x11c)+=static_cast<double>(0.03f);F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;break;
    }
    if(advance_frame()) RETIRE();if(S(0x140)==0 && S(0x142)==0 && S(0x364)==0) --I(0x330);return;
}


}
case 850: {

    switch(S(0x13e)) {
    case 0:
        F(0x11c)+=static_cast<double>(0.1f);F(0x120)+=static_cast<double>(0.1f);if(F(0x11c)>2.0f) F(0x11c)=2.0f;if(F(0x120)>2.0f) F(0x120)=2.0f;
        if(FIELD(OWNER,short,0x13c)!=600) RETIRE();position_relative_to_owner(-55,230);
        if(FIELD(OWNER,short,0x140)==8) {
            next_sequence_block();int facing=C(0x104);double targetX=FIELD(TARGET,float,0xec);float groundX=static_cast<float>(targetX-lookup_orientation_ratio_quantized_abs(-20)*static_cast<double>(FIELD(TARGET,float,0xf0))*(-facing));
            float dx=static_cast<float>((groundX-static_cast<double>(F(0xec)))*facing);float angle=-atan2_degrees(-F(0xf0),dx);float *parameters=PARAM;parameters[0]=angle;if(angle>=60.0f) parameters[0]=60.0f;if(parameters[0]<=10.0f) parameters[0]=10.0f;
        }break;
    case 1: {
        MOTION->set_components(PARAM[0],40.0f);float packet[3]={0.0f,0.0f,6.0f};double centerY=F(0xf0)+40.0;double centerX=F(0xec)+40.0;
        spawn_unparented(850,static_cast<float>(centerX-static_cast<double>(RF(80))),static_cast<float>(centerY-static_cast<double>(RF(80))),B(0x104),1,packet,3);
        double currentY=F(0xf0);if(stage_surface_height()<currentY) {F(0xec)=static_cast<float>(F(0xf4)*static_cast<double>(C(0x104))+F(0xec));F(0xf0)=F(0xf8)+F(0xf0);}
        else {
            WAVE(51);publish_battle_layout_scalar(10.0f);float burst[3]={15.0f,0.0f,2.0f};spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,burst,3);
            burst[0]=0.0f;burst[1]=0.0f;burst[2]=3.0f;spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,burst,3);
            int count=16;do {burst[0]=RF(360);burst[1]=static_cast<float>(static_cast<double>(RF(25))+5.0);burst[2]=4.0f;spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,burst,3);}while(--count);
            do {burst[0]=static_cast<float>(static_cast<unsigned>(count+selector_random_roll(40)));burst[1]=22.0f;burst[2]=5.0f;spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,burst,3);count+=45;}while(count<360);RETIRE();
        }break;
    }
    case 2:advance_six(0);advance_phase(5);break;
    case 3:F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.9f);if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;break;
    case 4:
        if(I(0x144)>=S(0x364)) {if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;}
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.95f);MOVE();break;
    case 5:
        if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.9f);F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.97f);
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    case 6:
        if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;F(0x11c)+=static_cast<double>(0.02f);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.3f);F(0xf0)=F(0xf8)+F(0xf0);break;
    }
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);return;


}
case 851: {
 {
    int collision=I(0x180);if(collision==5) RETIRE();if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0 || F(0xf0)<-100.0) RETIRE();
    if(S(0x13e)==1) {
        if(S(0x140)==0 && collision!=0) {
            advance_six(0);if(B(0x184)==0 || I(0x180)!=0) {
                F(0xf4)=0.0f;F(0xf8)=0.0f;select_frame(1);F(0x11c)=2.0f;F(0x120)=2.0f;float packet[3];packet[2]=3.0f;
                for(int count=2;count!=0;--count) {packet[0]=RF(360);float speed=static_cast<float>(RF(20)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+4.0);spawn_unparented(851,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
            }
        }
        if(S(0x140)==1) {F(0x11c)*=0.99f;F(0x120)=0.99f*F(0x120);if(B(0x113)<30) {B(0x113)=0;RETIRE();}B(0x113)-=30;}
    }else if(S(0x13e)==2) {F(0x11c)+=static_cast<double>(0.01f);F(0x120)=F(0x11c);if(B(0x113)<30) RETIRE();B(0x113)-=30;B(0x111)-=30;B(0x112)-=30;}
    else if(S(0x13e)==3) {F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);F(0xf8)-=static_cast<double>(0.3f);F(0x370)-=static_cast<double>(0.3f);if(F(0x370)<0.05f) F(0x370)=0.05f;if(I(0x144)>=10) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}}
    MOVE();FINISH();
}


}
case 852: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:
        F(0x12c)-=15.0;
        if(S(0x364)==0) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>=1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);void *owner=OWNER;if(FIELD(owner,short,0x13c)==602 && FIELD(owner,short,0x13e)==1) {F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}else S(0x364)=1;}
        if(S(0x364)==1) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.0f)) RETIRE();}break;
    case 1:
        F(0x12c)+=15.0;
        if(S(0x364)==0) {
            F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>=1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==602 && FIELD(owner,short,0x13e)==1) {
                F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144)*6.0-PARAM[0]))*150.0*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));
                F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6.0-PARAM[0]))*150.0+(FIELD(OWNER,float,0xf0)+100.0));
            }else S(0x364)=1;
        }
        if(S(0x364)==1) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.0f)) RETIRE();}break;
    case 2:
        F(0x12c)-=20.0;
        if(S(0x364)==0) {
            F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>=1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==602 && FIELD(owner,short,0x13e)==1) {
                float *parameters=PARAM;F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(-parameters[0]-I(0x144)*9.0))*parameters[1]*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));
                F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-parameters[0]-I(0x144)*9.0))*PARAM[1]+(FIELD(OWNER,float,0xf0)+100.0));
            }else S(0x364)=1;
        }
        if(S(0x364)==1) {F(0x11c)-=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.0f)) RETIRE();}break;
    case 3:F(0x12c)-=F(0x370);F(0x370)*=static_cast<double>(0.98f);F(0x11c)+=static_cast<double>(0.005f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;break;
    }FINISH();


}
case 853: {

    switch(S(0x13e)) {
    case 0: {
        F(0xec)=static_cast<float>(static_cast<double>(20*FIELD(OWNER,signed char,0x104))+FIELD(OWNER,float,0xec));
        if(I(0x144)%5==0) {float packet[3]={RF(360),12.0f,5.0f};spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(200))+60.0);packet[2]=6.0f;spawn_parented(853,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*packet[1]*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*packet[1]+F(0xf0)),B(0x104),1,packet,3);}
        void *owner=OWNER;F(0xf0)+=0.5;if(FIELD(owner,short,0x13c)!=603) RETIRE();
        if(FIELD(owner,short,0x13e)==1) {
            WAVE(54);next_sequence_block();B(0x184)=99;I(0x180)=0;float packet[3];
            for(float index=0.0f;index<3.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(40))+index*120.0);packet[1]=0.0f;packet[2]=4.0f;spawn_parented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(45))+index*90.0+160.0);packet[1]=1.0f;packet[2]=4.0f;spawn_parented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        }break;
    }
    case 1:
        if(S(0x364)==0) {
            F(0x11c)=static_cast<float>((1.0-F(0x370))*25.0+1.0);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.95f);int lower=static_cast<int>(F(0x11c)*-70.0);publish_bounds_descriptor(lower,static_cast<int>(F(0x11c)*70.0),static_cast<int>(F(0x11c)*70.0),lower,0,0,0);advance_six(0);
            if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(40))+20.0);packet[2]=2.0f;spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            if(I(0x144)%2==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=7.0f;spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            if(I(0x144)%15==0) {float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
            if(I(0x180)!=0 && ++S(0x366)>=3) {S(0x366)=0;I(0x180)=0;}
            if(B(0x113)<196) {B(0x113)=196;B(0x111)=196;B(0x110)=196;}else {B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;}
            void *owner=OWNER;if(FIELD(owner,short,0x13c)==603 && FIELD(owner,short,0x13e)==1) F(0xec)=static_cast<float>(static_cast<double>(20*FIELD(owner,signed char,0x104))+FIELD(owner,float,0xec));else S(0x364)=1;
        }
        if(S(0x364)==1) {B(0x184)=0;goto patchouli_853_fade10;}break;
    case 2:
        MOTION->set_components(PARAM[0],PARAM[1]);F(0x11c)+=static_cast<double>(0.1f);F(0x120)*=static_cast<double>(0.99f);if(I(0x144)>=15) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}MOVE();break;
    case 3:F(0x11c)+=1.0;F(0x120)=F(0x11c);
patchouli_853_fade10:
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 4:
        F(0x12c)=F(0x378)+F(0x12c);
        if(S(0x364)==0) {F(0x120)=static_cast<float>((1.0-F(0x374))*F(0x370));F(0x374)*=static_cast<double>(0.9f);if(!RELATED) S(0x364)=1;else {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x364)==1) S(0x364)=1;}}
        if(S(0x364)==1) {F(0x378)*=static_cast<double>(0.98f);F(0x120)*=static_cast<double>(0.85f);if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}break;
    case 5:
        MOTION->set_components(PARAM[0],PARAM[1]);if(I(0x144)>=15) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}MOVE();break;
    case 6: {
        if(!RELATED) RETIRE();float *parameters=PARAM;double orbitX=lookup_orientation_cosine_quantized_abs(-parameters[0]);float *radius=PARAM;
        F(0xec)=static_cast<float>(orbitX*parameters[1]*static_cast<double>(C(0x104))+FIELD(RELATED,float,0xec));F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])*radius[1]+FIELD(RELATED,float,0xf0));radius[1]*=static_cast<double>(0.95f);
        if(S(0x364)==0) {if(B(0x113)>235) {B(0x113)=255;B(0x111)=255;B(0x110)=255;}else {B(0x113)+=20;B(0x111)+=20;B(0x110)+=20;}if(I(0x144)>=30) S(0x364)=1;}
        if(S(0x364)==1) {if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;}break;
    }
    case 7:MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.9f);if(I(0x144)>=15) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}MOVE();break;
    }FINISH();


}
case 854: {

    switch(S(0x13e)) {
    case 0:
        F(0x12c)-=1.0;
        if(S(0x364)==0) {
            void *owner=OWNER;if(FIELD(owner,short,0x13c)!=604 || FIELD(owner,short,0x13e)>=3) {S(0x364)=2;return;}
            F(0x11c)=static_cast<float>(1.0-F(0x370)+1.0-F(0x370));F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.97f);if(F(0x370)<=0.01f) F(0x370)=0.0f;position_relative_to_owner(0,0);
            short phase=FIELD(OWNER,short,0x13e);if(phase==1 || phase==2) {
                if(I(0x144)%10==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(250))+50.0);packet[2]=4.0f;spawn_parented(854,F(0xec),F(0xf0),S(0x366)%2==0?1:255,packet[0]>180.0f?-1:1,packet,3);WAVE(56);++S(0x366);}
                if(I(0x144)%20==0) {float packet[3]={RF(360),0.0f,3.0f};spawn_parented(854,F(0xec),F(0xf0),S(0x368)%2==0?B(0x104):static_cast<unsigned char>(-B(0x104)),1,packet,3);++S(0x368);}
            }
        }
        if(S(0x364)==2) goto patchouli_854_fade10;break;
    case 1: {
        if(!RELATED) RETIRE();void *related=RELATED;F(0x12c)=FIELD(related,float,0x12c);
        if(FIELD(related,short,0x364)==0) {F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);position_relative_to_owner(0,0);B(0x113)=static_cast<unsigned char>(static_cast<int>(127.0-lookup_orientation_cosine_quantized_abs(static_cast<float>(4*I(0x144)))*127.0));}
        if(FIELD(RELATED,short,0x364)==2) goto patchouli_854_fade10;break;
    }
    case 2: {
        if(!RELATED) RETIRE();void *related=RELATED;F(0x12c)=-FIELD(related,float,0x12c);
        if(FIELD(related,short,0x364)==0) {F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);position_relative_to_owner(0,0);}
        if(FIELD(RELATED,short,0x364)==2) goto patchouli_854_fade10;break;
    }
    case 3:
        if(RELATED) {
            F(0x11c)=FIELD(RELATED,float,0x11c);F(0x120)=F(0x11c);F(0x12c)=F(0x370)+F(0x12c);
            if(S(0x364)==0) {if(B(0x113)>235) {B(0x113)=255;B(0x111)=255;B(0x112)=255;I(0x144)=0;S(0x364)=1;return;}B(0x113)+=20;B(0x111)+=20;B(0x112)+=20;}
            if(S(0x364)==1 && I(0x144)>=40) S(0x364)=2;if(S(0x364)!=2) break;
        }else F(0x12c)=F(0x370)+F(0x12c);
patchouli_854_fade10:
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;break;
    case 4:
        if(RELATED) {
            F(0x120)+=2.0;if(F(0x120)>=40.0f) F(0x120)=40.0f;F(0x11c)+=static_cast<double>(0.05f);if(F(0x11c)>=0.75f) F(0x11c)=0.75f;
            publish_bounds_descriptor(static_cast<int>(F(0x11c)*-30.0),static_cast<int>(F(0x120)*-32.0),static_cast<int>(F(0x11c)*30.0),0,0,0,0);
            float *parameters=PARAM;parameters[0]+=3.0;F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])*parameters[1]*static_cast<double>(C(0x104))+FIELD(RELATED,float,0xec));
            double orbitY=lookup_orientation_sine_quantized_abs(-parameters[0]);parameters=PARAM;F(0xf0)=static_cast<float>(orbitY*parameters[1]*static_cast<double>(0.2f)+FIELD(RELATED,float,0xf0));B(0x33c)=static_cast<unsigned char>(2*(static_cast<int>(parameters[0])%360<=180)-1);advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x364)>=6) {S(0x364)=0;B(0x184)=1;I(0x180)=0;}
            if(I(0x144)>=60) {B(0x184)=0;F(0x11c)*=static_cast<double>(0.9f);if(B(0x113)<6) RETIRE();B(0x113)-=6;B(0x111)-=6;B(0x112)-=6;}
        }else {B(0x184)=0;F(0x11c)*=static_cast<double>(0.8f);if(!(F(0x11c)>=0.01f)) RETIRE();}break;
    case 5:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);B(0x33c)=FIELD(related,unsigned char,0x33c);}else goto patchouli_854_shrink;break;
    case 6:
        if(RELATED) {
            if(I(0x144)%2==0 && F(0xf0)<=960.0f) {float packet[3];packet[0]=RF(360);float speed=static_cast<float>(RF(60)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+2.0);packet[2]=7.0f;spawn_unparented(854,F(0xec),F(0xf0),B(0x104),B(0x33c),packet,3);}
            void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=static_cast<float>(FIELD(related,float,0x120)*32.0+FIELD(related,float,0xf0));F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);B(0x33c)=FIELD(related,unsigned char,0x33c);
        }else {
patchouli_854_shrink:
            B(0x184)=0;F(0x11c)*=static_cast<double>(0.8f);F(0x120)=F(0x11c);if(F(0x11c)<0.01f) RETIRE();
        }break;
    case 7:MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.9f);MOVE();if(I(0x144)>=20) goto patchouli_854_fade10;break;
    case 8: {
        position_relative_to_owner(0,0);float *parameters=PARAM;F(0x11c)=parameters[1]+F(0x11c);F(0x120)=F(0x11c);parameters[1]*=static_cast<double>(0.96f);if(parameters[1]<=0.05f) parameters[1]=0.05f;F(0x12c)+=2.0;
        if(I(0x144)%8==0) {float packet[4]={F(0x12c),static_cast<float>(B(0x113)),9.0f,F(0x11c)};spawn_unparented(854,F(0xec),F(0xf0),B(0x104),1,packet,4);}if(I(0x144)>=20) goto patchouli_854_fade10;break;
    }
    case 9:F(0x12c)-=2.0;if(B(0x113)<7) RETIRE();B(0x113)-=7;B(0x111)-=7;B(0x112)-=7;F(0xf0)+=12.0;break;
    }FINISH();


}
case 855: {

    if(advance_frame()) RETIRE();
    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3:case 4: {
        float *parameters=PARAM;parameters[0]+=2.0;
        if(S(0x364)==0) {
            if(FIELD(OWNER,short,0x7a4)<=0) {S(0x364)=3;return;}
            if(B(0x113)>=245) {B(0x113)=255;S(0x364)=1;}else B(0x113)+=10;
            B(0x33c)=lookup_orientation_sine_quantized_abs(-PARAM[0])<0.0?1:255;
            parameters=PARAM;parameters[1]=static_cast<float>(150.0-F(0x378)*150.0);F(0x378)*=static_cast<double>(0.98f);
            double orbitX=lookup_orientation_cosine_quantized_abs(-parameters[0]);parameters=PARAM;
            F(0xec)=static_cast<float>(orbitX*parameters[1]*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));
            F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])*PARAM[1]*static_cast<double>(0.2f)+(FIELD(OWNER,float,0xf0)+100.0));
        }
        if(S(0x364)==1) {
            if(FIELD(OWNER,short,0x7a4)<=0) {S(0x364)=3;return;}
            B(0x33c)=lookup_orientation_sine_quantized_abs(-PARAM[0])<0.0?1:255;
            parameters=PARAM;parameters[1]=static_cast<float>(150.0-F(0x378)*150.0);F(0x378)*=static_cast<double>(0.95f);
            double orbitX=lookup_orientation_cosine_quantized_abs(-parameters[0]);parameters=PARAM;void *owner=OWNER;
            F(0xec)=static_cast<float>(orbitX*parameters[1]*static_cast<double>(C(0x104))+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])*PARAM[1]*static_cast<double>(0.2f)+(FIELD(owner,float,0xf0)+100.0));
            short phase=S(0x13e);short action=FIELD(owner,short,0x13c);
            if((phase==0 && action>=500 && action<=519) || (phase==1 && action>=520 && action<=539) || (phase==2 && action>=540 && action<=559) || (phase==3 && action>=560 && action<=579) || (phase==4 && action>=580 && action<=599)) {
                float packet[3];for(int count=8;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=static_cast<float>(S(0x13e)+5.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);}
                packet[0]=0.0f;packet[1]=0.25f;packet[2]=static_cast<float>(S(0x13e)+10.0);
                for(float index=0.0f;index<8.0f;index+=1.0) {packet[0]=static_cast<float>(index*45.0);packet[1]=35.0f;packet[2]=static_cast<float>(S(0x13e)+15.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);}
                spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(60);B(0x113)=0;S(0x366)=0;S(0x364)=2;
            }
        }
        if(S(0x364)==2) {
            if(FIELD(OWNER,short,0x7a4)<=0) {S(0x364)=3;return;}
            if(++S(0x366)>=210) {S(0x366)=0;float packet[3];for(int count=8;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=static_cast<float>(S(0x13e)+5.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);}
                packet[0]=0.0f;packet[1]=0.25f;packet[2]=static_cast<float>(S(0x13e)+10.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);B(0x113)=255;S(0x364)=1;
            }
            B(0x33c)=lookup_orientation_sine_quantized_abs(-PARAM[0])<0.0?1:255;
            parameters=PARAM;parameters[1]=static_cast<float>(100.0-F(0x378)*100.0);F(0x378)*=static_cast<double>(0.95f);
            double orbitX=lookup_orientation_cosine_quantized_abs(-parameters[0]);parameters=PARAM;
            F(0xec)=static_cast<float>(orbitX*parameters[1]*static_cast<double>(C(0x104))+FIELD(OWNER,float,0xec));
            F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])*PARAM[1]*static_cast<double>(0.2f)+(FIELD(OWNER,float,0xf0)+100.0));
        }
        if(S(0x364)==3) {float packet[3];for(int count=8;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=static_cast<float>(S(0x13e)+5.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);}packet[0]=0.0f;packet[1]=0.5f;packet[2]=static_cast<float>(S(0x13e)+10.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);--I(0x330);}break;
    }
    case 5:case 6:case 7:case 8:case 9:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.95f);if(I(0x144)>=5) {F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);if(B(0x113)<7) RETIRE();B(0x113)-=7;}MOVE();break;
    case 10:case 11:case 12:case 13:case 14: {
        float *parameters=PARAM;F(0x11c)=parameters[1]+F(0x11c);F(0x120)=F(0x11c);parameters[1]*=static_cast<double>(0.95f);if(parameters[1]<0.05f) parameters[1]=0.05f;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    }
    case 15:case 16:case 17:case 18:case 19:
        if(FIELD(OWNER,short,0x174)<=0) S(0x364)=2;
        if(S(0x364)==0) {
            PARAM[1]*=static_cast<double>(0.8f);turn_heading(0.0f,0.25f,100.0f);float *parameters=PARAM;
            if(parameters[1]<=0.1f) {parameters[1]=0.0f;S(0x364)=1;turn_heading(0.0f,360.0f,100.0f);
                if(S(0x13e)==15) replace_secondary(994,10.0f,15,1,2);if(S(0x13e)==16) replace_secondary(991,10.0f,15,1,2);if(S(0x13e)==17) replace_secondary(993,10.0f,15,1,2);if(S(0x13e)==18) replace_secondary(992,10.0f,15,1,2);if(S(0x13e)==19) replace_secondary(995,10.0f,15,1,2);
            }
        }
        if(S(0x364)==1) {float *parameters=PARAM;parameters[1]+=0.75;if(parameters[1]>=30.0f) parameters[1]=30.0f;turn_heading(0.0f,0.5f,100.0f);if(C(0x184)<=0) S(0x364)=2;if(F(0xec)>1480.0f || F(0xec)<-200.0 || F(0xf0)>1000.0 || F(0xf0)<-300.0) RETIRE();}
        if(S(0x364)==2) {float packet[3];for(int count=4;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+10.0);packet[2]=static_cast<float>(S(0x13e)+-10.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);}packet[0]=0.0f;packet[1]=0.25f;packet[2]=static_cast<float>(S(0x13e)-5.0);spawn_unparented(855,F(0xec),F(0xf0),B(0x104),1,packet,3);--I(0x330);}else {MOTION->set_components(PARAM[0],PARAM[1]);MOVE();}break;
    }return;


}
case 856: {

    switch(S(0x13e)) {
    case 0: {
        FIELD(OWNER,short,0x4a8)=3;FIELD(OWNER,short,0x4ac)=3;void *owner=OWNER;F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);
        if(FIELD(owner,short,0x174)<=0 || FIELD(TARGET,short,0x174)<=0 || I(0x144)>=600) {
            float packet[3];for(float index=0.0f;index<12.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;spawn_unparented(856,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}select_sequence(2);return;
        }
        short action=FIELD(owner,short,0x13c);
        if(action<600 || FIELD(TARGET,short,0x13c)>689 || (action==606 && FIELD(owner,short,0x13e)>=1)) {
            if(S(0x140)==0) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);}
            if(S(0x140)==1) {
                F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*12.0))*F(0x370)+1.0);
                F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*12.0+90.0))*F(0x370)+1.0);
                F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3.0))*static_cast<double>(0.1f)+F(0x11c));
                F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3.0+90.0))*static_cast<double>(0.1f)+F(0x120));
                if(F(0x370)>0.0f) {F(0x370)-=static_cast<double>(0.025f);if(F(0x370)<0.0f) F(0x370)=0.0f;}
                if(S(0x366)!=S(0x174)) {S(0x366)=S(0x174);F(0x370)=0.3f;}
                if(static_cast<double>(S(0x174))<-3000.0) {WAVE(13);next_sequence_block();float packet[3];for(float index=0.0f;index<12.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;spawn_unparented(856,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}return;}
            }
        }else {float packet[3];for(float index=0.0f;index<12.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;spawn_unparented(856,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}select_sequence(2);return;}
        break;
    }
    case 1:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) {FIELD(OWNER,short,0x7a6)=360;RETIRE();}B(0x113)-=20;break;
    case 2:case 4:if(I(0x144)>=20) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}F(0xf8)-=0.25;F(0xf4)*=static_cast<double>(0.98f);break;
    case 3:
        if(S(0x364)==0) {
            advance_six(0);advance_phase(3);if(F(0x11c)<1.0f) {F(0x11c)+=0.5;if(F(0x11c)>1.0f) {F(0x11c)=1.0f;B(0x184)=1;}F(0x120)=F(0x11c);}
            if(FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0) {S(0x364)=1;float packet[3];for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
            if(F(0xec)<0.0f || F(0xec)>1280.0 || F(0xf0)<0.0f || F(0xf0)>900.0) {
                S(0x364)=1;float packet[3];for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}
                if(g_match_identifier==2) {for(float index=0.0f;index<2.0f;index+=1.0) {packet[0]=static_cast<float>(RF(360));packet[1]=static_cast<float>(static_cast<double>(RF(5))+4.0);packet[2]=5.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}else if(g_match_identifier==3) {for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(RF(360));packet[1]=static_cast<float>(static_cast<double>(RF(10))+5.0);packet[2]=5.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
            }
        }
        if(S(0x364)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    case 5:
        if(S(0x364)==0 && (FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0 || I(0x144)>=120)) {S(0x364)=1;float packet[3];for(float index=0.0f;index<3.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
        if(S(0x364)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}
        MOTION->set_components(PARAM[0],PARAM[1]);{float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);if(parameters[1]<2.0f) parameters[1]=2.0f;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-200.0) RETIRE();break;
    }
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);return;


}
case 857: {

    switch(S(0x13e)) {
    case 0:case 1: {
        float *parameters=PARAM;F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])*parameters[1]*static_cast<double>(C(0x104))+F(0x370));
        F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])*(PARAM[1]*static_cast<double>(0.15f))+F(0x374));
        double scale=2.0-lookup_orientation_cosine_quantized_abs(static_cast<float>(6*I(0x144)));parameters=PARAM;F(0x11c)=static_cast<float>(scale);F(0x120)=F(0x11c);parameters[0]-=3.0;parameters[1]=static_cast<float>(F(0x378)+static_cast<double>(1.7f)+parameters[1]);F(0x374)+=2.0;F(0x378)*=static_cast<double>(0.95f);
        int phaseAge=I(0x144)%60;if(phaseAge==30 || phaseAge==33 || phaseAge==36 || phaseAge==39 || phaseAge==42 || phaseAge==45) {float packet[3]={0.0f,static_cast<float>(7.0-(static_cast<double>(I(0x144)%60)-30.0)*static_cast<double>(0.2f)),static_cast<float>((S(0x13e)==1)+4.0)};spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(0);}
        phaseAge=I(0x144)%60;if(phaseAge==30 || phaseAge==0) {float packet[3]={0.0f,0.0f,static_cast<float>(2.0+(S(0x13e)==1))};spawn_parented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(FIELD(TARGET,short,0x174)>0 && FIELD(OWNER,short,0x174)>0 && I(0x144)<360) break;
        float packet[3]={0.0f,0.0f,static_cast<float>((S(0x13e)==1)+8.0)};spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        for(int count=12;count!=0;--count) {packet[0]=RF(360);float speed=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+5.0);packet[2]=static_cast<float>((S(0x13e)==1)+10.0);spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();
    }
    case 2:case 3:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}F(0x11c)=static_cast<float>(2.0-F(0x370));F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.98f);if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    case 4:case 5: {
        F(0xf0)-=PARAM[1];advance_six(3);if(F(0xf0)>0.0f && C(0x184)>0 && I(0x144)<600) break;
        float packet[3]={0.0f,0.0f,static_cast<float>((S(0x13e)==5)+6.0)};spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);
        for(int count=4;count!=0;--count) {packet[0]=RF(360);float speed=static_cast<float>(RF(40)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+3.0);packet[2]=static_cast<float>((S(0x13e)==5)+10.0);spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();
    }
    case 6:case 7:F(0x11c)*=static_cast<double>(0.7f);F(0x120)=F(0x11c);if(!(F(0x11c)>0.5f)) {if(B(0x113)<15) RETIRE();B(0x113)-=15;}break;
    case 8:case 9:F(0x11c)=static_cast<float>(2.5-F(0x370)*1.5);F(0x120)=F(0x11c);F(0x370)*=static_cast<double>(0.94f);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 10:case 11:MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=static_cast<double>(0.9f);if(B(0x113)<10) RETIRE();B(0x113)-=10;MOVE();break;
    }FINISH();


}
case 860: {

    if(S(0x13e)==0) {
        if(S(0x364)==0) {F(0x11c)=static_cast<float>(1.0-F(0x370)*0.75);F(0x370)*=static_cast<double>(0.92f);if(B(0x113)>250) {B(0x113)=255;F(0x11c)=1.0f;S(0x364)=1;}else B(0x113)+=5;}
        if(S(0x364)==1) {
            F(0x374)+=1.0;F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x370))*static_cast<double>(0.1f)+1.0);++S(0x366);
            if(FIELD(TARGET,short,0x174)<=0 || FIELD(OWNER,short,0x174)<=0 || S(0x366)>=480 || (FIELD(OWNER,short,0x13c)>=600 && FIELD(OWNER,short,0x13c)<=699 && (FIELD(OWNER,short,0x13c)!=610 || FIELD(OWNER,short,0x13e)==0))) {S(0x364)=2;return;}
            void *owner=OWNER;if(absolute_scalar_float(FIELD(owner,float,0xec)-F(0xec))<=100.0f) FIELD(owner,short,0x482)+=10;
        }
        if(S(0x364)==2) {F(0x11c)*=static_cast<double>(0.97f);if(B(0x113)<5) RETIRE();B(0x113)-=5;}
    }FINISH();


}
case 861: {

    if(S(0x13e)==0) {F(0x11c)+=1.0;F(0x120)+=1.0;if(S(0x142)>0) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;}}
    if(S(0x13e)==1) {float *parameters=PARAM;F(0x11c)+=static_cast<double>(0.1f);F(0x120)+=1.0;F(0x12c)=static_cast<float>(parameters[1]*0.5+F(0x12c));if(B(0x111)>2) {B(0x110)-=2;B(0x111)-=2;}if(S(0x142)>10) {if(B(0x113)<=2) RETIRE();B(0x113)-=2;}}
    if(advance_frame()) --I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);return;


}
case 890: {

    if(FIELD(OWNER,short,0x13c)!=600) RETIRE();position_relative_to_owner(66,67);if(FIELD(OWNER,short,0x140)>=13) RETIRE();FINISH();


}
case 900: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:
        if(F(0xec)>1580.0f || F(0xec)<-300.0 || F(0xf0)>1000.0) RETIRE();
        if(S(0x364)==0) {
            int lower=static_cast<int>(F(0x11c)*-20.0);publish_bounds_descriptor(lower,static_cast<int>(F(0x11c)*20.0),static_cast<int>(F(0x11c)*20.0),lower,0,0,0);if(FIELD(OWNER,short,0x174)<=0) {S(0x364)=2;return;}
            F(0x374)+=static_cast<double>(0.2f);if(F(0x374)>2.0f) F(0x374)=2.0f;MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;F(0xf8)+=F(0x374);parameters[1]*=static_cast<double>(0.98f);if(parameters[1]<1.0f) parameters[1]=1.0f;F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);advance_six(0);advance_phase(3);
            if(I(0x144)>=S(0x36a) || C(0x184)<=0) {S(0x364)=2;return;}F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);
            double currentY=F(0xf0);if(stage_surface_height()>=currentY) {for(int count=3;count!=0;--count) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(30)*static_cast<double>(0.1f)+PARAM[1]);packet[2]=1.0f;spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();}
        }
        if(S(0x364)==2) {F(0xf4)*=static_cast<double>(0.9f);F(0xf8)=static_cast<float>(static_cast<double>(0.9f)*F(0xf8));F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);B(0x184)=0;if(B(0x111)>=10) {B(0x111)-=10;B(0x110)-=10;}else {if(B(0x113)<10) RETIRE();B(0x113)-=10;}}
        MOVE();break;
    case 2:
        if(F(0xec)>1580.0f || F(0xec)<-300.0 || F(0xf0)>1000.0) RETIRE();
        if(S(0x364)==0) {
            int lower=static_cast<int>(F(0x11c)*-20.0);publish_bounds_descriptor(lower,static_cast<int>(F(0x11c)*20.0),static_cast<int>(F(0x11c)*20.0),lower,0,0,0);if(FIELD(OWNER,short,0x174)<=0) {S(0x364)=2;return;}
            F(0x374)+=static_cast<double>(0.2f);if(F(0x374)>2.0f) F(0x374)=2.0f;MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;F(0xf8)+=F(0x374);parameters[1]*=static_cast<double>(0.98f);if(parameters[1]<1.0f) parameters[1]=1.0f;F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);advance_six(0);advance_phase(3);
            if(I(0x144)>=75 || C(0x184)<=0) {S(0x364)=2;return;}F(0x11c)+=static_cast<double>(0.05f);F(0x120)=F(0x11c);
            double currentY=F(0xf0);if(stage_surface_height()>=currentY) {for(int count=3;count!=0;--count) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(30)*static_cast<double>(0.1f)+PARAM[1]);packet[2]=3.0f;spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);}RETIRE();}
        }
        if(S(0x364)==2) {F(0xf4)*=static_cast<double>(0.9f);F(0xf8)=static_cast<float>(static_cast<double>(0.9f)*F(0xf8));F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);B(0x184)=0;if(B(0x111)>=10) {B(0x111)-=10;B(0x112)-=10;}else {if(B(0x113)<10) RETIRE();B(0x113)-=10;}}
        MOVE();break;
    case 1: {
        F(0x374)+=static_cast<double>(0.2f);if(F(0x374)>2.0f) F(0x374)=2.0f;MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;F(0xf8)+=F(0x374);parameters[1]*=static_cast<double>(0.92f);if(parameters[1]<1.0f) parameters[1]=1.0f;F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);if(B(0x113)<10) RETIRE();B(0x113)-=10;
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    }
    case 3: {
        F(0x374)+=static_cast<double>(0.2f);if(F(0x374)>2.0f) F(0x374)=2.0f;MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;F(0xf8)+=F(0x374);parameters[1]*=static_cast<double>(0.92f);if(parameters[1]<1.0f) parameters[1]=1.0f;F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.95f);if(B(0x113)<10) RETIRE();B(0x113)-=10;
        F(0xec)=static_cast<float>(static_cast<double>(C(0x104))*F(0xf4)+F(0xec));F(0xf0)=static_cast<float>(F(0xf8)*static_cast<double>(0.2f)+F(0xf0));break;
    }
    case 4:case 5:F(0xf4)*=static_cast<double>(0.95f);F(0xf8)*=static_cast<double>(0.95f);F(0x12c)=F(0x370)+F(0x12c);F(0x370)=static_cast<float>(static_cast<double>(0.95f)*F(0x370));if(B(0x113)<10) RETIRE();B(0x113)-=10;MOVE();break;
    }FINISH();


}
case 910: {

    switch(S(0x13e)) {
    case 0: {
        FIELD(OWNER,short,0x4a8)=3;FIELD(OWNER,short,0x4ac)=3;void *owner=OWNER;F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);
        if(FIELD(owner,short,0x174)<=0) {
float packet[3];for(float index=0.0f;index<12.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}        }
            if(S(0x140)==0) {F(0x11c)+=static_cast<double>(0.1f);if(F(0x11c)>1.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);}
            if(S(0x140)==1) {
                F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*12.0))*F(0x370)+1.0);
                F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*12.0+90.0))*F(0x370)+1.0);
                F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3.0))*static_cast<double>(0.1f)+F(0x11c));
                F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3.0+90.0))*static_cast<double>(0.1f)+F(0x120));
                if(F(0x370)>0.0f) {F(0x370)-=static_cast<double>(0.025f);if(F(0x370)<0.0f) F(0x370)=0.0f;}
                if(S(0x366)!=S(0x174)) {S(0x366)=S(0x174);F(0x370)=0.3f;}
                int count;float threshold;
                switch(g_match_identifier) {case 0:count=1;threshold=-600.0f;break;case 1:count=2;threshold=-1200.0f;break;case 2:count=4;threshold=-2750.0f;break;case 3:count=6;threshold=-4000.0f;break;}
                if(S(0x174)<-500*S(0x368)) {++S(0x368);if(count>0) {do {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+4.0);packet[2]=3.0f;spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);}while(--count);}}
                if(threshold<=static_cast<double>(S(0x174))) {if(S(0x140)!=1) break;++I(0x144);}else {WAVE(13);next_sequence_block();
float packet[3];for(float index=0.0f;index<12.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(20))+index*30.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=2.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}                }return;
            }
            break;
    }
    case 1:F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) {FIELD(OWNER,short,0x7a6)=360;RETIRE();}B(0x113)-=20;break;
    case 2:case 4:if(I(0x144)>=20) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}F(0xf8)-=0.25;F(0xf4)*=static_cast<double>(0.98f);break;
    case 3:
        if(S(0x364)==0) {
            advance_six(0);advance_phase(3);if(F(0x11c)<1.0f) {F(0x11c)+=0.5;if(F(0x11c)>1.0f) {F(0x11c)=1.0f;B(0x184)=1;}F(0x120)=F(0x11c);}
            if(FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0) {S(0x364)=1;float packet[3];for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
            if(F(0xec)<0.0f || F(0xec)>1280.0 || F(0xf0)<0.0f || F(0xf0)>900.0) {
                S(0x364)=1;float packet[3];for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}
                if(g_match_identifier==2) {for(float index=0.0f;index<2.0f;index+=1.0) {packet[0]=static_cast<float>(RF(360));packet[1]=static_cast<float>(static_cast<double>(RF(5))+4.0);packet[2]=5.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}else if(g_match_identifier==3) {for(float index=0.0f;index<4.0f;index+=1.0) {packet[0]=static_cast<float>(RF(360));packet[1]=static_cast<float>(static_cast<double>(RF(10))+5.0);packet[2]=5.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
            }
        }
        if(S(0x364)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    case 5:
        if(S(0x364)==0 && (FIELD(OWNER,short,0x174)<=0 || I(0x180)!=0 || I(0x144)>=120)) {S(0x364)=1;float packet[3];for(float index=0.0f;index<3.0f;index+=1.0) {packet[0]=static_cast<float>(static_cast<double>(RF(60))+index*90.0);packet[1]=static_cast<float>(static_cast<double>(RF(5))+3.0);packet[2]=4.0f;spawn_unparented(910,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*60.0*static_cast<double>(C(0x104))+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*60.0+F(0xf0)),B(0x104),1,packet,3);}}
        if(S(0x364)==1) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)+=static_cast<double>(0.2f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}
        MOTION->set_components(PARAM[0],PARAM[1]);{float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);if(parameters[1]<2.0f) parameters[1]=2.0f;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-200.0) RETIRE();break;
    }
    MOVE();if(advance_frame()) RETIRE();if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);return;


}
case 920: {

    switch(S(0x13e)) {
    case 0:
        if(S(0x364)==0) {
            F(0x128)*=static_cast<double>(0.8f);if(F(0x128)<=1.0f) {F(0x128)=0.0f;S(0x364)=1;float packet[3]={0.0f,0.0f,PARAM[3]==0.0f?1.0f:2.0f};spawn_unparented(920,F(0xec),F(0xf0),B(0x104),-1,packet,3);}
            if(FIELD(OWNER,short,0x174)<=0) {S(0x364)=1;return;}
        }
        if(S(0x364)==1) {B(0x33c)=1;F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<20) RETIRE();B(0x113)-=20;}break;
    case 1:
        if(S(0x364)==0) {
            if(I(0x144)>=90 || FIELD(OWNER,short,0x174)<=0) {
                float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=9.0f;
                for(int count=6;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(RF(10)*static_cast<double>(0.1f)+10.0);spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);}WAVE(62);RETIRE();
            }
            if(S(0x174)<0) {
                float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);float count,speed;
                switch(g_match_identifier) {case 0:count=4.0f;speed=6.0f;break;case 1:count=4.0f;speed=9.0f;break;case 2:count=4.0f;speed=12.0f;break;case 3:count=4.0f;speed=15.0f;break;}
                packet[2]=7.0f;double limit=count;for(int index=0;index<limit;++index) {packet[0]=RF(360);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+speed);spawn_unparented(920,static_cast<float>(static_cast<double>(RF(200))+F(0xec)-100.0),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)-100.0),B(0x104),1,packet,3);}WAVE(62);RETIRE();
            }
        }break;
    case 2:
        if(S(0x364)==0) {
            if(I(0x144)<90) {
                if(S(0x174)>=0 && FIELD(OWNER,short,0x174)>0) break;
                float packet[3]={0.0f,0.0f,5.0f};spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=10.0f;
                for(int count=6;count!=0;--count) {packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(10))+10.0);spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);}WAVE(62);RETIRE();
            }else {
                float packet[3]={0.0f,0.0f,5.0f};spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);float count,speed;
                switch(g_match_identifier) {case 0:count=4.0f;speed=6.0f;break;case 1:count=4.0f;speed=9.0f;break;case 2:count=4.0f;speed=12.0f;break;case 3:count=4.0f;speed=15.0f;break;}
                packet[2]=8.0f;double limit=count;for(int index=0;index<limit;++index) {packet[0]=RF(360);packet[1]=static_cast<float>(RF(50)*static_cast<double>(0.1f)+speed);spawn_unparented(920,static_cast<float>(static_cast<double>(RF(200))+F(0xec)-100.0),static_cast<float>(static_cast<double>(RF(200))+F(0xf0)-100.0),B(0x104),1,packet,3);}WAVE(62);RETIRE();
            }
        }break;
    case 3:case 5:F(0x11c)+=static_cast<double>(0.1f);F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;break;
    case 4:case 6:F(0x11c)+=static_cast<double>(0.3f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 7:case 8:
        if(S(0x364)<=2) {MOTION->set_components(PARAM[0],PARAM[1]);if(FIELD(OWNER,short,0x174)<=0) goto patchouli_920_burst;}
        if(S(0x364)==0) {float *parameters=PARAM;parameters[1]*=static_cast<double>(0.9f);if(parameters[1]<=0.1f) {parameters[1]=0.0f;S(0x364)=1;return;}}
        if(S(0x364)==1 && ++S(0x366)>=10) {S(0x364)=2;B(0x184)=1;turn_heading(0.0f,360.0f,100.0f);float *parameters=PARAM;parameters[0]=static_cast<float>(static_cast<double>(RF(30))-15.0+parameters[0]);F(0x12c)=parameters[0];F(0x378)=0.3f;return;}
        if(S(0x364)==2) {
            PARAM[1]+=0.75;F(0x11c)=F(0x378)+F(0x11c);F(0x378)=static_cast<float>(static_cast<double>(0.9f)*F(0x378));F(0x120)*=static_cast<double>(0.95f);if(F(0x120)<0.25f) F(0x120)=0.25f;advance_six(1);
            if(I(0x180)!=0) {
patchouli_920_burst:
                B(0x184)=0;F(0x11c)*=3.0;F(0x120)=static_cast<float>(3.0*F(0x120));S(0x364)=3;return;
            }
        }
        if(S(0x364)==3) {F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x11c)=static_cast<float>(static_cast<double>(0.9f)*F(0x11c));F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;}
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>960.0 || !(F(0xf0)>=-200.0f)) RETIRE();break;
    case 9:case 10: {
        float *parameters=PARAM;parameters[1]*=static_cast<double>(0.95f);MOTION->set_components(parameters[0],parameters[1]);F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=static_cast<double>(0.9f);F(0x11c)*=static_cast<double>(0.99f);F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    }
    }MOVE();FINISH();


}
case 980: {
update_ping_pong_motion();FINISH();


}
case 998: {

    F(0x12c)+=1.0;
    if(S(0x13e)==0) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action>153 && action<158) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+60.0);}
        action=FIELD(owner,short,0x13c);if(action>149 && action<154) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+94.0);}
        if(FIELD(owner,short,0x13c)==158) {F(0xec)=static_cast<float>(static_cast<double>(57*C(0x104))+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}
        action=FIELD(owner,short,0x13c);if(action<150 || action>158) {next_sequence_block();FIELD(OWNER,unsigned char,0x751)=0;}
    }
    if(S(0x13e)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}FINISH();

}
default:advance_frame();return;
}
}
}
