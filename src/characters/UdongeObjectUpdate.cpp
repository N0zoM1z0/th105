// Complete manual JP1.06a UdongeObject update hypothesis, 005D46C0.
#include "characters/UdongeObjectUpdate.hpp"
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
#define MOTION reinterpret_cast<UdongeUpdateMotionView*>(reinterpret_cast<unsigned char*>(this)+4)
#define WAVE(n) reinterpret_cast<UdongeUpdateOwnerView*>(OWNER)->dispatch_character_wave_handle(n)
#define SPAWN_OWNED(a,x,y,d,l,p,n) reinterpret_cast<UdongeUpdateOwnerView*>(OWNER)->spawn_owned(a,x,y,d,l,p,n)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define RETIRE() do { --I(0x330); return; } while(0)
#define MOVE() do {F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}while(0)
#define FINISH() do {if(advance_frame())--I(0x330);return;}while(0)
void UdongeObjectUpdateView::update_action_state() {
switch(S(0x13c)) {
case 800: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,0,3)) RETIRE();
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<3.0f) parameters[1]=3.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        advance_phase(2);
        if(I(0x144)>120 || I(0x180)!=0) {
            for(int count=5;count!=0;--count) {
                float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10));packet[2]=2.0f;
                spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOVE();break;
    }
    case 1:
        F(0x11c)-=0.1f;F(0x120)-=0.1f;break;
    case 2: {
        F(0x11c)-=0.01f;F(0x120)-=0.01f;
        if(F(0x11c)<0.5 || I(0x144)>10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        if(F(0x11c)<=0.0 || B(0x113)==0) RETIRE();
        float *parameters=PARAM;parameters[1]-=1.25;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOVE();break;
    }
    case 3: {
        if(!RELATED) RETIRE();B(0x104)=FIELD(RELATED,unsigned char,0x104);
        void *related=RELATED;
        F(0xec)=static_cast<float>(FIELD(related,signed char,0x104)*FIELD(related,float,0xf4)+FIELD(related,float,0xec));
        F(0xf0)=FIELD(related,float,0xf8)+FIELD(related,float,0xf0);
        F(0x12c)=FIELD(related,float,0x12c);B(0x113)=FIELD(related,unsigned char,0x113);break;
    }
    case 4: {
        if(FIELD(OWNER,short,0x7ae)<=0) {
            B(0x184)=0;if(emit_repeated(0,0,0)) RETIRE();
            if(B(0x113)>138) B(0x113)-=10;else B(0x113)=128;
        }else {
            B(0x184)=1;if(emit_repeated(0,0,3)) RETIRE();
            if(B(0x113)<245) B(0x113)+=10;else B(0x113)=255;
        }
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<3.0f) parameters[1]=3.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        if(I(0x144)>120 || I(0x180)!=0) {
            for(int count=5;count!=0;--count) {
                float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10));packet[2]=2.0f;
                spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOVE();break;
    }
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    }
    return;


}
case 801: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0) replace_secondary(991,15.0f,10,1,2);
        if(emit_repeated(0,3,5)) RETIRE();
        PARAM[1]+=0.5;turn_heading(0.0f,0.2f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)%4==0) {
            float trail[3]={F(0x12c),0.0f,3.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=180) {
            WAVE(4);float packet[3]={0.0f,0.0f,1.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=5.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            RETIRE();
        }
    }
    if(S(0x13e)==1) {
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=4;S(0x366)=1;}
            }
            if(S(0x366)==1) {
                float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));
                F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);
            }
            advance_six(0);
            if(I(0x180)!=0 && C(0x184)>0) {
                if(++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            }
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
    }
    if(S(0x13e)==2) {
        F(0x11c)+=F(0x370);F(0x370)*=0.85f;
        if(F(0x370)<=0.02f) F(0x370)=0.02f;F(0x120)=F(0x11c);
        if(I(0x144)>=10) {if(B(0x113)<8) RETIRE();B(0x113)-=8;}
    }
    if(S(0x13e)==3) {
        F(0x11c)+=0.04f;F(0x120)+=0.04f;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;
    }
    if(S(0x13e)==4) {
        F(0x11c)+=0.01f;F(0x120)+=0.01f;
        if(B(0x113)<40) RETIRE();B(0x113)-=40;B(0x110)-=40;B(0x111)-=40;
    }
    if(S(0x13e)==5) {
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.9f;
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)*=0.95f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;
    }
    if(S(0x13e)==6) {
        F(0x12c)-=F(0x370);F(0x370)=0.95f*F(0x370);
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)=0.85f*F(0x374);
        if(B(0x113)<5) RETIRE();B(0x113)-=5;
    }
    if(S(0x13e)==7) {
        if(emit_repeated(0,3,5)) RETIRE();
        PARAM[1]+=0.25;turn_heading(0.0f,1.0f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)%4==0) {
            float trail[3]={F(0x12c),0.0f,3.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=180) {
            WAVE(2);float packet[3]={0.0f,0.0f,12.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=11.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=5.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            RETIRE();
        }
    }
    if(S(0x13e)==8) {
        if(FIELD(OWNER,short,0x7ae)>0) {
            B(0x184)=1;if(emit_repeated(0,1,4)) RETIRE();
            if(B(0x113)<245) B(0x113)+=10;else B(0x113)=255;
            if(I(0x144)%4==0) {
                float trail[3]={F(0x12c),0.0f,3.0f};
                spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
            }
        }else {
            B(0x184)=0;if(emit_repeated(0,0,0)) RETIRE();
            if(B(0x113)>138) B(0x113)-=10;else B(0x113)=128;
        }
        PARAM[1]+=0.5;turn_heading(0.0f,0.2f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=180) {
            WAVE(4);float packet[3]={0.0f,0.0f,10.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=5.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            RETIRE();
        }
    }
    if(S(0x13e)==9) {
        if(FIELD(OWNER,short,0x7ae)>0) {
            B(0x184)=1;if(emit_repeated(0,1,4)) RETIRE();
            if(B(0x113)<245) B(0x113)+=10;else B(0x113)=255;
            if(I(0x144)%4==0) {
                float trail[3]={F(0x12c),0.0f,3.0f};
                spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
            }
        }else {
            B(0x184)=0;if(emit_repeated(0,0,0)) RETIRE();
            if(B(0x113)>138) B(0x113)-=10;else B(0x113)=128;
        }
        PARAM[1]+=0.25;turn_heading(0.0f,1.0f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=180) {
            WAVE(2);float packet[3]={0.0f,0.0f,12.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=11.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=5.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            RETIRE();
        }
    }
    if(S(0x13e)==10) {
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=4;S(0x366)=1;}
            }
            if(S(0x366)==1) {
                float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));
                F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);
            }
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)!=0 && C(0x184)>0) {
                if(++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            }
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
    }
    if(S(0x13e)==11) {
        int age=I(0x144);
        if(age==5 || age==10) {
            float packet[3]={0.0f,0.0f,12.0f};
            unsigned char facing=B(0x104);double center_y=F(0xf0)+80.0;
            float center_x=static_cast<float>(F(0xec)+80.0);
            float y=static_cast<float>(center_y-RF(160));
            float x=static_cast<float>(center_x-RF(160));
            spawn_unparented(801,x,y,facing,1,packet,3);
        }
        if(I(0x144)==10) RETIRE();
    }
    if(S(0x13e)==12) {
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=3;S(0x366)=1;}
            }
            if(S(0x366)==1) {
                float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));
                F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);
            }
            advance_six(0);
            if(I(0x180)!=0 && C(0x184)>0) {
                if(++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            }
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 802: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)<=1) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action>49 && action<150) {
            for(int offset=80;offset<305;offset+=15)
                emit_effect(201,static_cast<float>(RF(15)+(offset*C(0x104)+static_cast<double>(F(0xec)))),static_cast<float>(RF(60)+F(0xf0)),B(0x104),1);
            RETIRE();
        }
        if(action!=412) {select_sequence(2);return;}
        F(0xec)=FIELD(owner,float,0xec);F(0xf0)=FIELD(owner,float,0xf0);advance_six(0);
        if(S(0x13e)==1 && I(0x144)>=15) {next_sequence_block();return;}
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);
    return;


}
case 810: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,3,5)) RETIRE();turn_heading(0.0f,0.4f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];int age=I(0x144);
        if(age==0 || age==5 || age==10) {
            float packet[3]={parameters[0],0.0f,4.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=static_cast<float>(RF(14)+(PARAM[0]+180.0)-7.0);packet[1]=10.0f;packet[2]=3.0f;
            double center_y=F(0xf0);unsigned char facing=B(0x104);double center_x=F(0xec);
            float y=static_cast<float>(center_y-lookup_orientation_sine_quantized_abs(-PARAM[0])*35.0);
            float x=static_cast<float>(center_x-lookup_orientation_cosine_quantized_abs(-PARAM[0])*static_cast<float>(35*C(0x104)));
            spawn_unparented(810,x,y,facing,1,packet,3);
        }
        parameters=PARAM;parameters[1]+=0.5;MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=179) {
            WAVE(6);float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=2.0f;
            for(int count=8;count!=0;--count) {
                packet[0]=RF(360);float speed=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+15.0);
                spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2]=6.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=7.0f;spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
            spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        break;
    }
    case 1:
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=4;S(0x366)=1;}
            }
            if(S(0x366)==1) {float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);}
            advance_six(0);
            int collision=I(0x180);
            if(collision!=0) {
                if(collision==4 || collision==8) S(0x364)=5;
                if(C(0x184)>0 && ++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            }
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 2: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)>=15) {F(0x11c)*=0.95f;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        MOVE();break;
    }
    case 3: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);MOVE();
        // Both writes are present at5D68A2/5D68AE; do not silently repair the target's overwrite.
        F(0x11c)+=0.05f;F(0x11c)=F(0x120);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    }
    case 4:
        F(0x12c)+=10.0;F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 5:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=2) RETIRE();break;
    case 6:
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.9f;
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)*=0.95f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    case 7:
        F(0x12c)-=F(0x370);F(0x370)*=0.95f;
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)*=0.85f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    }
    return;


}
case 811: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,0,4)) RETIRE();
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<2.0f) parameters[1]=2.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0) {
            WAVE(16);float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=2.0f;spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=static_cast<float>(RF(14)+(PARAM[0]+180.0)-7.0);packet[1]=10.0f;packet[2]=5.0f;
            double center_y=F(0xf0);unsigned char facing=B(0x104);double center_x=F(0xec);
            float y=static_cast<float>(center_y-lookup_orientation_sine_quantized_abs(-PARAM[0])*35.0);
            float x=static_cast<float>(center_x-lookup_orientation_cosine_quantized_abs(-PARAM[0])*static_cast<float>(35*C(0x104)));
            spawn_unparented(811,x,y,facing,1,packet,3);
        }
        if(I(0x144)>=30) {
            float packet[4];packet[0]=0.0f;packet[1]=0.0f;packet[2]=2.0f;
            spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=7.0f;float base_angle=RF(360);float index=0.0f;
            do {
                packet[0]=static_cast<float>(RF(40)+static_cast<double>(base_angle)+index*45.0);
                packet[1]=static_cast<float>(RF(150)*static_cast<double>(0.1f)+20.0);
                packet[3]=static_cast<float>(index+index+10.0);
                spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,4);index+=1.0;
            }while(index<8.0f);
            RETIRE();
        }
        break;
    }
    case 1:case 6:
        F(0x11c)*=0.99f;F(0x120)=F(0x11c);
        if(S(0x140)>=1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
        break;
    case 2:
        F(0x11c)+=0.3f;F(0x120)+=0.3f;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 3:
        F(0x12c)+=10.0;F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 4:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=4) RETIRE();break;
    case 5: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);MOVE();
        F(0x11c)+=0.05f;F(0x11c)=F(0x120);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    }
    case 7: {
        float *parameters=PARAM;parameters[1]*=0.9f;if(parameters[1]<0.0f) parameters[1]=0.0f;
        MOTION->set_components(parameters[0],parameters[1]);parameters=PARAM;
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);parameters[3]-=1.0;
        if(parameters[3]<=0.0f) {
            WAVE(16);float packet[3];packet[0]=0.0f;packet[1]=0.0f;
            signed char level=FIELD(OWNER,signed char,0x608);
            if(level>1) {if(level>3) packet[2]=11.0f;else packet[2]=10.0f;}else packet[2]=8.0f;
            spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=9.0f;
            for(int count=4;count!=0;--count) {
                packet[0]=RF(360);packet[1]=static_cast<float>(RF(10)+10.0);
                spawn_unparented(811,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        break;
    }
    case 8:case 10:case 11:
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=1;S(0x366)=1;}
            }
            if(S(0x366)==1) {float variation=static_cast<float>(static_cast<double>(0.1f)*(I(0x144)%2));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);}
            advance_six(0);if(B(0x184)==0 && F(0x11c)>=1.0f) {next_sequence_frame();return;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 9: {
        float *parameters=PARAM;parameters[1]-=1.0;if(parameters[1]<0.5f) parameters[1]=0.5f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)>=5) {F(0x11c)*=0.95f;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        MOVE();break;
    }
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 812: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(emit_repeated(0,3,8)) RETIRE();int age=I(0x144);
        if(age==0 || age==5 || age==10) {
            float packet[3]={PARAM[0],0.0f,4.0f};spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=static_cast<float>(RF(14)+(F(0x12c)+180.0)-7.0);packet[1]=10.0f;packet[2]=7.0f;
            double center_y=F(0xf0);unsigned char facing=B(0x104);double center_x=F(0xec);
            float y=static_cast<float>(center_y-lookup_orientation_sine_quantized_abs(-PARAM[0])*35.0);
            float x=static_cast<float>(center_x-lookup_orientation_cosine_quantized_abs(-PARAM[0])*static_cast<float>(35*C(0x104)));
            spawn_unparented(812,x,y,facing,1,packet,3);
        }
        F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));
        float *parameters=PARAM;parameters[1]*=0.95f;MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)<45 && I(0x180)==0) {
            F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        }else {
            WAVE(2);float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(812,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;spawn_unparented(812,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=1.0f;
            float count=static_cast<float>(FIELD(OWNER,signed char,0x60c)+8.0);float index=0.0f;
            if(count>0.0f) do {
                packet[0]=static_cast<float>(RF(40)+index*360.0/count);
                packet[1]=static_cast<float>(RF(20)*static_cast<double>(0.1f)+8.0);
                spawn_unparented(812,F(0xec),F(0xf0),B(0x104),1,packet,3);index+=1.0;
            }while(index<count);
            RETIRE();
        }
        break;
    }
    case 1: {
        if(emit_repeated(0,0,4)) RETIRE();F(0xf8)-=0.5;
        F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));double next_y=static_cast<double>(F(0xf0))+F(0xf8);
        if(!(stage_surface_height()>=next_y) && I(0x180)==0) {
            F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        }else {
            WAVE(2);float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(812,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;spawn_unparented(812,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        break;
    }
    case 2:
        if(S(0x140)==0) {
            float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 3:
        if(S(0x140)==0) {
            float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 4:
        F(0x12c)+=10.0;F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 5:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=2) RETIRE();break;
    case 6:
        F(0x11c)+=0.2f;F(0x120)+=0.2f;if(B(0x113)<20) RETIRE();B(0x113)-=20;break;
    case 7: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);MOVE();F(0x11c)+=0.05f;F(0x11c)=F(0x120);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    }
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 815: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)<=3) {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)==520) {F(0xec)=static_cast<float>(60*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+108.0);}
        if(FIELD(owner,short,0x13c)==521) {F(0xec)=static_cast<float>(20*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+145.0);}
    }
    if(S(0x13e)<=1) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action>49 && action<150) {
            for(int count=0;count<40;++count) emit_effect(201,static_cast<float>(RF(15)+(static_cast<double>(30*count*C(0x104))+F(0xec))),F(0xf0),B(0x104),1);
            RETIRE();
        }
        F(0x12c)=PARAM[1]+F(0x12c);action=FIELD(owner,short,0x13c);
        if(action!=520 && action!=521) {select_sequence(2);return;}
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)!=0 && ++S(0x364)>3) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)>=30 || C(0x184)<=0) {next_sequence_block();return;}
    }
    if(S(0x13e)==3) {if(!RELATED || FIELD(RELATED,short,0x13e)==2) RETIRE();}
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) --I(0x330);
    return;

}
case 816: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(S(0x140)!=0) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;FINISH();}
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if((action==525 || action==526) && FIELD(owner,short,0x13e)<=1) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);
        }else {
            if((action!=527 && action!=528) || FIELD(owner,short,0x13e)>1) {next_sequence_frame();return;}
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0);
        }
        float angle=FIELD(owner,float,0x7b0);if(PARAM[1]!=0.0f) angle=-angle;F(0x12c)=angle;
        action=FIELD(owner,short,0x13c);
        if(action==525 || action==526) {F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);}
        action=FIELD(owner,short,0x13c);
        if(action==527 || action==528) {F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0);}
        F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(10*I(0x144)))*0.5+static_cast<double>(0.6f));FINISH();
    }
    case 1: {
        F(0x11c)=1.0f;F(0x120)=1.0f;
        if(I(0x180)!=0 && ++S(0x364)>=3) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)%5==0) {
            float packet[3]={RF(360),0.0f,2.0f};spawn_unparented(816,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(C(0x184)<=0 || I(0x144)>=30) RETIRE();
        short action=FIELD(OWNER,short,0x13c);if(action<525 || action>528) RETIRE();FINISH();
    }
    case 2:
        F(0x12c)+=20.0;F(0x11c)+=0.1f;F(0x120)+=0.1f;
        if(B(0x113)<20) RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x110)-=20;FINISH();
    case 3: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if((action==525 || action==526) && FIELD(owner,short,0x13e)==2) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);FINISH();
        }
        if((action!=527 && action!=528) || FIELD(owner,short,0x13e)!=2) RETIRE();
        F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0);FINISH();
    }
    case 4: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if((action==525 || action==526) && FIELD(owner,short,0x13e)<=1) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);
        }
        action=FIELD(owner,short,0x13c);
        if((action==527 || action==528) && FIELD(owner,short,0x13e)<=1) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0);
        }
        double sine=lookup_orientation_sine_quantized_abs(static_cast<float>(3*I(0x144)));
        F(0x12c)=static_cast<float>(sine*(PARAM[1]*FIELD(OWNER,float,0x7b0)));
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;FINISH();
    }
    default:FINISH();
    }


}
case 817: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        F(0x12c)+=6.0;
        if(S(0x140)==0) {
            if(emit_repeated(0,3,8)) RETIRE();
            publish_bounds_descriptor(-20,static_cast<int>(F(0x11c)*50.0),20,static_cast<int>(F(0x11c)*-50.0),static_cast<short>(static_cast<int>(PARAM[0])),0,0);
            F(0x11c)+=0.03f;F(0x120)=F(0x11c);
            if(I(0x144)%10==0) {
                float packet[4]={PARAM[0],1.0f,2.0f,F(0x11c)};
                if(FIELD(OWNER,signed char,0x60d)>=4) packet[2]=3.0f;
                spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,4);
            }
            advance_six(0);
            advance_phase(3);if(I(0x180)!=0) next_sequence_frame();
        }
        if(S(0x140)==1) {
            float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
            if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
        }
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        MOTION->set_components(PARAM[0],PARAM[1]);
    }
    if(S(0x13e)==1) {
        F(0x12c)+=6.0;
        if(S(0x140)==0) {
            if(emit_repeated(0,3,8)) RETIRE();
            publish_bounds_descriptor(static_cast<int>(F(0x11c)*-20.0),static_cast<int>(F(0x11c)*50.0),static_cast<int>(F(0x11c)*20.0),static_cast<int>(F(0x11c)*-50.0),static_cast<short>(static_cast<int>(PARAM[0])),0,0);
            F(0x11c)+=0.05f;F(0x120)=F(0x11c);
            if(I(0x144)%5==0) {
                float packet[4]={PARAM[0],1.0f,2.0f,F(0x11c)};
                if(FIELD(OWNER,signed char,0x60d)>=4) packet[2]=3.0f;
                spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,4);
            }
            advance_six(0);
            if(I(0x180)!=0) {
                if(C(0x184)>0) {if(++S(0x364)>6) {S(0x364)=0;I(0x180)=0;}}
                else next_sequence_frame();
            }
        }
        if(S(0x140)==1) {
            float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
            if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
        }
        if(F(0xec)>1580.0f || F(0xec)<-300.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        MOTION->set_components(PARAM[0],PARAM[1]);
    }
    if(S(0x13e)==2) {
        MOTION->set_components(PARAM[0],PARAM[1]);F(0x11c)+=0.1f;F(0x120)+=0.1f;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
    }
    if(S(0x13e)==3) {
        F(0x12c)+=6.0;
        if(S(0x140)==0) {
            if(emit_repeated(0,0,0)) RETIRE();
            publish_bounds_descriptor(-20,static_cast<int>(F(0x11c)*50.0),20,static_cast<int>(F(0x11c)*-50.0),static_cast<short>(static_cast<int>(PARAM[0])),0,0);
            F(0x11c)+=0.03f;F(0x120)=F(0x11c);advance_six(0);
            if(I(0x180)!=0 || I(0x144)>=30) {next_sequence_frame();B(0x184)=0;}
        }
        if(S(0x140)==1) {
            float *parameters=PARAM;F(0x11c)+=0.03f;F(0x120)=F(0x11c);
            parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
            if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
        }
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        MOTION->set_components(PARAM[0],PARAM[1]);
    }
    MOVE();FINISH();


}
case 820: {
 {
    if(I(0x180)==5) RETIRE();short owner_action=FIELD(OWNER,short,0x13c);
    if(owner_action>49 && owner_action<150 && S(0x13e)<=1) {select_sequence(2);return;}
    if(S(0x13e)==0) {
        F(0x370)+=5.0;if(F(0x370)>90.0f) F(0x370)=90.0f;
        F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x370))*PARAM[0]);F(0x120)=F(0x11c);
        if(F(0x370)>=90.0f) {next_sequence_block();return;}
    }
    if(S(0x13e)==1) {
        double y_squared=square_float_value(static_cast<float>(F(0xf0)-(FIELD(TARGET,float,0xf0)+100.0)));
        double distance_squared=square_float_value(F(0xec)-FIELD(TARGET,float,0xec))+y_squared;
        if(square_float_value(static_cast<float>(F(0x11c)*100.0))>distance_squared) {
            void *owner=OWNER;signed char level=FIELD(owner,signed char,0x606);
            FIELD(owner,short,0x7ac)=static_cast<short>(5*((level>=1)+(level>=3)+2*(level>=4)+1));
        }
        if(I(0x144)%15==0) {
            float packet[3]={PARAM[0],0.0f,3.0f};spawn_unparented(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(B(0x113)<10) B(0x113)=0;else B(0x113)-=10;
        if(PARAM[1]<=static_cast<double>(I(0x144))) {next_sequence_block();return;}
    }
    if(S(0x13e)==2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==3) {
        F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        B(0x113)=static_cast<unsigned char>(static_cast<int>(lookup_orientation_sine_quantized_abs(static_cast<float>(6*I(0x144)))*255.0));
        if(6*I(0x144)>=180) RETIRE();
    }
    FINISH();
}

}
case 821: {
 {
    if(I(0x180)==5) RETIRE();short owner_action=FIELD(OWNER,short,0x13c);
    if(owner_action>49 && owner_action<150 && S(0x13e)<=1) {select_sequence(2);return;}
    if(S(0x13e)==0) {
        F(0x370)+=5.0;if(F(0x370)>90.0f) F(0x370)=90.0f;
        F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x370))*PARAM[0]);F(0x120)=F(0x11c);
        if(F(0x370)>=90.0f) {next_sequence_block();return;}
    }
    if(S(0x13e)==1) {
        double y_squared=square_float_value(static_cast<float>(F(0xf0)-(FIELD(TARGET,float,0xf0)+100.0)));
        double distance_squared=square_float_value(F(0xec)-FIELD(TARGET,float,0xec))+y_squared;
        if(square_float_value(static_cast<float>(F(0x11c)*100.0))>distance_squared) {
            void *owner=OWNER;signed char level=FIELD(owner,signed char,0x60a);
            FIELD(owner,short,0x7ae)=static_cast<short>(20*(level>=4)+30*(level>=2)+15);
        }
        if(I(0x144)%15==0) {
            float packet[3]={PARAM[0],0.0f,3.0f};spawn_unparented(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(B(0x113)<10) B(0x113)=0;else B(0x113)-=10;
        if(PARAM[1]<=static_cast<double>(I(0x144))) {next_sequence_block();return;}
    }
    if(S(0x13e)==2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==3) {
        F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        B(0x113)=static_cast<unsigned char>(static_cast<int>(lookup_orientation_sine_quantized_abs(static_cast<float>(6*I(0x144)))*255.0));
        if(6*I(0x144)>=180) RETIRE();
    }
    FINISH();
}


}
case 822: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if((action!=550 && action!=551) || FIELD(owner,short,0x13e)>1) RETIRE();position_relative_to_owner(0,120);
        if(I(0x144)%5==0) {
            float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(822,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%8==0) {
            float packet[3]={RF(360),0.0f,3.0f};
            spawn_parented(822,F(0xec),F(0xf0),static_cast<unsigned char>(1-2*(static_cast<unsigned>(selector_random_roll(100))>50u)),1,packet,3);
        }
        if(I(0x180)!=0 && ++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
    }
    if(S(0x13e)==1) {
        F(0x12c)+=10.0;F(0x11c)+=0.2f;F(0x120)=F(0x11c);
        if(B(0x113)<25) RETIRE();B(0x113)-=25;B(0x111)-=25;B(0x110)-=25;
    }
    if(S(0x13e)==2) {
        F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        B(0x113)=static_cast<unsigned char>(static_cast<int>(lookup_orientation_sine_quantized_abs(static_cast<float>(6*I(0x144)))*255.0));
        if(6*I(0x144)>=180) RETIRE();
    }
    if(S(0x13e)==3) {
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        F(0x12c)+=2.0;F(0x11c)+=0.1f;F(0x120)*=0.95f;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
    }
    FINISH();


}
case 825: {

    if(I(0x180)==5) RETIRE();
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    switch(S(0x13e)) {
    case 0:case 1: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {
            short action=FIELD(owner,short,0x13c);if(action==560 || action==561) S(0x364)=1;
        }
        if(S(0x364)!=0) {
            if(B(0x113)<10) RETIRE();B(0x113)-=10;return;
        }
        if(emit_repeated(0,3,5)) RETIRE();
        if(S(0x13e)==1 && S(0x140)>=18) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        MOVE();
        break;
    }
    case 2:case 3: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {
            short action=FIELD(owner,short,0x13c);if(action==560 || action==561) S(0x364)=1;
        }
        if(S(0x364)!=0) {
            if(B(0x113)<10) RETIRE();B(0x113)-=10;return;
        }
        if(emit_repeated(0,3,5)) RETIRE();
        if(S(0x13e)==3 && S(0x140)>=20) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        F(0xf8)-=F(0x100);F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        break;
    }
    case 4:case 5: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {
            short action=FIELD(owner,short,0x13c);if(action==560 || action==561) S(0x364)=1;
        }
        if(S(0x364)!=0) {
            if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
        }
        if(emit_repeated(0,3,5)) RETIRE();
        if(S(0x13e)==5) {short level=S(0x36c);if(level==3 || (level>=4 && S(0x366)>=1)) S(0x364)=1;}
        MOVE();
        break;
    }
    case 6:case 7: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13e)==0 && FIELD(owner,short,0x140)==0) {
            short action=FIELD(owner,short,0x13c);if(action==560 || action==561) S(0x364)=1;
        }
        if(S(0x364)!=0) {
            if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
        }
        if(emit_repeated(0,3,5)) RETIRE();
        if(S(0x13e)==7) {short level=S(0x36c);if(level==3 || (level>=4 && S(0x366)>=1)) S(0x364)=1;}
        F(0xf8)-=F(0x100);F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        break;
    }
    case 8: {
        if(emit_repeated(0,0,3)) RETIRE();float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<3.0f) parameters[1]=3.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        if(I(0x144)>120 || I(0x180)!=0) {
            for(int count=5;count!=0;--count) {
                float packet[3]={RF(360),static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10)),2.0f};
                spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOVE();break;
    }
    case 9: {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0) replace_secondary(991,15.0f,10,1,2);
        if(emit_repeated(0,3,5)) RETIRE();PARAM[1]+=0.25;turn_heading(0.0f,0.2f,100.0f);
        float *parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)%4==0) {float packet[3]={F(0x12c),0.0f,3.0f};spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(I(0x180)!=0 || I(0x144)>=180) {
            WAVE(4);float packet[3]={0.0f,0.0f,10.0f};spawn_unparented(825,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=5.0f;spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        break;
    }
    case 10:
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=4;S(0x366)=1;}
            }
            if(S(0x366)==1) {float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);}
            advance_six(0);
            if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    }
    if(advance_frame()) RETIRE();
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1 && S(0x36c)>=3) {select_sequence(4);return;}
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) RETIRE();
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==3) {
            F(0xf4)*=0.2f;F(0xf8)=0.2f*F(0xf8);F(0x100)=0.05f;
            if(S(0x36c)>=3) {select_sequence(6);return;}
        }
    }
    if(S(0x13e)==1 && S(0x142)==0) {
        short frame=S(0x140);
        if(frame==2 || frame==5 || frame==8 || frame==11 || frame==14 || frame==17) {
            F(0x378)=0.0f;F(0x378)=static_cast<float>(RF(9)-4.0+F(0x378));
            float packet[3]={F(0x378),25.0f,8.0f};
            spawn_unparented(825,static_cast<float>(56*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+106.0),B(0x104),1,packet,3);
            packet[2]=1.0f;spawn_unparented(800,static_cast<float>(56*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+106.0),B(0x104),1,packet,3);
        }
        if((S(0x36c)==0 && S(0x142)==0 && S(0x140)==12) || (S(0x36c)==1 && S(0x142)==0 && S(0x140)==15)) {select_frame(18);return;}
    }
    if(S(0x13e)==3 && S(0x142)==0) {
        short frame=S(0x140);
        if(frame==4 || frame==7 || frame==10 || frame==13 || frame==16 || frame==19) {
            F(0x378)=30.0f;F(0x378)=static_cast<float>(RF(9)-4.0+F(0x378));
            float packet[3]={F(0x378),25.0f,8.0f};
            spawn_unparented(825,static_cast<float>(56*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+100.0),B(0x104),1,packet,3);
            packet[2]=1.0f;spawn_unparented(800,static_cast<float>(56*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+100.0),B(0x104),1,packet,3);
        }
        if((S(0x36c)==0 && S(0x142)==0 && S(0x140)==14) || (S(0x36c)==1 && S(0x142)==0 && S(0x140)==17)) {select_frame(20);return;}
    }
    if(S(0x13e)==4 && S(0x142)==0 && S(0x140)==4) {
        void *target=TARGET;
        F(0x378)=-atan2_degrees(FIELD(target,float,0xf0)-F(0xf0),static_cast<float>((FIELD(target,float,0xec)-F(0xec))*C(0x104)));
        if(F(0x378)<-10.0) F(0x378)=-10.0f;if(F(0x378)>10.0) F(0x378)=10.0f;
        float packet[3]={F(0x378),5.0f,9.0f};
        spawn_unparented(825,static_cast<float>(72*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+95.0),B(0x104),1,packet,3);
        packet[2]=4.0f;spawn_unparented(801,static_cast<float>(72*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+95.0),B(0x104),1,packet,3);WAVE(3);
    }
    if(S(0x13e)==5 && S(0x36c)>=4 && I(0x144)>=4 && S(0x366)==0) {select_sequence(4);++S(0x366);return;}
    if(S(0x13e)==6 && S(0x142)==0 && S(0x140)==4) {
        void *target=TARGET;
        F(0x378)=-atan2_degrees(FIELD(target,float,0xf0)-F(0xf0),static_cast<float>((FIELD(target,float,0xec)-F(0xec))*C(0x104)));
        if(F(0x378)<20.0) F(0x378)=20.0f;if(F(0x378)>50.0) F(0x378)=50.0f;
        float packet[3]={F(0x378),5.0f,9.0f};
        spawn_unparented(825,static_cast<float>(64*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+105.0),B(0x104),1,packet,3);
        packet[2]=4.0f;spawn_unparented(801,static_cast<float>(64*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+105.0),B(0x104),1,packet,3);WAVE(3);
    }
    if(S(0x13e)==7 && S(0x36c)>=4 && I(0x144)>=4 && S(0x366)==0) {select_sequence(6);++S(0x366);}
    return;


}
case 826: {
 {
    if(I(0x180)==5) RETIRE();short phase=S(0x13e);
    if(phase<=3) {
        if(emit_repeated(0,1,2)) RETIRE();void *owner=OWNER;
        double cosine=lookup_orientation_cosine_quantized_abs(PARAM[0]);float *parameters=PARAM;
        float x=static_cast<float>(cosine*(FIELD(owner,float,0x73c)*static_cast<double>(C(0x104)))+FIELD(owner,float,0xec));
        owner=OWNER;F(0xec)=x;
        double sine=lookup_orientation_sine_quantized_abs(parameters[0]);
        F(0xf0)=static_cast<float>(sine*(FIELD(owner,float,0x73c)*static_cast<double>(C(0x104)))+FIELD(owner,float,0xf0));
        if(S(0x13e)==1 && FIELD(owner,short,0x730)==1) next_sequence_block();
        if(S(0x13e)==2 && FIELD(OWNER,short,0x730)>=20) next_sequence_block();
        phase=S(0x13e);if(phase==3 && FIELD(OWNER,float,0x73c)==0.0f) RETIRE();
        short action=FIELD(OWNER,short,0x13c);if(action<565 || action>568) RETIRE();
    }
    if(phase==5) {
        F(0x370)-=0.1f;if(F(0x370)<0.01f) F(0x370)=0.01f;F(0x11c)+=F(0x370);F(0x120)=F(0x11c);
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
    }
    FINISH();
}

}
case 848: {

    if(S(0x13e)<=2) {
        F(0xf4)=0.0f;F(0xf8)=0.0f;if(B(0x113)<=15) --I(0x330);else B(0x113)-=15;
    }
    if(S(0x13e)==3) {
        F(0xf8)-=0.3f;if(B(0x113)<=15) --I(0x330);else B(0x113)-=15;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
    }
    if(S(0x13e)==4) {
        F(0xf4)=0.0f;F(0xf8)=0.0f;if(B(0x113)<=15) --I(0x330);else B(0x113)-=15;
    }
    if(S(0x13e)==5 || S(0x13e)==6) {
        F(0xf8)-=0.5;double next_y=static_cast<double>(F(0xf8))+F(0xf0);
        if(stage_surface_height()>=next_y) {
            F(0xf8)=0.0f;F(0xf4)=0.0f;F(0xf0)=stage_surface_height();select_sequence(7);return;
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
    }
    if(S(0x13e)>=5 && S(0x13e)<=7) {
        if(B(0x113)<=10) --I(0x330);else B(0x113)-=10;advance_frame();
    }
    if(S(0x13e)>=9 && S(0x13e)<=10) {
        if(S(0x13e)==10) {if(B(0x113)<=10) --I(0x330);else B(0x113)-=10;}
        F(0xf4)=PARAM[1];F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_frame();
    }
    return;

}
case 849: {

    switch(S(0x13e)) {
    case 1:case 2: {
        short action=FIELD(OWNER,short,0x13c);if(action!=301 && action!=321) RETIRE();position_relative_to_owner(0,0);
        if(S(0x13e)==2 && B(0x113)>=12) {B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}
        break;
    }
    case 3:case 4:
        if(FIELD(OWNER,short,0x13c)!=307) RETIRE();position_relative_to_owner(0,0);
        if(S(0x13e)==4 && B(0x113)>=12) {B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}
        break;
    case 5:case 6: {
        short action=FIELD(OWNER,short,0x13c);if(action!=305 && action!=322) RETIRE();position_relative_to_owner(0,0);
        if(S(0x13e)==6) {if(B(0x113)>=12) {B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}F(0x11c)*=0.98f;F(0x120)=F(0x11c);}
        break;
    }
    case 7:
        if(FIELD(OWNER,short,0x13c)!=309) RETIRE();position_relative_to_owner(0,0);
        if(S(0x13e)>=2) {if(B(0x113)>=12) {B(0x113)-=12;B(0x111)-=12;B(0x110)-=12;}F(0x11c)*=0.98f;F(0x120)=F(0x11c);}
        break;
    }
    FINISH();


}
case 850: {

    if(S(0x13e)==0) {
        if(S(0x140)==0) {
            publish_bounds_descriptor(static_cast<int>(F(0x11c)*-35.0),static_cast<int>(F(0x11c)*75.0),static_cast<int>(F(0x11c)*35.0),static_cast<int>(F(0x11c)*-75.0),static_cast<short>(static_cast<int>(PARAM[0])),0,0);
            F(0x11c)+=0.03f;F(0x120)=F(0x11c);advance_six(0);int collision=I(0x180);
            if(collision!=0) {
                if(C(0x184)<=0) {next_sequence_frame();return;}
                if(collision==4 || collision==8) S(0x364)=4;
                if(++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
            }
        }
        if(S(0x140)==1) {
            float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
            if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
        }
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);
    }else if(S(0x13e)==1) {
        F(0x12c)+=6.0;if(!RELATED) RETIRE();
        double cosine=lookup_orientation_cosine_quantized_abs(static_cast<float>(6*I(0x144)+PARAM[0]));void *related=RELATED;float *parameters=PARAM;
        F(0xec)=static_cast<float>(cosine*static_cast<float>(2*I(0x144))*static_cast<double>(0.3f)*C(0x104)+FIELD(related,float,0xec));
        double sine=lookup_orientation_sine_quantized_abs(static_cast<float>(6*I(0x144)+parameters[0]));
        F(0xf0)=static_cast<float>(sine*static_cast<float>(2*I(0x144))+FIELD(related,float,0xf0));
        F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);
        if(FIELD(related,short,0x140)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
        else if(I(0x144)%10==0) {
            float packet[4]={PARAM[0],1.0f,2.0f,F(0x11c)};spawn_unparented(850,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
    }else if(S(0x13e)==2) {
        MOTION->set_components(PARAM[0],PARAM[1]);F(0x11c)+=0.1f;F(0x120)+=0.1f;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
    }
    MOVE();FINISH();


}
case 852: {

    switch(S(0x13e)) {
    case 0: {
        F(0x12c)=PARAM[0];
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=static_cast<float>(RF(14)+(PARAM[0]+180.0)-7.0);packet[1]=10.0f;packet[2]=3.0f;
            double center_y=F(0xf0);unsigned char facing=B(0x104);double center_x=F(0xec);
            float y=static_cast<float>(center_y-lookup_orientation_sine_quantized_abs(-PARAM[0])*35.0);
            float x=static_cast<float>(center_x-lookup_orientation_cosine_quantized_abs(-PARAM[0])*static_cast<float>(35*C(0x104)));
            spawn_unparented(852,x,y,facing,1,packet,3);
        }
        float *parameters=PARAM;parameters[1]*=0.95f;MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);
        if(PARAM[3]<=static_cast<double>(I(0x144))) {
            WAVE(2);float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(852,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=2.0f;
            for(int count=4;count!=0;--count) {
                packet[0]=RF(360);float speed=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+15.0);
                spawn_unparented(852,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        break;
    }
    case 1:
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=1;S(0x366)=1;}
            }
            if(S(0x366)==1) {float variation=static_cast<float>(static_cast<double>(0.1f)*(I(0x144)%2));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);}
            advance_six(0);advance_phase(3);if(I(0x144)>=120) {next_sequence_frame();return;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 2: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)>=15) {F(0x11c)*=0.95f;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        MOVE();break;
    }
    case 3: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<1.0f) parameters[1]=1.0f;MOTION->set_components(parameters[0],parameters[1]);MOVE();
        F(0x11c)+=0.05f;F(0x11c)=F(0x120);
        if(B(0x113)<=20) RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;break;
    }
    case 4:
        F(0x12c)+=10.0;F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 5:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=2) RETIRE();break;
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 853: {

    if(S(0x13e)==0) {
        if(S(0x140)==0) {
            publish_bounds_descriptor(static_cast<int>(F(0x11c)*-35.0),static_cast<int>(F(0x11c)*75.0),static_cast<int>(F(0x11c)*35.0),static_cast<int>(F(0x11c)*-75.0),static_cast<short>(static_cast<int>(PARAM[0])),0,0);
            F(0x11c)+=0.2f;if(F(0x11c)>=4.0f) F(0x11c)=4.0f;F(0x120)=F(0x11c);advance_six(0);int collision=I(0x180);
            if(collision!=0) {
                if(C(0x184)<=0) {next_sequence_frame();return;}
                if(collision==4 || collision==8) S(0x364)=4;
                if(++S(0x364)>=4) {S(0x364)=0;I(0x180)=0;}
            }
        }
        if(S(0x140)==1) {
            float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
            if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
        }
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOTION->set_components(PARAM[0],PARAM[1]);
    }else if(S(0x13e)==1) {
        F(0x12c)+=12.0;if(!RELATED) RETIRE();void *related=RELATED;
        F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
        F(0x11c)=FIELD(related,float,0x11c);F(0x120)=F(0x11c);
        if(FIELD(related,short,0x140)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
        else if(I(0x144)%5==0) {
            float packet[4]={PARAM[0],1.0f,2.0f,F(0x11c)};spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
    }else if(S(0x13e)==2) {
        MOTION->set_components(PARAM[0],PARAM[1]);F(0x11c)+=0.02f;F(0x120)+=0.02f;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;
    }
    MOVE();FINISH();


}
case 855: {

    if(S(0x13e)<=1) {
        F(0x11c)+=0.8f;F(0x120)=F(0x11c);
        if(S(0x140)>=2) {if(B(0x113)<30) RETIRE();B(0x113)-=30;B(0x111)-=30;B(0x110)-=30;}
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)==605 && S(0x13e)<=1) {F(0xec)=FIELD(owner,float,0xec);F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+130.0);}
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)==4 && S(0x364)<2) {++S(0x364);++B(0x184);I(0x180)=0;}
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
    return;


}
case 856: {

    switch(S(0x13e)) {
    case 0:
        if(I(0x144)%2==0) F(0x12c)=RF(360);advance_six(0);break;
    case 1:
        F(0x12c)=RF(360);F(0x11c)*=0.85f;F(0x120)=F(0x11c);
        if(I(0x144)>=10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
        break;
    case 2:
        F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0x370)*=0.85f;if(F(0x370)<=0.01f) F(0x370)=0.01f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;break;
    case 3:case 4:case 5:case 6:
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.97f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;
        F(0xf4)+=0.25;F(0xf8)*=0.98f;F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);break;
    case 7:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=0.95f;
        if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;MOVE();break;
    case 8: {
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));
        F(0x12c)=F(0x374)+F(0x12c);F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        if(I(0x144)>=0) {if(B(0x113)<=5) RETIRE();B(0x113)-=5;}
        break;
    }
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) {
        float packet[3];
        for(int count=10;count!=0;--count) {
            packet[0]=RF(360);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+4.0);packet[2]=static_cast<float>(RF(4)+3.0);
            unsigned char facing=B(0x104);
            float y=static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*(packet[1]*10.0)+F(0xf0));
            float x=static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*(packet[1]*10.0)*C(0x104)+F(0xec));
            spawn_unparented(856,x,y,facing,1,packet,3);
        }
        packet[2]=7.0f;
        for(int count=10;count!=0;--count) {
            packet[0]=RF(360);packet[1]=static_cast<float>(RF(100)*static_cast<double>(0.1f)+6.0);packet[2]=7.0f;
            spawn_unparented(856,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        int collision=I(0x180);
        if((collision==1 || collision==7) && FIELD(TARGET,unsigned char,0x72c)!=2)
            reinterpret_cast<UdongeUpdateOwnerView*>(TARGET)->apply_deferred_counter_558(500);
    }
    return;


}
case 857: {

    switch(S(0x13e)) {
    case 0:
        if(I(0x144)%2==0) F(0x12c)=RF(360);advance_six(0);break;
    case 1:
        F(0x12c)=RF(360);F(0x11c)*=0.85f;F(0x120)=F(0x11c);
        if(I(0x144)>=10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;}
        break;
    case 2:
        F(0x11c)+=F(0x370);F(0x120)=F(0x11c);F(0x370)*=0.85f;if(F(0x370)<=0.01f) F(0x370)=0.01f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;break;
    case 3:case 4:case 5:case 6:
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.97f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x110)-=5;
        F(0xf4)+=0.35f;F(0xf8)*=0.98f;F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);break;
    case 7:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=0.95f;
        if(B(0x113)<8) RETIRE();B(0x113)-=8;B(0x111)-=8;B(0x110)-=8;MOVE();break;
    case 8: {
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));
        F(0x12c)=F(0x374)+F(0x12c);F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        if(I(0x144)>=0) {if(B(0x113)<=5) RETIRE();B(0x113)-=5;}
        break;
    }
    case 9: {
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==9) replace_secondary(991,15.0f,5,1,2);
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;parameters[1]+=2.5;if(parameters[1]>=40.0f) parameters[1]=40.0f;
        float packet[3]={static_cast<float>(I(0x144)*10.0),0.0f,10.0f};
        spawn_unparented(857,static_cast<float>(20*C(0x104)+F(0xec)),F(0xf0),B(0x104),1,packet,3);
        advance_six(0);advance_phase(3);
        if(I(0x180)!=0) {
            float explosion[3]={0.0f,0.0f,0.0f};spawn_unparented(857,F(0xec),F(0xf0),B(0x104),1,explosion,3);WAVE(55);RETIRE();
        }
        if(F(0xec)<-100.0 || F(0xec)>1380.0f || F(0xf0)<-200.0 || F(0xf0)>1280.0) RETIRE();
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);break;
    }
    case 10:
        F(0x11c)+=0.1f;F(0x120)=F(0x11c);F(0x12c)+=1.0;
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;break;
    case 11:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=3) RETIRE();break;
    case 12:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=0.95f;MOVE();F(0x11c)+=0.01f;F(0x120)=0.95f*F(0x120);
        if(I(0x144)>=0) {if(B(0x113)<=5) RETIRE();B(0x113)-=5;}break;
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) {
        float packet[3];
        for(int count=15;count!=0;--count) {
            packet[0]=RF(360);packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+4.0);packet[2]=static_cast<float>(RF(5)+4.0);
            unsigned char facing=B(0x104);
            float y=static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*(packet[1]*10.0)+F(0xf0));
            float x=static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*(packet[1]*10.0)*C(0x104)+F(0xec));
            spawn_unparented(856,x,y,facing,1,packet,3);
        }
        packet[2]=7.0f;
        for(int count=10;count!=0;--count) {
            packet[0]=RF(360);packet[1]=static_cast<float>(RF(100)*static_cast<double>(0.1f)+6.0);packet[2]=7.0f;
            spawn_unparented(856,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        int collision=I(0x180);
        if((collision==1 || collision==7) && FIELD(TARGET,unsigned char,0x72c)!=2) {
            reinterpret_cast<UdongeUpdateOwnerView*>(TARGET)->apply_deferred_counter_558(500);
            reinterpret_cast<UdongeUpdateOwnerView*>(TARGET)->apply_deferred_counter_558(500);
        }
    }
    return;


}
case 858: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        double next_y=static_cast<double>(F(0xf0))+F(0xf8);
        if(stage_surface_height()>=next_y) {
            float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(858,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=3.0f;spawn_unparented(858,640.0f,-200.0f,B(0x104),1,packet,3);WAVE(52);RETIRE();
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);break;
    }
    case 1:
        if(I(0x144)%3==0) {
            float packet[3];packet[0]=static_cast<float>(-70.0-RF(40));packet[1]=static_cast<float>(RF(5)+10.0);packet[2]=2.0f;
            spawn_unparented(858,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%30==0) WAVE(53);if(FIELD(TARGET,short,0x174)<=0 || I(0x144)>=600) RETIRE();break;
    case 2:
        MOTION->set_components(PARAM[0],PARAM[1]);F(0x11c)+=0.1f;F(0x120)=F(0x11c);F(0x12c)=F(0x370)+F(0x12c);
        if(B(0x113)<10) RETIRE();B(0x113)-=10;MOVE();break;
    case 3:
        if(S(0x364)==0) {
            if(B(0x113)>250) B(0x113)=255;else B(0x113)+=5;
            void *target=TARGET;
            if(FIELD(target,float,0xf0)<=200.0) {short health=FIELD(target,short,0x174);if(health>=3) FIELD(target,short,0x174)=health-2;}
            if(FIELD(TARGET,short,0x174)<=0 || I(0x144)>=600) S(0x364)=1;
        }
        if(S(0x364)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(I(0x144))+I(0x144)))*0.1f+3.0);break;
    }
    FINISH();


}
case 859: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:
        if(I(0x144)==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(859,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)==0 || I(0x144)==10 || I(0x144)==20) {float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(859,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%5==0 && I(0x144)>=15) {
            float packet[3]={0.0f,0.0f,3.0f};
            spawn_unparented(859,static_cast<float>(RF(200)+(FIELD(OWNER,float,0xec)-100.0)),static_cast<float>(RF(200)+(FIELD(OWNER,float,0xf0)+50.0)),B(0x104),1,packet,3);
        }
        F(0x11c)*=0.9f;F(0x120)=F(0x11c);if(B(0x113)<30) B(0x113)=0;else B(0x113)-=30;
        if(I(0x144)>=50) RETIRE();break;
    case 1:
        F(0x12c)+=5.0;F(0x11c)+=0.05f;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;break;
    case 2:
        F(0x11c)+=0.2f;F(0x120)=F(0x11c);if(B(0x113)<15) RETIRE();B(0x113)-=15;break;
    case 3:
        F(0x11c)*=0.9f;F(0x120)=F(0x11c);if(B(0x113)<30) RETIRE();B(0x113)-=30;break;
    case 4:
        position_relative_to_owner(0,static_cast<int>(F(0x370)));F(0x370)+=8.0;
        if(B(0x113)<6) RETIRE();B(0x113)-=6;break;
    case 5:
        F(0x120)+=0.05f;F(0x11c)*=0.995f;if(B(0x113)<6) RETIRE();B(0x113)-=6;break;
    case 6:
        if(I(0x144)>=2) B(0x184)=0;F(0x11c)*=0.98f;F(0x120)=F(0x11c);
        if(B(0x113)<6) RETIRE();B(0x110)-=6;B(0x112)-=6;B(0x113)-=6;break;
    case 7:case 8:
        F(0x11c)+=0.2f;F(0x120)=F(0x11c);if(B(0x113)<6) RETIRE();B(0x110)-=6;B(0x112)-=6;B(0x113)-=6;break;
    case 10: {
        float *parameters=PARAM;parameters[1]*=0.95f;F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.99f;
        F(0x11c)+=0.01f;F(0x120)=F(0x11c);MOTION->set_components(parameters[0],parameters[1]);
        if(B(0x113)<6) RETIRE();B(0x110)-=6;B(0x112)-=6;B(0x113)-=6;MOVE();break;
    }
    }
    FINISH();


}
case 900: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(FIELD(OWNER,short,0x174)<=0) RETIRE();
        if(I(0x144)==0) {float packet[3]={PARAM[0],0.0f,4.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);}
        if(I(0x144)%4==0) {
            float packet[3];packet[0]=static_cast<float>(RF(14)+(PARAM[0]+180.0)-7.0);packet[1]=10.0f;packet[2]=3.0f;
            double center_y=F(0xf0);unsigned char facing=B(0x104);double center_x=F(0xec);
            float y=static_cast<float>(center_y-lookup_orientation_sine_quantized_abs(-PARAM[0])*35.0);
            float x=static_cast<float>(center_x-lookup_orientation_cosine_quantized_abs(-PARAM[0])*static_cast<float>(35*C(0x104)));
            spawn_unparented(900,x,y,facing,1,packet,3);
        }
        float *parameters=PARAM;parameters[1]-=1.0;if(parameters[1]<=4.0f) parameters[1]=4.0f;
        turn_heading(0.0f,1.0f,100.0f);parameters=PARAM;F(0x12c)=parameters[0];MOTION->set_components(parameters[0],parameters[1]);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);advance_six(0);advance_phase(4);
        if(S(0x174)>-600) {
            if(I(0x180)==0 && I(0x144)<300) break;
            WAVE(6);float packet[3]={0.0f,0.0f,1.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=2.0f;
            for(int count=3;count!=0;--count) {
                packet[0]=RF(360);float speed=static_cast<float>(RF(50)*static_cast<double>(0.1f));packet[1]=static_cast<float>(speed+15.0);
                spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2]=6.0f;spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=7.0f;spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }else {
            float packet[3]={0.0f,0.0f,6.0f};spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=7.0f;spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        RETIRE();
    }
    case 1:
        if(S(0x140)==0) {
            if(F(0x11c)<1.0f) {
                F(0x11c)+=0.2f;F(0x120)+=0.2f;
                if(F(0x11c)>=1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;B(0x184)=4;S(0x366)=1;}
            }
            if(S(0x366)==1) {float variation=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f));F(0x11c)=static_cast<float>(variation+1.0);F(0x120)=F(0x11c);}
            advance_six(0);
            int collision=I(0x180);
            if(collision!=0) {
                if(collision==4 || collision==8) S(0x364)=5;
                if(C(0x184)>0 && ++S(0x364)>5) {S(0x364)=0;I(0x180)=0;}
            }
            if(B(0x184)==0 && F(0x11c)>=1.0f) {S(0x140)=1;S(0x142)=0;}
        }
        if(S(0x140)==1) {F(0x11c)-=0.1f;F(0x120)-=0.1f;if(F(0x11c)<=0.0f) RETIRE();}
        break;
    case 2: {
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<0.5f) parameters[1]=0.5f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(I(0x144)>=15) {F(0x11c)*=0.95f;F(0x120)=F(0x11c);if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        MOVE();break;
    }
    case 3: {
        float *parameters=PARAM;parameters[1]-=0.25;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);MOVE();
        // Both writes are present at5D68A2/5D68AE; do not silently repair the target's overwrite.
        F(0x11c)+=0.05f;F(0x11c)=F(0x120);
        if(B(0x113)<=15) RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;break;
    }
    case 4:
        F(0x12c)+=10.0;F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x110)-=10;B(0x111)-=10;break;
    case 5:
        F(0x11c)*=0.5;F(0x120)=F(0x11c);if(I(0x144)>=2) RETIRE();break;
    case 6:
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.9f;
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)*=0.95f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    case 7:
        F(0x12c)-=F(0x370);F(0x370)*=0.95f;
        F(0x11c)=F(0x374)+F(0x11c);F(0x120)=F(0x11c);F(0x374)*=0.85f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    case 8: {
        float *parameters=PARAM;parameters[1]*=0.95f;MOTION->set_components(parameters[0],parameters[1]);
        if(B(0x113)<4) RETIRE();B(0x113)-=4;
        F(0x12c)=F(0x370)+F(0x12c);F(0x370)*=0.9f;F(0x11c)+=0.005f;F(0x120)=F(0x11c);
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));break;
    }
    }
    FINISH();


}
case 910: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 1:
        F(0x11c)-=0.1f;F(0x120)-=0.1f;break;
    case 2: {
        F(0x11c)-=0.01f;F(0x120)-=0.01f;
        if(F(0x11c)<0.5 || I(0x144)>10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        if(F(0x11c)<=0.0 || B(0x113)==0) RETIRE();
        float *parameters=PARAM;parameters[1]-=1.25;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOVE();break;
    }
    case 3: {
        if(!RELATED) RETIRE();B(0x104)=FIELD(RELATED,unsigned char,0x104);
        void *related=RELATED;
        F(0xec)=static_cast<float>(FIELD(related,signed char,0x104)*FIELD(related,float,0xf4)+FIELD(related,float,0xec));
        F(0xf0)=FIELD(related,float,0xf8)+FIELD(related,float,0xf0);
        F(0x12c)=FIELD(related,float,0x12c);B(0x113)=FIELD(related,unsigned char,0x113);break;
    }
    case 4: {
        if(FIELD(OWNER,short,0x174)<=0) RETIRE();
        if(FIELD(OWNER,short,0x7ae)<=0) {
            B(0x184)=0;
            if(B(0x113)>68) B(0x113)-=10;else B(0x113)=64;
        }else {
            B(0x184)=1;
            if(B(0x113)<245) B(0x113)+=10;else B(0x113)=255;
        }
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<4.0f) parameters[1]=4.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        if(I(0x144)>420 || I(0x180)!=0) {
            for(int count=3;count!=0;--count) {
                float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10));packet[2]=2.0f;
                spawn_unparented(910,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOVE();break;
    }
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    }
    return;


}
case 911: {
 {
    if(I(0x180)==5) RETIRE();
    if(FIELD(OWNER,short,0x174)<=0 && S(0x13e)!=2) {select_sequence(2);return;}
    if(S(0x13e)==0) {
        F(0x370)+=5.0;if(F(0x370)>90.0f) F(0x370)=90.0f;
        F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x370))*PARAM[0]);F(0x120)=F(0x11c);
        if(F(0x370)>=90.0f) {next_sequence_block();return;}
    }
    if(S(0x13e)==1) {
        double y_squared=square_float_value(static_cast<float>(F(0xf0)-(FIELD(TARGET,float,0xf0)+100.0)));
        double distance_squared=square_float_value(F(0xec)-FIELD(TARGET,float,0xec))+y_squared;
        if(square_float_value(static_cast<float>(F(0x11c)*100.0))>distance_squared) {
            FIELD(OWNER,short,0x7ae)=3;
        }
        if(I(0x144)%15==0) {
            float packet[3]={PARAM[0],0.0f,3.0f};spawn_unparented(911,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(B(0x113)<10) B(0x113)=0;else B(0x113)-=10;
        if(PARAM[1]<=static_cast<double>(I(0x144))) {next_sequence_block();return;}
        if(g_match_identifier!=0) {MOTION->set_components(F(0x374),3.0f);MOVE();}
    }
    if(S(0x13e)==2) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
    if(S(0x13e)==3) {
        F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        B(0x113)=static_cast<unsigned char>(static_cast<int>(lookup_orientation_sine_quantized_abs(static_cast<float>(6*I(0x144)))*255.0));
        if(6*I(0x144)>=180) RETIRE();
    }
    FINISH();
}


}
case 912: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(S(0x140)!=0) {if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;FINISH();}
        void *owner=OWNER;if(FIELD(owner,short,0x13c)!=726 || FIELD(owner,short,0x13e)>1) {next_sequence_frame();return;}
        F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);
        float angle=FIELD(owner,float,0x7b0);if(PARAM[1]!=0.0f) angle=-angle;F(0x12c)=angle;
        F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(10*I(0x144)))*0.5+static_cast<double>(0.6f));FINISH();
    }
    case 1: {
        F(0x11c)=1.0f;F(0x120)=1.0f;
        if(I(0x180)!=0 && ++S(0x364)>=3) {S(0x364)=0;I(0x180)=0;}
        if(I(0x144)%5==0) {
            float packet[3]={RF(360),0.0f,2.0f};spawn_unparented(816,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(C(0x184)<=0 || I(0x144)>=30) RETIRE();
        short action=FIELD(OWNER,short,0x13c);if(action<525 || action>528) RETIRE();FINISH();
    }
    case 2:
        F(0x12c)+=20.0;F(0x11c)+=0.1f;F(0x120)+=0.1f;
        if(B(0x113)<20) RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x110)-=20;FINISH();
    case 3: {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if((action==525 || action==526) && FIELD(owner,short,0x13e)==2) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);FINISH();
        }
        if((action!=527 && action!=528) || FIELD(owner,short,0x13e)!=2) RETIRE();
        F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+140.0);FINISH();
    }
    case 4: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)==726 && FIELD(owner,short,0x13e)<=1) {
            F(0xec)=static_cast<float>(50*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);
        }
        double sine=lookup_orientation_sine_quantized_abs(static_cast<float>(3*I(0x144)));
        F(0x12c)=static_cast<float>(sine*(PARAM[1]*FIELD(OWNER,float,0x7b0)));
        if(B(0x113)<10) RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x110)-=10;FINISH();
    }
    default:FINISH();
    }


}
case 920: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 1:
        if(S(0x364)==0) {
            F(0xf4)-=0.25;if(F(0xf4)<1.0f) F(0xf4)=1.0f;F(0xf8)-=0.4f;
            if(F(0xf8)<-3.0f) {select_sequence(3);return;}
            if(FIELD(OWNER,short,0x174)<=0) S(0x364)=1;
        }else {if(B(0x113)<=10) RETIRE();B(0x113)-=10;}
        if(F(0xec)>1220.0f && C(0x104)*static_cast<double>(F(0xf4))>0.0) F(0xf4)=0.0f;
        if(F(0xec)<60.0 && C(0x104)*static_cast<double>(F(0xf4))<0.0) F(0xf4)=0.0f;
        MOVE();break;
    case 3:case 4:
        if(FIELD(OWNER,short,0x174)<=0) S(0x364)=1;
        if(S(0x364)==1) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;}
        if(F(0xec)>1220.0f && C(0x104)*static_cast<double>(F(0xf4))>0.0) F(0xf4)=0.0f;
        if(F(0xec)<60.0 && C(0x104)*static_cast<double>(F(0xf4))<0.0) F(0xf4)=0.0f;
        MOVE();break;
    case 11:
        if(B(0x113)<5) RETIRE();B(0x113)-=5;break;
    case 12:case 13: {
        if(S(0x364)!=0) {if(B(0x113)<5) RETIRE();B(0x113)-=5;}
        else {
            if(FIELD(OWNER,short,0x174)<=0) S(0x364)=1;
            if(S(0x13e)==13) {
                if(I(0x144)%5==0) {
                    float packet[3]={F(0x374)+F(0x370),15.0f,14.0f};
                    spawn_unparented(920,static_cast<float>(58*C(0x104)+F(0xec)),static_cast<float>(F(0xf0)+110.0),B(0x104),1,packet,3);
                }
                F(0x374)*=0.95f;
            }
        }
        if(F(0xec)>1220.0f && C(0x104)*static_cast<double>(F(0xf4))>0.0) F(0xf4)=0.0f;
        if(F(0xec)<60.0 && C(0x104)*static_cast<double>(F(0xf4))<0.0) F(0xf4)=0.0f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        double next_y=static_cast<double>(F(0xf0))+F(0xf8);
        if(stage_surface_height()>=next_y) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;F(0xf0)=stage_surface_height();select_sequence(10);return;
        }
        break;
    }
    case 14:
        if(FIELD(OWNER,short,0x174)<=0) RETIRE();
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        if(g_match_identifier==3) advance_six(0);
        if(I(0x180)!=0) {
            for(int count=2;count!=0;--count) {
                float packet[3]={RF(360),static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10)),16.0f};
                spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOVE();break;
    case 15:
        F(0x11c)-=0.1f;F(0x120)-=0.1f;break;
    case 16: {
        F(0x11c)-=0.01f;F(0x120)-=0.01f;
        if(F(0x11c)<0.5 || I(0x144)>10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}
        if(F(0x11c)<=0.0 || B(0x113)==0) RETIRE();float *parameters=PARAM;parameters[1]-=1.25;if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOVE();break;
    }
    case 17: {
        if(!RELATED) RETIRE();B(0x104)=FIELD(RELATED,unsigned char,0x104);void *related=RELATED;
        F(0xec)=FIELD(related,signed char,0x104)*FIELD(related,float,0xf4)+FIELD(related,float,0xec);
        F(0xf0)=FIELD(related,float,0xf8)+FIELD(related,float,0xf0);F(0x12c)=FIELD(related,float,0x12c);B(0x113)=FIELD(related,unsigned char,0x113);break;
    }
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==5) {
        select_sequence(12);
        if(C(0x104)==1 && FIELD(TARGET,float,0xec)<static_cast<double>(F(0xec))) {C(0x104)=-1;F(0xf4)=-F(0xf4);}
        if(C(0x104)==-1 && FIELD(TARGET,float,0xec)>static_cast<double>(F(0xec))) {C(0x104)=1;F(0xf4)=-F(0xf4);}
    }
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==11 && PARAM[3]==1.0f) {
            FIELD(OWNER,float,0xec)=F(0xec);FIELD(OWNER,float,0xf0)=F(0xf0);
            reinterpret_cast<UdongeUpdateOwnerView*>(OWNER)->set_action(700);FIELD(OWNER,short,0x768)=60;RETIRE();
        }
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==13) {
            F(0x370)=static_cast<float>(50.0-RF(50));
            if(g_match_identifier==2 || g_match_identifier==3) F(0x374)=-30.0f;else F(0x374)=0.0f;
        }
    }
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==16) --I(0x330);
    return;


}
case 980: {

    update_ping_pong_motion();FINISH();

}
case 998: {
 {
    short action=FIELD(OWNER,short,0x13c);
    if(action>153 && action<158) {if(PARAM[1]==0.0f) position_relative_to_owner(30,80);else position_relative_to_owner(70,80);}
    action=FIELD(OWNER,short,0x13c);
    if(action>149 && action<154) {if(PARAM[1]==0.0f) position_relative_to_owner(20,130);else position_relative_to_owner(60,130);}
    if(FIELD(OWNER,short,0x13c)==158) {if(PARAM[1]==0.0f) position_relative_to_owner(30,150);else position_relative_to_owner(70,150);}
    F(0x11c)+=0.4f;if(F(0x11c)>4.0f) F(0x11c)=1.0f;F(0x120)=F(0x11c);
    if(S(0x364)==0) {
        action=FIELD(OWNER,short,0x13c);
        if(action<150 || action>158) {S(0x364)=1;if(PARAM[1]==0.0f) FIELD(OWNER,unsigned char,0x751)=0;}
    }
    if(S(0x364)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}FINISH();
}

}
default:advance_frame();return;
}
}
}
