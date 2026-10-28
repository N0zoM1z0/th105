#pragma once
#include <math.h>
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class YuyukoActionStateView;
extern int g_match_identifier;
unsigned __cdecl yuyuko_random(int);
unsigned __cdecl yuyuko_random_u32();
float __cdecl yuyuko_atan(float,float);
double __cdecl yuyuko_sine(float);
double __cdecl yuyuko_cosine(float);
float __cdecl yuyuko_square(float);
float __fastcall yuyuko_surface(YuyukoActionStateView *);
unsigned char __fastcall yuyuko_on_surface(YuyukoActionStateView *);
struct YuyukoActionScratch { void reset(); };
// Pointer-only extension; never instantiate as a recovered complete Fighter.
class YuyukoActionStateView : public AnimationSequenceObjectView {
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
                set_action_and_finalize(10);at<float>(0xf0)=yuyuko_surface(this);zero_motion();return;
            }
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=12.0f;at<float>(0x100)=0.4f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%100u)),
               static_cast<float>(static_cast<float>(yuyuko_random_u32()%200u)+at<float>(0xf0)),direction,1);
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
            set_action_and_finalize(10);at<float>(0xf0)=yuyuko_surface(this);zero_motion();return;
        }
        if(yuyuko_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
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
    template<class T> __forceinline T &at(unsigned o) {
        return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+o);
    }
    __forceinline YuyukoActionStateView *peer() { return static_cast<YuyukoActionStateView *>(related_170); }
    __forceinline YuyukoActionStateView *owner() { return at<YuyukoActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<YuyukoActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void decelerate(double amount,bool clear) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-amount);
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=0.0f;if(clear)at<unsigned char>(0x47e)=0;}
    }
    __forceinline void mode848(float mode,int xoff=0,double height=0.0) {
        float p[3]={0.0f,0.0f,mode};spawn_offset(848,xoff,height,p,3);
    }
    __forceinline bool air_landing() {
        at<float>(0xf8)-=at<float>(0x100);
        if(!static_cast<unsigned char>(crossed()))return false;
        set_action_and_finalize(10);at<float>(0xf0)=yuyuko_surface(this);zero_motion();return true;
    }
    __forceinline void charge_flash(int xoff,double height) {
        next_sequence_block();
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction)));
        effect(62,x,y,direction,1);
    }
    __forceinline void aim_fan() {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));
        at<short>(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(yuyuko_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx))));
        if(at<short>(0x734)<-20)at<short>(0x734)=-20;
        if(at<short>(0x734)>20)at<short>(0x734)=20;
        at<short>(0x730)=1;counter(200,45);
    }
    __forceinline void fan800_emit(int step,bool extra) {
        at<int>(0x180)=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(static_cast<double>(at<short>(0x734)+5*n*(at<short>(0x732)+step))-10*(at<short>(0x732)+step));
            p[1]=1.0f;p[2]=static_cast<float>(at<short>(0x732));spawn_offset(800,60,160.0,p,3);
        }
        if(extra){p[2]=static_cast<float>(at<short>(0x732)+16.0);spawn_offset(800,60,160.0,p,3);}
        dispatch_character_wave_handle(1);++at<short>(0x732);
    }
    __forceinline void fan800_tick(int cap,bool extra) {
        if(at<short>(0x730)>0) {
            short tick=++at<short>(0x730);
            if(sequence_index_13e) {if(tick%10==1 && at<short>(0x732)<cap)fan800_emit(2,extra);}
            else if(tick%10==1 && at<short>(0x732)<3)fan800_emit(3,extra);
        }
    }
    __forceinline void fan_charge() {
        effect(62,at<float>(0xec),static_cast<float>(at<float>(0xf0)+150.0),at<unsigned char>(0x104),1);
        next_sequence_block();
    }
    __forceinline void ground_fan(int cap,bool extra) {
        landing();if(sequence_index_13e<2 && !at<int>(0x6c0))at<unsigned char>(0x750)=0;
        fan800_tick(cap,extra);if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142) {
            if(frame_index_140==5 && at<unsigned char>(0x750))fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)aim_fan();
    }
    __forceinline void air_fan() {
        if(sequence_index_13e==2)landing();if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;
        at<float>(0xf8)-=at<float>(0x100);
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            at<short>(0x730)=0;select_sequence(2);at<unsigned char>(0x47f)=0;
            at<float>(0xf0)=yuyuko_surface(this);zero_motion();return;
        }
        fan800_tick(4,true);if(advance())set_action_and_finalize(0);
        if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142) {
            if(frame_index_140==5 && at<unsigned char>(0x750))fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
            if(!frame_timer_142 && frame_index_140==14)at<float>(0x100)=0.6f;
        }
        if(sequence_index_13e==1 && !frame_timer_142) {
            if(frame_index_140==2)aim_fan();
            if(!frame_timer_142 && frame_index_140==12)at<float>(0x100)=0.6f;
        }
    }
    __forceinline void circle801(float *p) {
        spawn(801,
            static_cast<float>(yuyuko_cosine(-p[0])*100.0*facing()+at<float>(0xec)),
            static_cast<float>(yuyuko_sine(p[0])*100.0+at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline bool land_air801() {
        at<float>(0xf8)-=at<float>(0x100);
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);at<float>(0x100)=0.0f;at<unsigned char>(0x47f)=0;
            at<float>(0xf0)=yuyuko_surface(this);zero_motion();return true;
        }
        return false;
    }
    __forceinline void air801(bool reverse) {
        if(sequence_index_13e==2)landing();if(land_air801())return;
        if(!at<int>(0x6c4))at<unsigned char>(0x750)=0;
        if(!sequence_index_13e && at<short>(0x730)==1) {
            if(at<short>(0x732)%5==0 && at<short>(0x734)<=5) {
                dispatch_character_wave_handle(2);at<int>(0x180)=1;phase_counter(10);
                float p[3]={static_cast<float>(reverse?10*(at<short>(0x734)+12):-135-10*at<short>(0x734)),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++at<short>(0x734);
            }
            ++at<short>(0x732);
        }
        if(sequence_index_13e==1 && at<short>(0x730)==1) {
            if(at<short>(0x732)%3==0 && at<short>(0x734)<=10) {
                dispatch_character_wave_handle(2);at<int>(0x180)=1;phase_counter(10);
                float p[3]={static_cast<float>(reverse?7*(-30-at<short>(0x734)):-120-7*at<short>(0x734)),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++at<short>(0x734);
            }
            ++at<short>(0x732);
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142) {
            if(frame_index_140==5 && at<unsigned char>(0x750)){effect(62,at<float>(0xec),static_cast<float>(at<float>(0xf0)+155.0),at<unsigned char>(0x104),1);next_sequence_block();}
            if(!frame_timer_142 && frame_index_140==7){at<short>(0x730)=1;counter(200,60);if(reverse)phase_counter(30);}
            if(!frame_timer_142 && frame_index_140==15)at<float>(0x100)=0.5f;
        }
        if(sequence_index_13e==1 && !frame_timer_142) {
            if(frame_index_140==3){at<short>(0x730)=1;counter(200,60);if(reverse)phase_counter(30);}
            if(!frame_timer_142 && frame_index_140==13)at<float>(0x100)=0.5f;
        }
    }
    __forceinline void spread810_loop(float *p,double base,int limit) {
        for(int n=0;n<limit;n+=10){p[0]=static_cast<float>(base-n);spawn_offset(810,38,177.0,p,3);}
    }
    __forceinline void spread810(double base) {
        float p[3];p[1]=6.0f;p[2]=12.0f;
        if(at<signed char>(0x604)<4){if(at<signed char>(0x604)<1)spread810_loop(p,base,40);else spread810_loop(p,base,50);}
        else spread810_loop(p,base,60);
        phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);
    }
    __forceinline void shot811(float angle) {
        float p[3];p[1]=6.0f;p[2]=12.0f;p[0]=angle;
        spawn_offset(811,38,177.0,p,3);phase_counter(50);counter(200,120);dispatch_character_wave_handle(6);
    }
    __forceinline bool air810_motion(unsigned char mode) {
        if(sequence_index_13e==2)landing();at<unsigned char>(0x17c)=mode;
        if(sequence_index_13e<2)at<float>(0xf8)-=at<float>(0x100);
        if((!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed())) ||
           (sequence_index_13e==1 && frame_index_140>=11 && static_cast<unsigned char>(crossed()))) {
            select_sequence(2);zero_motion();at<float>(0xf0)=yuyuko_surface(this);return true;
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1) || entry(2)){set_action_and_finalize(9);return true;}
        return false;
    }
    __forceinline void arc812_emit(float limit,double angle_scale,double speed_scale) {
        if(at<float>(0x740)<limit) {
            float p[4];p[0]=static_cast<float>(80.0-at<float>(0x740)*9.0);
            p[1]=static_cast<float>(yuyuko_sine(static_cast<float>(at<float>(0x740)*angle_scale))*speed_scale+2.0);
            p[2]=0.0f;p[3]=at<float>(0x740);
            spawn(812,static_cast<float>((yuyuko_cosine(-p[0])*100.0+at<float>(0x740)*5.0-85.0)*facing()+at<float>(0xec)),
                  static_cast<float>(yuyuko_sine(-p[0])*40.0+at<float>(0xf0)+120.0),at<unsigned char>(0x104),1,p,4);
        }
        at<float>(0x740)=static_cast<float>(at<float>(0x740)+1.0);
    }
    __forceinline void ground812(float limit,double scale,double speed) {
        landing();at<unsigned char>(0x17c)=8;if(at<short>(0x730)==1)arc812_emit(limit,scale,speed);
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);at<short>(0x730)=1;}
    }
    __forceinline void air812(float limit,double scale,double speed) {
        if(sequence_index_13e==1)landing();
        if(!sequence_index_13e && static_cast<unsigned char>(crossed())){zero_motion();at<float>(0xf0)=yuyuko_surface(this);next_sequence_block();at<short>(0x730)=0;}
        at<unsigned char>(0x17c)=8;if(at<short>(0x730)==1)arc812_emit(limit,scale,speed);
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);at<short>(0x730)=1;}if(!frame_timer_142 && frame_index_140==11)at<float>(0x100)=0.5f;}
    }
    __forceinline void spread815(int step,double bias,bool ground_first) {
        at<int>(0x180)=1;float p[3]={0.0f,0.0f,0.0f};spawn_offset(815,95,150.0,p,3);p[2]=1.0f;
        for(int n=0;n<step*5;n+=step){p[0]=static_cast<float>(n-bias);spawn_offset(815,95,150.0,p,3);}
        if(ground_first){phase_counter(50);dispatch_character_wave_handle(12);}else{dispatch_character_wave_handle(12);phase_counter(50);}
        counter(200,120);
    }
    __forceinline void air815(int step,double bias) {
        if(sequence_index_13e==2)landing();at<unsigned char>(0x17c)=1;
        if(sequence_index_13e<=1){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);at<float>(0xf0)=yuyuko_surface(this);zero_motion();return;}}
        if(advance())set_action_and_finalize(0);
        if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==6)spread815(step,bias,false);if(!frame_timer_142 && frame_index_140==17)at<float>(0x100)=0.4f;}
    }
    __forceinline void ring820(float mode) {
        phase_counter(50);counter(200,120);dispatch_character_wave_handle(13);at<int>(0x180)=1;
        float p[3];int angle=0;
        for(int n=0;angle<360;++n,angle+=60) {
            p[0]=static_cast<float>(angle);p[1]=300.0f;p[2]=mode;
            spawn(820,static_cast<float>((yuyuko_cosine(static_cast<float>(static_cast<float>(n)*60.0))*300.0+50.0)*facing()+at<float>(0xec)),
                static_cast<float>(yuyuko_sine(static_cast<float>(static_cast<float>(n)-6.0))*300.0+(at<float>(0xf0)+170.0)),at<unsigned char>(0x104),1,p,3);
        }
    }
    __forceinline void hold821(unsigned control,float angle) {
        landing();at<unsigned char>(0x17c)=6;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            if(sequence_index_13e!=1)return;
            phase_counter(50);counter(200,120);dispatch_character_wave_handle(18);at<int>(0x180)=1;
            float p[3]={angle,10.0f,0.0f};spawn_offset(821,55,180.0,p,3);
        }
        if(sequence_index_13e==1){int time=time_counter_144;if((time>=24 && !at<unsigned char>(0x750)) || time>=20*(at<signed char>(0x60a)+3))next_sequence_block();}
    }
    __forceinline void rush825(float minimum,int duration,bool wave_first) {
        landing();at<unsigned char>(0x17c)=3;if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;
        if(sequence_index_13e==1) {
            at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-0.5);if(at<float>(0xf4)<minimum)at<float>(0xf4)=minimum;
            if(time_counter_144>=duration || (peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing())<=120.0){next_sequence_block();return;}
            if(time_counter_144%2==0) {
                float p[3]={static_cast<float>(yuyuko_random(360)),static_cast<float>(static_cast<float>(yuyuko_random(50))*static_cast<double>(0.1f)+5.0),1.0f};
                int direction=at<unsigned char>(0x104);double base=at<float>(0xec)+50.0;
                float y=static_cast<float>(static_cast<float>(yuyuko_random(200))+at<float>(0xf0));
                float x=static_cast<float>(base-static_cast<float>(yuyuko_random(100)));
                spawn(825,x,y,direction,1,p,3);
            }
        }
        if(sequence_index_13e==2){decelerate(0.5,false);if(frame_index_140<=4 && time_counter_144%4==0){float p[3]={0.0f,0.0f,0.0f};spawn_offset(825,56,127.0,p,3);}}
        if(advance())set_action_and_finalize(0);
        if(entry(1)) {
            at<float>(0xf4)=15.0f;if(wave_first)dispatch_character_wave_handle(14);counter(200,120);phase_counter(50);if(!wave_first)dispatch_character_wave_handle(14);
            effect(127,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1);
        }
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)dispatch_character_wave_handle(11);
    }
    __forceinline void petal826(int xoff,double height) {
        float p[3]={static_cast<float>(yuyuko_random(360)),0.0f,0.0f};spawn_offset(826,xoff,height,p,3);
    }
    __forceinline void ground826() {
        if(frame_index_140>=7)landing();at<unsigned char>(0x17c)=7;
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.5);if(at<float>(0xf4)>0.0f)at<float>(0xf4)=0.0f;
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==1)at<float>(0xf4)=-20.0f;
            if(!frame_timer_142 && frame_index_140==2){dispatch_character_wave_handle(17);counter(200,120);phase_counter(50);petal826(45,26.0);}
            if(!frame_timer_142 && frame_index_140==3)petal826(58,217.0);
            if(!frame_timer_142 && frame_index_140==4)petal826(5,266.0);
            if(!frame_timer_142 && frame_index_140==5)petal826(-64,234.0);
            if(!frame_timer_142 && frame_index_140==6)petal826(-90,132.0);
        }
    }
    __forceinline void spell_flash(int xoff,double height,int outcome) {
        at<short>(0x48a)=40;event(23);int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void orbit_spell(int object,float *p,bool reverse) {
        if(reverse) {
            double base=at<float>(0xec);int direction=static_cast<unsigned char>(-at<unsigned char>(0x104));
            spawn(object,static_cast<float>(base-yuyuko_cosine(-p[0])*100.0*facing()),
                  static_cast<float>(yuyuko_sine(-p[0])*100.0+at<float>(0xf0)+100.0),direction,1,p,3);
        } else {
            spawn(object,static_cast<float>(yuyuko_cosine(-p[0])*100.0*facing()+at<float>(0xec)),
                  static_cast<float>(yuyuko_sine(-p[0])*100.0+at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,3);
        }
    }
    __forceinline void ring_spell(int object,bool growing) {
        float p[3];
        for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)) {
            double angle=n*30.0;
            p[0]=static_cast<float>(angle);p[1]=growing?static_cast<float>(at<float>(0x740)+4.0):4.0f;p[2]=0.0f;orbit_spell(object,p,false);
            p[0]=static_cast<float>(angle);p[1]=growing?static_cast<float>(at<float>(0x740)+4.0):4.0f;p[2]=0.0f;orbit_spell(object,p,true);
            float offset=static_cast<float>(angle+15.0);
            p[0]=offset;p[1]=growing?static_cast<float>(at<float>(0x740)+7.0):7.0f;p[2]=2.0f;orbit_spell(object,p,false);
            p[0]=offset;p[1]=growing?static_cast<float>(at<float>(0x740)+7.0):7.0f;p[2]=2.0f;orbit_spell(object,p,true);
        }
        dispatch_character_wave_handle(50);
    }
    __forceinline void pair857(bool air) {
        float radius=static_cast<float>(static_cast<float>(yuyuko_random(125))+50.0);
        float height=static_cast<float>(at<short>(0x730)*60.0+100.0);
        float p[3]={static_cast<float>(5.0-static_cast<float>(yuyuko_random(10))),35.0f,12.0f};
        spawn(857,static_cast<float>(facing()*static_cast<double>(radius)+at<float>(0xec)),air?static_cast<float>(at<float>(0xf0)+height):height,at<unsigned char>(0x104),-1,p,3);
        spawn(857,static_cast<float>(at<float>(0xec)-facing()*static_cast<double>(radius)),air?static_cast<float>(at<float>(0xf0)+height):height,at<unsigned char>(0x104),1,p,3);
        dispatch_character_wave_handle(16);++at<short>(0x730);
    }
    __forceinline void difficulty900(float *p,bool every_wave) {
        float phase=static_cast<float>(yuyuko_random(360));if(!every_wave)dispatch_character_wave_handle(13);
        int angle=0;
        for(int n=0;angle<360;++n,angle+=40) {
            if(every_wave)dispatch_character_wave_handle(13);
            p[0]=static_cast<float>(static_cast<double>(angle)+phase);p[1]=700.0f;p[2]=0.0f;
            spawn(900,static_cast<float>((yuyuko_cosine(static_cast<float>(static_cast<float>(n)*60.0))*300.0+50.0)*facing()+at<float>(0xec)),
                static_cast<float>(yuyuko_sine(static_cast<float>(static_cast<float>(n)-6.0))*300.0+(at<float>(0xf0)+170.0)),at<unsigned char>(0x104),1,p,3);
        }
    }
    __forceinline void difficulty901(float *p,int period,double turn) {
        if(!time_counter_144)at<float>(0x740)=static_cast<float>(yuyuko_random(360));
        if(time_counter_144%period || at<float>(0x73c)>100.0f)return;
        dispatch_character_wave_handle(10);p[0]=static_cast<float>(at<float>(0x73c)*turn+at<float>(0x740));p[1]=6.0f;p[2]=0.0f;
        spawn_offset(901,0,120.0,p,3);p[2]=5.0f;spawn_offset(901,0,120.0,p,3);at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+1.0);
    }
    __forceinline void fade_alpha() {
        if(sequence_index_13e==1){unsigned char alpha=at<unsigned char>(0x113);at<unsigned char>(0x113)=alpha<6?0:static_cast<unsigned char>(alpha-6);}
        if(sequence_index_13e==3){unsigned char alpha=at<unsigned char>(0x113);at<unsigned char>(0x113)=alpha>249?255:static_cast<unsigned char>(alpha+6);}
    }
    __forceinline void finish_story_state() {
        at<unsigned char>(0x655)=1;finalize(-1);texture(2,-1);copy_health();at<int>(0x76a)=1;
        at<short>(0x766)=0;at<short>(0x768)=0;at<short>(0x764)=0;event(23);
    }
};
}
