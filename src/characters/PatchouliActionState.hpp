#pragma once
#include <math.h>
#include <stddef.h>
namespace th105 {
class PatchouliActionStateView;
extern int g_match_identifier;
unsigned __cdecl patchouli_random(int);
unsigned __cdecl patchouli_random_u32();
float __cdecl patchouli_atan(float,float);
float __cdecl patchouli_sine(float);
float __cdecl patchouli_cosine(float);
float __cdecl patchouli_square(float);
float __fastcall patchouli_surface(PatchouliActionStateView *);
int __fastcall patchouli_on_surface(PatchouliActionStateView *);
struct PatchouliActionScratch { void reset(); };
// Pointer-only extension; never instantiate as a recovered complete Fighter.
class PatchouliActionStateView {
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
        if(x_ec>static_cast<double>(related_170->x_ec))facing_104=-1;
        if(x_ec<static_cast<double>(related_170->x_ec))facing_104=1;
    }
    __forceinline void dash_dust(bool reverse) {
        double base=x_ec+50.0;
        effect(124,static_cast<float>(base-static_cast<float>(patchouli_random_u32()%100u)),
               static_cast<float>(static_cast<float>(patchouli_random_u32()%200u)+y_f0),reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
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
            if(x_ec>related_170->x_ec) {
                facing_104=-1;velocity_x_f4=-velocity_x_f4;
                select_sequence(sequence);
            } else select_sequence(sequence);
        } else {
            if(x_ec<related_170->x_ec) {
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
    __forceinline void ring820_ground(float *p,int xoff) {
        for(int angle=0;angle<360;angle+=45) {
            p[0]=static_cast<float>(patchouli_random(30)+angle);
            if(p[0]<0.0f || p[0]<180.0f)word_730=1;else word_730=-1;
            spawn(820,patchouli_cosine(-p[0])*50.0+x_ec+static_cast<float>(xoff*facing_104),
                  patchouli_sine(-p[0])*50.0*0.25+y_f0,
                  static_cast<unsigned char>(facing_104),static_cast<unsigned char>(word_730),p,3);
        }
    }

    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((related_170->x_ec-x_ec)*static_cast<double>(facing_104));
        field_744=-patchouli_atan(related_170->y_f0-y_f0,dx);
        if(field_744<low)field_744=low;
        if(field_744>high)field_744=high;
    }
    __forceinline void charge_effect(int xoff,double height) {
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+height);
        float x=xoff<0?static_cast<float>(x_ec-static_cast<float>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        effect(62,x,y,direction,1);next_sequence_block();
    }
    __forceinline void fan800_emit(int xoff,double height,double spread) {
        field_180=1;phase_counter(10);
        float p[3]={static_cast<float>(-15*word_732+static_cast<double>(field_744)+spread),12.0f,0.0f};
        spawn_offset(800,xoff,height,p,3);dispatch_character_wave_handle(0);++word_732;
    }
    __forceinline void ground_fan_tick(int xoff,double height) {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {
                if(word_730%3==1 && word_732<3)fan800_emit(xoff,height,15.0);
            } else if(word_730%3==1 && word_732<5)fan800_emit(xoff,height,30.0);
        }
    }
    __forceinline void air_fan_tick(int xoff,double height) {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e && word_730%3==1 && word_732<3)fan800_emit(xoff,height,15.0);
            if(sequence_index_13e==1 && word_730%3==1 && word_732<5)fan800_emit(xoff,height,30.0);
        }
    }
    __forceinline void air_fan_motion() {
        if(sequence_index_13e==2)landing();
        if(!field_6c0)byte_750=0;
        if(sequence_index_13e<=1) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                zero_motion();select_sequence(2);y_f0=patchouli_surface(this);
            }
        }
    }

    __forceinline void burst800(int xoff,double height) {
        if(word_730>0) {
        word_730=0;
        if(!sequence_index_13e) {
            float p[3];float n=0.0f;field_180=1;
            for(;n<4.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*40.0-60.0);p[1]=15.0f;p[2]=2.0f;
                spawn_offset(800,xoff,height,p,3);
            }
        } else {
            float p[3];float n=0.0f;field_180=1;
            for(;n<7.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*25.0-75.0);p[1]=15.0f;p[2]=2.0f;
                spawn_offset(800,xoff,height,p,3);
            }
        }
        }
    }
    __forceinline void pair801_emit(int bound,double center,int xoff,double height) {
        field_180=1;phase_counter(5);
        float p[3]={static_cast<float>(static_cast<float>(patchouli_random(bound))-center),25.0f,6.0f};
        spawn_offset(801,xoff,height,p,3);p[2]=7.0f;spawn_offset(801,xoff,height,p,3);
        dispatch_character_wave_handle(2);++word_732;
    }
    __forceinline void pair801_tick(int xoff,double height) {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {
                if(word_730%2==1 && word_732<5)pair801_emit(16,8.0,xoff,height);
            } else if(sequence_index_13e==1 && word_730%2==1 && word_732<10)pair801_emit(30,15.0,xoff,height);
        }
    }
    __forceinline void circle801() {
        float p[3];p[1]=5.0f;p[2]=0.0f;
        for(int angle=0;angle<315;angle+=45){p[0]=static_cast<float>(angle);spawn_offset(801,100,140.0,p,3);}
        p[2]=2.0f;spawn_offset(801,100,140.0,p,3);
    }

    __forceinline void ground810_emit(float speed,float mode) {
        float p[3]={0.0f,speed,mode};spawn_offset(810,60,114.0,p,3);
        int direction=static_cast<unsigned char>(facing_104);
        effect(128,static_cast<float>(200*static_cast<signed char>(direction)+static_cast<double>(x_ec)),
               y_f0,direction,-1);
    }
    __forceinline void ring820_surface(float *p) {
        for(int angle=0;angle<360;angle+=45) {
            p[0]=static_cast<float>(patchouli_random(30)+angle);
            if(p[0]<0.0f || p[0]<180.0f)word_730=1;else word_730=-1;
            double wave=patchouli_sine(-p[0])*75.0*0.25;
            spawn(820,
                patchouli_cosine(-p[0])*75.0+x_ec,
                patchouli_surface(this)+wave,static_cast<unsigned char>(facing_104),static_cast<unsigned char>(word_730),p,3);
        }
    }
    __forceinline void orbit825(float *p) {
        spawn(825,(patchouli_cosine(-p[0])*200.0-100.0)*facing_104+x_ec,
              patchouli_sine(-p[0])*200.0+y_f0+100.0,
              static_cast<unsigned char>(facing_104),1,p,3);
    }

    __forceinline void spell_flash(int xoff,double height,int outcome) {
        word_48a=40;event(23);
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+height);
        float x=xoff<0?static_cast<float>(x_ec-static_cast<float>(-xoff*static_cast<signed char>(direction))):
            static_cast<float>(xoff*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        effect(115,x,y,direction,1);sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void orbit852(float *p,double radius) {
        spawn(852,patchouli_cosine(-p[0])*radius*facing_104+x_ec,
              patchouli_sine(p[0])*radius+(static_cast<double>(y_f0)+100.0),
              static_cast<unsigned char>(facing_104),1,p,3);
    }

    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<PatchouliActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }
    __forceinline void orbit900(float *p,float &angle) {
        spawn(900,patchouli_cosine(-angle)*150.0*facing_104+x_ec,
              patchouli_sine(-angle)*150.0+(static_cast<double>(y_f0)+100.0),
              static_cast<unsigned char>(facing_104),1,p,3);
    }

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x37];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x20];
    PatchouliActionStateView * field_168;
    unsigned char unknown_16c[0x4];
    PatchouliActionStateView * related_170;
    short word_174;
    unsigned char unknown_176[0x6];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char unknown_185[0x1];
    short word_186;
    unsigned char unknown_188[0x2f6];
    unsigned char byte_47e;
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
    signed char byte_605;
    signed char byte_606;
    signed char byte_607;
    signed char byte_608;
    signed char byte_609;
    signed char byte_60a;
    unsigned char unknown_60b[0x2];
    signed char byte_60d;
    unsigned char unknown_60e[0x47];
    unsigned char byte_655;
    unsigned char unknown_656[0x56];
    float field_6ac;
    unsigned char unknown_6b0[0x4];
    int field_6b4;
    int field_6b8;
    unsigned int field_6bc;
    unsigned int field_6c0;
    unsigned int field_6c4;
    int field_6c8;
    unsigned char unknown_6cc[0x60];
    unsigned char byte_72c;
    unsigned char unknown_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    unsigned char unknown_738[0x4];
    float field_73c;
    float field_740;
    float field_744;
    float field_748;
    float field_74c;
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
    short word_7a4;
    unsigned char unknown_7a6[0xa];
    short word_7b0;
    unsigned char unknown_7b2[0x2];
    float field_7b4;
};

typedef char check_x_ec[offsetof(PatchouliActionStateView,x_ec)==0xec?1:-1];
typedef char check_y_f0[offsetof(PatchouliActionStateView,y_f0)==0xf0?1:-1];
typedef char check_velocity_x_f4[offsetof(PatchouliActionStateView,velocity_x_f4)==0xf4?1:-1];
typedef char check_velocity_y_f8[offsetof(PatchouliActionStateView,velocity_y_f8)==0xf8?1:-1];
typedef char check_acceleration_y_100[offsetof(PatchouliActionStateView,acceleration_y_100)==0x100?1:-1];
typedef char check_facing_104[offsetof(PatchouliActionStateView,facing_104)==0x104?1:-1];
typedef char check_action_id_13c[offsetof(PatchouliActionStateView,action_id_13c)==0x13c?1:-1];
typedef char check_sequence_index_13e[offsetof(PatchouliActionStateView,sequence_index_13e)==0x13e?1:-1];
typedef char check_frame_index_140[offsetof(PatchouliActionStateView,frame_index_140)==0x140?1:-1];
typedef char check_frame_timer_142[offsetof(PatchouliActionStateView,frame_timer_142)==0x142?1:-1];
typedef char check_time_counter_144[offsetof(PatchouliActionStateView,time_counter_144)==0x144?1:-1];
typedef char check_field_168[offsetof(PatchouliActionStateView,field_168)==0x168?1:-1];
typedef char check_related_170[offsetof(PatchouliActionStateView,related_170)==0x170?1:-1];
typedef char check_word_174[offsetof(PatchouliActionStateView,word_174)==0x174?1:-1];
typedef char check_byte_17c[offsetof(PatchouliActionStateView,byte_17c)==0x17c?1:-1];
typedef char check_field_180[offsetof(PatchouliActionStateView,field_180)==0x180?1:-1];
typedef char check_byte_184[offsetof(PatchouliActionStateView,byte_184)==0x184?1:-1];
typedef char check_word_186[offsetof(PatchouliActionStateView,word_186)==0x186?1:-1];
typedef char check_byte_47e[offsetof(PatchouliActionStateView,byte_47e)==0x47e?1:-1];
typedef char check_byte_47f[offsetof(PatchouliActionStateView,byte_47f)==0x47f?1:-1];
typedef char check_word_482[offsetof(PatchouliActionStateView,word_482)==0x482?1:-1];
typedef char check_word_48a[offsetof(PatchouliActionStateView,word_48a)==0x48a?1:-1];
typedef char check_word_48c[offsetof(PatchouliActionStateView,word_48c)==0x48c?1:-1];
typedef char check_word_4a8[offsetof(PatchouliActionStateView,word_4a8)==0x4a8?1:-1];
typedef char check_word_4ac[offsetof(PatchouliActionStateView,word_4ac)==0x4ac?1:-1];
typedef char check_word_4ae[offsetof(PatchouliActionStateView,word_4ae)==0x4ae?1:-1];
typedef char check_field_4b8[offsetof(PatchouliActionStateView,field_4b8)==0x4b8?1:-1];
typedef char check_byte_604[offsetof(PatchouliActionStateView,byte_604)==0x604?1:-1];
typedef char check_byte_605[offsetof(PatchouliActionStateView,byte_605)==0x605?1:-1];
typedef char check_byte_606[offsetof(PatchouliActionStateView,byte_606)==0x606?1:-1];
typedef char check_byte_607[offsetof(PatchouliActionStateView,byte_607)==0x607?1:-1];
typedef char check_byte_608[offsetof(PatchouliActionStateView,byte_608)==0x608?1:-1];
typedef char check_byte_609[offsetof(PatchouliActionStateView,byte_609)==0x609?1:-1];
typedef char check_byte_60a[offsetof(PatchouliActionStateView,byte_60a)==0x60a?1:-1];
typedef char check_byte_60d[offsetof(PatchouliActionStateView,byte_60d)==0x60d?1:-1];
typedef char check_byte_655[offsetof(PatchouliActionStateView,byte_655)==0x655?1:-1];
typedef char check_field_6ac[offsetof(PatchouliActionStateView,field_6ac)==0x6ac?1:-1];
typedef char check_field_6b4[offsetof(PatchouliActionStateView,field_6b4)==0x6b4?1:-1];
typedef char check_field_6b8[offsetof(PatchouliActionStateView,field_6b8)==0x6b8?1:-1];
typedef char check_field_6bc[offsetof(PatchouliActionStateView,field_6bc)==0x6bc?1:-1];
typedef char check_field_6c0[offsetof(PatchouliActionStateView,field_6c0)==0x6c0?1:-1];
typedef char check_field_6c4[offsetof(PatchouliActionStateView,field_6c4)==0x6c4?1:-1];
typedef char check_field_6c8[offsetof(PatchouliActionStateView,field_6c8)==0x6c8?1:-1];
typedef char check_byte_72c[offsetof(PatchouliActionStateView,byte_72c)==0x72c?1:-1];
typedef char check_word_730[offsetof(PatchouliActionStateView,word_730)==0x730?1:-1];
typedef char check_word_732[offsetof(PatchouliActionStateView,word_732)==0x732?1:-1];
typedef char check_word_734[offsetof(PatchouliActionStateView,word_734)==0x734?1:-1];
typedef char check_word_736[offsetof(PatchouliActionStateView,word_736)==0x736?1:-1];
typedef char check_field_73c[offsetof(PatchouliActionStateView,field_73c)==0x73c?1:-1];
typedef char check_field_740[offsetof(PatchouliActionStateView,field_740)==0x740?1:-1];
typedef char check_field_744[offsetof(PatchouliActionStateView,field_744)==0x744?1:-1];
typedef char check_field_748[offsetof(PatchouliActionStateView,field_748)==0x748?1:-1];
typedef char check_field_74c[offsetof(PatchouliActionStateView,field_74c)==0x74c?1:-1];
typedef char check_byte_750[offsetof(PatchouliActionStateView,byte_750)==0x750?1:-1];
typedef char check_byte_751[offsetof(PatchouliActionStateView,byte_751)==0x751?1:-1];
typedef char check_word_764[offsetof(PatchouliActionStateView,word_764)==0x764?1:-1];
typedef char check_word_766[offsetof(PatchouliActionStateView,word_766)==0x766?1:-1];
typedef char check_word_768[offsetof(PatchouliActionStateView,word_768)==0x768?1:-1];
typedef char check_word_76a[offsetof(PatchouliActionStateView,word_76a)==0x76a?1:-1];
typedef char check_word_76c[offsetof(PatchouliActionStateView,word_76c)==0x76c?1:-1];
typedef char check_word_7a0[offsetof(PatchouliActionStateView,word_7a0)==0x7a0?1:-1];
typedef char check_word_7a2[offsetof(PatchouliActionStateView,word_7a2)==0x7a2?1:-1];
typedef char check_word_7a4[offsetof(PatchouliActionStateView,word_7a4)==0x7a4?1:-1];
typedef char check_word_7b0[offsetof(PatchouliActionStateView,word_7b0)==0x7b0?1:-1];
typedef char check_field_7b4[offsetof(PatchouliActionStateView,field_7b4)==0x7b4?1:-1];
}
