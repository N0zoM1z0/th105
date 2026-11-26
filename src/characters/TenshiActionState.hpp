#pragma once
#include <math.h>
#include <stddef.h>
#include "battle/SpellRuntime.hpp"
#include "battle/PostSequenceTransition.hpp"
#include <deque>
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
#define ENTRY(seq) (time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==(seq))

class TenshiActionStateView;
struct InfoManager;
extern InfoManager *g_info_manager;
unsigned __cdecl tenshi_random(int);
unsigned __cdecl tenshi_random_u32();
float __cdecl tenshi_atan(float,float);
float __cdecl tenshi_sine(float);
float __cdecl tenshi_cosine(float);
float __cdecl tenshi_square(float);
float __fastcall tenshi_surface(TenshiActionStateView *);
int __fastcall tenshi_on_surface(TenshiActionStateView *);
void __cdecl tenshi_bgm_volume(int,int);
void __cdecl tenshi_fade_in(unsigned,int);
void __cdecl tenshi_fade_out(unsigned,int);
void __cdecl tenshi_play_bgm(const char *);
extern int g_match_identifier;
extern int g_fighter_state_4b8_default;
extern short g_tenshi_weather_counter;
extern unsigned char g_tenshi_weather_selector;
struct TenshiEvent130 {
    void trigger(int);
    void *pair(float,float);
    void music(int,int);
    void pair_mode(int,unsigned char);
};
struct TenshiActionScratch { void reset(); };
// Pointer-only receiver view, not a recovered complete Fighter allocation.
// Declaration-only helpers describe this caller; no callee implementation credit.
class TenshiActionStateView {
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
    signed char shared_first(signed char,float);
    signed char shared_second(signed char,float);


    __forceinline void dash_dust(bool reverse) {
        double base=x_ec+50.0;
        effect(124,
            static_cast<float>(base-static_cast<float>(tenshi_random_u32()%100u)),
            static_cast<float>(static_cast<float>(tenshi_random_u32()%200u)+y_f0),
            reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
    }
    __forceinline void dash_effects(bool reverse,double height,bool ahead) {
        effect(125,ahead?80*static_cast<signed char>(reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104))+x_ec:x_ec,
               y_f0+height,reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        effect(126,x_ec,y_f0+height,
               reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        event(31);
    }
    __forceinline void ground_face() {
        if(x_ec>related_170->x_ec) facing_104=-1;
        if(x_ec<related_170->x_ec) facing_104=1;
    }
    __forceinline void recover_air_sequence() {
        y_f0=tenshi_surface(this);zero_motion();select_sequence(2);
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<TenshiActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
    }



    __forceinline void aim(float low,float high) {
        float dx=static_cast<float>((related_170->x_ec-x_ec)*static_cast<double>(facing_104));
        field_744=-tenshi_atan(related_170->y_f0-y_f0,dx);
        if(field_744<low)field_744=low;
        if(field_744>high)field_744=high;
    }

    __forceinline void ring_801(double height) {
        float p[4];
        for(float n=0.0f;n<10.0f;n=static_cast<float>(n+1.0)) {
            p[3]=static_cast<float>(n*36.0+18.0);
            p[0]=static_cast<float>(p[3]+90.0);p[1]=15.0f;p[2]=0.0f;
            {
                spawn(801,tenshi_cosine(-p[3])*80.0*facing_104+x_ec,
                      tenshi_sine(-p[3])*80.0+y_f0+height,static_cast<unsigned char>(facing_104),1,p,3);
            }
            p[2]=2.0f;
            {
                spawn(801,tenshi_cosine(-p[3])*80.0*facing_104+x_ec,
                      tenshi_sine(-p[3])*80.0+y_f0+height,static_cast<unsigned char>(facing_104),1,p,3);
            }
        }
    }



    __forceinline void pair_821() {
        float p[3]={0.0f,1.0f,1.0f};
        spawn(821,x_ec,static_cast<float>(y_f0+200.0),static_cast<unsigned char>(facing_104),1,p,3);
        p[1]=-1.0f;p[2]=1.0f;
        spawn(821,x_ec,static_cast<float>(y_f0-100.0),static_cast<unsigned char>(facing_104),1,p,3);
        counter(200,120);phase_counter(50);
    }

    __forceinline void burst848(int offset,float mode) {
        float p[3]={0.0f,20.0f,mode};
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*45.0);
            if(p[0]>=0.0f && p[0]<=180.0f) {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(offset*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,1,p,3);
            } else {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(offset*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,-1,p,3);
            }
        }
    }
    __forceinline void dash825() {
        float p[3];
        p[0]=static_cast<float>(tenshi_random(360));
        p[1]=static_cast<float>(tenshi_random(6));p[2]=0.0f;
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+112.0);
        float x=static_cast<float>(36*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(825,x,y,direction,-1,p,3);
    }
    __forceinline void spell_flash(int xoff,double yoff,int outcome) {
        word_48a=40;event(23);
        effect(115,xoff==0?x_ec:(xoff<0?x_ec-static_cast<float>(-xoff*facing_104):
                    xoff*facing_104+x_ec),
               y_f0+yoff,static_cast<unsigned char>(facing_104),1);
        sequence_window(0,outcome,60);secondary_cycle();
    }
    __forceinline void burst_payload(float *p,float count,double step,int xoff,double yoff,bool surface,int object) {
        for(float n=0.0f;n<count;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*step);
            if(p[0]>=0.0f && p[0]<=180.0f) {
                int direction=static_cast<unsigned char>(facing_104);
                spawn(object,xoff==0?x_ec:static_cast<float>(xoff*facing_104+static_cast<double>(x_ec)),
                    surface?tenshi_surface(this):(yoff==0.0?y_f0:static_cast<float>(y_f0+yoff)),direction,1,p,3);
            } else {
                int direction=static_cast<unsigned char>(facing_104);
                spawn(object,xoff==0?x_ec:static_cast<float>(xoff*facing_104+static_cast<double>(x_ec)),
                    surface?tenshi_surface(this):(yoff==0.0?y_f0:static_cast<float>(y_f0+yoff)),direction,-1,p,3);
            }
        }
    }
    __forceinline void effect127_pair() {
        effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
        effect(127,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),-1);
    }

    __forceinline short card() {
        return cards_55c[0].record_id_00;
    }
    __forceinline TenshiEvent130 *event_owner() {
        return reinterpret_cast<TenshiEvent130 *>(reinterpret_cast<unsigned char *>(this)+0x130);
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
    unsigned char unknown_114[0x18];
    float orientation_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x20];
    TenshiActionStateView *field_168;
    unsigned char unknown_16c[4];
    TenshiActionStateView * related_170;
    short word_174;
    unsigned char unknown_176[0x6];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int field_180;
    unsigned char byte_184;
    unsigned char unknown_185[0x1];
    short word_186;
    unsigned char unknown_188[0x4];
    float field_18c;
    float field_190;
    unsigned char unknown_194[0x2ea];
    unsigned char byte_47e;
    unsigned char byte_47f;
    unsigned char unknown_480[0x2];
    short word_482;
    unsigned char unknown_484[0x6];
    short word_48a;
    short word_48c;
    short word_48e;
    unsigned char unknown_490[0x18];
    short word_4a8;
    unsigned char unknown_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char unknown_4b0[0x2];
    short word_4b2;
    unsigned char unknown_4b4[0x4];
    int field_4b8;
    unsigned char unknown_4bc[0x4];
    float field_4c0;
    float field_4c4;
    unsigned char unknown_4c8[0x21];
    unsigned char byte_4e9;
    unsigned char unknown_4ea[0x1];
    unsigned char byte_4eb;
    unsigned char byte_4ec;
    unsigned char unknown_4ed[0x6d];
    unsigned char byte_55a;
    unsigned char unknown_55b[0x1];
    std::deque<FighterSequenceSlot> cards_55c;
    unsigned char unknown_570[0x95];
    signed char byte_605;
    unsigned char unknown_606[0x1];
    signed char byte_607;
    unsigned char unknown_608[0x1];
    signed char byte_609;
    unsigned char unknown_60a[0x4b];
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
    unsigned char unknown_748[0x4];
    float field_74c;
    unsigned char byte_750;
    unsigned char byte_751;
    unsigned char unknown_752[0x12];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    short word_76e;
    unsigned char unknown_770[0x10];
    float field_780;
    float field_784;
    float field_788;
    short word_78c;
    unsigned char unknown_78e[0x12];
    short word_7a0;
    short word_7a2;
    float samples_7a4[8];
    unsigned char unknown_7c4[0x64];
    float field_828;
    unsigned char byte_82c;
    unsigned char unknown_82d[0x1];
    short word_82e;
    short word_830;
    unsigned char unknown_832[0x2];
    int field_834;
    int field_838;
    unsigned char unknown_83c[0x4];
    short word_840;
};

typedef char check_x_ec[offsetof(TenshiActionStateView,x_ec)==0xec?1:-1];
typedef char check_y_f0[offsetof(TenshiActionStateView,y_f0)==0xf0?1:-1];
typedef char check_velocity_x_f4[offsetof(TenshiActionStateView,velocity_x_f4)==0xf4?1:-1];
typedef char check_velocity_y_f8[offsetof(TenshiActionStateView,velocity_y_f8)==0xf8?1:-1];
typedef char check_acceleration_y_100[offsetof(TenshiActionStateView,acceleration_y_100)==0x100?1:-1];
typedef char check_facing_104[offsetof(TenshiActionStateView,facing_104)==0x104?1:-1];
typedef char check_byte_113[offsetof(TenshiActionStateView,byte_113)==0x113?1:-1];
typedef char check_orientation_12c[offsetof(TenshiActionStateView,orientation_12c)==0x12c?1:-1];
typedef char check_action_id_13c[offsetof(TenshiActionStateView,action_id_13c)==0x13c?1:-1];
typedef char check_sequence_index_13e[offsetof(TenshiActionStateView,sequence_index_13e)==0x13e?1:-1];
typedef char check_frame_index_140[offsetof(TenshiActionStateView,frame_index_140)==0x140?1:-1];
typedef char check_frame_timer_142[offsetof(TenshiActionStateView,frame_timer_142)==0x142?1:-1];
typedef char check_time_counter_144[offsetof(TenshiActionStateView,time_counter_144)==0x144?1:-1];
typedef char check_related_170[offsetof(TenshiActionStateView,related_170)==0x170?1:-1];
typedef char check_word_174[offsetof(TenshiActionStateView,word_174)==0x174?1:-1];
typedef char check_byte_17c[offsetof(TenshiActionStateView,byte_17c)==0x17c?1:-1];
typedef char check_field_180[offsetof(TenshiActionStateView,field_180)==0x180?1:-1];
typedef char check_byte_184[offsetof(TenshiActionStateView,byte_184)==0x184?1:-1];
typedef char check_word_186[offsetof(TenshiActionStateView,word_186)==0x186?1:-1];
typedef char check_field_18c[offsetof(TenshiActionStateView,field_18c)==0x18c?1:-1];
typedef char check_field_190[offsetof(TenshiActionStateView,field_190)==0x190?1:-1];
typedef char check_byte_47e[offsetof(TenshiActionStateView,byte_47e)==0x47e?1:-1];
typedef char check_byte_47f[offsetof(TenshiActionStateView,byte_47f)==0x47f?1:-1];
typedef char check_word_482[offsetof(TenshiActionStateView,word_482)==0x482?1:-1];
typedef char check_word_48a[offsetof(TenshiActionStateView,word_48a)==0x48a?1:-1];
typedef char check_word_48c[offsetof(TenshiActionStateView,word_48c)==0x48c?1:-1];
typedef char check_word_48e[offsetof(TenshiActionStateView,word_48e)==0x48e?1:-1];
typedef char check_word_4a8[offsetof(TenshiActionStateView,word_4a8)==0x4a8?1:-1];
typedef char check_word_4ac[offsetof(TenshiActionStateView,word_4ac)==0x4ac?1:-1];
typedef char check_word_4ae[offsetof(TenshiActionStateView,word_4ae)==0x4ae?1:-1];
typedef char check_word_4b2[offsetof(TenshiActionStateView,word_4b2)==0x4b2?1:-1];
typedef char check_field_4b8[offsetof(TenshiActionStateView,field_4b8)==0x4b8?1:-1];
typedef char check_field_4c0[offsetof(TenshiActionStateView,field_4c0)==0x4c0?1:-1];
typedef char check_field_4c4[offsetof(TenshiActionStateView,field_4c4)==0x4c4?1:-1];
typedef char check_byte_4e9[offsetof(TenshiActionStateView,byte_4e9)==0x4e9?1:-1];
typedef char check_byte_4eb[offsetof(TenshiActionStateView,byte_4eb)==0x4eb?1:-1];
typedef char check_byte_4ec[offsetof(TenshiActionStateView,byte_4ec)==0x4ec?1:-1];
typedef char check_byte_55a[offsetof(TenshiActionStateView,byte_55a)==0x55a?1:-1];
typedef char check_cards_55c[offsetof(TenshiActionStateView,cards_55c)==0x55c?1:-1];
typedef char check_byte_605[offsetof(TenshiActionStateView,byte_605)==0x605?1:-1];
typedef char check_byte_607[offsetof(TenshiActionStateView,byte_607)==0x607?1:-1];
typedef char check_byte_609[offsetof(TenshiActionStateView,byte_609)==0x609?1:-1];
typedef char check_byte_655[offsetof(TenshiActionStateView,byte_655)==0x655?1:-1];
typedef char check_field_6b4[offsetof(TenshiActionStateView,field_6b4)==0x6b4?1:-1];
typedef char check_field_6b8[offsetof(TenshiActionStateView,field_6b8)==0x6b8?1:-1];
typedef char check_field_6bc[offsetof(TenshiActionStateView,field_6bc)==0x6bc?1:-1];
typedef char check_field_6c0[offsetof(TenshiActionStateView,field_6c0)==0x6c0?1:-1];
typedef char check_field_6c4[offsetof(TenshiActionStateView,field_6c4)==0x6c4?1:-1];
typedef char check_field_6c8[offsetof(TenshiActionStateView,field_6c8)==0x6c8?1:-1];
typedef char check_byte_72c[offsetof(TenshiActionStateView,byte_72c)==0x72c?1:-1];
typedef char check_word_730[offsetof(TenshiActionStateView,word_730)==0x730?1:-1];
typedef char check_word_732[offsetof(TenshiActionStateView,word_732)==0x732?1:-1];
typedef char check_word_734[offsetof(TenshiActionStateView,word_734)==0x734?1:-1];
typedef char check_word_736[offsetof(TenshiActionStateView,word_736)==0x736?1:-1];
typedef char check_word_738[offsetof(TenshiActionStateView,word_738)==0x738?1:-1];
typedef char check_field_73c[offsetof(TenshiActionStateView,field_73c)==0x73c?1:-1];
typedef char check_field_740[offsetof(TenshiActionStateView,field_740)==0x740?1:-1];
typedef char check_field_744[offsetof(TenshiActionStateView,field_744)==0x744?1:-1];
typedef char check_field_74c[offsetof(TenshiActionStateView,field_74c)==0x74c?1:-1];
typedef char check_byte_750[offsetof(TenshiActionStateView,byte_750)==0x750?1:-1];
typedef char check_byte_751[offsetof(TenshiActionStateView,byte_751)==0x751?1:-1];
typedef char check_word_764[offsetof(TenshiActionStateView,word_764)==0x764?1:-1];
typedef char check_word_766[offsetof(TenshiActionStateView,word_766)==0x766?1:-1];
typedef char check_word_768[offsetof(TenshiActionStateView,word_768)==0x768?1:-1];
typedef char check_word_76a[offsetof(TenshiActionStateView,word_76a)==0x76a?1:-1];
typedef char check_word_76c[offsetof(TenshiActionStateView,word_76c)==0x76c?1:-1];
typedef char check_word_76e[offsetof(TenshiActionStateView,word_76e)==0x76e?1:-1];
typedef char check_field_780[offsetof(TenshiActionStateView,field_780)==0x780?1:-1];
typedef char check_field_784[offsetof(TenshiActionStateView,field_784)==0x784?1:-1];
typedef char check_field_788[offsetof(TenshiActionStateView,field_788)==0x788?1:-1];
typedef char check_word_78c[offsetof(TenshiActionStateView,word_78c)==0x78c?1:-1];
typedef char check_word_7a0[offsetof(TenshiActionStateView,word_7a0)==0x7a0?1:-1];
typedef char check_word_7a2[offsetof(TenshiActionStateView,word_7a2)==0x7a2?1:-1];
typedef char check_samples_7a4[offsetof(TenshiActionStateView,samples_7a4)==0x7a4?1:-1];
typedef char check_field_828[offsetof(TenshiActionStateView,field_828)==0x828?1:-1];
typedef char check_byte_82c[offsetof(TenshiActionStateView,byte_82c)==0x82c?1:-1];
typedef char check_word_82e[offsetof(TenshiActionStateView,word_82e)==0x82e?1:-1];
typedef char check_word_830[offsetof(TenshiActionStateView,word_830)==0x830?1:-1];
typedef char check_field_834[offsetof(TenshiActionStateView,field_834)==0x834?1:-1];
typedef char check_field_838[offsetof(TenshiActionStateView,field_838)==0x838?1:-1];
typedef char check_word_840[offsetof(TenshiActionStateView,word_840)==0x840?1:-1];
}

namespace th105 { typedef char check_tenshi_168[offsetof(TenshiActionStateView,field_168)==0x168?1:-1]; }
