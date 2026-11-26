#include <stddef.h>
namespace th105 {
    class SakuyaActionStateView;
    bool __fastcall sakuya_state_13c_in_32_95(SakuyaActionStateView *);
    float __fastcall sakuya_surface(SakuyaActionStateView *);
    int __fastcall sakuya_on_surface(SakuyaActionStateView *);
    float __cdecl sakuya_absolute(float);
    float __cdecl sakuya_sine(float);
    float __cdecl sakuya_cosine(float);
    float __cdecl sakuya_atan(float,float);
    unsigned __cdecl sakuya_random_u32();
    int __cdecl sakuya_random(int);
    class SakuyaActionScratch {
        public:
        void reset();
        void set_oriented_components(float,float);
    };
    // Target-observed members for this root; related_170 uses the same partial view.
    class SakuyaActionStateView {
        public:
        virtual void scalar_delete_slot_00();
        virtual int set_action_sequence_and_finalize(short, int);
        virtual int set_action_and_finalize(short);
        virtual int select_sequence(int);
        virtual int reset_sequence();
        virtual unsigned char next_sequence_block();
        virtual int previous_sequence_block();
        virtual int set_sequence_frame(short);
        void dispatch_character_wave_handle(unsigned);
        __forceinline void idle_motion() {
            if(!byte_47e)zero_motion();
            else {
                if(velocity_x_f4>0.0) {
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<0.0) {
                        zero_motion();
                        byte_47e=0;
                    }
                }
                if(velocity_x_f4<0.0) {
                    velocity_x_f4+=0.5;
                    if(velocity_x_f4>0.0) {
                        zero_motion();
                        byte_47e=0;
                    }
                }
            }
        }
        void dispatch_action_state_vslot28();
        unsigned char landing();
        unsigned char advance();
        int crossed();
        void zero_motion();
        void effect(int,float,float,unsigned char,int);
        int spawn(int,float,float,signed char,int,const void *,int);
        signed char x_boundary();
        void layout(float);
        void event(unsigned);
        void copy_action_word();
        void finalize(int);
        void sequence_window(signed char,int,int);
        void texture(signed char,short);
        void counter(short,int);
        void secondary_cycle();
        int phase_counter(int);
        void flip();
        unsigned char directional(int);
        void common_update();
        signed char shared_first(signed char,float);
        signed char shared_second(signed char,float);
        unsigned char pad_004[0xe8];
        float x_ec;
        float y_f0;
        float velocity_x_f4;
        float velocity_y_f8;
        unsigned char pad_0fc[0x4];
        float acceleration_y_100;
        signed char facing_104;
        unsigned char pad_105[0xf];
        int field_114;
        unsigned char pad_118[0x14];
        float field_12c;
        unsigned char pad_130[0xc];
        short action_id_13c;
        short sequence_index_13e;
        short frame_index_140;
        short frame_timer_142;
        int time_counter_144;
        unsigned char pad_148[0x28];
        SakuyaActionStateView * related_170;
        short word_174;
        unsigned char pad_176[0x6];
        unsigned char byte_17c;
        unsigned char pad_17d[0x3];
        int field_180;
        signed char byte_184;
        unsigned char pad_185[0x1];
        short word_186;
        unsigned char pad_188[0x2f6];
        unsigned char byte_47e;
        unsigned char byte_47f;
        unsigned char pad_480[0x2];
        short word_482;
        unsigned char pad_484[0x6];
        short word_48a;
        short word_48c;
        unsigned char pad_48e[0x1a];
        short word_4a8;
        unsigned char pad_4aa[0x2];
        short word_4ac;
        short word_4ae;
        unsigned char pad_4b0[0x8];
        int field_4b8;
        unsigned char pad_4bc[0x149];
        signed char byte_605;
        signed char byte_606;
        signed char byte_607;
        unsigned char pad_608[0x2];
        signed char byte_60a;
        unsigned char pad_60b[0x4a];
        unsigned char byte_655;
        unsigned char pad_656[0x5e];
        int field_6b4;
        int field_6b8;
        int field_6bc;
        int field_6c0;
        int field_6c4;
        int field_6c8;
        unsigned char pad_6cc[0x60];
        unsigned char byte_72c;
        unsigned char pad_72d[0x3];
        short word_730;
        short word_732;
        short word_734;
        short word_736;
        short word_738;
        unsigned char pad_73a[0x2];
        float field_73c;
        float field_740;
        float field_744;
        unsigned char pad_748[0x8];
        unsigned char byte_750;
        unsigned char byte_751;
        unsigned char pad_752[0x12];
        short word_764;
        short word_766;
        short word_768;
        short word_76a;
        short word_76c;
        unsigned char pad_76e[0x12];
        float field_780;
        float field_784;
        float field_788;
        unsigned char pad_78c[0x14];
        short word_7a0;
        short word_7a2;
        short word_7a4;
        short word_7a6;
    };
    extern int g_sakuya_action_match;
    typedef char check_x_ec[offsetof(SakuyaActionStateView,x_ec)==0xec?1:-1];
    typedef char check_y_f0[offsetof(SakuyaActionStateView,y_f0)==0xf0?1:-1];
    typedef char check_velocity_x_f4[offsetof(SakuyaActionStateView,velocity_x_f4)==0xf4?1:-1];
    typedef char check_velocity_y_f8[offsetof(SakuyaActionStateView,velocity_y_f8)==0xf8?1:-1];
    typedef char check_acceleration_y_100[offsetof(SakuyaActionStateView,acceleration_y_100)==0x100?1:-1];
    typedef char check_facing_104[offsetof(SakuyaActionStateView,facing_104)==0x104?1:-1];
    typedef char check_field_114[offsetof(SakuyaActionStateView,field_114)==0x114?1:-1];
    typedef char check_field_12c[offsetof(SakuyaActionStateView,field_12c)==0x12c?1:-1];
    typedef char check_action_id_13c[offsetof(SakuyaActionStateView,action_id_13c)==0x13c?1:-1];
    typedef char check_sequence_index_13e[offsetof(SakuyaActionStateView,sequence_index_13e)==0x13e?1:-1];
    typedef char check_frame_index_140[offsetof(SakuyaActionStateView,frame_index_140)==0x140?1:-1];
    typedef char check_frame_timer_142[offsetof(SakuyaActionStateView,frame_timer_142)==0x142?1:-1];
    typedef char check_time_counter_144[offsetof(SakuyaActionStateView,time_counter_144)==0x144?1:-1];
    typedef char check_related_170[offsetof(SakuyaActionStateView,related_170)==0x170?1:-1];
    typedef char check_word_174[offsetof(SakuyaActionStateView,word_174)==0x174?1:-1];
    typedef char check_byte_17c[offsetof(SakuyaActionStateView,byte_17c)==0x17c?1:-1];
    typedef char check_field_180[offsetof(SakuyaActionStateView,field_180)==0x180?1:-1];
    typedef char check_byte_184[offsetof(SakuyaActionStateView,byte_184)==0x184?1:-1];
    typedef char check_word_186[offsetof(SakuyaActionStateView,word_186)==0x186?1:-1];
    typedef char check_byte_47e[offsetof(SakuyaActionStateView,byte_47e)==0x47e?1:-1];
    typedef char check_byte_47f[offsetof(SakuyaActionStateView,byte_47f)==0x47f?1:-1];
    typedef char check_word_482[offsetof(SakuyaActionStateView,word_482)==0x482?1:-1];
    typedef char check_word_48a[offsetof(SakuyaActionStateView,word_48a)==0x48a?1:-1];
    typedef char check_word_48c[offsetof(SakuyaActionStateView,word_48c)==0x48c?1:-1];
    typedef char check_word_4a8[offsetof(SakuyaActionStateView,word_4a8)==0x4a8?1:-1];
    typedef char check_word_4ac[offsetof(SakuyaActionStateView,word_4ac)==0x4ac?1:-1];
    typedef char check_word_4ae[offsetof(SakuyaActionStateView,word_4ae)==0x4ae?1:-1];
    typedef char check_field_4b8[offsetof(SakuyaActionStateView,field_4b8)==0x4b8?1:-1];
    typedef char check_byte_605[offsetof(SakuyaActionStateView,byte_605)==0x605?1:-1];
    typedef char check_byte_606[offsetof(SakuyaActionStateView,byte_606)==0x606?1:-1];
    typedef char check_byte_607[offsetof(SakuyaActionStateView,byte_607)==0x607?1:-1];
    typedef char check_byte_60a[offsetof(SakuyaActionStateView,byte_60a)==0x60a?1:-1];
    typedef char check_byte_655[offsetof(SakuyaActionStateView,byte_655)==0x655?1:-1];
    typedef char check_field_6b4[offsetof(SakuyaActionStateView,field_6b4)==0x6b4?1:-1];
    typedef char check_field_6b8[offsetof(SakuyaActionStateView,field_6b8)==0x6b8?1:-1];
    typedef char check_field_6bc[offsetof(SakuyaActionStateView,field_6bc)==0x6bc?1:-1];
    typedef char check_field_6c0[offsetof(SakuyaActionStateView,field_6c0)==0x6c0?1:-1];
    typedef char check_field_6c4[offsetof(SakuyaActionStateView,field_6c4)==0x6c4?1:-1];
    typedef char check_field_6c8[offsetof(SakuyaActionStateView,field_6c8)==0x6c8?1:-1];
    typedef char check_byte_72c[offsetof(SakuyaActionStateView,byte_72c)==0x72c?1:-1];
    typedef char check_word_730[offsetof(SakuyaActionStateView,word_730)==0x730?1:-1];
    typedef char check_word_732[offsetof(SakuyaActionStateView,word_732)==0x732?1:-1];
    typedef char check_word_734[offsetof(SakuyaActionStateView,word_734)==0x734?1:-1];
    typedef char check_word_736[offsetof(SakuyaActionStateView,word_736)==0x736?1:-1];
    typedef char check_word_738[offsetof(SakuyaActionStateView,word_738)==0x738?1:-1];
    typedef char check_field_73c[offsetof(SakuyaActionStateView,field_73c)==0x73c?1:-1];
    typedef char check_field_740[offsetof(SakuyaActionStateView,field_740)==0x740?1:-1];
    typedef char check_field_744[offsetof(SakuyaActionStateView,field_744)==0x744?1:-1];
    typedef char check_byte_750[offsetof(SakuyaActionStateView,byte_750)==0x750?1:-1];
    typedef char check_byte_751[offsetof(SakuyaActionStateView,byte_751)==0x751?1:-1];
    typedef char check_word_764[offsetof(SakuyaActionStateView,word_764)==0x764?1:-1];
    typedef char check_word_766[offsetof(SakuyaActionStateView,word_766)==0x766?1:-1];
    typedef char check_word_768[offsetof(SakuyaActionStateView,word_768)==0x768?1:-1];
    typedef char check_word_76a[offsetof(SakuyaActionStateView,word_76a)==0x76a?1:-1];
    typedef char check_word_76c[offsetof(SakuyaActionStateView,word_76c)==0x76c?1:-1];
    typedef char check_field_780[offsetof(SakuyaActionStateView,field_780)==0x780?1:-1];
    typedef char check_field_784[offsetof(SakuyaActionStateView,field_784)==0x784?1:-1];
    typedef char check_field_788[offsetof(SakuyaActionStateView,field_788)==0x788?1:-1];
    typedef char check_word_7a0[offsetof(SakuyaActionStateView,word_7a0)==0x7a0?1:-1];
    typedef char check_word_7a2[offsetof(SakuyaActionStateView,word_7a2)==0x7a2?1:-1];
    typedef char check_word_7a4[offsetof(SakuyaActionStateView,word_7a4)==0x7a4?1:-1];
    typedef char check_word_7a6[offsetof(SakuyaActionStateView,word_7a6)==0x7a6?1:-1];
}
namespace th105 {
#define URAND(n) static_cast<float>(static_cast<unsigned>(sakuya_random(n)))
#define KNIFE(p,r,yoff,xoff) do {if((xoff)==0.0)spawn(800,sakuya_cosine(-(p)[0])*(r)*facing_104+x_ec,sakuya_sine(-(p)[0])*(r)+y_f0+(yoff),static_cast<unsigned char>(facing_104),1,p,3);else spawn(800,(sakuya_cosine(-(p)[0])*(r)+(xoff))*facing_104+x_ec,sakuya_sine(-(p)[0])*(r)+y_f0+(yoff),static_cast<unsigned char>(facing_104),1,p,3);}while(0)
#define AIM_KNIVES() do {float dx=(related_170->x_ec-x_ec)*facing_104;field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);if(field_744<-10.0)field_744=-10.0;if(field_744>10.0)field_744=10.0;word_730=1;counter(200,45);}while(0)
#define AIM_KNIVES_TAIL() do {float dx=(related_170->x_ec-x_ec)*facing_104;field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);if(field_744<-10.0)field_744=-10.0;if(field_744>10.0)field_744=10.0;{word_730=1;counter(200,45);return;}}while(0)
#define AIM_KNIVES_HIGH() do {float dx=(related_170->x_ec-x_ec)*facing_104;field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);if(field_744<40.0)field_744=40.0;if(field_744>60.0)field_744=60.0;word_730=1;counter(200,45);}while(0)
#define AIM_KNIVES_HIGH_TAIL() do {float dx=(related_170->x_ec-x_ec)*facing_104;field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);if(field_744<40.0)field_744=40.0;if(field_744>60.0)field_744=60.0;{word_730=1;counter(200,45);return;}}while(0)
#define SPELL_FLASH(x,y,cost) do {word_48a=40;word_7a4=0;word_7a6=0;event(23);effect(115,x,y,static_cast<unsigned char>(facing_104),1);sequence_window(0,cost,60);secondary_cycle();}while(0)
#define MOTION reinterpret_cast<SakuyaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)
#define ENTRY(n) (time_counter_144==0&&frame_timer_142==0&&frame_index_140==0&&sequence_index_13e==(n))
#define FRAME(n,f) (sequence_index_13e==(n)&&frame_timer_142==0&&frame_index_140==(f))
#define ADVANCE_TO(n) do {if(advance())set_action_and_finalize(n);}while(0)
#define SMOKE(dir) do {effect(124,x_ec+50.0-static_cast<float>(sakuya_random_u32()%100u),static_cast<float>(sakuya_random_u32()%200u)+y_f0,dir,1);}while(0)
#define FALL_LAND() do {velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=sakuya_surface(this);zero_motion();return;}}while(0)
    void SakuyaActionStateView::dispatch_action_state_vslot28() {
        // Out-of-range difficulty retains the target's uninitialized stack read.
        int threshold;
        word_7a0=0;
        word_7a2=94;
        if(action_id_13c>149&&action_id_13c<159&&!byte_751) {
            byte_751=1;
            if(action_id_13c>149&&action_id_13c<154)spawn(998,57*facing_104+x_ec,y_f0+94.0,static_cast<unsigned char>(facing_104),1,0,0);
            if(action_id_13c>153&&action_id_13c<158)spawn(998,57*facing_104+x_ec,y_f0+60.0,static_cast<unsigned char>(facing_104),1,0,0);
            if(action_id_13c==158)spawn(998,57*facing_104+x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1,0,0);
        }
        if(word_7a6>0) {
            if(related_170->word_174<=0||word_174<=0||sakuya_state_13c_in_32_95(this))word_7a6=0;
            if(action_id_13c>=600&&action_id_13c<=689&&(action_id_13c!=601||sequence_index_13e<4))word_7a6=0;
            if(!(word_7a6%2))word_48a=1;
            --word_7a6;
        }
        if(word_7a4>0) {
            if(related_170->word_174<=0||word_174<=0) {
                word_7a4=0;
                related_170->field_114=0;
            }
            if(action_id_13c>=600&&action_id_13c<=689&&(action_id_13c!=604||sequence_index_13e<4)) {
                word_7a4=0;
                related_170->field_114=0;
            }
            word_4a8=2;
            word_4ac=2;
            word_48a=2;
            related_170->field_114=1;
            --word_7a4;
            if(word_7a4<=0)related_170->field_114=0;
        }
        if(word_186||related_170->word_48c)return;
        switch(action_id_13c) {
            case 0:
            {
                landing();
                if(velocity_x_f4==0.0)byte_47e=0;
                idle_motion();
                break;
            }
            case 1:
            {
                landing();
                idle_motion();
                if(advance()&&!frame_index_140)set_action_and_finalize(2);
                return;
            }
            case 2:
            {
                landing();
                idle_motion();
                break;
            }
            case 3:
            {
                landing();
                idle_motion();
                if(advance()&&!frame_index_140)set_action_and_finalize(0);
                return;
            }
            case 4:
            {
                landing();
                velocity_x_f4=6.0;
                break;
            }
            case 5:
            {
                landing();
                velocity_x_f4=-6.0;
                break;
            }
            case 6:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e&&!byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    FALL_LAND();
                }
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=0.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                return;
            }
            case 7:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e&&!byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    FALL_LAND();
                }
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=5.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                return;
            }
            case 8:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e&&!byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    FALL_LAND();
                }
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=-5.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                return;
            }
            case 9:
            {
                if(acceleration_y_100==0.0)acceleration_y_100=0.6f;
                FALL_LAND();
                break;
            }
            case 10:
            {
                landing();
                zero_motion();
                if(advance()) {
                    if(field_6b8==0)set_action_and_finalize(0);
                    else set_action_and_finalize(2);
                }
                return;
            }
            case 197:
            {
                if((!sequence_index_13e&&frame_index_140<=3)||sequence_index_13e==2)landing();
                if(sequence_index_13e<2) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(2);
                        return;
                    }
                }
                if(advance()) {
                    if(byte_72c==2) {
                        set_action_and_finalize(700);
                        word_4a8=3;
                        word_4ac=3;
                        return;
                    }
                    set_action_and_finalize(0);
                    if(field_6b8>0)set_action_and_finalize(1);
                }
                if((sequence_index_13e==2&&frame_index_140==1&&frame_timer_142==0)) {
                    if(x_ec>related_170->x_ec)facing_104=-1;
                    if(x_ec<related_170->x_ec)facing_104=1;
                }
                if((sequence_index_13e==0&&frame_index_140==4&&frame_timer_142==0)) {
                    velocity_y_f8=8.0;
                    velocity_x_f4=12.5;
                    acceleration_y_100=0.7f;
                }
                return;
            }
            case 198:
            {
                if((!sequence_index_13e&&frame_index_140<=3)||sequence_index_13e==2)landing();
                if(sequence_index_13e<2) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(2);
                        return;
                    }
                }
                if(advance()) {
                    if(byte_72c==2) {
                        set_action_and_finalize(700);
                        word_4a8=3;
                        word_4ac=3;
                        return;
                    }
                    set_action_and_finalize(0);
                    if(field_6b8>0)set_action_and_finalize(1);
                }
                if((sequence_index_13e==2&&frame_index_140==3&&frame_timer_142==0)) {
                    if(x_ec>related_170->x_ec)facing_104=-1;
                    if(x_ec<related_170->x_ec)facing_104=1;
                }
                if((sequence_index_13e==0&&frame_index_140==4&&frame_timer_142==0)) {
                    velocity_y_f8=8.0;
                    velocity_x_f4=-12.5;
                    acceleration_y_100=0.7f;
                }
                return;
            }
            case 199:
            {
                landing();
                if(advance()) {
                    if(byte_72c==2) {
                        set_action_and_finalize(700);
                        word_4a8=3;
                        word_4ac=3;
                        return;
                    }
                    set_action_and_finalize(0);
                    if(field_6b8>0)set_action_and_finalize(1);
                }
                if((sequence_index_13e==0&&frame_index_140==9&&frame_timer_142==0)) {
                    if(x_ec>related_170->x_ec)facing_104=-1;
                    if(x_ec<related_170->x_ec)facing_104=1;
                }
                return;
            }
            case 200:
            {
                landing();
                byte_47e=1;
                if(velocity_x_f4>11.0) {
                    velocity_x_f4-=0.75;
                    if(velocity_x_f4<11.0)velocity_x_f4=11.0;
                }
                advance();
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%5)) {
                        SMOKE(static_cast<unsigned char>(facing_104));
                    }
                    if(field_6b8<0) {
                        if(field_6b4*facing_104>0)set_action_and_finalize(212);
                        else set_action_and_finalize(211);
                        return;
                    }
                    ++word_730;
                    if((field_6b4*facing_104<=0&&word_730>5)||word_730>45) {
                        set_action_and_finalize(204);
                        return;
                    }
                }
                if((sequence_index_13e==0&&frame_index_140==3&&frame_timer_142==0)) {
                    velocity_x_f4=15.0;
                    effect(125,80*facing_104+x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    event(31);
                }
                return;
            }
            case 201:
            {
                if(!sequence_index_13e||sequence_index_13e==3)landing();
                if(sequence_index_13e==3) {
                    velocity_x_f4+=2.0;
                    if(velocity_x_f4>0.0)velocity_x_f4=0.0;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2))velocity_x_f4=0.0;
                if(!static_cast<unsigned char>(sakuya_on_surface(this))) {
                    velocity_x_f4+=10.0;
                    if(velocity_x_f4>-10.0)velocity_x_f4=-10.0;
                    if(!(time_counter_144%5)) {
                        SMOKE(static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)));
                    }
                }
                if(sequence_index_13e<3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        velocity_y_f8=0.0;
                        acceleration_y_100=0.0;
                        y_f0=sakuya_surface(this);
                        select_sequence(3);
                        return;
                    }
                }
                if(advance()) {
                    set_action_and_finalize(0);
                    velocity_x_f4=0.0;
                    return;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2))velocity_x_f4=-50.0;
                if(ENTRY(1)) {
                    velocity_y_f8=4.0;
                    acceleration_y_100=0.6f;
                    velocity_x_f4=-30.0;
                    effect(125,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    event(31);
                }
                return;
            }
            case 202:
            {
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())) {
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    set_action_and_finalize(10);
                    return;
                }
                if((sequence_index_13e==1||sequence_index_13e==2)&&!(time_counter_144%5)) {
                    SMOKE(static_cast<unsigned char>(facing_104));
                }
                advance();
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2)) {
                    word_730=0;
                    velocity_x_f4=11.0;
                    velocity_y_f8=5.0;
                    acceleration_y_100=0.6f;
                    effect(125,80*facing_104+x_ec,y_f0+110.0,static_cast<unsigned char>(facing_104),1);
                    effect(126,x_ec,y_f0+110.0,static_cast<unsigned char>(facing_104),1);
                    event(31);
                }
                if(ENTRY(2))flip();
                return;
            }
            case 203:
            {
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())) {
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    set_action_and_finalize(10);
                    return;
                }
                if(sequence_index_13e<3&&!(time_counter_144%5)) {
                    SMOKE(static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)));
                }
                advance();
                if(!time_counter_144) {
                    if(ENTRY(1)) {
                        velocity_x_f4=-11.0;
                        velocity_y_f8=5.0;
                        acceleration_y_100=0.6f;
                        effect(125,x_ec,y_f0+120.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                        effect(126,x_ec,y_f0+120.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                        event(31);
                    }
                    if(ENTRY(2))flip();
                }
                return;
            }
            case 204:
            {
                landing();
                velocity_x_f4-=0.5;
                if(velocity_x_f4<0.0) {
                    velocity_x_f4=0.0;
                    byte_47e=0;
                }
                if(advance()) {
                    set_action_and_finalize(0);
                    byte_47e=0;
                }
                return;
            }
            case 208:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=0.0;
                velocity_y_f8=20.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                return;
            }
            case 209:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=10.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                return;
            }
            case 211:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=2.5;
                velocity_y_f8=20.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                return;
            }
            case 212:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=10.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                return;
            }
            case 214:
            {
                if (advance()) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(1))event(31);
                if(ENTRY(6)) {
                    set_action_and_finalize(9);
                    return;
                }
                if (field_6b8 > 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = -45;
                    else if (facing_104 * field_6b4 < 0) word_732 = -135;
                    else word_732 = -90;
                }
                else if (field_6b8 < 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = 45;
                    else if (facing_104 * field_6b4 < 0) word_732 = 135;
                    else word_732 = 90;
                }
                else {
                    if (facing_104 * field_6b4 > 0) word_732 = 0;
                    else if (facing_104 * field_6b4 < 0) word_732 = 180;
                }
                if (sequence_index_13e == 5 || sequence_index_13e == 6)                 velocity_y_f8 -= acceleration_y_100;
                if (sequence_index_13e > 0 && sequence_index_13e < 5) {
                    ++word_736;
                    word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
                    if (word_734 > 180) word_734 -= 360;
                    if (word_734 < -180) word_734 += 360;
                    if (word_734 > 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 1.0);
                        else field_740 = static_cast<float>(field_740 + 0.5);
                    }
                    if (word_734 < 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 1.0);
                        else field_740 = static_cast<float>(field_740 - 0.5);
                    }
                    velocity_x_f4 = sakuya_cosine(field_740) * field_73c;
                    velocity_y_f8 = sakuya_sine(field_740) * field_73c;
                    if (y_f0 > 680.0 && velocity_y_f8 > 0.0) velocity_y_f8 = 0.0f;
                    field_73c = static_cast<float>(field_73c + static_cast<double>(0.3f));
                    if (field_73c > 12.0f) field_73c = 12.0f;
                    if (field_4b8 == 0) counter(5, 1);
                    else counter(10, 1);
                    field_12c = -field_740;
                    if (velocity_x_f4 < 0.0) field_12c = 180.0 - field_740;
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 1) select_sequence(3);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 3) select_sequence(1);
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 2) select_sequence(4);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 4) select_sequence(2);
                    if (time_counter_144 % 5 == 1) {
                        effect(125,                         sakuya_cosine(field_740) * 100.0 * facing_104 + x_ec,                         sakuya_sine(field_740) * 100.0 + y_f0 + 100.0,                         facing_104, 1);
                    }
                    if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                        if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                            MOTION->reset();
                            if (sequence_index_13e == 1 || sequence_index_13e == 2) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                                else {
                                    if (x_ec < related_170->x_ec) {
                                        facing_104 = -facing_104;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                            }
                            if (sequence_index_13e == 3 || sequence_index_13e == 4) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(5);
                                    }
                                    else select_sequence(6);
                                    return;
                                }
                                if (x_ec < related_170->x_ec) {
                                    facing_104 = -facing_104;
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(5);
                                }
                                else select_sequence(6);
                            }
                            return;
                        }
                    }
                }
                if (static_cast<unsigned char>(crossed())) {
                    y_f0 = sakuya_surface(this);
                    acceleration_y_100 = 0.0f;
                    velocity_y_f8 = 0.0f;
                    if (sequence_index_13e < 5) {
                        MOTION->reset();
                        set_action_and_finalize(215);
                    }
                    else {
                        set_action_and_finalize(10);
                        zero_motion();
                    }
                }
                return;
            }
            case 215:
            {
                landing();
                if(velocity_x_f4>0.0) {
                    velocity_x_f4-=0.75;
                    if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                }
                if(velocity_x_f4<0.0) {
                    velocity_x_f4+=0.75;
                    if(velocity_x_f4>0.0)velocity_x_f4=0.0;
                }
                ADVANCE_TO(0);
                return;
            }
            case 220:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(ENTRY(1)) {
                    velocity_x_f4=0.0;
                    velocity_y_f8=20.0;
                    acceleration_y_100=0.7f;
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
                return;
            }
            case 221:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(!ENTRY(1))return;
                velocity_x_f4=10.0;
                velocity_y_f8=15.0;
                acceleration_y_100=0.7f;
                byte_47e=0;
                effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                return;
            }
            case 210:
            case 222:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(static_cast<unsigned char>(sakuya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;
                }
                if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
                advance();
                if(ENTRY(1)) {
                    velocity_x_f4=-10.0;
                    velocity_y_f8=15.0;
                    acceleration_y_100=0.7f;
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
                return;
            }
            case 223:
            {
                landing();
                byte_47e=1;
                advance();
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%5)) {
                        SMOKE(static_cast<unsigned char>(facing_104));
                    }
                    ++word_730;
                    if((field_6b4*facing_104<=0&&word_730>13)||word_730>45) {
                        set_action_and_finalize(204);
                        return;
                    }
                }
                if((sequence_index_13e==0&&frame_index_140==3&&frame_timer_142==0)) {
                    velocity_x_f4=7.5;
                    effect(125,80*facing_104+x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    event(31);
                }
                return;
            }
            case 224:
            {
                if(!sequence_index_13e||sequence_index_13e==3)landing();
                if(sequence_index_13e==3) {
                    velocity_x_f4+=2.0;
                    if(velocity_x_f4>0.0)velocity_x_f4=0.0;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2))velocity_x_f4=0.0;
                if(!static_cast<unsigned char>(sakuya_on_surface(this))) {
                    velocity_x_f4+=10.0;
                    if(velocity_x_f4>-10.0)velocity_x_f4=-10.0;
                    if(!(time_counter_144%5)) {
                        SMOKE(static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)));
                    }
                }
                if(sequence_index_13e<3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        velocity_y_f8=0.0;
                        acceleration_y_100=0.0;
                        y_f0=sakuya_surface(this);
                        select_sequence(3);
                        return;
                    }
                }
                if(advance()) {
                    set_action_and_finalize(0);
                    velocity_x_f4=0.0;
                    return;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2))velocity_x_f4=-50.0;
                if(ENTRY(1)) {
                    velocity_y_f8=4.0;
                    acceleration_y_100=0.6f;
                    velocity_x_f4=-30.0;
                    effect(125,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    event(31);
                }
                return;
            }
            case 225:
            {
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())) {
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    set_action_and_finalize(10);
                    return;
                }
                if(sequence_index_13e<3&&!(time_counter_144%5)) {
                    SMOKE(static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)));
                }
                if(advance())set_action_and_finalize(9);
                if(!time_counter_144) {
                    if(ENTRY(1)) {
                        velocity_x_f4=-11.0;
                        velocity_y_f8=5.0;
                        acceleration_y_100=0.6f;
                        effect(125,x_ec,y_f0+120.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                        effect(126,x_ec,y_f0+120.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                        event(31);
                    }
                    if(ENTRY(2))flip();
                }
                return;
            }
            case 226:
            {
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())) {
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    set_action_and_finalize(10);
                    return;
                }
                if((sequence_index_13e==1||sequence_index_13e==2)&&!(time_counter_144%5)) {
                    SMOKE(static_cast<unsigned char>(facing_104));
                }
                if(advance())set_action_and_finalize(9);
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2)) {
                    word_730=0;
                    velocity_x_f4=11.0;
                    velocity_y_f8=5.0;
                    acceleration_y_100=0.6f;
                    effect(125,80*facing_104+x_ec,y_f0+110.0,static_cast<unsigned char>(facing_104),1);
                    effect(126,x_ec,y_f0+110.0,static_cast<unsigned char>(facing_104),1);
                    event(31);
                }
                if(ENTRY(2))flip();
                return;
            }
            case 300:
            {
                landing();
                if(directional(0))return;
                if(byte_47e) {
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<0.0) {
                        velocity_x_f4=0.0;
                        byte_47e=0;
                    }
                }
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==3) {
                    event(27);
                    byte_47e=0;
                }
                return;
            }
            case 302:
            {
                if(directional(1))return;
                if(!sequence_index_13e||sequence_index_13e==2||sequence_index_13e==4)landing();
                if(sequence_index_13e==1) {
                    velocity_y_f8-=acceleration_y_100;
                    if(time_counter_144>=25)landing();
                }
                if(sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    velocity_x_f4-=0.75;
                    if(velocity_x_f4<3.0)velocity_x_f4=3.0;
                    if(time_counter_144>=24) {
                        velocity_x_f4=5.0;
                        velocity_y_f8=-25.0;
                    }
                }
                if(sequence_index_13e<2) {
                    if(static_cast<unsigned char>(crossed())) {
                        event(29);
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(2);
                        return;
                    }
                }
                else if(sequence_index_13e==3&&static_cast<unsigned char>(crossed())) {
                    event(29);
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    select_sequence(4);
                    event(22);
                    layout(2.0f);
                    effect(58,135*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                    return;
                }
                if(!field_6bc)byte_750=0;
                ADVANCE_TO(0);
                if(time_counter_144)return;
                if(!frame_timer_142&&!frame_index_140&&sequence_index_13e==3)set_action_and_finalize(0);
                if(ENTRY(1)) {
                    velocity_x_f4=15.0;
                    velocity_y_f8=4.0;
                    acceleration_y_100=0.85f;
                }
                return;
            }
            case 303:
            {
                landing();
                if(directional(0))return;
                if(static_cast<signed char>(byte_47e)>0) {
                    velocity_x_f4-=static_cast<double>(0.6f);
                    if(velocity_x_f4<0.0) {
                        velocity_x_f4=0.0;
                        byte_47e=0;
                    }
                }
                ADVANCE_TO(2);
                if(!frame_timer_142&&frame_index_140==4)event(28);
                return;
            }
            case 304:
            {
                if(sequence_index_13e==0||(sequence_index_13e==2&&time_counter_144>=30)||sequence_index_13e==3||sequence_index_13e==4||(sequence_index_13e==6&&time_counter_144>=30)||sequence_index_13e==7)landing();
                if(sequence_index_13e==1||sequence_index_13e==2) {
                    velocity_y_f8-=acceleration_y_100;
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<5.0)velocity_x_f4=5.0;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(3);
                        return;
                    }
                }
                if(sequence_index_13e==5||sequence_index_13e==6) {
                    velocity_y_f8-=acceleration_y_100;
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<7.0)velocity_x_f4=7.0;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(7);
                        return;
                    }
                }
                if(!field_6bc)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    velocity_x_f4=13.5;
                    velocity_y_f8=12.5;
                    acceleration_y_100=1.0;
                }
                if(!time_counter_144) {
                    if(ENTRY(4))set_action_and_finalize(0);
                    if(ENTRY(5)) {
                        velocity_x_f4=15.5;
                        velocity_y_f8=13.5;
                        acceleration_y_100=1.0;
                    }
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)&&byte_750) {
                    select_sequence(4);
                    effect(62,x_ec-17*facing_104,y_f0+72.0,static_cast<unsigned char>(facing_104),1);
                    return;
                }
                if(sequence_index_13e==1&&!frame_timer_142) {
                    if(frame_index_140==1) {
                        float request[3]= {
                            0.0f,1.0f,1.0f
                        };
                        spawn(849,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    if(!frame_timer_142) {
                        if(frame_index_140==2)event(29);
                        if(!frame_timer_142&&frame_index_140==4)field_180=0;
                    }
                }
                if(sequence_index_13e!=5)return;
                if(!frame_timer_142&&frame_index_140==1) {
                    float request[3]= {
                        0.0f,1.0f,1.0f
                    };
                    spawn(849,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(frame_timer_142)return;
                if(frame_index_140==2)event(29);
                if(!frame_timer_142&&frame_index_140==4)field_180=0;
                return;
            }
            case 305:
            {
                landing();
                if(directional(1))return;
                if(frame_index_140>4) {
                    velocity_x_f4-=1.0;
                    if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                }
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==3)event(28);
                return;
            }
            case 306:
            {
                FALL_LAND();
                ADVANCE_TO(9);
                if(!frame_timer_142&&frame_index_140==5)event(28);
                return;
            }
            case 307:
            {
                if(!field_6bc)byte_750=0;
                FALL_LAND();
                ADVANCE_TO(9);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==2))event(29);
                return;
            }
            case 308:
            {
                if(!field_6bc)byte_750=0;
                FALL_LAND();
                ADVANCE_TO(9);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==6) {
                    event(28);
                    float request[3]= {
                        0.0f,0.0f,0.0f
                    };
                    spawn(849,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(!frame_timer_142&&frame_index_140==9)acceleration_y_100=0.6f;
                return;
            }
            case 309:
            {
                if(!field_6bc)byte_750=0;
                FALL_LAND();
                ADVANCE_TO(9);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==2) {
                    acceleration_y_100=0.8f;
                    velocity_y_f8=12.0;
                }
                if(frame_timer_142)return;
                if(frame_index_140==4) {
                    float request[3]= {
                        0.0f,0.0f,1.0f
                    };
                    spawn(849,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(!frame_timer_142&&frame_index_140==5)event(29);
                return;
            }
            case 310:
            {
                if(field_180&&++word_730>5) {
                    field_180=0;
                    word_730=0;
                }
                if(sequence_index_13e==1) {
                    if(!time_counter_144)velocity_x_f4=15.0;
                    if(!(time_counter_144%8))event(27);
                    if(field_180&&++word_730>5) {
                        field_180=0;
                        word_730=0;
                    }
                    if(time_counter_144>30) {
                        next_sequence_block();
                        velocity_y_f8=6.0;
                        velocity_x_f4*=0.5;
                    }
                }
                if(sequence_index_13e==2) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        velocity_y_f8=0.0;
                        y_f0=sakuya_surface(this);
                        set_action_and_finalize(9);
                        return;
                    }
                }
                ADVANCE_TO(9);
                return;
            }
            case 320:
            {
                landing();
                if(directional(0))return;
                if(frame_index_140>1) {
                    velocity_x_f4-=2.0;
                    if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                }
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==2) {
                    event(28);
                    byte_47e=0;
                }
                return;
            }
            case 301:
            case 321:
            {
                landing();
                if(directional(0))return;
                if(byte_47e) {
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<0.0) {
                        velocity_x_f4=0.0;
                        byte_47e=0;
                    }
                }
                if(frame_index_140>=4) {
                    velocity_x_f4-=1.5;
                    if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                }
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==3) {
                    velocity_x_f4=20.0;
                    byte_47e=0;
                }
                if(!frame_timer_142&&frame_index_140==4) {
                    velocity_x_f4=5.0;
                    event(28);
                }
                return;
            }
            case 322:
            {
                landing();
                if(directional(1))return;
                velocity_x_f4-=0.5;
                if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==3) {
                    event(29);
                    byte_47e=0;
                }
                return;
            }
            case 400:
            {
                landing();
                if(!field_6c0)byte_750=0;
                if(word_730==1) {
                    if(!sequence_index_13e) {
                        if(!(word_732%3)&&word_734<5) {
                            field_180=1;
                            for(int i=0;i<15;i+=5) {
                                float request[3];
                                request[0]=field_744-4.0+word_734*2+i-5.0;
                                request[1]=5.0f;
                                request[2]=0.0f;
                                KNIFE(request,40.0,125.0,0.0);
                            }
                            phase_counter(10);
                            dispatch_character_wave_handle(0);
                            ++word_734;
                        }
                    }
                    else if(!(word_732%3)&&word_734<7) {
                        field_180=1;
                        for(int i=0;i<15;i+=5) {
                            float request[3];
                            request[0]=field_744-4.0+word_734*2+i-5.0;
                            request[1]=5.0f;
                            request[2]=0.0f;
                            KNIFE(request,40.0,125.0,0.0);
                        }
                        phase_counter(10);
                        dispatch_character_wave_handle(0);
                        ++word_734;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,x_ec-40*facing_104,y_f0+136.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==6) {
                        AIM_KNIVES();
                    }
                }
                if(FRAME(1,3)) {
                    AIM_KNIVES();
                }
                return;
            }
            case 401:
            {
                landing();
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==5&&byte_750) {
                        next_sequence_block();
                        effect(62,x_ec-6*facing_104,y_f0+203.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==7) {
                        dispatch_character_wave_handle(0);
                        counter(200,60);
                        field_180=1;
                        phase_counter(50);
                        for(int i=0,y=0;y<100;++i,y+=20) {
                            float request[3];
                            request[0]=2.0-i;
                            request[1]=25.0f;
                            request[2]=4.0f;
                            spawn(800,77*facing_104+x_ec,y_f0+40.0+y,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                if(FRAME(1,7)) {
                    dispatch_character_wave_handle(0);
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                    for(int i=0,y=0;y<105;++i,y+=15) {
                        float request[3];
                        request[0]=3.0-i;
                        request[1]=25.0f;
                        request[2]=4.0f;
                        spawn(800,77*facing_104+x_ec,y_f0+25.0+y,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                }
                return;
            }
            case 402:
            {
                landing();
                if(!field_6c0)byte_750=0;
                if(word_730==1) {
                    if(!sequence_index_13e) {
                        if(!(word_732%3)&&word_734<5) {
                            field_180=1;
                            for(int i=-50;i<-35;i+=5) {
                                float request[3];
                                request[0]=i-word_734*6;
                                request[1]=5.0f;
                                request[2]=0.0f;
                                KNIFE(request,70.0,75.0,50.0);
                            }
                            phase_counter(10);
                            dispatch_character_wave_handle(0);
                            ++word_734;
                        }
                    }
                    else if(!(word_732%3)&&word_734<5) {
                        field_180=1;
                        for(int i=0;i<15;i+=5) {
                            float request[3];
                            request[0]=field_744-4.0+word_734*2+i-5.0;
                            request[1]=5.0f;
                            request[2]=0.0f;
                            KNIFE(request,40.0,125.0,0.0);
                        }
                        phase_counter(10);
                        dispatch_character_wave_handle(0);
                        ++word_734;
                    }
                    ++word_732;
                }
                ADVANCE_TO(2);
                if(ENTRY(1)) {
                    set_action_and_finalize(2);
                    return;
                }
                if(FRAME(0,5)) {
                    word_730=1;
                    counter(200,45);
                }
                return;
            }
            case 404:
            {
                if(sequence_index_13e==2)landing();
                if(!field_6c0)byte_750=0;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(word_730==1) {
                    if(!sequence_index_13e) {
                        if(!(word_732%3)&&word_734<5) {
                            field_180=1;
                            for(int i=0;i<15;i+=5) {
                                float request[3];
                                request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                                request[1]=5.0f;
                                request[2]=0.0f;
                                KNIFE(request,80.0,100.0,0.0);
                            }
                            phase_counter(10);
                            dispatch_character_wave_handle(0);
                            ++word_734;
                        }
                    }
                    else if(sequence_index_13e==1&&!(word_732%3)&&word_734<7) {
                        field_180=1;
                        for(int i=0;i<15;i+=5) {
                            float request[3];
                            request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                            request[1]=5.0f;
                            request[2]=0.0f;
                            KNIFE(request,80.0,100.0,0.0);
                        }
                        phase_counter(10);
                        dispatch_character_wave_handle(0);
                        ++word_734;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,30*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        velocity_x_f4=-6.0;
                        velocity_y_f8=9.0;
                        acceleration_y_100=0.7f;
                        AIM_KNIVES();
                    }
                }
                if(FRAME(1,2)) {
                    velocity_x_f4=-6.0;
                    velocity_y_f8=9.0;
                    acceleration_y_100=0.7f;
                    AIM_KNIVES_TAIL();
                }
                return;
            }
            case 405:
            {
                if(sequence_index_13e==2)landing();
                if(!field_6c0)byte_750=0;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(word_730==1) {
                    if(!sequence_index_13e) {
                        if(!(word_732%3)&&word_734<5) {
                            field_180=1;
                            for(int i=0;i<15;i+=5) {
                                float request[3];
                                request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                                request[1]=5.0f;
                                request[2]=0.0f;
                                KNIFE(request,80.0,100.0,0.0);
                            }
                            phase_counter(10);
                            dispatch_character_wave_handle(0);
                            ++word_734;
                        }
                    }
                    else if(!(word_732%3)&&word_734<5) {
                        field_180=1;
                        for(int i=0;i<15;i+=5) {
                            float request[3];
                            request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                            request[1]=5.0f;
                            request[2]=0.0f;
                            KNIFE(request,80.0,100.0,0.0);
                        }
                        phase_counter(10);
                        dispatch_character_wave_handle(0);
                        ++word_734;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,30*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        velocity_x_f4=-6.0;
                        velocity_y_f8=9.0;
                        acceleration_y_100=0.7f;
                        AIM_KNIVES();
                    }
                }
                if(FRAME(1,2)) {
                    velocity_x_f4=-6.0;
                    velocity_y_f8=9.0;
                    acceleration_y_100=0.7f;
                    AIM_KNIVES_TAIL();
                }
                return;
            }
            case 406:
            {
                if(sequence_index_13e==2)landing();
                if(!field_6c0)byte_750=0;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(word_730==1) {
                    if(!sequence_index_13e) {
                        if(!(word_732%3)&&word_734<5) {
                            field_180=1;
                            for(int i=0;i<15;i+=5) {
                                float request[3];
                                request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                                request[1]=5.0f;
                                request[2]=0.0f;
                                KNIFE(request,80.0,100.0,0.0);
                            }
                            phase_counter(10);
                            dispatch_character_wave_handle(0);
                            ++word_734;
                        }
                    }
                    else if(sequence_index_13e==1&&!(word_732%3)&&word_734<7) {
                        field_180=1;
                        for(int i=0;i<15;i+=5) {
                            float request[3];
                            request[0]=field_744+4.0-static_cast<float>(word_734*2)+i-5.0;
                            request[1]=5.0f;
                            request[2]=0.0f;
                            KNIFE(request,80.0,100.0,0.0);
                        }
                        phase_counter(10);
                        dispatch_character_wave_handle(0);
                        ++word_734;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,30*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        velocity_x_f4=-6.0;
                        velocity_y_f8=9.0;
                        acceleration_y_100=0.7f;
                        AIM_KNIVES_HIGH();
                    }
                }
                if(FRAME(1,2)) {
                    velocity_x_f4=-4.0;
                    velocity_y_f8=12.0;
                    acceleration_y_100=0.7f;
                    AIM_KNIVES_HIGH_TAIL();
                }
                return;
            }
            case 408:
            {
                landing();
                if(frame_index_140>=4)velocity_x_f4-=0.5;
                if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                if(field_180)word_730=1;
                ADVANCE_TO(0);
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==2)event(29);
                if(frame_timer_142)return;
                if(frame_index_140==4)field_180=0;
                if(frame_timer_142)return;
                if(frame_index_140==5)field_180=0;
                if(!frame_timer_142&&frame_index_140==6&&word_730==1)field_180=1;
                return;
            }
            case 409:
            {
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    return;
                }
                ADVANCE_TO(9);
                return;
            }
            case 410:
            {
                landing();
                if(!field_6c4)byte_750=0;
                if(!sequence_index_13e&&word_730>0) {
                    if(word_730%2==1&&word_730<=13) {
                        field_73c+=3.0;
                        dispatch_character_wave_handle(1);
                        float request[3];
                        request[0]=30.0-field_73c;
                        request[1]=20.0f;
                        request[2]=0.0f;
                        spawn(803,(sakuya_cosine(-request[0])*80.0+20.0)*facing_104+x_ec,sakuya_sine(-request[0])*80.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    ++word_730;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(FRAME(0,4)) {
                    word_730=1;
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                }
                if(FRAME(1,7)) {
                    dispatch_character_wave_handle(1);
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                    for(float i=0.0f;i<7.0;i+=1.0) {
                        float request[3];
                        request[0]=3.0-i;
                        request[1]=sakuya_absolute(i-3.0);
                        request[1]=35.0-request[1];
                        request[2]=0.0f;
                        spawn(801,77*facing_104+x_ec,y_f0+25.0+i*15.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                }
                return;
            }
            case 411:
            {
                landing();
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==5&&byte_750) {
                        next_sequence_block();
                        effect(62,x_ec-6*facing_104,y_f0+203.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==7) {
                        dispatch_character_wave_handle(2);
                        counter(200,60);
                        field_180=1;
                        phase_counter(50);
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            float request[3];
                            request[0]=2.0-i;
                            request[1]=30.0-sakuya_absolute(2.0-i)*2.0;
                            request[2]=0.0f;
                            spawn(801,77*facing_104+x_ec,y_f0+40.0+i*20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                if(FRAME(1,7)) {
                    dispatch_character_wave_handle(2);
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                    for(float i=0.0f;i<7.0;i+=1.0) {
                        float request[3];
                        request[0]=3.0-i;
                        request[1]=sakuya_absolute(i-3.0);
                        request[1]=35.0-request[1];
                        request[2]=0.0f;
                        spawn(801,77*facing_104+x_ec,y_f0+25.0+i*15.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                }
                return;
            }
            case 412:
            {
                landing();
                if(sequence_index_13e<2&&!field_6c4)word_738=1;
                ADVANCE_TO(2);
                if(ENTRY(1))set_action_and_finalize(2);
                if(!FRAME(0,5))return;
                dispatch_character_wave_handle(2);
                field_180=1;
                counter(200,60);
                phase_counter(50);
                for(float i=0.0f;i<5.0f;i+=1.0) {
                    float request[3];
                    request[0]=0.0f;
                    request[1]=sakuya_absolute(2.0-i);
                    request[1]=40.0-request[1];
                    request[2]=0.0f;
                    spawn(802,100*facing_104+x_ec,20.0+y_f0+i*20.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                return;
            }
            case 414:
            {
                if(sequence_index_13e==2)landing();
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(!field_6c4)byte_750=0;
                if(!sequence_index_13e&&word_730>0) {
                    if(word_730%2==1&&word_730<=13) {
                        field_73c+=3.0;
                        dispatch_character_wave_handle(1);
                        float request[3];
                        request[0]=field_73c+5.0;
                        request[1]=20.0f;
                        request[2]=3.0f;
                        spawn(803,sakuya_cosine(-request[0])*80.0*facing_104+x_ec,sakuya_sine(-request[0])*80.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    ++word_730;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==5) {
                        word_730=1;
                        counter(200,60);
                        field_180=1;
                        phase_counter(50);
                    }
                    if(!frame_timer_142&&frame_index_140==7)acceleration_y_100=0.5f;
                }
                if(sequence_index_13e!=1||frame_timer_142)return;
                if(frame_index_140==2) {
                    word_730=1;
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                }
                if(!frame_timer_142&&frame_index_140==4)acceleration_y_100=0.5f;
                return;
            }
            case 415:
            {
                if(sequence_index_13e==2)landing();
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,x_ec-6*facing_104,y_f0+203.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142) {
                        if(frame_index_140==5) {
                            dispatch_character_wave_handle(2);
                            counter(200,60);
                            field_180=1;
                            phase_counter(50);
                            for(float i=0.0f;i<5.0f;i+=1.0) {
                                float request[3];
                                request[0]=2.0-i;
                                request[1]=30.0-sakuya_absolute(2.0-i)*2.0;
                                request[2]=0.0f;
                                spawn(801,80*facing_104+x_ec,y_f0+60.0+i*20.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                        }
                        if(!frame_timer_142&&frame_index_140==7)acceleration_y_100=0.5f;
                    }
                }
                if(sequence_index_13e!=1||frame_timer_142)return;
                if(frame_index_140==2) {
                    dispatch_character_wave_handle(2);
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                    for(float i=0.0f;i<7.0;i+=1.0) {
                        float request[3];
                        request[0]=3.0-i;
                        request[1]=sakuya_absolute(i-3.0);
                        request[1]=35.0-request[1];
                        request[2]=0.0f;
                        spawn(801,80*facing_104+x_ec,y_f0+60.0+i*20.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                }
                if(!frame_timer_142&&frame_index_140==4)acceleration_y_100=0.5f;
                return;
            }
            case 416:
            {
                if(sequence_index_13e==2)landing();
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2) {
                    select_sequence(2);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(ENTRY(2)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e&&!frame_timer_142) {
                    if(frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,x_ec-6*facing_104,y_f0+203.0,static_cast<unsigned char>(facing_104),1);
                    }
                    if(!frame_timer_142&&frame_index_140==6) {
                        dispatch_character_wave_handle(2);
                        counter(200,60);
                        field_180=1;
                        phase_counter(50);
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            float request[3];
                            request[0]=60.0-i*2.0;
                            request[1]=30.0-sakuya_absolute(2.0-i)*2.0;
                            request[2]=0.0f;
                            spawn(801,(i*20.0+10.0)*facing_104+x_ec,30.0+y_f0+i*6.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        velocity_x_f4=-5.0;
                        velocity_y_f8=10.0;
                        acceleration_y_100=0.5f;
                    }
                }
                if(FRAME(1,2)) {
                    dispatch_character_wave_handle(2);
                    counter(200,60);
                    field_180=1;
                    phase_counter(50);
                    for(float i=0.0f;i<7.0;i+=1.0) {
                        float request[3];
                        request[0]=60.0-i*2.0;
                        request[1]=30.0-sakuya_absolute(2.0-i)*2.0;
                        request[2]=0.0f;
                        spawn(801,(i*20.0+10.0)*facing_104+x_ec,30.0+y_f0+i*6.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    velocity_x_f4=-5.0;
                    velocity_y_f8=10.0;
                    acceleration_y_100=0.5f;
                }
                return;
            }
            case 418:
            {
                landing();
                if(frame_index_140<=4)velocity_x_f4-=0.5;
                if(frame_index_140>=7)velocity_x_f4-=0.75;
                if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==4) {
                    event(29);
                    velocity_x_f4=20.0;
                    byte_47e=0;
                }
                return;
            }
            case 500:
            {
                if(!sequence_index_13e||sequence_index_13e==5)landing();
                byte_17c=0;
                if(sequence_index_13e==1||sequence_index_13e==2) {
                    field_73c-=1.5;
                    if(field_73c<2.0)field_73c=2.0;
                    MOTION->set_oriented_components(-50.0f,field_73c);
                    if(sequence_index_13e==2) {
                        if(field_180&&byte_184>0&&++word_730>=10) {
                            word_730=0;
                            field_180=0;
                        }
                        if(time_counter_144>=35)next_sequence_block();
                    }
                }
                if(sequence_index_13e==3||sequence_index_13e==4) {
                    field_180=1;
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(5);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                for(float i=0.0f;i<6.0f;i+=1.0) {
                    float request[3];
                    request[0]=i*60.0;
                    request[1]=150.0f;
                    request[2]=2.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[2]=3.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                dispatch_character_wave_handle(10);
                phase_counter(50);
                field_73c=22.0;
                acceleration_y_100=0.6f;
                MOTION->set_oriented_components(-50.0f,field_73c);
                return;
            }
            case 501:
            {
                if(!sequence_index_13e||sequence_index_13e==5)landing();
                byte_17c=0;
                if(sequence_index_13e==1||sequence_index_13e==2) {
                    field_73c-=1.5;
                    if(field_73c<2.0)field_73c=2.0;
                    MOTION->set_oriented_components(-50.0f,field_73c);
                    if(sequence_index_13e==2) {
                        if(field_180&&byte_184>0&&++word_730>=10) {
                            word_730=0;
                            field_180=0;
                        }
                        if(time_counter_144>=45)next_sequence_block();
                    }
                }
                if(sequence_index_13e==3||sequence_index_13e==4) {
                    field_180=1;
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(5);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                for(float i=0.0f;i<6.0f;i+=1.0) {
                    float request[3];
                    request[0]=i*60.0;
                    request[1]=200.0f;
                    request[2]=2.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[2]=3.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(10);
                field_73c=30.0;
                acceleration_y_100=0.6f;
                MOTION->set_oriented_components(-50.0f,field_73c);
                return;
            }
            case 502:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=0;
                if(sequence_index_13e==1||sequence_index_13e==2) {
                    if(sequence_index_13e==2) {
                        if(field_180&&byte_184>0&&++word_730>=10) {
                            word_730=0;
                            field_180=0;
                        }
                        if(time_counter_144>=35)next_sequence_block();
                    }
                }
                if(sequence_index_13e==3||sequence_index_13e==4) {
                    field_180=1;
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(5);
                        return;
                    }
                    if(sequence_index_13e==4&&time_counter_144>=20) {
                        set_action_and_finalize(9);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                for(float i=0.0f;i<6.0f;i+=1.0) {
                    float request[3];
                    request[0]=i*60.0;
                    request[1]=150.0f;
                    request[2]=2.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[2]=3.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(static_cast<unsigned char>(crossed()))effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(10);
                acceleration_y_100=0.6f;
                return;
            }
            case 503:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=0;
                if(sequence_index_13e==1||sequence_index_13e==2) {
                    if(sequence_index_13e==2) {
                        if(field_180&&byte_184>0&&++word_730>=10) {
                            word_730=0;
                            field_180=0;
                        }
                        if(time_counter_144>=35)next_sequence_block();
                    }
                }
                if(sequence_index_13e==3||sequence_index_13e==4) {
                    field_180=1;
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        select_sequence(5);
                        return;
                    }
                    if(sequence_index_13e==4&&time_counter_144>=30) {
                        set_action_and_finalize(9);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                for(float i=0.0f;i<6.0f;i+=1.0) {
                    float request[3];
                    request[0]=i*60.0;
                    request[1]=150.0f;
                    request[2]=2.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[2]=3.0f;
                    spawn(810,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(static_cast<unsigned char>(crossed()))effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(10);
                acceleration_y_100=0.6f;
                return;
            }
            case 505:
            {
                landing();
                byte_17c=4;
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                float request[3];
                for(float i=0.0f;i<3.0f;i+=1.0) {
                    request[0]=i*120.0;
                    request[1]=14.0f;
                    request[2]=0.0f;
                    spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                for(float i=0.0f;i<3.0f;i+=1.0) {
                    request[0]=i*120.0+60.0;
                    request[1]=14.0f;
                    request[2]=0.0f;
                    spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1,request,3);
                }
                request[0]=URAND(360);
                request[1]=15.0f;
                request[2]=2.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=15.0f;
                request[2]=3.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=-15.0f;
                request[2]=4.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(14);
                return;
            }
            case 506:
            {
                landing();
                byte_17c=4;
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                float request[3];
                for(float i=0.0f;i<4.0f;i+=1.0) {
                    request[0]=i*90.0;
                    request[1]=15.0f;
                    request[2]=0.0f;
                    spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                for(float i=0.0f;i<4.0f;i+=1.0) {
                    request[0]=i*90.0+45.0;
                    request[1]=15.0f;
                    request[2]=0.0f;
                    spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1,request,3);
                }
                request[0]=URAND(360);
                request[1]=15.0f;
                request[2]=2.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=15.0f;
                request[2]=3.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=-15.0f;
                request[2]=4.0f;
                spawn(815,x_ec,y_f0+118.0,static_cast<unsigned char>(facing_104),1,request,3);
                effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(14);
                return;
            }
            case 520:
            {
                landing();
                byte_17c=1;
                if(!field_6c0)byte_750=0;
                if(word_730==1) {
                    float limit;
                    if(byte_605==0)limit=3.0f;
                    if(byte_605>=1)limit=4.0f;
                    if(byte_605>=4)limit=5.0f;
                    if(!(word_732%2)&&(field_73c<limit)) {
                        float request[3];
                        request[1]=14.0-field_73c;
                        request[2]=0.0f;
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            request[0]=i*5.0-5.0-70.0-field_73c*3.0;
                            spawn(811,(sakuya_cosine(-request[0])*70.0+15.0)*facing_104+x_ec,sakuya_sine(-request[0])*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        field_73c+=1.0;
                    }
                    ++word_732;
                }
                if(word_730==2) {
                    float limit;
                    if(byte_605==0)limit=3.0f;
                    if(byte_605>=1)limit=4.0f;
                    if(byte_605>=4)limit=5.0f;
                    if(!(word_732%2)&&(field_73c<limit)) {
                        float request[3];
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            request[0]=-70.0-field_73c*3.0-i*5.0;
                            request[1]=14.0-field_73c;
                            request[2]=0.0f;
                            spawn(811,(sakuya_cosine(-request[0])*70.0+15.0)*facing_104+x_ec,sakuya_sine(-request[0])*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        field_73c+=1.0;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e) {
                    if(!frame_timer_142&&frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,15*facing_104+x_ec,y_f0+90.0,static_cast<unsigned char>(facing_104),1);
                        return;
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        word_730=1;
                        dispatch_character_wave_handle(11);
                        counter(200,120);
                        phase_counter(50);
                    }
                }
                if(FRAME(1,2)) {
                    word_730=2;
                    dispatch_character_wave_handle(11);
                    counter(200,120);
                    phase_counter(50);
                }
                return;
            }
            case 521:
            {
                landing();
                byte_17c=1;
                if(!field_6c4)byte_750=0;
                if(word_730==1) {
                    float limit;
                    if(byte_605==0)limit=3.0f;
                    if(byte_605>=1)limit=4.0f;
                    if(byte_605>=4)limit=5.0f;
                    if(!(word_732%2)&&(field_73c<limit)) {
                        float request[3];
                        request[1]=14.0-field_73c;
                        request[2]=0.0f;
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            request[0]=i*5.0-5.0-135.0-field_73c*3.0;
                            spawn(811,(sakuya_cosine(-request[0])*70.0-20.0)*facing_104+x_ec,sakuya_sine(-request[0])*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        field_73c+=1.0;
                    }
                    ++word_732;
                }
                if(word_730==2) {
                    float limit;
                    if(byte_605==0)limit=3.0f;
                    if(byte_605>=1)limit=4.0f;
                    if(byte_605>=4)limit=5.0f;
                    if(!(word_732%2)&&(field_73c<limit)) {
                        float request[3];
                        request[1]=14.0-field_73c;
                        request[2]=0.0f;
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            request[0]=i*5.0-5.0-135.0-field_73c*3.0;
                            spawn(811,(sakuya_cosine(-request[0])*70.0-20.0)*facing_104+x_ec,sakuya_sine(-request[0])*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        field_73c+=1.0;
                    }
                    ++word_732;
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e) {
                    if(!frame_timer_142&&frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,15*facing_104+x_ec,y_f0+90.0,static_cast<unsigned char>(facing_104),1);
                        return;
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        word_730=1;
                        dispatch_character_wave_handle(11);
                        counter(200,120);
                        phase_counter(50);
                    }
                }
                if(FRAME(1,2)) {
                    word_730=2;
                    dispatch_character_wave_handle(11);
                    counter(200,120);
                    phase_counter(50);
                }
                return;
            }
            case 525:
            {
                landing();
                byte_17c=5;
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e) {
                    if(!frame_timer_142&&frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,15*facing_104+x_ec,y_f0+90.0,static_cast<unsigned char>(facing_104),1);
                        return;
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        float request[4]= {
                            -45.0f,15.0f,0.0f,0.0f
                        };
                        spawn(816,(sakuya_cosine(-request[0])*70.0-20.0)*facing_104+x_ec,sakuya_sine(45.0f)*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,4);
                        dispatch_character_wave_handle(11);
                        counter(200,120);
                        phase_counter(50);
                    }
                }
                if(FRAME(1,2)) {
                    float request[4]= {
                        -45.0f,15.0f,0.0f,1.0f
                    };
                    spawn(816,(sakuya_cosine(-request[0])*70.0-20.0)*facing_104+x_ec,sakuya_sine(45.0f)*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,4);
                    dispatch_character_wave_handle(11);
                    counter(200,120);
                    phase_counter(50);
                }
                return;
            }
            case 526:
            {
                landing();
                byte_17c=5;
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(!sequence_index_13e) {
                    if(!frame_timer_142&&frame_index_140==4&&byte_750) {
                        next_sequence_block();
                        effect(62,15*facing_104+x_ec,y_f0+90.0,static_cast<unsigned char>(facing_104),1);
                        return;
                    }
                    if(!frame_timer_142&&frame_index_140==5) {
                        float request[4]= {
                            -135.0f,15.0f,0.0f,0.0f
                        };
                        spawn(816,(sakuya_cosine(-request[0])*70.0+15.0)*facing_104+x_ec,sakuya_sine(135.0f)*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,4);
                        dispatch_character_wave_handle(11);
                        counter(200,120);
                        phase_counter(50);
                    }
                }
                if(FRAME(1,2)) {
                    float request[4]= {
                        -135.0f,15.0f,0.0f,1.0f
                    };
                    spawn(816,(sakuya_cosine(-request[0])*70.0+15.0)*facing_104+x_ec,sakuya_sine(135.0f)*70.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,4);
                    dispatch_character_wave_handle(11);
                    counter(200,120);
                    phase_counter(50);
                }
                return;
            }
            case 540:
            {
                landing();
                byte_17c=2;
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(FRAME(0,7)) {
                    phase_counter(50);
                    counter(200,120);
                    field_180=1;
                    float request[3];
                    request[2]=0.0f;
                    if(byte_606>=4)field_73c=1.15f;
                    else field_73c=1.0f;
                    {
                        request[0]=2.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-2.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=5.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-5.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=5.5f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-5.5f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=4.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-4.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-2.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(2.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-5.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(5.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-5.5f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(5.5f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-4.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(4.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(12);
                }
                if(sequence_index_13e==1&&!frame_index_140&&!byte_750) {
                    select_sequence(0);
                    frame_index_140=7;
                }
                return;
            }
            case 541:
            {
                landing();
                byte_17c=2;
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(FRAME(0,7)) {
                    phase_counter(50);
                    counter(200,120);
                    field_180=1;
                    float request[3];
                    request[2]=0.0f;
                    if(byte_606>=4)field_73c=1.15f;
                    else field_73c=1.0f;
                    {
                        request[0]=3.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-3.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=8.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-8.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=10.0f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-10.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=11.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-11.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-3.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(3.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-8.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(8.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-10.0f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(10.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-11.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(11.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(12);
                }
                if(sequence_index_13e==1&&!frame_index_140&&!byte_750) {
                    select_sequence(0);
                    frame_index_140=7;
                }
                return;
            }
            case 542:
            {
                if(sequence_index_13e==1)landing();
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<1) {
                    select_sequence(1);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==5) {
                    phase_counter(50);
                    counter(200,120);
                    field_180=1;
                    float request[3];
                    request[2]=0.0f;
                    if(byte_606>=4)field_73c=1.15f;
                    else field_73c=1.0f;
                    {
                        request[0]=2.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-2.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=5.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-5.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=5.5f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-5.5f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=4.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-4.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-2.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(2.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-5.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(5.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-5.5f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(5.5f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-4.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(4.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(12);
                }
                if(!frame_timer_142&&frame_index_140==7)acceleration_y_100=0.5f;
                return;
            }
            case 543:
            {
                if(sequence_index_13e==1)landing();
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<1) {
                    select_sequence(1);
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(!field_6c4)byte_750=0;
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==5) {
                    phase_counter(50);
                    counter(200,120);
                    field_180=1;
                    float request[3];
                    request[2]=0.0f;
                    if(byte_606>=4)field_73c=1.15f;
                    else field_73c=1.0f;
                    {
                        request[0]=3.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-3.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=8.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-8.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=10.0f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-10.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=11.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(-11.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-3.0f;
                        request[1]=field_73c*30.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(3.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-8.0f;
                        request[1]=field_73c*27.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(8.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-10.0f;
                        request[1]=field_73c*24.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(10.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    {
                        request[0]=-11.0f;
                        request[1]=field_73c*21.0;
                        spawn(812,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,sakuya_sine(11.0f)*200.0+y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(12);
                }
                if(!frame_timer_142&&frame_index_140==7)acceleration_y_100=0.5f;
                return;
            }
            case 545:
            {
                landing();
                byte_17c=6;
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float request[3]= {
                    0.0f,15.0f,0.0f
                };
                switch(byte_60a) {
                    case 1:
                    {
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0+45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+60.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<2.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0+22.5)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 3:
                    {
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 4:
                    {
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*30.0)*150.0-50.0)*facing_104+x_ec,(i*40.0+y_f0)-20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                dispatch_character_wave_handle(15);
                return;
            }
            case 546:
            {
                landing();
                byte_17c=6;
                if(!field_6c0)byte_750=0;
                ADVANCE_TO(0);
                if(!ENTRY(1))return;
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float request[3]= {
                    0.0f,15.0f,0.0f
                };
                switch(byte_60a) {
                    case 1:
                    {
                        for(float i=0.0f;i<4.0;i+=1.0) {
                            request[0]=45.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0+22.5)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<3.0;i+=1.0) {
                            request[0]=30.0-i*30.0;
                            spawn(817,(sakuya_sine(30.0+60.0*i)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+60.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[0]=60.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<4.0;i+=1.0) {
                            request[0]=45.0-30.0*i;
                            spawn(817,(sakuya_sine(i*60.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 3:
                    {
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[0]=75.0-30.0*i;
                            spawn(817,(sakuya_sine(i*36.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[0]=60.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 4:
                    {
                        for(float i=0.0f;i<7.0;i+=1.0) {
                            request[0]=90.0-30.0*i;
                            spawn(817,(sakuya_sine(30.0*i)*150.0-50.0)*facing_104+x_ec,(i*40.0+y_f0)-20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[0]=75.0-30.0*i;
                            spawn(817,(sakuya_sine(i*36.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                dispatch_character_wave_handle(15);
                return;
            }
            case 547:
            {
                if(sequence_index_13e==4)landing();
                byte_17c=6;
                if(!field_6c0)byte_750=0;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<4) {
                    byte_47f=0;
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    select_sequence(4);
                    return;
                }
                ADVANCE_TO(0);
                if(ENTRY(4)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!ENTRY(1))return;
                velocity_x_f4=-10.0;
                velocity_y_f8=5.0;
                acceleration_y_100=0.5f;
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float request[3]= {
                    0.0f,15.0f,0.0f
                };
                switch(byte_60a) {
                    case 1:
                    {
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0+45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+60.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<2.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0+22.5)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<3.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 3:
                    {
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 4:
                    {
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            spawn(817,(sakuya_sine(i*30.0)*150.0-50.0)*facing_104+x_ec,(i*40.0+y_f0)-20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            spawn(817,(URAND(100)+50.0+0.0)*facing_104+x_ec,URAND(250)+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                dispatch_character_wave_handle(15);
                return;
            }
            case 548:
            {
                if(sequence_index_13e==4)landing();
                byte_17c=6;
                if(!field_6c0)byte_750=0;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<4) {
                    byte_47f=0;
                    zero_motion();
                    y_f0=sakuya_surface(this);
                    select_sequence(4);
                    return;
                }
                ADVANCE_TO(0);
                if(ENTRY(4)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!ENTRY(1))return;
                velocity_x_f4=-10.0;
                velocity_y_f8=5.0;
                acceleration_y_100=0.5f;
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float request[3]= {
                    0.0f,15.0f,0.0f
                };
                switch(byte_60a) {
                    case 1:
                    {
                        for(float i=0.0f;i<4.0;i+=1.0) {
                            request[0]=45.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0+22.5)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<3.0;i+=1.0) {
                            request[0]=30.0-i*30.0;
                            spawn(817,(sakuya_sine(30.0+60.0*i)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+60.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[0]=60.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0+20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<4.0;i+=1.0) {
                            request[0]=45.0-30.0*i;
                            spawn(817,(sakuya_sine(i*60.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+40.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 3:
                    {
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[0]=75.0-30.0*i;
                            spawn(817,(sakuya_sine(i*36.0)*150.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[0]=60.0-30.0*i;
                            spawn(817,(sakuya_sine(i*45.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0+20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 4:
                    {
                        for(float i=0.0f;i<7.0;i+=1.0) {
                            request[0]=90.0-30.0*i;
                            spawn(817,(sakuya_sine(30.0*i)*150.0-50.0)*facing_104+x_ec,(i*40.0+y_f0)-20.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[0]=75.0-30.0*i;
                            spawn(817,(sakuya_sine(i*36.0)*120.0-50.0)*facing_104+x_ec,i*40.0+y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                dispatch_character_wave_handle(15);
                return;
            }
            case 560:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                byte_17c=3;
                if(ENTRY(2)) {
                    velocity_x_f4=0.0;
                    velocity_y_f8=0.0;
                }
                if(sequence_index_13e==1&&time_counter_144>=10) {
                    float request[3]= {
                        10.0f,0.0f,6.0f
                    };
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[0]=-10.0f;
                    request[2]=7.0f;
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    next_sequence_block();
                    velocity_x_f4=750.0;
                    velocity_y_f8=30.0;
                    if(byte_607>=4)velocity_y_f8=15.0;
                    acceleration_y_100=0.25f;
                    dispatch_character_wave_handle(13);
                    return;
                }
                if(sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        next_sequence_block();
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!time_counter_144) {
                    if(ENTRY(3)) {
                        float request[3]= {
                            0.0f,0.0f,8.0f
                        };
                        spawn(813,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=10.0f;
                        request[2]=9.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=-10.0f;
                        request[2]=10.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    if(ENTRY(1)) {
                        phase_counter(50);
                        counter(200,120);
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            float request[3]= {
                                0.0f,0.0f,i
                            };
                            spawn(813,x_ec-8*facing_104,y_f0+115.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                if(sequence_index_13e>=3&&byte_607>=4)word_4a8=2;
                return;
            }
            case 561:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                byte_17c=3;
                if(ENTRY(2)) {
                    velocity_x_f4=0.0;
                    velocity_y_f8=0.0;
                }
                if(sequence_index_13e==1&&time_counter_144>=10) {
                    float request[3]= {
                        10.0f,0.0f,6.0f
                    };
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[0]=-10.0f;
                    request[2]=7.0f;
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    next_sequence_block();
                    velocity_x_f4=-750.0;
                    velocity_y_f8=30.0;
                    if(byte_607>=4)velocity_y_f8=15.0;
                    acceleration_y_100=0.25f;
                    dispatch_character_wave_handle(13);
                    return;
                }
                if(sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        next_sequence_block();
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(!time_counter_144) {
                    if(ENTRY(3)) {
                        float request[3]= {
                            0.0f,0.0f,8.0f
                        };
                        spawn(813,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=10.0f;
                        request[2]=9.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=-10.0f;
                        request[2]=10.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    if(ENTRY(1)) {
                        phase_counter(50);
                        counter(200,120);
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            float request[3]= {
                                0.0f,0.0f,i
                            };
                            spawn(813,x_ec-8*facing_104,y_f0+115.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                if(sequence_index_13e>=3&&byte_607>=4)word_4a8=2;
                return;
            }
            case 562:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=3;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<5) {
                    select_sequence(5);
                    acceleration_y_100=0.0;
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(sequence_index_13e<2&&!field_6c4)byte_750=0;
                if(word_730>0&&(sequence_index_13e==2||sequence_index_13e==3)) {
                    if(word_730%4==1) {
                        phase_counter(10);
                        field_180=1;
                        {
                            float dx=(related_170->x_ec-x_ec)*facing_104;
                            word_734=-static_cast<short>(static_cast<int>(sakuya_atan(related_170->y_f0-y_f0,dx)));
                            if(word_734<-10)word_734=-10;
                            if(word_734>10)word_734=10;
                        }
                        dispatch_character_wave_handle(9);
                        if(word_738==1) {
                            float request[3];
                            double angle=word_734+30.0;
                            request[0]=angle-static_cast<float>(sakuya_random_u32()%60u);
                            request[1]=15.0f;
                            request[2]=URAND(4);
                            spawn(808,44*facing_104+x_ec,y_f0+85.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        else {
                            float request[3];
                            double angle=word_734+30.0;
                            request[0]=angle-static_cast<float>(sakuya_random_u32()%60u);
                            request[1]=15.0f;
                            request[2]=URAND(4);
                            spawn(808,44*facing_104+x_ec,y_f0+85.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                    ++word_730;
                }
                ADVANCE_TO(0);
                if(ENTRY(5)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1&&time_counter_144>4&&(!byte_750||time_counter_144>25))next_sequence_block();
                if(ENTRY(1)) {
                    if(byte_750==1)effect(62,x_ec-23*facing_104,y_f0+107.0,static_cast<unsigned char>(facing_104),1);
                    float request[3]= {
                        0.0f,0.0f,4.0f
                    };
                    spawn(808,x_ec-23*facing_104,y_f0+107.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if((sequence_index_13e==2&&frame_index_140==2&&frame_timer_142==0)) {
                    word_730=1;
                    counter(200,120);
                }
                if(sequence_index_13e==3&&((time_counter_144>10&&!byte_750)||time_counter_144>25))next_sequence_block();
                if(FRAME(4,5))acceleration_y_100=0.6f;
                return;
            }
            case 565:
            {
                landing();
                byte_17c=7;
                if(!sequence_index_13e&&field_180==3) {
                    float request[3]= {
                        0.0f,20.0f,2.0f
                    };
                    spawn(818,x_ec,y_f0+200.0,1,1,request,3);
                    word_48a=60;
                    next_sequence_block();
                    dispatch_character_wave_handle(16);
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(ENTRY(2)) {
                    float request[3];
                    request[1]=20.0f;
                    request[2]=0.0f;
                    for(float i=0.0f;i<20.0f;i+=1.0) {
                        request[0]=i*18.0+176.0;
                        float angle=-i*18.0;
                        spawn(818,sakuya_cosine(angle)*300.0*facing_104+related_170->x_ec,sakuya_sine(angle)*300.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    for(float i=0.0f;i<20.0f;i+=1.0) {
                        request[0]=i*18.0+184.0;
                        float angle=-i*18.0;
                        spawn(818,sakuya_cosine(angle)*400.0*facing_104+related_170->x_ec,sakuya_sine(angle)*400.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(2);
                    x_ec=150*facing_104+related_170->x_ec;
                    y_f0=sakuya_surface(this);
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)) {
                    phase_counter(50);
                    counter(200,120);
                }
                return;
            }
            case 566:
            {
                landing();
                byte_17c=7;
                if(!sequence_index_13e&&field_180==3) {
                    float request[3]= {
                        0.0f,20.0f,2.0f
                    };
                    spawn(818,x_ec,y_f0+200.0,1,1,request,3);
                    word_48a=60;
                    next_sequence_block();
                    dispatch_character_wave_handle(16);
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    set_action_and_finalize(0);
                    return;
                }
                if(ENTRY(2)) {
                    float request[3];
                    request[1]=20.0f;
                    request[2]=0.0f;
                    for(float i=0.0f;i<20.0f;i+=1.0) {
                        request[0]=i*18.0+176.0;
                        float angle=-i*18.0;
                        spawn(818,sakuya_cosine(angle)*300.0*facing_104+related_170->x_ec,sakuya_sine(angle)*300.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    for(float i=0.0f;i<20.0f;i+=1.0) {
                        request[0]=i*18.0+184.0;
                        float angle=-i*18.0;
                        spawn(818,sakuya_cosine(angle)*400.0*facing_104+related_170->x_ec,sakuya_sine(angle)*400.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    dispatch_character_wave_handle(2);
                    x_ec=150*facing_104+related_170->x_ec;
                    y_f0=sakuya_surface(this);
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)) {
                    phase_counter(50);
                    counter(200,120);
                }
                return;
            }
            case 567:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=7;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())&&sequence_index_13e<5) {
                    select_sequence(5);
                    acceleration_y_100=0.0;
                    byte_47f=0;
                    y_f0=sakuya_surface(this);
                    zero_motion();
                    return;
                }
                if(sequence_index_13e<2&&!field_6c4)byte_750=0;
                if((sequence_index_13e==2&&frame_index_140==2&&frame_timer_142==0)) {
                    {
                        float dx=(related_170->x_ec-x_ec)*facing_104;
                        word_734=-static_cast<short>(static_cast<int>(sakuya_atan(related_170->y_f0-y_f0,dx)));
                        if(word_734<-10)word_734=-10;
                        if(word_734>10)word_734=10;
                    }
                    dispatch_character_wave_handle(29);
                    field_180=1;
                    counter(200,60);
                    phase_counter(50);
                    float request[3]= {
                        0.0f,0.0f,0.0f
                    };
                    if(word_738==1)spawn(824,48*facing_104+x_ec,y_f0+104.0,static_cast<unsigned char>(facing_104),1,request,3);
                    else spawn(824,48*facing_104+x_ec,y_f0+104.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                ADVANCE_TO(0);
                if(ENTRY(1)) {
                    float request[3]= {
                        0.0f,0.0f,4.0f
                    };
                    spawn(824,x_ec-48*facing_104,y_f0+104.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                if(ENTRY(5)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1&&time_counter_144>10&&(!byte_750||time_counter_144>25))next_sequence_block();
                if(sequence_index_13e==3&&time_counter_144>40)next_sequence_block();
                if((sequence_index_13e==4&&frame_timer_142==0&&frame_index_140==5))acceleration_y_100=0.6f;
                return;
            }
            case 599:
            {
                if(word_730>0&&frame_index_140<7&&word_730<12) {
                    word_734=static_cast<short>(sakuya_random_u32()%35u);
                    float request[3];
                    request[0]=-20-word_734;
                    request[1]=static_cast<short>(sakuya_random_u32()%5u+10);
                    request[2]=0.0f;
                    spawn(807,(word_730+1)*facing_104*20+x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[0]=static_cast<float>(sakuya_random_u32()%360u);
                    request[1]=0.0f;
                    request[2]=1.0f;
                    spawn(801,(word_730+1)*facing_104*20+x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    if(word_730==1) {
                        dispatch_character_wave_handle(0);
                        counter(200,120);
                    }
                    ++word_730;
                }
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==5)word_730=1;
                return;
            }
            case 600:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==1) {
                    if(time_counter_144>35) {
                        next_sequence_block();
                        return;
                    }
                    if(!(time_counter_144%2)&&time_counter_144<=30) {
                        float request[4];
                        request[0]=time_counter_144*12+90.0;
                        request[1]=15.0f;
                        request[2]=0.0f;
                        request[3]=90.0f;
                        {
                            spawn(850,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,4);
                        }
                        request[0]=time_counter_144*12+270.0;
                        {
                            spawn(850,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,4);
                        }
                    }
                }
                ADVANCE_TO(0);
                if(ENTRY(1))dispatch_character_wave_handle(50);
                if(FRAME(0,3)) {
                    SPELL_FLASH(x_ec-23*facing_104,y_f0+158.0,2);
                }
                return;
            }
            case 601:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==4&&time_counter_144>=45)next_sequence_block();
                ADVANCE_TO(0);
                if(ENTRY(2)) {
                    SPELL_FLASH(26*facing_104+x_ec,y_f0+88.0,3);
                }
                if(ENTRY(4)) {
                    float request[3]= {
                        0.0f,0.0f,0.0f
                    };
                    spawn(851,640.0f,480.0f,1,-2,request,3);
                    dispatch_character_wave_handle(52);
                    word_7a6=300;
                }
                return;
            }
            case 602:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                texture(5,2);
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%4)) {
                        float request[3]= {
                            0.0f,0.0f,0.0f
                        };
                        spawn(852,60*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[2]=1.0f;
                        spawn(852,60*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                        dispatch_character_wave_handle(54);
                    }
                    if(time_counter_144>90) {
                        next_sequence_block();
                        return;
                    }
                }
                if(sequence_index_13e==2||sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        select_sequence(4);
                        zero_motion();
                        return;
                    }
                }
                ADVANCE_TO(0);
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)) {
                    SPELL_FLASH(30*facing_104+x_ec,y_f0+85.0,3);
                }
                if(ENTRY(1)) {
                    velocity_x_f4=0.5f;
                    velocity_y_f8=1.0f;
                    acceleration_y_100=0.5f;
                }
                return;
            }
            case 603:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==1&&time_counter_144>60) {
                    next_sequence_block();
                    return;
                }
                ADVANCE_TO(0);
                if(ENTRY(1))dispatch_character_wave_handle(51);
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==3)) {
                    SPELL_FLASH(x_ec-23*facing_104,y_f0+158.0,4);
                }
                if(!ENTRY(1))return;
                float request[4];
                request[1]=15.0f;
                request[2]=0.0f;
                for(float i=0.0f;i<12.0f;i+=1.0) {
                    float angle=30.0*i;
                    request[0]=angle+15.0;
                    request[3]=i*4.0+60.0;
                    spawn(853,sakuya_cosine(-request[0])*20.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*20.0,static_cast<unsigned char>(facing_104),1,request,4);
                }
                return;
            }
            case 604:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==1&&time_counter_144>=60) {
                    next_sequence_block();
                    SPELL_FLASH(26*facing_104+x_ec,y_f0+88.0,5);
                }
                if(sequence_index_13e==4&&time_counter_144>=45)next_sequence_block();
                ADVANCE_TO(0);
                if(ENTRY(4)) {
                    float request[3]= {
                        0.0f,0.0f,0.0f
                    };
                    spawn(854,640.0f,480.0f,1,-2,request,3);
                    dispatch_character_wave_handle(53);
                    word_48a=40;
                    word_7a4=300;
                }
                return;
            }
            case 605:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                texture(5,2);
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%4)) {
                        float request[3]= {
                            0.0f,0.0f,0.0f
                        };
                        spawn(855,60*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[2]=1.0f;
                        spawn(855,x_ec-640*facing_104,y_f0+300.0-URAND(400),static_cast<unsigned char>(facing_104),1,request,3);
                        request[2]=2.0f;
                        spawn(855,60*facing_104+x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                        dispatch_character_wave_handle(54);
                    }
                    if(time_counter_144>90) {
                        next_sequence_block();
                        return;
                    }
                }
                if(sequence_index_13e==2||sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        select_sequence(4);
                        zero_motion();
                        return;
                    }
                }
                ADVANCE_TO(0);
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)) {
                    SPELL_FLASH(30*facing_104+x_ec,y_f0+85.0,3);
                }
                if(ENTRY(1)) {
                    velocity_x_f4=0.5f;
                    velocity_y_f8=0.9f;
                    acceleration_y_100=0.5f;
                }
                return;
            }
            case 606:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==1&&time_counter_144>36) {
                    next_sequence_block();
                    return;
                }
                ADVANCE_TO(0);
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==3) {
                    SPELL_FLASH(x_ec-23*facing_104,y_f0+158.0,2);
                }
                if(frame_timer_142||frame_index_140!=8)return;
                dispatch_character_wave_handle(15);
                for(float i=0.0f;i<30.0;i+=1.0) {
                    float request[4];
                    request[0]=i*12.0;
                    request[1]=6.0f;
                    request[2]=0.0f;
                    spawn(856,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                }
                return;
            }
            case 607:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                texture(5,2);
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%2)) {
                        float request[3];
                        request[0]=URAND(60);
                        request[0]-=30.0;
                        if(!(time_counter_144%10)) {
                            request[1]=URAND(50)*static_cast<double>(0.1f)+15.0;
                            request[2]=1.0f;
                            dispatch_character_wave_handle(2);
                        }
                        else {
                            request[1]=URAND(50)*static_cast<double>(0.1f)+10.0;
                            request[2]=0.0f;
                        }
                        spawn(857,(sakuya_cosine(-request[0])*200.0-100.0)*facing_104+x_ec,y_f0+110.0+sakuya_sine(-request[0])*200.0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    if(time_counter_144>90) {
                        next_sequence_block();
                        return;
                    }
                }
                if(sequence_index_13e==2||sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        y_f0=sakuya_surface(this);
                        select_sequence(4);
                        zero_motion();
                        return;
                    }
                }
                ADVANCE_TO(0);
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==4)) {
                    SPELL_FLASH(30*facing_104+x_ec,y_f0+85.0,3);
                }
                if(ENTRY(1)) {
                    velocity_x_f4=0.5f;
                    velocity_y_f8=0.9f;
                    acceleration_y_100=0.5f;
                }
                return;
            }
            case 608:
            {
                landing();
                texture(5,2);
                ADVANCE_TO(0);
                if(sequence_index_13e||frame_timer_142)return;
                if(frame_index_140==3) {
                    SPELL_FLASH(x_ec-35*facing_104,y_f0+155.0,2);
                }
                if(frame_timer_142||frame_index_140!=6)return;
                float request[4];
                request[0]=2.0f;
                if(field_6b8)request[0]=88.0f;
                request[1]=100.0f;
                request[2]=0.0f;
                request[3]=14.0f;
                spawn(858,100*facing_104+x_ec,y_f0+110.0,static_cast<unsigned char>(facing_104),1,request,4);
                dispatch_character_wave_handle(15);
                return;
            }
            case 609:
            {
                landing();
                texture(5,2);
                if(sequence_index_13e==1&&time_counter_144>=40)next_sequence_block();
                if(sequence_index_13e==4&&time_counter_144>=45)next_sequence_block();
                ADVANCE_TO(0);
                if(time_counter_144)return;
                if(!frame_timer_142&&!frame_index_140&&sequence_index_13e==2) {
                    word_48a=40;
                    event(23);
                    effect(115,26*facing_104+x_ec,y_f0+88.0,static_cast<unsigned char>(facing_104),1);
                    sequence_window(0,4,60);
                    word_7a4=0;
                    word_7a6=0;
                    secondary_cycle();
                }
                if(!ENTRY(4))return;
                float request[3]= {
                    0.0f,25.0f,0.0f
                };
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-180.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-60.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-120.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=60.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=120.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=30.0f;
                request[1]=5.0f;
                request[2]=0.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-150.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-30.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=-90.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=90.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=150.0f;
                spawn(859,x_ec,y_f0+130.0,1,-1,request,3);
                request[0]=URAND(360);
                request[1]=15.0f;
                request[2]=4.0f;
                spawn(859,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=15.0f;
                request[2]=5.0f;
                spawn(859,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=-15.0f;
                request[2]=6.0f;
                spawn(859,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                effect(128,200*facing_104+x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(53);
                return;
            }
            case 656:
            {
                texture(5,2);
                if(sequence_index_13e==1&&time_counter_144>36) {
                    next_sequence_block();
                    return;
                }
                if(sequence_index_13e<3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        select_sequence(3);
                        return;
                    }
                }
                ADVANCE_TO(0);
                if(ENTRY(3)) {
                    set_action_and_finalize(9);
                    return;
                }
                if(!sequence_index_13e) {
                    if(!frame_timer_142&&frame_index_140==3) {
                        SPELL_FLASH(x_ec-23*facing_104,y_f0+158.0,2);
                    }
                    if(!frame_timer_142&&frame_index_140==8) {
                        for(float i=0.0f;i<30.0;i+=1.0) {
                            float request[4];
                            request[0]=i*12.0;
                            request[1]=6.0f;
                            request[2]=0.0f;
                            spawn(856,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                if((sequence_index_13e==2&&frame_timer_142==0&&frame_index_140==1))acceleration_y_100=0.5f;
                return;
            }
            case 695:
            {
                landing();
                ADVANCE_TO(0);
                if(!(sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==8))return;
                event(55);
                effect(140,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1);
                effect(140,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1);
                effect(140,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1);
                effect(141,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),-1);
                effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                return;
            }
            case 696:
            {
                landing();
                velocity_x_f4-=0.5;
                if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                ADVANCE_TO(0);
                if(!frame_timer_142&&frame_index_140==3) {
                    event(29);
                    byte_47e=0;
                }
                return;
            }
            case 707:
            {
                if(velocity_x_f4>12.0) {
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<12.0)velocity_x_f4=12.0;
                }
                if(advance()) {
                    set_action_and_finalize(700);
                    return;
                }
                if(FRAME(0,3)) {
                    velocity_x_f4=15.0;
                    effect(125,80*facing_104+x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(facing_104),1);
                    event(31);
                }
                if(sequence_index_13e==1) {
                    if(!(time_counter_144%5)) {
                        SMOKE(static_cast<unsigned char>(facing_104));
                    }
                    if(time_counter_144>30) {
                        next_sequence_block();
                        return;
                    }
                }
                if(sequence_index_13e==2) {
                    velocity_x_f4-=0.5;
                    if(velocity_x_f4<0.0)velocity_x_f4=0.0;
                }
                return;
            }
            case 708:
            {
                if(sequence_index_13e==2) {
                    landing();
                    velocity_x_f4+=2.0;
                    if(velocity_x_f4>0.0)velocity_x_f4=0.0;
                }
                if(!static_cast<unsigned char>(sakuya_on_surface(this))&&!(time_counter_144%5)) {
                    SMOKE(static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)));
                }
                if(sequence_index_13e<2) {
                    velocity_y_f8-=0.5;
                    if(static_cast<unsigned char>(crossed())) {
                        velocity_y_f8=0.0;
                        acceleration_y_100=0.0;
                        y_f0=sakuya_surface(this);
                        select_sequence(2);
                        return;
                    }
                }
                if(advance()) {
                    set_action_and_finalize(700);
                    return;
                }
                if(ENTRY(1)) {
                    velocity_x_f4=-14.0;
                    velocity_y_f8=4.0;
                    effect(125,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1);
                    event(31);
                }
                return;
            }
            // These count-three packets reserve four floats; the fourth stays unwritten.
            case 710:
            {
                landing();
                if(sequence_index_13e==1&&time_counter_144>90) {
                    next_sequence_block();
                    return;
                }
                ADVANCE_TO(700);
                if(!FRAME(0,7))return;
                dispatch_character_wave_handle(15);
                switch(g_sakuya_action_match) {
                    case 3:
                    {
                        for(float i=0.0f;i<30.0;i+=1.0) {
                            float request[4];
                            request[0]=i*12.0;
                            request[1]=8.0f;
                            request[2]=0.0f;
                            spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<10.0;i+=1.0) {
                            float request[4];
                            request[0]=i*12.0;
                            request[1]=6.0f;
                            request[2]=0.0f;
                            spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(float i=0.0f;i<30.0;i+=1.0) {
                            float request[4];
                            request[0]=i*12.0;
                            request[1]=8.0f;
                            request[2]=0.0f;
                            spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 1:
                    {
                        for(float i=0.0f;i<20.0;i+=1.0) {
                            float request[4];
                            request[0]=i*18.0;
                            request[1]=8.0f;
                            request[2]=0.0f;
                            spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 0:
                    {
                        for(float i=0.0f;i<15.0;i+=1.0) {
                            float request[4];
                            request[0]=i*24.0;
                            request[1]=6.0f;
                            request[2]=0.0f;
                            spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                return;
            }
            case 711:
            {
                if(sequence_index_13e==4&&time_counter_144>90) {
                    next_sequence_block();
                    return;
                }
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(sequence_index_13e<5&&velocity_y_f8<0.0) {
                        velocity_y_f8=0.0;
                        velocity_x_f4=0.0;
                    }
                    if(static_cast<unsigned char>(crossed())) {
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        set_action_and_finalize(709);
                        return;
                    }
                }
                if(advance()) {
                    set_action_and_finalize(704);
                    acceleration_y_100=0.25f;
                    return;
                }
                if(ENTRY(1)) {
                    velocity_x_f4=field_780;
                    velocity_y_f8=field_784;
                    acceleration_y_100=field_788;
                }
                if(FRAME(3,7)) {
                    acceleration_y_100=0.0;
                    dispatch_character_wave_handle(15);
                    switch(g_sakuya_action_match) {
                        case 3:
                        {
                            for(float i=0.0f;i<30.0;i+=1.0) {
                                float request[4];
                                request[0]=i*12.0;
                                request[1]=8.0f;
                                request[2]=0.0f;
                                spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            for(float i=0.0f;i<10.0;i+=1.0) {
                                float request[4];
                                request[0]=i*12.0;
                                request[1]=6.0f;
                                request[2]=0.0f;
                                spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            break;
                        }
                        case 2:
                        {
                            for(float i=0.0f;i<30.0;i+=1.0) {
                                float request[4];
                                request[0]=i*12.0;
                                request[1]=8.0f;
                                request[2]=0.0f;
                                spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            break;
                        }
                        case 1:
                        {
                            for(float i=0.0f;i<20.0;i+=1.0) {
                                float request[4];
                                request[0]=i*18.0;
                                request[1]=8.0f;
                                request[2]=0.0f;
                                spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            break;
                        }
                        case 0:
                        {
                            for(float i=0.0f;i<15.0;i+=1.0) {
                                float request[4];
                                request[0]=i*24.0;
                                request[1]=6.0f;
                                request[2]=0.0f;
                                spawn(900,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            break;
                        }
                    }
                }
                if(FRAME(5,1))acceleration_y_100=0.25f;
                return;
            }
            case 720:
            {
                landing();
                if(sequence_index_13e==1&&time_counter_144>=40)next_sequence_block();
                if(sequence_index_13e==3&&time_counter_144>=45)next_sequence_block();
                ADVANCE_TO(700);
                if(!ENTRY(3))return;
                dispatch_character_wave_handle(53);
                float request[3]= {
                    URAND(360),15.0f,4.0f
                };
                spawn(901,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=15.0f;
                request[2]=5.0f;
                spawn(901,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                request[1]=-15.0f;
                request[2]=6.0f;
                spawn(901,x_ec,y_f0+130.0,static_cast<unsigned char>(facing_104),1,request,3);
                float angle;
                switch(g_sakuya_action_match) {
                    case 3:
                    {
                        request[1]=15.0f;
                        request[2]=0.0f;
                        angle=URAND(360);
                        for(float i=0.0f;i<8.0f;i+=1.0) {
                            request[0]=i*45.0+angle;
                            spawn(901,x_ec,y_f0+130.0,1,-1,request,3);
                        }
                        return;
                    }
                    case 2:
                    {
                        request[1]=15.0f;
                        request[2]=0.0f;
                        angle=URAND(360);
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            request[0]=i*60.0+angle;
                            spawn(901,x_ec,y_f0+130.0,1,-1,request,3);
                        }
                        return;
                    }
                    case 1:
                    {
                        request[1]=15.0f;
                        request[2]=0.0f;
                        angle=URAND(360);
                        for(float i=0.0f;i<5.0f;i+=1.0) {
                            request[0]=i*72.0+angle;
                            spawn(901,x_ec,y_f0+130.0,1,-1,request,3);
                        }
                        return;
                    }
                    case 0:
                    {
                        request[1]=15.0f;
                        request[2]=0.0f;
                        angle=URAND(360);
                        for(float i=0.0f;i<4.0f;i+=1.0) {
                            request[0]=i*90.0+angle;
                            spawn(901,x_ec,y_f0+130.0,1,-1,request,3);
                        }
                        return;
                    }
                }
                return;
            }
            case 721:
            {
                if(sequence_index_13e==4&&time_counter_144>60) {
                    next_sequence_block();
                    return;
                }
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(sequence_index_13e<5&&velocity_y_f8<0.0) {
                        velocity_y_f8=0.0;
                        velocity_x_f4=0.0;
                    }
                    if(static_cast<unsigned char>(crossed())) {
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        set_action_and_finalize(709);
                        return;
                    }
                }
                if(word_730==1&&!(time_counter_144%4)) {
                    float request[3];
                    switch(g_sakuya_action_match) {
                        case 3:
                        if(field_740<10.0f) {
                            float dx=(related_170->x_ec-x_ec)*facing_104;
                            field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);
                            for(float i=0.0f;i<3.0f;i+=1.0) {
                                double offset=i*15.0;
                                request[0]=offset+(field_744-15.0);
                                request[1]=15.0-field_740;
                                request[2]=7.0f;
                                spawn(901,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            field_740+=1.0;
                        }
                        break;
                        case 2:
                        if(field_740<8.0f) {
                            float dx=(related_170->x_ec-x_ec)*facing_104;
                            field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);
                            for(float i=0.0f;i<3.0f;i+=1.0) {
                                request[0]=i*15.0+(field_744-15.0);
                                request[1]=15.0-field_740;
                                request[2]=7.0f;
                                spawn(901,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            field_740+=1.0;
                        }
                        break;
                        case 1:
                        if(field_740<6.0f) {
                            float dx=(related_170->x_ec-x_ec)*facing_104;
                            field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);
                            for(float i=0.0f;i<3.0f;i+=1.0) {
                                request[0]=i*15.0+(field_744-15.0);
                                request[1]=15.0-field_740;
                                request[2]=7.0f;
                                spawn(901,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            field_740+=1.0;
                        }
                        break;
                        case 0:
                        if(field_740<4.0f) {
                            float dx=(related_170->x_ec-x_ec)*facing_104;
                            field_744=-sakuya_atan(related_170->y_f0-y_f0,dx);
                            for(float i=0.0f;i<3.0f;i+=1.0) {
                                request[0]=i*15.0+(field_744-15.0);
                                request[1]=15.0-field_740;
                                request[2]=7.0f;
                                spawn(901,sakuya_cosine(-request[0])*100.0*facing_104+x_ec,y_f0+150.0+sakuya_sine(-request[0])*100.0,static_cast<unsigned char>(facing_104),1,request,3);
                            }
                            field_740+=1.0;
                        }
                        break;
                    }
                }
                if(advance()) {
                    set_action_and_finalize(704);
                    acceleration_y_100=0.25f;
                    return;
                }
                if(ENTRY(1)) {
                    velocity_x_f4=field_780;
                    velocity_y_f8=field_784;
                    acceleration_y_100=field_788;
                }
                if(FRAME(3,7)) {
                    acceleration_y_100=0.0;
                    dispatch_character_wave_handle(1);
                    word_730=1;
                }
                if(FRAME(5,1))acceleration_y_100=0.25f;
                return;
            }
            case 722:
            {
                if(!sequence_index_13e||sequence_index_13e==4)landing();
                if(ENTRY(2)) {
                    velocity_x_f4=0.0;
                    velocity_y_f8=0.0;
                }
                if(sequence_index_13e==1&&time_counter_144>=10) {
                    float request[3]= {
                        10.0f,0.0f,6.0f
                    };
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[0]=-10.0f;
                    request[2]=7.0f;
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    next_sequence_block();
                    if(facing_104==1) {
                        if(x_ec>640.0)velocity_x_f4=-250.0-URAND(450);
                        else velocity_x_f4=URAND(450)+250.0;
                    }
                    else {
                        if(x_ec>640.0)velocity_x_f4=URAND(450)+250.0;
                        else velocity_x_f4=-250.0-URAND(450);
                    }
                    velocity_y_f8=30.0;
                    acceleration_y_100=0.25f;
                    dispatch_character_wave_handle(13);
                    return;
                }
                if(sequence_index_13e==3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        next_sequence_block();
                        zero_motion();
                        y_f0=sakuya_surface(this);
                        return;
                    }
                }
                ADVANCE_TO(700);
                if(!time_counter_144) {
                    if(ENTRY(3)) {
                        float request[3]= {
                            0.0f,0.0f,8.0f
                        };
                        spawn(813,x_ec,y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=10.0f;
                        request[2]=9.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                        request[0]=-10.0f;
                        request[2]=10.0f;
                        spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    }
                    if(ENTRY(1)) {
                        for(float i=0.0f;i<6.0f;i+=1.0) {
                            float request[3]= {
                                0.0f,0.0f,i
                            };
                            spawn(813,x_ec-8*facing_104,y_f0+115.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                    }
                }
                return;
            }
            case 730:
            {
                landing();
                if(sequence_index_13e==1) {
                    if(time_counter_144==40) {
                        dispatch_character_wave_handle(53);
                        word_7a4=60;
                        related_170->field_114=1;
                        float request[3]= {
                            0.0f,0.0f,0.0f
                        };
                        spawn(854,640.0f,480.0f,1,-2,request,3);
                    }
                    if(time_counter_144>=100) {
                        next_sequence_block();
                        return;
                    }
                }
                if(sequence_index_13e==4&&time_counter_144>=75)next_sequence_block();
                ADVANCE_TO(700);
                if(!ENTRY(3))return;
                float request[3];
                request[0]=0.0f;
                switch(g_sakuya_action_match) {
                    case 3:
                    {
                        request[2]=0.0f;
                        for(float i=0.0f;i<8.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-100.0,(i*30.0+(y_f0-20.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<7.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-50.0,(i*30.0+(y_f0-5.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 2:
                    {
                        request[2]=1.0f;
                        for(float i=0.0f;i<8.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-100.0,(i*30.0+(y_f0-20.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<7.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-50.0,(i*30.0+(y_f0-5.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 1:
                    {
                        request[2]=1.0f;
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-100.0,(i*30.0+(y_f0+10.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            spawn(920,(URAND(200)+x_ec)-50.0,(i*30.0+(y_f0+25.0)+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                    case 0:
                    {
                        request[2]=1.0f;
                        for(float i=0.0f;i<6.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            double row=i*30.0;
                            spawn(920,(URAND(200)+x_ec)-100.0,URAND(20)+(y_f0+10.0+row)-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        for(float i=0.0f;i<5.0;i+=1.0) {
                            request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;
                            double row=i*30.0;
                            spawn(920,(URAND(200)+x_ec)-50.0,(y_f0+25.0+row+URAND(20))-10.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        break;
                    }
                }
                dispatch_character_wave_handle(55);
                return;
            }
            case 740:
            {
                landing();
                if(sequence_index_13e==1) {
                    switch(g_sakuya_action_match) {
                        case 3:
                        threshold=60;
                        break;
                        case 2:
                        threshold=70;
                        break;
                        case 1:
                        threshold=70;
                        break;
                        case 0:
                        threshold=70;
                        break;
                    }
                    if(time_counter_144>=threshold) {
                        next_sequence_block();
                        dispatch_character_wave_handle(53);
                        word_7a4=60;
                        related_170->field_114=1;
                        float request[3]= {
                            0.0f,0.0f,0.0f
                        };
                        spawn(854,640.0f,480.0f,1,-2,request,3);
                        return;
                    }
                }
                if(sequence_index_13e==3) {
                    if(time_counter_144>=60)next_sequence_block();
                    if(!(time_counter_144%2)&&field_73c<20.0f) {
                        float mode;
                        switch(g_sakuya_action_match) {
                            case 3:
                            mode=0.0f;
                            break;
                            case 2:
                            mode=1.0f;
                            break;
                            case 1:
                            mode=1.0f;
                            break;
                            case 0:
                            mode=2.0f;
                            break;
                        }
                        float request[3];
                        request[0]=field_73c*18.0;
                        request[1]=3.0f;
                        request[2]=mode;
                        {
                            spawn(930,sakuya_cosine(180.0-request[0])*350.0*facing_104+related_170->x_ec,sakuya_sine(180.0-request[0])*350.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                        }
                        dispatch_character_wave_handle(0);
                        switch(g_sakuya_action_match) {
                            case 2:
                            case 3:
                            {
                                request[0]=field_73c*18.0+9.0;
                                request[1]=3.0f;
                                request[2]=mode;
                                spawn(930,sakuya_cosine(180.0-request[0])*400.0*facing_104+related_170->x_ec,sakuya_sine(180.0-request[0])*400.0+related_170->y_f0+100.0,static_cast<unsigned char>(facing_104),1,request,3);
                                break;
                            }
                        }
                        field_73c+=1.0;
                    }
                }
                if(sequence_index_13e==4&&time_counter_144>=8)next_sequence_block();
                ADVANCE_TO(700);
                return;
            }
            case 770:
            {
                ADVANCE_TO(700);
                if(!FRAME(0,7))return;
                byte_655=1;
                finalize(-1);
                texture(2,-1);
                copy_action_word();
                word_76c=0;
                word_76a=1;
                word_766=0;
                word_768=0;
                word_764=0;
                event(23);
                return;
            }
            case 795:
            {
                if(!sequence_index_13e) {
                    velocity_y_f8-=static_cast<double>(0.3f);
                    if(static_cast<unsigned char>(crossed())) {
                        event(30);
                        select_sequence(1);
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        return;
                    }
                }
                ADVANCE_TO(700);
                return;
            }
            case 797:
            {
                if(sequence_index_13e<3) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        event(30);
                        select_sequence(3);
                        x_ec=480.0f;
                        y_f0=sakuya_surface(this);
                        zero_motion();
                        return;
                    }
                }
                ADVANCE_TO(0);
                return;
            }
            case 798:
            {
                if(sequence_index_13e==1&&time_counter_144>=60) {
                    next_sequence_block();
                    return;
                }
                if(advance()) {
                    set_action_and_finalize(700);
                    return;
                }
                if((sequence_index_13e==0&&frame_timer_142==0&&frame_index_140==1)) {
                    float request[3]= {
                        10.0f,0.0f,6.0f
                    };
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    request[0]=-10.0f;
                    request[2]=7.0f;
                    spawn(813,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,request,3);
                    dispatch_character_wave_handle(13);
                }
                return;
            }
            default:
            common_update();
            return;
        }
        advance();
    }
}
