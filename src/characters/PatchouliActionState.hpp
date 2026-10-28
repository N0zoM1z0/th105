#pragma once
#include <math.h>
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class PatchouliActionStateView;
extern int g_match_identifier;
unsigned __cdecl patchouli_random(int);
unsigned __cdecl patchouli_random_u32();
float __cdecl patchouli_atan(float,float);
double __cdecl patchouli_sine(float);
double __cdecl patchouli_cosine(float);
float __cdecl patchouli_square(float);
float __fastcall patchouli_surface(PatchouliActionStateView *);
unsigned char __fastcall patchouli_on_surface(PatchouliActionStateView *);
struct PatchouliActionScratch { void reset(); };
// Pointer-only extension; never instantiate as a recovered complete Fighter.
class PatchouliActionStateView : public AnimationSequenceObjectView {
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
                set_action_and_finalize(10);at<float>(0xf0)=patchouli_surface(this);zero_motion();return;
            }
        }
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f)next_sequence_block();
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=13.0f;at<float>(0x100)=0.4f;at<unsigned char>(0x47e)=0;}
    }

    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(patchouli_random_u32()%100u)),
               static_cast<float>(static_cast<float>(patchouli_random_u32()%200u)+at<float>(0xf0)),direction,1);
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
    __forceinline void high_jump(float vx,float vy) {
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);at<float>(0xf0)=patchouli_surface(this);zero_motion();return;
        }
        if(patchouli_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(at<float>(0xf8)<-20.0f)at<float>(0xf8)=-20.0f;
        }
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=0.6f;at<unsigned char>(0x47e)=0;
            effect(63,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1);
        }
    }
    __forceinline void release_flight(int sequence) {
        if(at<unsigned char>(0x104)==1) {
            if(peer()->at<float>(0xec)<at<float>(0xec)) {
                at<unsigned char>(0x104)=255;at<float>(0xf4)=-at<float>(0xf4);
            }
            select_sequence(sequence);
        } else {
            if(peer()->at<float>(0xec)>at<float>(0xec)) {
                at<unsigned char>(0x104)=static_cast<unsigned char>(-at<unsigned char>(0x104));
                at<float>(0xf4)=-at<float>(0xf4);
            }
            select_sequence(sequence);
        }
    }

    __forceinline void spawn_offset(int object,int xoff,double yoff,float *p,int count) {
        int direction=at<unsigned char>(0x104);
        float y=yoff==0.0?at<float>(0xf0):(yoff<0.0?static_cast<float>(at<float>(0xf0)-(-yoff)):static_cast<float>(at<float>(0xf0)+yoff));
        float x=xoff==0?at<float>(0xec):(xoff<0?
            static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline void ring820_ground(float *p,int xoff) {
        for(int angle=0;angle<360;angle+=45) {
            p[0]=static_cast<float>(patchouli_random(30)+angle);
            at<short>(0x730)=(p[0]<0.0f || p[0]<180.0f)?1:-1;
            spawn(820,
                static_cast<float>(patchouli_cosine(-p[0])*50.0+at<float>(0xec)+static_cast<double>(xoff*facing())),
                static_cast<float>(patchouli_sine(-p[0])*50.0*0.25+at<float>(0xf0)),
                at<unsigned char>(0x104),at<unsigned char>(0x730),p,3);
        }
    }

    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));
        at<float>(0x744)=-patchouli_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);
        if(at<float>(0x744)<low)at<float>(0x744)=low;
        if(at<float>(0x744)>high)at<float>(0x744)=high;
    }
    __forceinline void charge_effect(int xoff,double height) {
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(62,x,y,direction,1);next_sequence_block();
    }
    __forceinline void fan800_emit(int xoff,double height,double spread) {
        at<int>(0x180)=1;phase_counter(10);
        float p[3]={static_cast<float>(-15*at<short>(0x732)+static_cast<double>(at<float>(0x744))+spread),12.0f,0.0f};
        spawn_offset(800,xoff,height,p,3);dispatch_character_wave_handle(0);++at<short>(0x732);
    }
    __forceinline void ground_fan_tick(int xoff,double height) {
        if(at<short>(0x730)>0) {
            short tick=++at<short>(0x730);
            if(sequence_index_13e) {
                if(tick%3==1 && at<short>(0x732)<5)fan800_emit(xoff,height,30.0);
            } else if(tick%3==1 && at<short>(0x732)<3)fan800_emit(xoff,height,15.0);
        }
    }
    __forceinline void air_fan_tick(int xoff,double height) {
        if(at<short>(0x730)>0) {
            short tick=++at<short>(0x730);
            if(!sequence_index_13e && tick%3==1 && at<short>(0x732)<3)fan800_emit(xoff,height,15.0);
            if(sequence_index_13e==1 && at<short>(0x730)%3==1 && at<short>(0x732)<5)fan800_emit(xoff,height,30.0);
        }
    }
    __forceinline void air_fan_motion() {
        if(sequence_index_13e==2)landing();
        if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;
        if(sequence_index_13e<=1) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                zero_motion();select_sequence(2);at<float>(0xf0)=patchouli_surface(this);
            }
        }
    }

    __forceinline void burst800(int xoff,double height) {
        if(at<short>(0x730)<=0)return;
        at<short>(0x730)=0;at<int>(0x180)=1;
        if(!sequence_index_13e) {
            float p[3];
            for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*40.0-60.0);p[1]=15.0f;p[2]=2.0f;
                spawn_offset(800,xoff,height,p,3);
            }
        } else {
            float p[3];
            for(float n=0.0f;n<7.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*25.0-75.0);p[1]=15.0f;p[2]=2.0f;
                spawn_offset(800,xoff,height,p,3);
            }
        }
    }
    __forceinline void pair801_emit(int bound,double center,int xoff,double height) {
        at<int>(0x180)=1;phase_counter(5);
        float p[3]={static_cast<float>(static_cast<float>(patchouli_random(bound))-center),25.0f,6.0f};
        spawn_offset(801,xoff,height,p,3);p[2]=7.0f;spawn_offset(801,xoff,height,p,3);
        dispatch_character_wave_handle(2);++at<short>(0x732);
    }
    __forceinline void pair801_tick(int xoff,double height) {
        if(at<short>(0x730)>0) {
            short tick=++at<short>(0x730);
            if(sequence_index_13e) {
                if(sequence_index_13e==1 && tick%2==1 && at<short>(0x732)<10)pair801_emit(30,15.0,xoff,height);
            } else if(tick%2==1 && at<short>(0x732)<5)pair801_emit(16,8.0,xoff,height);
        }
    }
    __forceinline void circle801() {
        float p[3];p[1]=5.0f;p[2]=0.0f;
        for(int angle=0;angle<315;angle+=45){p[0]=static_cast<float>(angle);spawn_offset(801,100,140.0,p,3);}
        p[2]=2.0f;spawn_offset(801,100,140.0,p,3);
    }

    __forceinline void ground810_emit(float speed,float mode) {
        float p[3]={0.0f,speed,mode};spawn_offset(810,60,114.0,p,3);
        int direction=at<unsigned char>(0x104);
        effect(128,static_cast<float>(200*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))),
               at<float>(0xf0),direction,-1);
    }
    __forceinline void ground810(unsigned control,float speed) {
        landing();at<unsigned char>(0x17c)=0;
        if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.75);if(at<float>(0xf4)>0.0f)at<float>(0xf4)=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
            if(at<signed char>(0x604)<3)ground810_emit(speed,0.0f);
            else ground810_emit(speed,6.0f);
            phase_counter(50);counter(200,60);dispatch_character_wave_handle(3);
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2) {
            float p[3]={0.0f,speed,1.0f};spawn_offset(810,60,114.0,p,3);
            int direction=at<unsigned char>(0x104);
            effect(128,static_cast<float>(200*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))),
                   at<float>(0xf0),direction,-1);
            counter(200,60);phase_counter(50);at<float>(0xf4)=-10.0f;dispatch_character_wave_handle(3);
        }
    }
    __forceinline void air810(float angle) {
        if(sequence_index_13e==2)landing();
        at<unsigned char>(0x17c)=0;
        if(sequence_index_13e<2) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();at<float>(0xf0)=patchouli_surface(this);return;}
        }
        if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(9);return;}
        if(entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
            if(at<signed char>(0x604)<3){float ordinary[3]={angle,15.0f,0.0f};spawn_offset(810,40,45.0,ordinary,3);}
            else {float upgraded[3]={angle,15.0f,6.0f};spawn_offset(810,40,45.0,upgraded,3);}
            counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            at<float>(0xf4)=-6.0f;at<float>(0xf8)=8.0f;at<float>(0x100)=0.45f;
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
            float p[3]={angle,15.0f,0.0f};
            spawn_offset(810,40,45.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            at<float>(0xf4)=-6.0f;at<float>(0xf8)=8.0f;at<float>(0x100)=0.45f;
        }
    }

    __forceinline void ring820_surface(float *p) {
        for(int angle=0;angle<360;angle+=45) {
            p[0]=static_cast<float>(patchouli_random(30)+angle);
            at<short>(0x730)=(p[0]<0.0f || p[0]<180.0f)?1:-1;
            double wave=patchouli_sine(-p[0])*75.0*0.25;
            int layer=at<unsigned char>(0x730),direction=at<unsigned char>(0x104);
            spawn(820,
                static_cast<float>(patchouli_cosine(-p[0])*75.0+at<float>(0xec)),
                static_cast<float>(patchouli_surface(this)+wave),direction,layer,p,3);
        }
    }
    __forceinline void rising820(unsigned control,double height_limit,float vy,float drift) {
        if(!sequence_index_13e || sequence_index_13e==4)landing();
        at<unsigned char>(0x17c)=2;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(sequence_index_13e<4) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                zero_motion();select_sequence(4);at<float>(0xf0)=patchouli_surface(this);return;
            }
        }
        if(sequence_index_13e==1) {
            if(time_counter_144%5==0){float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);}
            if(time_counter_144%10==0) {
                double y=at<float>(0xf0);
                if(y-patchouli_surface(this)<height_limit) {
                    float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);
                }
            }
            if(time_counter_144>=34){next_sequence_block();return;}
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1)) {
            dispatch_character_wave_handle(6);phase_counter(50);counter(200,60);
            at<float>(0xf8)=vy;at<float>(0x100)=0.4f;at<float>(0x7b4)=drift;
        }
    }
    __forceinline void orbit825(float *p) {
        spawn(825,
            static_cast<float>((patchouli_cosine(-p[0])*200.0-100.0)*facing()+at<float>(0xec)),
            static_cast<float>(patchouli_sine(-p[0])*200.0+at<float>(0xf0)+100.0),
            at<unsigned char>(0x104),1,p,3);
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        at<short>(0x48a)=40;event(23);
        int direction=at<unsigned char>(0x104);float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void orbit852(float *p,double radius) {
        spawn(852,
              static_cast<float>(patchouli_cosine(-p[0])*radius*facing()+at<float>(0xec)),
              static_cast<float>(patchouli_sine(p[0])*radius+at<float>(0xf0)+100.0),
              at<unsigned char>(0x104),1,p,3);
    }

    template<class T> __forceinline T &at(unsigned o) {
        return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+o);
    }
    __forceinline PatchouliActionStateView *peer() { return static_cast<PatchouliActionStateView *>(related_170); }
    __forceinline PatchouliActionStateView *owner() { return at<PatchouliActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<PatchouliActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void orbit900(float *p,unsigned angle_offset) {
        spawn(900,
            static_cast<float>(patchouli_cosine(-at<float>(angle_offset))*150.0*facing()+at<float>(0xec)),
            static_cast<float>(patchouli_sine(-at<float>(angle_offset))*150.0+at<float>(0xf0)+100.0),
            at<unsigned char>(0x104),1,p,3);
    }
};
}
