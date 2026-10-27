#pragma once
#include <math.h>
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class TenshiActionStateView;
unsigned __cdecl tenshi_random(int);
unsigned __cdecl tenshi_random_u32();
float __cdecl tenshi_atan(float,float);
double __cdecl tenshi_sine(float);
double __cdecl tenshi_cosine(float);
float __cdecl tenshi_square(float);
float __fastcall tenshi_surface(TenshiActionStateView *);
unsigned char __fastcall tenshi_on_surface(TenshiActionStateView *);
void __cdecl tenshi_bgm_volume(int,int);
void __cdecl tenshi_fade_in(unsigned,int);
void __cdecl tenshi_fade_out(unsigned,int);
void __cdecl tenshi_play_bgm(const char *);
extern int g_match_identifier;
extern int g_fighter_state_4b8_default;
extern short g_tenshi_weather_counter;
extern unsigned char g_tenshi_weather_selector;
double __cdecl tenshi_sine_radians(float);
struct TenshiCardDeque { short *at(unsigned); };
struct TenshiEvent130 {
    int trigger(int);
    void *pair(float,float);
    void music(int,int);
    void pair_mode(int,unsigned char);
};
struct TenshiActionScratch { void reset(); };
// Pointer-only receiver view, not a recovered complete Fighter allocation.
// Declaration-only helpers describe this caller; no callee implementation credit.
class TenshiActionStateView : public AnimationSequenceObjectView {
public:
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    unsigned char advance();
    void zero_motion();
    void event(unsigned);
    void layout(float);
    void effect(int,float,float,int,int);
    int spawn(int,float,float,int,int,const void *,int);
    void counter(short,int);
    int phase_counter(int);
    void flip();
    unsigned char directional(int);
    void texture(signed char,short);
    void finalize(int);
    void copy_health();
    void sequence_window(signed char,int,int);
    void secondary_cycle();
    void common_update();
    void transition(float);
    signed char shared_first(signed char,float);
    signed char shared_second(signed char,float);


    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        float y=static_cast<float>(static_cast<double>(tenshi_random_u32()%200u)+at<float>(0xf0));
        float x=static_cast<float>(base-static_cast<double>(tenshi_random_u32()%100u));
        effect(124,x,y,direction,1);
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
    __forceinline void ground_face() {
        if(peer()->at<float>(0xec)<static_cast<double>(at<float>(0xec))) at<unsigned char>(0x104)=255;
        if(peer()->at<float>(0xec)>static_cast<double>(at<float>(0xec))) at<unsigned char>(0x104)=1;
    }
    __forceinline void recover_air_sequence() {
        at<float>(0xf0)=tenshi_surface(this);zero_motion();select_sequence(2);
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<TenshiActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void jump_cycle(float vx,float vy,float gravity) {
        if(sequence_index_13e==0) landing();
        if(crossed()) {set_action_and_finalize(10);at<float>(0xf0)=tenshi_surface(this);zero_motion();return;}
        if(tenshi_on_surface(this) || at<float>(0xf8)>0.0f) at<short>(0x4ae)=2;
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(at<float>(0xf8)<-20.0f) at<float>(0xf8)=-20.0f;
        }
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f) select_sequence(2);
        advance();
        if(entry(1)) {
            at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=gravity;
            at<unsigned char>(0x47e)=0;
            effect(63,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1);
        }
    }


    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));
        float dy=peer()->at<float>(0xf0)-at<float>(0xf0);
        at<float>(0x744)=-tenshi_atan(dy,dx);
        if(at<float>(0x744)<low)at<float>(0x744)=low;
        if(at<float>(0x744)>high)at<float>(0x744)=high;
    }
    __forceinline void air_800(float low,float high) {
        if(sequence_index_13e==2)landing();
        if(sequence_index_13e<2 && !at<int>(0x6c0))at<unsigned char>(0x750)=0;
        at<float>(0xf8)-=at<float>(0x100);
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);at<unsigned char>(0x47f)=0;
            at<float>(0xf0)=tenshi_surface(this);zero_motion();return;
        }
        if(advance())set_action_and_finalize(0);
        if(time_counter_144==0 && ((!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) ||
                                  (!frame_timer_142 && !frame_index_140 && sequence_index_13e==2))) {
            set_action_and_finalize(9);return;
        }
        if(sequence_index_13e==0 && !frame_timer_142) {
            if(frame_index_140==6) {
                at<int>(0x180)=1;aim(low,high);
                float p[3]={at<float>(0x744),17.5f,4.0f};
                int direction=at<unsigned char>(0x104);
                float y=static_cast<float>(at<float>(0xf0)+115.0);
                float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
                spawn(800,x,y,direction,1,p,3);
                dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
            }
            if(!frame_timer_142 && frame_index_140==15)at<float>(0x100)=0.5f;
        }
    }
    __forceinline void ring_801(double height) {
        // Fourth live packet slot retains the angle across exposed payload calls.
        float p[4];
        for(float n=0.0f;n<10.0f;n=static_cast<float>(n+1.0)) {
            p[3]=static_cast<float>(n*36.0+18.0);
            p[0]=static_cast<float>(p[3]+90.0);p[1]=15.0f;p[2]=0.0f;
            int direction=at<unsigned char>(0x104);
            float y=static_cast<float>(tenshi_sine(-p[3])*80.0+at<float>(0xf0)+height);
            float x=static_cast<float>(tenshi_cosine(-p[3])*80.0*facing()+at<float>(0xec));
            spawn(801,x,y,direction,1,p,3);
            p[2]=2.0f;direction=at<unsigned char>(0x104);
            y=static_cast<float>(tenshi_sine(-p[3])*80.0+at<float>(0xf0)+height);
            x=static_cast<float>(tenshi_cosine(-p[3])*80.0*facing()+at<float>(0xec));
            spawn(801,x,y,direction,1,p,3);
        }
    }
    __forceinline void air_801() {
        if(sequence_index_13e==4)landing();
        if((sequence_index_13e==1 && time_counter_144>=16) ||
           (sequence_index_13e==2 && time_counter_144>=20)) {next_sequence_block();return;}
        if(sequence_index_13e==2 || sequence_index_13e==3) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                select_sequence(4);at<float>(0xf0)=tenshi_surface(this);zero_motion();return;
            }
        }
        if(advance())set_action_and_finalize(0);
        if(entry(4)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
            at<int>(0x180)=1;float p[3]={-10.0f,20.0f,4.0f};
            int direction=at<unsigned char>(0x104);
            float y=static_cast<float>(at<float>(0xf0)+115.0);
            float x=static_cast<float>(70*facing()+static_cast<double>(at<float>(0xec)));
            spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)at<float>(0x100)=0.5f;
    }


    __forceinline void pair_821() {
        float p[3]={0.0f,1.0f,1.0f};
        spawn(821,at<float>(0xec),static_cast<float>(at<float>(0xf0)+200.0),at<unsigned char>(0x104),1,p,3);
        p[1]=-1.0f;p[2]=1.0f;
        spawn(821,at<float>(0xec),static_cast<float>(at<float>(0xf0)-100.0),at<unsigned char>(0x104),1,p,3);
        counter(200,120);phase_counter(50);
    }
    __forceinline void air_pair821(unsigned control,int minimum,int maximum) {
        if(sequence_index_13e==4)landing();
        at<unsigned char>(0x17c)=6;
        if(!at<int>(control))at<unsigned char>(0x750)=0;
        at<float>(0xf8)-=at<float>(0x100);
        if(sequence_index_13e==3 && frame_index_140>=2 && static_cast<unsigned char>(crossed())) {
            zero_motion();at<float>(0xf0)=tenshi_surface(this);next_sequence_block();return;
        }
        if(advance())set_action_and_finalize(0);
        if(entry(4))set_action_and_finalize(9);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
        if(sequence_index_13e==1 && time_counter_144>=minimum &&
           (time_counter_144>=maximum || !at<unsigned char>(0x750))) {
            at<int>(0x180)=1;next_sequence_block();return;
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)at<float>(0x100)=0.5f;
    }
    __forceinline void burst848(int offset,float mode) {
        float p[3];p[1]=20.0f;p[2]=mode;
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<double>(tenshi_random(30))+n*45.0);
            if(p[0]<0.0f || p[0]>180.0f) {
                int direction=at<unsigned char>(0x104);
                float y=at<float>(0xf0);
                float x=static_cast<float>(offset*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
                spawn(848,x,y,direction,-1,p,3);
            } else {
                int direction=at<unsigned char>(0x104);
                float y=at<float>(0xf0);
                float x=static_cast<float>(offset*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
                spawn(848,x,y,direction,1,p,3);
            }
        }
    }
    __forceinline void dash825() {
        float p[3];
        p[0]=static_cast<float>(tenshi_random(360));
        p[1]=static_cast<float>(tenshi_random(6));p[2]=0.0f;
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+112.0);
        float x=static_cast<float>(36*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        spawn(825,x,y,direction,-1,p,3);
    }
    __forceinline void dash_burst_tail() {
        if(sequence_index_13e==2 && !frame_timer_142) {
            if(frame_index_140==1)dispatch_character_wave_handle(14);
            if(!frame_timer_142 && frame_index_140==2 && at<signed char>(0x607)>=4)burst848(150,3.0f);
        }
    }


    __forceinline void spell_flash(int xoff,double yoff,int outcome) {
        at<short>(0x48a)=40;event(23);
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+yoff);
        float x=xoff==0?at<float>(0xec):(xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void burst_payload(float *p,float count,double step,int xoff,double yoff,bool surface,int object) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<double>(tenshi_random(30))+n*step);
            if(p[0]<0.0f || p[0]>180.0f) {
                int direction=at<unsigned char>(0x104);
                float y=surface?tenshi_surface(this):(yoff==0.0?at<float>(0xf0):static_cast<float>(at<float>(0xf0)+yoff));
                float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*facing()+static_cast<double>(at<float>(0xec)));
                spawn(object,x,y,direction,-1,p,3);
            } else {
                int direction=at<unsigned char>(0x104);
                float y=surface?tenshi_surface(this):(yoff==0.0?at<float>(0xf0):static_cast<float>(at<float>(0xf0)+yoff));
                float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*facing()+static_cast<double>(at<float>(0xec)));
                spawn(object,x,y,direction,1,p,3);
            }
        }
    }
    __forceinline void effect127_pair() {
        effect(127,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1);
        effect(127,at<float>(0xec),at<float>(0xf0),static_cast<unsigned char>(-at<unsigned char>(0x104)),-1);
    }

    template<class T> __forceinline T &at(unsigned o) {
        return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+o);
    }
    __forceinline TenshiActionStateView *peer() {
        return static_cast<TenshiActionStateView *>(related_170);
    }
    __forceinline short card() {
        return *reinterpret_cast<TenshiCardDeque *>(reinterpret_cast<unsigned char *>(this)+0x55c)->at(0);
    }
    __forceinline TenshiEvent130 *event_owner() {
        return reinterpret_cast<TenshiEvent130 *>(reinterpret_cast<unsigned char *>(this)+0x130);
    }
    __forceinline int facing() { return static_cast<signed char>(at<unsigned char>(0x104)); }
    __forceinline bool entry(short seq) {
        return time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==seq;
    }
};
}
