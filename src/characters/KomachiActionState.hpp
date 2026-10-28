#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
class KomachiActionStateView;
extern int g_match_identifier;
extern float komachi_boundary_6fbd24;
extern float komachi_boundary_6fbd1c;
unsigned __cdecl komachi_random(int);
unsigned __cdecl komachi_random_u32();
float __cdecl komachi_atan(float,float);
float __cdecl sqrt_float_value(float);
float __cdecl absolute_scalar_float(float);
double __cdecl komachi_sine(float);
double __cdecl komachi_cosine(float);
float __fastcall komachi_surface(KomachiActionStateView *);
unsigned char __fastcall komachi_on_surface(KomachiActionStateView *);
struct KomachiCardDeque { short *at(unsigned); };
struct KomachiActionScratch { void reset(); };
// Pointer-only extension, not a complete owner layout.
// Pointer-only extension; never instantiate as a recovered complete Fighter.
// Pointer-only extension; never instantiate as a recovered complete Fighter.
class KomachiActionStateView : public AnimationSequenceObjectView {
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
    // Byte direction is a manager-proved call view; original formal signedness remains unknown.
    int spawn(int,float,float,unsigned char,int,const void *,int);
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
    __forceinline KomachiActionStateView *peer() { return static_cast<KomachiActionStateView *>(related_170); }
    __forceinline KomachiActionStateView *owner() { return at<KomachiActionStateView *>(0x168); }
    __forceinline int facing() { return at<signed char>(0x104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<KomachiActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base=at<float>(0xec)+50.0;
        int direction=reverse?static_cast<unsigned char>(-at<unsigned char>(0x104)):at<unsigned char>(0x104);
        effect(124,static_cast<float>(base-static_cast<float>(komachi_random_u32()%100u)),
               static_cast<float>(static_cast<float>(komachi_random_u32()%200u)+at<float>(0xf0)),direction,1);
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

    __forceinline void idle_motion() {
        if(!at<unsigned char>(0x47e)){zero_motion();return;}
        if(at<float>(0xf4)>0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-0.5);if(at<float>(0xf4)<0.0f){zero_motion();at<unsigned char>(0x47e)=0;}}
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=static_cast<float>(at<float>(0xf4)+0.5);if(at<float>(0xf4)>0.0f){zero_motion();at<unsigned char>(0x47e)=0;}}
    }
    __forceinline void normal_jump(float vx) {
        if(!sequence_index_13e){landing();if(!sequence_index_13e && !at<unsigned char>(0x47e))zero_motion();}
        if(sequence_index_13e>0){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);at<float>(0xf0)=komachi_surface(this);zero_motion();return;}}
        advance();if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=15.0f;at<float>(0x100)=0.6f;at<unsigned char>(0x47e)=0;}
    }
    __forceinline void face_peer() {
        if(peer()->at<float>(0xec)<static_cast<double>(at<float>(0xec)))at<unsigned char>(0x104)=255;
        if(peer()->at<float>(0xec)>static_cast<double>(at<float>(0xec)))at<unsigned char>(0x104)=1;
    }
    __forceinline void card_expiration() {
        at<int>(0x644)=at<int>(0x648)-at<int>(0x178);
        if(at<int>(0x644)<=0 && action_id_13c>=700 && at<unsigned char>(0x752)==1){
            signed char direction=at<signed char>(0x104);
            if((direction==1 && peer()->at<float>(0xec)<static_cast<double>(at<float>(0xec))) ||
               (direction==-1 && peer()->at<float>(0xec)>static_cast<double>(at<float>(0xec))))at<unsigned char>(0x104)=static_cast<unsigned char>(-direction);
            set_action_and_finalize(149);at<unsigned char>(0x752)=0;at<unsigned char>(0x654)=0;
            effect(68,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),1);
        }
    }
    __forceinline void recovery_jump(float vx) {
        if(!sequence_index_13e || sequence_index_13e==3)landing();
        else{at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){at<float>(0xf0)=komachi_surface(this);zero_motion();select_sequence(3);return;}}
        if(advance()){if(at<unsigned char>(0x72c)==2){set_action_and_finalize(700);at<short>(0x4a8)=3;at<short>(0x4ac)=3;return;}set_action_and_finalize(0);if(at<int>(0x6b8)>0)set_action_and_finalize(1);}
        if(sequence_index_13e==3 && frame_index_140==1 && !frame_timer_142)face_peer();
        if(entry(1)){at<float>(0xf8)=6.0f;at<float>(0xf4)=vx;at<float>(0x100)=0.5f;}
    }

    __forceinline void high_jump(float vx,float vy,float gravity,bool clamp,bool floor_after) {
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);at<float>(0xf0)=komachi_surface(this);zero_motion();return;}
        if(!floor_after && (komachi_on_surface(this) || at<float>(0xf8)>0.0f))at<short>(0x4ae)=2;
        if(sequence_index_13e>0){at<float>(0xf8)-=at<float>(0x100);if(clamp && at<float>(0xf8)<-20.0f)at<float>(0xf8)=-20.0f;}
        if(floor_after && (komachi_on_surface(this) || at<float>(0xf8)>0.0f))at<short>(0x4ae)=2;
        if(sequence_index_13e==1 && at<float>(0xf8)<4.0f)select_sequence(2);advance();
        if(entry(1)){at<float>(0xf4)=vx;at<float>(0xf8)=vy;at<float>(0x100)=gravity;at<unsigned char>(0x47e)=0;effect(63,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1);}
    }

    __forceinline void decelerate(double amount,bool clear) {
        at<float>(0xf4)=static_cast<float>(at<float>(0xf4)-amount);
        if(at<float>(0xf4)<0.0f){at<float>(0xf4)=0.0f;if(clear)at<unsigned char>(0x47e)=0;}
    }
    __forceinline void normal301() {
        if(at<unsigned char>(0x47e))decelerate(0.5,true);
        if(at<float>(0xf4)>0.0f && frame_index_140>=7)decelerate(0.5,false);
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142){if(frame_index_140==4){event(29);at<unsigned char>(0x47e)=0;}
            if(!frame_timer_142){if(frame_index_140==3)at<float>(0xf4)=10.0f;if(!frame_timer_142 && frame_index_140==7)at<float>(0xf4)=static_cast<float>(at<float>(0xf4)*0.25);}}
    }
    __forceinline void charge(int xoff,double height) {
        next_sequence_block();int direction=at<unsigned char>(0x104);float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff<0?static_cast<float>(at<float>(0xec)-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
        effect(62,x,y,direction,1);
    }
    __forceinline void ring817() {
        event(29);
        for(int angle=0;angle<360;angle+=45){
            float p[3]={static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0),10.0f,2.0f};
            spawn_ring817(p,228);
        }
    }
    __forceinline bool air_normal_land() {
        at<float>(0xf8)-=at<float>(0x100);
        if(!static_cast<unsigned char>(crossed()))return false;
        set_action_and_finalize(10);at<float>(0xf0)=komachi_surface(this);at<float>(0x100)=0.0f;at<float>(0xf8)=0.0f;return true;
    }

    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
        int direction=at<unsigned char>(0x104);float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):(xoff<0?static_cast<float>(at<float>(0xec)-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));float dy=peer()->at<float>(0xf0)-at<float>(0xf0);at<float>(0x744)=-komachi_atan(dy,dx);
        if(at<float>(0x744)<low)at<float>(0x744)=low;if(at<float>(0x744)>high)at<float>(0x744)=high;
    }
    __forceinline void start800(float low,float high,bool early_flag) {
        phase_counter(30);if(early_flag)at<short>(0x730)=1;aim(low,high);at<short>(0x730)=1;counter(200,45);
    }
    __forceinline void stream800(int limit,double bias,int x,double y,bool reverse,bool narrow) {
        if(at<short>(0x732)%2==0 && at<short>(0x734)<limit){
            dispatch_character_wave_handle(0);float p[3];
            if(narrow){p[0]=static_cast<float>(at<float>(0x744)-static_cast<double>(at<short>(0x734))+6.0);p[1]=static_cast<float>(at<short>(0x734)*1.5+9.0);}
            else{p[0]=reverse?static_cast<float>(at<float>(0x744)-at<short>(0x734)*5.0+bias):static_cast<float>(at<short>(0x734)*5.0+at<float>(0x744)-bias);p[1]=static_cast<float>(static_cast<double>(at<short>(0x734))+10.0);}
            p[2]=static_cast<float>(at<short>(0x734)%3);spawn_offset(800,x,y,p,3);++at<short>(0x734);
        }
        ++at<short>(0x732);
    }
    __forceinline void ground800(bool reverse,float low,float high) {
        landing();if(!at<int>(0x6c0))at<unsigned char>(0x750)=0;
        if(at<short>(0x730)==1){if(!sequence_index_13e)stream800(6,15.0,113,128.0,reverse,false);if(sequence_index_13e==1)stream800(10,25.0,113,128.0,reverse,false);}
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)==1){charge(-35,155.0);return;}if(frame_index_140==5)start800(low,high,false);}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)start800(low,high,false);
    }
    __forceinline bool air_shot_landing(bool clear_gravity) {
        if(sequence_index_13e==2)landing();at<float>(0xf8)-=at<float>(0x100);
        if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);if(clear_gravity)at<float>(0x100)=0.0f;at<unsigned char>(0x47f)=0;at<float>(0xf0)=komachi_surface(this);zero_motion();return true;}
        return false;
    }

    __forceinline void emit801(float *p,double xoff,double yoff) {
        int direction=at<unsigned char>(0x104);
        float y=static_cast<float>(komachi_sine(-p[0])*150.0+at<float>(0xf0)+yoff);
        float x=xoff==0.0?static_cast<float>(komachi_cosine(-p[0])*150.0*facing()+at<float>(0xec)):static_cast<float>((komachi_cosine(-p[0])*150.0+xoff)*facing()+at<float>(0xec));
        spawn(801,x,y,direction,1,p,3);
    }
    __forceinline void fan801(double spread,double second,float second_speed,double xoff,double yoff,bool charged,float low,float high) {
        phase_counter(50);dispatch_character_wave_handle(2);at<int>(0x180)=1;counter(200,60);aim(low,high);
        float p[3]={static_cast<float>(at<float>(0x744)+spread),20.0f,2.0f};emit801(p,xoff,yoff);
        p[0]=static_cast<float>(at<float>(0x744)-spread);emit801(p,xoff,yoff);
        if(charged){p[0]=static_cast<float>(at<float>(0x744)+second);p[1]=second_speed;p[2]=2.0f;emit801(p,xoff,yoff);p[0]=static_cast<float>(at<float>(0x744)-second);emit801(p,xoff,yoff);}
    }

    __forceinline void skill_cost(int wave) {counter(200,120);phase_counter(50);dispatch_character_wave_handle(wave);}
    __forceinline void shot811(float mode,float extra) {
        float p[3]={0.0f,0.0f,mode};spawn(811,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
        if(at<signed char>(0x608)>=4){p[2]=extra;spawn(811,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);}skill_cost(16);
    }
    __forceinline void ground811(float mode,float extra) {
        landing();at<unsigned char>(0x17c)=4;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10)shot811(mode,extra);
    }
    __forceinline void air811(int frame,float mode,float extra,int gravity_frame) {
        if(sequence_index_13e==2)landing();
        if(sequence_index_13e<=1){at<float>(0xf8)-=at<float>(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);at<float>(0xf0)=komachi_surface(this);zero_motion();return;}}
        at<unsigned char>(0x17c)=4;if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==frame)shot811(mode,extra);if(!frame_timer_142 && frame_index_140==gravity_frame)at<float>(0x100)=0.25f;}
    }
    __forceinline void stream815(double speed) {
        landing();at<unsigned char>(0x17c)=1;
        if(at<short>(0x730)==1){
            int limit=5;if(at<unsigned char>(0x605)>=2)limit=6;if(at<unsigned char>(0x605)>=4)limit=8;
            if(at<short>(0x732)<limit){
                if(!(at<short>(0x734)%3)){float p[3];p[0]=static_cast<float>(-80.0-static_cast<double>(komachi_random(20)));p[1]=static_cast<float>(static_cast<double>(komachi_random(50))*static_cast<double>(0.1f)+speed);p[2]=0.0f;
                    spawn(815,static_cast<float>(113*facing()+static_cast<double>(at<float>(0xec))),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);++at<short>(0x732);}
                ++at<short>(0x734);
            }
        }
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==10){at<short>(0x730)=1;dispatch_character_wave_handle(12);counter(200,120);phase_counter(50);}
    }
    __forceinline bool sweep817(float mode,double speed,int timeout) {
        if(at<signed char>(0x184)>0 && at<int>(0x180) && ++at<short>(0x730)>=5){at<int>(0x180)=0;at<short>(0x730)=0;}
        if(!(time_counter_144%5)){dispatch_character_wave_handle(29);float p[3]={mode,static_cast<float>(static_cast<double>(komachi_random(5))+speed),0.0f};spawn_offset(817,120,140.0,p,3);}
        if(!(time_counter_144%15)){
            for(int angle=0;angle<360;angle+=60){float p[3]={static_cast<float>(static_cast<double>(komachi_random(30))+angle+30.0),10.0f,2.0f};
                spawn_ring817(p,120);}
        }
        if(time_counter_144>=timeout){next_sequence_block();return true;}return false;
    }
    __forceinline void sweep_entry() {effect(127,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);}

    __forceinline void swap820(int skill,bool extra,bool cooldown_before) {
        at<unsigned char>(0x17c)=2;if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(9);
        if(entry(2)){
            if(peer()->action_id_13c<=599){
                float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);
                p[1]=1.0f;spawn(820,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,3);
                p[1]=0.0f;p[2]=2.0f;spawn_offset(820,0,100.0,p,3);
                p[1]=1.0f;spawn(820,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),at<unsigned char>(0x104),1,p,3);
                if(cooldown_before && at<unsigned char>(skill)!=4){peer()->at<short>(0x4a8)=15;peer()->at<short>(0x4ac)=15;}
                if(komachi_on_surface(this)){
                    for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;
                        int layer=(p[0]>=0.0f && p[0]<=180.0f)?1:-1;spawn(817,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),layer,p,3);}
                }
                if(komachi_on_surface(peer())){
                    for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;
                        if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->at<float>(0xec),peer()->at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);
                        else spawn(817,peer()->at<float>(0xec),peer()->at<float>(0xf0),at<unsigned char>(0x104),1,p,3);}
                }
                if(!cooldown_before){
                    if(extra && at<unsigned char>(skill)==4){
                        float ring[3]={0.0f,0.0f,4.0f};
                        for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){
                            float angle=static_cast<float>(-n*60.0);int direction=at<unsigned char>(0x104);
                            float y=static_cast<float>(komachi_sine(angle)*200.0+at<float>(0xf0)+100.0);
                            float x=static_cast<float>(komachi_cosine(angle)*200.0*facing()+at<float>(0xec));
                            spawn(820,x,y,direction,1,ring,3);
                        }
                    }else if(at<unsigned char>(skill)!=4){peer()->at<short>(0x4a8)=15;peer()->at<short>(0x4ac)=15;}
                }
                KomachiActionStateView *other=peer();at<float>(0x73c)=at<float>(0xec);at<float>(0x740)=at<float>(0xf0);
                at<float>(0xec)=other->at<float>(0xec);at<float>(0xf0)=other->at<float>(0xf0);
                other->at<float>(0xec)=at<float>(0x73c);peer()->at<float>(0xf0)=at<float>(0x740);
            }
            dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);at<short>(0x738)=1;
        }
        if(entry(3) && !komachi_on_surface(this)){select_sequence(4);return;}
        if(entry(4)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(820,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),-1,p,3);p[1]=1.0f;spawn(820,at<float>(0xec),static_cast<float>(at<float>(0xf0)+100.0),at<unsigned char>(0x104),-1,p,3);}
        if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)at<float>(0x100)=0.5f;
    }

    __forceinline void pair821(float mode) {
        float p[3]={mode,10.0f,0.0f};spawn(821,static_cast<float>(200*facing()+static_cast<double>(at<float>(0xec))),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
        p[2]=4.0f;spawn(821,static_cast<float>(200*facing()+static_cast<double>(at<float>(0xec))),at<float>(0xf0),at<unsigned char>(0x104),-1,p,3);skill_cost(19);
    }
    __forceinline void ground821(int control) {
        landing();at<unsigned char>(0x17c)=6;if(!at<int>(control))at<unsigned char>(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==7 && at<unsigned char>(0x750)){charge(-100,164.0);return;}if(frame_index_140==10)pair821(1.0f);}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)pair821(2.0f);
    }
    __forceinline void accelerate822() {
        at<float>(0x73c)=static_cast<float>(at<float>(0x73c)+static_cast<double>(0.2f));double limit=at<signed char>(0x60e)*1.5+4.0;
        if(limit<at<float>(0x73c))at<float>(0x73c)=static_cast<float>(limit);
    }
    __forceinline void publish822() {
        KomachiActionStateView *other=peer();at<float>(0x6ac)=at<float>(0x73c);
        if((at<float>(0xec)<static_cast<double>(other->at<float>(0xec)) && other->at<unsigned char>(0x104)==1) ||
           (at<float>(0xec)>static_cast<double>(other->at<float>(0xec)) && other->at<unsigned char>(0x104)==255))at<float>(0x6ac)=-at<float>(0x73c);
    }
    __forceinline void movement822(int control,int alternate,bool clear_first) {
        landing();at<unsigned char>(0x17c)=10;if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(!sequence_index_13e && frame_index_140>=4){accelerate822();publish822();}
        if(sequence_index_13e==1){
            accelerate822();
            if(!(time_counter_144%3)){float p[3]={static_cast<float>(komachi_random(360)),static_cast<float>(static_cast<double>(komachi_random(150))+250.0),0.0f};spawn(822,at<float>(0xec),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);}
            publish822();
            if(time_counter_144>=10){
                if(!at<unsigned char>(0x750) || time_counter_144>=90){if(clear_first){at<int>(0x180)=0;next_sequence_block();}else{next_sequence_block();at<int>(0x180)=0;}return;}
                if(at<int>(alternate)){select_sequence(3);at<int>(0x180)=0;return;}
            }
        }
        if(sequence_index_13e==2){at<float>(0x73c)=static_cast<float>(at<float>(0x73c)-static_cast<double>(0.4f));if(at<float>(0x73c)<0.0f)at<float>(0x73c)=0.0f;at<float>(0x6ac)=at<float>(0x73c);if(at<unsigned char>(0x104)==peer()->at<unsigned char>(0x104))at<float>(0x6ac)=-at<float>(0x73c);}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){dispatch_character_wave_handle(20);at<int>(0x180)=1;}if(entry(3))set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){counter(200,120);phase_counter(50);}
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(16);
            for(int angle=0;angle<360;angle+=60){float p[3]={static_cast<float>(static_cast<double>(komachi_random(30))+angle+30.0),10.0f,2.0f};spawn_ring817(p,120);}
        }
    }

    __forceinline void primary825() {dispatch_character_wave_handle(14);float p[3]={static_cast<float>(at<float>(0x744)-at<short>(0x734)*25.0+25.0),7.0f,0.0f};spawn_offset(825,90,180.0,p,3);++at<short>(0x734);}
    __forceinline void ground825(int control) {
        landing();at<unsigned char>(0x17c)=3;if(sequence_index_13e<2 && !at<int>(control))at<unsigned char>(0x750)=0;
        if(at<short>(0x730)==1){
            if(!sequence_index_13e){if(!(at<short>(0x732)%6)){at<int>(0x180)=1;if(at<short>(0x734)<(at<signed char>(0x607)>=4)+3)primary825();}}
            else if(!(at<short>(0x732)%6)){
                at<int>(0x180)=1;int high=at<signed char>(0x607)>=4;
                if(at<short>(0x734)<high+3)primary825();
                else if(at<short>(0x736)<high+2){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(at<float>(0x744)-at<short>(0x736)*25.0+12.5),7.0f,0.0f};spawn_offset(825,90,180.0,p,3);++at<short>(0x736);}
            }++at<short>(0x732);
        }
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)){charge(10,135.0);return;}if(frame_index_140==5){at<short>(0x730)=1;counter(200,120);phase_counter(50);aim(-20.0f,10.0f);}}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){at<short>(0x730)=1;counter(200,120);phase_counter(50);aim(-20.0f,10.0f);}
    }
    __forceinline void aim_short() {
        float dx=static_cast<float>((peer()->at<float>(0xec)-at<float>(0xec))*static_cast<double>(facing()));float dy=peer()->at<float>(0xf0)-at<float>(0xf0);
        at<short>(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(komachi_atan(dy,dx))));
        if(at<short>(0x734)<-10)at<short>(0x734)=-10;if(at<short>(0x734)>10)at<short>(0x734)=10;
    }
    __forceinline void burst808() {
        float p[3];p[0]=static_cast<float>(static_cast<double>(at<short>(0x734))+30.0-static_cast<double>(komachi_random_u32()%60u));p[1]=15.0f;p[2]=static_cast<float>(komachi_random(4));spawn_offset(808,44,85.0,p,3);
    }
    __forceinline void ground827(int control) {
        landing();if(!at<int>(control))at<unsigned char>(0x750)=0;
        if(at<short>(0x730)==1){
            if(!sequence_index_13e){if(!(at<short>(0x732)%5) && at<short>(0x734)<1){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(at<short>(0x734)*-60.0),7.0f,0.0f};spawn_offset(827,90,180.0,p,3);++at<short>(0x734);}++at<short>(0x732);}
            if(sequence_index_13e==1){if(!(at<short>(0x732)%5) && at<short>(0x734)<2){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(45.0-at<short>(0x734)*90.0),7.0f,0.0f};spawn_offset(827,90,180.0,p,3);++at<short>(0x734);}++at<short>(0x732);}
        }
        if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3 && at<unsigned char>(0x750)){charge(10,135.0);return;}if(frame_index_140==4){at<short>(0x730)=1;counter(200,120);phase_counter(50);}}
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){at<short>(0x730)=1;counter(200,120);phase_counter(50);}
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        at<short>(0x48a)=40;event(23);int direction=at<unsigned char>(0x104);float y=static_cast<float>(at<float>(0xf0)+height);
        float x=xoff==0?at<float>(0xec):(xoff<0?static_cast<float>(at<float>(0xec)-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec))));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void ring817_at(float *p,int xoff) {
        for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;
            spawn_ring817(p,xoff);}
    }
    __forceinline void spell_ground_particles(int object,int random_range,double bias,double speed,float mode) {
        float p[3];p[0]=static_cast<float>(bias-static_cast<double>(komachi_random(random_range)));p[1]=static_cast<float>(static_cast<double>(komachi_random(5))+speed);p[2]=mode;
        spawn(object,static_cast<float>(80*facing()+static_cast<double>(at<float>(0xec))),at<float>(0xf0),at<unsigned char>(0x104),1,p,3);
    }
    __forceinline void grab_peer() {peer()->set_action_and_finalize(102);peer()->zero_motion();next_sequence_block();}

    __forceinline void ring902(float *p,float base,float jitter,int count,double step,double offset,bool reversed,float speed) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)){
            double angle=offset==0.0?n*step+base:n*step+base+offset;
            float coordinate=static_cast<float>(reversed?angle:angle+180.0);
            p[0]=static_cast<float>(reversed?angle+jitter+180.0:angle+jitter);p[1]=speed;p[2]=0.0f;
            int direction=at<unsigned char>(0x104);float neg=-coordinate;
            float y=static_cast<float>(komachi_sine(neg)*500.0+peer()->at<float>(0xf0)+100.0);
            float x=static_cast<float>(komachi_cosine(neg)*500.0*facing()+peer()->at<float>(0xec));spawn(902,x,y,direction,1,p,3);
        }
    }

    __forceinline void spawn_ring817(float *p,int xoff) {
        if(p[0]>=0.0f && p[0]<=180.0f){
            int direction=at<unsigned char>(0x104);float y=at<float>(0xf0);float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
            spawn(817,x,y,direction,1,p,3);
        }else{
            int direction=at<unsigned char>(0x104);float y=at<float>(0xf0);float x=xoff==0?at<float>(0xec):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(at<float>(0xec)));
            spawn(817,x,y,direction,-1,p,3);
        }
    }
};
}
