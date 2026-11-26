#pragma once
#include <stddef.h>
#include <deque>
#include "battle/SpellRuntime.hpp"
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
float __cdecl komachi_sine(float);
float __cdecl komachi_cosine(float);
float __fastcall komachi_surface(KomachiActionStateView *);
unsigned char __fastcall komachi_on_surface(KomachiActionStateView *);
struct KomachiActionScratch { void reset(); };
// Partial receiver; never instantiate as a recovered complete Fighter.
class KomachiActionStateView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short,int);
    virtual int set_action_and_finalize(short);
    virtual int select_sequence(int);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short);
    void dispatch_character_wave_handle(unsigned);
    void forward_hit_quantity(int,int,short,signed char);
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
    // Byte direction is a manager-proved call view; signed char matches target push -1 in 510/511.
    int spawn(int,float,float,signed char,int,const void *,int);
    void effect(int,float,float,unsigned char,int);
    void counter(short,int);
    int phase_counter(int);
    void texture(signed char,short);
    void finalize(int);
    void copy_health();
    void sequence_window(signed char,int,int);
    void secondary_cycle();
    void common_update();

    __forceinline KomachiActionStateView *peer() { return fighter_170; }
    __forceinline KomachiActionStateView *owner() { return fighter_168; }
    __forceinline int facing() { return facing_104; }
    __forceinline unsigned char ufacing() { return static_cast<unsigned char>(facing_104); }
    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<KomachiActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        effect(124,
               static_cast<float>(x_ec + 50.0 - static_cast<float>(komachi_random_u32()%100u)),
               static_cast<float>(static_cast<float>(komachi_random_u32()%200u)+y_f0),
               reverse?static_cast<unsigned char>(-facing_104):ufacing(),1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        effect(125,
               ahead?static_cast<float>(80*static_cast<signed char>(reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104))+static_cast<double>(x_ec)):x_ec,
               static_cast<float>(y_f0+height),
               reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        effect(126,x_ec,static_cast<float>(y_f0+height),
               reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        event(31);
    }

    __forceinline void idle_motion() {
        if(!byte_47e){zero_motion();}
        else{
            if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){zero_motion();byte_47e=0;}}
            if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f){zero_motion();byte_47e=0;}}
        }
    }
    __forceinline void normal_jump(float vx) {
        if(!sequence_index_13e){landing();if(!sequence_index_13e && !byte_47e)zero_motion();}
        if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}}
        advance();if(entry(1)){velocity_x_f4=vx;velocity_y_f8=15.0f;acceleration_y_100=0.6f;byte_47e=0;}
    }
    __forceinline void face_peer() {
        if(x_ec>static_cast<double>(peer()->x_ec))facing_104=-1;
        if(x_ec<static_cast<double>(peer()->x_ec))facing_104=1;
    }
    __forceinline void card_expiration() {
        field_644 = field_648 - accumulated_hit_quantity_178;
        if (field_644 <= 0 && action_id_13c >= 700 && field_752 == 1) {
            if ((facing_104 == 1 && x_ec > peer()->x_ec) ||
                (facing_104 == -1 && x_ec < peer()->x_ec))
                facing_104 = static_cast<signed char>(-facing_104);
            set_action_and_finalize(149);
            field_752 = 0;
            field_654 = 0;
            effect(68, x_ec, static_cast<float>(y_f0 + 100.0), ufacing(), 1);
        }
    }
    __forceinline void recovery_jump(float vx) {
        if(!sequence_index_13e || sequence_index_13e==3)landing();
        else{velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){y_f0=komachi_surface(this);zero_motion();select_sequence(3);return;}}
        if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
        if(sequence_index_13e==3 && frame_index_140==1 && !frame_timer_142)face_peer();
        if(entry(1)){velocity_y_f8=6.0f;velocity_x_f4=vx;acceleration_y_100=0.5f;}
    }

    __forceinline void high_jump(
        float vx, float vy, float gravity, bool clamp, bool floor_after) {
        if (!sequence_index_13e)
            landing();

        if (static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);
            y_f0 = komachi_surface(this);
            zero_motion();
            return;
        }

        if (!floor_after && (komachi_on_surface(this) || velocity_y_f8 > 0.0f))
            word_4ae = 2;
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (clamp && velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (floor_after && (komachi_on_surface(this) || velocity_y_f8 > 0.0f))
            word_4ae = 2;

        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f)
            select_sequence(2);
        advance();

        if (entry(1)) {
            velocity_x_f4 = vx;
            velocity_y_f8 = vy;
            acceleration_y_100 = gravity;
            byte_47e = 0;
            effect(63, x_ec, y_f0, ufacing(), 1);
        }
    }

    __forceinline void decelerate(double amount,bool clear) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-amount);
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;if(clear)byte_47e=0;}
    }
    __forceinline void normal301() {
        if(byte_47e)decelerate(0.5,true);
        if(velocity_x_f4>0.0f && frame_index_140>=7)decelerate(0.5,false);
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142){if(frame_index_140==4){event(29);byte_47e=0;}
            if(!frame_timer_142){if(frame_index_140==3)velocity_x_f4=10.0f;if(!frame_timer_142 && frame_index_140==7)velocity_x_f4=static_cast<float>(velocity_x_f4*0.25);}}
    }
    __forceinline void charge(int xoff,double height) {
        next_sequence_block();int direction=ufacing();float y=static_cast<float>(y_f0+height);
        float x=xoff<0?static_cast<float>(x_ec-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        effect(62,x,y,static_cast<unsigned char>(direction),1);
    }
    __forceinline void ring817() {
        event(29);
        for(int angle=0;angle<360;angle+=45){
            float p[3]={static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0)),10.0f,2.0f};
            spawn_ring817(p,228);
        }
    }
    __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
        int direction=ufacing();float y=static_cast<float>(y_f0+height);
        float x=xoff==0?x_ec:(xoff<0?static_cast<float>(x_ec-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec)));
        spawn(object,x,y,static_cast<signed char>(direction),1,p,count);
    }
    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((peer()->x_ec-x_ec)*static_cast<double>(facing_104));
        field_744=-komachi_atan(peer()->y_f0-y_f0,dx);
        if(field_744<low)field_744=low;if(field_744>high)field_744=high;
    }
    __forceinline void start800(float low,float high,bool early_flag) {
        phase_counter(30);if(early_flag)word_730=1;aim(low,high);word_730=1;counter(200,45);
    }
    __forceinline void stream800(int limit,double bias,int x,double y,bool reverse,bool narrow) {
        if(word_732%2==0 && word_734<limit){
            dispatch_character_wave_handle(0);float p[3];
            if(narrow){p[0]=static_cast<float>(field_744-static_cast<double>(word_734)+6.0);p[1]=static_cast<float>(word_734*1.5+9.0);}
            else if(reverse){p[0]=static_cast<float>(field_744-word_734*5.0+bias);p[1]=static_cast<float>(static_cast<double>(word_734)+10.0);}
            else{double step=word_734*5.0;p[0]=static_cast<float>(step+field_744-bias);p[1]=static_cast<float>(static_cast<double>(word_734)+10.0);}
            p[2]=static_cast<float>(word_734%3);spawn_offset(800,x,y,p,3);++word_734;
        }
        ++word_732;
    }
    __forceinline void ground800(bool reverse,float low,float high) {
        landing();if(!field_6c0)byte_750=0;
        if(word_730==1){if(!sequence_index_13e)stream800(6,15.0,113,128.0,reverse,false);if(sequence_index_13e==1)stream800(10,25.0,113,128.0,reverse,false);}
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e){
            if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(-35,155.0);return;}
            if(!frame_timer_142 && frame_index_140==5)start800(low,high,false);
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)start800(low,high,false);
    }
    __forceinline void emit801(float *p,double xoff,double yoff) {
        if(xoff==0.0) {
            spawn(801,
                  static_cast<float>(komachi_cosine(-p[0])*150.0*facing_104+x_ec),
                  static_cast<float>(komachi_sine(-p[0])*150.0+y_f0+yoff),
                  static_cast<unsigned char>(facing_104),1,p,3);
        } else {
            spawn(801,
                  static_cast<float>((komachi_cosine(-p[0])*150.0+xoff)*facing_104+x_ec),
                  static_cast<float>(komachi_sine(-p[0])*150.0+y_f0+yoff),
                  static_cast<unsigned char>(facing_104),1,p,3);
        }
    }
    __forceinline void fan801(double spread,double second,float second_speed,double xoff,double yoff,bool charged,float low,float high) {
        phase_counter(50);dispatch_character_wave_handle(2);field_180=1;counter(200,60);aim(low,high);
        float p[3]={static_cast<float>(field_744+spread),20.0f,2.0f};emit801(p,xoff,yoff);
        p[0]=static_cast<float>(field_744-spread);emit801(p,xoff,yoff);
        if(charged){p[0]=static_cast<float>(field_744+second);p[1]=second_speed;p[2]=2.0f;emit801(p,xoff,yoff);p[0]=static_cast<float>(field_744-second);emit801(p,xoff,yoff);}
    }

    __forceinline void skill_cost(int wave) {counter(200,120);phase_counter(50);dispatch_character_wave_handle(wave);}
    __forceinline void shot811(float mode,float extra) {
        float p[3]={0.0f,0.0f,mode};spawn(811,x_ec,y_f0,ufacing(),1,p,3);
        if(byte_608>=4){p[2]=extra;spawn(811,x_ec,y_f0,ufacing(),1,p,3);}skill_cost(16);
    }
    __forceinline void ground811(float mode,float extra) {
        landing();field_17c=4;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10)shot811(mode,extra);
    }
    __forceinline void stream815(double speed) {
        landing();field_17c=1;
        if(word_730==1){
            int limit=5;if(byte_605>=2)limit=6;if(byte_605>=4)limit=8;
            if(word_732<limit){
                if(!(word_734%3)){float p[3];p[0]=static_cast<float>(-80.0-static_cast<double>(static_cast<float>(komachi_random(20))));p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(50)))*static_cast<double>(0.1f)+speed);p[2]=0.0f;
                    spawn(815,static_cast<float>(113*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);++word_732;}
                ++word_734;
            }
        }
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==10){word_730=1;dispatch_character_wave_handle(12);counter(200,120);phase_counter(50);}
    }
    __forceinline bool sweep817(float mode,double speed,int timeout) {
        if(byte_184>0 && field_180 && ++word_730>=5){field_180=0;word_730=0;}
        if(!(time_counter_144%5)){dispatch_character_wave_handle(29);float p[3]={mode,static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(5)))+speed),0.0f};spawn_offset(817,120,140.0,p,3);}
        if(!(time_counter_144%15)){
            for(int angle=0;angle<360;angle+=60){float p[3]={static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(30)))+(static_cast<double>(angle)+30.0)),10.0f,2.0f};
                spawn_ring817(p,120);}
        }
        if(time_counter_144>=timeout){next_sequence_block();return true;}return false;
    }
    __forceinline void sweep_entry() {effect(127,x_ec,y_f0,ufacing(),-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);}

    __forceinline void pair821(float mode) {
        float p[3]={mode,10.0f,0.0f};spawn(821,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        p[2]=4.0f;spawn(821,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),-1,p,3);skill_cost(19);
    }
    __forceinline void ground821(int &control) {
        landing();field_17c=6;if(!control)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
        if(!sequence_index_13e){
            if(!frame_timer_142 && frame_index_140==7 && byte_750){charge(-100,164.0);return;}
            if(!frame_timer_142 && frame_index_140==10)pair821(1.0f);
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)pair821(2.0f);
    }
    __forceinline void accelerate822() {
        field_73c=static_cast<float>(field_73c+static_cast<double>(0.2f));double limit=byte_60e*1.5+4.0;
        if(limit<field_73c)field_73c=static_cast<float>(limit);
    }
    __forceinline void publish822() {
        KomachiActionStateView *other=peer();field_6ac=field_73c;
        if((other->x_ec>x_ec && other->facing_104==1) ||
           (other->x_ec<x_ec && other->facing_104==-1))field_6ac=-field_73c;
    }
    __forceinline void movement822(int &control,int &alternate,bool clear_first) {
        landing();field_17c=10;if(!control)byte_750=0;
        if(!sequence_index_13e && frame_index_140>=4){accelerate822();publish822();}
        if(sequence_index_13e==1){
            accelerate822();
            if(!(time_counter_144%3)){float p[3]={static_cast<float>(komachi_random(360)),static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(150)))+250.0),0.0f};spawn(822,x_ec,y_f0,facing_104,1,p,3);}
            publish822();
            if(time_counter_144>=10){
                if(!byte_750 || time_counter_144>=90){if(clear_first){field_180=0;next_sequence_block();}else{next_sequence_block();field_180=0;}return;}
                if(static_cast<unsigned int>(alternate)>0){select_sequence(3);field_180=0;return;}
            }
        }
        if(sequence_index_13e==2){field_73c=static_cast<float>(field_73c-static_cast<double>(0.4f));if(field_73c<0.0f)field_73c=0.0f;field_6ac=field_73c;if(facing_104==peer()->facing_104)field_6ac=-field_73c;}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){dispatch_character_wave_handle(20);field_180=1;}if(entry(3))set_action_and_finalize(0);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){counter(200,120);phase_counter(50);}
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(16);
            for(int angle=0;angle<360;angle+=60){float p[3]={static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(30)))+(static_cast<double>(angle)+30.0)),10.0f,2.0f};spawn_ring817(p,120);}
        }
    }

    __forceinline void primary825() {dispatch_character_wave_handle(14);float p[3]={static_cast<float>(field_744-word_734*25.0+25.0),7.0f,0.0f};spawn_offset(825,90,180.0,p,3);++word_734;}
    __forceinline void ground825(int &control) {
        landing();field_17c=3;if(sequence_index_13e<2 && !control)byte_750=0;
        if(word_730==1){
            if(!sequence_index_13e){if(!(word_732%6)){field_180=1;if(word_734<(byte_607>=4)+3)primary825();}}
            else if(!(word_732%6)){
                field_180=1;int high=byte_607>=4;
                if(word_734<high+3)primary825();
                else if(word_736<high+2){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(field_744-word_736*25.0+12.5),7.0f,0.0f};spawn_offset(825,90,180.0,p,3);++word_736;}
            }++word_732;
        }
        if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e){
            if(!frame_timer_142 && frame_index_140==3 && byte_750){charge(10,135.0);return;}
            if(!frame_timer_142 && frame_index_140==5){word_730=1;counter(200,120);phase_counter(50);aim(-20.0f,10.0f);}
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){word_730=1;counter(200,120);phase_counter(50);aim(-20.0f,10.0f);}
    }
    __forceinline void aim_short() {
        float dx=static_cast<float>((peer()->x_ec-x_ec)*static_cast<double>(facing_104));
        word_734=static_cast<short>(-static_cast<short>(static_cast<int>(komachi_atan(peer()->y_f0-y_f0,dx))));
        if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;
    }
    __forceinline void burst808() {
        float p[3];p[0]=static_cast<float>(static_cast<double>(word_734)+30.0-static_cast<double>(static_cast<float>(komachi_random_u32()%60u)));p[1]=15.0f;p[2]=static_cast<float>(komachi_random(4));spawn_offset(808,44,85.0,p,3);
    }
    __forceinline void ground827(int &control) {
        landing();if(!control)byte_750=0;
        if(word_730==1){
            if(!sequence_index_13e){if(!(word_732%5) && word_734<1){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(word_734*-60.0),7.0f,0.0f};spawn_offset(827,90,180.0,p,3);++word_734;}++word_732;}
            if(sequence_index_13e==1){if(!(word_732%5) && word_734<2){dispatch_character_wave_handle(14);float p[3]={static_cast<float>(45.0-word_734*90.0),7.0f,0.0f};spawn_offset(827,90,180.0,p,3);++word_734;}++word_732;}
        }
        if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
        if(!sequence_index_13e){
            if(!frame_timer_142 && frame_index_140==3 && byte_750){charge(10,135.0);return;}
            if(!frame_timer_142 && frame_index_140==4){word_730=1;counter(200,120);phase_counter(50);}
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){word_730=1;counter(200,120);phase_counter(50);}
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        word_48a=40;event(23);int direction=ufacing();float y=static_cast<float>(y_f0+height);
        float x=xoff==0?x_ec:(xoff<0?static_cast<float>(x_ec-(-xoff)*static_cast<signed char>(direction)):static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec)));
        effect(115,x,y,static_cast<unsigned char>(direction),1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void ring817_at(float *p,int xoff) {
        for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
            spawn_ring817(p,xoff);}
    }
    __forceinline void spell_ground_particles(int object,int random_range,double bias,double speed,float mode) {
        float p[3];p[0]=static_cast<float>(bias-static_cast<double>(static_cast<float>(komachi_random(random_range))));p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(5)))+speed);p[2]=mode;
        spawn(object,static_cast<float>(80*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
    }
    __forceinline void grab_peer() {peer()->set_action_and_finalize(102);peer()->zero_motion();next_sequence_block();}

    __forceinline void spawn_ring817(float *p,int xoff) {
        if(p[0]>=0.0f && p[0]<=180.0f){
            int direction=ufacing();float y=y_f0;float x=xoff==0?x_ec:static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(817,x,y,static_cast<signed char>(direction),1,p,3);
        }else{
            int direction=ufacing();float y=y_f0;float x=xoff==0?x_ec:static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(817,x,y,static_cast<signed char>(direction),-1,p,3);
        }
    }

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float field_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x27];
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x20];
    KomachiActionStateView *fighter_168;
    unsigned char unknown_16c[0x4];
    KomachiActionStateView *fighter_170;
    short word_174;
    unsigned char unknown_176[0x2];
    int accumulated_hit_quantity_178;
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char unknown_185;
    short word_186;
    unsigned char unknown_188[0x4];
    float field_18c;
    float field_190;
    unsigned char unknown_194[0x2ea];
    signed char byte_47e;
    unsigned char byte_47f;
    unsigned char unknown_480[0x2];
    short word_482;
    unsigned char unknown_484[0x6];
    short word_48a;
    short word_48c;
    unsigned char unknown_48e[0x1a];
    short word_4a8;
    unsigned char unknown_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char unknown_4b0[0x8];
    int field_4b8;
    unsigned char unknown_4bc[0x9e];
    signed char byte_55a;
    unsigned char unknown_55b;
    std::deque<FighterSequenceSlot> cards_55c;
    unsigned char unknown_570[0x95];
    signed char byte_605;
    unsigned char byte_606;
    signed char byte_607;
    signed char byte_608;
    signed char byte_609;
    unsigned char byte_60a;
    unsigned char unknown_60b;
    signed char byte_60c;
    unsigned char unknown_60d;
    signed char byte_60e;
    unsigned char unknown_60f[0x35];
    int field_644;
    int field_648;
    unsigned char unknown_64c[0x8];
    unsigned char field_654;
    unsigned char byte_655;
    unsigned char unknown_656[0x56];
    float field_6ac;
    unsigned char unknown_6b0[0x4];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char unknown_6cc[0x60];
    unsigned char byte_72c;
    unsigned char unknown_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char unknown_748[0x8];
    unsigned char byte_750;
    unsigned char unknown_751;
    unsigned char field_752;
    unsigned char unknown_753[0x11];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char unknown_76e[0x32];
    short word_7a0;
    short word_7a2;
    unsigned char unknown_7a4[0x4];
    int field_7a8;
};

typedef char check_komachi_x_ec[offsetof(KomachiActionStateView,x_ec)==0xec?1:-1];
typedef char check_komachi_y_f0[offsetof(KomachiActionStateView,y_f0)==0xf0?1:-1];
typedef char check_komachi_velocity_x_f4[offsetof(KomachiActionStateView,velocity_x_f4)==0xf4?1:-1];
typedef char check_komachi_velocity_y_f8[offsetof(KomachiActionStateView,velocity_y_f8)==0xf8?1:-1];
typedef char check_komachi_field_fc[offsetof(KomachiActionStateView,field_fc)==0xfc?1:-1];
typedef char check_komachi_acceleration_y_100[offsetof(KomachiActionStateView,acceleration_y_100)==0x100?1:-1];
typedef char check_komachi_facing_104[offsetof(KomachiActionStateView,facing_104)==0x104?1:-1];
typedef char check_komachi_field_12c[offsetof(KomachiActionStateView,field_12c)==0x12c?1:-1];
typedef char check_komachi_action_id_13c[offsetof(KomachiActionStateView,action_id_13c)==0x13c?1:-1];
typedef char check_komachi_sequence_index_13e[offsetof(KomachiActionStateView,sequence_index_13e)==0x13e?1:-1];
typedef char check_komachi_frame_index_140[offsetof(KomachiActionStateView,frame_index_140)==0x140?1:-1];
typedef char check_komachi_frame_timer_142[offsetof(KomachiActionStateView,frame_timer_142)==0x142?1:-1];
typedef char check_komachi_time_counter_144[offsetof(KomachiActionStateView,time_counter_144)==0x144?1:-1];
typedef char check_komachi_fighter_168[offsetof(KomachiActionStateView,fighter_168)==0x168?1:-1];
typedef char check_komachi_fighter_170[offsetof(KomachiActionStateView,fighter_170)==0x170?1:-1];
typedef char check_komachi_word_174[offsetof(KomachiActionStateView,word_174)==0x174?1:-1];
typedef char check_komachi_hit_178[offsetof(KomachiActionStateView,accumulated_hit_quantity_178)==0x178?1:-1];
typedef char check_komachi_field_17c[offsetof(KomachiActionStateView,field_17c)==0x17c?1:-1];
typedef char check_komachi_field_180[offsetof(KomachiActionStateView,field_180)==0x180?1:-1];
typedef char check_komachi_byte_184[offsetof(KomachiActionStateView,byte_184)==0x184?1:-1];
typedef char check_komachi_word_186[offsetof(KomachiActionStateView,word_186)==0x186?1:-1];
typedef char check_komachi_field_18c[offsetof(KomachiActionStateView,field_18c)==0x18c?1:-1];
typedef char check_komachi_field_190[offsetof(KomachiActionStateView,field_190)==0x190?1:-1];
typedef char check_komachi_byte_47e[offsetof(KomachiActionStateView,byte_47e)==0x47e?1:-1];
typedef char check_komachi_byte_47f[offsetof(KomachiActionStateView,byte_47f)==0x47f?1:-1];
typedef char check_komachi_word_482[offsetof(KomachiActionStateView,word_482)==0x482?1:-1];
typedef char check_komachi_word_48a[offsetof(KomachiActionStateView,word_48a)==0x48a?1:-1];
typedef char check_komachi_word_48c[offsetof(KomachiActionStateView,word_48c)==0x48c?1:-1];
typedef char check_komachi_word_4a8[offsetof(KomachiActionStateView,word_4a8)==0x4a8?1:-1];
typedef char check_komachi_word_4ac[offsetof(KomachiActionStateView,word_4ac)==0x4ac?1:-1];
typedef char check_komachi_word_4ae[offsetof(KomachiActionStateView,word_4ae)==0x4ae?1:-1];
typedef char check_komachi_field_4b8[offsetof(KomachiActionStateView,field_4b8)==0x4b8?1:-1];
typedef char check_komachi_byte_55a[offsetof(KomachiActionStateView,byte_55a)==0x55a?1:-1];
typedef char check_komachi_cards_55c[offsetof(KomachiActionStateView,cards_55c)==0x55c?1:-1];
typedef char check_komachi_byte_605[offsetof(KomachiActionStateView,byte_605)==0x605?1:-1];
typedef char check_komachi_byte_606[offsetof(KomachiActionStateView,byte_606)==0x606?1:-1];
typedef char check_komachi_byte_607[offsetof(KomachiActionStateView,byte_607)==0x607?1:-1];
typedef char check_komachi_byte_608[offsetof(KomachiActionStateView,byte_608)==0x608?1:-1];
typedef char check_komachi_byte_609[offsetof(KomachiActionStateView,byte_609)==0x609?1:-1];
typedef char check_komachi_byte_60a[offsetof(KomachiActionStateView,byte_60a)==0x60a?1:-1];
typedef char check_komachi_byte_60c[offsetof(KomachiActionStateView,byte_60c)==0x60c?1:-1];
typedef char check_komachi_byte_60e[offsetof(KomachiActionStateView,byte_60e)==0x60e?1:-1];
typedef char check_komachi_field_644[offsetof(KomachiActionStateView,field_644)==0x644?1:-1];
typedef char check_komachi_field_648[offsetof(KomachiActionStateView,field_648)==0x648?1:-1];
typedef char check_komachi_field_654[offsetof(KomachiActionStateView,field_654)==0x654?1:-1];
typedef char check_komachi_byte_655[offsetof(KomachiActionStateView,byte_655)==0x655?1:-1];
typedef char check_komachi_field_6ac[offsetof(KomachiActionStateView,field_6ac)==0x6ac?1:-1];
typedef char check_komachi_field_6b4[offsetof(KomachiActionStateView,field_6b4)==0x6b4?1:-1];
typedef char check_komachi_field_6b8[offsetof(KomachiActionStateView,field_6b8)==0x6b8?1:-1];
typedef char check_komachi_field_6bc[offsetof(KomachiActionStateView,field_6bc)==0x6bc?1:-1];
typedef char check_komachi_field_6c0[offsetof(KomachiActionStateView,field_6c0)==0x6c0?1:-1];
typedef char check_komachi_field_6c4[offsetof(KomachiActionStateView,field_6c4)==0x6c4?1:-1];
typedef char check_komachi_field_6c8[offsetof(KomachiActionStateView,field_6c8)==0x6c8?1:-1];
typedef char check_komachi_byte_72c[offsetof(KomachiActionStateView,byte_72c)==0x72c?1:-1];
typedef char check_komachi_word_730[offsetof(KomachiActionStateView,word_730)==0x730?1:-1];
typedef char check_komachi_word_732[offsetof(KomachiActionStateView,word_732)==0x732?1:-1];
typedef char check_komachi_word_734[offsetof(KomachiActionStateView,word_734)==0x734?1:-1];
typedef char check_komachi_word_736[offsetof(KomachiActionStateView,word_736)==0x736?1:-1];
typedef char check_komachi_word_738[offsetof(KomachiActionStateView,word_738)==0x738?1:-1];
typedef char check_komachi_field_73c[offsetof(KomachiActionStateView,field_73c)==0x73c?1:-1];
typedef char check_komachi_field_740[offsetof(KomachiActionStateView,field_740)==0x740?1:-1];
typedef char check_komachi_field_744[offsetof(KomachiActionStateView,field_744)==0x744?1:-1];
typedef char check_komachi_byte_750[offsetof(KomachiActionStateView,byte_750)==0x750?1:-1];
typedef char check_komachi_field_752[offsetof(KomachiActionStateView,field_752)==0x752?1:-1];
typedef char check_komachi_word_764[offsetof(KomachiActionStateView,word_764)==0x764?1:-1];
typedef char check_komachi_word_766[offsetof(KomachiActionStateView,word_766)==0x766?1:-1];
typedef char check_komachi_word_768[offsetof(KomachiActionStateView,word_768)==0x768?1:-1];
typedef char check_komachi_word_76a[offsetof(KomachiActionStateView,word_76a)==0x76a?1:-1];
typedef char check_komachi_word_76c[offsetof(KomachiActionStateView,word_76c)==0x76c?1:-1];
typedef char check_komachi_word_7a0[offsetof(KomachiActionStateView,word_7a0)==0x7a0?1:-1];
typedef char check_komachi_word_7a2[offsetof(KomachiActionStateView,word_7a2)==0x7a2?1:-1];
typedef char check_komachi_field_7a8[offsetof(KomachiActionStateView,field_7a8)==0x7a8?1:-1];
}
