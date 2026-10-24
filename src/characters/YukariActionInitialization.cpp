// JP1.06a58A4F0: complete target-reviewed action initialization.
#include "YukariActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
#define DIR static_cast<unsigned char>(C(0x104))
void YukariActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=4.5f;return;
 case 5:F(0xf4)=-4.5f;return;
 case 70:
  S(0x730)=0;F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;
  if(F(0xf4)>0.0f)S(0x730)=1;
  if(F(0xf4)<0.0f)S(0x730)=-1;
  F(0x12c)=0;return;
 case 71:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.5f;S(0x730)=7;F(0x12c)=0;return;
 case 72:F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=1.3f;F(0x12c)=0;return;
 case 73:case 88:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;S(0x730)=7;F(0x12c)=0;return;
 case 74:case 75:F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;F(0x12c)=0;return;
 case 76:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  ++S(0x730);S(0x186)=5;S(0x7a0)=0;S(0x7a2)=85;
  emit_effect(38,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  emit_effect(59,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  F(0x108)=S(0x7a0);F(0x10c)=S(0x7a2);F(0xf4)=0;F(0xf8)=0;F(0x100)=0;
  publish_layout_scalar(6.0f);dispatch_event(22);F(0x12c)=0;return;
 case 77:
  S(0x7a0)=0;F(0xf4)=-F(0x18c);S(0x7a2)=85;F(0xf8)=F(0x190);F(0x100)=0.8f;
  F(0x108)=0;F(0x10c)=85.0f;F(0x12c)=0;return;
 case 78:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  ++S(0x730);F(0xf4)=0;F(0xf8)=0;F(0x100)=0;publish_layout_scalar(4.0f);dispatch_event(22);
  emit_effect(38,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  emit_effect(59,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  F(0x12c)=0;return;
 case 89:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  if(S(0x7a4)==0) {S(0x7a4)=1;spawn_owned_object(999,F(0xec),F(0xf0),DIR,1,0,0);}
  emit_effect(58,F(0xec),0,DIR,-1);F(0x12c)=0;return;
 case 145:F(0xf4)=-10.0f;F(0xf8)=14.0f;F(0x100)=0.5f;S(0x730)=7;F(0x12c)=0;return;
 case 214:
  reinterpret_cast<YukariEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;F(0xf8)=0;S(0x736)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=115.0f;F(0x73c)=10.0f;F(0x74c)=0;return;
 case 300:
  if(S(0x142)==0 && S(0x140)==0) {
   if(B(0x47e)==0)zero_motion();
   B(0x184)=1;I(0x180)=0;
  }
  if(B(0x47e)!=0) {
   F(0xf4)=static_cast<float>(F(0xf4)-0.5);
   if(F(0xf4)<0) {F(0xf4)=0;B(0x47e)=0;}
  }
  if(advance_frame_and_dispatch())set_action(0);
  if(S(0x142)==0 && S(0x140)==3) {dispatch_event(27);B(0x47e)=0;}
  return;
 case 301:case 303:case 320:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:
  F(0xf8)=0;F(0x100)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x47e)=0;B(0x750)=1;return;
 case 305:F(0xf4)=10.0f;I(0x180)=0;B(0x47e)=0;S(0x738)=0;B(0x184)=1;return;
 case 306:case 307:case 309:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 308:B(0x184)=1;I(0x180)=0;zero_motion();return;
 case 310:
  F(0xf4)=15.0f;S(0x730)=0;F(0x100)=0.5f;I(0x180)=0;F(0x108)=0;B(0x184)=3;F(0x10c)=105.0f;return;
 case 321:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 322:zero_motion();B(0x184)=1;I(0x180)=0;return;
 case 400:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;B(0x750)=1;return;
 case 401:case 410:case 411:case 412:
  I(0x180)=0;zero_motion();S(0x738)=0;S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 402:
  I(0x180)=0;zero_motion();F(0x740)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 404:
  F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;
  S(0x738)=0;S(0x736)=0;S(0x734)=0;S(0x732)=0;S(0x730)=0;I(0x180)=0;B(0x750)=1;return;
 case 406:
  F(0x740)=0;F(0x100)=0;F(0xf4)*=0.1f;F(0xf8)*=0.1f;
  S(0x738)=0;S(0x736)=0;S(0x734)=0;S(0x732)=0;S(0x730)=0;I(0x180)=0;B(0x750)=1;return;
 case 408:case 418:
  F(0xf4)=12.5f;F(0xf8)=0;F(0x100)=0;B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 414:case 415:case 416:
  I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;
  S(0x738)=0;S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 500:case 501:case 502:case 503:B(0x17c)=0;I(0x180)=1;zero_motion();B(0x750)=1;return;
 case 505:case 506:
  B(0x17c)=4;I(0x180)=1;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 510:case 511:
  B(0x17c)=8;I(0x180)=1;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 520:case 521:
  B(0x17c)=1;S(0x730)=0;B(0x184)=4;I(0x180)=0;zero_motion();
  if(S(0x13c)==520 && C(0x605)>=4)S(0x4a8)=2;return;
 case 522:case 523:
  B(0x17c)=1;I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;return;
 case 525:case 526:
  B(0x17c)=5;S(0x730)=0;B(0x184)=0;I(0x180)=1;zero_motion();B(0x750)=1;return;
 case 540:case 541:case 542:case 543:B(0x17c)=2;zero_motion();I(0x180)=1;B(0x47e)=0;return;
 case 545:case 546:B(0x17c)=6;zero_motion();B(0x184)=1;I(0x180)=1;B(0x47e)=0;return;
 case 547:case 548:B(0x17c)=6;zero_motion();I(0x180)=1;B(0x47e)=0;return;
 case 560:case 561:
  B(0x17c)=3;zero_motion();F(0x740)=0;B(0x184)=0;I(0x180)=0;S(0x730)=0;return;
 case 562:case 563:
  B(0x17c)=3;zero_motion();F(0x740)=0;B(0x184)=0;I(0x180)=0;S(0x730)=0;return;
 case 565:
  B(0x17c)=7;zero_motion();B(0x47e)=0;B(0x184)=1;I(0x180)=0;S(0x730)=0;B(0x750)=1;return;
 case 566:
  B(0x17c)=7;zero_motion();B(0x47e)=0;B(0x184)=10;I(0x180)=0;S(0x730)=0;B(0x750)=1;return;
 case 600:case 601:case 602:case 603:I(0x180)=1;zero_motion();return;
 case 604:case 605:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 606:case 656:F(0x73c)=0;S(0x730)=0;S(0x738)=0;I(0x180)=0;zero_motion();return;
 case 607:case 740:case 741:case 750:
  I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;return;
 case 615:zero_motion();I(0x180)=0;return;
 case 700:case 701:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();F(0x100)=0.25f;return;
 case 708:S(0x730)=0;S(0x732)=0;S(0x734)=0;I(0x180)=1;zero_motion();return;
 case 710:S(0x730)=0;S(0x732)=0;S(0x734)=0;zero_motion();return;
 case 720:zero_motion();S(0x730)=0;S(0x738)=0;I(0x180)=0;B(0x184)=1;return;
 case 721:zero_motion();S(0x730)=0;B(0x47e)=0;I(0x180)=0;B(0x184)=10;return;
 case 730:S(0x730)=0;S(0x738)=0;I(0x180)=0;return;
 case 797: {
  float payload[3];
  zero_motion();payload[0]=0;payload[1]=0;payload[2]=0;S(0x730)=0;
  spawn_owned_object(899,360.0f,100.0f,DIR,-1,payload,3);dispatch_character_wave_handle(1);return;
 }
 case 798: {
  float payload[3];
  zero_motion();payload[0]=0;payload[1]=0;payload[2]=0;S(0x730)=0;
  spawn_owned_object(899,920.0f,100.0f,DIR,-1,payload,3);dispatch_character_wave_handle(1);return;
 }
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef C
#undef I
#undef DIR
}
