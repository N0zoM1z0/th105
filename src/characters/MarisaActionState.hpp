#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class MarisaActionStateView;
extern int g_match_identifier;
unsigned __cdecl marisa_random(int);
unsigned __cdecl marisa_random_u32();
float __cdecl marisa_atan(float,float);
float __cdecl marisa_square(float);
double __cdecl marisa_sine(float);
double __cdecl marisa_cosine(float);
float __fastcall marisa_surface(MarisaActionStateView *);
unsigned char __fastcall marisa_on_surface(MarisaActionStateView *);
struct MarisaActionScratch { void reset(); };
// Pointer-only extension, not a complete owner layout.
// Declaration-only caller interfaces do not confer callee implementation credit.
class MarisaActionStateView : public AnimationSequenceObjectView {
public:
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    signed char classify_fighter_x_boundary();
    unsigned char advance();
    void zero_motion();
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
    __forceinline MarisaActionStateView *peer() { return static_cast<MarisaActionStateView *>(related_170); }
    __forceinline MarisaActionStateView *owner() { return at<MarisaActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<MarisaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,
            static_cast<float>(base-static_cast<float>(marisa_random_u32()%100u)),
            static_cast<float>(static_cast<float>(marisa_random_u32()%200u)+at<float>(0xf0)),
            direction,1);
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
            set_action_and_finalize(10);at<float>(0xf0)=marisa_surface(this);zero_motion();return;
        }
        if(marisa_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
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
    __forceinline void decelerate(double step,bool clear) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-step);
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=0.0f;if(clear)at<unsigned char>(0x47e)=0;}
    }
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
        int direction=at<unsigned char>(0x104);
        float y=height==0.0?at<float>(0xf0):height<0.0?static_cast<float>(at<float>(0xf0)-(-height)):static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline void orbit901(float *p,double spacing,float count) {
        float n=0.0f;do{p[0]=static_cast<float>(spacing*n);p[1]=0.0f;p[2]=n;spawn_offset(901,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<count);
    }
    __forceinline void wind_action() {
        landing();
        if(sequence_index_13e==1){
            switch(g_match_identifier){
            case 0:at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+0.5);if(at<float>(0x73c)>4.0f)at<float>(0x73c)=4.0f;if(time_counter_144>59){next_sequence_block();return;}break;
            case 1:at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+0.5);if(at<float>(0x73c)>6.0f)at<float>(0x73c)=6.0f;if(time_counter_144>89){next_sequence_block();return;}break;
            case 2:at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+0.5);if(at<float>(0x73c)>7.0)at<float>(0x73c)=7.0f;if(time_counter_144>89){next_sequence_block();return;}break;
            case 3:at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+0.5);if(at<float>(0x73c)>8.0f)at<float>(0x73c)=8.0f;if(time_counter_144>89){next_sequence_block();return;}break;
            }
        }else{at<float>(0x73c)=static_cast<float>(at<float>(0x73c)-0.5);if(at<float>(0x73c)<0.0f)at<float>(0x73c)=0.0f;}
        if(sequence_index_13e==2 && time_counter_144>59){next_sequence_block();return;}
        at<float>(0x6ac)=-at<float>(0x73c);
        if((at<float>(0xec)<peer()->at<float>(0xec) && peer()->at<signed char>(0x104)==1) || (peer()->at<float>(0xec)<at<float>(0xec) && peer()->at<signed char>(0x104)==-1))at<float>(0x6ac)=at<float>(0x73c);
        if(advance())set_action_and_finalize(700);if(entry(1))spawn_offset(990,-80,130.0,0,0);
    }
    __forceinline void ending_slide(int action,float x) {
        if(!sequence_index_13e){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();at<float>(0xf0)=marisa_surface(this);at<float>(0xf8)=0.0f;return;}}
        if(sequence_index_13e==1){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-0.75);if(at<float>(0xf4)<=0.0f){at<float>(0xf4)=0.0f;++at<short>(0x730);if(at<short>(0x730)>1){next_sequence_block();at<float>(0xf4)=-5.0f;at<float>(0xf8)=5.0f;}}}
        if(sequence_index_13e==2 || sequence_index_13e==3){at<float>(0xf8)=static_cast<float>(at<float>(0xf8)-0.25);if(static_cast<unsigned char>(crossed())){zero_motion();at<float>(0xf0)=marisa_surface(this);select_sequence(4);event(30);at<float>(0xec)=x;return;}}
        if(advance())set_action_and_finalize(action);
    }
    __forceinline void aimed900(int xoff,double height) {
        flip();float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        float p[3];p[0]=marisa_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);p[0]=-p[0];at<float>(0x744)=p[0];p[1]=15.0f;p[2]=static_cast<float>(marisa_random(4));
        spawn_offset(900,xoff,height,p,3);p[2]=4.0f;spawn_offset(900,xoff,height,p,3);dispatch_character_wave_handle(0);
    }
    __forceinline void spell_flash(int xoff,double height,int window) {
        at<short>(0x48a)=40;event(23);
        effect(115,static_cast<float>(xoff<0?at<float>(0xec)-static_cast<double>(-xoff*facing()):xoff*facing()+static_cast<double>(at<float>(0xec))),static_cast<float>(at<float>(0xf0)+height),at<unsigned char>(0x104),1);
        sequence_window(0,window,60);secondary_cycle();
    }
    __forceinline void shot827_volley(float *p,bool air,double spread) {
        spawn_offset(827,44,85.0,p,3);
        float n=0.0f;
        do{p[1]=static_cast<float>(n*5.0+spread);p[2]=6.0f;if(at<signed char>(0x60f)<4)p[2]=0.0f;spawn_offset(827,air?48:44,air?104.0:85.0,p,3);n=static_cast<float>(n+1.0);}while(n<3.0f);
        n=0.0f;
        do{p[1]=static_cast<float>(-n*5.0-spread);p[2]=6.0f;if(at<signed char>(0x60f)<4)p[2]=0.0f;spawn_offset(827,air?48:44,air?104.0:85.0,p,3);n=static_cast<float>(n+1.0);}while(n<3.0f);
    }
    __forceinline void shot827_action(bool air,bool alternate) {
        if(!air || sequence_index_13e==5)landing();at<unsigned char>(0x17c)=11;
        if(air){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){select_sequence(5);at<unsigned char>(0x47f)=0;at<float>(0xf0)=marisa_surface(this);zero_motion();return;}}
        if(sequence_index_13e<2 && !at<int>(0x6c4))at<unsigned char>(0x750)=0;
        if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
            phase_counter(50);at<int>(0x180)=1;dispatch_character_wave_handle(34);counter(200,60);
            float p[3]={alternate?45.0f:30.0f,0.0f,4.0f};
            if(at<short>(0x738)==1)shot827_volley(p,air,alternate?20.0:10.0);
            else shot827_volley(p,air,alternate?20.0:10.0);
        }
        if(advance())set_action_and_finalize(0);if(air && entry(5)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==1 && time_counter_144>2)next_sequence_block();
        if(sequence_index_13e==3 && time_counter_144>(alternate?20:10))next_sequence_block();
        if(air && sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)at<float>(0x100)=0.6f;
    }
    __forceinline void shot826_action(bool air,bool alternate) {
        if(!air || sequence_index_13e==5)landing();at<unsigned char>(0x17c)=7;
        if(air){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){select_sequence(5);at<unsigned char>(0x47f)=0;at<float>(0xf0)=marisa_surface(this);zero_motion();return;}}
        if(sequence_index_13e<2 && !at<int>(alternate?0x6c4:0x6c0))at<unsigned char>(0x750)=0;
        if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
            if(!air){phase_counter(50);at<int>(0x180)=1;dispatch_character_wave_handle(29);}
            aim_short(-10,10);
            if(air){dispatch_character_wave_handle(29);at<int>(0x180)=1;}else dispatch_character_wave_handle(4);
            counter(200,60);if(air)phase_counter(50);
            float p[3]={0.0f,0.0f,0.0f};if(at<signed char>(0x60b)>3)p[2]=6.0f;
            if(at<short>(0x738)==1)spawn_offset(826,air?48:44,air?104.0:85.0,p,3);
            else spawn_offset(826,air?48:44,air?104.0:85.0,p,3);
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(826,air?-48:-24,air?104.0:95.0,p,3);}
        if(air && entry(5)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==1 && time_counter_144>10 && (!at<unsigned char>(0x750) || time_counter_144>25))next_sequence_block();
        if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
        if(air && sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)at<float>(0x100)=0.6f;
    }
    __forceinline void shot825_action(bool air,bool alternate) {
        if(!air || sequence_index_13e==5)landing();
        at<unsigned char>(0x17c)=3;
        if(air){
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){select_sequence(5);at<unsigned char>(0x47f)=0;at<float>(0xf0)=marisa_surface(this);zero_motion();return;}
        }
        if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<10)) && !at<int>(alternate?0x6c4:0x6c0))at<unsigned char>(0x750)=0;
        shot825_burst(air,air||alternate);
        if(advance())set_action_and_finalize(0);
        if(air && entry(5)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==1){
            if(time_counter_144>3 && time_counter_144<11){
                if(!at<unsigned char>(0x750)){next_sequence_block();return;}
                if(time_counter_144==10)effect(62,static_cast<float>(at<float>(0xec)-23*facing()),static_cast<float>(at<float>(0xf0)+(air?107.0:95.0)),at<unsigned char>(0x104),1);
            }
            if(time_counter_144>24){next_sequence_block();return;}
        }
        if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(825,air?-23:-24,air?107.0:95.0,p,3);}
        if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){at<short>(0x730)=1;counter(200,120);if(!air && !alternate)phase_counter(50);}
        if(sequence_index_13e==3 && ((time_counter_144>10 && !at<unsigned char>(0x750)) || time_counter_144>25)){
            next_sequence_block();if(!air)return;
        }
        if(air && sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)at<float>(0x100)=0.6f;
    }
    __forceinline void shot825_burst(bool air,bool phase) {
        if(at<short>(0x730)>0 && (sequence_index_13e==2 || sequence_index_13e==3)){
            if(at<short>(0x730)%4==1){
                if(phase)phase_counter(10);
                at<int>(0x180)=1;aim_short(-10,10);dispatch_character_wave_handle(9);
                if(!air)effect(129,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1);
                if(air?at<short>(0x738)==1:at<unsigned char>(0x750)==1){
                    double base=at<short>(0x734)+30.0;
                    float p[3];p[0]=static_cast<float>(base-static_cast<float>(marisa_random_u32()%60u));p[1]=15.0f;p[2]=static_cast<float>(marisa_random(4));
                    spawn_offset(825,44,85.0,p,3);
                }else{
                    double base=at<short>(0x734)+30.0;
                    float p[3];p[0]=static_cast<float>(base-static_cast<float>(marisa_random_u32()%60u));p[1]=15.0f;p[2]=static_cast<float>(marisa_random(4));
                    spawn_offset(825,44,85.0,p,3);
                }
            }
            ++at<short>(0x730);
        }
    }
    __forceinline void rising_trail() {
        float p[3];p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+95.0-30.0);
        float speed=static_cast<float>(static_cast<double>(marisa_random(100))*static_cast<double>(0.1f));
        p[1]=static_cast<float>(speed+10.0);p[2]=static_cast<float>(marisa_random_u32()&3u);
        spawn_offset(810,40,51.0,p,3);
    }
    __forceinline void aim_short(short low,short high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        at<short>(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(marisa_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx))));
        if(at<short>(0x734)<low)at<short>(0x734)=low;
        if(at<short>(0x734)>high)at<short>(0x734)=high;
    }
    __forceinline void shot800_fan(int xoff,double height,int angle_step=-10) {
        if(at<short>(0x730)>0){
            ++at<short>(0x730);
            if(!at<unsigned char>(0x750)){
                if(at<short>(0x730)%3!=1 || at<short>(0x732)>=3)return;
                at<int>(0x180)=1;phase_counter(10);
                float p[3]={static_cast<float>(at<short>(0x734)+angle_step*at<short>(0x732)),2.0f,0.0f};
                spawn_offset(800,xoff,height,p,3);
            }else{
                if(at<short>(0x730)%3!=1 || at<short>(0x732)>=5)return;
                at<int>(0x180)=1;phase_counter(10);
                float p[3]={static_cast<float>(at<short>(0x734)+angle_step*at<short>(0x732)),2.0f,0.0f};
                spawn_offset(800,xoff,height,p,3);
            }
            dispatch_character_wave_handle(0);++at<short>(0x732);
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
    __forceinline void normal_jump(float vx) {
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !at<unsigned char>(0x47e))zero_motion();
        }
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);at<float>(0xf0)=marisa_surface(this);zero_motion();return;
            }
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=16.0f;at<float>(0x100)=0.75f;at<unsigned char>(0x47e)=0;}
    }
};
}
