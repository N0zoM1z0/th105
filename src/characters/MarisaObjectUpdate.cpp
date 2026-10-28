// Complete manual JP1.06a MarisaObject update hypothesis, 004BBE00.
#include "characters/MarisaObjectUpdate.hpp"
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
#define MOTION reinterpret_cast<MarisaUpdateMotionView*>(reinterpret_cast<unsigned char*>(this)+4)
#define WAVE(n) reinterpret_cast<MarisaSpawnOwnerView*>(OWNER)->dispatch_character_wave_handle(n)
#define SPAWN_OWNED(a,x,y,d,l,p,n) reinterpret_cast<MarisaSpawnOwnerView*>(OWNER)->spawn_owned(a,x,y,d,l,p,n)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define RETIRE() do { --I(0x330); return; } while(0)
#define MOVE() do {F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf8)+F(0xf0);}while(0)
#define FINISH() do {if(advance_frame())--I(0x330);return;}while(0)
void MarisaObjectUpdateView::update_action_state() {
switch(S(0x13c)) {
// Native primary800:4BBE37, nested phases0..8 at4C7DF4.
case 800: {

    if (I(0x180) == 5) RETIRE();
    if (I(0x144) == 0 && S(0x142) == 0 && S(0x140) == 0 && S(0x13e) == 0) {
        B(0x184) = 1;
        S(0x364) = 0;
    }
    ++S(0x364);
    MOTION->set_components(PARAM[0], static_cast<float>(PARAM[1] + S(0x364) * 0.2f));
    if (F(0xec) > 1380.0f || F(0xec) < -100.0 || F(0xf0) > 1000.0 || F(0xf0) < -100.0)
        RETIRE();
    switch (S(0x13e)) {
    case 0: case 1: {
        if (emit_repeated(0,0,4)) RETIRE();
        bool burst = S(0x142) > 180 || I(0x180);
        if (!burst) {
            double y_before_height = F(0xf0);
            burst = stage_surface_height() >= y_before_height;
        }
        if (burst) {
            WAVE(1);
            --I(0x330);
            float packet[3] = {0.0f,0.0f,0.0f};
            for (int count=6;count!=0;--count) {
                packet[0] = RF(360);
                packet[2] = 7.0f;
                spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2] = 8.0f;
            spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        break;
    }
    case 2: case 3: case 4: case 5:
        if (emit_repeated(0,0,3)) RETIRE();
        F(0x12c) += 30.0;
        if (I(0x144) == 10) {
            float packet[3] = {0.0f,0.0f,8.0f};
            SPAWN_OWNED(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for (int count=4;count!=0;--count) {
                packet[0] = RF(360);
                packet[2] = 7.0f;
                spawn_unparented(800,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        break;
    case 6:
        if (I(0x144) > 20) {
            F(0x11c) *= 0.85f;
            F(0x120) *= 0.85f;
            if (B(0x113) < 10) RETIRE();
            if (I(0x144) > 10) B(0x113) -= 10;
        } else {
            F(0x11c) = static_cast<float>((I(0x144)%2)*0.1f+2.0);
            F(0x120) = static_cast<float>(0.1f*(I(0x144)%2)+2.0);
        }
        break;
    case 7:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1] -= 0.4f;
        if (PARAM[1] < 0.5) PARAM[1] = 0.5f;
        F(0xec) = C(0x104)*F(0xf4)+F(0xec);
        F(0xf0) = F(0xf8)+F(0xf0);
        F(0x11c) *= 0.97f;
        F(0x120) = F(0x11c);
        if (B(0x113) < 5) RETIRE();
        B(0x113) -= 5;
        B(0x112) -= 5;
        B(0x111) -= 5;
        break;
    case 8:
        F(0x11c) += 0.3f;
        F(0x120) += 0.3f;
        if (B(0x113) < 20) RETIRE();
        B(0x113) -= 20;
        B(0x112) -= 20;
        B(0x111) -= 20;
        break;
    }
    MOVE();
    FINISH();

// Native801:4BC36A; nested phases0..7 at4C7E18.

}
case 801: {

    switch (S(0x13e)) {
    case 0: {
        if (I(0x180)==5 || emit_repeated(0,3,5)) RETIRE();
        PARAM[1] += 0.5;
        MOTION->set_components(PARAM[0],PARAM[1]);
        F(0x12c) += 10.0;
        float scale = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(10*I(0x144)))*0.5+1.0);
        F(0x11c)=scale; F(0x120)=scale;
        if (I(0x144)%7==0) {
            float trail[3]={PARAM[0],0.0f,2.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        if (F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
        advance_six(0);
        bool burst = I(0x144)>180 || I(0x180);
        if (!burst) {
            double y_before_height=F(0xf0);
            burst=stage_surface_height()>=y_before_height;
        }
        if (burst) {
            WAVE(3);
            --I(0x330);
            float packet[3]={0.0f,0.0f,3.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for (int count=12;count!=0;--count) {
                packet[0]=RF(360);
                packet[1]=static_cast<float>(RF(10)+5.0);
                packet[2]=5.0f;
                spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2]=6.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        MOVE();
        break;
    }
    case 1: {
        if (I(0x180)==5 || emit_repeated(0,3,5)) RETIRE();
        PARAM[1] += 0.5;
        MOTION->set_components(PARAM[0],PARAM[1]);
        F(0x12c) += 10.0;
        float scale = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(10*I(0x144)))*0.5+1.0);
        F(0x11c)=scale; F(0x120)=scale;
        if (I(0x144)%4==0) {
            float trail[3]={PARAM[0],0.0f,2.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        if (F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
        advance_six(0);
        bool burst = I(0x144)>180 || I(0x180);
        if (!burst) {
            double y_before_height=F(0xf0);
            burst=stage_surface_height()>=y_before_height;
        }
        if (burst) {
            WAVE(3);
            --I(0x330);
            float packet[3]={0.0f,0.0f,4.0f};
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for (int count=12;count!=0;--count) {
                packet[0]=RF(360);
                packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+5));
                packet[2]=5.0f;
                spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2]=7.0f;
            spawn_unparented(801,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        MOVE();
        break;
    }
    case 2:
        F(0x11c)+=0.1f; F(0x120)+=0.1f;
        if (B(0x113)<=20) RETIRE();
        B(0x113)-=20; B(0x112)-=20; B(0x110)-=20;
        break;
    case 3:
        if (S(0x140)>0) {
            F(0x11c)*=0.85f; F(0x120)*=0.85f;
            if (B(0x113)<10) RETIRE();
            if (S(0x142)>10) {
                B(0x113)-=10;
                if (B(0x111)>=20) { B(0x111)-=20; B(0x112)-=20; }
            }
        } else {
            if (I(0x180)==6) { I(0x180)=0; ++B(0x184); }
            if (I(0x180)) {
                if (++S(0x368)>5) { S(0x368)=0; I(0x180)=0; }
            }
            F(0x11c)=static_cast<float>((I(0x144)%2)*0.1f+1.0);
            F(0x120)=static_cast<float>(0.1f*(I(0x144)%2)+1.0);
            if (!B(0x184)) { S(0x142)=0; S(0x140)=1; }
        }
        break;
    case 4:
        if (S(0x140)>0) {
            F(0x11c)*=0.85f; F(0x120)*=0.85f;
            if (B(0x113)<10) RETIRE();
            if (S(0x142)>10) {
                B(0x113)-=10;
                if (B(0x111)>=20) { B(0x111)-=20; B(0x112)-=20; }
            }
        } else {
            if (I(0x180)==6) { I(0x180)=0; ++B(0x184); }
            if (I(0x180)) {
                if (++S(0x368)>10) { S(0x368)=0; I(0x180)=0; }
            }
            F(0x11c)=static_cast<float>((I(0x144)%2)*0.1f+1.0);
            F(0x120)=static_cast<float>(0.1f*(I(0x144)%2)+1.0);
            if (!B(0x184)) { S(0x142)=0; S(0x140)=1; }
        }
        break;
    case 5:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.4f;
        if (PARAM[1]<0.5) PARAM[1]=0.5f;
        MOVE();
        F(0x11c)*=0.97f; F(0x120)=F(0x11c);
        if (B(0x113)<5) RETIRE();
        B(0x113)-=5; B(0x112)-=5; B(0x111)-=5;
        break;
    case 6: case 7:
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<20) RETIRE();
        B(0x113)-=20;
        break;
    }
    if (advance_frame()) --I(0x330);
    if (S(0x13e)>2 && S(0x142)==0) --I(0x330);
    return;

// Primary802:4BCD47, five nested phases; owner348 is receiver of465190/45C030.

}
case 802: {

    if (I(0x180)==5) RETIRE();
    switch (S(0x13e)) {
    case 0: {
        if (emit_repeated(0,4,5)) RETIRE();
        F(0x12c)+=12.0;
        F(0xf8)-=0.85f;
        if (F(0xec)>1380.0f || F(0xec)<-100.0) RETIRE();
        int burst=I(0x180);
        if (!burst) {
            double y_before_height=F(0xf0);
            burst=stage_surface_height()>=y_before_height;
        }
        if (burst) {
            --I(0x330);
            float packet[3]={0.0f,0.0f,1.0f};
            WAVE(3);
            SPAWN_OWNED(802,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(int count=8;count!=0;--count) {
                packet[0]=static_cast<float>(mt19937_next_u32()%360u);
                packet[2]=2.0f;
                SPAWN_OWNED(802,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            for(int count=8;count!=0;--count) {
                packet[0]=static_cast<float>(mt19937_next_u32()%360u);
                packet[2]=3.0f;
                SPAWN_OWNED(802,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            packet[2]=4.0f;
            SPAWN_OWNED(802,F(0xec),F(0xf0),B(0x104),1,packet,3);
            return;
        }
        break;
    }
    case 1:
        if(S(0x140)>0) {
            F(0x11c)*=0.85f;F(0x120)*=0.85f;
            if(B(0x113)<10) RETIRE();
            if(I(0x144)>10) B(0x113)-=10;
        } else {
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)) {
                if(++S(0x368)>5) {S(0x368)=0;I(0x180)=0;}
            }
            F(0x11c)=static_cast<float>((I(0x144)%2)*0.1f+1.0);
            F(0x120)=static_cast<float>(0.1f*(I(0x144)%2)+1.0);
            if(!B(0x184)) {S(0x142)=0;S(0x140)=1;}
        }
        break;
    case 2:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.75;
        if(PARAM[1]<0.25) PARAM[1]=0.25f;
        F(0x370)*=0.995f;
        F(0x12c)=F(0x370)+F(0x12c);
        F(0x11c)*=1.005f;F(0x120)=F(0x11c);
        if(B(0x113)<5) RETIRE();
        B(0x113)-=5;
        if(B(0x112)>=10) {B(0x112)-=10;B(0x111)-=10;}
        break;
    case 3:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.25;
        if(PARAM[1]<0.5) PARAM[1]=0.5f;
        F(0x370)*=0.995f;
        F(0x12c)=F(0x370)+F(0x12c);
        F(0x11c)*=0.97f;F(0x120)=F(0x11c);
        if(B(0x113)<5) RETIRE();
        B(0x113)-=5;
        if(B(0x112)>=10) {B(0x112)-=10;B(0x111)-=10;}
        break;
    case 4:
        F(0x11c)+=0.5;F(0x120)+=0.5;
        if(B(0x113)<25) RETIRE();
        B(0x113)-=25;
        break;
    }
    MOVE();FINISH();

}
case 803: {

    if(S(0x13e)==0 || S(0x13e)==1) {
        if(S(0x364)%3==0) I(0x180)=0;
        void *owner=OWNER;
        short owner_action=FIELD(owner,short,0x13c);
        if(owner_action>49 && owner_action<150) {
            for(int count=0;count<40;++count)
                emit_effect(201,static_cast<float>(RF(15)+(static_cast<double>(30*count*C(0x104))+F(0xec))),F(0xf0),B(0x104),1);
            RETIRE();
        }
        if(owner_action==411 && FIELD(owner,short,0x13e)<5) {
            F(0xec)=static_cast<float>(44*C(0x104)+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
        } else if(owner_action==415 && FIELD(owner,short,0x13e)<5) {
            F(0xec)=static_cast<float>(48*C(0x104)+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+104.0);
        } else select_sequence(2);
        ++S(0x364);
    }
    if(S(0x13e)==2) {
        B(0x184)=0;
        F(0x120)*=0.8f;
        F(0x11c)+=0.1f;
        if(I(0x144)==40) RETIRE();
    }
    FINISH();

}
case 804: {

    if(S(0x13e)==0) {
        MOTION->set_components(PARAM[0],PARAM[1]);
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        F(0xf0)=F(0xf0)+F(0xf8);
        float scale=static_cast<float>(RF(60)*static_cast<double>(0.01f)+0.7f);
        F(0x11c)=scale;F(0x120)=scale;
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        int land=I(0x180);
        if(!land) {
            double y_before_height=static_cast<double>(F(0xf0))+F(0xf8);
            land=stage_surface_height()>=y_before_height;
        }
        if(land) {
            next_sequence_block();
            F(0x11c)=2.0f;F(0x120)=2.0f;
            return;
        }
    }
    if(S(0x13e)==1) {
        ++S(0x364);
        F(0x11c)*=0.85f;F(0x120)=F(0x11c);
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;
    }
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
    FINISH();


}
case 810: {

    MOTION->set_components(PARAM[0],PARAM[1]);
    PARAM[1]-=0.5;
    if(PARAM[1]<0.0) PARAM[1]=0.0f;
    F(0x12c)+=8.0;
    if(B(0x113)<=10) RETIRE();
    B(0x113)-=10;
    if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
    MOVE();FINISH();

}
case 811: {

    switch(S(0x13e)) {
    case 0:
        if(I(0x180)==5 || emit_repeated(1,3,7)) RETIRE();
        advance_six(0);
        if(I(0x144)>0 && I(0x144)%5==0 && I(0x144)<=10) {
            for(int count=6;count!=0;--count) {
                float packet[3];
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(811,static_cast<float>(20*I(0x144)*C(0x104)+F(0xec)),F(0xf0),B(0x104),B(0x364),packet,3);
            }
        }
        if(I(0x144)<=120 && C(0x184)>0) {MOVE();}
        else {next_sequence_block();return;}
        break;
    case 1:
        PARAM[1]*=0.9f;
        MOTION->set_components(PARAM[0],PARAM[1]);
        MOVE();
        break;
    case 2:
        F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);
        F(0x370)-=0.2f;
        if(F(0x370)<=static_cast<double>(0.1f)) F(0x370)=0.1f;
        if(I(0x144)>10) {
            if(B(0x113)<=8) RETIRE();
            B(0x113)-=8;B(0x112)-=8;B(0x111)-=8;
        }
        break;
    case 3:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.5;
        if(PARAM[1]<0.0) PARAM[1]=0.0f;
        F(0x11c)*=0.95f;F(0x120)=F(0x11c);
        if(PARAM[3]<static_cast<double>(I(0x144))) {
            if(B(0x113)<=15) RETIRE();
            B(0x113)-=15;B(0x112)-=15;B(0x111)-=15;
        }
        MOVE();
        break;
    case 4:
        F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);
        F(0x370)-=0.2f;
        if(F(0x370)<=static_cast<double>(0.1f)) F(0x370)=0.1f;
        if(B(0x113)<=20) RETIRE();
        B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;
        break;
    case 5:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.5;
        if(PARAM[1]<0.5) PARAM[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));
        F(0x11c)+=0.01f;F(0x120)+=0.01f;
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;
        if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
        break;
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    return;

}
case 812: {

    switch(S(0x13e)) {
    case 1: {
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action!=510 && owner_action!=511 && owner_action!=512 && owner_action!=513) RETIRE();
        double cosine=lookup_orientation_cosine_quantized_abs(static_cast<float>(-FIELD(OWNER,float,0x12c)-30.0));
        F(0xec)=static_cast<float>(cosine*static_cast<float>(58*C(0x104))+FIELD(OWNER,float,0xec));
        double y_offset=lookup_orientation_sine_quantized_abs(static_cast<float>(-FIELD(OWNER,float,0x12c)-30.0))*58.0;
        F(0xf0)=static_cast<float>(y_offset+(FIELD(OWNER,float,0xf0)+100.0));
        F(0x12c)=FIELD(OWNER,float,0x12c);
        if(FIELD(OWNER,short,0x13e)!=1) RETIRE();
        break;
    }
    case 0: {
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action!=510 && owner_action!=511 && owner_action!=512 && owner_action!=513) RETIRE();
        double cosine=lookup_orientation_cosine_quantized_abs(static_cast<float>(-FIELD(OWNER,float,0x12c)-30.0));
        F(0xec)=static_cast<float>(cosine*static_cast<float>(58*C(0x104))+FIELD(OWNER,float,0xec));
        double y_offset=lookup_orientation_sine_quantized_abs(static_cast<float>(-FIELD(OWNER,float,0x12c)-30.0))*58.0;
        F(0xf0)=static_cast<float>(y_offset+(FIELD(OWNER,float,0xf0)+100.0));
        F(0x12c)=FIELD(OWNER,float,0x12c);
        float packet[3];
        packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%60u)+static_cast<double>(F(0x12c))-30.0);
        float speed=static_cast<float>(RF(150)*static_cast<double>(0.1f));
        packet[1]=static_cast<float>(speed+10.0);
        packet[2]=static_cast<float>(mt19937_next_u32()&3u);
        spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
        if(I(0x180)==6) {++B(0x184);I(0x180)=0;}
        if(I(0x180)) {
            FIELD(OWNER,int,0x180)=I(0x180);
            if(++S(0x364)>=10) {I(0x180)=0;S(0x364)=0;}
        }
        if(FIELD(OWNER,short,0x13e)!=1) RETIRE();
        break;
    }
    }
    goto owner_hitstop_finish;


}
case 817: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action>49 && owner_action<150) {
            for(int count=7;count!=0;--count)
                emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
            for(int count=3;count!=0;--count)
                emit_effect(200,F(0xec),F(0xf0),B(0x104),1);
            RETIRE();
        }
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x144)%3==0) {
            float trail[3];
            trail[0]=static_cast<float>(RF(30)-15.0+PARAM[0]+180.0);
            trail[1]=static_cast<float>(RF(15)+15.0);
            trail[2]=5.0f;
            spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        if(I(0x144)<15 && C(0x184)>0) {
            PARAM[1]*=0.9f;
            MOTION->set_components(PARAM[0],PARAM[1]);
            MOVE();
            break;
        }
        WAVE(31);
        float packet[3];packet[0]=0.0f;packet[1]=0.0f;
        packet[2]=FIELD(OWNER,signed char,0x60d)<4?1.0f:6.0f;
        spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[2]=2.0f;
        spawn_unparented(817,F(0xec),F(0xf0),B(0x104),1,packet,3);
        for(int count=6;count!=0;--count) {
            packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
            packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
            packet[2]=5.0f;
            if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
            SPAWN_OWNED(820,F(0xec),F(0xf0),B(0x104),B(0x364),packet,3);
        }
        RETIRE();
    }
    case 1: case 6:
        if(C(0x184)>0 && I(0x144)<=20*((FIELD(OWNER,signed char,0x60d)>=4)+3)) {
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)) {
                if(++S(0x364)>=10) {S(0x364)=0;I(0x180)=0;}
            }
        } else {
            B(0x184)=0;
            F(0x11c)+=0.02f;F(0x120)=F(0x11c);
            if(B(0x113)<=10) RETIRE();
            B(0x113)-=10;
            if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
        }
        break;
    case 2:
        F(0x11c)+=0.25;F(0x120)=F(0x11c);
        if(B(0x113)<=20) RETIRE();
        B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;
        break;
    case 5: {
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.5;
        if(PARAM[1]<0.5) PARAM[1]=0.5f;
        double cosine=lookup_orientation_cosine_quantized_abs(-PARAM[0]);
        F(0xec)=static_cast<float>(cosine*(static_cast<double>(C(0x104))*F(0xf4))+F(0xec));
        double sine=lookup_orientation_sine_quantized_abs(-PARAM[0]);
        F(0xf0)=static_cast<float>(sine*(F(0xf8)*0.25)+F(0xf0));
        F(0x11c)+=0.01f;F(0x120)+=0.01f;
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;
        if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
        break;
    }
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    return;


}
case 820: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: case 1: {
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action>49 && owner_action<150 && S(0x13e)==0) {
            for(int count=10;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
            for(int count=5;count!=0;--count) emit_effect(200,F(0xec),F(0xf0),B(0x104),1);
            RETIRE();
        }
        F(0x12c)+=8.0;
        if(S(0x13e)==0) F(0xf8)-=0.5;
        if(F(0xec)>1380.0f || F(0xec)<-100.0) RETIRE();
        if(I(0x144)%3==0) {
            float trail[3];
            trail[0]=static_cast<float>(mt19937_next_u32()%360u);
            trail[1]=5.0f;
            trail[2]=static_cast<float>(mt19937_next_u32()&3u);
            spawn_unparented(810,F(0xec),F(0xf0),B(0x104),1,trail,3);
        }
        double y_before_height=F(0xf0);
        if(stage_surface_height()>=y_before_height) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;
            float packet[3]={0.0f,0.0f,4.0f};
            emit_effect(127,F(0xec),F(0xf0),B(0x104),-1);
            emit_effect(127,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),-1);
            packet[2]=8.0f;
            if(FIELD(OWNER,signed char,0x606)>=2) packet[2]=9.0f;
            if(FIELD(OWNER,signed char,0x606)>=4) packet[2]=10.0f;
            SPAWN_OWNED(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+25.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,F(0xec),F(0xf0),B(0x104),B(0x364),packet,3);
            }
            RETIRE();
        }
        MOVE();
        break;
    }
    case 2:
        if(I(0x144)==5 && FIELD(OWNER,signed char,0x606)>=1) {
            float packet[3];
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-100.0),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-100.0),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(F(0xec)-100.0),F(0xf0),B(0x104),B(0x364),packet,3);
            }
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)+100.0),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)+100.0),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(F(0xec)+100.0),F(0xf0),B(0x104),B(0x364),packet,3);
            }
        }
        if(I(0x144)==10 && FIELD(OWNER,signed char,0x606)>=4) {
            float packet[3];
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-200.0),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-200.0),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(F(0xec)-200.0),F(0xf0),B(0x104),B(0x364),packet,3);
            }
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)+200.0),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)+200.0),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(F(0xec)+200.0),F(0xf0),B(0x104),B(0x364),packet,3);
            }
        }
        if(I(0x144)==10) RETIRE();
        break;
    case 3:
        if(I(0x144)>0 && I(0x144)%5==0 && I(0x144)<=60) {
            float packet[3];
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(static_cast<double>(20*I(0x144)*C(0x104))+F(0xec)),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(static_cast<double>(20*I(0x144)*C(0x104))+F(0xec)),F(0xf0),B(0x104),1,packet,3);
            WAVE(8);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(static_cast<double>(20*I(0x144)*C(0x104))+F(0xec)),F(0xf0),B(0x104),B(0x364),packet,3);
            }
            packet[0]=0.0f;packet[1]=0.0f;packet[2]=4.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-static_cast<double>(20*I(0x144)*C(0x104))),F(0xf0),B(0x104),1,packet,3);
            packet[2]=6.0f;
            SPAWN_OWNED(820,static_cast<float>(F(0xec)-static_cast<double>(20*I(0x144)*C(0x104))),F(0xf0),B(0x104),1,packet,3);
            WAVE(1);
            for(int count=6;count!=0;--count) {
                packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%360u)-180.0);
                packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%50u)*static_cast<double>(0.1f)+15.0);
                packet[2]=5.0f;
                if(packet[0]<0.0) S(0x364)=1;else S(0x364)=-1;
                SPAWN_OWNED(820,static_cast<float>(F(0xec)-static_cast<double>(20*I(0x144)*C(0x104))),F(0xf0),B(0x104),B(0x364),packet,3);
            }
        }
        break;
    case 4:
        if(S(0x140)<2) {
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)) {
                if(++S(0x368)>10) {S(0x368)=0;I(0x180)=0;}
            }
            F(0x11c)=static_cast<float>((I(0x144)%2)*0.1f+1.0);
            F(0x120)=static_cast<float>(1.0+0.1f*(I(0x144)%2));
        } else {
            F(0x11c)*=0.9f;F(0x120)*=0.9f;
            if(B(0x113)<10) RETIRE();
            if(S(0x142)>10) {
                B(0x113)-=10;
                if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
            }
        }
        break;
    case 5:
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.5;
        if(PARAM[1]<0.5) PARAM[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));
        F(0x11c)+=0.01f;F(0x120)+=0.01f;
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;
        if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
        break;
    case 6:
        F(0x11c)+=0.4f;F(0x120)+=0.4f;
        if(B(0x113)<30) RETIRE();
        B(0x113)-=30;B(0x112)-=30;B(0x111)-=30;
        break;
    case 7: {
        if(!RELATED) RETIRE();
        void *related=RELATED;
        F(0xec)=FIELD(related,float,0xec);
        F(0xf0)=FIELD(related,float,0xf0);
        if(FIELD(related,short,0x13e)>=2) RETIRE();
        break;
    }
    case 8: case 9: case 10:
        if(S(0x140)<2) {
            advance_six(0);advance_phase(10);
            F(0x11c)=static_cast<float>((I(0x144)%2)*0.1f+1.0);
            F(0x120)=static_cast<float>(1.0+0.1f*(I(0x144)%2));
        } else {
            F(0x11c)*=0.8f;F(0x120)*=0.8f;
            if(B(0x113)<10) RETIRE();
            if(S(0x142)>4) {
                B(0x113)-=10;
                if(B(0x111)>=20) {B(0x111)-=20;B(0x112)-=20;}
            }
        }
        break;
    }
    if(advance_frame()) --I(0x330);
    if(S(0x13e)>0 && S(0x13e)<7 && S(0x142)==0) --I(0x330);
    return;


}
case 821: {

    if(S(0x13e)==0) {
        if(emit_repeated(0,3,7)) RETIRE();
        F(0xf8)-=1.0;
        double next_y=static_cast<double>(F(0xf8))+F(0xf0);
        if(stage_surface_height()>=next_y) {
            select_sequence(3);
            F(0xf8)=0.0f;F(0xf4)=0.0f;F(0xf0)=0.0f;
            return;
        }
        F(0x12c)+=8.0;
        F(0xf0)=F(0xf0)+F(0xf8);
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
    }
    if(S(0x13e)==3) {
        signed char level=FIELD(OWNER,signed char,0x60a);
        int limit=2;
        if(level>=2) limit=3;
        if(level>=4) ++limit;
        if(I(0x144)%6==0 && S(0x364)<=limit) {
            WAVE(27);
            float packet[2]={5.0f,9.0f};
            if(FIELD(OWNER,signed char,0x60a)>=2) packet[1]=11.0f;
            if(FIELD(OWNER,signed char,0x60a)>=3) packet[1]=13.0f;
            if(FIELD(OWNER,signed char,0x60a)>=4) packet[1]=18.0f;
            spawn_unparented(821,static_cast<float>(20*I(0x144)*C(0x104)+F(0xec)),F(0xf0),B(0x104),1,packet,2);
            ++S(0x364);
        }
        if(S(0x364)>limit) RETIRE();
    }
    if(S(0x13e)==5) {
        F(0xf8)-=0.15f;
        if(S(0x140)==1) F(0xf8)*=0.95f;
        if(F(0xf8)<=0.5) F(0xf8)=0.5f;
        float scale=static_cast<float>(static_cast<double>(0.9f)-0.1f*(I(0x144)%3));
        F(0x11c)=scale;F(0x120)=scale;
        advance_six(0);
        if(I(0x144)>=15) {
            F(0xf8)-=0.2f;
            if(F(0xf8)<=0.5) F(0xf8)=0.5f;
            B(0x184)=0;
            if(B(0x113)<=10) RETIRE();
            B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;
        }
        if(I(0x144)%3==0 && I(0x144)<20) {
            float packet[1]={6.0f};
            spawn_unparented(821,static_cast<float>(RF(60)+static_cast<double>(F(0xec))-30.0),static_cast<float>(RF(60)+static_cast<double>(F(0xf0))-30.0),B(0x104),1,packet,1);
        }
        F(0xf0)=F(0xf0)+F(0xf8);
    }
    if(S(0x13e)==6) {
        F(0x11c)*=0.98f;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();
        B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;
        F(0xf8)+=0.05f;F(0xf0)=F(0xf8)+F(0xf0);
    }
    if(S(0x13e)==7) {
        F(0x11c)+=0.1f;F(0x120)=0.1f+F(0x120);
        if(B(0x113)<=10) RETIRE();
        B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;
    }
    if(S(0x13e)==8) {
        F(0x11c)=0.05f+F(0x11c);F(0x120)=F(0x11c);
        if(B(0x113)<=8) RETIRE();
        B(0x113)-=8;B(0x112)-=8;B(0x111)-=8;
    }
    FINISH();


}
case 822: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3:case 4:case 5: {
        if(S(0x364)<=4) {
            short owner_action=FIELD(OWNER,short,0x13c);
            if(owner_action>49 && owner_action<150) S(0x364)=5;
            short owner_action_again=FIELD(OWNER,short,0x13c);
            if(owner_action_again==550 || owner_action_again==551) {
                if(FIELD(OWNER,short,0x140)==0) S(0x364)=5;
            } else if(owner_action_again>=500 && owner_action_again<=799) S(0x364)=5;
        }
        short state=S(0x364);
        if(state==0) {
            if(S(0x366)==0) WAVE(32);
            F(0xf4)=15.0f;F(0xf8)=0.0f;
            if(S(0x366)%4==0) {
                float packet[3]={0.0f,0.0f,13.0f};
                spawn_unparented(822,F(0xec),F(0xf0),B(0x104),-1,packet,3);
            }
            if(++S(0x366)>=10) {
                S(0x364)=1;S(0x366)=0;F(0xf4)=0.0f;F(0xf8)=0.0f;
            }
        }
        else if(state==1) {
            if(++S(0x366)>=15) {S(0x366)=0;S(0x364)=2;}
        }
        else if(state==2) {
            if(S(0x366)==0) WAVE(32);
            MOTION->set_components(PARAM[0],PARAM[1]);
            if(S(0x366)%4==0) {
                float packet[3]={0.0f,0.0f,13.0f};
                spawn_unparented(822,F(0xec),F(0xf0),B(0x104),-1,packet,3);
            }
            if(++S(0x366)>=10) {
                S(0x364)=3;S(0x366)=0;F(0xf4)=0.0f;F(0xf8)=0.0f;
            }
        }
        else if(state==3) {
            if(++S(0x366)>=60) {S(0x364)=4;S(0x366)=0;}
        }
        else if(state==4) {
            int level=FIELD(OWNER,signed char,0x60e);
            if(S(0x366)%(2*(10-level))==0 && S(0x368)<level+2) {
                ++S(0x368);
                WAVE(33);
                float packet[3];
                packet[0]=-atan2_degrees(static_cast<float>(FIELD(TARGET,float,0xf0)-F(0xf0)+100.0),static_cast<float>((FIELD(TARGET,float,0xec)-F(0xec))*C(0x104)));
                packet[1]=10.0f;packet[2]=6.0f;
                spawn_unparented(822,static_cast<float>(lookup_orientation_cosine_quantized_abs(-packet[0])*50.0*C(0x104)+F(0xec)),static_cast<float>(lookup_orientation_sine_quantized_abs(-packet[0])*50.0+F(0xf0)),B(0x104),-1,packet,3);
            }
            if(S(0x366)==120) {S(0x364)=5;S(0x366)=0;return;}
            ++S(0x366);
        }
        else if(state==5) {
            if(B(0x113)<12) RETIRE();
            B(0x113)-=12;
        }
        break;
    }
    case 6: {
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action>49 && owner_action<150) {
            for(int count=10;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
            for(int count=5;count!=0;--count) emit_effect(200,F(0xec),F(0xf0),B(0x104),1);
            RETIRE();
        }
        if(I(0x180)==6 && ++S(0x384)<=5) {++B(0x184);I(0x180)=0;}
        if(I(0x180)) {
            float packet[3]={0.0f,0.0f,9.0f};
            spawn_unparented(822,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=11.0f;
            spawn_unparented(822,F(0xec),F(0xf0),B(0x104),1,packet,3);
            for(int count=6;count!=0;--count) {
                packet[0]=RF(360);packet[1]=static_cast<float>(RF(15)+10.0);packet[2]=10.0f;
                spawn_unparented(822,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            RETIRE();
        }
        MOTION->set_components(PARAM[0],PARAM[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1280.0 || F(0xf0)<-200.0) RETIRE();
        break;
    }
    case 7:
        F(0x11c)+=0.1f;F(0x120)*=0.95f;
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;
        break;
    case 8:case 11:
        F(0x11c)+=0.1f;F(0x120)=F(0x11c);
        if(B(0x113)<10) RETIRE();
        B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;
        break;
    case 9:
        F(0x11c)*=0.95f;F(0x120)=F(0x11c);
        if(B(0x113)<30) RETIRE();
        B(0x113)-=30;B(0x112)-=30;B(0x111)-=30;
        break;
    case 10: {
        float *parameters=PARAM;
        F(0x11c)*=0.95f;F(0x120)+=0.15f;
        MOTION->set_components(parameters[0],parameters[1]);
        PARAM[1]*=0.9f;
        if(B(0x113)<20) RETIRE();
        B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;
        break;
    }
    case 12: {
        if(!RELATED) RETIRE();
        void *related=RELATED;
        F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
        float scale=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3.0))*static_cast<double>(0.2f)+1.0);
        F(0x11c)=scale;F(0x120)=scale;
        unsigned char color=static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6.0))*127.0+127.0);
        B(0x112)=static_cast<unsigned char>(color);B(0x111)=static_cast<unsigned char>(color);
        if(FIELD(RELATED,short,0x364)==5) {
            if(B(0x113)<20) RETIRE();
            B(0x113)-=20;
        }
        break;
    }
    case 13:
        F(0x11c)+=0.1f;F(0x120)=F(0x11c);
        if(B(0x113)<20) RETIRE();
        B(0x113)-=20;B(0x112)-=20;B(0x111)-=20;
        break;
    }
    MOVE();FINISH();


}
case 825: {

    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3: {
        if(I(0x180)==5) RETIRE();
        short owner_action=FIELD(OWNER,short,0x13c);
        if(owner_action>49 && owner_action<150) {
            for(int count=4;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
            RETIRE();
        }
        float *parameters=PARAM;
        F(0x12c)+=8.0;
        MOTION->set_components(parameters[0],parameters[1]);
        PARAM[0]*=0.98f;PARAM[1]+=0.75;
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
        if(S(0x142)<=45 && I(0x180)==0) {MOVE();FINISH();}
        float packet[3]={0.0f,0.0f,7.0f};
        spawn_unparented(825,F(0xec),F(0xf0),B(0x104),1,packet,3);
        select_sequence(6);
        return;
    }
    case 4: {
        if(I(0x144)%8!=0) {
            float packet[3]={0.0f,0.0f,5.0f};
            spawn_parented(810,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;
        short action=FIELD(owner,short,0x13c);
        if(action<=559 || action>=564) RETIRE();
        if(FIELD(owner,short,0x13c)==560 || FIELD(owner,short,0x13c)==561) {
            if(FIELD(owner,short,0x13e)>=4) RETIRE();
            if(FIELD(owner,short,0x13e)==1) {
                F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-24*C(0x104));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0);
            }
            if(FIELD(owner,short,0x13e)==2) {
                if(FIELD(owner,short,0x140)==0) {
                    F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-12*C(0x104));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+80.0);
                }
                if(FIELD(owner,short,0x140)==1) {
                    F(0xec)=static_cast<float>(static_cast<double>(18*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+80.0);
                }
                if(FIELD(owner,short,0x140)==2) {
                    F(0xec)=static_cast<float>(static_cast<double>(36*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
                }
                if(FIELD(owner,short,0x140)>=3) {
                    F(0xec)=static_cast<float>(static_cast<double>(38*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
                }
            }
            if(FIELD(owner,short,0x13e)==3) {
                F(0xec)=static_cast<float>(static_cast<double>(38*C(0x104))+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
            }
        }
        if(FIELD(owner,short,0x13c)==562 || FIELD(owner,short,0x13c)==563) {
            if(FIELD(owner,short,0x13e)>=4) RETIRE();
            if(FIELD(owner,short,0x13e)==1) {
                F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-23*C(0x104));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+107.0);
            }
            if(FIELD(owner,short,0x13e)==2) {
                if(FIELD(owner,short,0x140)==0) {
                    F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-21*C(0x104));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+96.0);
                }
                if(FIELD(owner,short,0x140)==1) {
                    F(0xec)=static_cast<float>(static_cast<double>(15*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0);
                }
                if(FIELD(owner,short,0x140)==2) {
                    F(0xec)=static_cast<float>(static_cast<double>(45*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
                }
                if(FIELD(owner,short,0x140)>=3) {
                    F(0xec)=static_cast<float>(static_cast<double>(47*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+103.0);
                }
            }
            if(FIELD(owner,short,0x13e)==3) {
                F(0xec)=static_cast<float>(static_cast<double>(47*C(0x104))+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+103.0);
            }
        }
        float scale=static_cast<float>((I(0x144)%2)*static_cast<double>(0.2f)+0.9f);
        F(0x11c)=scale;F(0x120)=scale;
        FINISH();
    }
    case 5:
        goto attached_expand_fade;
    case 6:
        F(0x11c)*=0.8f;F(0x120)=F(0x11c);
        if(I(0x144)>=30) RETIRE();
        FINISH();
    case 7:
        goto expand_fade;
    default:FINISH();
    }


}
case 826: {

    if(static_cast<unsigned short>(S(0x13e))<2 || S(0x13e)==6 || S(0x13e)==7) {
        if(S(0x364)%3==0) I(0x180)=0;
        if(S(0x364)%6==0) {
            float packet[3]={0.0f,0.0f,3.0f};
            spawn_parented(826,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;
        short action=FIELD(owner,short,0x13c);
        if(action>49 && action<150) {
            for(int count=0;count<40;++count)
                emit_effect(201,static_cast<float>(RF(15)+static_cast<double>(30*count*C(0x104))+F(0xec)),F(0xf0),B(0x104),1);
            RETIRE();
        }
        if((action==565 || action==566) && FIELD(owner,short,0x13e)<4) {
            F(0xec)=static_cast<float>(44*C(0x104)+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
        } else if((action==567 || action==568) && FIELD(owner,short,0x13e)<4) {
            F(0xec)=static_cast<float>(48*C(0x104)+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+104.0);
        } else {
            if(S(0x13e)>=2) select_sequence(8);else select_sequence(2);
            return;
        }
        ++S(0x364);
    }
    if(S(0x13e)==2 || S(0x13e)==8) {
        B(0x184)=0;F(0x120)*=0.8f;F(0x11c)+=0.1f;
        if(I(0x144)==40) RETIRE();
    }
    if(S(0x13e)==3) {
        if(RELATED) {F(0xec)=FIELD(RELATED,float,0xec);F(0xf0)=FIELD(RELATED,float,0xf0);}
        F(0x11c)+=0.3f;F(0x120)=F(0x11c);
        if(B(0x113)<20) RETIRE();B(0x113)-=20;
    }
    if(S(0x13e)==4) {
        if(I(0x144)%8!=0) {
            float packet[3]={0.0f,0.0f,5.0f};
            spawn_parented(826,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;
        short action=FIELD(owner,short,0x13c);
        if(action<=564 || action>=569) RETIRE();
        if(FIELD(owner,short,0x13c)==565 || FIELD(owner,short,0x13c)==566) {
            if(FIELD(owner,short,0x13e)>=4) RETIRE();
            if(FIELD(owner,short,0x13e)==1) {
                F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-24*C(0x104));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0);
            }
            if(FIELD(owner,short,0x13e)==2) {
                if(FIELD(owner,short,0x140)==0) {
                    F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-12*C(0x104));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+80.0);
                }
                if(FIELD(owner,short,0x140)==1) {
                    F(0xec)=static_cast<float>(static_cast<double>(18*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+80.0);
                }
                if(FIELD(owner,short,0x140)==2) {
                    F(0xec)=static_cast<float>(static_cast<double>(36*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
                }
                if(FIELD(owner,short,0x140)>=3) {
                    F(0xec)=static_cast<float>(static_cast<double>(38*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
                }
            }
            if(FIELD(owner,short,0x13e)==3) {
                F(0xec)=static_cast<float>(static_cast<double>(38*C(0x104))+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+85.0);
            }
        }
        if(FIELD(owner,short,0x13c)==567 || FIELD(owner,short,0x13c)==568) {
            if(FIELD(owner,short,0x13e)>=4) RETIRE();
            if(FIELD(owner,short,0x13e)==1) {
                F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-23*C(0x104));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+107.0);
            }
            if(FIELD(owner,short,0x13e)==2) {
                if(FIELD(owner,short,0x140)==0) {
                    F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-21*C(0x104));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+96.0);
                }
                if(FIELD(owner,short,0x140)==1) {
                    F(0xec)=static_cast<float>(static_cast<double>(15*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+95.0);
                }
                if(FIELD(owner,short,0x140)==2) {
                    F(0xec)=static_cast<float>(static_cast<double>(45*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
                }
                if(FIELD(owner,short,0x140)>=3) {
                    F(0xec)=static_cast<float>(static_cast<double>(47*C(0x104))+FIELD(owner,float,0xec));
                    F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+103.0);
                }
            }
            if(FIELD(owner,short,0x13e)==3) {
                F(0xec)=static_cast<float>(static_cast<double>(47*C(0x104))+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+103.0);
            }
        }
        float scale=static_cast<float>((I(0x144)%2)*static_cast<double>(0.2f)+0.9f);
        F(0x11c)=scale;F(0x120)=scale;
    }
    if(S(0x13e)==5) {
attached_expand_fade:
        if(RELATED) {F(0xec)=FIELD(RELATED,float,0xec);F(0xf0)=FIELD(RELATED,float,0xf0);}
expand_fade:
        F(0x11c)+=0.4f;F(0x120)=F(0x11c);
        if(B(0x113)<30) RETIRE();B(0x113)-=30;
    }
    FINISH();


}
case 827: {

    if(I(0x180)==5) RETIRE();
    switch(S(0x13e)) {
    case 0: {
        if(I(0x144)==0) replace_secondary(989,5.0f,30,1,2);
        PARAM[0]-=1.5;F(0xf4)=PARAM[0];
        double cosine=lookup_orientation_cosine_quantized_abs(F(0x370));
        F(0xf8)=static_cast<float>(cosine*PARAM[1]);
        F(0x370)+=10.0;
        if(F(0x370)>180.0) {
            F(0xf4)=0.0f;F(0xf8)=0.0f;B(0x113)=0;
            if(!(F(0x374)>=20.0)) RETIRE();
            set_secondary_alpha(static_cast<unsigned char>(F(0x374)));
            F(0x374)-=20.0;
        } else {
            short owner_action=FIELD(OWNER,short,0x13c);
            if(owner_action>49 && owner_action<150) {
                for(int count=4;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
                RETIRE();
            }
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        FINISH();
    }
    case 1:
        if(F(0x11c)<1.0) {
            F(0x11c)+=0.2f;
            if(F(0x11c)>=1.0) {F(0x11c)=1.0f;B(0x184)=4;}
            F(0x120)=F(0x11c);
            FINISH();
        }
        advance_six(0);
        if(I(0x180)) {
            if(S(0x364)>=3) {S(0x364)=0;I(0x180)=0;}
            else ++S(0x364);
        }
        if(I(0x144)<45 && C(0x184)>0) {
            float packet[3];
            packet[0]=RF(360);
            packet[1]=static_cast<float>(RF(250)*static_cast<double>(0.01f)+10.0);
            packet[2]=5.0f;
            spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,packet,3);
            FINISH();
        }
        B(0x184)=0;
        if(B(0x113)<10) RETIRE();B(0x113)-=10;
        FINISH();
    case 2:case 3:
        F(0x11c)+=0.3f;F(0x120)+=0.3f;
        if(B(0x113)<20) RETIRE();B(0x113)-=20;
        FINISH();
    case 4: {
        F(0x370)+=10.0;
        if(F(0x370)>=180.0) {
            WAVE(35);
            float packet[3]={0.0f,0.0f,1.0f};
            spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=2.0f;
            spawn_unparented(827,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=3.0f;
            spawn_unparented(827,F(0xec),stage_surface_height(),B(0x104),-1,packet,3);
            RETIRE();
        }
        short action=FIELD(OWNER,short,0x13c);
        if(action>49 && action<150) RETIRE();
        PARAM[0]-=1.5;F(0xf4)=PARAM[0];
        MOVE();FINISH();
    }
    case 5:
        F(0x11c)*=0.99f;F(0x120)=F(0x11c);
        if(B(0x113)<10) RETIRE();B(0x113)-=10;
        PARAM[1]*=0.9f;
        if(PARAM[1]<0.5) PARAM[1]=0.5f;
        MOTION->set_components(PARAM[0],PARAM[1]);
        MOVE();FINISH();
    case 6: {
        if(I(0x144)==0) replace_secondary(989,5.0f,30,1,2);
        PARAM[0]-=1.5;F(0xf4)=PARAM[0];
        double cosine=lookup_orientation_cosine_quantized_abs(F(0x370));
        F(0xf8)=static_cast<float>(cosine*PARAM[1]);
        F(0x370)+=10.0;
        if(F(0x370)<=180.0) {
            short action=FIELD(OWNER,short,0x13c);
            if(action>49 && action<150) {
                for(int count=4;count!=0;--count) emit_effect(201,F(0xec),F(0xf0),B(0x104),1);
                RETIRE();
            }
        } else {
            F(0xf4)=0.0f;F(0xf8)=0.0f;B(0x113)=0;
            if(!(F(0x374)>=20.0)) RETIRE();
            set_secondary_alpha(static_cast<unsigned char>(F(0x374)));
            F(0x374)-=20.0;
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        FINISH();
    }
    default:FINISH();
    }


}
case 848: {

    if(S(0x13e)==0) {
        void *owner=OWNER;
        F(0xec)=FIELD(owner,float,0xec);F(0xf0)=FIELD(owner,float,0xf0);
        short action=FIELD(owner,short,0x13c);
        if(action!=322 && action!=418 && action!=696) RETIRE();
    } else if(S(0x13e)==1) {
        float *parameters=PARAM;
        if(parameters[1]==0.0) {
            void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==307 && FIELD(owner,short,0x140)>4) {
                F(0xec)=static_cast<float>(67*C(0x104)+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+110.0);
            }
        }
        if(parameters[1]==1.0) {
            void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==308 && FIELD(owner,short,0x140)>4) {
                F(0xec)=static_cast<float>(30*C(0x104)+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+30.0);
            }
        }
        if(parameters[1]==2.0) {
            void *owner=OWNER;
            if(FIELD(owner,short,0x13c)==408 && FIELD(owner,short,0x13e)>0) {
                F(0xec)=static_cast<float>(106*C(0x104)+FIELD(owner,float,0xec));
                F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+103.0);
            }
        }
    } else if(S(0x13e)==2) {
        MOTION->set_components(PARAM[0],PARAM[1]);
        PARAM[1]-=0.5;if(PARAM[1]<0.5) PARAM[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        F(0xf0)=static_cast<float>(F(0xf8)*0.25+F(0xf0));
        F(0x12c)=F(0x374)+F(0x12c);
        F(0x11c)+=0.02f;F(0x120)=F(0x11c);
        if(I(0x144)>=0) {
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        F(0xf0)=static_cast<float>(0.25*F(0xf8)+F(0xf0));
    }
    if(FIELD(OWNER,short,0x186)==0) {
        if(advance_frame()) --I(0x330);
        if(I(0x144)==0) {
            if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
            if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
        }
        if(S(0x13e)==1 && S(0x142)==0 && S(0x140)==3) {
            float packet[3];
            packet[0]=RF(360);packet[1]=static_cast<float>(RF(10)*static_cast<double>(0.1f)+1.0);packet[2]=2.0f;
            spawn_unparented(848,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
    }
    return;

}
case 849: {

    if(S(0x13e)==0) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(109*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+84.0);
        if(FIELD(owner,short,0x13c)!=500 || FIELD(owner,short,0x13e)!=1) RETIRE();
    }
    if(S(0x13e)==1) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(61*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+232.0);
        short action=FIELD(owner,short,0x13c);
        if((action!=520 && action!=521) || FIELD(owner,short,0x13e)!=1) RETIRE();
    }
    if(S(0x13e)==2) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(61*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+232.0);
        if(FIELD(owner,short,0x13c)!=606 || FIELD(owner,short,0x13e)!=1) RETIRE();
    }
    if(S(0x13e)==3 || S(0x13e)==4 || S(0x13e)==5) {
        B(0x17c)=5;
        if(I(0x180)==6) {++B(0x184);I(0x180)=0;}
        if(I(0x180)) {
            if(++S(0x364)>5) {I(0x180)=0;S(0x364)=0;}
        }
        position_relative_to_owner(38,54);
        void *owner=OWNER;
        short action=FIELD(owner,short,0x13c);
        if((action!=525 || FIELD(owner,short,0x13e)!=1) && (action!=526 || FIELD(owner,short,0x13e)!=1)) RETIRE();
    }
owner_hitstop_finish:
    if(FIELD(OWNER,short,0x186)==0) {FINISH();}
    return;


}
case 850: {

    switch(S(0x13e)) {
    case 0: {
        advance_six(0);
        if(I(0x144)%3==0) {B(0x184)=1;I(0x180)=0;}
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
        if(FIELD(owner,short,0x13c)!=600 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
        if(I(0x144)>60) next_sequence_block();
        F(0x120)-=0.01f;
        FINISH();
    }
    case 1:
        F(0x120)*=0.8f;F(0x11c)+=0.2f;
        if(I(0x144)==40) RETIRE();
        F(0xec)=static_cast<float>(30*C(0x104)+F(0xec));
        FINISH();
    case 2: {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
        if(FIELD(owner,short,0x13c)!=600 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
        if(I(0x144)>40) next_sequence_block();
        FINISH();
    }
    case 3:
        F(0x120)-=0.01f;F(0x11c)-=0.01f;
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;
        FINISH();
    case 4: {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
        F(0x120)+=0.1f;F(0x11c)+=0.05f;
        if(B(0x113)<=15) RETIRE();B(0x113)-=15;
        FINISH();
    }
    default:FINISH();
    }

}
case 851: {

    switch(S(0x13e)) {
    case 0: {
        advance_six(0);
        F(0x120)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x370)));
        float *parameters=PARAM;
        F(0x12c)=parameters[1]+F(0x12c);
        parameters[1]*=0.9f;
        if(parameters[1]>-0.3f && parameters[1]<0.0) parameters[1]=-0.3f;
        if(parameters[1]<0.3f && parameters[1]>0.0) parameters[1]=0.3f;
        if(F(0x370)<90.0f) F(0x370)+=9.0;
        else {
            if(I(0x144)%3==0) {B(0x184)=1;I(0x180)=0;}
            void *owner=OWNER;
            F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
            F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
            if(FIELD(owner,short,0x13c)!=601 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
            if(I(0x144)>=90) next_sequence_block();
            F(0x120)-=0.01f;
        }
        FINISH();
    }
    case 1: {
        float *parameters=PARAM;
        F(0x12c)=parameters[1]+F(0x12c);
        parameters[1]*=0.9f;
        if(parameters[1]>-0.3f && parameters[1]<0.0) parameters[1]=-0.3f;
        if(parameters[1]<0.3f && parameters[1]>0.0) parameters[1]=0.3f;
        F(0x120)*=0.8f;F(0x11c)+=0.2f;
        if(I(0x144)==40) RETIRE();
        MOTION->set_components(F(0x12c),30.0f);
        FINISH();
    }
    case 2: {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
        if(FIELD(owner,short,0x13c)!=601 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
        if(I(0x144)>=90) next_sequence_block();
        FINISH();
    }
    case 3:
        F(0x120)-=0.01f;F(0x11c)-=0.01f;
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;
        FINISH();
    default:FINISH();
    }


}
case 852: {

    if(S(0x13e)==0) {
        advance_six(0);
        if(F(0x120)<1.5f) F(0x120)+=0.25;
        else if(I(0x144)%3==0) {B(0x184)=1;I(0x180)=0;}
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+150.0);
        if(FIELD(owner,short,0x13c)!=602 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
        if(I(0x144)>90) next_sequence_block();
        F(0x120)+=0.001f;
    }
    if(S(0x13e)==1) {
        F(0x120)*=0.75;F(0x11c)+=0.2f;
        if(I(0x144)==40) RETIRE();
        MOTION->set_components(-30.0f,10.0f);
        MOVE();
    }
    if(S(0x13e)==2) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+150.0);
        if(FIELD(owner,short,0x13c)!=602 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
        if(I(0x144)>70) next_sequence_block();
    }
    if(S(0x13e)==3) {
        F(0x120)-=0.01f;F(0x11c)-=0.01f;
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;
    }
    if(S(0x13e)==4) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+150.0);
        F(0x120)+=0.15f;F(0x11c)+=0.15f;
        if(B(0x113)<=20) RETIRE();B(0x113)-=20;
    }
    if(S(0x13e)==5) {
        MOTION->set_components(-30.0f,60.0f);MOVE();
        F(0x12c)+=30.0;F(0x120)+=0.4f;F(0x11c)+=0.4f;
        if(B(0x113)<=20) RETIRE();B(0x113)-=20;
    }
    FINISH();

}
case 853: {

    if(S(0x13e)==0) {
        advance_six(0);
        if(F(0x120)<1.5f) F(0x120)+=0.25;
        else if(I(0x144)%3==0) {B(0x184)=1;I(0x180)=0;}
        void *owner=OWNER;
        F(0xec)=static_cast<float>((FIELD(owner,float,0xf4)+30.0)*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>((FIELD(owner,float,0xf0)+54.0)+FIELD(owner,float,0xf8));
        if(FIELD(owner,short,0x13c)!=603 || (FIELD(owner,short,0x13e)!=3 && FIELD(owner,short,0x13e)!=2)) next_sequence_block();
        if(I(0x144)>90) next_sequence_block();
        F(0x12c)=FIELD(OWNER,float,0x73c);
    }
    if(S(0x13e)==1) {
        F(0x120)*=0.75;F(0x11c)+=0.2f;
        if(I(0x144)==40) RETIRE();
        MOTION->set_components(F(0x12c),10.0f);
        MOVE();
    }
    if(S(0x13e)==2) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>((FIELD(owner,float,0xf4)+30.0)*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>((FIELD(owner,float,0xf0)+54.0)+FIELD(owner,float,0xf8));
        if(FIELD(owner,short,0x13c)!=603 || (FIELD(owner,short,0x13e)!=3 && FIELD(owner,short,0x13e)!=2)) next_sequence_block();
        if(I(0x144)>70) next_sequence_block();
        F(0x12c)=FIELD(OWNER,float,0x73c);
    }
    if(S(0x13e)==3) {
        F(0x120)-=0.01f;F(0x11c)-=0.01f;
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;
    }
    if(S(0x13e)==4) {
        void *owner=OWNER;
        F(0xec)=static_cast<float>((FIELD(owner,float,0xf4)+30.0)*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>((FIELD(owner,float,0xf0)+54.0)+FIELD(owner,float,0xf8));
        F(0x120)+=0.15f;F(0x11c)+=0.15f;
        if(B(0x113)<=20) RETIRE();B(0x113)-=20;
    }
    if(S(0x13e)==5) {
        F(0x12c)+=30.0;F(0x120)+=0.4f;F(0x11c)+=0.4f;
        if(B(0x113)<=20) RETIRE();B(0x113)-=20;
    }
    if(S(0x13e)==10) {
        void *owner=OWNER;
        F(0x12c)+=2.0;
        if(FIELD(owner,short,0x13c)!=603) RETIRE();
        if(FIELD(owner,short,0x13e)!=0) {
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;B(0x111)-=5;B(0x112)-=5;
        } else {
            F(0x11c)=static_cast<float>(1.0-F(0x370));F(0x120)=F(0x11c);
            F(0x370)*=0.8f;
            float packet[3]={F(0x12c),F(0x11c),11.0f};
            spawn_unparented(853,F(0xec),F(0xf0),B(0x104),-1,packet,3);
        }
    }
    if(S(0x13e)==11) {
        F(0x11c)+=0.05f;F(0x120)=F(0x11c);
        if(B(0x113)<=50) RETIRE();B(0x113)-=50;B(0x111)-=50;B(0x112)-=50;
    }
    FINISH();


}
case 854: {

    if(S(0x13e)==0) {
        if(I(0x144)%2==0) {B(0x184)=1;I(0x180)=0;}
        void *owner=OWNER;
        F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-25*C(0x104));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+170.0);
        if(FIELD(owner,short,0x13c)!=603 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
    }
    if(S(0x13e)==1) {
        B(0x184)=0;F(0x120)*=0.9f;F(0x11c)+=0.2f;
        if(I(0x144)==20) RETIRE();
    }
    F(0x12c)-=1.0;
    FINISH();

}
case 855: {

    if(S(0x13e)==0) {
        if(I(0x144)%5==0) {B(0x184)=1;I(0x180)=0;}
        void *owner=OWNER;
        F(0xec)=static_cast<float>(25*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+87.0);
        if(FIELD(owner,short,0x13c)!=600 || FIELD(owner,short,0x13e)!=1) next_sequence_block();
    }
    if(S(0x13e)==1) {
        F(0x120)*=0.9f;F(0x11c)+=0.2f;
        if(I(0x144)==40) RETIRE();
        F(0xec)=static_cast<float>(30*C(0x104)+F(0xec));
    }
    FINISH();

}
case 856: {

    if(S(0x13e)<=5) {
        if(S(0x140)==0) {
            float *parameters=PARAM;
            F(0x370)+=parameters[1];
            parameters[1]-=0.5;
            if(parameters[1]<0.3f) parameters[1]=0.3f;
            if(parameters[3]<=static_cast<double>(I(0x144))) {
                next_sequence_frame();
                float packet[4]={0.0f,0.0f,6.0f,0.0f};
                WAVE(25);
                spawn_parented(856,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,4);
            }
        }
        if(S(0x140)==1) {
            F(0x11c)=static_cast<float>((S(0x142)%3)*0.1f+1.0);F(0x120)=F(0x11c);
            if(S(0x142)%5==0) {
                float packet[4]={0.0f,0.0f,8.0f,0.0f};
                spawn_parented(856,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,4);
            }
            if(S(0x142)==60) next_sequence_frame();
        }
        if(S(0x140)==2) {
            F(0x11c)*=0.85f;F(0x120)=F(0x11c);
            if(F(0x11c)<=static_cast<double>(0.05f)) RETIRE();
        }
        double cosine=lookup_orientation_cosine_quantized_abs(static_cast<float>(3*I(0x144)+PARAM[0]));
        F(0xec)=static_cast<float>((cosine*F(0x370))*C(0x104)+FIELD(OWNER,float,0xec));
        double sine=lookup_orientation_sine_quantized_abs(static_cast<float>(3*I(0x144)+PARAM[0]));
        F(0xf0)=static_cast<float>(sine*F(0x370)+(FIELD(OWNER,float,0xf0)+100.0));
    }
    if(S(0x13e)==6 || S(0x13e)==7) {
        if(RELATED) {
            void *related=RELATED;
            if(FIELD(related,short,0x140)<=1) {F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        }
        if(S(0x13e)==7 && I(0x144)>5) {
            B(0x184)=0;I(0x180)=0;F(0x120)*=0.85f;
            if(F(0x120)<=static_cast<double>(0.05f)) RETIRE();
        }
    }
    if(S(0x13e)==8) {
        if(RELATED) {
            void *related=RELATED;
            if(FIELD(related,short,0x140)<=1) {F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        }
        F(0x11c)+=0.3f;F(0x120)=F(0x11c);
        if(B(0x113)<20) RETIRE();B(0x113)-=20;
    }
    FINISH();


}
case 857: {

    if(S(0x13e)==0) {
        void *owner=OWNER; F(0xec)=FIELD(owner,float,0xec);F(0xf0)=FIELD(owner,float,0xf0);
        if(FIELD(owner,short,0x13c)!=605 || FIELD(owner,short,0x13e)!=1) RETIRE();
    }
    if(S(0x13e)==1) {
        void *owner=OWNER;F(0xec)=static_cast<float>(61*C(0x104)+FIELD(owner,float,0xec));
        F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+232.0);
        if(FIELD(owner,short,0x13c)!=605 || FIELD(owner,short,0x13e)!=1) RETIRE();
    }
    if(FIELD(OWNER,short,0x186)==0) {FINISH();}
    return;

}
case 858: {

    if(S(0x13e)==1 || S(0x13e)==2) {F(0xf4)=-30.0f;F(0xf8)=9.99f;}
    if(S(0x13e)==3) {
        F(0xf4)=80.0f;F(0xf8)=0.0f;
        if(F(0xf0)<=150.0f) reinterpret_cast<MarisaSpawnOwnerView*>(OWNER)->emit_effect(127,F(0xec),0.0f,B(0x104),1);
        if(I(0x144)%2==0) {
            float packet[3];
            packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%80u)-40.0);
            packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%15u)+10.0);
            packet[2]=5.0f;
            SPAWN_OWNED(858,static_cast<float>(F(0xec)-83*C(0x104)),static_cast<float>(F(0xf0)+77.0),static_cast<unsigned char>(-B(0x104)),1,packet,3);
        }
        if(C(0x104)>0) {
            void *owner=OWNER;
            if(F(0xec)>FIELD(owner,float,0xec) && FIELD(owner,short,0x13e)==2 && FIELD(owner,short,0x13c)==607) FIELD(owner,float,0xf4)=80.0f;
        }
        if(C(0x104)<0) {
            void *owner=OWNER;
            if(F(0xec)<FIELD(owner,float,0xec) && FIELD(owner,short,0x13e)==2 && FIELD(owner,short,0x13c)==607) FIELD(owner,float,0xf4)=80.0f;
        }
        if(F(0xec)>2000.0 || F(0xec)<-720.0f) {--I(0x330);FIELD(OWNER,short,0x730)=1;return;}
    }
    if(S(0x13e)==4) {
        void *owner=OWNER;F(0xf4)=80.0f;F(0xf8)=0.0f;
        if(FIELD(owner,short,0x13e)!=2) RETIRE();
    }
    if(S(0x13e)==5) {
        float *parameters=PARAM;parameters[1]-=0.5;
        if(parameters[1]<1.0f) parameters[1]=1.0f;
        MOTION->set_components(parameters[0],parameters[1]);F(0x12c)+=12.0;
        F(0x11c)+=0.01f;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
    }
    MOVE();FINISH();

}
case 859: {

    if(I(0x180)==5) RETIRE();
    if(S(0x140)==0 && S(0x13e)<4) {
        float *parameters=PARAM;F(0x12c)=F(0x370)+F(0x12c);parameters[1]+=1.0;
        MOTION->set_components(parameters[0],parameters[1]);turn_heading(0.0f,0.2f,100.0f);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
        if(S(0x142)%2==0) {
            float packet[4]={F(0x12c),0.0f,static_cast<float>(S(0x13e)),1.0f};
            SPAWN_OWNED(859,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(S(0x142)>240 || I(0x180)!=0) {
            --I(0x330);float packet[4]={F(0x12c),0.0f,static_cast<float>(S(0x13e)),1.0f};
            SPAWN_OWNED(859,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
        MOVE();
    }
    if(S(0x140)==1 && S(0x13e)<4) {
        if(B(0x113)<=30) RETIRE();
        F(0x11c)-=0.05f;F(0x120)-=0.05f;B(0x113)-=30;
    }
    if(S(0x13e)==4) {
        if(B(0x113)<=40) RETIRE();
        F(0x11c)+=0.1f;F(0x120)+=0.1f;B(0x113)-=40;
    }
    FINISH();


}
case 860: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)==0) {
        float *parameters=PARAM;F(0x12c)=F(0x370)+F(0x12c);F(0x370)+=0.1f;
        parameters[1]+=1.0;MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();
        if(I(0x144)%10==0) {
            float packet[4]={0.0f,0.0f,1.0f,0.0f};
            spawn_parented(860,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
        if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
        if(I(0x180)!=0) {
            if(C(0x184)<=0) {
                --I(0x330);WAVE(21);
                for(int n=12;n!=0;--n) {
                    float packet[4]={0.0f,0.0f,2.0f,0.0f};
                    spawn_unparented(860,F(0xec),F(0xf0),B(0x104),1,packet,4);
                }
                return;
            }
            I(0x180)=0;
        }
        MOVE();
    }
    if(S(0x13e)==1) {
        if(RELATED) {
            void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);S(0x186)=FIELD(related,short,0x186);
            if(B(0x113)<20) RETIRE();F(0x11c)+=0.1f;F(0x120)+=0.1f;B(0x113)-=20;
        } else {
            if(B(0x113)<=30) RETIRE();F(0x11c)+=0.25;F(0x120)+=0.25;B(0x113)-=30;
        }
    }
    if(S(0x13e)==2) {
        float *parameters=PARAM;parameters[1]-=0.5;
        if(parameters[1]<0.0f) parameters[1]=0.0f;
        MOTION->set_components(parameters[0],parameters[1]);F(0x12c)=F(0x370)+F(0x12c);
        if(B(0x113)<=10) RETIRE();F(0x11c)+=0.005f;F(0x120)+=0.005f;B(0x113)-=10;MOVE();
    }
    if(S(0x13e)==3) {
        if(B(0x113)<=8) RETIRE();
        F(0x11c)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(3*I(0x144)))*0.25+F(0x11c));
        F(0x120)=F(0x11c);B(0x113)-=8;
    }
    if(S(0x13e)==4) {
        if(!RELATED) RETIRE();S(0x186)=FIELD(RELATED,short,0x186);
        F(0x12c)-=F(0x370);F(0x370)+=0.1f;
        if(B(0x113)>128) B(0x113)-=20;else B(0x113)=128;
        void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
        F(0x11c)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(20*I(0x144)))*0.1f+1.2f);
        F(0x120)=F(0x11c);
    }
    FINISH();

}
case 861: {

    if(I(0x180)==5) RETIRE();
    if(S(0x140)==0 && S(0x13e)<4) {
        if(S(0x364)==0) {
            float *parameters=PARAM;F(0x12c)+=12.0;parameters[1]-=0.1f;
            if(parameters[1]<=0.0f) {S(0x364)=1;parameters=PARAM;parameters[1]=0.0f;}
            parameters[0]+=1.0;MOTION->set_components(parameters[0],parameters[1]);
        }
        if(S(0x364)==1) {
            float *parameters=PARAM;F(0x12c)+=12.0;parameters[1]+=0.5;parameters[0]+=1.0;
            MOTION->set_components(parameters[0],parameters[1]);
        }
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1000.0 || F(0xf0)<-100.0) RETIRE();
        if(S(0x142)>240 || I(0x180)!=0) --I(0x330);MOVE();
    }
    if(S(0x140)==1 && S(0x13e)<4) {
        if(B(0x113)<=20) RETIRE();F(0x11c)*=0.98f;F(0x120)=F(0x11c);B(0x113)-=20;
    }
    if(S(0x13e)==4) {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)==610 && FIELD(owner,short,0x13e)<=1) {
            F(0xec)=static_cast<float>(28*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+185.0);
            float variation=static_cast<float>(RF(20)*static_cast<double>(0.01f));
            F(0x11c)=variation+0.9f;F(0x120)=F(0x11c);
        } else {
            if(B(0x113)<=20) RETIRE();F(0x11c)*=0.85f;F(0x120)=F(0x11c);B(0x113)-=20;
        }
    }
    if(S(0x13e)==5) {
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)==610 && FIELD(owner,short,0x13e)<=1 && I(0x144)<40) {
            F(0xec)=static_cast<float>(28*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+185.0);
            F(0x370)-=0.05f;if(F(0x370)<0.01f) F(0x370)=0.01f;
            F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);
            if(B(0x113)>192) {B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}
        } else {
            F(0x370)-=0.05f;if(F(0x370)<0.01f) F(0x370)=0.01f;
            F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);
            if(B(0x113)<=10) RETIRE();B(0x113)-=10;
        }
    }
    FINISH();


}
case 863: {

    if(I(0x180)==5) RETIRE();
    if(S(0x13e)<=1) {
        F(0x12c)+=8.0;
        if(F(0xec)>1380.0 || F(0xec)<-100.0) RETIRE();
        if(I(0x144)%5==0) {
            float packet[4]={0.0f,0.0f,6.0f,0.0f};
            spawn_parented(863,F(0xec),F(0xf0),B(0x104),-1,packet,4);
        }
        if(S(0x13e)==0) F(0xf8)-=0.5;
        double previousY=F(0xf0);
        if(stage_surface_height()>=previousY) {
            select_sequence(2);F(0xf4)=0.0f;F(0xf8)=0.0f;F(0xf0)=0.0f;
            emit_effect(127,F(0xec),0.0f,B(0x104),-1);
            emit_effect(127,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),-1);
            float packet[4]={0.0f,0.0f,4.0f,0.0f};
            spawn_unparented(863,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(8);return;
        }
        MOVE();
    }
    if(S(0x13e)==2) {
        int age=I(0x144);
        if(age>=0 && age%3==0 && age<=15) {
            double x=20*age*C(0x104)+static_cast<double>(F(0xec));
            if(x>=-100.0 && x<=1380.0) {
                float packet[4]={0.0f,0.0f,3.0f,0.0f};
                spawn_unparented(863,static_cast<float>(20*I(0x144)*C(0x104)+F(0xec)),F(0xf0),B(0x104),1,packet,4);
            }
            x=F(0xec)-static_cast<double>(20*I(0x144)*C(0x104));
            if(x>=-100.0 && x<=1380.0) {
                float packet[4]={0.0f,0.0f,3.0f,0.0f};
                spawn_unparented(863,static_cast<float>(F(0xec)-20*I(0x144)*C(0x104)),F(0xf0),B(0x104),1,packet,4);
            }
        }
        if(I(0x144)>=60) RETIRE();
    }
    if(S(0x13e)==3) {
        if(S(0x140)==0) {
            if(I(0x180)==6) {I(0x180)=0;++B(0x184);}
            if(I(0x180)!=0) {if(++S(0x368)>10) {S(0x368)=0;I(0x180)=0;}}
            F(0x11c)=static_cast<float>((I(0x144)%2)*static_cast<double>(0.1f)+1.0);
            F(0x120)=static_cast<float>(static_cast<double>(0.1f)*(I(0x144)%2)+1.0);
        }
        if(S(0x140)==1) {
            F(0x11c)*=1.05f;F(0x120)=1.05f*F(0x120);
            if(B(0x113)<30) RETIRE();if(I(0x144)>10) B(0x113)-=30;
        }
    }
    if(S(0x13e)==4) {
        F(0x11c)=F(0x370)+F(0x11c);F(0x120)=F(0x11c);F(0x370)-=0.15f;
        if(F(0x370)<=static_cast<double>(0.05f)) F(0x370)=0.05f;
        if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;
    }
    if(S(0x13e)==5) {
        MOTION->set_components(PARAM[0],PARAM[1]);float *parameters=PARAM;
        parameters[1]-=1.25;if(parameters[1]<0.5f) parameters[1]=0.5f;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
        F(0x11c)+=0.01f;F(0x120)+=0.01f;
        if(B(0x113)<10) RETIRE();
        if(parameters[3]<=static_cast<double>(I(0x144))) {B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
    }
    if(S(0x13e)==6) {
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        F(0x11c)+=0.3f;F(0x120)+=0.3f;
        if(B(0x113)<30) RETIRE();B(0x113)-=30;B(0x112)-=30;B(0x111)-=30;
    }
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0) {
        if(S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) --I(0x330);
        if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2) --I(0x330);
    }
    return;


}
case 865: {

    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3:case 4:case 5: {
        if(FIELD(OWNER,short,0x7a4)==0) {S(0x364)=0;S(0x366)=0;S(0x368)=0;}
        void *owner=OWNER;
        if(FIELD(owner,short,0x174)<=0 || FIELD(TARGET,short,0x174)<=0 || FIELD(owner,short,0x7a6)<=0) {
            float packet[3]={0.0f,0.0f,6.0f};
            spawn_unparented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
            packet[2]=7.0f;
            spawn_unparented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);RETIRE();
        }
        if(FIELD(owner,short,0x7a4)==S(0x13e)+2) {
            FIELD(owner,short,0x7a4)=1;WAVE(0);
            owner=OWNER;void *target=TARGET;
            float packet[3];
            packet[0]=-atan2_degrees(FIELD(target,float,0xf0)-FIELD(owner,float,0xf0),static_cast<float>((FIELD(target,float,0xec)-FIELD(owner,float,0xec))*static_cast<double>(FIELD(owner,signed char,0x104))));
            if(packet[0]>30.0) packet[0]=30.0f;if(packet[0]<-30.0) packet[0]=-30.0f;
            packet[1]=15.0f;packet[2]=8.0f;
            spawn_unparented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
            packet[2]=9.0f;
            spawn_unparented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
            packet[2]=10.0f;
            spawn_unparented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
        }
        if(FIELD(OWNER,short,0x7a4)==8 && S(0x364)==0) {
            S(0x364)=1;if(S(0x13e)==0) WAVE(4);
            float packet[3]={0.0f,0.0f,19.0f};
            spawn_parented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
            packet[2]=21.0f;
            spawn_parented(865,F(0xec),F(0xf0),FIELD(OWNER,unsigned char,0x104),1,packet,3);
        }
        float *parameters=PARAM;parameters[1]+=5.0;if(parameters[1]>120.0) parameters[1]=120.0f;
        double cosine=lookup_orientation_cosine_quantized_abs(-parameters[0]-FIELD(OWNER,float,0x7ac));
        parameters=PARAM;owner=OWNER;
        F(0xec)=static_cast<float>(cosine*parameters[1]*C(0x104)+FIELD(owner,float,0xec));
        double sine=lookup_orientation_sine_quantized_abs(-parameters[0]-FIELD(owner,float,0x7ac));
        F(0xf0)=static_cast<float>(sine*PARAM[1]+(FIELD(OWNER,float,0xf0)+100.0));
        FINISH();
    }
    case 6:case 9:
shrink_rgb_fade:
        F(0x11c)*=0.9f;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
    case 7:case 10:
expand_rgb_fade:
        F(0x11c)+=0.2f;F(0x120)=F(0x11c);
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
    case 8: {
        advance_six(5);if(emit_repeated(0,0,3)) RETIRE();
        if(C(0x184)<=0) {
            float packet[3]={0.0f,0.0f,9.0f};
            spawn_unparented(865,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=10.0f;
            spawn_unparented(865,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        float *parameters=PARAM;parameters[1]+=0.1f;MOTION->set_components(parameters[0],parameters[1]);MOVE();
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || !(F(0xf0)>=-100.0)) RETIRE();FINISH();
    }
    case 19:case 20:
        if(RELATED) {
            void *related=RELATED;F(0xec)=static_cast<float>(50*C(0x104)+FIELD(related,float,0xec));F(0xf0)=FIELD(related,float,0xf0);
            F(0x12c)=static_cast<float>(lookup_orientation_sine_quantized_abs(-FIELD(related,float*,0x340)[0]-FIELD(OWNER,float,0x7ac))*(-4.0));
        } else {S(0x364)=1;B(0x184)=0;}
        if(S(0x364)!=0) {
            B(0x184)=0;F(0x120)*=0.9f;
            if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
        }
        if(FIELD(OWNER,short,0x7a8)<=0) {S(0x364)=1;B(0x184)=0;return;}
        F(0x120)+=0.1f;if(F(0x120)>1.0f) F(0x120)=1.0f;advance_six(0);
        if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        FINISH();
    case 21:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);} else S(0x364)=1;
        if(S(0x364)==0) {
            F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(I(0x144))*3.0))*0.2f+1.0);
            F(0x120)=F(0x11c);
            if(B(0x113)>245) B(0x113)=255;else B(0x113)+=10;
            if(FIELD(OWNER,short,0x7a8)<=0) {S(0x364)=1;B(0x184)=0;return;}
            FINISH();
        }
        F(0x120)*=0.98f;if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
    default:FINISH();
    }


}
case 869: {

    switch(S(0x13e)) {
    case 1:case 3:case 5:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}else S(0x364)=2;
        if(S(0x364)==0) {
            void *owner=OWNER;if(FIELD(owner,short,0x13c)!=619 || FIELD(owner,short,0x13e)>=5) {S(0x364)=2;return;}
            advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        }
        if(S(0x364)==2) {
            B(0x184)=0;F(0x120)*=0.99f;F(0x11c)+=0.2f;
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        FINISH();
    case 2:case 4:case 6:
        F(0x120)+=0.2f;F(0x11c)+=0.05f;if(B(0x113)<=5) RETIRE();B(0x113)-=5;FINISH();
    case 7: {
        if(S(0x364)!=0) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();}
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(70)*static_cast<double>(0.1f)+10.0);packet[2]=12.0f;
            spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)!=619) S(0x364)=1;
        else {
            F(0xec)=static_cast<float>(100*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
            if(FIELD(owner,short,0x13c)==619 && FIELD(owner,short,0x13e)>=5) S(0x364)=1;
        }
        FINISH();
    }
    case 9: {
        if(S(0x364)==0) {
            float *parameters=PARAM;void *owner=OWNER;F(0x370)+=parameters[1];parameters[1]*=0.95f;
            F(0x11c)+=parameters[3];F(0x120)=F(0x11c);parameters[3]*=0.8f;
            if(FIELD(owner,short,0x13c)==619 && FIELD(owner,short,0x13e)==4) {parameters[3]=0.75f;parameters[1]=7.0f;S(0x364)=1;}
            if(FIELD(OWNER,short,0x13c)!=619) {S(0x364)=2;return;}
        }
        if(S(0x364)==1) {
            float *parameters=PARAM;F(0x370)+=parameters[1];parameters[1]*=0.9f;
            F(0x11c)+=parameters[3];F(0x120)=F(0x11c);parameters[3]=0.95f*parameters[3];
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        if(!RELATED) {S(0x364)=2;return;}
        double cosine=lookup_orientation_cosine_quantized_abs(-PARAM[0]);
        F(0xec)=static_cast<float>(cosine*F(0x370)*C(0x104)+FIELD(RELATED,float,0xec));
        double sine=lookup_orientation_sine_quantized_abs(-PARAM[0]);
        F(0xf0)=static_cast<float>(sine*F(0x370)+FIELD(RELATED,float,0xf0));
        if(S(0x364)==2) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;}FINISH();
    }
    case 10:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        if(S(0x364)==0) {
            if(FIELD(OWNER,short,0x13c)!=619) {S(0x364)=2;return;}
            if(!(F(0x120)<static_cast<double>(0.1f))) {F(0x120)=0.1f;B(0x184)=1;S(0x364)=1;}
            else F(0x120)+=0.005f;
        }
        if(S(0x364)==1) {
            void *owner=OWNER;if(FIELD(owner,short,0x13c)!=619) {S(0x364)=2;return;}
            if(FIELD(owner,short,0x13e)==4) {
                float packet[3];packet[0]=F(0x12c);select_sequence(5);packet[2]=6.0f;
                F(0x11c)=4.0f;F(0x120)=2.0f;S(0x364)=0;S(0x366)=0;packet[1]=0.0f;
                spawn_unparented(869,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(11);B(0x184)=1;I(0x180)=0;return;
            }
            advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        }
        if(S(0x364)==2) {
            B(0x184)=0;F(0x120)*=0.99f;F(0x11c)+=0.2f;
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        FINISH();
    case 11: {
        if(S(0x364)!=0) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();}
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(30)*static_cast<double>(0.1f)+2.0);packet[2]=12.0f;
            spawn_unparented(869,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;
        if(FIELD(owner,short,0x13c)!=619) {S(0x364)=1;return;}
        F(0xec)=static_cast<float>(100*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
        if(FIELD(owner,short,0x13c)!=619) {S(0x364)=1;return;}
        if(FIELD(owner,short,0x13e)==4) {select_sequence(7);return;}FINISH();
    }
    case 12:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=0.95f;F(0x11c)*=0.98f;F(0x120)=F(0x11c);
        if(I(0x144)>=10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}MOVE();FINISH();
    default:FINISH();
    }


}
case 900: {

    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3: {
        if(FIELD(OWNER,short,0x174)<=0) RETIRE();
        if(I(0x144)%5==0) {
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(60))+(PARAM[0]+150.0));
            packet[1]=static_cast<float>(RF(9)+6.0);packet[2]=static_cast<float>(S(0x13e)+14.0);
            spawn_parented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(I(0x144)%20==0) {
            float packet[3]={0.0f,0.0f,static_cast<float>(S(0x13e)+8.0)};
            spawn_parented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        F(0x12c)=F(0x378)+F(0x12c);advance_six(0);
        double verticalSquared=square_float_value(F(0xf0)-F(0x374));
        if(square_float_value(F(0xec)-F(0x370))+verticalSquared<=10000.0 || I(0x180)!=0) {
            WAVE(3);float packet[3]={0.0f,0.0f,12.0f};
            spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=13.0f;
            spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
            switch(g_match_identifier) {
            case 1: {float index=0.0f;do {packet[0]=static_cast<float>(index*60.0);packet[1]=6.0f;packet[2]=18.0f;
                spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);index+=1.0;}while(index<6.0f);break;}
            case 2: {float index=0.0f;do {packet[0]=static_cast<float>(index*36.0);packet[1]=6.0f;packet[2]=18.0f;
                spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);index+=1.0;}while(index<10.0f);break;}
            case 3: {float index=0.0f;do {packet[0]=static_cast<float>(index*22.5);packet[1]=6.0f;packet[2]=18.0f;
                spawn_unparented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);index+=1.0;}while(index<16.0f);break;}
            }
            RETIRE();
        }
        float *parameters=PARAM;parameters[1]-=0.5;if(parameters[1]<6.0f) parameters[1]=6.0f;
        MOTION->set_components(parameters[0],parameters[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();
    }
    case 4:case 5:case 6:case 7:
        F(0x11c)*=0.9f;F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;FINISH();
    case 8:case 9:case 10:case 11: {
        if(!RELATED) RETIRE();void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);
        F(0x11c)+=0.05f;F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();
    }
    case 12:
        if(S(0x364)<=1 && FIELD(OWNER,short,0x174)<=0) {S(0x364)=2;B(0x184)=0;return;}
        if(S(0x364)==0) {
            F(0x11c)+=0.15f;F(0x120)=F(0x11c);
            if(F(0x11c)>1.0f) {F(0x11c)=1.0f;F(0x120)=1.0f;S(0x364)=1;B(0x184)=1;return;}
        }
        if(S(0x364)==1) {
            advance_six(0);advance_phase(0);if(--S(0x366)<=0) B(0x184)=0;
            if(C(0x184)<=0) {S(0x364)=2;return;}
        }
        if(S(0x364)==2) {
            F(0x11c)*=0.99f;F(0x120)=F(0x11c);if(B(0x113)<5) RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;
        }
        FINISH();
    case 13:
        F(0x11c)+=0.2f;F(0x120)=F(0x11c);if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();
    case 14:case 15:case 16:case 17:
        if(B(0x113)<=10) RETIRE();B(0x113)-=10;MOTION->set_components(PARAM[0],PARAM[1]);MOVE();FINISH();
    case 18:
        if(FIELD(OWNER,short,0x174)<=0 || C(0x184)<=0) {
            float packet[3]={0.0f,0.0f,4.0f};spawn_parented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        if(I(0x144)%20==0) {
            float packet[3]={0.0f,0.0f,10.0f};spawn_parented(900,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        F(0x12c)+=2.0;MOTION->set_components(PARAM[0],PARAM[1]);
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || F(0xf0)<-100.0) RETIRE();MOVE();FINISH();
    default:FINISH();
    }


}
case 901: {

    switch(S(0x13e)) {
    case 0:case 1:case 2:case 3:case 4:case 5: {
        void *owner=OWNER;
        if(FIELD(owner,short,0x174)<=0) {
            float packet[3]={0.0f,0.0f,6.0f};spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);
            packet[2]=7.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        if(FIELD(owner,short,0x13c)==720) {
            short sequence=FIELD(owner,short,0x13e);if(sequence>=2 && sequence<=4) S(0x364)=0;
            owner=OWNER;
            if(FIELD(owner,short,0x13e)==5 && FIELD(owner,short,0x738)==1 && FIELD(owner,short,0x736)==S(0x13e)+1) {
                FIELD(owner,short,0x736)=0;WAVE(0);void *target=TARGET;owner=OWNER;
                float packet[3]={-atan2_degrees(FIELD(target,float,0xf0)-FIELD(owner,float,0xf0),static_cast<float>((FIELD(target,float,0xec)-FIELD(owner,float,0xec))*static_cast<double>(C(0x104)))),7.0f,8.0f};
                spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=9.0f;
                spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=10.0f;
                spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            owner=OWNER;
            if(FIELD(owner,short,0x13e)==6 && FIELD(owner,short,0x738)==1 && I(0x144)%5==0) {
                ++S(0x364);WAVE(0);
                float packet[3]={PARAM[0]+FIELD(OWNER,float,0x73c),4.0f,static_cast<float>((S(0x364)%4)+11.0)};
                spawn_parented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=9.0f;
                spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
            owner=OWNER;
            if(FIELD(owner,short,0x13e)==7 && FIELD(owner,short,0x738)==1 && S(0x364)==0) {
                S(0x364)=1;if(S(0x13e)==0) WAVE(10);
                float packet[3]={PARAM[0]+FIELD(OWNER,float,0x73c),0.0f,19.0f};
                spawn_parented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=21.0f;
                spawn_parented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);
            }
        }
        owner=OWNER;double cosine=lookup_orientation_cosine_quantized_abs(-PARAM[0]-FIELD(owner,float,0x73c));
        F(0xec)=static_cast<float>(cosine*FIELD(owner,float,0x740)*C(0x104)+FIELD(owner,float,0xec));
        double sine=lookup_orientation_sine_quantized_abs(-PARAM[0]-FIELD(owner,float,0x73c));
        F(0xf0)=static_cast<float>(sine*FIELD(OWNER,float,0x740)+(FIELD(OWNER,float,0xf0)+100.0));FINISH();
    }
    case 6:case 9:goto shrink_rgb_fade;
    case 7:case 10:goto expand_rgb_fade;
    case 8: {
        advance_six(5);
        if(FIELD(OWNER,short,0x174)>0 && C(0x184)>0) {
            float *parameters=PARAM;parameters[1]+=0.1f;MOTION->set_components(parameters[0],parameters[1]);MOVE();
            if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || !(F(0xf0)>=-100.0)) RETIRE();FINISH();
        }
        float packet[3]={0.0f,0.0f,9.0f};spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);
        packet[2]=10.0f;spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
    }
    case 11:case 12:case 13:case 14:
        F(0x12c)=F(0x370)+F(0x12c);advance_six(1);
        if(FIELD(OWNER,short,0x174)<=0 || C(0x184)<=0) {
            float packet[3]={F(0x12c),0.0f,static_cast<float>(S(0x13e)+4.0)};
            spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,packet,3);RETIRE();
        }
        MOTION->set_components(PARAM[0],PARAM[1]);MOVE();
        if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1060.0f || !(F(0xf0)>=-100.0)) RETIRE();FINISH();
    case 15:case 16:case 17:case 18:
        F(0x11c)+=0.2f;F(0x120)=F(0x11c);if(B(0x113)<=15) RETIRE();B(0x113)-=15;FINISH();
    case 19:case 20: {
        if(RELATED) {
            void *related=RELATED;
            double cosine=lookup_orientation_cosine_quantized_abs(-FIELD(related,float*,0x340)[0]-FIELD(OWNER,float,0x73c));
            void *owner=OWNER;F(0xec)=static_cast<float>(cosine*50.0*C(0x104)+FIELD(related,float,0xec));
            double sine=lookup_orientation_sine_quantized_abs(-FIELD(related,float*,0x340)[0]-FIELD(owner,float,0x73c));
            related=RELATED;owner=OWNER;F(0xf0)=static_cast<float>(sine*50.0+FIELD(related,float,0xf0));
            F(0x12c)=FIELD(related,float*,0x340)[0]+FIELD(owner,float,0x73c);
        }else {S(0x364)=1;B(0x184)=0;}
        if(S(0x364)!=0) {
            B(0x184)=0;F(0x120)*=0.9f;if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
        }
        void *owner=OWNER;
        if(FIELD(owner,short,0x174)<=0 || FIELD(owner,short,0x738)==0 || FIELD(owner,short,0x13c)!=720 || FIELD(owner,short,0x13e)!=7) {S(0x364)=1;B(0x184)=0;return;}
        if(I(0x144)>60) {
            F(0x120)+=0.1f;if(F(0x120)>1.0f) F(0x120)=1.0f;advance_six(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        } else if(I(0x144)==60) B(0x184)=1;
        FINISH();
    }
    case 21:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}else S(0x364)=1;
        if(S(0x364)==0) {
            F(0x11c)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(I(0x144))*3.0))*0.2f+1.0);F(0x120)=F(0x11c);
            if(B(0x113)>245) B(0x113)=255;else B(0x113)+=10;
            void *owner=OWNER;
            if(FIELD(owner,short,0x174)<=0 || FIELD(owner,short,0x738)==0 || FIELD(owner,short,0x13c)!=720 || FIELD(owner,short,0x13e)!=7) {S(0x364)=1;return;}FINISH();
        }
        F(0x120)*=0.98f;if(B(0x113)<=10) RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;FINISH();
    default:FINISH();
    }


}
case 920: {

    switch(S(0x13e)) {
    case 1:case 3:case 5:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        if(S(0x364)==0) {
            void *owner=OWNER;short action=FIELD(owner,short,0x13c);
            if(action<=729 || action>=734 || FIELD(owner,short,0x13e)>=2) S(0x364)=2;
            advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        }
        if(S(0x364)==2) {
            B(0x184)=0;F(0x120)*=0.99f;F(0x11c)+=0.2f;if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        FINISH();
    case 2:case 4:case 6:
        F(0x120)+=0.2f;F(0x11c)+=0.05f;if(B(0x113)<=5) RETIRE();B(0x113)-=5;FINISH();
    case 7: {
        if(S(0x364)!=0) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();}
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(70)*static_cast<double>(0.1f)+10.0);packet[2]=12.0f;
            spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        if(g_match_identifier==3 && I(0x144)%3==0) {
            float center=static_cast<float>(PARAM[0]+180.0+60.0);float packet[4];
            packet[0]=static_cast<float>(center-static_cast<double>(RF(120)));packet[1]=static_cast<float>(RF(13)+12.0);packet[2]=RF(4);
            packet[3]=static_cast<float>(RF(60)*static_cast<double>(0.1f)-3.0);
            spawn_unparented(921,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
        if(g_match_identifier==2 && I(0x144)%5==0) {
            float center=static_cast<float>(PARAM[0]+180.0+40.0);float packet[4];
            packet[0]=static_cast<float>(center-static_cast<double>(RF(80)));packet[1]=static_cast<float>(RF(13)+12.0);packet[2]=RF(4);
            packet[3]=static_cast<float>(RF(60)*static_cast<double>(0.1f)-3.0);
            spawn_unparented(921,F(0xec),F(0xf0),B(0x104),1,packet,4);
        }
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action==730 || action==731) {
            F(0xec)=static_cast<float>(100*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
            if(FIELD(owner,short,0x13c)==731 && FIELD(owner,short,0x13e)>1) S(0x364)=1;
        }else if(action==732 || action==733) {
            F(0xec)=static_cast<float>(90*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+130.0);
            if(FIELD(owner,short,0x13c)==733 && FIELD(owner,short,0x13e)>1) S(0x364)=1;
        }else S(0x364)=1;
        FINISH();
    }
    case 9: {
        if(S(0x364)==0) {
            float *parameters=PARAM;void *owner=OWNER;F(0x370)+=parameters[1];parameters[1]*=0.95f;
            F(0x11c)+=parameters[3];F(0x120)=F(0x11c);parameters[3]*=0.8f;
            short action=FIELD(owner,short,0x13c);
            if((action==731 || action==733) && FIELD(owner,short,0x13e)==1) {parameters[3]=0.75f;parameters[1]=7.0f;S(0x364)=1;}
        }
        if(S(0x364)==1) {
            float *parameters=PARAM;F(0x370)+=parameters[1];parameters[1]*=0.9f;
            F(0x11c)+=parameters[3];F(0x120)=F(0x11c);parameters[3]=0.95f*parameters[3];
            if(B(0x113)<=5) RETIRE();B(0x113)-=5;
        }
        if(RELATED) {
            double cosine=lookup_orientation_cosine_quantized_abs(-PARAM[0]);
            F(0xec)=static_cast<float>(cosine*F(0x370)*C(0x104)+FIELD(RELATED,float,0xec));
            double sine=lookup_orientation_sine_quantized_abs(-PARAM[0]);
            F(0xf0)=static_cast<float>(sine*F(0x370)+FIELD(RELATED,float,0xf0));
        }
        if(S(0x364)==2) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;}FINISH();
    }
    case 10:
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);}
        if(S(0x364)==0) {
            short action=FIELD(OWNER,short,0x13c);if(action<=729 || action>=734) S(0x364)=2;
            if(F(0x120)<static_cast<double>(0.1f)) F(0x120)+=0.005f;
            else {F(0x120)=0.1f;B(0x184)=1;S(0x364)=1;}
        }
        if(S(0x364)==1) {
            short action=FIELD(OWNER,short,0x13c);if(action<=729 || action>=734) S(0x364)=2;
            void *owner=OWNER;action=FIELD(owner,short,0x13c);
            if((action==731 || action==733) && FIELD(owner,short,0x13e)==1) {
                float packet[3];packet[0]=F(0x12c);
                switch(g_match_identifier) {
                case 0:select_sequence(1);packet[2]=2.0f;F(0x11c)=10.0f;F(0x120)=1.0f;break;
                case 1:select_sequence(3);packet[2]=2.0f;F(0x11c)=10.0f;F(0x120)=1.0f;break;
                case 2:select_sequence(3);packet[2]=4.0f;F(0x11c)=6.0f;F(0x120)=1.5f;break;
                case 3:select_sequence(5);packet[2]=6.0f;F(0x11c)=4.0f;F(0x120)=2.0f;break;
                }
                S(0x364)=0;S(0x366)=0;packet[1]=0.0f;
                spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);WAVE(11);B(0x184)=1;I(0x180)=0;return;
            }
            advance_six(0);advance_phase(0);
            if(I(0x180)!=0 && ++S(0x366)>=5) {S(0x366)=0;B(0x184)=1;I(0x180)=0;}
        }
        if(S(0x364)==2) {B(0x184)=0;F(0x120)*=0.99f;F(0x11c)+=0.2f;if(B(0x113)<=5) RETIRE();B(0x113)-=5;}FINISH();
    case 11: {
        if(S(0x364)!=0) {if(B(0x113)<=10) RETIRE();B(0x113)-=10;FINISH();}
        if(I(0x144)%2==0) {
            float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(RF(30)*static_cast<double>(0.1f)+2.0);packet[2]=12.0f;
            spawn_unparented(920,F(0xec),F(0xf0),B(0x104),1,packet,3);
        }
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action==730 || action==731) {
            F(0xec)=static_cast<float>(100*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+105.0);
            action=FIELD(owner,short,0x13c);if(action==731 && FIELD(owner,short,0x13e)==1) {select_sequence(7);return;}
        }
        if(action==732 || action==733) {
            F(0xec)=static_cast<float>(90*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+130.0);
            action=FIELD(owner,short,0x13c);if(action==733 && FIELD(owner,short,0x13e)==1) {select_sequence(7);return;}
        }
        if(action<=729 || action>=734) S(0x364)=1;FINISH();
    }
    case 12:
        MOTION->set_components(PARAM[0],PARAM[1]);PARAM[1]*=0.95f;F(0x11c)*=0.98f;F(0x120)=F(0x11c);
        if(I(0x144)>=10) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}MOVE();FINISH();
    default:FINISH();
    }


}
case 921: {

    F(0x12c)=PARAM[3]+F(0x12c);
    if(S(0x140)!=0) {
        if(B(0x113)<5) RETIRE();B(0x113)-=5;F(0x11c)+=0.05f;F(0x120)=F(0x11c);
    }else if(I(0x180)!=0) {next_sequence_frame();F(0xf4)=0.0f;F(0xf8)=0.0f;return;}
    MOVE();if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)<-200.0 || F(0xf0)>1000.0) RETIRE();FINISH();

}
case 980: {

    update_ping_pong_motion();FINISH();

}
case 989: {
 {
    void *owner=OWNER;if(FIELD(owner,short,0x13c)<300) RETIRE();if(FIELD(owner,short,0x186)>0) return;
    if(S(0x13e)==0) {
        float *parameters=PARAM;F(0xec)=static_cast<float>(C(0x104)*parameters[0]+FIELD(owner,float,0xec));F(0xf0)=FIELD(owner,float,0xf0)+parameters[1];
        F(0x11c)+=0.001f;F(0x120)+=0.001f;
        if(B(0x110)>=250) {B(0x110)=255;B(0x111)+=4;}else B(0x110)+=5;
        if(I(0x144)>=120) {
            select_sequence(2);float packet[3]={0.0f,0.0f,3.0f};spawn_parented(989,F(0xec),F(0xf0),B(0x104),1,packet,3);
            B(0x110)=255;B(0x111)=255;B(0x112)=255;return;
        }
    }
    if(S(0x13e)==1) {
        if(B(0x113)>=250) B(0x113)=255;else B(0x113)+=5;
        F(0x11c)-=0.002f;F(0x120)-=0.002f;
        if(RELATED) {void *related=RELATED;F(0xec)=FIELD(related,float,0xec);F(0xf0)=FIELD(related,float,0xf0);if(FIELD(related,short,0x13e)==2) RETIRE();}
    }
    if(S(0x13e)==2) {
        if(B(0x113)<10) RETIRE();F(0x11c)*=0.9f;F(0x120)=F(0x11c);B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;
    }
    if(S(0x13e)==3) {
        if(B(0x113)<5) RETIRE();F(0x11c)+=0.1f;F(0x120)+=0.1f;B(0x113)-=5;B(0x111)-=5;B(0x112)-=5;
    }
    FINISH();
}

}
case 990: {
 {
    void *owner=OWNER;F(0xec)=static_cast<float>(FIELD(owner,float,0xec)-82*C(0x104));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+132.0);
    short action=FIELD(owner,short,0x13c);
    if((action==600 && FIELD(owner,short,0x13e)==1) || (action==601 && FIELD(owner,short,0x13e)==1)
       || (action==602 && FIELD(owner,short,0x13e)==1) || (action==619 && (FIELD(owner,short,0x13e)==4 || FIELD(owner,short,0x13e)==5))
       || (action==731 && FIELD(owner,short,0x13e)==1) || (action==731 && FIELD(owner,short,0x13e)==2)
       || (action==733 && (FIELD(owner,short,0x13e)==1 || FIELD(owner,short,0x13e)==2))) {FINISH();}
    RETIRE();
}

}
case 998: {

    F(0x12c)+=5.0;
    if(S(0x13e)==0) {
        void *owner=OWNER;short action=FIELD(owner,short,0x13c);
        if(action>153 && action<158) {F(0xec)=static_cast<float>(57*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+60.0);}
        action=FIELD(owner,short,0x13c);
        if(action>149 && action<154) {F(0xec)=static_cast<float>(57*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+94.0);}
        if(FIELD(owner,short,0x13c)==158) {F(0xec)=static_cast<float>(57*C(0x104)+FIELD(owner,float,0xec));F(0xf0)=static_cast<float>(FIELD(owner,float,0xf0)+100.0);}
        action=FIELD(owner,short,0x13c);if(action<150 || action>158) {next_sequence_block();FIELD(OWNER,unsigned char,0x751)=0;}
    }
    if(S(0x13e)==1) {if(B(0x113)<10) RETIRE();B(0x113)-=10;}FINISH();

}
case 999: {

    if(static_cast<unsigned>(S(0x13e))<=1u) {
        FIELD(OWNER,float,0xec)=F(0xec);if(F(0xec)>1480.0f || F(0xec)<-200.0) RETIRE();
        if(S(0x13e)>=1) F(0xf8)-=F(0x100);
    }
    F(0xec)=C(0x104)*F(0xf4)+F(0xec);F(0xf0)=F(0xf0)+F(0xf8);
    if(advance_frame()) --I(0x330);
    if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1) {F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}
    return;

}
default:advance_frame();return;
}
}
}
