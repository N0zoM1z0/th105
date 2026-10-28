#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class YukariActionStateView;
extern int g_match_identifier;
unsigned __cdecl yukari_random(int);
unsigned __cdecl yukari_random_u32();
float __cdecl yukari_atan(float,float);
float __cdecl sqrt_float_value(float);
float __cdecl absolute_scalar_float(float);
double __cdecl yukari_sine(float);
double __cdecl yukari_cosine(float);
float __fastcall yukari_surface(YukariActionStateView *);
unsigned char __fastcall yukari_on_surface(YukariActionStateView *);
struct YukariCardDeque { short *at(unsigned); };
struct YukariActionScratch { void reset(); };
// Pointer-only extension, not a complete owner layout.
class YukariActionStateView : public AnimationSequenceObjectView {
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
    __forceinline YukariActionStateView *peer() { return static_cast<YukariActionStateView *>(related_170); }
    __forceinline YukariActionStateView *owner() { return at<YukariActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<YukariActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(yukari_random_u32()%100u)),
               static_cast<float>(static_cast<float>(yukari_random_u32()%200u)+at<float>(0xf0)),direction,1);
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
            set_action_and_finalize(10);at<float>(0xf0)=yukari_surface(this);zero_motion();return;
        }
        if(yukari_on_surface(this) || at<float>(0xf8)>0.0f)at<short>(0x4ae)=2;
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
    __forceinline void normal_jump(float vx) {
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !at<unsigned char>(0x47e))zero_motion();
        }
        if(sequence_index_13e>0) {
            at<float>(0xf8)-=at<float>(0x100);
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);at<float>(0xf0)=yukari_surface(this);zero_motion();return;
            }
        }
        advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=12.5f;at<float>(0x100)=0.55f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline void ensure_recovery_object() {
        if(!at<short>(0x7a4)){at<short>(0x7a4)=1;spawn(999,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,0,0);}
    }
    __forceinline void recovery_land(short action) {
        at<short>(0x730)=static_cast<short>(100*static_cast<int>(at<float>(0xf4)));
        at<short>(0x732)=static_cast<short>(100*static_cast<int>(at<float>(0xf8)));
        zero_motion();at<float>(0xf0)=yukari_surface(this);set_action_and_finalize(action);
    }
    __forceinline void recovery_slide(double step,bool counter_velocity) {
        if(classify_fighter_x_boundary() && at<float>(0xf4)<0.0f) {
            at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+step);
            if(at<float>(0xf4)>0.0f)at<float>(0xf4)=0.0f;
            if(at<unsigned char>(0x490))at<float>(0x6ac)=counter_velocity?static_cast<float>(at<short>(0x730)*-2.0):at<float>(0xf4);
        }
    }
    __forceinline bool recovery_entry_sequence() {
        if(entry(1)){ensure_recovery_object();if(at<float>(0xf8)!=0.0f){if(at<float>(0xf4)==0.0f)select_sequence(3);else select_sequence(2);return true;}}
        return false;
    }
    __forceinline void packet981(float mode) {
        float p[3]={0.0f,0.0f,mode};spawn(981,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
    }
    __forceinline void packet981_pair() {
        float p[3]={0.0f,0.0f,0.0f};spawn(981,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=6.0f;spawn(981,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
    }
    __forceinline bool recover_action() {
        if(!advance())return false;
        if(at<unsigned char>(0x72c)==2){set_action_and_finalize(700);at<short>(0x4a8)=3;at<short>(0x4ac)=3;return true;}
        set_action_and_finalize(0);if(at<int>(0x6b8)>0)set_action_and_finalize(1);return false;
    }
    __forceinline void decelerate(double amount,bool clear) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-amount);
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=0.0f;if(clear)at<unsigned char>(0x47e)=0;}
    }
    __forceinline void packet848(float mode,int layer) {
        float p[3]={0.0f,0.0f,mode};spawn(848,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),layer,p,3);
    }
    __forceinline void aim800(float cap) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));
        at<float>(0x744)=-yukari_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);
        if(at<float>(0x744)<-cap)at<float>(0x744)=-cap;
        if(at<float>(0x744)>cap)at<float>(0x744)=cap;
    }
    __forceinline void charge800() {
        next_sequence_block();effect(62,static_cast<float>(30*facing()+static_cast<double>(at<float>(0xec))),static_cast<float>(at<float>(0xf0)+190.0),at<unsigned char>(0x104),1);
    }
    __forceinline void fan800(double height,bool air) {
        if(at<short>(0x730)!=1)return;
        if(!sequence_index_13e) {
            if(at<short>(0x732)%3==0 && at<short>(0x734)<5) {
                at<int>(0x180)=1;if(air && !at<short>(0x734))counter(200,45);
                float p[3];for(int n=0;n<45;n+=15){p[0]=static_cast<float>(10*at<short>(0x734)+static_cast<double>(at<float>(0x744))-20.0+n-15.0);p[1]=10.0f;p[2]=0.0f;spawn_offset(800,82,height,p,3);}
                phase_counter(10);dispatch_character_wave_handle(2);++at<short>(0x734);
            }
        } else {
            if(at<short>(0x732)%3==(air?1:0) && at<short>(0x734)<5) {
                at<int>(0x180)=1;if(air && !at<short>(0x734))counter(200,45);
                float p[3];for(int n=0;n<75;n+=15){p[0]=static_cast<float>(10*at<short>(0x734)+static_cast<double>(at<float>(0x744))-20.0+n-30.0);p[1]=10.0f;p[2]=0.0f;spawn_offset(800,82,height,p,3);}
                phase_counter(10);dispatch_character_wave_handle(2);++at<short>(0x734);
            }
        }
        ++at<short>(0x732);
    }
    __forceinline void ground800() {
        landing();if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;fan800(135.0,false);
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2 && at<unsigned char>(0x750)){charge800();return;}if(frame_index_140==3){at<short>(0x730)=1;
            float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));at<float>(0x744)=-yukari_atan(peer()->at<float>(0xf0)-at<float>(0xf0),dx);counter(200,45);
            if(at<float>(0x744)<-30.0f)at<float>(0x744)=-30.0f;if(at<float>(0x744)>30.0f)at<float>(0x744)=30.0f;}}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){at<short>(0x730)=1;counter(200,45);aim800(30.0f);}
    }
    __forceinline void fan801(int x,double y,float angle) {
        float p[4];
        for(float n=0.0f;n<2.0f;n=static_cast<float>(n+1.0)){p[0]=angle;p[1]=10.0f;p[2]=0.0f;p[3]=static_cast<float>(5.0+n*5.0);spawn_offset(801,x,y,p,4);}
        for(float n=0.0f;n<2.0f;n=static_cast<float>(n+1.0)){p[0]=angle;p[1]=-10.0f;p[2]=0.0f;p[3]=static_cast<float>(n*5.0+5.0);spawn_offset(801,x,y,p,4);}
        p[0]=angle;p[1]=0.0f;p[2]=0.0f;p[3]=0.0f;spawn_offset(801,x,y,p,4);
    }
    __forceinline void split801(int x,double y) {
        float p[4];
        for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=-90.0f;p[1]=10.0f;p[2]=5.0f;p[3]=static_cast<float>(n*5.0+10.0);spawn_offset(801,x,y,p,4);}
        for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=90.0f;p[1]=10.0f;p[2]=6.0f;p[3]=static_cast<float>(n*5.0+10.0);spawn_offset(801,x,y,p,4);}
    }
    __forceinline void ground810(int control,int frame,int x) {
        landing();at<unsigned char>(0x17c)=0;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==frame){at<int>(0x180)=1;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn(810,static_cast<float>(x*facing()+static_cast<double>(at<float>(0xec))),0.0f,at<unsigned char>(0x104),1,p,3);dispatch_character_wave_handle(10);}
    }
    __forceinline void air810(int control,int x) {
        if(sequence_index_13e==2)landing();at<unsigned char>(0x17c)=0;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4){at<int>(0x180)=1;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn(810,static_cast<float>(x*facing()+static_cast<double>(at<float>(0xec))),640.0f,at<unsigned char>(0x104),1,p,3);dispatch_character_wave_handle(10);}if(!frame_timer_142 && frame_index_140==7)at<float>(0x100)=0.5f;}
    }
    __forceinline void ground811(int control) {
        landing();at<unsigned char>(0x17c)=4;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(811,100,145.0,p,3);dispatch_character_wave_handle(17);}
    }
    __forceinline void ground812(int control,int x,double y) {
        landing();at<unsigned char>(0x17c)=8;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4 && at<unsigned char>(0x750)){next_sequence_block();effect(62,static_cast<float>(at<float>(0xec)-40*facing()),static_cast<float>(at<float>(0xf0)+158.0),at<unsigned char>(0x104),1);return;}if(frame_index_140==5){counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(812,x,y,p,3);dispatch_character_wave_handle(21);}}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,4.0f};spawn_offset(812,x,y,p,3);dispatch_character_wave_handle(21);}
    }
    __forceinline void air802(float speed,float first_x,float first_square,float second_x,float second_square) {
        if(sequence_index_13e==5)landing();at<unsigned char>(0x17c)=1;
        if(sequence_index_13e<5){if(sequence_index_13e==4){at<float>(0x100)=0.6f;at<float>(0xf8)=static_cast<float>(at<float>(0xf8)-static_cast<double>(0.6f));}
            double y=at<float>(0xf0)+static_cast<double>(at<float>(0xf8));if(yukari_surface(this)>=y && at<float>(0xf8)<0.0f){zero_motion();at<float>(0xf0)=yukari_surface(this);select_sequence(5);return;}}
        if(sequence_index_13e==3 && !time_counter_144){counter(200,120);at<int>(0x180)=1;phase_counter(50);float p[3]={0.0f,speed,0.0f};spawn_offset(802,43,107.0,p,3);
            p[0]=yukari_atan(135.0f,first_x);float first_speed=static_cast<float>(sqrt_float_value(first_square)/15.0);p[1]=first_speed;p[2]=2.0f;spawn_offset(802,43,107.0,p,3);
            p[0]=yukari_atan(-135.0f,first_x);p[1]=first_speed;spawn_offset(802,43,107.0,p,3);
            p[0]=yukari_atan(-115.0f,second_x);float second_speed=static_cast<float>(sqrt_float_value(second_square)/15.0);p[1]=second_speed;spawn_offset(802,43,107.0,p,3);
            p[0]=yukari_atan(115.0f,second_x);p[1]=second_speed;spawn_offset(802,43,107.0,p,3);
        }
        if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}if(sequence_index_13e==1 && time_counter_144>0)next_sequence_block();
    }
    __forceinline void hold816(int control,float angle) {
        landing();at<unsigned char>(0x17c)=5;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(sequence_index_13e==1){at<float>(0x12c)=static_cast<float>(at<float>(0x12c)-40.0);short ticks=at<short>(0x730);if((ticks>=15 && !at<unsigned char>(0x750)) || ticks>=120){next_sequence_block();at<float>(0x12c)=0.0f;return;}at<short>(0x730)=static_cast<short>(ticks+1);}
        if(advance())set_action_and_finalize(0);
        if(entry(1) && !at<short>(0x730)){counter(200,120);phase_counter(50);float p[3]={angle,15.0f,0.0f};if(at<signed char>(0x609)>=4)p[2]=2.0f;spawn_offset(816,0,135.0,p,3);at<float>(0x108)=0.0f;at<float>(0x10c)=135.0f;dispatch_character_wave_handle(12);}
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==8){dispatch_character_wave_handle(18);at<int>(0x180)=1;}
    }
    __forceinline void projectile820(bool air,float mode,int wave) {
        if(!air || sequence_index_13e==1)landing();at<unsigned char>(0x17c)=2;
        if(air && !sequence_index_13e){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){at<float>(0xf0)=yukari_surface(this);next_sequence_block();zero_motion();return;}}
        if(advance())set_action_and_finalize(0);if(air && entry(1)){set_action_and_finalize(9);return;}
        if((!air || !sequence_index_13e) && !frame_timer_142){if(frame_index_140==7){at<int>(0x180)=1;counter(200,120);phase_counter(25);float p[3]={0.0f,0.0f,mode};spawn_offset(820,65,100.0,p,3);dispatch_character_wave_handle(wave);}if(air && !frame_timer_142 && frame_index_140==14)at<float>(0x100)=0.5f;}
    }
    __forceinline void projectile821(bool air) {
        if(!air || sequence_index_13e==1)landing();at<unsigned char>(0x17c)=6;
        if(air && !sequence_index_13e){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){at<float>(0xf0)=yukari_surface(this);next_sequence_block();zero_motion();return;}}
        if(advance())set_action_and_finalize(0);if(air && entry(1)){set_action_and_finalize(9);return;}
        if((!air || !sequence_index_13e) && !frame_timer_142){if(frame_index_140==7){at<int>(0x180)=1;counter(200,120);phase_counter(50);++at<short>(0x7bc);float p[3]={0.0f,static_cast<float>(at<short>(0x7bc)),0.0f};spawn_offset(821,65,100.0,p,3);dispatch_character_wave_handle(19);}if(air && !frame_timer_142 && frame_index_140==14)at<float>(0x100)=0.5f;}
    }
    __forceinline void vanish825() {
        at<float>(0x108)=0.0f;at<float>(0x10c)=100.0f;at<float>(0x11c)=static_cast<float>(at<float>(0x11c)*static_cast<double>(0.8f));
    }
    __forceinline void opening825() {
        dispatch_character_wave_handle(15);float p[3]={0.0f,0.0f,0.0f};spawn(825,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),-1,p,3);
    }
    __forceinline void ground825() {
        if(sequence_index_13e>0)landing();at<unsigned char>(0x17c)=3;
        if(sequence_index_13e)decelerate(static_cast<double>(0.3f),false);else if(frame_index_140>=5)vanish825();
        if(sequence_index_13e==1 && time_counter_144>=36)next_sequence_block();if(advance())set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)opening825();if(!frame_timer_142){if(frame_index_140==5){counter(200,120);phase_counter(50);}if(!frame_timer_142 && frame_index_140==7){
            if(facing()*at<int>(0x6b4)>0)at<float>(0xec)=static_cast<float>(450*facing()+static_cast<double>(at<float>(0xec)));
            if(facing()*at<int>(0x6b4)<0)at<float>(0xec)=static_cast<float>(at<float>(0xec)-300*facing());
            if(!at<int>(0x6b4))at<float>(0xec)=static_cast<float>(250*facing()+static_cast<double>(at<float>(0xec)));
            if(at<float>(0xec)>980.0f && at<unsigned char>(0x104)==1)at<float>(0xec)=980.0f;
            if(at<float>(0xec)<200.0f && at<unsigned char>(0x104)==255)at<float>(0xec)=200.0f;at<float>(0xf0)=yukari_surface(this);
        }}}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3 && at<short>(0x730)==1){at<unsigned char>(0x184)=1;++at<short>(0x730);}
        if(entry(1)){if(!at<short>(0x730)){dispatch_character_wave_handle(16);float p[3]={0.0f,0.0f,1.0f};spawn(825,static_cast<float>(70*facing()+static_cast<double>(at<float>(0xec))),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),-1,p,3);time_counter_144=0;at<float>(0x11c)=1.0f;at<float>(0xf4)=20.0f;at<short>(0x4a8)=6;at<short>(0x4ac)=6;}++at<short>(0x730);}
    }
    __forceinline void diving825() {
        if(sequence_index_13e==2)landing();at<unsigned char>(0x17c)=3;if(!sequence_index_13e && frame_index_140>=5)vanish825();
        if(sequence_index_13e==1){at<float>(0x108)=0.0f;at<float>(0x10c)=100.0f;at<float>(0x12c)=static_cast<float>(at<float>(0x12c)-35.0);if(static_cast<unsigned char>(crossed())){at<float>(0x12c)=0.0f;at<float>(0xf0)=yukari_surface(this);at<float>(0xf8)=0.0f;next_sequence_block();}}
        if(sequence_index_13e==2 && at<float>(0xf4)!=0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)*static_cast<double>(0.8f));if(absolute_scalar_float(at<float>(0xf4))<0.01f)at<float>(0xf4)=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)opening825();if(!frame_timer_142){if(frame_index_140==5){counter(200,120);phase_counter(50);}if(!frame_timer_142 && frame_index_140==7){int input=at<int>(0x6b4)*facing();if(input>0)at<float>(0x740)=1.0f;else if(input<0)at<float>(0x740)=-1.0f;at<float>(0xf0)=static_cast<float>(yukari_surface(this)+600.0);}}}
        if(sequence_index_13e==1 && time_counter_144==6){at<unsigned char>(0x184)=1;++at<short>(0x730);}
        if(entry(1)){if(!at<short>(0x730)){dispatch_character_wave_handle(16);float p[3]={0.0f,0.0f,2.0f};spawn(825,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);time_counter_144=0;at<float>(0x11c)=1.0f;at<float>(0xf4)=0.0f;at<float>(0xf8)=-25.0f;at<float>(0xf4)=static_cast<float>(at<float>(0x740)*25.0);at<short>(0x4a8)=6;at<short>(0x4ac)=6;}++at<short>(0x730);}
    }
    __forceinline void opening826() {
        at<float>(0x108)=0.0f;at<float>(0x10c)=135.0f;float p[3]={0.0f,0.0f,1.0f};spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[1]=0.5f;p[2]=4.0f;spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=4.0f;p[1]=0.25f;spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);dispatch_character_wave_handle(1);counter(200,120);phase_counter(50);
    }
    __forceinline void packet826(float mode) {
        float p[3]={0.0f,0.0f,mode};spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void launch826(float mode) {
        at<float>(0xf4)=6.0f;float p[3]={0.0f,0.5f,4.0f};spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=4.0f;p[1]=0.25f;spawn(826,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=mode;spawn(826,at<float>(0xec),static_cast<float>(at<float>(0xf0)-250.0),at<unsigned char>(0x104),1,p,3);dispatch_character_wave_handle(1);
    }
    __forceinline void interval_clear() {
        if(at<int>(0x180) && ++at<short>(0x730)>=6){at<int>(0x180)=0;at<short>(0x730)=0;}
    }
    __forceinline void falling826() {
        at<float>(0xf8)-=at<float>(0x100);if(time_counter_144%12==0)event(29);at<float>(0x12c)=static_cast<float>(at<float>(0x12c)-40.0);interval_clear();
        if(static_cast<unsigned char>(crossed())){reset_action_scratch();at<float>(0xf0)=yukari_surface(this);zero_motion();next_sequence_block();}
    }
    __forceinline void spell_flash(int xoff,double height,int outcome) {
        at<short>(0x48a)=40;event(23);int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):xoff<0?static_cast<float>(at<float>(0xec)-static_cast<double>(-xoff*static_cast<signed char>(direction))):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void simple_spell(int object,int flash_frame,int flash_x,double flash_y,int window,int shot_frame,int shot_x,double shot_y,int wave) {
        landing();texture(2,2);if(advance())set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==flash_frame)spell_flash(flash_x,flash_y,window);if(!frame_timer_142 && frame_index_140==shot_frame){float p[3]={0.0f,0.0f,0.0f};spawn_offset(object,shot_x,shot_y,p,3);dispatch_character_wave_handle(wave);}}
    }
    __forceinline void shower856() {
        short tick=at<short>(0x730);if(tick<=0)return;
        if(tick%2==0 && tick<=60){dispatch_character_wave_handle(21);float p[3]={0.0f,at<float>(0x73c),0.0f};int direction=at<unsigned char>(0x104);
            double base_y=at<float>(0xf0)+350.0;
            spawn(856,static_cast<float>((100.0-static_cast<float>(yukari_random(300)))*facing()+at<float>(0xec)),static_cast<float>(base_y-static_cast<float>(yukari_random(400))),direction,-1,p,3);at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+1.0);}
        ++at<short>(0x730);
    }
    __forceinline void difficulty900(int period,int extra_modulus) {
        if(at<short>(0x732)%period)return;dispatch_character_wave_handle(2);float p[3];p[1]=0.0f;p[2]=0.0f;
        for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*30.0);if(at<short>(0x734)%2==0)spawn(900,at<float>(0xec),static_cast<float>(100.0+at<float>(0xf0)),at<unsigned char>(0x104),1,p,3);else spawn(900,at<float>(0xec),static_cast<float>(100.0+at<float>(0xf0)),static_cast<unsigned char>(-at<unsigned char>(0x104)),1,p,3);}
        if(extra_modulus && at<short>(0x734)%extra_modulus==0){p[2]=1.0f;for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*30.0);if(at<short>(0x734)%4==0)spawn(900,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,3);else spawn(900,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),static_cast<unsigned char>(-at<unsigned char>(0x104)),1,p,3);}}
        ++at<short>(0x734);
    }
    __forceinline void opening910() {
        at<float>(0x108)=0.0f;at<float>(0x10c)=135.0f;float p[3]={0.0f,0.0f,1.0f};spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[1]=0.5f;p[2]=4.0f;spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=4.0f;p[1]=0.25f;spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);dispatch_character_wave_handle(1);
    }
    __forceinline void packet910(float mode) {
        float p[3]={0.0f,0.0f,mode};spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void launch910(float mode,float vx=6.0f) {
        at<float>(0xf4)=vx;float p[3]={0.0f,0.5f,4.0f};spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=4.0f;p[1]=0.25f;spawn(910,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
        p[2]=mode;spawn(910,at<float>(0xec),static_cast<float>(at<float>(0xf0)-250.0),at<unsigned char>(0x104),1,p,3);dispatch_character_wave_handle(1);
    }
    __forceinline void burst910(float *p,int count,double angle,int range,int speed_range,double speed) {
        at<short>(0x738)=1;
        do{p[0]=static_cast<float>(angle-static_cast<float>(yukari_random(range)));p[1]=static_cast<float>(static_cast<float>(yukari_random(speed_range))*static_cast<double>(0.1f)+speed);p[2]=12.0f;
            int direction=at<unsigned char>(0x104);double base=at<float>(0xec)+100.0;spawn(910,static_cast<float>(base-static_cast<float>(yukari_random(200))),owner()->at<float>(0xf0),direction,1,p,3);
        }while(--count);
    }
    __forceinline void finish_story_state() {
        at<unsigned char>(0x655)=1;finalize(-1);texture(2,-1);copy_health();at<int>(0x76a)=1;
        at<short>(0x766)=0;at<short>(0x768)=0;at<short>(0x764)=0;event(23);
    }
};
}
