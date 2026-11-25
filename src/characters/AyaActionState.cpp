#include <stddef.h>

namespace th105 {
class AyaActionStateView;
float __fastcall aya_surface(AyaActionStateView *);
int __fastcall aya_on_surface(AyaActionStateView *);
float __cdecl aya_absolute(float);
float __cdecl aya_sine(float);
float __cdecl aya_cosine(float);
float __cdecl aya_atan(float, float);
unsigned __cdecl aya_random_u32();
int __cdecl aya_random(int);
extern int g_aya_action_match;

class AyaActionScratch {
public:
    void reset();
    void set_oriented_components(float, float);
};

struct AyaPeerView {
    unsigned char pad_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char pad_0f4[0x10];
    signed char facing_104;
    unsigned char pad_105[0x387];
    short word_48c;
};

class AyaActionStateView {
public:
    virtual void vslot00();
    virtual void vslot04();
    virtual void set_action_and_finalize(int action_id);
    virtual void select_sequence(int sequence_index);
    virtual void set_sequence_frame(int frame_index);
    virtual void next_sequence_block();

    void dispatch_action_state_vslot28();
    void dispatch_character_wave_handle(unsigned);
    unsigned char landing();
    unsigned char advance();
    int crossed();
    void zero_motion();
    void effect(int, float, float, unsigned char, int);
    int spawn(int, float, float, signed char, int, const void *, int);
    signed char x_boundary();
    void layout(float);
    void event(unsigned);
    void copy_action_word();
    void finalize(int);
    void sequence_window(signed char, int, int);
    void texture(signed char, short);
    void counter(short, int);
    void secondary_cycle();
    int phase_counter(int);
    void flip();
    unsigned char directional(int);
    void common_update();
    signed char shared_first(signed char, float);
    signed char shared_second(signed char, float);

    unsigned char pad_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char pad_105[0x27];
    float field_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x20];
    AyaActionStateView *emitter_168;
    unsigned char pad_16c[0x4];
    AyaPeerView *related_170;
    unsigned char pad_174[0x8];
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int state_180;
    unsigned char pad_184[0x2];
    short word_186;
    unsigned char pad_188[0x2f6];
    unsigned char byte_47e;
    unsigned char pad_47f[0x3];
    short word_482;
    unsigned char pad_484[0x6];
    short word_48a;
    unsigned char pad_48c[0x1c];
    short word_4a8;
    unsigned char pad_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char pad_4b0[0x8];
    int field_4b8;
    unsigned char pad_4bc[0x14a];
    signed char sbyte_606;
    signed char sbyte_607;
    signed char sbyte_608;
    signed char sbyte_609;
    signed char sbyte_60a;
    unsigned char pad_60b[0x3];
    signed char sbyte_60e;
    unsigned char pad_60f[0x46];
    unsigned char byte_655;
    unsigned char pad_656[0x5e];
    int field_6b4;
    int field_6b8;
    unsigned int field_6bc;
    unsigned int field_6c0;
    unsigned int field_6c4;
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
    unsigned char pad_748[0x4];
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
};

#define AYA_ASSERT_OFFSET(type, field, expected) \
    typedef char aya_assert_offset_##type##_##field[(offsetof(type, field) == (expected)) ? 1 : -1]

AYA_ASSERT_OFFSET(AyaPeerView, x_ec, 0x0ec);
AYA_ASSERT_OFFSET(AyaPeerView, y_f0, 0x0f0);
AYA_ASSERT_OFFSET(AyaPeerView, facing_104, 0x104);
AYA_ASSERT_OFFSET(AyaPeerView, word_48c, 0x48c);

AYA_ASSERT_OFFSET(AyaActionStateView, x_ec, 0x0ec);
AYA_ASSERT_OFFSET(AyaActionStateView, y_f0, 0x0f0);
AYA_ASSERT_OFFSET(AyaActionStateView, velocity_x_f4, 0x0f4);
AYA_ASSERT_OFFSET(AyaActionStateView, velocity_y_f8, 0x0f8);
AYA_ASSERT_OFFSET(AyaActionStateView, acceleration_y_100, 0x100);
AYA_ASSERT_OFFSET(AyaActionStateView, facing_104, 0x104);
AYA_ASSERT_OFFSET(AyaActionStateView, field_12c, 0x12c);
AYA_ASSERT_OFFSET(AyaActionStateView, action_id_13c, 0x13c);
AYA_ASSERT_OFFSET(AyaActionStateView, sequence_index_13e, 0x13e);
AYA_ASSERT_OFFSET(AyaActionStateView, frame_index_140, 0x140);
AYA_ASSERT_OFFSET(AyaActionStateView, frame_timer_142, 0x142);
AYA_ASSERT_OFFSET(AyaActionStateView, time_counter_144, 0x144);
AYA_ASSERT_OFFSET(AyaActionStateView, emitter_168, 0x168);
AYA_ASSERT_OFFSET(AyaActionStateView, related_170, 0x170);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_17c, 0x17c);
AYA_ASSERT_OFFSET(AyaActionStateView, state_180, 0x180);
AYA_ASSERT_OFFSET(AyaActionStateView, word_186, 0x186);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_47e, 0x47e);
AYA_ASSERT_OFFSET(AyaActionStateView, word_482, 0x482);
AYA_ASSERT_OFFSET(AyaActionStateView, word_48a, 0x48a);
AYA_ASSERT_OFFSET(AyaActionStateView, word_4a8, 0x4a8);
AYA_ASSERT_OFFSET(AyaActionStateView, word_4ac, 0x4ac);
AYA_ASSERT_OFFSET(AyaActionStateView, word_4ae, 0x4ae);
AYA_ASSERT_OFFSET(AyaActionStateView, field_4b8, 0x4b8);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_606, 0x606);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_607, 0x607);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_608, 0x608);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_609, 0x609);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_60a, 0x60a);
AYA_ASSERT_OFFSET(AyaActionStateView, sbyte_60e, 0x60e);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_655, 0x655);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6b4, 0x6b4);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6b8, 0x6b8);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6bc, 0x6bc);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6c0, 0x6c0);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6c4, 0x6c4);
AYA_ASSERT_OFFSET(AyaActionStateView, field_6c8, 0x6c8);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_72c, 0x72c);
AYA_ASSERT_OFFSET(AyaActionStateView, word_730, 0x730);
AYA_ASSERT_OFFSET(AyaActionStateView, word_732, 0x732);
AYA_ASSERT_OFFSET(AyaActionStateView, word_734, 0x734);
AYA_ASSERT_OFFSET(AyaActionStateView, word_736, 0x736);
AYA_ASSERT_OFFSET(AyaActionStateView, word_738, 0x738);
AYA_ASSERT_OFFSET(AyaActionStateView, field_73c, 0x73c);
AYA_ASSERT_OFFSET(AyaActionStateView, field_740, 0x740);
AYA_ASSERT_OFFSET(AyaActionStateView, field_744, 0x744);
AYA_ASSERT_OFFSET(AyaActionStateView, field_74c, 0x74c);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_750, 0x750);
AYA_ASSERT_OFFSET(AyaActionStateView, byte_751, 0x751);
AYA_ASSERT_OFFSET(AyaActionStateView, word_764, 0x764);
AYA_ASSERT_OFFSET(AyaActionStateView, word_766, 0x766);
AYA_ASSERT_OFFSET(AyaActionStateView, word_768, 0x768);
AYA_ASSERT_OFFSET(AyaActionStateView, word_76a, 0x76a);
AYA_ASSERT_OFFSET(AyaActionStateView, word_76c, 0x76c);
AYA_ASSERT_OFFSET(AyaActionStateView, word_7a0, 0x7a0);
AYA_ASSERT_OFFSET(AyaActionStateView, word_7a2, 0x7a2);
#undef AYA_ASSERT_OFFSET

#define URAND(n) static_cast<float>(static_cast<unsigned>(aya_random(n)))
#define JITTER_ANGLE(p,opposite) do {if(opposite)(p)[0]=static_cast<float>(URAND(40)*static_cast<double>(0.1f)+(field_740+180.0)-2.0);else(p)[0]=static_cast<float>(URAND(40)*static_cast<double>(0.1f)+field_740-2.0);}while(0)
#define WIDE_ANGLE(p,opposite) do {if(opposite)(p)[0]=static_cast<float>(URAND(30)+(field_740+180.0)-15.0);else(p)[0]=static_cast<float>(URAND(30)+field_740-15.0);}while(0)
#define ORBIT_SPAWN(p,radius,range,offset) do {spawn(903,static_cast<float>((URAND(range)+(aya_cosine(static_cast<float>(180.0-(p)[0]))*(radius)*facing_104+x_ec))-(offset)),static_cast<float>((URAND(range)+(aya_sine(static_cast<float>(180.0-(p)[0]))*(radius)+(y_f0+100.0)))-(offset)),facing_104,1,p,3);}while(0)
#define MOTION reinterpret_cast<AyaActionScratch *>(reinterpret_cast<unsigned char *>(this)+4)
#define ENTRY(n) (time_counter_144==0&&frame_timer_142==0&&frame_index_140==0&&sequence_index_13e==(n))
#define FRAME(n,f) (sequence_index_13e==(n)&&frame_timer_142==0&&frame_index_140==(f))
#define ADVANCE_TO(n) do {if(advance())set_action_and_finalize(n);}while(0)
#define CHOOSE_FOLLOWUP(up) do {if(facing_104*field_6b4>0){if(field_6b8<0)word_730=1;if(field_6b8>0)word_730=(up)?-1:0;if(!field_6b8)word_730=0;}if(!field_6b4){if(field_6b8<0)word_730=2;if(field_6b8>0)word_730=(up)?-2:0;if(!field_6b8)word_730=0;}if(facing_104*field_6b4<0){facing_104=-facing_104;if(field_6b8<0)word_730=1;if(field_6b8>0)word_730=(up)?-1:0;if(!field_6b8)word_730=0;}}while(0)
#define AIM_SHORT() do {float dx=static_cast<float>((static_cast<double>(related_170->x_ec)-x_ec)*facing_104);word_734=static_cast<short>(-static_cast<int>(aya_atan(related_170->y_f0-y_f0,dx)));}while(0)
#define SMOKE(dir) do {effect(124,static_cast<float>((x_ec+50.0)-static_cast<float>(aya_random_u32()%100u)),static_cast<float>(static_cast<float>(aya_random_u32()%200u)+y_f0),(dir),1);}while(0)

void AyaActionStateView::dispatch_action_state_vslot28() {
word_7a0=0;word_7a2=101;
if(action_id_13c>149&&action_id_13c<159&&!byte_751){
 byte_751=1;
 if(action_id_13c>149&&action_id_13c<154)spawn(998,57*facing_104+x_ec,y_f0+94.0,facing_104,1,0,0);
 if(action_id_13c>153&&action_id_13c<158)spawn(998,57*facing_104+x_ec,y_f0+60.0,facing_104,1,0,0);
 if(action_id_13c==158)spawn(998,57*facing_104+x_ec,y_f0+100.0,facing_104,1,0,0);
}
if(word_186||related_170->word_48c)return;

switch(action_id_13c){
case 0:{landing();if(velocity_x_f4==0.0)byte_47e=0;if (!byte_47e) { zero_motion(); break; } if (velocity_x_f4 > 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) { zero_motion(); byte_47e = 0; } } if (velocity_x_f4 < 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5); if (velocity_x_f4 > 0.0f) { zero_motion(); byte_47e = 0; break; } } break;}

case 1:{
 landing();
 if(!byte_47e)zero_motion();
 else{
  if(velocity_x_f4>0.0){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){zero_motion();byte_47e=0;}}
  if(velocity_x_f4<0.0){velocity_x_f4+=0.5;if(velocity_x_f4>0.0){zero_motion();byte_47e=0;}}
 }
 if(advance()&&!frame_index_140)set_action_and_finalize(2);return;
}

case 2:{landing();if (!byte_47e) { zero_motion(); break; } if (velocity_x_f4 > 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) { zero_motion(); byte_47e = 0; } } if (velocity_x_f4 < 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5); if (velocity_x_f4 > 0.0f) { zero_motion(); byte_47e = 0; break; } } break;}

case 3:{
 landing();
 if(!byte_47e)zero_motion();
 else{
  if(velocity_x_f4>0.0){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){zero_motion();byte_47e=0;}}
  if(velocity_x_f4<0.0){velocity_x_f4+=0.5;if(velocity_x_f4>0.0){zero_motion();byte_47e=0;}}
 }
 if(advance()&&!frame_index_140)set_action_and_finalize(0);return;
}

case 4:{landing();velocity_x_f4=5.5f;break;}

case 5:{landing();velocity_x_f4=-5.5f;break;}

case 6:{
 if(!sequence_index_13e){landing();if(!sequence_index_13e&&!byte_47e)zero_motion();}
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}}
 advance();if(!(!frame_timer_142&&!frame_index_140&&sequence_index_13e==1))return;
 velocity_x_f4=0.0;velocity_y_f8=18.0;acceleration_y_100=0.75f;byte_47e=0;return;
}

case 7:{
 if(!sequence_index_13e){landing();if(!sequence_index_13e&&!byte_47e)zero_motion();}
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}}
 advance();if(!(!frame_timer_142&&!frame_index_140&&sequence_index_13e==1))return;
 velocity_x_f4=8.0;velocity_y_f8=18.0;acceleration_y_100=0.75f;byte_47e=0;return;
}

case 8:{
 if(!sequence_index_13e){landing();if(!sequence_index_13e&&!byte_47e)zero_motion();}
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}}
 advance();if(!(!frame_timer_142&&!frame_index_140&&sequence_index_13e==1))return;
 velocity_x_f4=-8.0;velocity_y_f8=18.0;acceleration_y_100=0.75f;byte_47e=0;return;
}

case 9:{if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}break;}

case 10:{landing();zero_motion();if(advance()){if(!field_6b8)set_action_and_finalize(0);else set_action_and_finalize(2);}return;}

case 197:{
 if((!sequence_index_13e&&frame_index_140<=4)||sequence_index_13e==2)landing();
 if(!frame_timer_142&&frame_index_140==5)spawn(990,x_ec,y_f0,facing_104,1,0,0);
 if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){y_f0=aya_surface(this);zero_motion();select_sequence(2);return;}
 if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
 if(sequence_index_13e==2&&frame_index_140==2&&!frame_timer_142){if(x_ec>related_170->x_ec)facing_104=-1;if(x_ec<related_170->x_ec)facing_104=1;}
 if(sequence_index_13e==0&&frame_index_140==5&&!frame_timer_142){velocity_y_f8=4.8f;velocity_x_f4=15.0;acceleration_y_100=0.4f;}return;
}

case 198:{
 if((!sequence_index_13e&&frame_index_140<=4)||sequence_index_13e==2)landing();
 if(!frame_timer_142&&frame_index_140==5)spawn(990,x_ec,y_f0,facing_104,1,0,0);
 if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){y_f0=aya_surface(this);zero_motion();select_sequence(2);return;}
 if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
 if(sequence_index_13e==2&&frame_index_140==2&&!frame_timer_142){if(x_ec>related_170->x_ec)facing_104=-1;if(x_ec<related_170->x_ec)facing_104=1;}
 if(sequence_index_13e==0&&frame_index_140==5&&!frame_timer_142){velocity_y_f8=4.8f;velocity_x_f4=-15.0;acceleration_y_100=0.4f;}return;
}

case 199:{
 landing();if(!frame_timer_142&&frame_index_140==5)spawn(990,x_ec,y_f0,facing_104,1,0,0);
 if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
 if(sequence_index_13e==0&&frame_index_140==17&&!frame_timer_142){if(x_ec>related_170->x_ec)facing_104=-1;if(x_ec<related_170->x_ec)facing_104=1;}return;
}

case 200:{
 landing();byte_47e=1;if(velocity_x_f4>10.0){velocity_x_f4-=0.5;if(velocity_x_f4<10.0)velocity_x_f4=10.0;}advance();
 if(sequence_index_13e==1){if(!(time_counter_144%5)){SMOKE(facing_104);}if(field_6b8<0){if(field_6b4*facing_104>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}++word_730;if((field_6b4*facing_104<=0&&word_730>5)||word_730>45){set_action_and_finalize(204);return;}}
 if(ENTRY(1)){velocity_x_f4=18.5;effect(125,80*facing_104+x_ec,y_f0+80.0,facing_104,1);effect(126,x_ec,y_f0+80.0,facing_104,1);event(31);}return;
}

case 201:{
 if(!sequence_index_13e||sequence_index_13e==3)landing();
 if(sequence_index_13e==3){velocity_x_f4+=2.0;if(velocity_x_f4>0.0)velocity_x_f4=0.0;}
 if(!static_cast<unsigned char>(aya_on_surface(this))&&!(time_counter_144%5)){SMOKE(static_cast<unsigned char>(-facing_104));}
 if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0;y_f0=aya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0;return;}
 if(ENTRY(1)&&!word_730){word_730=1;velocity_x_f4=-17.0;velocity_y_f8=3.5;acceleration_y_100=0.75f;effect(125,x_ec,y_f0+80.0,static_cast<unsigned char>(-facing_104),1);effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(-facing_104),1);event(31);}return;
}

case 202:{
 velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){ zero_motion(); y_f0 = aya_surface(this); set_action_and_finalize(10); return; }
 if(sequence_index_13e==1&&!(time_counter_144%5)){SMOKE(facing_104);}advance();
 if(!sequence_index_13e&&frame_index_140==2&&!frame_timer_142){word_730=0;velocity_x_f4=12.0;velocity_y_f8=4.0;acceleration_y_100=0.45f;effect(125,80*facing_104+x_ec,y_f0+110.0,facing_104,1);effect(126,x_ec,y_f0+110.0,facing_104,1);event(31);}
 if(ENTRY(2))flip();return;
}

case 203:{
 velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){ zero_motion(); y_f0 = aya_surface(this); set_action_and_finalize(10); return; }
 if(sequence_index_13e==1&&!(time_counter_144%5)){SMOKE(static_cast<unsigned char>(-facing_104));}advance();
 if(!sequence_index_13e&&frame_index_140==3&&!frame_timer_142){velocity_x_f4=-12.0;velocity_y_f8=4.0;acceleration_y_100=0.45f;effect(125,x_ec,y_f0+120.0,static_cast<unsigned char>(-facing_104),1);effect(126,x_ec,y_f0+120.0,static_cast<unsigned char>(-facing_104),1);event(31);}if(ENTRY(2))flip();return;
}

case 204:{landing();velocity_x_f4-=1.5;if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}if(advance()){set_action_and_finalize(0);byte_47e=0;}return;}

case 208:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=0.0;velocity_y_f8=22.5;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 209:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=10.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 210:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=-10.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 211:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=3.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 212:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=12.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 214:{
 if(advance()){set_action_and_finalize(9);return;}
 if(ENTRY(6)){set_action_and_finalize(9);return;}
 if(ENTRY(1))event(31);
 if(field_6b8>0){
  if(field_6b4*facing_104>0)word_732=-45;
  else if(field_6b4*facing_104<0)word_732=-135;
  else word_732=-90;
 }else if(field_6b8<0){
  if(field_6b4*facing_104>0)word_732=45;
  else if(field_6b4*facing_104<0)word_732=135;
  else word_732=90;
 }else{
  if(field_6b4*facing_104>0)word_732=0;
  else if(field_6b4*facing_104<0)word_732=180;
 }
 if(sequence_index_13e==5||sequence_index_13e==6)velocity_y_f8-=acceleration_y_100;
 if(sequence_index_13e>0&&sequence_index_13e<5){
  ++word_736;word_734=static_cast<short>(word_732-static_cast<int>(field_740));
  if(word_734>180)word_734-=360;
  if(word_734<-180)word_734+=360;
  if(word_734>0){if(!field_4b8)field_740+=2.0;else field_740+=1.0;}
  if(word_734<0){if(!field_4b8)field_740-=2.0;else field_740-=1.0;}
  velocity_x_f4=aya_cosine(field_740)*field_73c;
  velocity_y_f8=aya_sine(field_740)*field_73c;
  if(y_f0>680.0&&velocity_y_f8>0.0)velocity_y_f8=0.0;
  field_73c+=static_cast<double>(0.3f);if(field_73c>12.0)field_73c=12.0;
  if(!field_4b8)counter(5,1);else counter(10,1);
  field_12c=-field_740;if(velocity_x_f4<0.0f)field_12c=180.0-field_740;
  if(velocity_x_f4<0.0f&&sequence_index_13e==1)select_sequence(3);
  if(velocity_x_f4>=0.0f&&sequence_index_13e==3)select_sequence(1);
  if(velocity_x_f4<0.0f&&sequence_index_13e==2)select_sequence(4);
  if(velocity_x_f4>=0.0f&&sequence_index_13e==4)select_sequence(2);
  if(time_counter_144%5==1){effect(125,static_cast<float>(aya_cosine(field_740)*100.0*facing_104+x_ec),static_cast<float>(aya_sine(field_740)*100.0+y_f0+100.0),facing_104,1);}
  if((!field_6c8&&word_736>10)||word_482<=0){
   if((!field_6c8&&word_736>10)||word_482<=0){
    MOTION->reset();
    if(sequence_index_13e==1||sequence_index_13e==2){
     if(facing_104==1){if(x_ec>related_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(6);}else select_sequence(5);}
     else if(x_ec<related_170->x_ec){facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;select_sequence(6);}else select_sequence(5);
    }
    if(sequence_index_13e==3||sequence_index_13e==4){
     if(facing_104==1){if(x_ec>related_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(5);}else select_sequence(6);}
     else if(x_ec<related_170->x_ec){facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;select_sequence(5);}
     else select_sequence(6);
    }return;
   }
  }
 }
 if(static_cast<unsigned char>(crossed())){
  y_f0=aya_surface(this);velocity_y_f8=0.0;acceleration_y_100=0.0;
  if(sequence_index_13e<5){MOTION->reset();set_action_and_finalize(215);return;}
  set_action_and_finalize(10);zero_motion();return;
 }return;
}

case 215:{landing();if(velocity_x_f4>0.0){velocity_x_f4-=0.75;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}if(velocity_x_f4<0.0){velocity_x_f4+=0.75;if(velocity_x_f4>0.0)velocity_x_f4=0.0;}ADVANCE_TO(0);return;}

case 220:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=0.0;velocity_y_f8=22.5;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 221:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=10.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 222:{
 if(!sequence_index_13e)landing();if(static_cast<unsigned char>(crossed())){ set_action_and_finalize(10); y_f0 = aya_surface(this); zero_motion(); return; }
 if(static_cast<unsigned char>(aya_on_surface(this))||velocity_y_f8>0.0)word_4ae=2;
 if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0)velocity_y_f8=-20.0;}
 if(sequence_index_13e==1&&velocity_y_f8<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;velocity_x_f4=-10.0;velocity_y_f8=18.0;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);return;
}

case 223:{
 landing();byte_47e=1;advance();
 if(sequence_index_13e==1){if(!(time_counter_144%5)){SMOKE(facing_104);}++word_730;if((field_6b4*facing_104<=0&&word_730>15)||word_730>45){set_action_and_finalize(204);return;}}
 if(ENTRY(1)){velocity_x_f4=7.0;effect(125,80*facing_104+x_ec,y_f0+80.0,facing_104,1);effect(126,x_ec,y_f0+80.0,facing_104,1);event(31);}return;
}

case 224:{
 if(!sequence_index_13e||sequence_index_13e==3)landing();
 if(sequence_index_13e==3){velocity_x_f4+=2.0;if(velocity_x_f4>0.0)velocity_x_f4=0.0;}
 if(!static_cast<unsigned char>(aya_on_surface(this))&&!(time_counter_144%5)){SMOKE(static_cast<unsigned char>(-facing_104));}
 if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0;y_f0=aya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0;return;}
 if(ENTRY(1)&&!word_730){word_730=1;velocity_x_f4=-17.0;velocity_y_f8=4.0;acceleration_y_100=0.75f;effect(125,x_ec,y_f0+80.0,static_cast<unsigned char>(-facing_104),1);effect(126,x_ec,y_f0+80.0,static_cast<unsigned char>(-facing_104),1);event(31);}return;
}

case 225:{
 velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){ zero_motion(); y_f0 = aya_surface(this); set_action_and_finalize(10); return; }
 if(sequence_index_13e==2&&!(time_counter_144%5)){SMOKE(static_cast<unsigned char>(-facing_104));}ADVANCE_TO(9);
 if(ENTRY(1)){velocity_x_f4=-12.0;velocity_y_f8=4.0;acceleration_y_100=0.45f;effect(125,x_ec,y_f0+120.0,static_cast<unsigned char>(-facing_104),1);effect(126,x_ec,y_f0+120.0,static_cast<unsigned char>(-facing_104),1);event(31);}return;
}

case 226:{
 velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){ zero_motion(); y_f0 = aya_surface(this); set_action_and_finalize(10); return; }
 if(sequence_index_13e==1&&!(time_counter_144%5)){SMOKE(facing_104);}ADVANCE_TO(9);
 if(ENTRY(1)){word_730=0;velocity_x_f4=12.0;velocity_y_f8=4.0;acceleration_y_100=0.45f;effect(125,80*facing_104+x_ec,y_f0+110.0,facing_104,1);effect(126,x_ec,y_f0+110.0,facing_104,1);event(31);}
 if(ENTRY(2))flip();return;
}

case 300:{landing();if(directional(0))return;if(byte_47e){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}}ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==2){event(27);byte_47e=0;}return;}

case 301:{landing();if(directional(0))return;if(byte_47e){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}}ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==3){velocity_x_f4=10.0;event(27);byte_47e=0;}if(frame_index_140>3){velocity_x_f4-=1.0;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}return;}

case 302:{
 landing();if(directional(1))return;if(frame_index_140<4&&!field_6bc)byte_750=0;
 if(!sequence_index_13e){if(velocity_x_f4>0.0)velocity_x_f4-=1.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;if(!frame_timer_142){if(frame_index_140==4)velocity_x_f4=15.5;if(!frame_timer_142&&frame_index_140==6)event(27);}}
 if(sequence_index_13e==1){if(velocity_x_f4>0.0)velocity_x_f4-=1.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;if(!frame_timer_142){if(frame_index_140==1)velocity_x_f4=25.0;if(!frame_timer_142&&frame_index_140==3)event(27);}}
 ADVANCE_TO(0);if(ENTRY(1))set_action_and_finalize(0);
 if(FRAME(0,4)&&byte_750==1){effect(62,7*facing_104+x_ec,y_f0+180.0,facing_104,1);next_sequence_block();}return;
}

case 303:{landing();if(directional(0))return;if(static_cast<signed char>(byte_47e)>0){velocity_x_f4-=static_cast<double>(0.6f);if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}}ADVANCE_TO(2);if(!frame_timer_142&&frame_index_140==2)event(27);return;}

case 304:{
 landing();if(directional(1))return;if(frame_index_140<4&&!field_6bc)byte_750=0;
 if(advance()||ENTRY(1)){set_action_and_finalize(2);return;}
 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==3){if(byte_750==1){next_sequence_block();effect(62,64*facing_104+x_ec,y_f0+108.0,facing_104,1);return;}velocity_x_f4=10.0;event(28);}
  if(!frame_timer_142&&frame_index_140==5)velocity_x_f4=5.0;
  if(frame_index_140>=5){velocity_x_f4-=0.75;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 }
 if(sequence_index_13e==1){if(!frame_timer_142){if(frame_index_140==1){velocity_x_f4=20.0;event(28);}if(!frame_timer_142&&frame_index_140==3)velocity_x_f4=10.0;}if(frame_index_140>=3){velocity_x_f4-=0.75;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}}return;
}

case 305:{landing();if(directional(1))return;velocity_x_f4-=0.75;if(velocity_x_f4<0.0)velocity_x_f4=0.0;ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==3)event(27);return;}

case 306:{velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}ADVANCE_TO(9);if(!frame_timer_142&&frame_index_140==2)event(27);return;}

case 307:{velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}ADVANCE_TO(9);if(frame_index_140>2&&frame_index_140<8){MOTION->set_oriented_components(-20.0f,field_73c);field_73c-=1.5;if(field_73c<6.0)field_74c=6.0;}if(!frame_timer_142){if(frame_index_140==3)event(28);if(!frame_timer_142&&frame_index_140==8)acceleration_y_100=0.6f;}return;}

case 308:{if(sequence_index_13e==2)landing();if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){select_sequence(2);y_f0=aya_surface(this);zero_motion();return;}ADVANCE_TO(0);if(FRAME(0,4)){dispatch_character_wave_handle(14);velocity_x_f4=6.0;velocity_y_f8=-18.0;}return;}

case 309:{if(!sequence_index_13e){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1))set_action_and_finalize(9);if(!sequence_index_13e&&!frame_timer_142){if(frame_index_140==3){event(29);velocity_y_f8=7.5;acceleration_y_100=0.75f;}if(!frame_timer_142&&frame_index_140==7)acceleration_y_100=0.5f;}return;}

case 310:{
 if(state_180&&++word_730>5){state_180=0;word_730=0;}
 if(sequence_index_13e==1){if(!time_counter_144)velocity_x_f4=15.0;if(!(time_counter_144%8))event(27);if(state_180&&++word_730>5){state_180=0;word_730=0;}if(time_counter_144>30){next_sequence_block();velocity_y_f8=6.0;velocity_x_f4*=0.5;}}
 if(sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8+y_f0<=aya_surface(this)&&velocity_y_f8<0.0){velocity_y_f8=0.0;y_f0=aya_surface(this);set_action_and_finalize(9);return;}}
 ADVANCE_TO(9);return;
}

case 320:{landing();if(directional(0))return;if(byte_47e){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}}ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==2){event(27);byte_47e=0;}return;}

case 321:{landing();if(directional(0))return;if(byte_47e){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){velocity_x_f4=0.0;byte_47e=0;}}ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==3){velocity_x_f4=10.0;event(27);byte_47e=0;}if(frame_index_140>3){velocity_x_f4-=1.0;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}return;}

case 322:{landing();if(directional(1))return;if(!sequence_index_13e){if(velocity_x_f4>0.0)velocity_x_f4-=1.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;if(!frame_timer_142){if(frame_index_140==4)velocity_x_f4=15.5;if(!frame_timer_142&&frame_index_140==6)event(27);}}ADVANCE_TO(0);return;}

case 400:{
 landing();if(sequence_index_13e<2&&!field_6c0)byte_750=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==3&&byte_750==1){next_sequence_block();effect(62,x_ec+0.0,y_f0+216.0,facing_104,1);return;}
  if(!frame_timer_142&&frame_index_140==4){phase_counter(10);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;counter(200,45);state_180=1;
   float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
   spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){phase_counter(30);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;counter(200,45);state_180=1;
  float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 401:{
 landing();if(sequence_index_13e<2&&!field_6c0)byte_750=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==3&&byte_750==1){next_sequence_block();effect(62,x_ec+0.0,y_f0+216.0,facing_104,1);return;}
  if(!frame_timer_142&&frame_index_140==4){AIM_SHORT();if(word_734<-60)word_734=-60;if(word_734>-30)word_734=-30;counter(200,45);state_180=1;phase_counter(10);
   float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
   spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(word_734>-30)word_734=-30;if(word_734<-60)word_734=-60;counter(200,45);state_180=1;phase_counter(30);
  float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 402:{landing();ADVANCE_TO(2);if(!frame_timer_142&&frame_index_140==4){dispatch_character_wave_handle(1);phase_counter(30);state_180=1;counter(200,45);float packet[3]={0.0f,20.0f,0.0f};spawn(807,100*facing_104+x_ec,y_f0+70.0,facing_104,1,packet,3);}return;}

case 404:{
 if(sequence_index_13e==2)landing();if(sequence_index_13e<2&&!field_6c0)byte_750=0;
 if((!sequence_index_13e&&frame_index_140>6)||(sequence_index_13e==1&&frame_index_140>4))velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){select_sequence(2);y_f0=aya_surface(this);zero_motion();return;}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==3&&byte_750==1){next_sequence_block();effect(62,x_ec-14*facing_104,y_f0+226.0,facing_104,1);return;}
  if(!frame_timer_142&&frame_index_140==4){AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;counter(200,45);state_180=1;phase_counter(10);
   float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
   spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;counter(200,45);state_180=1;phase_counter(30);
  float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 406:{
 if(sequence_index_13e==2)landing();if(sequence_index_13e<2&&!field_6c0)byte_750=0;
 if((!sequence_index_13e&&frame_index_140>6)||(sequence_index_13e==1&&frame_index_140>4))velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){select_sequence(2);y_f0=aya_surface(this);zero_motion();return;}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==3&&byte_750==1){next_sequence_block();effect(62,x_ec-14*facing_104,y_f0+226.0,facing_104,1);return;}
  if(!frame_timer_142&&frame_index_140==4){AIM_SHORT();if(word_734<20)word_734=20;if(word_734>40)word_734=40;counter(200,45);state_180=1;phase_counter(10);
   float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
   spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(word_734<20)word_734=20;if(word_734>40)word_734=40;counter(200,45);state_180=1;phase_counter(30);
  float packet[3]={static_cast<float>(word_734),20.0f,0.0f};
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);
  packet[0]=word_734-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*facing_104+x_ec,y_f0+126.0,facing_104,1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 408:{landing();velocity_x_f4-=0.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;ADVANCE_TO(0);if(!frame_timer_142&&frame_index_140==6)event(29);return;}

case 409:{velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=aya_surface(this);return;}ADVANCE_TO(9);return;}

case 410:{
 landing();if(sequence_index_13e<2&&!field_6c4)byte_750=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==4&&byte_750==1){next_sequence_block();effect(62,7*facing_104+x_ec,y_f0+180.0,facing_104,1);}
  if(!frame_timer_142&&frame_index_140==6){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={-40.0f,4.0f,0.0f};spawn(801,110*facing_104+x_ec,y_f0+100.0,facing_104,1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);state_180=1;phase_counter(50);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
 }return;
}

case 411:{
 landing();if(sequence_index_13e<2&&!field_6c4)byte_750=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(FRAME(0,6)){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*facing_104+x_ec,y_f0,facing_104,1,packet,3);}
 if(FRAME(1,3)){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*facing_104+x_ec,y_f0,facing_104,1,packet,3);}return;
}

case 412:{
 landing();if(sequence_index_13e<2&&!field_6c4)byte_750=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==4&&byte_750==1){next_sequence_block();effect(62,7*facing_104+x_ec,y_f0+180.0,facing_104,1);}
  if(!frame_timer_142&&frame_index_140==6){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={40.0f,-4.0f,0.0f};spawn(801,110*facing_104+x_ec,y_f0+50.0,facing_104,1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);state_180=1;phase_counter(50);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
 }return;
}

case 414:{
 if(sequence_index_13e==2)landing();
 if(sequence_index_13e<2){if((!sequence_index_13e&&frame_index_140>8)||(sequence_index_13e==1&&frame_index_140>5))velocity_y_f8-=acceleration_y_100;if(!field_6c4)byte_750=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(ENTRY(2)){set_action_and_finalize(9);return;}

 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==4&&byte_750==1){next_sequence_block();effect(62,7*facing_104+x_ec,y_f0+187.0,facing_104,1);}
  if(!frame_timer_142&&frame_index_140==6){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={-50.0f,4.0f,0.0f};spawn(801,110*facing_104+x_ec,y_f0+156.0,facing_104,1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);state_180=1;phase_counter(50);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
 }return;
}

case 415:{
 if(sequence_index_13e==2)landing();if(sequence_index_13e<2){if((!sequence_index_13e&&frame_index_140>8)||(sequence_index_13e==1&&frame_index_140>5))velocity_y_f8-=acceleration_y_100;if(!field_6c4)byte_750=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}
 if(!frame_timer_142&&frame_index_140==6){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*facing_104+x_ec,y_f0,facing_104,1,packet,3);}return;
}

case 416:{
 if(sequence_index_13e==2)landing();
 if(sequence_index_13e<2){if((!sequence_index_13e&&frame_index_140>8)||(sequence_index_13e==1&&frame_index_140>5))velocity_y_f8-=acceleration_y_100;if(!field_6c4)byte_750=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(ENTRY(2)){set_action_and_finalize(9);return;}

 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==4&&byte_750==1){next_sequence_block();effect(62,7*facing_104+x_ec,y_f0+187.0,facing_104,1);}
  if(!frame_timer_142&&frame_index_140==6){counter(200,60);state_180=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={50.0f,-4.0f,0.0f};spawn(801,110*facing_104+x_ec,y_f0+50.0,facing_104,1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);state_180=1;phase_counter(50);AIM_SHORT();if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);
 }return;
}

case 418:{
 if((!sequence_index_13e&&frame_index_140<=2)||sequence_index_13e==2)landing();ADVANCE_TO(0);
 if(sequence_index_13e<2){
  if(!sequence_index_13e){
   if(frame_index_140<3){velocity_x_f4-=1.0;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
   if(frame_index_140>2&&frame_index_140<9){MOTION->set_oriented_components(-20.0f,field_73c);field_73c-=1.5;if(field_73c<6.0)field_74c=6.0;}
   if(!frame_timer_142){if(frame_index_140==4)event(28);if(!frame_timer_142&&frame_index_140==9)acceleration_y_100=0.5f;}
  }
  velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=aya_surface(this);velocity_y_f8=0.0;}
 }
 if(sequence_index_13e==2){velocity_x_f4-=2.0;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}return;
}

case 500:{landing();byte_17c=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(FRAME(0,4)){dispatch_character_wave_handle(4);state_180=1;counter(200,120);phase_counter(50);float packet[3]={0.0f,25.0f,0.0f};spawn(810,60*facing_104+x_ec,y_f0,facing_104,1,packet,3);}return;}

case 502:{if(sequence_index_13e==1)landing();byte_17c=0;if(!sequence_index_13e){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){next_sequence_block();y_f0=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(FRAME(0,4)){dispatch_character_wave_handle(4);state_180=1;counter(200,120);phase_counter(50);velocity_x_f4=-4.0;velocity_y_f8=6.0;acceleration_y_100=0.5f;float packet[3]={60.0f,20.0f,1.0f};spawn(810,53*facing_104+x_ec,y_f0+76.0,facing_104,1,packet,3);}return;}

case 505:{
 landing();byte_17c=4;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);state_180=1;phase_counter(50);int count;if(sbyte_608>=4)count=4;if(sbyte_608<=3)count=3;if(sbyte_608<=1)count=2;
  float packet[3];for(int i=0;i<count;++i){packet[0]=i*-20+20.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+100.0)*facing_104+x_ec,aya_sine(-packet[0])*100.0+(y_f0+100.0),facing_104,1,packet,3);
  }
 }return;
}

case 506:{
 landing();byte_17c=4;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);state_180=1;phase_counter(50);int count;if(sbyte_608>=4)count=4;if(sbyte_608<=3)count=3;if(sbyte_608<=1)count=2;
  float packet[3];for(int i=0;i<count;++i){packet[0]=i*-20-30.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+100.0)*facing_104+x_ec,aya_sine(-packet[0])*100.0+(y_f0+100.0),facing_104,1,packet,3);
  }
 }return;
}

case 507:{
 if(sequence_index_13e==2)landing();byte_17c=4;if(!sequence_index_13e){if(frame_index_140>=8)velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}
 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==4){dispatch_character_wave_handle(14);counter(200,120);state_180=1;phase_counter(50);int count;if(sbyte_608>=4)count=4;if(sbyte_608<=3)count=3;if(sbyte_608<=1)count=2;
   float packet[3];for(int i=0;i<count;++i){packet[0]=i*-20+20.0;packet[1]=25.0f;packet[2]=0.0f;
    spawn(811,(aya_cosine(-packet[0])*100.0+47.0)*facing_104+x_ec,aya_sine(-packet[0])*100.0+(y_f0+121.0),facing_104,1,packet,3);
   }
  }
  if(!frame_timer_142&&frame_index_140==8)acceleration_y_100=0.5f;
 }return;
}

case 508:{
 if(sequence_index_13e==2)landing();byte_17c=4;if(!sequence_index_13e){if(frame_index_140>=8)velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}
 if(!sequence_index_13e){
  if(!frame_timer_142&&frame_index_140==4){dispatch_character_wave_handle(14);counter(200,120);state_180=1;phase_counter(50);int count;if(sbyte_608>=4)count=4;if(sbyte_608<=3)count=3;if(sbyte_608<=1)count=2;
   float packet[3];for(int i=0;i<count;++i){packet[0]=i*20+30.0;packet[1]=25.0f;packet[2]=0.0f;
    spawn(811,(aya_cosine(-packet[0])*100.0+47.0)*facing_104+x_ec,aya_sine(-packet[0])*100.0+(y_f0+121.0),facing_104,1,packet,3);
   }
  }
  if(!frame_timer_142&&frame_index_140==8)acceleration_y_100=0.5f;
 }return;
}

case 510:{landing();byte_17c=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(FRAME(0,4)){dispatch_character_wave_handle(16);state_180=1;counter(200,120);phase_counter(50);float packet[3]={0.0f,0.0f,1.0f};spawn(812,175*facing_104+x_ec,y_f0+130.0,facing_104,1,packet,3);packet[1]=150.0f;packet[2]=0.0f;float n=0.0f;do{packet[0]=n*45.0;spawn(812,175*facing_104+x_ec,y_f0+130.0,facing_104,1,packet,3);n+=1.0;}while(n<8.0);n=0.0f;do{packet[0]=n*60.0+30.0;packet[1]=15.0f;packet[2]=2.0f;if(packet[0]>=0.0&&packet[0]<=180.0)spawn(812,175*facing_104+x_ec,y_f0,facing_104,1,packet,3);else spawn(812,175*facing_104+x_ec,y_f0,facing_104,-1,packet,3);n+=1.0;}while(n<6.0);}return;}

case 520:{
 if(!sequence_index_13e||sequence_index_13e==4||sequence_index_13e==5)landing();byte_17c=1;
 if(sequence_index_13e==1&&(state_180==2||state_180==7)){next_sequence_block();velocity_x_f4=-8.0;velocity_y_f8=12.5;return;}
 if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();y_f0=aya_surface(this);return;}}
 if(sequence_index_13e==4){velocity_x_f4-=1.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=0.0f;spawn(815,x_ec,y_f0+45.0,facing_104,1,&packet,1);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20)select_sequence(4);if(ENTRY(5))set_action_and_finalize(0);return;
}

case 521:{
 if(!sequence_index_13e||sequence_index_13e==6)landing();byte_17c=1;
 if(sequence_index_13e==1&&(state_180==2||state_180==7)){next_sequence_block();velocity_x_f4=-8.0;velocity_y_f8=12.5;return;}
 if(sequence_index_13e==2||sequence_index_13e==3||sequence_index_13e==4||sequence_index_13e==5){if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;}velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=-45.0f;spawn(815,x_ec,y_f0+45.0,facing_104,1,&packet,1);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(-45.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20){state_180=1;select_sequence(4);acceleration_y_100=0.6f;velocity_y_f8*=0.5;velocity_x_f4*=0.25;}return;
}

case 522:{
 if(sequence_index_13e==6)landing();byte_17c=1;
 if(sequence_index_13e==1&&(state_180==2||state_180==7)){next_sequence_block();velocity_x_f4=-8.0;velocity_y_f8=12.5;return;}
 if(sequence_index_13e==2||sequence_index_13e==3||sequence_index_13e==4||sequence_index_13e==5){if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;}velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=0.0f;spawn(815,x_ec,y_f0+45.0,facing_104,1,&packet,1);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20){state_180=1;select_sequence(4);velocity_x_f4*=0.5;}return;
}

case 523:{
 if(sequence_index_13e==6)landing();byte_17c=1;
 if(sequence_index_13e==1&&(state_180==2||state_180==7)){next_sequence_block();velocity_x_f4=-8.0;velocity_y_f8=12.5;return;}
 if(sequence_index_13e==1||sequence_index_13e==2||sequence_index_13e==3||sequence_index_13e==4||sequence_index_13e==5){if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;}if(sequence_index_13e>1)velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0;if(sequence_index_13e>1)zero_motion();select_sequence(6);y_f0=aya_surface(this);return;}}
 if(sequence_index_13e==6){velocity_x_f4-=1.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=45.0f;spawn(815,x_ec,y_f0+45.0,facing_104,1,&packet,1);MOTION->set_oriented_components(45.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20){select_sequence(4);acceleration_y_100=0.6f;velocity_y_f8*=0.5;velocity_x_f4*=0.25;}return;
}

case 525:{
 if(!sequence_index_13e||sequence_index_13e==3||sequence_index_13e==4)landing();
 if(sequence_index_13e==1){if(state_180!=0&&state_180!=3){next_sequence_block();return;}if(time_counter_144>=30){select_sequence(3);velocity_x_f4*=0.5;return;}if(time_counter_144>=20&&(field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(0);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==2){if(time_counter_144>=20){next_sequence_block();return;}if((field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(0);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==3||sequence_index_13e==4){velocity_x_f4-=static_cast<double>(0.35f);if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={0.0f,0.0f,0.0f};spawn(816,x_ec,y_f0+45.0,facing_104,1,packet,3);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(0.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 526:{
 if(!sequence_index_13e||sequence_index_13e==5)landing();
 if(sequence_index_13e==1){if(state_180!=0&&state_180!=3){next_sequence_block();return;}if(time_counter_144>=30){select_sequence(3);velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if(time_counter_144>=20&&(field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==2){if(time_counter_144>=20){next_sequence_block();velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if((field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==3||sequence_index_13e==4){velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={-45.0f,0.0f,0.0f};spawn(816,x_ec,y_f0+45.0,facing_104,1,packet,3);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(-45.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 527:{
 if(sequence_index_13e==5)landing();
 if(sequence_index_13e==1){if(state_180!=0&&state_180!=3){next_sequence_block();return;}if(time_counter_144>=30){select_sequence(3);velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if(time_counter_144>=20&&(field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==2){if(time_counter_144>=20){next_sequence_block();velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if((field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==3||sequence_index_13e==4){velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={0.0f,0.0f,0.0f};spawn(816,x_ec,y_f0+45.0,facing_104,1,packet,3);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(0.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 528:{
 if(sequence_index_13e==5)landing();
 if(sequence_index_13e==1){if(state_180!=0&&state_180!=3){next_sequence_block();return;}if(static_cast<unsigned char>(crossed())){ velocity_y_f8 = 0.0f; select_sequence(5); y_f0 = aya_surface(this); return; }if(time_counter_144>=30){select_sequence(3);velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if(time_counter_144>=20&&(field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==2){if(static_cast<unsigned char>(crossed())){ velocity_y_f8 = 0.0f; select_sequence(5); y_f0 = aya_surface(this); return; }if(time_counter_144>=20){next_sequence_block();velocity_x_f4*=0.5;velocity_y_f8*=0.5;return;}if((field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(sequence_index_13e==3||sequence_index_13e==4){velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=aya_surface(this);zero_motion();return;}}if(sequence_index_13e==5&&velocity_x_f4>0.0){velocity_x_f4-=0.75;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={45.0f,0.0f,0.0f};spawn(816,x_ec,y_f0+45.0,facing_104,1,packet,3);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(45.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 529:{
 if(sequence_index_13e==16||sequence_index_13e==19)landing();
 if(sequence_index_13e==2||sequence_index_13e==5||sequence_index_13e==8||sequence_index_13e==11||sequence_index_13e==14){
  if(time_counter_144>=20){next_sequence_block();return;}
  if(((!word_738&&sbyte_609>=2)||(word_738==1&&sbyte_609>=4))&&(field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);++word_738;set_action_and_finalize(529);return;}
 }
 if(sequence_index_13e==3||sequence_index_13e==6||sequence_index_13e==9||sequence_index_13e==12||sequence_index_13e==15){
  if(time_counter_144>=5){if(static_cast<unsigned char>(aya_on_surface(this)))select_sequence(16);else select_sequence(17);velocity_x_f4*=0.5;if(velocity_y_f8>0.0)velocity_y_f8*=0.5;return;}
  if(!word_738&&sbyte_609>=4&&(field_6bc>0||field_6c0>0||field_6c4>0)){CHOOSE_FOLLOWUP(1);word_738=1;set_action_and_finalize(529);return;}
 }
 if(sequence_index_13e<=15&&static_cast<unsigned char>(crossed())){select_sequence(19);y_f0=aya_surface(this);velocity_y_f8=0.0;return;}
 if(sequence_index_13e==16){velocity_x_f4-=0.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 if(sequence_index_13e==17||sequence_index_13e==18){velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(19);y_f0=aya_surface(this);velocity_y_f8=0.0;return;}}
 if(sequence_index_13e==19){velocity_x_f4-=1.0;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);
 if(!time_counter_144){
  if(!frame_timer_142&&!frame_index_140&&sequence_index_13e==1){
   float packet[3];
   if(word_730==0){packet[0]=0.0f;packet[1]=80.0f;packet[2]=0.0f;select_sequence(1);MOTION->set_oriented_components(0.0f,20.0f);}
   if(word_730==1){packet[0]=-45.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(4);MOTION->set_oriented_components(-45.0f,20.0f);}
   if(word_730==2){packet[0]=-90.0f;packet[1]=120.0f;packet[2]=0.0f;select_sequence(10);MOTION->set_oriented_components(-90.0f,20.0f);}
   if(word_730==-1){packet[0]=45.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(7);MOTION->set_oriented_components(45.0f,20.0f);}
   if(word_730==-2){packet[0]=90.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(13);MOTION->set_oriented_components(90.0f,20.0f);}
   spawn(816,x_ec,packet[2]+y_f0,facing_104,1,packet,3);
   if(static_cast<unsigned char>(aya_on_surface(this)))effect(127,x_ec,y_f0,facing_104,-1);
   dispatch_character_wave_handle(5);
  }
  if(ENTRY(17)){set_action_and_finalize(0);zero_motion();}
 }return;
}

case 530:{
 if(sequence_index_13e==4)landing();byte_17c=9;
 if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4-=3.0;if(velocity_x_f4<3.0)velocity_x_f4=3.0;velocity_y_f8-=acceleration_y_100;if(sequence_index_13e==2&&frame_index_140<=11&&velocity_y_f8<=-1.0)velocity_y_f8=-1.0;if(static_cast<unsigned char>(crossed())){select_sequence(4);y_f0=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(2))acceleration_y_100=0.5f;if(FRAME(0,5)){velocity_x_f4=40.0;velocity_y_f8=10.0;effect(127,x_ec,y_f0,facing_104,-1);}
 if(FRAME(2,5)){float packet[2]={15.0f,30.0f};spawn(817,x_ec-static_cast<float>(130*facing_104),static_cast<float>(y_f0+50.0),static_cast<signed char>(-facing_104),1,packet,3);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(19);return;}return;
}

case 532:{
 if(sequence_index_13e==4)landing();byte_17c=9;
 if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4-=3.0;if(velocity_x_f4<3.0)velocity_x_f4=3.0;velocity_y_f8-=acceleration_y_100;if(sequence_index_13e==2&&frame_index_140<=11&&velocity_y_f8<=-1.0)velocity_y_f8=-1.0;if(static_cast<unsigned char>(crossed())){select_sequence(4);y_f0=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(2))acceleration_y_100=0.5f;if(FRAME(0,5)){velocity_x_f4=40.0;velocity_y_f8=10.0;effect(127,x_ec,y_f0,facing_104,-1);}
 if(FRAME(2,5)){float packet[2]={15.0f,30.0f};spawn(817,x_ec-static_cast<float>(130*facing_104),static_cast<float>(y_f0+50.0),static_cast<signed char>(-facing_104),1,packet,3);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(19);return;}return;
}

case 540:{
 byte_17c=2;
 if(FRAME(0,5)){float packet[3]={0.0f,0.0f,0.0f};dispatch_character_wave_handle(6);counter(200,120);state_180=1;phase_counter(50);spawn(820,x_ec,y_f0,facing_104,1,packet,3);}
 if(sequence_index_13e==1){
  if(time_counter_144>60){select_sequence(5);acceleration_y_100=0.5f;return;}
  if(field_6b8<0){
   if(field_6b4*facing_104>0){
    select_sequence(2);dispatch_character_wave_handle(7);velocity_x_f4=8.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;
    float packet[3]={135.0f,20.0f,4.0f};spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[2]=5.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);
    if(sbyte_606>=4){packet[2]=6.0f;packet[0]=150.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[0]=120.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);}return;
   }
   if(field_6b4*facing_104<0){
    dispatch_character_wave_handle(7);select_sequence(4);velocity_x_f4=-8.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;
    float packet[3]={45.0f,20.0f,4.0f};spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[2]=5.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);
    if(sbyte_606>=4){packet[2]=6.0f;packet[0]=30.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[0]=60.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);}return;
   }
   dispatch_character_wave_handle(7);select_sequence(3);velocity_x_f4=0.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;
   float packet[3]={90.0f,20.0f,4.0f};spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[2]=5.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);
   if(sbyte_606>=4){packet[2]=6.0f;packet[0]=105.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);packet[0]=75.0f;spawn(820,x_ec,y_f0,facing_104,1,packet,3);}return;
  }
 }
 if(sequence_index_13e>1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(9);if(ENTRY(3)||ENTRY(4)){set_action_and_finalize(9);return;}if(ENTRY(5))set_action_and_finalize(9);return;
}

case 545:{
 if(sequence_index_13e==2)landing();byte_17c=6;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){
  dispatch_character_wave_handle(23);layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};spawn(821,x_ec,y_f0,facing_104,1,packet,3);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}
  select_sequence(2);y_f0=aya_surface(this);zero_motion();return;
 }
 ADVANCE_TO(0);if(FRAME(0,4)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);float packet[3]={70.0f,0.0f,2.0f};spawn(821,20*facing_104+x_ec,y_f0,facing_104,1,packet,3);}return;
}

case 546:{
 if(sequence_index_13e==2)landing();byte_17c=6;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){
  dispatch_character_wave_handle(23);layout(5.0f);float packet[3]={0.0f,0.0f,5.0f};spawn(821,x_ec,y_f0,facing_104,-1,packet,3);packet[2]=6.0f;spawn(821,x_ec,y_f0,facing_104,-1,packet,3);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}
  packet[0]=0.0f;packet[1]=17.5f;packet[2]=3.0f;spawn(821,x_ec,0.0f,facing_104,1,packet,3);spawn(821,x_ec,0.0f,static_cast<unsigned char>(-facing_104),1,packet,3);
  if(sbyte_60a>=4){packet[1]=30.0f;spawn(821,x_ec,0.0f,facing_104,1,packet,3);spawn(821,x_ec,0.0f,static_cast<unsigned char>(-facing_104),1,packet,3);}
  select_sequence(2);y_f0=aya_surface(this);zero_motion();state_180=1;return;
 }
 ADVANCE_TO(0);if(FRAME(0,4)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);float packet[3]={70.0f,0.0f,2.0f};spawn(821,20*facing_104+x_ec,y_f0,facing_104,1,packet,3);}return;
}

case 550:{
 byte_17c=10;if(!sequence_index_13e||sequence_index_13e==7)landing();
 if(sequence_index_13e==2&&state_180){next_sequence_block();zero_motion();return;}
 if(sequence_index_13e>0&&sequence_index_13e<7)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<7){select_sequence(7);y_f0=aya_surface(this);zero_motion();return;}
 if(sequence_index_13e==1||sequence_index_13e==2){
  if(aya_absolute(x_ec-related_170->x_ec)<=100.0)word_730=1;
  if(word_730==1)velocity_x_f4*=static_cast<double>(0.92f);
  if(facing_104*field_6b4>0)velocity_x_f4+=(static_cast<double>(sbyte_60e)*static_cast<double>(0.1f)+0.25);
  if(facing_104*field_6b4<0)velocity_x_f4-=(static_cast<double>(sbyte_60e)*static_cast<double>(0.1f)+0.25);
  if(velocity_x_f4>10.0)velocity_x_f4=10.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
 }
 if(sequence_index_13e==5||sequence_index_13e==6){
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>12.0)velocity_x_f4=12.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
  if(sequence_index_13e==6||(sequence_index_13e==5&&frame_index_140>=3)){if(field_6c4>0){set_action_and_finalize(554);select_sequence(6);return;}if(field_6c0>0){set_action_and_finalize(554);return;}if(field_6bc>0){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);velocity_x_f4=10.0;velocity_y_f8=25.0;acceleration_y_100=1.25f;spawn(990,x_ec,y_f0,facing_104,1,0,0);effect(128,200*facing_104+x_ec,y_f0,facing_104,-1);}
 if(ENTRY(5)){velocity_x_f4=-6.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;}
 return;
}

case 551:{
 byte_17c=10;if(!sequence_index_13e||sequence_index_13e==7)landing();
 if(sequence_index_13e==2&&state_180){next_sequence_block();zero_motion();return;}
 if(sequence_index_13e>0&&sequence_index_13e<7)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<7){select_sequence(7);y_f0=aya_surface(this);zero_motion();return;}
 if(sequence_index_13e==1||sequence_index_13e==2){
  if(aya_absolute(x_ec-related_170->x_ec)<=300.0)word_730=1;
  if(word_730==1)velocity_x_f4*=static_cast<double>(0.92f);
  if(facing_104*field_6b4>0)velocity_x_f4+=(static_cast<double>(sbyte_60e)*static_cast<double>(0.1f)+0.25);
  if(facing_104*field_6b4<0)velocity_x_f4-=(static_cast<double>(sbyte_60e)*static_cast<double>(0.1f)+0.25);
  if(velocity_x_f4>25.0)velocity_x_f4=25.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
 }
 if(sequence_index_13e==5||sequence_index_13e==6){
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>12.0)velocity_x_f4=12.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
  if(sequence_index_13e==6||(sequence_index_13e==5&&frame_index_140>=3)){if(field_6c4>0){set_action_and_finalize(554);select_sequence(6);return;}if(field_6c0>0){set_action_and_finalize(554);return;}if(field_6bc>0){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);velocity_x_f4=25.0;velocity_y_f8=25.0;acceleration_y_100=1.0f;spawn(990,x_ec,y_f0,facing_104,1,0,0);effect(128,200*facing_104+x_ec,y_f0,facing_104,-1);}
 if(ENTRY(5)){velocity_x_f4=-6.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;}
 return;
}

case 552:{
 byte_17c=10;if(sequence_index_13e==7)landing();
 if(sequence_index_13e==2&&state_180){next_sequence_block();zero_motion();return;}
 if(sequence_index_13e>0&&sequence_index_13e<7)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<7){select_sequence(7);y_f0=aya_surface(this);zero_motion();return;}
 if(sequence_index_13e==1||sequence_index_13e==2){
  if(aya_absolute(x_ec-related_170->x_ec)<=100.0)word_730=1;
  if(word_730==1)velocity_x_f4*=static_cast<double>(0.92f);
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;
  if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>25.0)velocity_x_f4=25.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
 }
 if(sequence_index_13e==5||sequence_index_13e==6){
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>12.0)velocity_x_f4=12.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
  if(sequence_index_13e==6&&field_6c4>0){set_action_and_finalize(554);select_sequence(6);return;}if(sequence_index_13e==6&&field_6c0>0){set_action_and_finalize(554);return;}if(sequence_index_13e==6&&field_6bc>0){set_action_and_finalize(554);select_sequence(3);return;}
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);velocity_x_f4=10.0;velocity_y_f8=25.0;acceleration_y_100=1.25f;spawn(990,x_ec,y_f0,facing_104,1,0,0);}
 if(ENTRY(5)){velocity_x_f4=-6.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;}
 return;
}

case 553:{
 byte_17c=10;if(sequence_index_13e==7)landing();
 if(sequence_index_13e==2&&state_180){next_sequence_block();zero_motion();return;}
 if(sequence_index_13e>0&&sequence_index_13e<7)velocity_y_f8-=acceleration_y_100;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<7){select_sequence(7);y_f0=aya_surface(this);zero_motion();return;}
 if(sequence_index_13e==1||sequence_index_13e==2){
  if(aya_absolute(x_ec-related_170->x_ec)<=300.0)word_730=1;
  if(word_730==1)velocity_x_f4*=static_cast<double>(0.92f);
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;
  if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>25.0)velocity_x_f4=25.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
 }
 if(sequence_index_13e==5||sequence_index_13e==6){
  if(facing_104*field_6b4>0)velocity_x_f4+=0.25;if(facing_104*field_6b4<0)velocity_x_f4-=0.25;
  if(velocity_x_f4>12.0)velocity_x_f4=12.0;if(velocity_x_f4<-12.0)velocity_x_f4=-12.0;
  if(sequence_index_13e==6&&field_6c4>0){set_action_and_finalize(554);select_sequence(6);return;}if(sequence_index_13e==6&&field_6c0>0){set_action_and_finalize(554);return;}if(sequence_index_13e==6&&field_6bc>0){set_action_and_finalize(554);select_sequence(3);return;}
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);velocity_x_f4=25.0;velocity_y_f8=25.0;acceleration_y_100=1.0f;spawn(990,x_ec,y_f0,facing_104,1,0,0);}
 if(ENTRY(5)){velocity_x_f4=-6.0;velocity_y_f8=12.0;acceleration_y_100=0.5f;}
 return;
}

case 554:{
 if(sequence_index_13e==2||sequence_index_13e==5)landing();
 if(ENTRY(0)){zero_motion();byte_47e=0;word_730=0;}
 if(ENTRY(3)){byte_47e=0;word_730=0;}if(ENTRY(6)){velocity_x_f4*=0.25;velocity_y_f8*=0.25;acceleration_y_100=0.0;}
 byte_17c=10;
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){
  layout(5.0f);float packet[3];for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}
  select_sequence(2);y_f0=aya_surface(this);zero_motion();return;
 }
 if(sequence_index_13e==3||sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=aya_surface(this);zero_motion();return;}}
 if(sequence_index_13e==6){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=aya_surface(this);zero_motion();return;}}
 if(advance()){select_sequence(4);return;}
 if(ENTRY(3)||ENTRY(6)){set_action_and_finalize(0);return;}
 if(FRAME(0,4)){dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);phase_counter(25);}
 if(FRAME(3,4)){dispatch_character_wave_handle(15);phase_counter(25);}
 if(FRAME(6,3)){
  field_744=-aya_atan(related_170->y_f0-y_f0,static_cast<float>((static_cast<double>(related_170->x_ec)-x_ec)*facing_104));
  if(field_744>75.0)field_744=75.0;if(field_744<-30.0)field_744=-30.0;
  float packet[3]={field_744,15.0f,0.0f};spawn(822,47*facing_104+x_ec,y_f0+106.0,facing_104,1,packet,3);
  MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(25);dispatch_character_wave_handle(19);state_180=1;velocity_y_f8=7.5;velocity_x_f4=-7.5;acceleration_y_100=0.5f;
 }return;
}

case 560:{
 landing();byte_17c=3;
 if(word_730==1){if(!(word_732%4)&&word_732*0.25<=sbyte_607+5){
  float packet[3];packet[0]=(static_cast<float>(static_cast<unsigned>(aya_random(400)))+x_ec)-200.0;packet[1]=(y_f0+175.0)+175.0;packet[2]=0.0f;
  spawn(825,static_cast<float>(1380.0-1480*(facing_104==1)),static_cast<float>(static_cast<float>(static_cast<unsigned>(aya_random(300)))+(y_f0+300.0)),facing_104,1,packet,3);
 }++word_732;}
 ADVANCE_TO(0);if(FRAME(0,1)){dispatch_character_wave_handle(17);word_730=1;state_180=1;counter(200,120);phase_counter(50);}return;
}

case 561:{
 landing();byte_17c=3;
 if(word_730==1){if(!(word_732%4)&&word_732*0.25<=sbyte_607+5){
  float packet[3];packet[0]=(static_cast<float>(static_cast<unsigned>(aya_random(400)))+related_170->x_ec)-200.0;packet[1]=(related_170->y_f0+175.0)+175.0;packet[2]=0.0f;
  spawn(825,static_cast<float>(1380.0-1480*(facing_104==1)),static_cast<float>(static_cast<float>(static_cast<unsigned>(aya_random(300)))+(y_f0+300.0)),facing_104,1,packet,3);
 }++word_732;}
 ADVANCE_TO(0);if(FRAME(0,1)){dispatch_character_wave_handle(17);word_730=1;state_180=1;counter(200,120);phase_counter(50);}return;
}

case 565:{landing();ADVANCE_TO(0);if(FRAME(0,8)){float packet[3];packet[0]=(y_f0<=aya_surface(this))?0.0f:1.0f;packet[1]=0.0f;packet[2]=0.0f;spawn(826,x_ec+0.0,y_f0+100.0,facing_104,1,packet,3);dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);}return;}

case 567:{if(advance()){set_action_and_finalize(9);acceleration_y_100=0.6f;}if(FRAME(0,8)){float packet[3];packet[0]=(y_f0<=aya_surface(this))?0.0f:1.0f;packet[1]=0.0f;packet[2]=0.0f;spawn(826,x_ec+0.0,y_f0+100.0,facing_104,1,packet,3);dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);}return;}

case 600:{
 landing();texture(2,2);if(sequence_index_13e==1&&time_counter_144>60){next_sequence_block();return;}ADVANCE_TO(0);
 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==3){word_48a=40;event(23);effect(115,44*facing_104+x_ec,y_f0+138.0,facing_104,1);sequence_window(0,3,60);secondary_cycle();}
  if(!frame_timer_142&&frame_index_140==6){spawn(850,80*facing_104+x_ec,y_f0,facing_104,1,0,0);dispatch_character_wave_handle(9);}
 }return;
}

case 601:{
 landing();texture(2,2);if(sequence_index_13e==1){layout(5.0f);if(time_counter_144>90){next_sequence_block();return;}}if(sequence_index_13e==2&&time_counter_144>60){next_sequence_block();return;}ADVANCE_TO(0);
 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==3){word_48a=40;event(23);effect(115,44*facing_104+x_ec,y_f0+138.0,facing_104,1);sequence_window(0,5,60);secondary_cycle();}
  if(!frame_timer_142&&frame_index_140==6){spawn(851,x_ec,y_f0,facing_104,1,0,0);dispatch_character_wave_handle(10);}
 }return;
}

case 602:{
 landing();texture(2,2);if(sequence_index_13e==1){layout(2.0f);if(time_counter_144>30){next_sequence_block();return;}}if(advance()){set_action_and_finalize(0);texture(2,240);}
 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==3){word_48a=40;event(23);effect(115,44*facing_104+x_ec,y_f0+138.0,facing_104,1);sequence_window(0,4,60);secondary_cycle();}
  if(!frame_timer_142&&frame_index_140==6){float packet[3]={0.0f,0.0f,0.0f};spawn(852,x_ec,y_f0,facing_104,1,packet,3);dispatch_character_wave_handle(11);}
 }return;
}

case 603:{
 texture(2,2);if(sequence_index_13e==1&&time_counter_144>=40){next_sequence_block();return;}if(sequence_index_13e==1&&time_counter_144>=40){next_sequence_block();return;}
 if(sequence_index_13e>1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(9);
 if(ENTRY(1)){word_48a=40;event(23);effect(115,x_ec,y_f0+120.0,facing_104,1);sequence_window(0,3,60);secondary_cycle();}
 if(ENTRY(3)){dispatch_character_wave_handle(24);float packet[3]={0.0f,0.0f,8.0f};spawn(853,x_ec,y_f0,facing_104,1,packet,3);
  for(int n=0;n<4;++n){packet[0]=static_cast<float>(static_cast<unsigned>(aya_random(60)))+60.0;packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(10)))+15.0;packet[2]=4.0f;spawn(853,x_ec,y_f0,facing_104,1,packet,3);}
  for(int n=0;n<8;++n){packet[0]=static_cast<float>(static_cast<unsigned>(aya_random(100)))+40.0;packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(15)))+5.0;packet[2]=6.0f;spawn(853,x_ec,y_f0,facing_104,1,packet,3);}
  velocity_x_f4=0.0;velocity_y_f8=17.5;acceleration_y_100=0.5f;
 }
 if(FRAME(0,5)){float packet[3]={0.0f,0.0f,0.0f};dispatch_character_wave_handle(6);spawn(853,x_ec,y_f0,facing_104,1,packet,3);}return;
}

case 604:{landing();ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(word_730>0){if(word_730==1){dispatch_character_wave_handle(2);float packet[3]={30.0f,-4.0f,0.0f};spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);packet[0]=-30.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);}if(word_730==6){dispatch_character_wave_handle(2);float packet[3]={45.0f,-4.0f,0.0f};spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);packet[0]=-45.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);}if(word_730==11){dispatch_character_wave_handle(2);float packet[3]={60.0f,-4.0f,0.0f};spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);packet[0]=-60.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*facing_104+x_ec,y_f0+105.0,facing_104,1,packet,3);}++word_730;}
 if(!sequence_index_13e&&!frame_timer_142){if(frame_index_140==2){word_48a=40;event(23);effect(115,8*facing_104+x_ec,y_f0+176.0,facing_104,1);sequence_window(0,2,60);secondary_cycle();}if(!frame_timer_142&&frame_index_140==5)word_730=1;}return;
}

case 605:{
 landing();texture(2,2);if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(!sequence_index_13e&&!frame_timer_142){
  if(frame_index_140==3){word_48a=40;event(23);effect(115,44*facing_104+x_ec,y_f0+138.0,facing_104,1);sequence_window(0,2,60);secondary_cycle();}
  if(!frame_timer_142&&frame_index_140==6){spawn(855,x_ec+0.0,y_f0+100.0,facing_104,1,0,0);dispatch_character_wave_handle(12);}
 }return;
}

case 606:{
 if(!sequence_index_13e||sequence_index_13e==4||sequence_index_13e==9)landing();texture(2,2);
 if(sequence_index_13e==1&&state_180==1){float packet[3]={0.0f,0.0f,0.0f};spawn(856,x_ec,y_f0,facing_104,1,packet,3);select_sequence(5);zero_motion();shared_first(1,related_170->x_ec);shared_second(1,y_f0);x_ec=related_170->x_ec;y_f0=related_170->y_f0;return;}
 if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4-=0.5;if(velocity_x_f4<5.0)velocity_x_f4=5.0;velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();y_f0=aya_surface(this);event(30);return;}}
 if(sequence_index_13e==5){shared_first(1,related_170->x_ec);shared_second(1,y_f0);x_ec=related_170->x_ec;y_f0=related_170->y_f0;if(time_counter_144>=60){y_f0=related_170->y_f0;next_sequence_block();return;}}
 if(sequence_index_13e==6){
  if(field_73c==0.0&&field_6b4){field_73c=static_cast<float>(field_6b4);velocity_y_f8+=1.0;}
  if(field_73c>0.0&&field_6b4<0){field_73c=static_cast<float>(field_6b4);velocity_y_f8+=1.0;}
  if(field_73c<0.0&&field_6b4>0){field_73c=static_cast<float>(field_6b4);velocity_y_f8+=1.0;}
  if(velocity_y_f8>15.0)velocity_y_f8=15.0;velocity_y_f8-=static_cast<double>(0.1f);if(velocity_x_f4<-6.0)velocity_x_f4=-6.0;
  if(static_cast<unsigned char>(crossed()))velocity_y_f8=0.0;
  shared_first(1,related_170->x_ec);shared_second(1,y_f0);x_ec=related_170->x_ec;
  float packet[3];
  if(--word_730<=0){
   if(!word_732&&related_170->x_ec<640.0)word_732=1;
   if(y_f0<960.0){
    dispatch_character_wave_handle(22);
    if(!(word_732%2)){packet[0]=0.0f;packet[1]=120.0f;packet[2]=1.0f;spawn(856,1380.0f,static_cast<float>((y_f0+300.0)-static_cast<float>(static_cast<unsigned>(aya_random(400)))),-1,1,packet,3);++word_732;word_730=static_cast<short>(30-word_732);if(word_730<15)word_730=15;}
    else{packet[0]=0.0f;packet[1]=120.0f;packet[2]=1.0f;spawn(856,-100.0f,static_cast<float>((y_f0+300.0)-static_cast<float>(static_cast<unsigned>(aya_random(400)))),1,1,packet,3);++word_732;word_730=static_cast<short>(30-word_732);if(word_730<10)word_730=10;}
   }
  }
  if(time_counter_144>=20&&--word_734<=0&&y_f0<960.0){
   if(!(word_736%2)){packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=word_736+120.0;packet[2]=3.0f;spawn(856,1380.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+y_f0,-1,1,packet,3);}
   else{packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=word_736+120.0;packet[2]=3.0f;spawn(856,-100.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+y_f0,1,1,packet,3);}
   ++word_736;word_734=static_cast<short>(25-word_736);if(word_734<10)word_734=10;
  }
  if(time_counter_144>=100&&!(time_counter_144%14)&&y_f0<960.0){
   if(!(word_738%2)){packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(50)))+150.0;packet[2]=2.0f;spawn(856,1380.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+y_f0,-1,1,packet,3);}
   else{packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(50)))+150.0;packet[2]=2.0f;spawn(856,-100.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+y_f0,1,1,packet,3);}++word_738;
  }
  if(time_counter_144>=300){packet[0]=90.0f;packet[1]=30.0f;packet[2]=5.0f;spawn(856,640.0f,y_f0+100.0,1,1,packet,3);packet[0]=-90.0f;spawn(856,640.0f,y_f0+100.0,1,1,packet,3);packet[2]=4.0f;spawn(856,related_170->x_ec,y_f0+100.0,1,1,packet,3);next_sequence_block();return;}
 }
 if(sequence_index_13e==7){x_ec=related_170->x_ec;velocity_y_f8=40.0;if(y_f0>1280.0)y_f0=1280.0;if(time_counter_144>=40){velocity_y_f8=-30.0;acceleration_y_100=0.5f;next_sequence_block();shared_first(0,related_170->x_ec);shared_second(0,y_f0);return;}}
 if(sequence_index_13e==8){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){next_sequence_block();y_f0=aya_surface(this);zero_motion();return;}}
 if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(ENTRY(1)){dispatch_character_wave_handle(21);velocity_x_f4=60.0;velocity_y_f8=16.0;acceleration_y_100=0.15f;float packet[3];for(int angle=0;angle<360;angle+=36){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}}
 if(ENTRY(2)){velocity_x_f4*=0.25;velocity_y_f8=2.0;}
 if(ENTRY(5)){set_action_and_finalize(0);return;}
 if(FRAME(0,3)){word_48a=40;event(23);effect(115,x_ec-80*facing_104,y_f0+130.0,facing_104,1);sequence_window(0,5,60);secondary_cycle();}return;
}

case 611:{landing();texture(2,2);if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(!sequence_index_13e&&!frame_timer_142){if(frame_index_140==2){word_48a=40;event(23);effect(115,32*facing_104+x_ec,y_f0+144.0,facing_104,1);sequence_window(0,1,60);secondary_cycle();}if(!frame_timer_142&&frame_index_140==8){float packet[3]={y_f0==0.0?0.0f:1.0f,0.0f,0.0f};spawn(861,x_ec+0.0,y_f0+100.0,facing_104,1,packet,3);dispatch_character_wave_handle(13);}}return;
}

case 612:{
 if(!sequence_index_13e||sequence_index_13e==4||sequence_index_13e==5)landing();if(sequence_index_13e<2)texture(2,2);
 if(sequence_index_13e==1){if(!(time_counter_144%5))effect(127,x_ec,0.0f,facing_104,-1);if(state_180==2||state_180==7||x_boundary()){next_sequence_block();velocity_x_f4=-10.0;velocity_y_f8=14.0;return;}}
 if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();y_f0=aya_surface(this);return;}}if(sequence_index_13e==4){velocity_x_f4-=2.5;if(velocity_x_f4<0.0)velocity_x_f4=0.0;}
 ADVANCE_TO(0);if(FRAME(0,3)){word_48a=40;event(23);effect(115,x_ec-77*facing_104,y_f0+144.0,facing_104,1);sequence_window(0,3,60);secondary_cycle();}
 if(ENTRY(1)){float packet[2]={0.0f,0.0f};spawn(862,x_ec,y_f0+45.0,facing_104,1,packet,1);effect(127,x_ec,y_f0,facing_104,-1);MOTION->set_oriented_components(0.0f,40.0f);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20)select_sequence(4);if(ENTRY(5))set_action_and_finalize(0);return;
}

case 661:{texture(2,2);if(advance()){set_action_and_finalize(9);texture(2,60);acceleration_y_100=0.6f;}
 if(!sequence_index_13e&&!frame_timer_142){if(frame_index_140==2){word_48a=40;event(23);effect(115,32*facing_104+x_ec,y_f0+144.0,facing_104,1);sequence_window(0,1,60);secondary_cycle();}if(!frame_timer_142&&frame_index_140==8){float packet[3]={y_f0==0.0?0.0f:1.0f,0.0f,0.0f};spawn(861,x_ec+0.0,y_f0+100.0,facing_104,1,packet,3);dispatch_character_wave_handle(13);}}return;
}

case 662:{
 if(sequence_index_13e==6)landing();if(sequence_index_13e<2)texture(2,2);
 if(sequence_index_13e==1){if(!(time_counter_144%5))effect(127,x_ec,0.0f,facing_104,-1);if(state_180==2||state_180==7||x_boundary()){next_sequence_block();velocity_x_f4=-10.0;velocity_y_f8=14.0;return;}}
 if(sequence_index_13e==2||sequence_index_13e==3||sequence_index_13e==4||sequence_index_13e==5){if(sequence_index_13e==2||sequence_index_13e==3){velocity_x_f4+=static_cast<double>(0.15f);if(velocity_x_f4>0.0)velocity_x_f4=0.0;}velocity_y_f8-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();y_f0=aya_surface(this);return;}}
 ADVANCE_TO(0);if(FRAME(0,3)){word_48a=40;event(23);effect(115,x_ec-77*facing_104,y_f0+144.0,facing_104,1);sequence_window(0,3,60);secondary_cycle();}
 if(ENTRY(1)){float packet[2]={0.0f,0.0f};spawn(862,x_ec,y_f0+45.0,facing_104,1,packet,2);if(y_f0-aya_surface(this)<=150.0)effect(127,x_ec,aya_surface(this),facing_104,-1);MOTION->set_oriented_components(0.0f,40.0f);dispatch_character_wave_handle(5);}
 if(sequence_index_13e==1&&time_counter_144>20){select_sequence(4);velocity_x_f4*=0.5;}return;
}

case 695:{landing();ADVANCE_TO(0);if(FRAME(0,7)){event(55);effect(140,x_ec,y_f0+100.0,facing_104,1);effect(140,x_ec,y_f0+100.0,facing_104,1);effect(140,x_ec,y_f0+100.0,facing_104,1);effect(141,x_ec,y_f0+100.0,facing_104,-1);effect(142,x_ec,y_f0,facing_104,-1);}return;}

case 696:{landing();ADVANCE_TO(0);if(FRAME(0,3))event(29);return;}

case 710:{
 if(!sequence_index_13e||sequence_index_13e==6)landing();
 if(sequence_index_13e==1||sequence_index_13e==2){
  if(word_730==1){if(word_734<=60)++word_734;else{y_f0=related_170->y_f0;facing_104=-facing_104;float packet[3]={0.0f,35.0f,0.0f};spawn(900,static_cast<float>(-960*facing_104+640),y_f0,facing_104,1,packet,3);dispatch_character_wave_handle(5);word_730=2;}}
  if(word_730==3){velocity_x_f4=-60.0;if(x_boundary()==facing_104){float packet[3]={0.0f,0.0f,5.0f};spawn(900,x_ec-300*facing_104,y_f0+150.0,facing_104,1,packet,3);word_730=0;select_sequence(3);return;}}
 }
 if(sequence_index_13e==3&&word_730==1){velocity_x_f4=10.0;velocity_y_f8=-2.0;acceleration_y_100=0.45f;select_sequence(4);return;}
 if(sequence_index_13e==4||sequence_index_13e==5){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(6);y_f0=aya_surface(this);zero_motion();return;}}
 if(advance()){set_action_and_finalize(700);return;}
 if(ENTRY(1)){dispatch_character_wave_handle(5);float packet[3]={0.0f,35.0f,0.0f};spawn(900,x_ec,y_f0,facing_104,1,packet,3);}
 if(FRAME(0,2)){float packet[3]={0.0f,0.0f,5.0f};spawn(821,x_ec,y_f0,facing_104,-1,packet,3);packet[2]=6.0f;spawn(821,x_ec,y_f0,facing_104,-1,packet,3);for(int angle=0;angle<480;angle+=60){packet[0]=angle+45.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}}return;
}

case 720:{landing();if(advance()){set_action_and_finalize(700);return;}if(!frame_timer_142&&frame_index_140==8){float packet[3];float base;switch(g_aya_action_match){case 3:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=3.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+30.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 2:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<5.0;counter+=1.0){packet[0]=counter*72.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<5.0;counter+=1.0){packet[0]=counter*72.0+36.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 1:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<4.0;counter+=1.0){packet[0]=counter*90.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<4.0;counter+=1.0){packet[0]=counter*90.0+45.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 0:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<3.0;counter+=1.0){packet[0]=counter*120.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<3.0;counter+=1.0){packet[0]=counter*120.0+60.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}}dispatch_character_wave_handle(20);}return;}

case 721:{if(!sequence_index_13e||sequence_index_13e==5)landing();if(sequence_index_13e==1||sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;velocity_x_f4*=static_cast<double>(0.98f);if(velocity_y_f8<0.0)velocity_y_f8=0.0;}if(sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();y_f0=aya_surface(this);return;}}
 if(advance()){set_action_and_finalize(700);return;}if(ENTRY(1)){velocity_y_f8=17.5;velocity_x_f4=static_cast<float>(static_cast<unsigned>(aya_random(10)))-5.0;acceleration_y_100=0.5f;}if(ENTRY(3))zero_motion();if(sequence_index_13e==3&&!frame_timer_142){if(frame_index_140==8){float packet[3];float base;switch(g_aya_action_match){case 3:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=3.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<6.0;counter+=1.0){packet[0]=counter*60.0+30.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 2:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<5.0;counter+=1.0){packet[0]=counter*72.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<5.0;counter+=1.0){packet[0]=counter*72.0+36.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 1:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<4.0;counter+=1.0){packet[0]=counter*90.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<4.0;counter+=1.0){packet[0]=counter*90.0+45.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}case 0:{base=static_cast<float>(static_cast<unsigned>(aya_random(360)));for(float counter=0.0f;counter<3.0;counter+=1.0){packet[0]=counter*120.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,facing_104,1,packet,3);}for(float counter=0.0f;counter<3.0;counter+=1.0){packet[0]=counter*120.0+60.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,x_ec,y_f0+100.0,static_cast<unsigned char>(-facing_104),1,packet,3);}break;}}dispatch_character_wave_handle(20);}if(!frame_timer_142&&frame_index_140==15)acceleration_y_100=0.5f;}return;}

case 730:{landing();if(sequence_index_13e==1&&time_counter_144>60){next_sequence_block();return;}ADVANCE_TO(700);if(!sequence_index_13e){if(frame_index_140<=4&&!(time_counter_144%3)){field_73c-=16.0;if(field_73c<=-180.0)field_73c+=360.0;float packet[3]={field_73c,15.0f,1.0f};if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}if(!frame_timer_142&&frame_index_140==6){float packet[3]={0.0f,15.0f,0.0f};spawn(902,80*facing_104+x_ec,y_f0,facing_104,1,packet,3);dispatch_character_wave_handle(10);}}return;}

case 740:{
 if(!sequence_index_13e||sequence_index_13e==5)landing();
 if(sequence_index_13e==1){
  ++word_732;--word_734;
  if(word_734<=0){
   word_738-=5;if(word_738<10)word_738=10;word_734=word_738;
   float packet[3];packet[1]=URAND(30)+60.0;if(packet[1]>=90.0)packet[1]=90.0f;packet[2]=1.0f;
   dispatch_character_wave_handle(22);++word_736;
   if(!(word_736%2)){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,100,50.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,100,50.0);}
   if(!(word_736%3)){
    packet[1]=static_cast<double>(word_738)+static_cast<double>(word_738)+100.0;if(packet[1]>=100.0)packet[1]=100.0f;packet[2]=2.0f;
    if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
    else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   }
  }
  if(!word_730){velocity_x_f4=(640.0-x_ec)*static_cast<double>(0.2f)*facing_104;velocity_y_f8=(250.0-y_f0)*static_cast<double>(0.2f);}
  if(word_738==10){next_sequence_block();word_736=0;word_738=60;return;}
 }
 if(sequence_index_13e==2){
  if(!(word_732%60))emitter_168->dispatch_character_wave_handle(10);
  ++word_732;--word_734;--word_736;
  field_73c=-aya_atan(related_170->y_f0-y_f0,static_cast<float>((static_cast<double>(related_170->x_ec)-x_ec)*facing_104));field_740+=1.0;
  switch(g_aya_action_match){case 3:MOTION->set_oriented_components(field_73c,1.5f);break;case 2:MOTION->set_oriented_components(field_73c,1.0f);break;case 1:case 0:MOTION->set_oriented_components(field_73c,0.75f);break;}
  if(!(word_732%20)){float packet[3];JITTER_ANGLE(packet,0);packet[1]=URAND(30)+60.0;packet[2]=6.0f;ORBIT_SPAWN(packet,1680.0,100,50.0);}
  switch(g_aya_action_match){
  case 3:
   if(!(word_732%180)){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,0);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   if(word_732%180==90){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,1);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   break;
  case 2:
   if(!(word_732%360)){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,0);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   if(word_732%360==180){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,1);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   break;
  }
  if(word_734<=0){word_734=10;dispatch_character_wave_handle(22);float packet[3];packet[1]=URAND(30)+120.0;packet[2]=3.0f;
   if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
  }
  if(!word_736){word_738-=10;if(word_738<5)word_738=5;word_736=word_738;float packet[3];packet[1]=static_cast<double>(word_738)+static_cast<double>(word_738)+100.0;if(packet[1]>=180.0)packet[1]=180.0f;packet[2]=2.0f;
   if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
  }
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){word_734=60;word_736=60;word_738=60;field_740=0.0;float packet[3]={0.0f,0.0f,0.0f};spawn(903,x_ec,y_f0,facing_104,1,packet,3);packet[2]=4.0f;spawn(903,x_ec,y_f0+100.0,facing_104,1,packet,3);packet[2]=5.0f;spawn(903,x_ec,y_f0+100.0,facing_104,1,packet,3);facing_104=-1;dispatch_character_wave_handle(21);}return;
}

case 770:{ADVANCE_TO(700);if(FRAME(0,7)){byte_655=1;finalize(-1);texture(2,-1);copy_action_word();word_76c=0;word_76a=1;word_766=0;word_768=0;word_764=0;event(23);}return;}

case 791:{advance();if(FRAME(0,5))spawn(990,x_ec,y_f0,facing_104,1,0,0);if(ENTRY(1))facing_104=related_170->facing_104;if(ENTRY(2)){float packet[3]={0.0f,0.0f,0.0f};spawn(997,x_ec,y_f0,facing_104,1,packet,3);for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}dispatch_character_wave_handle(5);}return;}

case 795:{if(!sequence_index_13e){velocity_y_f8-=static_cast<double>(0.3f);if(static_cast<unsigned char>(crossed())){event(30);select_sequence(1);y_f0=aya_surface(this);zero_motion();return;}}ADVANCE_TO(700);return;}

case 797:{
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){
  x_ec=480.0;layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};
  spawn(821,x_ec,y_f0,facing_104,1,packet,3);dispatch_character_wave_handle(15);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}
  select_sequence(2);y_f0=aya_surface(this);zero_motion();return;
 }ADVANCE_TO(0);return;
}

case 798:{
 if(static_cast<unsigned char>(crossed())&&sequence_index_13e<2){
  x_ec=800.0;layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};
  spawn(821,x_ec,y_f0,facing_104,1,packet,3);dispatch_character_wave_handle(15);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;if(packet[0]>=0.0f&&packet[0]<=180.0f)spawn(821,x_ec,y_f0,facing_104,1,packet,3);else spawn(821,x_ec,y_f0,facing_104,-1,packet,3);}
  select_sequence(2);y_f0=aya_surface(this);zero_motion();return;
 }ADVANCE_TO(700);return;
}

default:common_update();return;
}
    advance();
}

typedef char Aya_off_ec[(offsetof(AyaActionStateView, x_ec) == 0xec) ? 1 : -1];
typedef char Aya_off_104[(offsetof(AyaActionStateView, facing_104) == 0x104) ? 1 : -1];
typedef char Aya_off_12c[(offsetof(AyaActionStateView, field_12c) == 0x12c) ? 1 : -1];
typedef char Aya_off_13c[(offsetof(AyaActionStateView, action_id_13c) == 0x13c) ? 1 : -1];
typedef char Aya_off_168[(offsetof(AyaActionStateView, emitter_168) == 0x168) ? 1 : -1];
typedef char Aya_off_170[(offsetof(AyaActionStateView, related_170) == 0x170) ? 1 : -1];
typedef char Aya_off_17c[(offsetof(AyaActionStateView, byte_17c) == 0x17c) ? 1 : -1];
typedef char Aya_off_180[(offsetof(AyaActionStateView, state_180) == 0x180) ? 1 : -1];
typedef char Aya_off_186[(offsetof(AyaActionStateView, word_186) == 0x186) ? 1 : -1];
typedef char Aya_off_47e[(offsetof(AyaActionStateView, byte_47e) == 0x47e) ? 1 : -1];
typedef char Aya_off_482[(offsetof(AyaActionStateView, word_482) == 0x482) ? 1 : -1];
typedef char Aya_off_48a[(offsetof(AyaActionStateView, word_48a) == 0x48a) ? 1 : -1];
typedef char Aya_off_4a8[(offsetof(AyaActionStateView, word_4a8) == 0x4a8) ? 1 : -1];
typedef char Aya_off_4ae[(offsetof(AyaActionStateView, word_4ae) == 0x4ae) ? 1 : -1];
typedef char Aya_off_4b8[(offsetof(AyaActionStateView, field_4b8) == 0x4b8) ? 1 : -1];
typedef char Aya_off_606[(offsetof(AyaActionStateView, sbyte_606) == 0x606) ? 1 : -1];
typedef char Aya_off_60e[(offsetof(AyaActionStateView, sbyte_60e) == 0x60e) ? 1 : -1];
typedef char Aya_off_655[(offsetof(AyaActionStateView, byte_655) == 0x655) ? 1 : -1];
typedef char Aya_off_6b4[(offsetof(AyaActionStateView, field_6b4) == 0x6b4) ? 1 : -1];
typedef char Aya_off_72c[(offsetof(AyaActionStateView, byte_72c) == 0x72c) ? 1 : -1];
typedef char Aya_off_730[(offsetof(AyaActionStateView, word_730) == 0x730) ? 1 : -1];
typedef char Aya_off_73c[(offsetof(AyaActionStateView, field_73c) == 0x73c) ? 1 : -1];
typedef char Aya_off_74c[(offsetof(AyaActionStateView, field_74c) == 0x74c) ? 1 : -1];
typedef char Aya_off_750[(offsetof(AyaActionStateView, byte_750) == 0x750) ? 1 : -1];
typedef char Aya_off_764[(offsetof(AyaActionStateView, word_764) == 0x764) ? 1 : -1];
typedef char Aya_off_7a0[(offsetof(AyaActionStateView, word_7a0) == 0x7a0) ? 1 : -1];
typedef char AyaPeer_off_ec[(offsetof(AyaPeerView, x_ec) == 0xec) ? 1 : -1];
typedef char AyaPeer_off_104[(offsetof(AyaPeerView, facing_104) == 0x104) ? 1 : -1];
typedef char AyaPeer_off_48c[(offsetof(AyaPeerView, word_48c) == 0x48c) ? 1 : -1];
}
