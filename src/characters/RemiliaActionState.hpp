#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class RemiliaActionStateView;
int __fastcall initialize_fighter_phase_631e0(RemiliaActionStateView *);
extern int g_match_identifier;
unsigned __cdecl remilia_random(int);
unsigned __cdecl remilia_random_u32();
float __cdecl remilia_atan(float,float);
float __cdecl sqrt_float_value(float);
float __cdecl absolute_scalar_float(float);
double __cdecl remilia_sine(float);
double __cdecl remilia_cosine(float);
float __fastcall remilia_surface(RemiliaActionStateView *);
unsigned char __fastcall remilia_on_surface(RemiliaActionStateView *);
struct RemiliaCardDeque { short *at(unsigned); };
struct RemiliaActionScratch { void reset(); };
// Pointer-only extension, not a complete owner layout.
// Pointer-only extension; never instantiate as a recovered complete Fighter.
class RemiliaActionStateView : public AnimationSequenceObjectView {
public:
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    signed char classify_fighter_x_boundary();
    unsigned char advance();
    void zero_motion();
    void set_oriented_components_f0_f4(float,float);
    void event(unsigned);
    void flip();
    unsigned char directional(int);
    void layout(float);
    int spawn(int,float,float,int,int,const void *,int);
    void effect(int,float,float,int,int);
    void counter(short,int);
    int phase_counter(int);
    void texture(signed char,short);
    void finalize(int);
    void copy_health();
    void sequence_window(signed char,int,int);
    void secondary_cycle();
    void common_update();
    template<class T> __forceinline T &at(unsigned o) {
        return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+o);
    }
    __forceinline RemiliaActionStateView *peer() { return static_cast<RemiliaActionStateView *>(related_170); }
    __forceinline RemiliaActionStateView *owner() { return at<RemiliaActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<RemiliaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(remilia_random_u32()%100u)),
               static_cast<float>(static_cast<float>(remilia_random_u32()%200u)+at<float>(0xf0)),direction,1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=ahead?static_cast<float>(80*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))):at<float>(0xec);
        effect(125,x,y,direction,1);
        effect(126,at<float>(0xec),static_cast<float>(at<float>(0xf0)+height),
               reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104),1);
        event(31);
    }
    __forceinline void high_jump(float vx,float vy,float gravity) {
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);at<float>(0xf0)=remilia_surface(this);zero_motion();return;
        }
        if(remilia_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(at<float>(0xf8)<-20.0f)at<float>(0xf8)=-20.0f;
        }
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=gravity;at<unsigned char>(0x47e)=0;
            effect(63,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1);
        }
    }
    __forceinline void idle_motion() {
        if(!at<unsigned char>(0x47e)){zero_motion();return;}
        if(at<float>(0xf4)>0.0f) {
            at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-0.5);
            if(at<float>(0xf4)<0.0f){zero_motion();at<unsigned char>(0x47e)=0;}
        }
        if(at<float>(0xf4)<0.0f) {
            at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.5);
            if(at<float>(0xf4)>0.0f){zero_motion();at<unsigned char>(0x47e)=0;}
        }
    }
    __forceinline void ground_face() {
        if(peer()->at<float>(0xec)<static_cast<double>(at<float>(0xec)))at<unsigned char>(0x104)=255;
        if(peer()->at<float>(0xec)>static_cast<double>(at<float>(0xec)))at<unsigned char>(0x104)=1;
    }
    __forceinline void normal_jump(float vx,float vy) {
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !at<unsigned char>(0x47e))zero_motion();
        }
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);at<float>(0xf0)=remilia_surface(this);zero_motion();return;
            }
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=0.95f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline void recovery_jump(float vx,float vy) {
        if(!sequence_index_13e || sequence_index_13e==3)landing();
        else{at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){at<float>(0xf0)=remilia_surface(this);zero_motion();select_sequence(3);return;}}
        if(advance()){if(at<unsigned char>(0x72c)==2){set_action_and_finalize(700);at<short>(0x4a8)=3;at<short>(0x4ac)=3;return;}set_action_and_finalize(0);if(at<int>(0x6b8)>0)set_action_and_finalize(1);}
        if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)ground_face();
        if(entry(1)){at<float>(0xf8)=vy;at<float>(0xf4)=vx;at<float>(0x100)=0.75f;}
    }
    __forceinline void decelerate(double amount,bool clear) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-amount);
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=0.0f;if(clear)at<unsigned char>(0x47e)=0;}
    }
    __forceinline void packet848(float mode) {
        float p[3]={0.0f,0.0f,mode};spawn(848,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void interval_clear() {
        if(at<int>(0x180) && ++at<short>(0x730)>5){at<int>(0x180)=0;at<short>(0x730)=0;}
    }
    __forceinline void aim800(float low,float high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));float dy=peer()->at<float>(0xf0)-at<float>(0xf0);at<float>(0x744)=-remilia_atan(dy,dx);
        if(at<float>(0x744)<low)at<float>(0x744)=low;if(at<float>(0x744)>high)at<float>(0x744)=high;
    }
    __forceinline void charge(int xoff,double y) {
        int direction=at<unsigned char>(0x104);float yy=static_cast<float>(at<float>(0xf0)+y);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(62,x,yy,direction,1);next_sequence_block();
    }
    __forceinline void fan800(int count,int random_range,double bias,double speed,int x,double y,bool float_loop) {
        float p[3];
        if(float_loop){for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(random_range)))+at<float>(0x744)-bias);p[1]=static_cast<float>(n+speed);p[2]=0.0f;spawn_offset(800,x,y,p,3);}}
        else{for(int n=0;n<count;++n){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(random_range)))+at<float>(0x744)-bias);p[1]=static_cast<float>(n+speed);p[2]=0.0f;spawn_offset(800,x,y,p,3);}}
    }
    __forceinline void shot800(float low,float high,int count,int range,double bias,double speed,int x,double y,bool air,bool float_loop) {
        at<int>(0x180)=1;aim800(low,high);counter(200,45);if(air){at<float>(0xf4)=-4.0f;at<float>(0xf8)=9.0f;at<float>(0x100)=0.65f;}phase_counter(30);dispatch_character_wave_handle(0);fan800(count,range,bias,speed,x,y,float_loop);
    }
    __forceinline void air800(float low,float high,int x,double y) {
        if(sequence_index_13e==2)landing();if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;at<float>(0xf8)-=at<float>(0x100);
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);at<unsigned char>(0x47f)=0;at<float>(0xf0)=remilia_surface(this);zero_motion();return;}
        if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)==1){charge(-22,96.0);return;}if(frame_index_140==4)shot800(low,high,6,20,10.0,15.0,x,y,true,false);}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)shot800(low,high,10,30,15.0,10.0,x,y,true,false);
    }
    __forceinline void packet801(float angle,float speed,int x,double y) {
        float p[3]={angle,speed,0.0f};spawn_offset(801,x,y,p,3);dispatch_character_wave_handle(1);
    }
    __forceinline void start801(int x,double y,float angle) {
        at<int>(0x180)=1;counter(200,60);phase_counter(50);packet801(angle,12.0f,x,y);
    }
    __forceinline void air801() {
        if(sequence_index_13e==2)landing();if(sequence_index_13e<2){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);at<float>(0xf0)=remilia_surface(this);zero_motion();return;}}
        if(sequence_index_13e<2 && !at<int>(0x6c4))at<unsigned char>(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)==1){charge(5,107.0);return;}if(frame_index_140==5)start801(36,102.0,0.0f);}if(!frame_timer_142 && frame_index_140==12)at<float>(0x100)=0.5f;}
        if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==3)start801(36,102.0,0.0f);if(!frame_timer_142 && frame_index_140==5)packet801(20.0f,12.0f,36,102.0);if(!frame_timer_142 && frame_index_140==7)packet801(-20.0f,12.0f,36,102.0);if(!frame_timer_142 && frame_index_140==10)at<float>(0x100)=0.5f;}
    }
    __forceinline void ring810() {
        float p[3];p[2]=0.0f;p[1]=30.0f;
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(25)))+n*45.0);int layer=static_cast<unsigned char>(2*(remilia_sine(p[0])>=0.0)-1);spawn(810,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),layer,p,3);}
    }
    __forceinline void packet811(float mode) {
        float p[3]={0.0f,0.0f,mode};spawn(811,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void ring815(float speed,bool charged) {
        dispatch_character_wave_handle(11);at<int>(0x180)=1;counter(200,120);phase_counter(50);
        switch(at<signed char>(0x605)){case 0:at<float>(0x740)=charged?5.0f:3.0f;break;case 1:case 2:case 3:at<float>(0x740)=charged?6.0f:4.0f;break;case 4:at<float>(0x740)=charged?7.0f:5.0f;break;}
        float p[4];for(float n=0.0f;at<float>(0x740)>static_cast<double>(n);n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(360.0*n/at<float>(0x740));p[1]=speed;p[2]=0.0f;p[3]=static_cast<float>(n*5.0+60.0);spawn_offset(815,40,102.0,p,4);}
        p[2]=2.0f;spawn_offset(815,40,102.0,p,3);p[2]=3.0f;spawn_offset(815,40,102.0,p,3);
    }
    __forceinline void ground815(int control,float speed) {
        landing();at<unsigned char>(0x17c)=1;if(!at<int>(control))at<unsigned char>(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)){charge(0,107.0);return;}if(frame_index_140==5)ring815(speed,false);}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)ring815(speed,true);
    }
    __forceinline void ground816(int control) {
        landing();at<unsigned char>(0x17c)=5;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(sequence_index_13e==2 && (time_counter_144>=10*(at<signed char>(0x609)+1) || !at<unsigned char>(0x750))){next_sequence_block();return;}
        if(advance())set_action_and_finalize(0);if(entry(1)){float p[4]={0.0f,0.0f,0.0f,0.0f};spawn_offset(816,20,100.0,p,4);p[2]=1.0f;spawn_offset(816,20,100.0,p,4);dispatch_character_wave_handle(16);counter(200,120);phase_counter(50);}
    }
    __forceinline void fan817(double offset,bool charged) {
        at<int>(0x180)=1;counter(200,120);dispatch_character_wave_handle(20);phase_counter(50);aim800(-15.0f,0.0f);
        // Native exposes three written scalar cells but passes count four. The fourth value is not recovered.
        float p[3];for(float n=0.0f;n<(charged?6.0:static_cast<double>(at<signed char>(0x60d)+1));n=static_cast<float>(n+1.0)){
            p[0]=offset==0.0?static_cast<float>(at<float>(0x744)-n*6.0):static_cast<float>(at<float>(0x744)-n*6.0-offset);p[1]=35.0f;p[2]=0.0f;
            spawn(817,static_cast<float>((remilia_cosine(-p[0])*200.0-120.0)*facing()+at<float>(0xec)),static_cast<float>(remilia_sine(-p[0])*200.0+at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,4);
        }
    }
    __forceinline void ground817(int control,double offset) {
        landing();at<unsigned char>(0x17c)=9;if(!at<int>(control))at<unsigned char>(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==10 && at<unsigned char>(0x750)){charge(-140,160.0);return;}if(frame_index_140==12)fan817(offset,false);}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)fan817(offset,true);
    }
    __forceinline void jumping820(int control,float vx,float vy,float gravity,float mode) {
        if(!sequence_index_13e || sequence_index_13e==6)landing();at<unsigned char>(0x17c)=2;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(sequence_index_13e<6){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(6);at<float>(0xf0)=remilia_surface(this);return;}}
        if((sequence_index_13e==2 || sequence_index_13e==3) && at<signed char>(0x184)>0 && at<int>(0x180)){if(++at<short>(0x730)>=4){at<short>(0x730)=0;at<int>(0x180)=0;}}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){phase_counter(50);counter(200,120);dispatch_character_wave_handle(12);at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=gravity;float p[3]={0.0f,0.0f,mode};spawn(820,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);}
        if(entry(4))at<float>(0xf4)=static_cast<float>(at<float>(0xf4)*0.5);
    }
    __forceinline void ground821(float angle) {
        landing();at<unsigned char>(0x17c)=6;if(advance())set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){phase_counter(50);counter(200,120);at<int>(0x180)=1;float p[3]={angle,20.0f,4.0f};if(at<signed char>(0x60a)<=3)p[2]=3.0f;if(at<signed char>(0x60a)<=1)p[2]=0.0f;spawn_offset(821,110,227.0,p,3);
            p[0]=0.0f;p[1]=0.5f;p[2]=2.0f;spawn(821,static_cast<float>(80*facing()+static_cast<double>(at<float>(0xec))),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);dispatch_character_wave_handle(23);}
    }

    __forceinline void diving826(float vx) {
        if(sequence_index_13e==6)landing();
        if(sequence_index_13e==3) {
            if(!(time_counter_144%2)){float p[3]={0.0f,0.0f,3.0f};spawn(826,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),-1,p,3);}
            if(static_cast<unsigned char>(crossed())) {
                next_sequence_block();layout(8.0f);dispatch_character_wave_handle(18);at<float>(0xf0)=remilia_surface(this);
                at<float>(0xf4)=-15.0f;at<float>(0xf8)=12.5f;at<float>(0x100)=0.5f;
                float p[3]={0.0f,0.0f,0.0f};spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
                p[1]=15.0f;p[2]=1.0f;
                for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){
                    p[0]=static_cast<float>(static_cast<double>(remilia_random(30))+n*60.0+30.0);
                    if(p[0]<0.0f || p[0]>180.0f)spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
                    else spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
                }
                p[0]=0.0f;p[1]=50.0f;p[2]=6.0f;
                if(at<signed char>(0x60b)<=3){p[1]=42.5f;p[2]=4.0f;}
                if(at<signed char>(0x60b)<=1){p[1]=35.0f;p[2]=4.0f;}
                int direction=at<unsigned char>(0x104);
                spawn(826,static_cast<float>(50*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))),at<float>(0xf0),direction,1,p,3);
                direction=at<unsigned char>(0x104);
                spawn(826,static_cast<float>(50*direction+static_cast<double>(at<float>(0xec))),at<float>(0xf0),static_cast<unsigned char>(-direction),1,p,3);
            }
        }
        if(sequence_index_13e==4 || sequence_index_13e==5){
            at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.5);if(at<float>(0xf4)>0.0f)at<float>(0xf4)=0.0f;
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())){zero_motion();at<float>(0xf0)=remilia_surface(this);select_sequence(6);return;}
        }
        at<unsigned char>(0x17c)=7;if(advance())set_action_and_finalize(0);
        if(entry(1)){counter(200,120);dispatch_character_wave_handle(13);at<float>(0xf4)=vx;at<float>(0xf8)=static_cast<float>((700.0-at<float>(0xf0))*static_cast<double>(0.05f));}
        if(entry(2))zero_motion();
        if(entry(3)){float p[3]={0.0f,0.0f,2.0f};spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);at<float>(0xf8)=-50.0f;phase_counter(50);}
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        at<short>(0x48a)=40;event(23);int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):(xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>((-xoff)*static_cast<signed char>(direction))):static_cast<float>(at<float>(0xec)+static_cast<double>(xoff*static_cast<signed char>(direction))));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void hover(double height) {
        at<float>(0xf0)=static_cast<float>(remilia_surface(this)+height-at<float>(0x73c));
        if(at<float>(0x73c)!=0.0f)at<float>(0x73c)=static_cast<float>(at<float>(0x73c)*static_cast<double>(0.95f));
        if(at<float>(0x73c)<=1.0f)at<float>(0x73c)=0.0f;
    }
    __forceinline void contact_interval() {
        if(at<int>(0x180) && at<signed char>(0x184)>0 && ++at<short>(0x732)>=3){at<short>(0x732)=0;at<int>(0x180)=0;}
    }
    __forceinline void aim_unbounded() {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));
        float dy=peer()->at<float>(0xf0)-at<float>(0xf0);at<float>(0x744)=-remilia_atan(dy,dx);
    }

    __forceinline void random902(int range) {
        dispatch_character_wave_handle(58);
        float p[3];p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(remilia_random(range))*static_cast<double>(0.1f)+4.0);p[2]=0.0f;spawn_offset(902,30,90.0,p,3);
    }

    __forceinline void ring902(float *p,int count) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){
            p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(remilia_random(12))+18.0);p[2]=1.0f;
            spawn(902,static_cast<float>(remilia_cosine(static_cast<float>(180.0-p[0]))*(p[1]*60.0)*facing()+at<float>(0xec)),
                static_cast<float>(remilia_sine(static_cast<float>(180.0-p[0]))*(p[1]*60.0)+at<float>(0xf0)+100.0),
                at<unsigned char>(0x104),1,p,3);
        }
    }
    __forceinline void burst902(float *p,int count,double bias) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(remilia_random(10))+bias);p[2]=5.0f;spawn_offset(902,0,100.0,p,3);}
    }
    __forceinline void teleport902(float vx,float vy) {
        if(sequence_index_13e==1 || sequence_index_13e==2) {
            if(time_counter_144<=60){
                switch(g_match_identifier){
                case 1:if(!(time_counter_144%6))random902(60);
                case 0:if(!(time_counter_144%10))random902(40);break;
                case 2:if(!(time_counter_144%4))random902(80);break;
                case 3:if(!(time_counter_144%3))random902(100);break;
                }
            }
            if(time_counter_144>=50){if(at<unsigned char>(0x113)<10){select_sequence(3);at<unsigned char>(0x113)=255;zero_motion();return;}at<unsigned char>(0x113)-=10;}
        }
        if(sequence_index_13e==3) {
            if(time_counter_144==45){
                at<float>(0xec)=peer()->at<float>(0xec);at<float>(0xf0)=peer()->at<float>(0xf0);dispatch_character_wave_handle(59);
                float p[3];switch(g_match_identifier){case 0:ring902(p,10);break;case 1:ring902(p,10);break;case 2:ring902(p,15);break;case 3:ring902(p,20);break;}
            }
            if(time_counter_144==85) {
                dispatch_character_wave_handle(60);float p[3];
                switch(g_match_identifier){case 1:burst902(p,12,2.0);break;case 2:burst902(p,18,2.0);break;case 3:burst902(p,25,1.0);break;}
                p[0]=0.0f;p[1]=0.0f;p[2]=2.0f;
                spawn_offset(902,0,100.0,p,3);spawn_offset(902,0,100.0,p,3);spawn_offset(902,0,100.0,p,3);
                p[2]=4.0f;spawn_offset(902,0,100.0,p,3);p[2]=3.0f;
                for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(remilia_random(22))+8.0);spawn_offset(902,0,100.0,p,3);}
                select_sequence(4);return;
            }
        }
        if(advance()){if(!static_cast<unsigned char>(crossed())){set_action_and_finalize(704);at<float>(0x100)=0.3f;}else set_action_and_finalize(700);}
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=vy;}
    }

    __forceinline void spell_finish() {
        texture(2,-1);copy_health();at<int>(0x76a)=1;at<short>(0x766)=0;at<short>(0x768)=0;at<short>(0x764)=0;event(23);
    }
    __forceinline void ring903(float *p,int count,double step) {
        float angle=static_cast<float>(remilia_random(360));
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*step+angle);p[1]=0.0f;p[2]=0.0f;spawn_offset(903,0,230.0,p,3);}
    }
    __forceinline void burst903(float *p,int count,double bias) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(remilia_random(40))*static_cast<double>(0.1f)+bias);p[2]=3.0f;spawn_offset(903,0,230.0,p,3);}
    }
};
}
