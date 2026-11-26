#include <stddef.h>
namespace th105 {
    class MarisaActionStateView;
    extern int g_match_identifier;
    unsigned __cdecl marisa_random(int);
    unsigned __cdecl marisa_random_u32();
    float __cdecl marisa_atan(float,float);
    float __cdecl marisa_square(float);
    float __cdecl marisa_sine(float);
    float __cdecl marisa_cosine(float);
    float __fastcall marisa_surface(MarisaActionStateView *);
    unsigned char __fastcall marisa_on_surface(MarisaActionStateView *);
    struct MarisaActionScratch {
        void reset();
    };
    // Target-observed member widths and sequence vslots for this action root.
    // Every accessed offset is checked below; the opponent uses the same view.
    class MarisaActionStateView {
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
        __forceinline MarisaActionStateView *peer() {
            return related_170;
        }
        __forceinline int facing() {
            return facing_104;
        }
        __forceinline bool entry(short seq) {
            return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==seq;
        }
        __forceinline void reset_action_scratch() {
            reinterpret_cast<MarisaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
        }
        __forceinline void dash_dust(bool reverse) {
            double base=x_ec+50.0;
            effect(124,             static_cast<float>(base-static_cast<float>(marisa_random_u32()%100u)),             static_cast<float>(static_cast<float>(marisa_random_u32()%200u)+y_f0),             reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
        }
        __forceinline void dash_effects(bool reverse,double height,bool ahead) {
            effect(125,             ahead?static_cast<float>(80*facing_104+static_cast<double>(x_ec)):x_ec,             static_cast<float>(y_f0+height),             reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
            effect(126,x_ec,static_cast<float>(y_f0+height),             reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
            event(31);
        }
        __forceinline void decelerate(double step,bool clear) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-step);
            if(velocity_x_f4<0.0f){
                velocity_x_f4=0.0f;
                if(clear)byte_47e=0;
            }
        }
        __forceinline void spawn_offset(int object,int xoff,double height,float *p,int count) {
            spawn(object,             xoff==0?x_ec:xoff<0?static_cast<float>(x_ec-static_cast<float>(-xoff*facing_104)):static_cast<float>(xoff*facing_104+static_cast<double>(x_ec)),             height==0.0?y_f0:height<0.0?static_cast<float>(y_f0-(-height)):static_cast<float>(y_f0+height),             facing_104,1,p,count);
        }
        __forceinline void aimed900(int xoff,double height) {
            flip();
            float dx=static_cast<float>((peer()->x_ec-x_ec)*facing());
            float p[3];
            field_744=-marisa_atan(peer()->y_f0-y_f0,dx);
            p[0]=field_744;
            p[1]=15.0f;
            p[2]=static_cast<float>(marisa_random(4));
            spawn_offset(900,xoff,height,p,3);
            p[2]=4.0f;
            spawn_offset(900,xoff,height,p,3);
            dispatch_character_wave_handle(0);
        }
        __forceinline void spell_flash(int xoff,double height,int window) {
            word_48a=40;
            event(23);
            effect(115,static_cast<float>(xoff<0?x_ec-static_cast<float>(-xoff*facing()):xoff*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+height),static_cast<unsigned char>(facing_104),1);
            sequence_window(0,window,60);
            secondary_cycle();
        }
        __forceinline void shot825_burst(bool air,bool phase) {
            if(word_730>0 && (sequence_index_13e==2 || sequence_index_13e==3)){
                if(word_730%4==1){
                    if(phase)phase_counter(10);
                    field_180=1;
                    aim_short(-10,10);
                    dispatch_character_wave_handle(9);
                    if(!air)effect(129,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                    if(air?word_738==1:byte_750==1){
                        double base=word_734+30.0;
                        float p[3];
                        p[0]=static_cast<float>(base-static_cast<float>(marisa_random_u32()%60u));
                        p[1]=15.0f;
                        p[2]=static_cast<float>(marisa_random(4));
                        spawn_offset(825,44,85.0,p,3);
                    }
                    else{
                        double base=word_734+30.0;
                        float p[3];
                        p[0]=static_cast<float>(base-static_cast<float>(marisa_random_u32()%60u));
                        p[1]=15.0f;
                        p[2]=static_cast<float>(marisa_random(4));
                        spawn_offset(825,44,85.0,p,3);
                    }
                }
                ++word_730;
            }
        }
        __forceinline void rising_trail() {
            float p[3];
            p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+95.0-30.0);
            float speed=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(100)))*static_cast<double>(0.1f));
            p[1]=static_cast<float>(speed+10.0);
            p[2]=static_cast<float>(marisa_random_u32()&3u);
            spawn_offset(810,40,51.0,p,3);
        }
        __forceinline void aim_short(short low,short high) {
            float dx=static_cast<float>((peer()->x_ec-x_ec)*facing());
            word_734=static_cast<short>(-static_cast<short>(static_cast<int>(marisa_atan(peer()->y_f0-y_f0,dx))));
            if(word_734<low)word_734=low;
            if(word_734>high)word_734=high;
        }
        __forceinline void shot800_fan(int xoff,double height,int angle_step=-10) {
            if(word_730>0){
                ++word_730;
                if(!byte_750){
                    if(word_730%3==1 && word_732<3){
                        field_180=1;
                        phase_counter(10);
                        float p[3]={
                            static_cast<float>(word_734+angle_step*word_732),2.0f,0.0f
                        };
                        spawn_offset(800,xoff,height,p,3);
                        dispatch_character_wave_handle(0);
                        ++word_732;
                    }
                }
                else{
                    if(word_730%3==1 && word_732<5){
                        field_180=1;
                        phase_counter(10);
                        float p[3]={
                            static_cast<float>(word_734+angle_step*word_732),2.0f,0.0f
                        };
                        spawn_offset(800,xoff,height,p,3);
                        dispatch_character_wave_handle(0);
                        ++word_732;
                    }
                }
            }
        }
        __forceinline void idle_motion() {
            if(!byte_47e)zero_motion();
            else {
                if(velocity_x_f4>0.0f){
                    velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
                    if(velocity_x_f4<0.0f){
                        zero_motion();
                        byte_47e=0;
                    }
                }
                if(velocity_x_f4<0.0f){
                    velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);
                    if(velocity_x_f4>0.0f){
                        zero_motion();
                        byte_47e=0;
                    }
                }
            }
        }
        __forceinline void ground_face() {
            if(x_ec>peer()->x_ec)facing_104=255;
            if(x_ec<peer()->x_ec)facing_104=1;
        }
        unsigned char pad_004[0xe8];
        float x_ec;
        float y_f0;
        float velocity_x_f4;
        float velocity_y_f8;
        unsigned char pad_0fc[0x4];
        float acceleration_y_100;
        signed char facing_104;
        unsigned char pad_105[0x3];
        float field_108;
        float field_10c;
        unsigned char pad_110[0x1c];
        float field_12c;
        unsigned char pad_130[0xc];
        short action_id_13c;
        short sequence_index_13e;
        short frame_index_140;
        short frame_timer_142;
        int time_counter_144;
        unsigned char pad_148[0x20];
        MarisaActionStateView * owner_168;
        unsigned char pad_16c[0x4];
        MarisaActionStateView * related_170;
        short word_174;
        unsigned char pad_176[0x6];
        unsigned char byte_17c;
        unsigned char pad_17d[0x3];
        int field_180;
        unsigned char byte_184;
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
        unsigned char pad_4bc[0x14d];
        signed char byte_609;
        unsigned char pad_60a[0x1];
        signed char byte_60b;
        unsigned char pad_60c[0x3];
        signed char byte_60f;
        unsigned char pad_610[0x45];
        unsigned char byte_655;
        unsigned char pad_656[0x56];
        float field_6ac;
        unsigned char pad_6b0[0x4];
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
        float field_748;
        float field_74c;
        unsigned char byte_750;
        unsigned char byte_751;
        unsigned char pad_752[0x12];
        short word_764;
        short word_766;
        short word_768;
        short word_76a;
        short word_76c;
        unsigned char pad_76e[0x32];
        short word_7a0;
        short word_7a2;
        short word_7a4;
        short word_7a6;
        short word_7a8;
        unsigned char pad_7aa[0x2];
        float field_7ac;
        float field_7b0;
    };
    typedef char check_x_ec[offsetof(MarisaActionStateView,x_ec)==0xec?1:-1];
    typedef char check_y_f0[offsetof(MarisaActionStateView,y_f0)==0xf0?1:-1];
    typedef char check_velocity_x_f4[offsetof(MarisaActionStateView,velocity_x_f4)==0xf4?1:-1];
    typedef char check_velocity_y_f8[offsetof(MarisaActionStateView,velocity_y_f8)==0xf8?1:-1];
    typedef char check_acceleration_y_100[offsetof(MarisaActionStateView,acceleration_y_100)==0x100?1:-1];
    typedef char check_facing_104[offsetof(MarisaActionStateView,facing_104)==0x104?1:-1];
    typedef char check_action_id_13c[offsetof(MarisaActionStateView,action_id_13c)==0x13c?1:-1];
    typedef char check_sequence_index_13e[offsetof(MarisaActionStateView,sequence_index_13e)==0x13e?1:-1];
    typedef char check_frame_index_140[offsetof(MarisaActionStateView,frame_index_140)==0x140?1:-1];
    typedef char check_frame_timer_142[offsetof(MarisaActionStateView,frame_timer_142)==0x142?1:-1];
    typedef char check_time_counter_144[offsetof(MarisaActionStateView,time_counter_144)==0x144?1:-1];
    typedef char check_owner_168[offsetof(MarisaActionStateView,owner_168)==0x168?1:-1];
    typedef char check_related_170[offsetof(MarisaActionStateView,related_170)==0x170?1:-1];
    typedef char check_field_108[offsetof(MarisaActionStateView,field_108)==0x108?1:-1];
    typedef char check_field_10c[offsetof(MarisaActionStateView,field_10c)==0x10c?1:-1];
    typedef char check_field_12c[offsetof(MarisaActionStateView,field_12c)==0x12c?1:-1];
    typedef char check_word_174[offsetof(MarisaActionStateView,word_174)==0x174?1:-1];
    typedef char check_byte_17c[offsetof(MarisaActionStateView,byte_17c)==0x17c?1:-1];
    typedef char check_field_180[offsetof(MarisaActionStateView,field_180)==0x180?1:-1];
    typedef char check_byte_184[offsetof(MarisaActionStateView,byte_184)==0x184?1:-1];
    typedef char check_word_186[offsetof(MarisaActionStateView,word_186)==0x186?1:-1];
    typedef char check_byte_47e[offsetof(MarisaActionStateView,byte_47e)==0x47e?1:-1];
    typedef char check_byte_47f[offsetof(MarisaActionStateView,byte_47f)==0x47f?1:-1];
    typedef char check_word_482[offsetof(MarisaActionStateView,word_482)==0x482?1:-1];
    typedef char check_word_48a[offsetof(MarisaActionStateView,word_48a)==0x48a?1:-1];
    typedef char check_word_48c[offsetof(MarisaActionStateView,word_48c)==0x48c?1:-1];
    typedef char check_word_4a8[offsetof(MarisaActionStateView,word_4a8)==0x4a8?1:-1];
    typedef char check_word_4ac[offsetof(MarisaActionStateView,word_4ac)==0x4ac?1:-1];
    typedef char check_word_4ae[offsetof(MarisaActionStateView,word_4ae)==0x4ae?1:-1];
    typedef char check_field_4b8[offsetof(MarisaActionStateView,field_4b8)==0x4b8?1:-1];
    typedef char check_byte_609[offsetof(MarisaActionStateView,byte_609)==0x609?1:-1];
    typedef char check_byte_60b[offsetof(MarisaActionStateView,byte_60b)==0x60b?1:-1];
    typedef char check_byte_60f[offsetof(MarisaActionStateView,byte_60f)==0x60f?1:-1];
    typedef char check_byte_655[offsetof(MarisaActionStateView,byte_655)==0x655?1:-1];
    typedef char check_field_6ac[offsetof(MarisaActionStateView,field_6ac)==0x6ac?1:-1];
    typedef char check_field_6b4[offsetof(MarisaActionStateView,field_6b4)==0x6b4?1:-1];
    typedef char check_field_6b8[offsetof(MarisaActionStateView,field_6b8)==0x6b8?1:-1];
    typedef char check_field_6bc[offsetof(MarisaActionStateView,field_6bc)==0x6bc?1:-1];
    typedef char check_field_6c0[offsetof(MarisaActionStateView,field_6c0)==0x6c0?1:-1];
    typedef char check_field_6c4[offsetof(MarisaActionStateView,field_6c4)==0x6c4?1:-1];
    typedef char check_field_6c8[offsetof(MarisaActionStateView,field_6c8)==0x6c8?1:-1];
    typedef char check_byte_72c[offsetof(MarisaActionStateView,byte_72c)==0x72c?1:-1];
    typedef char check_word_730[offsetof(MarisaActionStateView,word_730)==0x730?1:-1];
    typedef char check_word_732[offsetof(MarisaActionStateView,word_732)==0x732?1:-1];
    typedef char check_word_734[offsetof(MarisaActionStateView,word_734)==0x734?1:-1];
    typedef char check_word_736[offsetof(MarisaActionStateView,word_736)==0x736?1:-1];
    typedef char check_word_738[offsetof(MarisaActionStateView,word_738)==0x738?1:-1];
    typedef char check_field_73c[offsetof(MarisaActionStateView,field_73c)==0x73c?1:-1];
    typedef char check_field_740[offsetof(MarisaActionStateView,field_740)==0x740?1:-1];
    typedef char check_field_744[offsetof(MarisaActionStateView,field_744)==0x744?1:-1];
    typedef char check_field_748[offsetof(MarisaActionStateView,field_748)==0x748?1:-1];
    typedef char check_field_74c[offsetof(MarisaActionStateView,field_74c)==0x74c?1:-1];
    typedef char check_byte_750[offsetof(MarisaActionStateView,byte_750)==0x750?1:-1];
    typedef char check_byte_751[offsetof(MarisaActionStateView,byte_751)==0x751?1:-1];
    typedef char check_word_764[offsetof(MarisaActionStateView,word_764)==0x764?1:-1];
    typedef char check_word_766[offsetof(MarisaActionStateView,word_766)==0x766?1:-1];
    typedef char check_word_768[offsetof(MarisaActionStateView,word_768)==0x768?1:-1];
    typedef char check_word_76a[offsetof(MarisaActionStateView,word_76a)==0x76a?1:-1];
    typedef char check_word_76c[offsetof(MarisaActionStateView,word_76c)==0x76c?1:-1];
    typedef char check_word_7a0[offsetof(MarisaActionStateView,word_7a0)==0x7a0?1:-1];
    typedef char check_word_7a2[offsetof(MarisaActionStateView,word_7a2)==0x7a2?1:-1];
    typedef char check_word_7a4[offsetof(MarisaActionStateView,word_7a4)==0x7a4?1:-1];
    typedef char check_word_7a6[offsetof(MarisaActionStateView,word_7a6)==0x7a6?1:-1];
    typedef char check_word_7a8[offsetof(MarisaActionStateView,word_7a8)==0x7a8?1:-1];
    typedef char check_field_7ac[offsetof(MarisaActionStateView,field_7ac)==0x7ac?1:-1];
    typedef char check_field_7b0[offsetof(MarisaActionStateView,field_7b0)==0x7b0?1:-1];
}
// Original Japanese v1.06a action root at 0x004A3710.
// Canonical unit: exact-first-marisa-action-state.
namespace th105 {
    void MarisaActionStateView::dispatch_action_state_vslot28() {
        word_7a0=0;
        word_7a2=106;
        if(word_7a6>0){
            if((action_id_13c>=600 && action_id_13c!=615) || (action_id_13c==615 && !frame_index_140)){
                word_7a6=0;
                word_7a8=0;
                word_7a4=0;
                field_7ac=0.0f;
                field_7b0=0.0f;
            }
            --word_7a6;
            --word_7a8;
            if(word_174<=0 || peer()->word_174<=0){
                word_7a6=0;
                word_7a8=0;
                word_7a4=0;
            }
            if(action_id_13c>=50 && action_id_13c<=149){
                word_7a8=0;
                word_7a4=0;
            }
            if(word_7a8<=0){
                word_7a8=0;
                word_7a4=0;
            }
            if(!word_7a4){
                if(field_7b0>3.0f){
                    field_7b0=static_cast<float>(field_7b0-static_cast<double>(0.1f));
                    if(field_7b0<3.0f)field_7b0=3.0f;
                }
                if(field_7b0<3.0f){
                    field_7b0=static_cast<float>(field_7b0+static_cast<double>(0.1f));
                    if(field_7b0>3.0f)field_7b0=3.0f;
                }
            }
            if(word_7a4>=1 && word_7a4<=7){
                // Native 4A38CD/38FF compares the adjusted value with 3, then stores 12.
                if(field_7b0>12.0f){
                    field_7b0=static_cast<float>(field_7b0-static_cast<double>(0.1f));
                    if(field_7b0<3.0f)field_7b0=12.0f;
                }
                if(field_7b0<12.0f){
                    field_7b0=static_cast<float>(field_7b0+static_cast<double>(0.1f));
                    if(field_7b0>3.0f)field_7b0=12.0f;
                }
                if(word_7a8%5==0 && word_7a4==1 && word_7a8>0)word_7a4=static_cast<short>(marisa_random(4)+2);
            }
            if(word_7a4==8){
                if(field_7b0>0.5f){
                    field_7b0=static_cast<float>(field_7b0-static_cast<double>(0.1f));
                    if(field_7b0<0.5f)field_7b0=0.5f;
                }
                if(field_7b0<0.5f){
                    field_7b0=static_cast<float>(field_7b0+static_cast<double>(0.1f));
                    if(field_7b0>0.5f)field_7b0=0.5f;
                }
            }
            field_7ac-=field_7b0;
        }
        else{
            word_7a6=0;
            word_7a8=0;
            word_7a4=0;
            field_7ac=0.0f;
            field_7b0=0.0f;
        }
        if(action_id_13c==720){
            if(sequence_index_13e==1){
                field_740=static_cast<float>(field_740+4.0);
                if(field_740>=120.0)field_740=120.0f;
                if(field_744>3.0f){
                    field_744=static_cast<float>(field_744-static_cast<double>(0.1f));
                    if(field_744<=3.0f)field_744=3.0f;
                }
                if(field_744<3.0f){
                    field_744=static_cast<float>(field_744+static_cast<double>(0.1f));
                    if(field_744>=3.0f)field_744=3.0f;
                }
                field_73c+=field_744;
            }
            if(sequence_index_13e>=2 && sequence_index_13e<=5){
                if(field_744>3.0f){
                    field_744=static_cast<float>(field_744-static_cast<double>(0.1f));
                    if(field_744<=3.0f)field_744=3.0f;
                }
                if(field_744<3.0f){
                    field_744=static_cast<float>(field_744+static_cast<double>(0.1f));
                    if(field_744>=3.0f)field_744=3.0f;
                }
                field_73c+=field_744;
            }
            if(sequence_index_13e==6){
                // Native compares against 12 before adjustment, then clamps to 11.
                if(field_744>12.0f){
                    field_744=static_cast<float>(field_744-static_cast<double>(0.1f));
                    if(field_744<=11.0f)field_744=11.0f;
                }
                if(field_744<12.0f){
                    field_744=static_cast<float>(field_744+static_cast<double>(0.1f));
                    if(field_744>=11.0f)field_744=11.0f;
                }
                field_73c+=field_744;
            }
            if(sequence_index_13e==7){
                if(field_744>0.5f){
                    field_744=static_cast<float>(field_744-static_cast<double>(0.1f));
                    if(field_744<=0.5f)field_744=0.5f;
                }
                if(field_744<0.5f){
                    field_744=static_cast<float>(field_744+static_cast<double>(0.1f));
                    if(field_744>=0.5f)field_744=0.5f;
                }
                field_73c+=field_744;
            }
        }
        if(action_id_13c>149 && action_id_13c<159 && !byte_751){
            byte_751=1;
            if(action_id_13c>149 && action_id_13c<154)spawn_offset(998,57,94.0,0,0);
            if(action_id_13c>153 && action_id_13c<158)spawn_offset(998,57,60.0,0,0);
            if(action_id_13c==158)spawn_offset(998,57,100.0,0,0);
        }
        if(word_186 || peer()->word_48c)return;
        switch(action_id_13c){
        case 0:
            landing();
            if(velocity_x_f4==0.0f)byte_47e=0;
            idle_motion();
            break;
        case 1:
            landing();
            idle_motion();
            if(advance() && !frame_index_140)set_action_and_finalize(2);
            return;
        case 2:
            landing();
            idle_motion();
            break;
        case 3:
            landing();
            idle_motion();
            if(advance() && !frame_index_140)set_action_and_finalize(0);
            return;
        case 4:
            landing();
            velocity_x_f4=6.0f;
            break;
        case 5:
            landing();
            velocity_x_f4=-5.0f;
            break;
        case 6:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e && !byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        set_action_and_finalize(10);
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                advance();
                if(entry(1)){
                    velocity_x_f4=(0.0f);
                    velocity_y_f8=16.0f;
                    acceleration_y_100=0.75f;
                    byte_47e=0;
                }
            }
            return;
        case 7:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e && !byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        set_action_and_finalize(10);
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                advance();
                if(entry(1)){
                    velocity_x_f4=(5.0f);
                    velocity_y_f8=16.0f;
                    acceleration_y_100=0.75f;
                    byte_47e=0;
                }
            }
            return;
        case 8:
            {
                if(!sequence_index_13e) {
                    landing();
                    if(!sequence_index_13e && !byte_47e)zero_motion();
                }
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())) {
                        set_action_and_finalize(10);
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                advance();
                if(entry(1)){
                    velocity_x_f4=(-4.0f);
                    velocity_y_f8=16.0f;
                    acceleration_y_100=0.75f;
                    byte_47e=0;
                }
            }
            return;
        case 9:
            if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            break;
        case 10:
            landing();
            zero_motion();
            if(advance()){
                if(field_6b8)set_action_and_finalize(2);
                else set_action_and_finalize(0);
            }
            return;
        case 197:
            if((!sequence_index_13e && frame_index_140<=4) || sequence_index_13e==2)landing();
            if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){
                y_f0=marisa_surface(this);
                zero_motion();
                select_sequence(2);
                return;
            }
            if(advance()){
                if(byte_72c==2){
                    set_action_and_finalize(700);
                    word_4a8=3;
                    word_4ac=3;
                    return;
                }
                set_action_and_finalize(0);
                if(field_6b8>0)set_action_and_finalize(1);
            }
            if(sequence_index_13e==2 && frame_index_140==3 && !frame_timer_142)ground_face();
            if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142){
                velocity_y_f8=6.0f;
                velocity_x_f4=14.5f;
                acceleration_y_100=0.5f;
            }
            return;
        case 198:
            if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==2)landing();
            if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){
                y_f0=marisa_surface(this);
                zero_motion();
                select_sequence(2);
                return;
            }
            if(advance()){
                if(byte_72c==2){
                    set_action_and_finalize(700);
                    word_4a8=3;
                    word_4ac=3;
                    return;
                }
                set_action_and_finalize(0);
                if(field_6b8>0)set_action_and_finalize(1);
            }
            if(sequence_index_13e==2 && frame_index_140==3 && !frame_timer_142)ground_face();
            if(!sequence_index_13e && frame_index_140==4 && !frame_timer_142){
                velocity_y_f8=6.0f;
                velocity_x_f4=-14.5f;
                acceleration_y_100=0.5f;
            }
            return;
        case 199:
            landing();
            if(advance()){
                if(byte_72c==2){
                    set_action_and_finalize(700);
                    word_4a8=3;
                    word_4ac=3;
                    return;
                }
                set_action_and_finalize(0);
                if(field_6b8>0)set_action_and_finalize(1);
            }
            if(!sequence_index_13e && frame_index_140==12 && !frame_timer_142)ground_face();
            return;
        case 200:
            landing();
            byte_47e=1;
            if(velocity_x_f4>12.0f){
                velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
                if(velocity_x_f4<12.0f)velocity_x_f4=12.0f;
            }
            advance();
            if(sequence_index_13e==1){
                if(time_counter_144%5==0)dash_dust(false);
                if(field_6b8<0){
                    if(field_6b4*facing()>0)set_action_and_finalize(212);
                    else set_action_and_finalize(211);
                    return;
                }
                ++word_730;
                if((field_6b4*facing()<=0 && word_730>5) || word_730>45){
                    set_action_and_finalize(204);
                    return;
                }
            }
            if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){
                velocity_x_f4=15.0f;
                dash_effects(false,80.0,true);
            }
            return;
        case 201:
            if(!sequence_index_13e || sequence_index_13e==3)landing();
            if(sequence_index_13e==3){
                velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);
                if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
            }
            if(!marisa_on_surface(this) && time_counter_144%5==0)dash_dust(true);
            if(sequence_index_13e<3){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    velocity_y_f8=0.0f;
                    acceleration_y_100=0.0f;
                    y_f0=marisa_surface(this);
                    select_sequence(3);
                    return;
                }
            }
            if(advance()){
                set_action_and_finalize(0);
                zero_motion();
                return;
            }
            if(entry(1)){
                velocity_x_f4=-14.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(true,80.0,false);
            }
            return;
        case 202:
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                zero_motion();
                y_f0=marisa_surface(this);
                set_action_and_finalize(10);
                return;
            }
            if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
            advance();
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){
                word_730=0;
                velocity_x_f4=11.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(false,110.0,true);
            }
            if(entry(2))flip();
            return;
        case 203:
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                zero_motion();
                y_f0=marisa_surface(this);
                set_action_and_finalize(10);
                return;
            }
            if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
            advance();
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
                velocity_x_f4=-11.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(true,120.0,false);
            }
            if(entry(2))flip();
            return;
        case 204:
            landing();
            velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
            if(velocity_x_f4<0.0f){
                velocity_x_f4=0.0f;
                byte_47e=0;
            }
            if(advance()){
                set_action_and_finalize(0);
                byte_47e=0;
            }
            return;
        case 208:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(!entry(1))return;
                {
                    velocity_x_f4=(0.0f);
                    velocity_y_f8=(22.5f);
                    acceleration_y_100=(0.85f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
        case 211:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(!entry(1))return;
                {
                    velocity_x_f4=(3.0f);
                    velocity_y_f8=(22.5f);
                    acceleration_y_100=(0.85f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
        case 212:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(!entry(1))return;
                {
                    velocity_x_f4=(10.0f);
                    velocity_y_f8=(16.0f);
                    acceleration_y_100=(0.7f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
            // Flight rate, release gates and facing reloads follow the complete target CFG.
        case 214:
            {
                if (advance()) {
                    set_action_and_finalize(9);
                    return;
                }
                if(entry(1))event(31);
                if(entry(6)){
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
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 1.5);
                        else field_740 = static_cast<float>(field_740 + 0.5);
                    }
                    if (word_734 < 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 1.5);
                        else field_740 = static_cast<float>(field_740 - 0.5);
                    }
                    velocity_x_f4 = marisa_cosine(field_740) * field_73c;
                    velocity_y_f8 = marisa_sine(field_740) * field_73c;
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
                        effect(125,                         marisa_cosine(field_740) * 100.0 * facing_104 + x_ec,                         marisa_sine(field_740) * 100.0 + y_f0 + 100.0,                         facing_104, 1);
                    }
                    if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                        if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                            reset_action_scratch();
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
                    y_f0 = marisa_surface(this);
                    acceleration_y_100 = 0.0f;
                    velocity_y_f8 = 0.0f;
                    if (sequence_index_13e < 5) {
                        reset_action_scratch();
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
            landing();
            if(velocity_x_f4>0.0f){
                velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);
                if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
            }
            if(velocity_x_f4<0.0f){
                velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);
                if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
            }
            if(advance())set_action_and_finalize(0);
            return;
        case 220:
            {
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(entry(1)) {
                    velocity_x_f4=(0.0f);
                    velocity_y_f8=(22.5f);
                    acceleration_y_100=(0.85f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
        case 209:
            case 221:{
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(entry(1)) {
                    velocity_x_f4=(10.0f);
                    velocity_y_f8=(18.0f);
                    acceleration_y_100=(0.85f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
        case 210:
            case 222:{
                if(!sequence_index_13e)landing();
                if(static_cast<unsigned char>(crossed())) {
                    set_action_and_finalize(10);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
                if(marisa_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
                if(sequence_index_13e>0) {
                    velocity_y_f8-=acceleration_y_100;
                    if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
                }
                if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
                advance();
                if(entry(1)) {
                    velocity_x_f4=(-10.0f);
                    velocity_y_f8=(18.0f);
                    acceleration_y_100=(0.85f);
                    byte_47e=0;
                    effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
                }
            }
            return;
        case 223:
            landing();
            byte_47e=1;
            advance();
            if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
                if(sequence_index_13e!=1)return;
                if(!word_730){
                    velocity_x_f4=7.5f;
                    dash_effects(false,80.0,true);
                }
            }
            if(sequence_index_13e==1){
                if(time_counter_144%5==0)dash_dust(false);
                ++word_730;
                if((field_6b4*facing()<=0 && word_730>15) || word_730>45){
                    set_action_and_finalize(204);
                    return;
                }
            }
            return;
        case 224:
            if(!sequence_index_13e || sequence_index_13e==3)landing();
            if(sequence_index_13e==3){
                velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);
                if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
            }
            if(!marisa_on_surface(this) && time_counter_144%5==0)dash_dust(true);
            if(sequence_index_13e<3){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    velocity_y_f8=0.0f;
                    acceleration_y_100=0.0f;
                    y_f0=marisa_surface(this);
                    select_sequence(3);
                    return;
                }
            }
            if(advance()){
                set_action_and_finalize(0);
                velocity_x_f4=0.0f;
                acceleration_y_100=0.0f;
                return;
            }
            if(entry(1) && !word_730){
                word_730=1;
                velocity_x_f4=-14.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(true,80.0,false);
            }
            return;
        case 225:
            if(sequence_index_13e>=1)velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                zero_motion();
                y_f0=marisa_surface(this);
                set_action_and_finalize(10);
                return;
            }
            if(sequence_index_13e>=2 && time_counter_144%5==0)dash_dust(true);
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                velocity_x_f4=-11.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(true,120.0,false);
            }
            return;
        case 226:
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                zero_motion();
                y_f0=marisa_surface(this);
                set_action_and_finalize(10);
                return;
            }
            if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                word_730=0;
                velocity_x_f4=11.0f;
                velocity_y_f8=4.0f;
                acceleration_y_100=0.5f;
                dash_effects(false,110.0,true);
            }
            if(entry(2))flip();
            return;
        case 300:
            landing();
            if(directional(0))return;
            if(byte_47e)decelerate(0.5,true);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142 && frame_index_140==4){
                event(27);
                byte_47e=0;
            }
            return;
        case 301:
            landing();
            if(directional(0))return;
            if(byte_47e)decelerate(0.5,true);
            if(frame_index_140>4)decelerate(1.5,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142){
                if(frame_index_140==3)velocity_x_f4=30.0f;
                if(!frame_timer_142 && frame_index_140==4){
                    velocity_x_f4=10.0f;
                    event(27);
                    byte_47e=0;
                }
            }
            if(frame_index_140>3)decelerate(0.5,false);
            return;
        case 302:
            if(sequence_index_13e==0 || sequence_index_13e==1 || sequence_index_13e==4)landing();
            if(frame_index_140<2 && !field_6bc)byte_750=0;
            if(!sequence_index_13e){
                if(velocity_x_f4>0.0f)velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);
                if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
            }
            if(entry(2)){
                dispatch_character_wave_handle(17);
                velocity_x_f4=15.5f;
                velocity_y_f8=6.5f;
                acceleration_y_100=0.55f;
            }
            if(entry(3)){
                dispatch_character_wave_handle(17);
                velocity_x_f4=18.5f;
                velocity_y_f8=7.5f;
                acceleration_y_100=0.55f;
            }
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1){
                if(!byte_750 && time_counter_144<2){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144>12){
                    select_sequence(3);
                    return;
                }
                if(time_counter_144==2)effect(62,x_ec,static_cast<float>(y_f0+68.0),static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==3 || sequence_index_13e==2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    dispatch_character_wave_handle(18);
                    select_sequence(4);
                    y_f0=marisa_surface(this);
                    velocity_y_f8=0.0f;
                    velocity_x_f4=5.0f;
                    return;
                }
            }
            if(sequence_index_13e==4)decelerate(0.5,false);
            return;
        case 303:
            landing();
            if(directional(0))return;
            if(static_cast<signed char>(byte_47e)>0)decelerate(static_cast<double>(0.6f),true);
            if(advance())set_action_and_finalize(2);
            if(!frame_timer_142 && frame_index_140==3)event(27);
            return;
        case 304:
            landing();
            if(directional(1))return;
            if(velocity_x_f4>0.0f)decelerate(2.0,false);
            if(!field_6bc)byte_750=0;
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                set_action_and_finalize(0);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
                if(byte_750==1){
                    next_sequence_block();
                    effect(62,static_cast<float>(75*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+98.0),static_cast<unsigned char>(facing_104),1);
                    return;
                }
                velocity_x_f4=15.0f;
                event(28);
            }
            if(sequence_index_13e==1 && !frame_timer_142){
                if(frame_index_140==1){
                    velocity_x_f4=25.0f;
                    event(28);
                }
                if(!frame_timer_142 && frame_index_140==4)velocity_x_f4=0.0f;
            }
            return;
        case 305:
            landing();
            if(directional(1))return;
            if(frame_index_140>4)decelerate(1.0,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142 && frame_index_140==4)event(28);
            return;
        case 306:
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(sequence_index_13e==1 && time_counter_144>12)next_sequence_block();
            if(advance())set_action_and_finalize(9);
            if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142)event(27);
            return;
        case 307:
            if(!field_6bc)byte_750=0;
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                set_action_and_finalize(9);
                return;
            }
            if(!sequence_index_13e){
                if(!frame_timer_142 && frame_index_140==3 && byte_750==1){
                    next_sequence_block();
                    return;
                }
                if(!frame_timer_142 && frame_index_140==5){
                    dispatch_character_wave_handle(1);
                    velocity_x_f4=-8.0f;
                    velocity_y_f8=7.0f;
                    acceleration_y_100=0.5f;
                    float p[3]={
                        0.0f,0.0f,1.0f
                    };
                    spawn_offset(848,67,110.0,p,3);
                }
            }
            if(sequence_index_13e==1){
                if(!frame_index_140){
                    if(!byte_750 && time_counter_144<5){
                        select_sequence(0);
                        frame_index_140=3;
                        return;
                    }
                    if(time_counter_144==5)effect(62,static_cast<float>(x_ec-static_cast<float>(70*facing())),static_cast<float>(y_f0+180.0),static_cast<unsigned char>(facing_104),1);
                }
                if(!frame_timer_142 && frame_index_140==3){
                    dispatch_character_wave_handle(1);
                    velocity_x_f4=-8.0f;
                    velocity_y_f8=7.0f;
                    acceleration_y_100=0.5f;
                    // The target writes only slots 0/1 while passing count 3.
                    float p[3];
                    p[0]=0.0f;
                    p[1]=20.0f;
                    spawn_offset(804,67,110.0,p,3);
                }
            }
            return;
        case 308:
            if(!field_6bc)byte_750=0;
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                set_action_and_finalize(9);
                return;
            }
            if(!sequence_index_13e){
                if(!frame_timer_142 && frame_index_140==3 && byte_750==1){
                    next_sequence_block();
                    return;
                }
                if(!frame_timer_142 && frame_index_140==5){
                    dispatch_character_wave_handle(1);
                    velocity_x_f4=-4.0f;
                    velocity_y_f8=8.0f;
                    acceleration_y_100=0.5f;
                    float p[3]={
                        60.0f,1.0f,1.0f
                    };
                    spawn_offset(848,30,30.0,p,3);
                }
            }
            if(sequence_index_13e==1){
                if(!frame_index_140){
                    if(!byte_750 && time_counter_144<5){
                        select_sequence(0);
                        frame_index_140=3;
                        return;
                    }
                    if(time_counter_144==5)effect(62,static_cast<float>(x_ec-static_cast<float>(70*facing())),static_cast<float>(y_f0+180.0),static_cast<unsigned char>(facing_104),1);
                }
                if(!frame_timer_142 && frame_index_140==3){
                    dispatch_character_wave_handle(1);
                    velocity_x_f4=-4.0f;
                    velocity_y_f8=8.0f;
                    acceleration_y_100=0.5f;
                    // The target writes only slots 0/1 while passing count 3.
                    float p[3];
                    p[0]=60.0f;
                    p[1]=20.0f;
                    spawn_offset(804,30,30.0,p,3);
                }
            }
            return;
        case 309:
            velocity_y_f8-=acceleration_y_100;
            velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.3f));
            if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(advance())set_action_and_finalize(9);
            if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){
                event(29);
                velocity_x_f4=10.0f;
                velocity_y_f8=15.0f;
                acceleration_y_100=0.85f;
            }
            return;
        case 310:
            //4A74D4 TEST AH,5/JP rejects unordered values: clamp only ordered FX<0.
            if(sequence_index_13e==2){
                decelerate(1.0,false);
                landing();
            }
            else{
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    select_sequence(2);
                    y_f0=marisa_surface(this);
                    velocity_y_f8=0.0f;
                    acceleration_y_100=0.0f;
                    field_180=1;
                }
            }
            if(advance()){
                if(field_6b8>0){
                    set_action_and_finalize(2);
                    return;
                }
                set_action_and_finalize(3);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7)event(29);
            return;
        case 320:
            landing();
            if(directional(0))return;
            if(frame_index_140>1)decelerate(2.0,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142 && frame_index_140==2){
                event(28);
                byte_47e=0;
            }
            return;
        case 321:
            landing();
            if(directional(0))return;
            if(frame_index_140>3)decelerate(0.5,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142 && frame_index_140==3){
                event(28);
                velocity_x_f4=7.5f;
                byte_47e=0;
            }
            return;
        case 322:
            landing();
            if(directional(1))return;
            if(frame_index_140>5)decelerate(3.0,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142){
                if(frame_index_140==4){
                    velocity_x_f4=15.0f;
                    float p[3]={
                        0.0f,0.0f,0.0f
                    };
                    spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
                }
                if(!frame_timer_142 && frame_index_140==5){
                    event(29);
                    byte_47e=0;
                }
            }
            return;
        case 400:
            landing();
            if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=4)) && !field_6c0)byte_750=0;
            shot800_fan(94,102.0);
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1){
                if((!byte_750 && time_counter_144>=2 && time_counter_144<5) || time_counter_144>15){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==5)effect(62,static_cast<float>(x_ec-12*facing()),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                aim_short(-10,10);
                word_730=1;
                counter(200,45);
            }
            return;
        case 401:
            landing();
            if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=4)) && !field_6c0)byte_750=0;
            shot800_fan(96,130.0);
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1){
                if((!byte_750 && time_counter_144>=2 && time_counter_144<5) || time_counter_144>15){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==5)effect(62,static_cast<float>(x_ec-12*facing()),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                aim_short(-40,-20);
                word_730=1;
                counter(200,45);
            }
            return;
        case 402:
            landing();
            if(!field_6c0)byte_750=0;
            if(word_730>=0){
                --word_730;
                if(!word_730 && sequence_index_13e<4){
                    field_180=1;
                    dispatch_character_wave_handle(0);
                    phase_counter(5);
                    float p[3];
                    p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%30u)-15.0);
                    p[1]=static_cast<float>(15+2*word_732);
                    p[2]=static_cast<float>(static_cast<float>(marisa_random_u32()&3u)+2.0);
                    spawn_offset(800,87,67.0,p,3);
                    word_730=4;
                    ++word_732;
                }
            }
            if(advance())set_action_and_finalize(2);
            if(sequence_index_13e==3 && (!byte_750 || time_counter_144>=30)){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                word_730=1;
                counter(200,45);
                effect(62,static_cast<float>(90*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+70.0),static_cast<unsigned char>(facing_104),1);
            }
            return;
        case 404:
            if(sequence_index_13e==3)landing();
            if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=4)) && !field_6c0)byte_750=0;
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){
                select_sequence(3);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            shot800_fan(80,115.0);
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1){
                if((!byte_750 && time_counter_144>=2 && time_counter_144<=4) || time_counter_144>15){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==5)effect(62,static_cast<float>(x_ec-25*facing()),static_cast<float>(y_f0+125.0),static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                velocity_x_f4=-6.0f;
                velocity_y_f8=6.0f;
                acceleration_y_100=0.5f;
                aim_short(-10,10);
                word_730=1;
                counter(200,45);
            }
            if(entry(3))set_action_and_finalize(9);
            return;
        case 406:
            if(sequence_index_13e==3)landing();
            if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=4)) && !field_6c0)byte_750=0;
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){
                select_sequence(3);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            shot800_fan(69,87.0,10);
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1){
                if((!byte_750 && time_counter_144>=2 && time_counter_144<=4) || time_counter_144>15){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==5 && byte_750==1)effect(62,static_cast<float>(x_ec-25*facing()),static_cast<float>(y_f0+125.0),static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                velocity_x_f4=-6.0f;
                velocity_y_f8=6.0f;
                acceleration_y_100=0.5f;
                aim_short(20,40);
                word_730=1;
                counter(200,45);
            }
            if(entry(3))set_action_and_finalize(9);
            return;
        case 408:
            landing();
            decelerate(0.75,false);
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
                dispatch_character_wave_handle(1);
                float p[3]={
                    0.0f,2.0f,1.0f
                };
                spawn_offset(848,106,103.0,p,3);
            }
            return;
        case 409:
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){
                set_action_and_finalize(10);
                zero_motion();
                y_f0=marisa_surface(this);
                return;
            }
            if(advance())set_action_and_finalize(9);
            return;
        case 410:
            landing();
            if(!field_6c4)byte_750=0;
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                aim_short(-20,20);
                dispatch_character_wave_handle(2);
                counter(200,60);
                field_180=1;
                phase_counter(50);
                if(word_738){
                    float p[3]={
                        static_cast<float>(word_734),5.0f,1.0f
                    };
                    spawn_offset(801,44,85.0,p,3);
                }
                else{
                    float p[3]={
                        static_cast<float>(word_734),5.0f,0.0f
                    };
                    spawn_offset(801,44,85.0,p,3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1 && time_counter_144>0){
                if((!byte_750 && time_counter_144<=9) || time_counter_144>=30){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==10){
                    effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+93.0),static_cast<unsigned char>(facing_104),1);
                    word_738=1;
                }
            }
            if(sequence_index_13e==3 && time_counter_144>20)next_sequence_block();
            return;
        case 411:
            landing();
            if(sequence_index_13e<2 && !field_6c4)byte_750=0;
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                phase_counter(50);
                aim_short(-10,10);
                dispatch_character_wave_handle(4);
                field_180=1;
                counter(200,60);
                if(word_738==1)spawn_offset(803,44,85.0,0,0);
                else spawn_offset(803,44,85.0,0,0);
            }
            if(advance())set_action_and_finalize(0);
            if((sequence_index_13e==1 && time_counter_144>4 && (!byte_750 || time_counter_144>25)) || (sequence_index_13e==4 && time_counter_144>8))next_sequence_block();
            return;
        case 412:
            landing();
            if(sequence_index_13e<2 && !field_6c4)word_738=1;
            if(sequence_index_13e==2 && frame_index_140==1 && !frame_timer_142){
                dispatch_character_wave_handle(7);
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                field_180=1;
                counter(200,60);
                phase_counter(50);
                if(word_738==1)spawn_offset(802,70,162.0,p,3);
                else spawn_offset(802,70,162.0,p,3);
            }
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1 && time_counter_144>4)next_sequence_block();
            return;
        case 414:
            if(sequence_index_13e==5)landing();
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                select_sequence(5);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(!field_6c4)byte_750=0;
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                counter(200,60);
                field_180=1;
                phase_counter(50);
                aim_short(-40,40);
                dispatch_character_wave_handle(2);
                if(word_738){
                    float p[3]={
                        static_cast<float>(word_734),0.0f,1.0f
                    };
                    spawn_offset(801,48,104.0,p,3);
                }
                else{
                    float p[3]={
                        static_cast<float>(word_734),0.0f,0.0f
                    };
                    spawn_offset(801,48,104.0,p,3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(5)){
                set_action_and_finalize(9);
                return;
            }
            if(sequence_index_13e==1){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.01f));
                if((!byte_750 && time_counter_144<=9) || time_counter_144>30){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144==10){
                    word_738=1;
                    effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+107.0),static_cast<unsigned char>(facing_104),1);
                }
            }
            if(sequence_index_13e==3 && time_counter_144>20){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            return;
        case 415:
            if(sequence_index_13e==6)landing();
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<6){
                select_sequence(6);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(sequence_index_13e<2 && !field_6c4)byte_750=0;
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                aim_short(-10,10);
                dispatch_character_wave_handle(4);
                field_180=1;
                counter(200,60);
                phase_counter(50);
                if(word_738==1){
                    float p[3]={
                        static_cast<float>(word_734),2.0f,0.0f
                    };
                    spawn_offset(803,48,104.0,p,3);
                }
                else{
                    float p[3]={
                        static_cast<float>(word_734),2.0f,0.0f
                    };
                    spawn_offset(803,48,104.0,p,3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(6)){
                set_action_and_finalize(9);
                return;
            }
            if((sequence_index_13e==1 && time_counter_144>4 && (!byte_750 || time_counter_144>25)) || (sequence_index_13e==4 && time_counter_144>8)){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==5 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            return;
        case 416:
            if(sequence_index_13e==1)landing();
            if(!sequence_index_13e){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    next_sequence_block();
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                set_action_and_finalize(9);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                dispatch_character_wave_handle(2);
                velocity_x_f4=-4.0f;
                velocity_y_f8=8.0f;
                acceleration_y_100=0.5f;
                float p[3]={
                    60.0f,0.0f,0.0f
                };
                field_180=1;
                counter(200,60);
                phase_counter(50);
                spawn_offset(801,30,30.0,p,3);
            }
            return;
        case 418:
            landing();
            decelerate(0.5,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142){
                if(frame_index_140==4){
                    float p[3]={
                        0.0f,0.0f,0.0f
                    };
                    spawn_offset(848,0,0.0,p,3);
                }
                if(!frame_timer_142 && frame_index_140==5){
                    event(29);
                    byte_47e=0;
                }
            }
            return;
        case 420:
            landing();
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1 && time_counter_144>=2){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                field_180=1;
                word_7a8=40;
                word_7a4=1;
                word_730=1;
                counter(200,60);
            }
            return;
        case 421:
            landing();
            if(advance())set_action_and_finalize(2);
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                field_180=1;
                word_7a8=40;
                word_7a4=1;
                word_730=1;
                counter(200,60);
            }
            return;
        case 422:
            if(sequence_index_13e==3)landing();
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){
                select_sequence(3);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(advance())set_action_and_finalize(0);
            if(sequence_index_13e==1 && time_counter_144>=2){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                field_180=1;
                velocity_x_f4=-6.0f;
                velocity_y_f8=6.0f;
                acceleration_y_100=0.5f;
                word_7a8=40;
                word_7a4=1;
                word_730=1;
                counter(200,60);
            }
            if(entry(3))set_action_and_finalize(9);
            return;
        case 430:
            landing();
            if(sequence_index_13e<2 && !field_6c4)byte_750=0;
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                counter(200,120);
                word_7a8=60;
                word_7a4=8;
                field_180=1;
                phase_counter(50);
            }
            if(advance())set_action_and_finalize(0);
            if((sequence_index_13e==1 && time_counter_144>16) || (sequence_index_13e==3 && time_counter_144>20))next_sequence_block();
            return;
        case 431:
            landing();
            if(advance())set_action_and_finalize(2);
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                field_180=1;
                word_7a8=60;
                word_7a4=8;
                word_730=1;
                counter(200,120);
            }
            if(sequence_index_13e==3 && time_counter_144>20)next_sequence_block();
            return;
        case 432:
            if(sequence_index_13e==5)landing();
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                select_sequence(5);
                byte_47f=0;
                y_f0=marisa_surface(this);
                zero_motion();
                return;
            }
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                counter(200,120);
                field_180=1;
                word_7a8=60;
                word_7a4=8;
                phase_counter(50);
            }
            if(advance())set_action_and_finalize(0);
            if(entry(5)){
                set_action_and_finalize(9);
                return;
            }
            if(sequence_index_13e==1){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.01f));
                if(time_counter_144>16){
                    next_sequence_block();
                    return;
                }
            }
            if(sequence_index_13e==3 && time_counter_144>20){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            return;
        case 500:
            if(sequence_index_13e==4)landing();
            byte_17c=0;
            if(sequence_index_13e==1){
                if(time_counter_144>20){
                    set_action_and_finalize(504);
                    return;
                }
                if(time_counter_144%3==0){
                    float p[3];
                    p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+180.0-30.0);
                    p[1]=15.0f;
                    p[2]=static_cast<float>(marisa_random_u32()&3u);
                    spawn_offset(810,-95,100.0,p,3);
                }
                if(field_180!=0 && field_180!=1 && field_180!=3){
                    next_sequence_block();
                    velocity_x_f4=-5.0f;
                    velocity_y_f8=10.0f;
                    acceleration_y_100=0.35f;
                    return;
                }
            }
            if(sequence_index_13e==2 || sequence_index_13e==3){
                velocity_y_f8-=acceleration_y_100;
                velocity_x_f4=static_cast<float>(static_cast<double>(0.1f)+velocity_x_f4);
                if(velocity_x_f4>-1.0f)velocity_x_f4=-1.0f;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(4);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                spawn_offset(849,109,84.0,p,3);
                double y=y_f0;
                if(marisa_surface(this)==y)effect(128,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),-1);
                velocity_x_f4=20.0f;
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(6);
            }
            return;
        case 504:
            if(sequence_index_13e==2)landing();
            byte_17c=0;
            if(sequence_index_13e==0 || sequence_index_13e==1){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(2);
                }
            }
            if(advance())set_action_and_finalize(0);
            return;
        case 505:
            if(sequence_index_13e==3)landing();
            byte_17c=4;
            if(sequence_index_13e==1 || sequence_index_13e==2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                phase_counter(50);
                // Four native stores at 4AA153/169/175/17C, while the request count is three.
                float p[4]={
                    0.0f,27.5f,0.0f,0.0f
                };
                spawn_offset(811,109,84.0,p,3);
                effect(127,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),-1);
                velocity_x_f4=-7.5f;
                velocity_y_f8=10.0f;
                acceleration_y_100=0.55f;
                counter(200,120);
                dispatch_character_wave_handle(26);
            }
            return;
        case 506:
            if(sequence_index_13e==3)landing();
            byte_17c=4;
            if(sequence_index_13e==1 || sequence_index_13e==2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                phase_counter(50);
                float p[4]={
                    -30.0f,27.5f,0.0f,0.0f
                };
                spawn_offset(811,109,84.0,p,3);
                effect(127,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),-1);
                velocity_x_f4=-7.5f;
                velocity_y_f8=10.0f;
                acceleration_y_100=0.55f;
                counter(200,120);
                dispatch_character_wave_handle(26);
            }
            return;
        case 510:
            case 512:
            if(sequence_index_13e==4)landing();
            byte_17c=8;
            if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3){
                velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);
                if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(4);
                    field_12c=0.0f;
                }
                if(sequence_index_13e==1){
                    field_73c=static_cast<float>(field_73c+2.0);
                    field_12c=static_cast<float>(field_12c-25.0);
                    if(field_12c<-720.0f){
                        next_sequence_block();
                        field_12c=0.0f;
                        return;
                    }
                }
                if(sequence_index_13e==3 && time_counter_144>=24){
                    set_action_and_finalize(9);
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                spawn_offset(812,50,50.0,p,3);
                p[2]=1.0f;
                spawn_offset(812,50,50.0,p,3);
                velocity_x_f4=17.5f;
                velocity_y_f8=12.5f;
                acceleration_y_100=0.45f;
                counter(200,120);
                phase_counter(50);
                dispatch_character_wave_handle(6);
                field_108=0.0f;
                field_10c=100.0f;
            }
            return;
        case 520:
            if(!sequence_index_13e || sequence_index_13e==4)landing();
            byte_17c=1;
            if(sequence_index_13e==1){
                if(time_counter_144>20)next_sequence_block();
                if(time_counter_144%3==0)rising_trail();
            }
            if(sequence_index_13e>0 && sequence_index_13e<4){
                velocity_y_f8=static_cast<float>(velocity_y_f8-0.75);
                decelerate(0.5,false);
            }
            if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){
                next_sequence_block();
                y_f0=marisa_surface(this);
                zero_motion();
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    -85.0f,0.0f,1.0f
                };
                spawn_offset(849,61,232.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(5);
                counter(200,120);
                phase_counter(50);
                velocity_x_f4=12.5f;
                velocity_y_f8=17.5f;
                acceleration_y_100=0.6f;
            }
            return;
        case 521:
            if(!sequence_index_13e || sequence_index_13e==4)landing();
            byte_17c=1;
            if(sequence_index_13e==1){
                if(time_counter_144>20)next_sequence_block();
                if(time_counter_144%3==0)rising_trail();
            }
            if(sequence_index_13e>0 && sequence_index_13e<4){
                velocity_y_f8=static_cast<float>(velocity_y_f8-0.75);
                decelerate(static_cast<double>(0.4f),false);
            }
            if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){
                next_sequence_block();
                y_f0=marisa_surface(this);
                zero_motion();
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    -85.0f,0.0f,1.0f
                };
                spawn_offset(849,61,232.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(5);
                counter(200,120);
                phase_counter(50);
                velocity_x_f4=15.0f;
                velocity_y_f8=25.0f;
                acceleration_y_100=0.6f;
            }
            return;
        case 525:
            if(!sequence_index_13e || sequence_index_13e==4)landing();
            byte_17c=5;
            if(sequence_index_13e==1){
                if(time_counter_144>20){
                    next_sequence_block();
                    velocity_y_f8=static_cast<float>(velocity_y_f8*0.5);
                }
                if(time_counter_144%3==0)rising_trail();
            }
            if(sequence_index_13e>0 && sequence_index_13e<4){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.55f));
                decelerate(0.5,false);
            }
            if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){
                next_sequence_block();
                y_f0=marisa_surface(this);
                zero_motion();
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3];
                p[0]=-85.0f;
                p[1]=0.0f;
                if(byte_609>=4)p[2]=5.0f;
                if(byte_609<=3)p[2]=4.0f;
                if(byte_609<=1)p[2]=3.0f;
                spawn_offset(849,61,232.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(28);
                counter(200,120);
                phase_counter(50);
                velocity_x_f4=7.0f;
                velocity_y_f8=30.0f;
                acceleration_y_100=0.5f;
                field_180=1;
            }
            if(entry(3))field_180=1;
            return;
        case 526:
            if(!sequence_index_13e || sequence_index_13e==4)landing();
            byte_17c=5;
            if(sequence_index_13e==1){
                if(time_counter_144>30)next_sequence_block();
                if(time_counter_144%3==0)rising_trail();
            }
            if(sequence_index_13e>0 && sequence_index_13e<4){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.55f));
                decelerate(0.5,false);
            }
            if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){
                next_sequence_block();
                y_f0=marisa_surface(this);
                zero_motion();
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    -85.0f,0.0f,3.0f
                };
                spawn_offset(849,61,232.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(28);
                counter(200,120);
                phase_counter(50);
                velocity_x_f4=25.0f;
                velocity_y_f8=20.0f;
                acceleration_y_100=0.5f;
                field_180=1;
            }
            if(entry(3))field_180=1;
            return;
        case 530:
            landing();
            byte_17c=9;
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                float p[3]={
                    -70.0f,30.0f,0.0f
                };
                spawn_offset(817,18,164.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(30);
                counter(200,120);
                phase_counter(50);
                field_180=1;
            }
            return;
        case 531:
            landing();
            byte_17c=9;
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                float p[3]={
                    -70.0f,50.0f,0.0f
                };
                spawn_offset(817,18,164.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(30);
                counter(200,120);
                phase_counter(50);
                field_180=1;
            }
            return;
        case 540:
            landing();
            byte_17c=2;
            if(sequence_index_13e<=1 && !field_6c0)byte_750=0;
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                set_action_and_finalize(0);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float p[3]={
                    4.0f,0.0f,0.0f
                };
                spawn_offset(820,70,165.0,p,3);
                dispatch_character_wave_handle(7);
            }
            if(sequence_index_13e==1 && !frame_index_140 && !byte_750){
                select_sequence(0);
                frame_index_140=7;
            }
            return;
        case 541:
            landing();
            byte_17c=2;
            if(sequence_index_13e<=1 && !field_6c4)byte_750=0;
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                set_action_and_finalize(0);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float p[3]={
                    10.0f,0.0f,0.0f
                };
                spawn_offset(820,70,165.0,p,3);
                dispatch_character_wave_handle(7);
            }
            if(sequence_index_13e==1 && !frame_index_140 && !byte_750){
                select_sequence(0);
                frame_index_140=7;
            }
            return;
        case 542:
            if(sequence_index_13e==2)landing();
            byte_17c=2;
            if(sequence_index_13e<2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    select_sequence(2);
                    y_f0=marisa_surface(this);
                    return;
                }
            }
            if(sequence_index_13e<=1 && !field_6c0)byte_750=0;
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                set_action_and_finalize(9);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
                dispatch_character_wave_handle(7);
                velocity_x_f4=-4.0f;
                velocity_y_f8=8.0f;
                acceleration_y_100=0.5f;
                field_180=1;
                float p[3]={
                    0.0f,0.0f,1.0f
                };
                spawn_offset(820,30,62.0,p,3);
                counter(200,120);
                phase_counter(50);
            }
            return;
        case 545:
            landing();
            byte_17c=6;
            if(sequence_index_13e<=1 && !field_6c0)byte_750=0;
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                set_action_and_finalize(0);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                phase_counter(50);
                counter(200,120);
                field_180=1;
                float p=0.0f;
                spawn_offset(821,70,165.0,&p,1);
                dispatch_character_wave_handle(7);
            }
            if(sequence_index_13e==1 && !frame_index_140 && !byte_750){
                select_sequence(0);
                frame_index_140=7;
            }
            return;
        case 547:
            if(sequence_index_13e==2)landing();
            byte_17c=2;
            if(sequence_index_13e<2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    select_sequence(2);
                    y_f0=marisa_surface(this);
                    return;
                }
            }
            if(sequence_index_13e<=1 && !field_6c0)byte_750=0;
            if(advance())set_action_and_finalize(9);
            if(entry(1)){
                set_action_and_finalize(9);
                return;
            }
            if(!sequence_index_13e){
                if(!frame_timer_142 && frame_index_140==8 && byte_750==1){
                    next_sequence_block();
                    return;
                }
                if(!frame_timer_142 && frame_index_140==6){
                    field_180=1;
                    dispatch_character_wave_handle(7);
                    velocity_x_f4=-4.0f;
                    velocity_y_f8=8.0f;
                    acceleration_y_100=0.5f;
                    spawn_offset(816,30,62.0,0,0);
                    counter(200,120);
                    phase_counter(50);
                }
            }
            return;
        case 550:
            landing();
            byte_17c=10;
            if(advance())set_action_and_finalize(9);
            if(!frame_timer_142 && frame_index_140==5){
                float p[3];
                p[0]=-90.0f;
                p[1]=20.0f;
                p[2]=static_cast<float>(marisa_random(6));
                spawn_offset(822,53,124.0,p,3);
            }
            return;
        case 551:
            landing();
            byte_17c=10;
            if(advance())set_action_and_finalize(9);
            if(!frame_timer_142 && frame_index_140==5){
                float p[3];
                p[0]=180.0f;
                p[1]=20.0f;
                p[2]=static_cast<float>(marisa_random(6));
                spawn_offset(822,53,124.0,p,3);
            }
            return;
        case 560:
            {
                landing();
                byte_17c=3;
                if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=9)) && !(field_6c0))byte_750=0;
                shot825_burst(false,false);
                if(advance())set_action_and_finalize(0);
                if(sequence_index_13e==1){
                    if(time_counter_144>=4 && time_counter_144<=10){
                        if(!byte_750){
                            next_sequence_block();
                            return;
                        }
                        if(time_counter_144==10)effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+(95.0)),static_cast<unsigned char>(facing_104),1);
                    }
                    if(time_counter_144>=25){
                        next_sequence_block();
                        return;
                    }
                }
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(825,-24,95.0,p,3);
                }
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    word_730=1;
                    counter(200,120);
                    phase_counter(50);
                }
                if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25)){
                    next_sequence_block();
                    return;
                }
            }
            return;
        case 561:
            {
                landing();
                byte_17c=3;
                if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=9)) && !(field_6c4))byte_750=0;
                shot825_burst(false,true);
                if(advance())set_action_and_finalize(0);
                if(sequence_index_13e==1){
                    if(time_counter_144>=4 && time_counter_144<=10){
                        if(!byte_750){
                            next_sequence_block();
                            return;
                        }
                        if(time_counter_144==10)effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+(95.0)),static_cast<unsigned char>(facing_104),1);
                    }
                    if(time_counter_144>=25){
                        next_sequence_block();
                        return;
                    }
                }
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(825,-24,95.0,p,3);
                }
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    word_730=1;
                    counter(200,120);
                }
                if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25)){
                    next_sequence_block();
                    return;
                }
            }
            return;
        case 562:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=3;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=9)) && !(field_6c0))byte_750=0;
                shot825_burst(true,true);
                if(advance())set_action_and_finalize(0);
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1){
                    if(time_counter_144>=4 && time_counter_144<=10){
                        if(!byte_750){
                            next_sequence_block();
                            return;
                        }
                        if(time_counter_144==10)effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+(107.0)),static_cast<unsigned char>(facing_104),1);
                    }
                    if(time_counter_144>=25){
                        next_sequence_block();
                        return;
                    }
                }
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(825,-23,107.0,p,3);
                }
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    word_730=1;
                    counter(200,120);
                }
                if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25)){
                    next_sequence_block();
                }
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 563:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=3;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<=9)) && !(field_6c4))byte_750=0;
                shot825_burst(true,true);
                if(advance())set_action_and_finalize(0);
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1){
                    if(time_counter_144>=4 && time_counter_144<=10){
                        if(!byte_750){
                            next_sequence_block();
                            return;
                        }
                        if(time_counter_144==10)effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+(107.0)),static_cast<unsigned char>(facing_104),1);
                    }
                    if(time_counter_144>=25){
                        next_sequence_block();
                        return;
                    }
                }
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(825,-23,107.0,p,3);
                }
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    word_730=1;
                    counter(200,120);
                }
                if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25)){
                    next_sequence_block();
                }
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 565:
            {
                landing();
                byte_17c=7;
                if(sequence_index_13e<2 && !(field_6c0))byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    {
                        phase_counter(50);
                        field_180=1;
                        dispatch_character_wave_handle(29);
                    }
                    aim_short(-10,10);
                    dispatch_character_wave_handle(4);
                    counter(200,60);
                    float p[3];
                    p[0]=0.0f;
                    p[1]=0.0f;
                    if(byte_60b<=3)p[2]=0.0f;
                    else p[2]=6.0f;
                    // Native 4AD134..4AD1D7 captures direction/Y before either request.
                    int direction=static_cast<unsigned char>(facing_104);
                    double y=y_f0+(85.0);
                    if(word_738==1)                 spawn(826,static_cast<float>((44)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                    else                 spawn(826,static_cast<float>((44)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                }
                if(advance())set_action_and_finalize(0);
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(826,-24,95.0,p,3);
                }
                if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750 || time_counter_144>25))next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
            }
            return;
        case 566:
            {
                landing();
                byte_17c=7;
                if(sequence_index_13e<2 && !(field_6c4))byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    {
                        phase_counter(50);
                        field_180=1;
                        dispatch_character_wave_handle(29);
                    }
                    aim_short(-10,10);
                    dispatch_character_wave_handle(4);
                    counter(200,60);
                    float p[3];
                    p[0]=0.0f;
                    p[1]=0.0f;
                    if(byte_60b<=3)p[2]=0.0f;
                    else p[2]=6.0f;
                    // Native 4AD134..4AD1D7 captures direction/Y before either request.
                    int direction=static_cast<unsigned char>(facing_104);
                    double y=y_f0+(85.0);
                    if(word_738==1)                 spawn(826,static_cast<float>((44)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                    else                 spawn(826,static_cast<float>((44)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                }
                if(advance())set_action_and_finalize(0);
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(826,-24,95.0,p,3);
                }
                if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750 || time_counter_144>25))next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
            }
            return;
        case 567:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=7;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if(sequence_index_13e<2 && !(field_6c0))byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    aim_short(-10,10);
                    {
                        dispatch_character_wave_handle(29);
                        field_180=1;
                    }
                    counter(200,60);
                    phase_counter(50);
                    float p[3];
                    p[0]=0.0f;
                    p[1]=0.0f;
                    if(byte_60b<=3)p[2]=0.0f;
                    else p[2]=6.0f;
                    // Native 4AD134..4AD1D7 captures direction/Y before either request.
                    int direction=static_cast<unsigned char>(facing_104);
                    double y=y_f0+(104.0);
                    if(word_738==1)                 spawn(826,static_cast<float>((48)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                    else                 spawn(826,static_cast<float>((48)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                }
                if(advance())set_action_and_finalize(0);
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(826,-48,104.0,p,3);
                }
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750 || time_counter_144>25))next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 568:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=7;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if(sequence_index_13e<2 && !(field_6c4))byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    aim_short(-10,10);
                    {
                        dispatch_character_wave_handle(29);
                        field_180=1;
                    }
                    counter(200,60);
                    phase_counter(50);
                    float p[3];
                    p[0]=0.0f;
                    p[1]=0.0f;
                    if(byte_60b<=3)p[2]=0.0f;
                    else p[2]=6.0f;
                    // Native 4AD134..4AD1D7 captures direction/Y before either request.
                    int direction=static_cast<unsigned char>(facing_104);
                    double y=y_f0+(104.0);
                    if(word_738==1)                 spawn(826,static_cast<float>((48)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                    else                 spawn(826,static_cast<float>((48)*static_cast<signed char>(direction)+x_ec),y,direction,1,p,3);
                }
                if(advance())set_action_and_finalize(0);
                if(entry(1)){
                    float p[3]={
                        0.0f,0.0f,4.0f
                    };
                    spawn_offset(826,-48,104.0,p,3);
                }
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750 || time_counter_144>25))next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 570:
            {
                landing();
                byte_17c=11;
                if(sequence_index_13e<2 && !field_6c4)byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    phase_counter(50);
                    field_180=1;
                    dispatch_character_wave_handle(34);
                    counter(200,60);
                    float p[3]={
                        30.0f,0.0f,4.0f
                    };
                    if(word_738==1){
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                    else {
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                }
                if(advance())set_action_and_finalize(0);
                if(sequence_index_13e==1 && time_counter_144>2)next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>(10))next_sequence_block();
            }
            return;
        case 571:
            {
                landing();
                byte_17c=11;
                if(sequence_index_13e<2 && !field_6c4)byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    phase_counter(50);
                    field_180=1;
                    dispatch_character_wave_handle(34);
                    counter(200,60);
                    float p[3]={
                        45.0f,0.0f,4.0f
                    };
                    if(word_738==1){
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                    else {
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,44,85.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                }
                if(advance())set_action_and_finalize(0);
                if(sequence_index_13e==1 && time_counter_144>2)next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>(20))next_sequence_block();
            }
            return;
        case 572:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=11;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if(sequence_index_13e<2 && !field_6c4)byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    phase_counter(50);
                    field_180=1;
                    dispatch_character_wave_handle(34);
                    counter(200,60);
                    float p[3]={
                        30.0f,0.0f,4.0f
                    };
                    if(word_738==1){
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                    else {
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-10.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                }
                if(advance())set_action_and_finalize(0);
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1 && time_counter_144>2)next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>(10))next_sequence_block();
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 573:
            {
                if(sequence_index_13e==5)landing();
                byte_17c=11;
                {
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){
                        select_sequence(5);
                        byte_47f=0;
                        y_f0=marisa_surface(this);
                        zero_motion();
                        return;
                    }
                }
                if(sequence_index_13e<2 && !field_6c4)byte_750=0;
                if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
                    phase_counter(50);
                    field_180=1;
                    dispatch_character_wave_handle(34);
                    counter(200,60);
                    float p[3]={
                        45.0f,0.0f,4.0f
                    };
                    if(word_738==1){
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                    else {
                        spawn_offset(827,44,85.0,p,3);
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(n*5.0+20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                        {
                            float n=0.0f;
                            do{
                                p[1]=static_cast<float>(-n*5.0-20.0);
                                if(byte_60f<=3)p[2]=0.0f;
                                else p[2]=6.0f;
                                spawn_offset(827,48,104.0,p,3);
                                n=static_cast<float>(n+1.0);
                            }
                            while(n<3.0f);
                        }
                    }
                }
                if(advance())set_action_and_finalize(0);
                if(entry(5)){
                    set_action_and_finalize(9);
                    return;
                }
                if(sequence_index_13e==1 && time_counter_144>2)next_sequence_block();
                if(sequence_index_13e==3 && time_counter_144>(20))next_sequence_block();
                if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
            }
            return;
        case 599:
            if(word_730>0 && frame_index_140<7 && word_730<12){
                word_734=static_cast<short>(marisa_random_u32()%35u);
                float p[3];
                p[0]=static_cast<float>(-20-word_734);
                p[1]=static_cast<float>(static_cast<short>(static_cast<short>(marisa_random_u32()%5u)+10));
                p[2]=0.0f;
                spawn(807,static_cast<float>((word_730+1)*facing()*20+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
                p[0]=static_cast<float>(marisa_random_u32()%360u);
                p[1]=0.0f;
                p[2]=1.0f;
                spawn(801,static_cast<float>((word_730+1)*facing()*20+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
                if(word_730==1){
                    dispatch_character_wave_handle(0);
                    counter(200,120);
                }
                ++word_730;
            }
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142 && frame_index_140==5)word_730=1;
            return;
        case 600:
            landing();
            texture(5,2);
            if(sequence_index_13e==1){
                if(time_counter_144>60){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144%10==0)effect(127,static_cast<float>(x_ec-static_cast<float>(100*facing())),y_f0,static_cast<unsigned char>(facing_104),-1);
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142)spell_flash(-23,94.0,3);
            if(entry(1)){
                spawn_offset(990,-80,130.0,0,0);
                dispatch_character_wave_handle(10);
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                spawn_offset(850,25,87.0,p,3);
                p[2]=2.0f;
                spawn_offset(850,25,87.0,p,3);
                p[2]=4.0f;
                spawn_offset(850,25,87.0,p,3);
            }
            return;
        case 601:
            landing();
            texture(5,2);
            if(sequence_index_13e==1){
                if(time_counter_144>90){
                    next_sequence_block();
                    return;
                }
                if(time_counter_144%10==0)effect(127,static_cast<float>(x_ec-static_cast<float>(100*facing())),y_f0,static_cast<unsigned char>(facing_104),-1);
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142)spell_flash(-23,94.0,3);
            if(entry(1)){
                spawn_offset(990,-80,130.0,0,0);
                dispatch_character_wave_handle(10);
                float p[3]={
                    0.0f,2.0f,0.0f
                };
                spawn_offset(851,25,87.0,p,3);
                p[1]=-2.0f;
                spawn_offset(851,25,87.0,p,3);
                p[1]=0.0f;
                p[2]=2.0f;
                spawn_offset(851,25,87.0,p,3);
            }
            return;
        case 602:
            landing();
            texture(5,2);
            if(sequence_index_13e==1){
                if(time_counter_144%10==0 && time_counter_144<=90){
                    float p[3]={
                        0.0f,0.0f,5.0f
                    };
                    spawn_offset(852,25,150.0,p,3);
                    effect(127,static_cast<float>(x_ec-static_cast<float>(100*facing())),y_f0,static_cast<unsigned char>(facing_104),-1);
                }
                if(time_counter_144>120){
                    next_sequence_block();
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(18,83.0,5);
            if(entry(1)){
                spawn_offset(990,-80,130.0,0,0);
                dispatch_character_wave_handle(11);
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                spawn_offset(852,25,150.0,p,3);
                p[2]=2.0f;
                spawn_offset(852,25,150.0,p,3);
                p[2]=4.0f;
                spawn_offset(852,25,150.0,p,3);
            }
            return;
        case 603:
            if(sequence_index_13e==6)landing();
            texture(5,2);
            if(sequence_index_13e==1)velocity_y_f8-=acceleration_y_100;
            if(sequence_index_13e==3){
                if(time_counter_144%10==0 && time_counter_144<=90){
                    float p[3]={
                        field_73c,0.0f,5.0f
                    };
                    spawn_offset(853,30,53.0,p,3);
                }
                if(facing()*field_6b4>0 || field_6b8<0)field_73c=static_cast<float>(field_73c-static_cast<double>(0.2f));
                if(facing()*field_6b4<0 || field_6b8>0)field_73c=static_cast<float>(field_73c+static_cast<double>(0.2f));
                velocity_x_f4=static_cast<float>(marisa_cosine(static_cast<float>(180.0-field_73c))*3.0);
                velocity_y_f8=static_cast<float>(marisa_sine(static_cast<float>(180.0-field_73c))*3.0);
                if(time_counter_144>120){
                    next_sequence_block();
                    return;
                }
            }
            if(sequence_index_13e==4 || sequence_index_13e==5){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    y_f0=marisa_surface(this);
                    select_sequence(6);
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(18,83.0,5);
            if(sequence_index_13e==1 && !frame_timer_142){
                if(!frame_index_140){
                    velocity_x_f4=-4.0f;
                    velocity_y_f8=23.0f;
                    acceleration_y_100=0.6f;
                }
                if(!frame_timer_142 && frame_index_140==9){
                    velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.2f));
                    velocity_y_f8=static_cast<float>(static_cast<double>(0.2f)*velocity_y_f8);
                    acceleration_y_100=0.0f;
                    zero_motion();
                }
            }
            if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
                dispatch_character_wave_handle(11);
                float p[3];
                field_73c=60.0f;
                p[0]=field_73c;
                p[1]=0.0f;
                p[2]=0.0f;
                spawn_offset(853,30,53.0,p,3);
                p[2]=2.0f;
                spawn_offset(853,30,53.0,p,3);
                p[2]=4.0f;
                spawn_offset(853,30,53.0,p,3);
            }
            if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;
            return;
        case 604:
            landing();
            texture(5,2);
            if(sequence_index_13e==1 && time_counter_144>120){
                next_sequence_block();
                return;
            }
            if(entry(1)){
                dispatch_character_wave_handle(10);
                float p=0.0f;
                spawn_offset(853,-25,150.0,&p,1);
                p=90.0f;
                spawn_offset(853,-25,150.0,&p,1);
                p=180.0f;
                spawn_offset(853,-25,150.0,&p,1);
                p=270.0f;
                spawn_offset(853,-25,150.0,&p,1);
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(-2,120.0,3);
            return;
        case 605:
            if(sequence_index_13e==4)landing();
            if(sequence_index_13e<2)texture(5,2);
            if(field_180==1 && !word_732){
                word_732=1;
                dispatch_character_wave_handle(14);
            }
            if(sequence_index_13e==1){
                if((classify_fighter_x_boundary()!=0 && field_180!=1 && ((facing_104==1 && x_ec>640.0f) || (facing_104==-1 && x_ec<640.0f))) || (!byte_184 && field_180==2)){
                    next_sequence_block();
                    velocity_x_f4=-2.5f;
                    velocity_y_f8=15.0f;
                    acceleration_y_100=0.5f;
                }
                float p[3];
                p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)-30.0);
                p[1]=static_cast<float>(marisa_random_u32()%10u+15u);
                p[2]=2.0f;
                spawn(810,static_cast<float>(x_ec-static_cast<float>(90*facing())),static_cast<float>(y_f0+95.0),static_cast<unsigned char>(-facing_104),1,p,3);
            }
            if(sequence_index_13e==2 || sequence_index_13e==3){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    y_f0=marisa_surface(this);
                    select_sequence(4);
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){
                word_48a=40;
                event(23);
                sequence_window(0,2,60);
                secondary_cycle();
                effect(115,static_cast<float>(x_ec-0.0),static_cast<float>(y_f0+70.0),static_cast<unsigned char>(facing_104),1);
            }
            if(entry(1)){
                byte_184=20;
                velocity_x_f4=30.0f;
                dispatch_character_wave_handle(13);
                float p[3]={
                    0.0f,0.0f,0.0f
                };
                spawn_offset(857,0,0.0,p,3);
                if(marisa_on_surface(this))effect(127,x_ec,0.0f,static_cast<unsigned char>(facing_104),1);
            }
            if(sequence_index_13e==1 && !frame_timer_142){
                if(field_180!=0){
                    field_180=0;
                    velocity_x_f4=10.0f;
                }
                else{
                    field_180=0;
                    velocity_x_f4=25.0f;
                }
            }
            return;
        case 606:
            if(!sequence_index_13e || sequence_index_13e==4)landing();
            texture(5,2);
            if(sequence_index_13e==1){
                if(time_counter_144>40)next_sequence_block();
                if(time_counter_144%3==0){
                    float p[3];
                    p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+95.0-30.0);
                    p[1]=15.0f;
                    p[2]=static_cast<float>(marisa_random_u32()&3u);
                    spawn_offset(810,40,51.0,p,3);
                }
                if(field_180){
                    ++word_730;
                    if(word_730>3){
                        word_730=0;
                        field_180=0;
                    }
                }
            }
            if(sequence_index_13e>0 && sequence_index_13e<4){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.85f));
                decelerate(static_cast<double>(0.35f),false);
            }
            if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){
                next_sequence_block();
                y_f0=marisa_surface(this);
                zero_motion();
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
                word_48a=40;
                event(23);
                sequence_window(0,3,60);
                secondary_cycle();
                effect(115,static_cast<float>(66*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+81.0),static_cast<unsigned char>(facing_104),1);
            }
            if(entry(1)){
                float p[3]={
                    -80.0f,0.0f,2.0f
                };
                spawn_offset(849,61,232.0,p,3);
                effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
                dispatch_character_wave_handle(15);
                velocity_x_f4=15.0f;
                velocity_y_f8=32.5f;
                acceleration_y_100=0.6f;
            }
            return;
        case 607:
            if(sequence_index_13e==4)landing();
            if(sequence_index_13e<3)texture(5,2);
            if(sequence_index_13e==1 && time_counter_144>60){
                next_sequence_block();
                dispatch_character_wave_handle(16);
                float p[3]={
                    0.0f,0.0f,3.0f
                };
                spawn_offset(858,-200,275.0,p,3);
                p[2]=4.0f;
                spawn_offset(858,-200,275.0,p,3);
            }
            if(sequence_index_13e==2 && word_730==1){
                next_sequence_block();
                zero_motion();
                acceleration_y_100=0.5f;
                y_f0=1600.0f;
            }
            if(sequence_index_13e==3){
                velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);
                if(static_cast<unsigned char>(crossed())){
                    next_sequence_block();
                    y_f0=marisa_surface(this);
                    zero_motion();
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(1)){
                float p[3]={
                    0.0f,0.0f,1.0f
                };
                spawn_offset(858,0,0.0,p,3);
                word_48a=40;
                event(23);
                sequence_window(0,5,60);
                secondary_cycle();
                effect(115,static_cast<float>(66*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+81.0),static_cast<unsigned char>(facing_104),1);
                velocity_x_f4=-30.0f;
            }
            return;
        case 608:
            landing();
            texture(5,2);
            if(sequence_index_13e<5 && word_730>0){
                if(sequence_index_13e<=3 && word_730%4==1){
                    dispatch_character_wave_handle(19);
                    float p[4];
                    p[0]=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(40)))-20.0);
                    p[1]=10.0f;
                    p[2]=static_cast<float>(marisa_random(4));
                    p[3]=0.0f;
                    spawn_offset(859,25,87.0,p,4);
                }
                ++word_730;
            }
            if(sequence_index_13e==1 && time_counter_144>40){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==3 && time_counter_144>40){
                next_sequence_block();
                return;
            }
            if(advance())set_action_and_finalize(0);
            if(entry(5)){
                set_action_and_finalize(0);
                return;
            }
            if(entry(1))spell_flash(-23,94.0,1);
            if(entry(6))spell_flash(-25,106.0,1);
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142)word_730=1;
            if(sequence_index_13e==7 && frame_index_140==2 && !frame_timer_142)word_730=1;
            return;
        case 658:
            if(sequence_index_13e==5)landing();
            else texture(5,2);
            if(word_730>0){
                if(sequence_index_13e<=3 && word_730%4==1){
                    dispatch_character_wave_handle(19);
                    float p[4];
                    p[0]=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(40)))-20.0);
                    p[1]=10.0f;
                    p[2]=static_cast<float>(marisa_random(4));
                    p[3]=0.0f;
                    spawn_offset(859,25,107.0,p,4);
                }
                ++word_730;
            }
            if(sequence_index_13e==1 && time_counter_144>40){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==3 && time_counter_144>40){
                next_sequence_block();
                return;
            }
            if(sequence_index_13e==4){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    select_sequence(5);
                    zero_motion();
                    y_f0=marisa_surface(this);
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(5)){
                set_action_and_finalize(9);
                return;
            }
            if(entry(1))spell_flash(-23,106.0,1);
            if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142)word_730=1;
            if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.3f;
            return;
        case 611:
            if(sequence_index_13e==3)landing();
            texture(5,2);
            if(sequence_index_13e==1 || sequence_index_13e==2){
                velocity_y_f8-=acceleration_y_100;
                velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);
                if(velocity_x_f4>-1.0f)velocity_x_f4=-1.0f;
                if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
                if(static_cast<unsigned char>(crossed())){
                    y_f0=marisa_surface(this);
                    zero_motion();
                    select_sequence(3);
                }
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)spell_flash(-23,94.0,2);
            if(entry(1)){
                dispatch_character_wave_handle(20);
                float p[4]={
                    0.0f,25.0f,0.0f,0.0f
                };
                velocity_x_f4=-25.0f;
                velocity_y_f8=10.0f;
                acceleration_y_100=0.5f;
                spawn_offset(860,73,95.0,p,4);
                effect(127,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),-1);
            }
            return;
        case 610:
            landing();
            if(sequence_index_13e==1){
                float p[4]={
                    static_cast<float>((15*word_732+word_730)*6),10.0f,static_cast<float>(word_732%4),0.0f
                };
                spawn_offset(861,28,185.0,p,4);
                ++word_732;
                ++word_730;
                if(sequence_index_13e==1 && time_counter_144>60){
                    next_sequence_block();
                    return;
                }
            }
            if(advance())set_action_and_finalize(0);
            if(entry(5)){
                set_action_and_finalize(0);
                return;
            }
            if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142){
                word_48a=40;
                event(23);
                effect(115,static_cast<float>(x_ec-20*facing()),static_cast<float>(y_f0+80.0),static_cast<unsigned char>(facing_104),1);
                sequence_window(0,1,60);
            }
            if(entry(6))spell_flash(-25,106.0,4);
            if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142){
                word_730=1;
                float p[4]={
                    0.0f,0.0f,4.0f,0.0f
                };
                spawn_offset(861,28,185.0,p,4);
                p[2]=5.0f;
                p[3]=0.0f;
                spawn_offset(861,28,185.0,p,4);
            }
            if(sequence_index_13e==7 && frame_index_140==2 && !frame_timer_142)word_730=1;
            return;
        case 612:
            landing();
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e){
                if(!frame_timer_142 && frame_index_140==5){
                    float p[4]={
                        0.0f,0.0f,0.0f,0.0f
                    };
                    spawn_offset(863,70,165.0,p,4);
                    dispatch_character_wave_handle(7);
                }
                if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){
                    word_48a=40;
                    event(23);
                    effect(115,static_cast<float>(x_ec-22*facing()),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1);
                    sequence_window(0,1,60);
                }
            }
            return;
        case 613:
            if(sequence_index_13e==2)landing();
            if(sequence_index_13e<2){
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    select_sequence(2);
                    y_f0=marisa_surface(this);
                    return;
                }
            }
            if(sequence_index_13e==1 && time_counter_144>20){
                set_action_and_finalize(9);
                return;
            }
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142){
                if(frame_index_140==3){
                    velocity_x_f4=0.0f;
                    velocity_y_f8=0.0f;
                    acceleration_y_100=0.0f;
                    spell_flash(-46,150.0,1);
                }
                if(!frame_timer_142 && frame_index_140==6){
                    dispatch_character_wave_handle(7);
                    velocity_x_f4=-4.0f;
                    velocity_y_f8=8.0f;
                    acceleration_y_100=0.5f;
                    float p[4]={
                        0.0f,0.0f,1.0f,0.0f
                    };
                    spawn_offset(863,30,62.0,p,4);
                }
            }
            return;
        case 615:
            landing();
            texture(5,2);
            if(advance())set_action_and_finalize(0);
            {
                if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){
                    dispatch_character_wave_handle(24);
                    word_7a6=600;
                    word_7a4=0;
                    float p[3];
                    float n=0.0f;
                    do{
                        p[0]=static_cast<float>(90.0*n);
                        p[1]=0.0f;
                        p[2]=static_cast<float>(n+0.0);
                        spawn(865,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1,p,3);
                        n=static_cast<float>(n+1.0);
                    }
                    while(n<4.0f);
                    for(int angle=0;angle<360;angle+=45){
                        p[0]=static_cast<float>(static_cast<double>(angle)+30.0+static_cast<double>(static_cast<float>(marisa_random(40))));
                        p[1]=13.0f;
                        p[2]=2.0f;
                        if(p[0]>=0.0f && p[0]<=180.0f)spawn(848,x_ec,y_f0,facing_104,1,p,3);
                        else spawn(848,x_ec,y_f0,facing_104,-1,p,3);
                    }
                }
                if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(-36,83.0,2);
            }
            return;
        case 619:
            landing();
            texture(5,2);
            if((sequence_index_13e==1 && time_counter_144>=45) || (sequence_index_13e==4 && time_counter_144>=90) || (sequence_index_13e==5 && time_counter_144>=40)){
                next_sequence_block();
                return;
            }
            if(advance())set_action_and_finalize(0);
            if(entry(4))spawn_offset(990,-80,130.0,0,0);
            if(!sequence_index_13e && !frame_timer_142){
                if(frame_index_140==3)spell_flash(-16,100.0,5);
                if(!frame_timer_142 && frame_index_140==5){
                    float p[3]={
                        0.0f,0.0f,11.0f
                    };
                    spawn_offset(869,100,105.0,p,3);
                    dispatch_character_wave_handle(10);
                    ++word_732;
                }
            }
            return;
        case 695:
            landing();
            if(advance())set_action_and_finalize(0);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
                event(55);
                effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
                effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
                effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
                effect(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);
                effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
            }
            return;
        case 696:
            landing();
            if(frame_index_140>5)decelerate(3.0,false);
            if(advance())set_action_and_finalize(0);
            if(!frame_timer_142){
                if(frame_index_140==4){
                    velocity_x_f4=15.0f;
                    float p[3]={
                        0.0f,0.0f,0.0f
                    };
                    spawn_offset(848,0,0.0,p,3);
                }
                if(!frame_timer_142 && frame_index_140==5){
                    event(29);
                    byte_47e=0;
                }
            }
            return;
        case 707:
            landing();
            if(velocity_x_f4>12.0f){
                velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
                if(velocity_x_f4<12.0f)velocity_x_f4=12.0f;
            }
            if(advance()){
                set_action_and_finalize(700);
                return;
            }
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
                velocity_x_f4=15.0f;
                dash_effects(false,80.0,true);
            }
            if(sequence_index_13e==1){
                if(time_counter_144%5==0)dash_dust(false);
                if(time_counter_144>30){
                    next_sequence_block();
                    return;
                }
            }
            if(sequence_index_13e==2)decelerate(0.5,false);
            return;
        case 708:
            if(!sequence_index_13e || sequence_index_13e==2)landing();
            if(sequence_index_13e==2){
                velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);
                if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
            }
            if(!marisa_on_surface(this)){
                if(time_counter_144%5==0)dash_dust(true);
                // 4B256B narrows velocity before the QWORD prediction at 4B257F.
                velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);
                double predicted=static_cast<double>(velocity_y_f8)+y_f0;
                if(marisa_surface(this)>=predicted && velocity_y_f8<0.0f){
                    velocity_y_f8=0.0f;
                    y_f0=marisa_surface(this);
                    select_sequence(2);
                    return;
                }
            }
            if(advance()){
                set_action_and_finalize(700);
                return;
            }
            if(entry(1)){
                velocity_x_f4=-14.0f;
                velocity_y_f8=4.0f;
                dash_effects(true,80.0,false);
            }
            return;
        case 710:
            landing();
            if(advance())set_action_and_finalize(700);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)aimed900(94,102.0);
            if(sequence_index_13e==1 && time_counter_144>60)next_sequence_block();
            return;
        case 711:
            if(!sequence_index_13e)landing();
            else{
                velocity_y_f8-=acceleration_y_100;
                if(static_cast<unsigned char>(crossed())){
                    zero_motion();
                    y_f0=marisa_surface(this);
                    set_action_and_finalize(709);
                    return;
                }
            }
            if(advance())set_action_and_finalize(700);
            if(entry(1)){
                velocity_y_f8=14.0f;
                velocity_x_f4=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(10)))-5.0);
                acceleration_y_100=0.3f;
            }
            if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==7){
                aimed900(72,88.0);
                velocity_x_f4=-10.0f;
                velocity_y_f8=5.0f;
                acceleration_y_100=0.3f;
            }
            if(sequence_index_13e==2 && time_counter_144>20)next_sequence_block();
            return;
        case 720:
            if(!sequence_index_13e && frame_index_140>=3)velocity_y_f8-=acceleration_y_100;
            if(sequence_index_13e==1){
                velocity_y_f8=static_cast<float>(velocity_y_f8*static_cast<double>(0.9f));
                velocity_x_f4=static_cast<float>(static_cast<double>(0.9f)*velocity_x_f4);
                if(time_counter_144>=72){
                    select_sequence(4);
                    velocity_x_f4=0.0f;
                    velocity_y_f8=0.0f;
                    return;
                }
            }
            if(entry(2)){
                if(x_ec<640.0f)field_74c=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(360)))+700.0);
                else field_74c=static_cast<float>(580.0-static_cast<double>(static_cast<float>(marisa_random(360))));
                field_748=static_cast<float>(static_cast<double>(static_cast<float>(marisa_random(260)))+60.0);
                if(x_ec>field_74c)facing_104=-1;
                else facing_104=1;
            }
            if(sequence_index_13e==3){
                word_736=0;
                word_738=0;
                velocity_x_f4=static_cast<float>((field_74c-x_ec)*static_cast<double>(0.05f)*facing());
                velocity_y_f8=static_cast<float>((field_748-y_f0)*static_cast<double>(0.05f));
                double dy=marisa_square(field_748-y_f0);
                if(marisa_square(field_74c-x_ec)+dy<=900.0){
                    next_sequence_block();
                    return;
                }
            }
            if(sequence_index_13e==4){
                word_736=0;
                word_738=0;
            }
            if(sequence_index_13e==5 && time_counter_144>=20){
                word_738=1;
                if(time_counter_144%5==0)word_736=static_cast<short>(static_cast<short>(marisa_random(6))+1);
            }
            if(sequence_index_13e==6 && time_counter_144>=20)word_738=1;
            if(sequence_index_13e==7 && time_counter_144>=60)word_738=1;
            if(advance())set_action_and_finalize(700);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
                velocity_x_f4=3.0f;
                velocity_y_f8=14.0f;
                acceleration_y_100=0.3f;
            }
            if(entry(1)){
                float p[3];
                switch(g_match_identifier){
                case 3:
                    {
                        for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){
                            p[0]=static_cast<float>(60.0*n);
                            p[1]=0.0f;
                            p[2]=n;
                            spawn_offset(901,0,100.0,p,3);
                        }
                    }
                    break;
                case 2:
                    {
                        for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)){
                            p[0]=static_cast<float>(72.0*n);
                            p[1]=0.0f;
                            p[2]=n;
                            spawn_offset(901,0,100.0,p,3);
                        }
                    }
                    break;
                case 1:
                    {
                        for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)){
                            p[0]=static_cast<float>(90.0*n);
                            p[1]=0.0f;
                            p[2]=n;
                            spawn_offset(901,0,100.0,p,3);
                        }
                    }
                    break;
                case 0:
                    {
                        for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){
                            p[0]=static_cast<float>(120.0*n);
                            p[1]=0.0f;
                            p[2]=n;
                            spawn_offset(901,0,100.0,p,3);
                        }
                    }
                    break;
                }
                field_73c=0.0f;
                field_740=0.0f;
                field_744=3.0f;
                word_730=0;
                word_732=0;
            }
            return;
        case 730:
            landing();
            if(sequence_index_13e==1 && time_counter_144>=30){
                next_sequence_block();
                return;
            }
            if(advance())set_action_and_finalize(731);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                float p[3]={
                    0.0f,0.0f,11.0f
                };
                spawn_offset(920,100,105.0,p,3);
                dispatch_character_wave_handle(10);
                ++word_732;
            }
            return;
        case 731:
            {
                landing();
                if(sequence_index_13e==1){
                    switch(g_match_identifier){
                    case 3:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>8.0f)field_73c=8.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 2:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>7.0)field_73c=7.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 1:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>6.0f)field_73c=6.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 0:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>4.0f)field_73c=4.0f;
                        if(time_counter_144>=60){
                            next_sequence_block();
                            return;
                        }
                        break;
                    }
                }
                else{
                    field_73c=static_cast<float>(field_73c-0.5);
                    if(field_73c<0.0f)field_73c=0.0f;
                }
                if(sequence_index_13e==2 && time_counter_144>=60){
                    next_sequence_block();
                    return;
                }
                field_6ac=-field_73c;
                if((peer()->x_ec>x_ec && peer()->facing_104==1) || (peer()->x_ec<x_ec && peer()->facing_104==-1))field_6ac=field_73c;
                if(advance())set_action_and_finalize(700);
                if(entry(1))spawn_offset(990,-80,130.0,0,0);
            }
            return;
        case 732:
            landing();
            if(sequence_index_13e==1 && time_counter_144>=30){
                next_sequence_block();
                return;
            }
            if(advance())set_action_and_finalize(733);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                float p[3]={
                    -35.0f,0.0f,11.0f
                };
                spawn_offset(920,90,130.0,p,3);
                dispatch_character_wave_handle(10);
                ++word_732;
            }
            return;
        case 733:
            {
                landing();
                if(sequence_index_13e==1){
                    switch(g_match_identifier){
                    case 3:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>8.0f)field_73c=8.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 2:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>7.0)field_73c=7.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 1:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>6.0f)field_73c=6.0f;
                        if(time_counter_144>=90){
                            next_sequence_block();
                            return;
                        }
                        break;
                    case 0:
                        field_73c=static_cast<float>(field_73c+0.5);
                        if(field_73c>4.0f)field_73c=4.0f;
                        if(time_counter_144>=60){
                            next_sequence_block();
                            return;
                        }
                        break;
                    }
                }
                else{
                    field_73c=static_cast<float>(field_73c-0.5);
                    if(field_73c<0.0f)field_73c=0.0f;
                }
                if(sequence_index_13e==2 && time_counter_144>=60){
                    next_sequence_block();
                    return;
                }
                field_6ac=-field_73c;
                if((peer()->x_ec>x_ec && peer()->facing_104==1) || (peer()->x_ec<x_ec && peer()->facing_104==-1))field_6ac=field_73c;
                if(advance())set_action_and_finalize(700);
                if(entry(1))spawn_offset(990,-80,130.0,0,0);
            }
            return;
        case 770:
            if(advance())set_action_and_finalize(700);
            if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
                byte_655=1;
                finalize(-1);
                texture(5,-1);
                copy_health();
                word_76c=0;
                word_76a=1;
                word_766=0;
                word_768=0;
                word_764=0;
                event(23);
            }
            return;
        case 795:
            if(!sequence_index_13e){
                velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));
                if(static_cast<unsigned char>(crossed())){
                    select_sequence(1);
                    y_f0=marisa_surface(this);
                    zero_motion();
                    return;
                }
            }
            if(advance())set_action_and_finalize(700);
            return;
        case 797:
            {
                if(!sequence_index_13e){
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())){
                        next_sequence_block();
                        y_f0=marisa_surface(this);
                        velocity_y_f8=0.0f;
                        return;
                    }
                }
                if(sequence_index_13e==1){
                    velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);
                    if(velocity_x_f4<=0.0f){
                        velocity_x_f4=0.0f;
                        ++word_730;
                        if(word_730>=2){
                            next_sequence_block();
                            velocity_x_f4=-5.0f;
                            velocity_y_f8=5.0f;
                        }
                    }
                }
                if(sequence_index_13e==2 || sequence_index_13e==3){
                    velocity_y_f8=static_cast<float>(velocity_y_f8-0.25);
                    if(static_cast<unsigned char>(crossed())){
                        zero_motion();
                        y_f0=marisa_surface(this);
                        select_sequence(4);
                        event(30);
                        x_ec=(480.0f);
                        return;
                    }
                }
                if(advance())set_action_and_finalize((0));
            }
            return;
        case 798:
            {
                if(!sequence_index_13e){
                    velocity_y_f8-=acceleration_y_100;
                    if(static_cast<unsigned char>(crossed())){
                        next_sequence_block();
                        y_f0=marisa_surface(this);
                        velocity_y_f8=0.0f;
                        return;
                    }
                }
                if(sequence_index_13e==1){
                    velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);
                    if(velocity_x_f4<=0.0f){
                        velocity_x_f4=0.0f;
                        ++word_730;
                        if(word_730>=2){
                            next_sequence_block();
                            velocity_x_f4=-5.0f;
                            velocity_y_f8=5.0f;
                        }
                    }
                }
                if(sequence_index_13e==2 || sequence_index_13e==3){
                    velocity_y_f8=static_cast<float>(velocity_y_f8-0.25);
                    if(static_cast<unsigned char>(crossed())){
                        zero_motion();
                        y_f0=marisa_surface(this);
                        select_sequence(4);
                        event(30);
                        x_ec=(800.0f);
                        return;
                    }
                }
                if(advance())set_action_and_finalize((700));
            }
            return;
        default:common_update();
            return;
        }
        advance();
    }
}
