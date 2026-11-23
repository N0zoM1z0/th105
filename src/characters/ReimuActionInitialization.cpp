// JP 1.06a Reimu action initializer at 0x491C40. The 404/414 shared tail still differs.
#include "ReimuActionInitialization.hpp"
namespace th105 {
#define FIELD(type,offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(offset)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
void ReimuFinalizationView::initialize_action_entry()
{
 switch (action_id_13c) {
 case 4:velocity_x_f4=4.5f;return;
 case 5:velocity_x_f4=-4.5f;return;
 case 70:
  S(0x730)=0;velocity_x_f4=-F(0x18c);velocity_y_f8=F(0x190);acceleration_y_100=0.8f;
  if(velocity_x_f4>0.0f)S(0x730)=1;
  if(velocity_x_f4<0.0f)S(0x730)=-1;
  F(0x12c)=0;return;
 case 71:
  velocity_x_f4=-F(0x18c);velocity_y_f8=F(0x190);acceleration_y_100=0.5f;
  S(0x730)=7;F(0x12c)=0;return;
 case 72:
  velocity_x_f4=-F(0x18c);velocity_y_f8=F(0x190);acceleration_y_100=1.3f;F(0x12c)=0;return;
 case 73:case 88:
  velocity_x_f4=-F(0x18c);velocity_y_f8=F(0x190);acceleration_y_100=0.8f;
  S(0x730)=7;F(0x12c)=0;return;
 case 74:case 75:
  velocity_x_f4=-F(0x18c);velocity_y_f8=F(0x190);acceleration_y_100=0.8f;F(0x12c)=0;return;
 case 76:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  ++S(0x730);S(0x186)=5;S(0x7a0)=0;S(0x7a2)=85;
  emit_effect(38,static_cast<float>(x_ec-facing_104*50),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  emit_effect(59,static_cast<float>(x_ec-facing_104*50),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  F(0x108)=S(0x7a0);F(0x10c)=S(0x7a2);
  acceleration_y_100=velocity_y_f8=velocity_x_f4=0;
  publish_layout_scalar(6.0f);dispatch_event(22);F(0x12c)=0;return;
 case 77:
  S(0x7a0)=0;velocity_x_f4=-F(0x18c);S(0x7a2)=85;
  velocity_y_f8=F(0x190);acceleration_y_100=0.8f;F(0x108)=0;F(0x10c)=85.0f;F(0x12c)=0;return;
 case 78:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  ++S(0x730);acceleration_y_100=velocity_y_f8=velocity_x_f4=0;
  publish_layout_scalar(4.0f);dispatch_event(22);
  emit_effect(38,static_cast<float>(x_ec-facing_104*50),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  emit_effect(59,static_cast<float>(x_ec-facing_104*50),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  F(0x12c)=0;return;
 case 89:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  if(S(0x7a4)==0) {S(0x7a4)=1;spawn_owned_object(951,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,0,0);}
  emit_effect(58,x_ec,0,static_cast<unsigned char>(facing_104),-1);F(0x12c)=0;return;
 case 145:
  velocity_x_f4=-10.0f;velocity_y_f8=14.0f;acceleration_y_100=0.5f;S(0x730)=7;F(0x12c)=0;return;
 case 214:
  velocity_x_f4=0;S(0x736)=0;velocity_y_f8=0;acceleration_y_100=0.6f;F(0x108)=0;
  F(0x10c)=95.0f;F(0x73c)=10.0f;F(0x74c)=0;return;
 case 300:
  if(B(0x47e)==0)zero_motion();
  I(0x180)=0;S(0x7cc)=0;B(0x184)=1;return;
 case 301:case 320:
  if(B(0x47e)==0)zero_motion();
  I(0x180)=0;S(0x7cc)=0;B(0x184)=1;return;
 case 302:
  if(B(0x47e)==0)zero_motion();
  B(0x750)=1;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 303:
  if(B(0x47e)==0)zero_motion();
  I(0x180)=0;S(0x7cc)=0;B(0x184)=6;return;
 case 304:
  zero_motion();B(0x750)=1;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 305:
  velocity_x_f4=15.0f;S(0x738)=0;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 307:
  zero_motion();
 case 306:
  S(0x730)=0;I(0x180)=0;S(0x7cc)=0;B(0x184)=1;return;
 case 308:case 309:
  I(0x180)=0;S(0x7cc)=0;B(0x184)=1;return;
 case 310:
  velocity_x_f4=15.0f;S(0x730)=0;acceleration_y_100=0.5f;I(0x180)=0;
  S(0x7cc)=0;F(0x108)=0;B(0x184)=3;F(0x10c)=105.0f;return;
 case 322:
  if (B(0x47e) == 0) {
   zero_motion();
   S(0x738) = 0;
   B(0x184) = 1;
   B(0x47e) = 0;
   I(0x180) = 0;
   S(0x7cc) = 0;
   return;
  }
  S(0x738) = 0;
  B(0x184) = 1;
  B(0x47e) = 0;
  I(0x180) = 0;
  S(0x7cc) = 0;
  return;
 case 400:case 401:case 410:case 412:
  I(0x180)=0;zero_motion();S(0x736)=S(0x732)=S(0x730)=S(0x738)=0;
  B(0x750)=1;S(0x7cc)=1;return;
 case 402:
  I(0x180)=0;zero_motion();S(0x738)=S(0x736)=S(0x732)=S(0x730)=0;S(0x7cc)=1;return;
 case 404:
 case 406:
  acceleration_y_100 = 0;
  S(0x734) = 0;
  I(0x180) = 0;
  velocity_x_f4 *= 0.2f;
  velocity_y_f8 *= 0.2f;
  S(0x736) = S(0x732) = S(0x730) = S(0x738) = 0;
  B(0x750) = 1;
  S(0x7cc) = 1;
  return;
 case 408:
  velocity_x_f4 = 14.0f;
  acceleration_y_100 = velocity_y_f8 = 0;
  // Fall through to the shared flag reset.
 case 321:
  B(0x184) = 1;
  B(0x47e) = 0;
  I(0x180) = 0;
  S(0x7cc) = 0;
  return;
 case 414:
 case 416:
  I(0x180) = 0;
  velocity_x_f4 *= 0.25;
  velocity_y_f8 *= 0.25;
  S(0x736) = S(0x732) = S(0x730) = S(0x738) = 0;
  B(0x750) = 1;
  S(0x7cc) = 1;
  return;
 case 418:
  velocity_x_f4=8.5f;acceleration_y_100=velocity_y_f8=0;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 500:case 501:
  B(0x17c)=0;I(0x180)=0;zero_motion();S(0x736)=S(0x732)=S(0x730)=0;B(0x750)=1;S(0x7cc)=1;return;
 case 502:case 503:case 512:case 513:
  B(0x17c)=0;I(0x180)=0;velocity_x_f4*=0.25;velocity_y_f8*=0.25;
  S(0x736)=S(0x732)=S(0x730)=0;B(0x750)=1;S(0x7cc)=1;return;
 case 505:case 506:
  B(0x17c)=4;I(0x180)=0;zero_motion();S(0x736)=S(0x732)=S(0x730)=0;B(0x750)=1;S(0x7cc)=1;return;
 case 507:case 508:
  B(0x17c)=4;I(0x180)=0;velocity_x_f4*=0.25;velocity_y_f8*=0.25;
  S(0x736)=S(0x732)=S(0x730)=0;B(0x750)=1;S(0x7cc)=1;return;
 case 510:case 511:
  B(0x17c)=8;I(0x180)=0;zero_motion();S(0x736)=S(0x732)=S(0x730)=0;B(0x750)=1;S(0x7cc)=1;return;
 case 520:case 521:
  B(0x17c)=1;I(0x180)=0;zero_motion();S(0x7cc)=1;return;
 case 522:case 523:
  B(0x17c)=1;I(0x180)=0;S(0x7cc)=1;velocity_x_f4*=0.25;velocity_y_f8*=0.25;return;
 case 525:case 526:
  B(0x17c)=5;S(0x738)=S(0x732)=S(0x730)=0;I(0x180)=0;zero_motion();S(0x7cc)=1;return;
 case 530:case 531:
  B(0x17c)=9;I(0x180)=0;zero_motion();S(0x7cc)=1;return;
 case 540:
  B(0x17c)=2;zero_motion();B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 541:
  B(0x17c)=2;zero_motion();B(0x184)=99;S(0x734)=S(0x730)=0;
  B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 545:case 546:
  B(0x17c)=6;zero_motion();B(0x184)=1;I(0x180)=1;B(0x47e)=0;S(0x7cc)=1;return;
 case 550:case 551:
  B(0x17c)=10;zero_motion();B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x7cc)=1;return;
 case 560:case 561:
  velocity_y_f8=velocity_x_f4=0;B(0x17c)=3;acceleration_y_100=0;B(0x184)=1;I(0x180)=0;S(0x7cc)=0;
  if(C(0x607)>=4)S(0x4ac)=S(0x4a8)=15;return;
 case 565:case 566:
  velocity_y_f8=velocity_x_f4=0;S(0x732)=S(0x730)=0;acceleration_y_100=0;B(0x47e)=0;I(0x180)=0;
  S(0x7cc)=0;B(0x17c)=7;B(0x184)=1;B(0x750)=1;return;
 case 600:case 601:case 602:case 604:case 605:case 606:
  S(0x732)=S(0x730)=0;I(0x180)=1;zero_motion();S(0x7cc)=1;return;
 case 608:case 658:
  S(0x732)=S(0x730)=S(0x734)=0;I(0x180)=1;zero_motion();S(0x7cc)=1;return;
 case 609:
  S(0x738)=S(0x732)=S(0x730)=0;I(0x180)=1;zero_motion();
  dispatch_sequence_window(0,2,60);advance_secondary_event_effect_cycle();S(0x48a)=40;dispatch_event(23);
  emit_effect(115,static_cast<float>(facing_104*24+x_ec),static_cast<float>(y_f0+144.0),static_cast<unsigned char>(facing_104),1);
  S(0x7cc)=1;return;
 case 610:
  S(0x732)=S(0x730)=0;I(0x180)=1;zero_motion();
  dispatch_sequence_window(0,4,60);advance_secondary_event_effect_cycle();S(0x48a)=40;dispatch_event(23);
  emit_effect(115,static_cast<float>(facing_104*24+x_ec),static_cast<float>(y_f0+144.0),static_cast<unsigned char>(facing_104),1);
  S(0x7cc)=1;return;
 case 612:
  zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=5;S(0x7cc)=1;return;
 case 614:
  velocity_y_f8=velocity_x_f4=0;S(0x730)=0;I(0x180)=0;acceleration_y_100=0;S(0x7cc)=0;return;
 case 616:
  zero_motion();F(0x73c)=0;I(0x180)=0;B(0x184)=5;B(0x47e)=0;S(0x7cc)=1;return;
 case 619:
  zero_motion();F(0x73c)=0;S(0x7ca)=S(0x7c8)=0;B(0x47e)=0;I(0x180)=0;S(0x7cc)=0;return;
 case 650:case 651:
  S(0x732)=S(0x730)=0;I(0x180)=1;zero_motion();S(0x7cc)=1;acceleration_y_100=0.25f;return;
 case 669:
  S(0x734)=0;F(0x73c)=0;S(0x732)=S(0x730)=0;I(0x180)=1;zero_motion();S(0x7cc)=1;return;
 case 695:
  B(0x184)=1;I(0x180)=0;zero_motion();dispatch_sequence_window(0,1,60);S(0x7cc)=0;return;
 case 696:
  B(0x184)=1;I(0x180)=0;B(0x47e)=0;zero_motion();
  emit_effect(69,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
  S(0x48a)=15;dispatch_sequence_window(0,1,60);S(0x7cc)=0;return;
 case 710:case 711:case 720:case 721:case 730:case 731:case 740:
  zero_motion();
 case 797:S(0x730)=0;return;
 case 760:
  zero_motion();S(0x730)=0;finalize_sequence_entry(-1);B(0x655)=1;
  publish_texture_state(6,-1);copy_action_word_176_to_174();dispatch_event(23);return;
 case 798:
  zero_motion();velocity_x_f4=12.0f;S(0x730)=0;velocity_y_f8=0;acceleration_y_100=0.5f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef F
#undef S
#undef B
#undef C
#undef I
#undef FIELD
}
