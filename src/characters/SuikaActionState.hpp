#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class SuikaActionStateView;
extern int g_match_identifier;
unsigned __cdecl suika_random(int);
unsigned __cdecl suika_random_u32();
float __cdecl suika_atan(float,float);
float __cdecl suika_square(float);
float __cdecl suika_sine_int(int);
float __cdecl suika_absolute(float);
double __cdecl suika_sine(float);
double __cdecl suika_cosine(float);
float __fastcall suika_surface(SuikaActionStateView *);
unsigned char __fastcall suika_on_surface(SuikaActionStateView *);
struct SuikaActionScratch { void reset(); void oriented_components(float,float); };
// Pointer-only extension, not a complete owner layout.
// Declaration-only caller interfaces do not confer callee implementation credit.
class SuikaActionStateView : public AnimationSequenceObjectView {
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
    void consume_steps(signed char);
    void set_counter_48a(short);
    signed char shared_first(signed char,float);
    signed char shared_second(signed char,float);
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
    __forceinline SuikaActionStateView *peer() { return static_cast<SuikaActionStateView *>(related_170); }
    __forceinline SuikaActionStateView *owner() { return at<SuikaActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<SuikaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,
            static_cast<float>(base-static_cast<float>(suika_random_u32()%100u)),
            static_cast<float>(static_cast<float>(suika_random_u32()%200u)+at<float>(0xf0)),
            direction,1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=ahead?static_cast<float>(80*facing()+static_cast<double>(at<float>(0xec))):at<float>(0xec);
        effect(125,x,y,direction,1);
        effect(126,at<float>(0xec),static_cast<float>(at<float>(0xf0)+height),
               reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104),1);
        event(31);
    }
    __forceinline void high_jump(float vx,float vy,float gravity) {
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);at<float>(0xf0)=suika_surface(this);zero_motion();return;
        }
        if(suika_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
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
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count,int layer=1) {
        int direction=at<unsigned char>(0x104);
        float y=height==0.0?at<float>(0xf0):height<0.0?static_cast<float>(at<float>(0xf0)-(-height)):static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-(-xoff*static_cast<signed char>(direction))):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        spawn(object,x,y,direction,layer,p,count);
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
                set_action_and_finalize(10);at<float>(0xf0)=suika_surface(this);zero_motion();return;
            }
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=16.0f;at<float>(0x100)=0.75f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline void aim_short(short low,short high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        at<short>(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(suika_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx))));
        if(at<short>(0x734)<low)at<short>(0x734)=low;
        if(at<short>(0x734)>high)at<short>(0x734)=high;
    }
    __forceinline void aim_float(float minimum,float maximum) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        at<float>(0x744)=-suika_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);
        if(at<float>(0x744)<minimum)at<float>(0x744)=minimum;
        if(at<float>(0x744)>maximum)at<float>(0x744)=maximum;
    }
    __forceinline void release_fragments811() {
        at<short>(0x732)=1;float p[3];p[2]=1.0f;float n=0.0f;
        do {
            p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));
            p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
            at<short>(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;
            spawn_offset(811,40,0.0,p,3,at<unsigned char>(0x730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
    }
    __forceinline void impact_fragments811() {
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(811,40,0.0,p,3);
        p[2]=2.0f;spawn_offset(811,40,0.0,p,3,255);p[2]=1.0f;float n=0.0f;
        do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
           at<short>(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(811,40,0.0,p,3,at<unsigned char>(0x730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
    }
    __forceinline void mist817() {
        float p[3];p[0]=static_cast<float>(suika_random(360));p[1]=static_cast<float>(static_cast<float>(suika_random(5))+5.0);p[2]=5.0f;
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(static_cast<double>(static_cast<float>(suika_random(60)))+at<float>(0xf0)+30.0);
        float x=static_cast<float>(static_cast<double>(static_cast<float>(suika_random(60)))+at<float>(0xec)-30.0);
        spawn(817,x,y,direction,1,p,3);
    }
    __forceinline void steer_cloud(double rate) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+facing()*(at<int>(0x6b4)*rate));
        at<float>(0xf8)=static_cast<float>(at<float>(0xf8)-at<int>(0x6b8)*rate);
        if(at<float>(0xf4)>10.0f)at<float>(0xf4)=10.0f;if(at<float>(0xf4)<-10.0f)at<float>(0xf4)=-10.0f;
        if(at<float>(0xf8)>10.0f)at<float>(0xf8)=10.0f;if(at<float>(0xf8)<-10.0f)at<float>(0xf8)=-10.0f;
    }
    __forceinline void shot808_burst(bool air,bool phase) {
        if(at<short>(0x730)>0 && (sequence_index_13e==2 || sequence_index_13e==3)){
            if(at<short>(0x730)%4==1){
                if(phase)phase_counter(10);
                at<int>(0x180)=1;aim_short(-10,10);dispatch_character_wave_handle(9);
                if(!air)effect(129,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1);
                if(air?at<short>(0x738)==1:at<unsigned char>(0x750)==1){
                    double base=at<short>(0x734)+30.0;
                    float p[3];p[0]=static_cast<float>(base-static_cast<float>(suika_random_u32()%60u));p[1]=15.0f;p[2]=static_cast<float>(suika_random(4));
                    spawn_offset(808,44,85.0,p,3);
                }else{
                    double base=at<short>(0x734)+30.0;
                    float p[3];p[0]=static_cast<float>(base-static_cast<float>(suika_random_u32()%60u));p[1]=15.0f;p[2]=static_cast<float>(suika_random(4));
                    spawn_offset(808,44,85.0,p,3);
                }
            }
            ++at<short>(0x730);
        }
    }
    __forceinline void spell_flash(int xoff,double height,int window) {
        set_counter_48a(40);event(23);
        effect(115,xoff<0?static_cast<float>(at<float>(0xec)-(-xoff*facing())):xoff?static_cast<float>(xoff*facing()+static_cast<double>(at<float>(0xec))):at<float>(0xec),static_cast<float>(at<float>(0xf0)+height),at<unsigned char>(0x104),1);
        sequence_window(0,window,60);secondary_cycle();
    }
    __forceinline void sync_grab_peer() {
        peer()->at<float>(0xec)=static_cast<float>(facing()*(at<float>(0xf4)+45.0)+at<float>(0xec));
        peer()->at<float>(0xf0)=static_cast<float>(at<float>(0xf0)+120.0+at<float>(0xf8));
    }
    __forceinline void pose_grab_peer(float rotation,int xoff,double height) {
        peer()->at<float>(0x12c)=rotation;
        peer()->at<float>(0xec)=xoff<0?static_cast<float>(at<float>(0xec)-(-xoff*facing())):static_cast<float>(xoff*facing()+at<float>(0xec));
        peer()->at<float>(0xf0)=static_cast<float>(at<float>(0xf0)+height);
    }
    __forceinline void ending_smoke999() {
        float p[3];p[0]=static_cast<float>(suika_random(360));
        p[1]=static_cast<float>(static_cast<float>(static_cast<float>(suika_random(50))*static_cast<double>(0.1f))+6.0);p[2]=1.0f;
        spawn_offset(999,0,100.0,p,3);
    }
    __forceinline void ending_fragments811() {
        float p[3];float n=0.0f;
        do{p[0]=static_cast<float>((n*36.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);p[2]=1.0f;
            at<short>(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(811,40,0.0,p,3,at<unsigned char>(0x730));n=static_cast<float>(n+1.0);
        }while(n<10.0f);
    }
    __forceinline void burst999() {
        float n=0.0f;float p[3];
        do{p[0]=static_cast<float>((n*45.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(13))+12.0);p[2]=0.0f;spawn_offset(999,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);
    }
    __forceinline void orbit_particle930() {
        float p[3];p[0]=static_cast<float>(suika_random(360));p[1]=static_cast<float>(suika_random(120));p[2]=1.0f;
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(suika_sine(-p[0])*p[1]+at<float>(0xf0));
        float x=static_cast<float>(suika_cosine(-p[0])*p[1]+at<float>(0xec));spawn(930,x,y,direction,1,p,3);
    }
    __forceinline void shot_particle930() {
        float p[3];p[0]=static_cast<float>(suika_random(360));p[1]=0.0f;p[2]=4.0f;float radius=static_cast<float>(suika_random(120));
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(suika_sine(-p[0])*radius+at<float>(0xf0));
        float x=static_cast<float>(suika_cosine(-p[0])*radius+at<float>(0xec));spawn(930,x,y,direction,1,p,3);
    }
    __forceinline void moving_grab_pose(float rotation,double xoff,double height) {
        peer()->at<float>(0x12c)=rotation;
        peer()->at<float>(0xec)=static_cast<float>(facing()*(at<float>(0xf4)+xoff)+at<float>(0xec));
        peer()->at<float>(0xf0)=static_cast<float>((at<float>(0xf0)+height)+at<float>(0xf8));
    }
    __forceinline void moving_grab_vertical() {
        peer()->at<float>(0x12c)=0.0f;
        peer()->at<float>(0xec)=static_cast<float>(facing()*at<float>(0xf4)*(-30.0)+at<float>(0xec));
        peer()->at<float>(0xf0)=static_cast<float>(at<float>(0xf0)+110.0+at<float>(0xf8));
        peer()->set_action_and_finalize(107);
    }
    __forceinline void grab_impact_effect(int object,int xoff) {
        effect(object,static_cast<float>(xoff*facing()+at<float>(0xec)),static_cast<float>(at<float>(0xf0)+10.0),at<unsigned char>(0x104),1);
    }
    __forceinline bool above_stage_margin() {
        double y=at<float>(0xf0);return y>=static_cast<double>(suika_surface(this))+10.0;
    }
    __forceinline bool button_active(unsigned counter,unsigned button,unsigned edge) {
        return (at<unsigned>(counter)>0 && at<unsigned>(counter)<3) || at<int>(button)==2 || at<unsigned>(edge)>0;
    }
    __forceinline void giant_ring855(float *p,float count,double spacing,float speed,int xoff) {
        float n=0.0f;
        do{p[0]=static_cast<float>((n*spacing-20.0)+static_cast<float>(suika_random(40)));p[1]=speed;p[2]=2.0f;
            at<short>(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(855,xoff,0.0,p,3,at<unsigned char>(0x730));n=static_cast<float>(n+1.0);
        }while(n<count);
    }
    __forceinline void giant_ring920(int object,float *p,float count,double spacing,float speed,int xoff) {
        float n=0.0f;
        do{p[0]=static_cast<float>((n*spacing-20.0)+static_cast<float>(suika_random(40)));p[1]=speed;p[2]=2.0f;
            at<short>(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(object,xoff,0.0,p,3,at<unsigned char>(0x730));n=static_cast<float>(n+1.0);
        }while(n<count);
    }
    __forceinline void update_oriented_velocity() {
        reinterpret_cast<SuikaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->oriented_components(at<float>(0x744),at<float>(0x740));
    }
};
}
