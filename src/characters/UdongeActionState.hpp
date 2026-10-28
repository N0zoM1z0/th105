#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class UdongeActionStateView;
extern int g_match_identifier;
unsigned __cdecl udonge_random(int);
unsigned __cdecl udonge_random_u32();
float __cdecl udonge_atan(float,float);
float __cdecl udonge_tangent(float);
double __cdecl udonge_sine(float);
double __cdecl udonge_cosine(float);
float __fastcall udonge_surface(UdongeActionStateView *);
unsigned char __fastcall udonge_on_surface(UdongeActionStateView *);
struct UdongeActionScratch { void reset(); };
// Pointer-only extension, not a complete owner layout or callee implementation.
class UdongeActionStateView : public AnimationSequenceObjectView {
public:
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
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
    __forceinline UdongeActionStateView *peer() { return static_cast<UdongeActionStateView *>(related_170); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<UdongeActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count,int layer=1) {
        int direction=at<unsigned char>(0x104);
        float y=height==0.0?at<float>(0xf0):height<0.0?static_cast<float>(at<float>(0xf0)-(-height)):static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-(-xoff*static_cast<signed char>(direction))):static_cast<float>(xoff*static_cast<signed char>(direction)+at<float>(0xec));
        spawn(object,x,y,direction,layer,p,count);
    }
    __forceinline void idle_motion() {
        if(!at<unsigned char>(0x47e)){zero_motion();return;}
        if(at<float>(0xf4)>0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-0.5);if(at<float>(0xf4)<0.0f){zero_motion();at<unsigned char>(0x47e)=0;}}
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.5);if(at<float>(0xf4)>0.0f){zero_motion();at<unsigned char>(0x47e)=0;}}
    }
    __forceinline void normal_jump(float vx) {
        if(!sequence_index_13e)landing();
        if(!sequence_index_13e && !at<unsigned char>(0x47e))zero_motion();
        if(sequence_index_13e>0){
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);at<float>(0xf0)=udonge_surface(this);zero_motion();return;}
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=15.0f;at<float>(0x100)=0.6f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline bool recover_advance() {
        if(advance()){
            if(at<signed char>(0x72c)==2){set_action_and_finalize(700);at<short>(0x4a8)=3;at<short>(0x4ac)=3;return true;}
            set_action_and_finalize(0);if(at<int>(0x6b8)>0)set_action_and_finalize(1);
        }return false;
    }
    __forceinline void face_without_velocity() {
        if(peer()->at<float>(0xec)<at<float>(0xec))at<unsigned char>(0x104)=255;
        if(at<float>(0xec)<peer()->at<float>(0xec))at<unsigned char>(0x104)=1;
    }
    __forceinline void recovery_jump(float vx) {
        if((!sequence_index_13e && frame_index_140<3)||sequence_index_13e==3)landing();
        if(sequence_index_13e<3){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){at<float>(0xf0)=udonge_surface(this);zero_motion();select_sequence(3);return;}}
        if(recover_advance())return;
        if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)face_without_velocity();
        if(entry(1)){at<float>(0xf8)=4.5f;at<float>(0xf4)=vx;at<float>(0x100)=0.35f;}
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(udonge_random_u32()%100u)),
            static_cast<float>(static_cast<float>(udonge_random_u32()%200u)+at<float>(0xf0)),direction,1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=ahead?static_cast<float>(80*facing()+at<float>(0xec)):at<float>(0xec);
        effect(125,x,y,direction,1);
        effect(126,at<float>(0xec),static_cast<float>(at<float>(0xf0)+height),reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104),1);
        event(31);
    }
    __forceinline void high_jump(float vx,float vy,float gravity) {
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);at<float>(0xf0)=udonge_surface(this);zero_motion();return;}
        if(udonge_on_surface(this)||at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
        if(sequence_index_13e>0){at<float>(0xf8)-=at<float>(0x100);if(at<float>(0xf8)<-20.0f)at<float>(0xf8)=-20.0f;}
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f)select_sequence(2);
        advance();if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=gravity;at<unsigned char>(0x47e)=0;effect(63,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1);}
    }
    __forceinline void aim_to_peer() {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        at<float>(0x744)=-udonge_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);
    }
    __forceinline void fan800(int xoff,double height,bool aimed) {
        float p[3];
        if(aimed)p[0]=static_cast<float>((static_cast<float>(udonge_random(9))-4.0)+at<float>(0x744));
        else p[0]=static_cast<float>(static_cast<float>(udonge_random(9))-4.0);
        at<float>(0x744)=p[0];p[1]=25.0f;p[2]=0.0f;spawn_offset(800,xoff,height,p,3);
        p[2]=1.0f;spawn_offset(800,xoff,height,p,3);
        p[0]=static_cast<float>(at<float>(0x744)+5.0);p[2]=4.0f;spawn_offset(800,xoff,height,p,3);
        p[0]=static_cast<float>(at<float>(0x744)-5.0);p[2]=4.0f;spawn_offset(800,xoff,height,p,3);
        p[0]=static_cast<float>(at<float>(0x744)+10.0);p[2]=4.0f;spawn_offset(800,xoff,height,p,3);
        p[0]=static_cast<float>(at<float>(0x744)-10.0);p[2]=4.0f;spawn_offset(800,xoff,height,p,3);
        phase_counter(10);
    }
    __forceinline void aim_short(short lo,short hi) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*facing());
        at<short>(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(udonge_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx))));
        if(at<short>(0x734)<lo)at<short>(0x734)=lo;
        if(at<short>(0x734)>hi)at<short>(0x734)=hi;
    }
    __forceinline void fan801(int xoff,double height,bool charged,bool air=false) {
        float p[3];p[0]=static_cast<float>(at<short>(0x734));p[1]=5.0f;p[2]=charged?7.0f:0.0f;
        spawn_offset(801,xoff,height,p,3);p[2]=4.0f;spawn_offset(801,xoff,height,p,3);
        p[0]=static_cast<float>(at<short>(0x734)+(charged?45.0:15.0));p[2]=charged?9.0f:8.0f;spawn_offset(801,xoff,height,p,3);
        p[0]=static_cast<float>(at<short>(0x734)-(charged?45.0:15.0));p[2]=charged?9.0f:8.0f;spawn_offset(801,xoff,height,p,3);
        if(air){dispatch_character_wave_handle(3);at<float>(0xf4)=-6.0f;at<float>(0xf8)=5.0f;at<float>(0x100)=0.6f;phase_counter(50);}
        else{phase_counter(50);dispatch_character_wave_handle(3);}
    }
    __forceinline void expand_cone() {
        if(at<float>(0x73c)>0.0f){at<float>(0x7b0)+=at<float>(0x73c);at<float>(0x73c)=static_cast<float>(at<float>(0x73c)-static_cast<double>(0.2f));if(at<float>(0x73c)<0.25f)at<float>(0x73c)=0.25f;}
    }
    __forceinline void spawn_at_peer(int object,float *p) {
        int direction=at<unsigned char>(0x104);float y=static_cast<float>(peer()->at<float>(0xf0)+100.0);float x=peer()->at<float>(0xec);spawn(object,x,y,direction,1,p,3);
    }
    __forceinline bool peer_in_cone() {
        if(at<signed char>(0x104)==1){
            UdongeActionStateView *target=peer();
            if(at<float>(0xec)<target->at<float>(0xec)){
                double y=target->at<float>(0xf0);double slope=udonge_tangent(at<float>(0x7b0));
                if(y<(static_cast<double>(target->at<float>(0xec))-at<float>(0xec))*slope+at<float>(0xf0)){
                    y=target->at<float>(0xf0);slope=udonge_tangent(-at<float>(0x7b0));
                    if((static_cast<double>(peer()->at<float>(0xec))-at<float>(0xec))*slope+at<float>(0xf0)<y)return true;
                }
            }
        }
        if(at<signed char>(0x104)==-1){
            UdongeActionStateView *target=peer();
            if(target->at<float>(0xec)<at<float>(0xec)){
                double y=target->at<float>(0xf0);double slope=udonge_tangent(at<float>(0x7b0));
                if(y<(static_cast<double>(at<float>(0xec))-target->at<float>(0xec))*slope+at<float>(0xf0)){
                    y=target->at<float>(0xf0);slope=udonge_tangent(-at<float>(0x7b0));
                    if((static_cast<double>(at<float>(0xec))-peer()->at<float>(0xec))*slope+at<float>(0xf0)<y)return true;
                }
            }
        }
        return false;
    }
    __forceinline bool update_beam_radius() {
        if(sequence_index_13e==1){
            if(!at<short>(0x730)){at<float>(0x73c)=at<float>(0x740)+at<float>(0x73c);if(at<float>(0x73c)>=200.0){at<float>(0x73c)=200.0f;at<short>(0x730)=1;}}
            if(at<short>(0x730)>0 && at<short>(0x730)<20){at<float>(0x73c)+=at<float>(0x740);at<float>(0x740)=static_cast<float>(at<float>(0x740)-8.0);if(at<float>(0x740)<1.0){at<float>(0x740)=1.0f;++at<short>(0x730);}}
            if(at<short>(0x730)>19){at<float>(0x73c)=static_cast<float>(at<float>(0x73c)-40.0);if(at<float>(0x73c)<0.0f){at<float>(0x73c)=0.0f;next_sequence_block();return true;}}
        }return false;
    }
    __forceinline void beam_pair826(float *p) {
        spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
        spawn(826,at<float>(0xec),at<float>(0xf0),static_cast<unsigned char>(-at<signed char>(0x104)),1,p,3);
    }
    __forceinline void begin_beams826(bool diagonal) {
        at<short>(0x730)=0;at<float>(0x73c)=0.0f;at<float>(0x740)=40.0f;dispatch_character_wave_handle(19);counter(200,120);phase_counter(50);at<int>(0x180)=1;
        float p[3];
        if(diagonal){
            p[0]=-45.0f;p[1]=0.0f;p[2]=1.0f;beam_pair826(p);
            p[0]=45.0f;p[1]=0.0f;p[2]=1.0f;beam_pair826(p);
            if(at<signed char>(0x60b)>3){p[1]=0.0f;p[2]=1.0f;p[0]=90.0f;spawn_offset(826,0,0.0,p,3);p[0]=90.0f;spawn(826,at<float>(0xec),at<float>(0xf0),static_cast<unsigned char>(-at<signed char>(0x104)),1,p,3);}
        }else{
            p[0]=0.0f;p[1]=0.0f;p[2]=1.0f;beam_pair826(p);
            if(at<signed char>(0x60b)>3){p[0]=-45.0f;p[1]=0.0f;p[2]=1.0f;beam_pair826(p);p[0]=45.0f;p[1]=0.0f;p[2]=1.0f;beam_pair826(p);}
        }
        p[2]=5.0f;spawn_offset(826,0,100.0,p,3);
    }
    __forceinline void spell_flash(int xoff,double height,int window) {
        at<short>(0x48a)=40;event(23);
        effect(115,xoff<0?static_cast<float>(at<float>(0xec)-(-xoff*facing())):xoff?static_cast<float>(xoff*facing()+at<float>(0xec)):at<float>(0xec),static_cast<float>(at<float>(0xf0)+height),at<unsigned char>(0x104),1);
        sequence_window(0,window,60);secondary_cycle();
    }
    __forceinline void orbit900(float *p) {
        spawn(900,static_cast<float>(udonge_cosine(-p[0])*100.0*facing()+at<float>(0xec)),
            static_cast<float>(udonge_sine(-p[0])*100.0+at<float>(0xf0)+85.0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void orbit852(float *p) {
        spawn(852,static_cast<float>(udonge_cosine(-p[0])*100.0*facing()+at<float>(0xec)),
            static_cast<float>(udonge_sine(-p[0])*100.0+(at<float>(0xf0)+130.0)),at<unsigned char>(0x104),1,p,4);
    }
};
}
