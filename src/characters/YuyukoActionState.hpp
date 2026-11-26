#pragma once
#include <math.h>
#include <stddef.h>
namespace th105 {
class YuyukoActionStateView;
extern int g_match_identifier;
unsigned __cdecl yuyuko_random(int);
unsigned __cdecl yuyuko_random_u32();
float __cdecl yuyuko_atan(float,float);
float __cdecl yuyuko_sine(float);
float __cdecl yuyuko_cosine(float);
float __cdecl yuyuko_square(float);
float __fastcall yuyuko_surface(YuyukoActionStateView *);
int __fastcall yuyuko_on_surface(YuyukoActionStateView *);
struct YuyukoActionScratch { void reset(); };
// Partial receiver; never instantiate as a recovered complete Fighter.
class YuyukoActionStateView {
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
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    unsigned char advance();
    void zero_motion();
    void event(unsigned);
    void layout(float);
    void effect(int,float,float,unsigned char,int);
    int spawn(int,float,float,signed char,int,const void *,int);
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
        if(!byte_47e)zero_motion();
        else {
        if(velocity_x_f4>0.0f) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
            if(velocity_x_f4<0.0f){zero_motion();byte_47e=0;}
        }
        if(velocity_x_f4<0.0f) {
            velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);
            if(velocity_x_f4>0.0f){zero_motion();byte_47e=0;}
        }
        }
    }
    __forceinline void ground_face() {
        if(x_ec>static_cast<double>(peer()->x_ec))facing_104=-1;
        if(x_ec<static_cast<double>(peer()->x_ec))facing_104=1;
    }
    __forceinline void dash_dust(bool reverse) {
        double base=x_ec+50.0;
        effect(124,static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%100u)),
               static_cast<float>(static_cast<float>(yuyuko_random_u32()%200u)+y_f0),reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        effect(125,ahead?80*static_cast<signed char>(reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104))+x_ec:x_ec,
               y_f0+height,reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        effect(126,x_ec,y_f0+height,
               reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        event(31);
    }
    __forceinline void release_flight(int sequence) {
        if(static_cast<unsigned char>(facing_104)==1) {
            if(x_ec>peer()->x_ec) {
                facing_104=-1;velocity_x_f4=-velocity_x_f4;
                select_sequence(sequence);
            } else select_sequence(sequence);
        } else {
            if(x_ec<peer()->x_ec) {
                facing_104=-facing_104;
                velocity_x_f4=-velocity_x_f4;
                select_sequence(sequence);
            } else select_sequence(sequence);
        }
    }

    __forceinline void spawn_offset(int object,int xoff,double yoff,float *p,int count) {
        int direction=static_cast<unsigned char>(facing_104);
        float y=yoff==0.0?y_f0:(yoff<0.0?static_cast<float>(y_f0-(-yoff)):static_cast<float>(y_f0+yoff));
        float x=xoff==0?x_ec:(xoff<0?
            static_cast<float>(x_ec-static_cast<float>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec)));
        spawn(object,x,y,direction,1,p,count);
    }
    __forceinline YuyukoActionStateView *peer() { return fighter_170; }
    __forceinline YuyukoActionStateView *owner() { return fighter_168; }
    __forceinline int facing() { return facing_104; }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<YuyukoActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void decelerate(double amount,bool clear) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-amount);
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;if(clear)byte_47e=0;}
    }
    __forceinline void mode848(float mode,int xoff=0,double height=0.0) {
        float p[3]={0.0f,0.0f,mode};spawn_offset(848,xoff,height,p,3);
    }

    __forceinline void charge_flash(int xoff,double height) {
        next_sequence_block();
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+height);
        float x=static_cast<float>(x_ec-static_cast<float>(-xoff*static_cast<signed char>(direction)));
        effect(62,x,y,direction,1);
    }
    __forceinline void aim_fan() {
        float dx=static_cast<float>((peer()->x_ec-x_ec)*static_cast<double>(facing()));
        word_734=static_cast<short>(-static_cast<short>(static_cast<int>(yuyuko_atan(peer()->y_f0-y_f0,dx))));
        if(word_734<-20)word_734=-20;
        if(word_734>20)word_734=20;
        word_730=1;counter(200,45);
    }

    __forceinline void fan_charge() {
        effect(62,x_ec,static_cast<float>(y_f0+150.0),static_cast<unsigned char>(facing_104),1);
        next_sequence_block();
    }

    __forceinline void circle801(float *p) {
        spawn(801,static_cast<float>(yuyuko_cosine(-p[0])*100.0*facing_104+x_ec),
              static_cast<float>(yuyuko_sine(p[0])*100.0+y_f0+100.0),
              static_cast<unsigned char>(facing_104),1,p,3);
    }

    __forceinline void spread810_loop(float *p,double base,int limit) {
        for(int n=0;n<limit;n+=10){p[0]=static_cast<float>(base-n);spawn_offset(810,38,177.0,p,3);}
    }
    __forceinline void spread810(double base) {
        float p[3];p[1]=6.0f;p[2]=12.0f;
        if(byte_604>=4)spread810_loop(p,base,60);
        else if(byte_604>=1)spread810_loop(p,base,50);
        else spread810_loop(p,base,40);
        phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);
    }
    __forceinline void shot811(float angle) {
        float p[3];p[1]=6.0f;p[2]=12.0f;p[0]=angle;
        spawn_offset(811,38,177.0,p,3);phase_counter(50);counter(200,120);dispatch_character_wave_handle(6);
    }

    __forceinline void arc812_emit(float limit,double angle_scale,double speed_scale) {
        if(field_740<limit) {
            float p[4];p[0]=static_cast<float>(80.0-field_740*9.0);
            p[1]=static_cast<float>(yuyuko_sine(static_cast<float>(field_740*angle_scale))*speed_scale+2.0);
            p[2]=0.0f;p[3]=field_740;
            spawn(812,static_cast<float>((yuyuko_cosine(-p[0])*100.0+(field_740*5.0-85.0))*facing_104+x_ec),
                  static_cast<float>(yuyuko_sine(-p[0])*40.0+(static_cast<double>(y_f0)+120.0)),
                  static_cast<unsigned char>(facing_104),1,p,4);
        }
        field_740=static_cast<float>(field_740+1.0);
    }

    __forceinline void spread815(int step,double bias,bool ground_first) {
        field_180=1;float p[3]={0.0f,0.0f,0.0f};spawn_offset(815,95,150.0,p,3);p[2]=1.0f;
        for(int n=0;n<step*5;n+=step){p[0]=static_cast<float>(n-bias);spawn_offset(815,95,150.0,p,3);}
        if(ground_first){phase_counter(50);dispatch_character_wave_handle(12);}else{dispatch_character_wave_handle(12);phase_counter(50);}
        counter(200,120);
    }

    __forceinline void ring820(float mode) {
        phase_counter(50);counter(200,120);dispatch_character_wave_handle(13);field_180=1;
        float p[3];int angle=0;
        for(int n=0;angle<360;++n,angle+=60) {
            p[0]=static_cast<float>(angle);p[1]=300.0f;p[2]=mode;
            spawn(820,static_cast<float>((yuyuko_cosine(static_cast<float>(static_cast<float>(n)*60.0))*300.0+50.0)*facing_104+x_ec),
                  static_cast<float>(yuyuko_sine(static_cast<float>(static_cast<float>(n)-6.0))*300.0+(y_f0+170.0)),
                  static_cast<unsigned char>(facing_104),1,p,3);
        }
    }

    __forceinline void petal826(int xoff,double height) {
        float p[3]={static_cast<float>(yuyuko_random(360)),0.0f,0.0f};spawn_offset(826,xoff,height,p,3);
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        word_48a=40;event(23);
        effect(115,xoff==0?x_ec:xoff<0?static_cast<float>(x_ec-static_cast<float>(-xoff*facing_104)):
               static_cast<float>(xoff*facing_104+static_cast<double>(x_ec)),
               static_cast<float>(y_f0+height),static_cast<unsigned char>(facing_104),1);
        sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void orbit_spell(int object,float *p,bool reverse) {
        if(reverse) {
            spawn(object,static_cast<float>(x_ec-yuyuko_cosine(-p[0])*100.0*facing_104),
                  static_cast<float>(yuyuko_sine(-p[0])*100.0+y_f0+100.0),
                  static_cast<unsigned char>(-facing_104),1,p,3);
        } else {
            spawn(object,static_cast<float>(yuyuko_cosine(-p[0])*100.0*facing_104+x_ec),
                  static_cast<float>(yuyuko_sine(-p[0])*100.0+y_f0+100.0),
                  static_cast<unsigned char>(facing_104),1,p,3);
        }
    }
    __forceinline void ring_spell(int object,bool growing) {
        float p[3];
        for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)) {
            double angle=n*30.0;
            p[0]=static_cast<float>(angle);p[1]=growing?static_cast<float>(field_740+4.0):4.0f;p[2]=0.0f;orbit_spell(object,p,false);
            p[0]=static_cast<float>(angle);p[1]=growing?static_cast<float>(field_740+4.0):4.0f;p[2]=0.0f;orbit_spell(object,p,true);
            p[0]=static_cast<float>(angle+15.0);p[1]=growing?static_cast<float>(field_740+7.0):7.0f;p[2]=2.0f;orbit_spell(object,p,false);
            p[0]=static_cast<float>(angle+15.0);p[1]=growing?static_cast<float>(field_740+7.0):7.0f;p[2]=2.0f;orbit_spell(object,p,true);
        }
        dispatch_character_wave_handle(50);
    }
    __forceinline void pair857(bool air) {
        float radius=static_cast<float>(static_cast<float>(yuyuko_random(125))+50.0);
        float height=static_cast<float>(word_730*60.0+100.0);
        float p[3]={static_cast<float>(5.0-static_cast<float>(yuyuko_random(10))),35.0f,12.0f};
        spawn(857,static_cast<float>(facing()*static_cast<double>(radius)+x_ec),air?static_cast<float>(y_f0+height):height,static_cast<unsigned char>(facing_104),-1,p,3);
        spawn(857,static_cast<float>(x_ec-facing()*static_cast<double>(radius)),air?static_cast<float>(y_f0+height):height,static_cast<unsigned char>(facing_104),1,p,3);
        dispatch_character_wave_handle(16);++word_730;
    }
    __forceinline void difficulty900(float *p,bool every_wave) {
        float phase=static_cast<float>(yuyuko_random(360));if(!every_wave)dispatch_character_wave_handle(13);
        int angle=0;
        for(int n=0;angle<360;++n,angle+=40) {
            if(every_wave)dispatch_character_wave_handle(13);
            p[0]=static_cast<float>(static_cast<double>(angle)+phase);p[1]=700.0f;p[2]=0.0f;
            spawn(900,static_cast<float>((yuyuko_cosine(static_cast<float>(static_cast<float>(n)*60.0))*300.0+50.0)*facing_104+x_ec),
                  static_cast<float>(yuyuko_sine(static_cast<float>(static_cast<float>(n)-6.0))*300.0+(y_f0+170.0)),
                  static_cast<unsigned char>(facing_104),1,p,3);
        }
    }
    __forceinline void difficulty901(float *p,int period,double turn) {
        if(!time_counter_144)field_740=static_cast<float>(yuyuko_random(360));
        if(time_counter_144%period==0 && field_73c<=100.0f) {
        dispatch_character_wave_handle(10);p[0]=static_cast<float>(field_73c*turn+field_740);p[1]=6.0f;p[2]=0.0f;
        spawn_offset(901,0,120.0,p,3);p[2]=5.0f;spawn_offset(901,0,120.0,p,3);field_73c=static_cast<float>(field_73c+1.0);
        }
    }
    __forceinline void fade_alpha() {
        if(sequence_index_13e==1){if(byte_113>=6)byte_113-=6;else byte_113=0;}
        if(sequence_index_13e==3){if(byte_113<=249)byte_113+=6;else byte_113=255;}
    }
    __forceinline void finish_story_state() {
        byte_655=1;finalize(-1);texture(2,-1);copy_health();word_76c=0;word_76a=1;
        word_766=0;word_768=0;word_764=0;event(23);
    }

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0xe];
    unsigned char byte_113;
    unsigned char unknown_114[0x28];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x20];
    YuyukoActionStateView * fighter_168;
    unsigned char unknown_16c[0x4];
    YuyukoActionStateView * fighter_170;
    short word_174;
    unsigned char unknown_176[0x6];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int field_180;
    unsigned char unknown_184[0x2];
    short word_186;
    unsigned char unknown_188[0x2f6];
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
    unsigned char unknown_4bc[0x148];
    signed char byte_604;
    unsigned char unknown_605[0x5];
    signed char byte_60a;
    unsigned char unknown_60b[0x4a];
    unsigned char byte_655;
    unsigned char unknown_656[0x5e];
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
    unsigned char byte_751;
    unsigned char unknown_752[0x12];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char unknown_76e[0x32];
    short word_7a0;
    short word_7a2;
};
typedef char check_yuyuko_x_ec[offsetof(YuyukoActionStateView,x_ec)==0xec?1:-1];
typedef char check_yuyuko_y_f0[offsetof(YuyukoActionStateView,y_f0)==0xf0?1:-1];
typedef char check_yuyuko_velocity_x_f4[offsetof(YuyukoActionStateView,velocity_x_f4)==0xf4?1:-1];
typedef char check_yuyuko_velocity_y_f8[offsetof(YuyukoActionStateView,velocity_y_f8)==0xf8?1:-1];
typedef char check_yuyuko_acceleration_y_100[offsetof(YuyukoActionStateView,acceleration_y_100)==0x100?1:-1];
typedef char check_yuyuko_facing_104[offsetof(YuyukoActionStateView,facing_104)==0x104?1:-1];
typedef char check_yuyuko_byte_113[offsetof(YuyukoActionStateView,byte_113)==0x113?1:-1];
typedef char check_yuyuko_action_id_13c[offsetof(YuyukoActionStateView,action_id_13c)==0x13c?1:-1];
typedef char check_yuyuko_sequence_index_13e[offsetof(YuyukoActionStateView,sequence_index_13e)==0x13e?1:-1];
typedef char check_yuyuko_frame_index_140[offsetof(YuyukoActionStateView,frame_index_140)==0x140?1:-1];
typedef char check_yuyuko_frame_timer_142[offsetof(YuyukoActionStateView,frame_timer_142)==0x142?1:-1];
typedef char check_yuyuko_time_counter_144[offsetof(YuyukoActionStateView,time_counter_144)==0x144?1:-1];
typedef char check_yuyuko_fighter_168[offsetof(YuyukoActionStateView,fighter_168)==0x168?1:-1];
typedef char check_yuyuko_fighter_170[offsetof(YuyukoActionStateView,fighter_170)==0x170?1:-1];
typedef char check_yuyuko_word_174[offsetof(YuyukoActionStateView,word_174)==0x174?1:-1];
typedef char check_yuyuko_byte_17c[offsetof(YuyukoActionStateView,byte_17c)==0x17c?1:-1];
typedef char check_yuyuko_field_180[offsetof(YuyukoActionStateView,field_180)==0x180?1:-1];
typedef char check_yuyuko_word_186[offsetof(YuyukoActionStateView,word_186)==0x186?1:-1];
typedef char check_yuyuko_byte_47e[offsetof(YuyukoActionStateView,byte_47e)==0x47e?1:-1];
typedef char check_yuyuko_byte_47f[offsetof(YuyukoActionStateView,byte_47f)==0x47f?1:-1];
typedef char check_yuyuko_word_482[offsetof(YuyukoActionStateView,word_482)==0x482?1:-1];
typedef char check_yuyuko_word_48a[offsetof(YuyukoActionStateView,word_48a)==0x48a?1:-1];
typedef char check_yuyuko_word_48c[offsetof(YuyukoActionStateView,word_48c)==0x48c?1:-1];
typedef char check_yuyuko_word_4a8[offsetof(YuyukoActionStateView,word_4a8)==0x4a8?1:-1];
typedef char check_yuyuko_word_4ac[offsetof(YuyukoActionStateView,word_4ac)==0x4ac?1:-1];
typedef char check_yuyuko_word_4ae[offsetof(YuyukoActionStateView,word_4ae)==0x4ae?1:-1];
typedef char check_yuyuko_field_4b8[offsetof(YuyukoActionStateView,field_4b8)==0x4b8?1:-1];
typedef char check_yuyuko_byte_604[offsetof(YuyukoActionStateView,byte_604)==0x604?1:-1];
typedef char check_yuyuko_byte_60a[offsetof(YuyukoActionStateView,byte_60a)==0x60a?1:-1];
typedef char check_yuyuko_byte_655[offsetof(YuyukoActionStateView,byte_655)==0x655?1:-1];
typedef char check_yuyuko_field_6b4[offsetof(YuyukoActionStateView,field_6b4)==0x6b4?1:-1];
typedef char check_yuyuko_field_6b8[offsetof(YuyukoActionStateView,field_6b8)==0x6b8?1:-1];
typedef char check_yuyuko_field_6bc[offsetof(YuyukoActionStateView,field_6bc)==0x6bc?1:-1];
typedef char check_yuyuko_field_6c0[offsetof(YuyukoActionStateView,field_6c0)==0x6c0?1:-1];
typedef char check_yuyuko_field_6c4[offsetof(YuyukoActionStateView,field_6c4)==0x6c4?1:-1];
typedef char check_yuyuko_field_6c8[offsetof(YuyukoActionStateView,field_6c8)==0x6c8?1:-1];
typedef char check_yuyuko_byte_72c[offsetof(YuyukoActionStateView,byte_72c)==0x72c?1:-1];
typedef char check_yuyuko_word_730[offsetof(YuyukoActionStateView,word_730)==0x730?1:-1];
typedef char check_yuyuko_word_732[offsetof(YuyukoActionStateView,word_732)==0x732?1:-1];
typedef char check_yuyuko_word_734[offsetof(YuyukoActionStateView,word_734)==0x734?1:-1];
typedef char check_yuyuko_word_736[offsetof(YuyukoActionStateView,word_736)==0x736?1:-1];
typedef char check_yuyuko_word_738[offsetof(YuyukoActionStateView,word_738)==0x738?1:-1];
typedef char check_yuyuko_field_73c[offsetof(YuyukoActionStateView,field_73c)==0x73c?1:-1];
typedef char check_yuyuko_field_740[offsetof(YuyukoActionStateView,field_740)==0x740?1:-1];
typedef char check_yuyuko_field_744[offsetof(YuyukoActionStateView,field_744)==0x744?1:-1];
typedef char check_yuyuko_byte_750[offsetof(YuyukoActionStateView,byte_750)==0x750?1:-1];
typedef char check_yuyuko_byte_751[offsetof(YuyukoActionStateView,byte_751)==0x751?1:-1];
typedef char check_yuyuko_word_764[offsetof(YuyukoActionStateView,word_764)==0x764?1:-1];
typedef char check_yuyuko_word_766[offsetof(YuyukoActionStateView,word_766)==0x766?1:-1];
typedef char check_yuyuko_word_768[offsetof(YuyukoActionStateView,word_768)==0x768?1:-1];
typedef char check_yuyuko_word_76a[offsetof(YuyukoActionStateView,word_76a)==0x76a?1:-1];
typedef char check_yuyuko_word_76c[offsetof(YuyukoActionStateView,word_76c)==0x76c?1:-1];
typedef char check_yuyuko_word_7a0[offsetof(YuyukoActionStateView,word_7a0)==0x7a0?1:-1];
typedef char check_yuyuko_word_7a2[offsetof(YuyukoActionStateView,word_7a2)==0x7a2?1:-1];
}
