// JP1.06a51D650: complete target-reviewed action initialization.
#include "PatchouliActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
#define DIR static_cast<unsigned char>(C(0x104))
void PatchouliActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=4.0f;return;
 case 5:F(0xf4)=-4.0f;return;
 case 197:F(0xf4)=11.0f;return;
 case 198:F(0xf4)=-11.0f;return;
 case 214:
  reinterpret_cast<PatchouliEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x73c)=9.0f;F(0x74c)=0;return;
 case 300:case 301:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x750)=1;return;
 case 302:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 303:case 321:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:B(0x47e)=0;F(0xf4)=10.0f;I(0x180)=0;B(0x184)=1;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=3;return;
 case 307:
  B(0x184)=1;I(0x180)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;B(0x750)=1;F(0x100)=0;return;
 case 308:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 309:B(0x184)=0;I(0x180)=0;B(0x750)=1;return;
 case 310:
  F(0xf4)=0;S(0x730)=0;F(0xf8)=0;I(0x180)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 320:S(0x730)=0;zero_motion();B(0x47e)=0;I(0x180)=0;B(0x184)=3;return;
 case 400:case 401:case 402:case 407:
  I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 404:case 406:case 409:case 415:
  I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;
  F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:
  F(0xf8)=0;S(0x730)=0;B(0x47e)=0;F(0xf4)=10.0f;I(0x180)=0;B(0x184)=3;F(0x100)=0;return;
 case 410:
  I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 411:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;B(0x750)=1;return;
 case 412:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 414:
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;
  S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 416:I(0x180)=0;S(0x738)=0;B(0x184)=1;return;
 case 418:F(0xf4)=8.5f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 500:case 501:case 502:case 503:
  B(0x750)=1;B(0x17c)=0;zero_motion();B(0x47e)=0;I(0x180)=1;return;
 case 505:case 506:
  B(0x17c)=5;B(0x750)=1;zero_motion();B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 520:case 521:
  B(0x17c)=1;zero_motion();B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 525:case 526:
  B(0x17c)=6;zero_motion();B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 540:case 541:
  B(0x17c)=2;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 542:I(0x180)=0;B(0x750)=0;B(0x17c)=2;B(0x184)=1;return;
 case 545:case 546:B(0x17c)=6;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 560:case 561:
  B(0x17c)=3;I(0x180)=0;zero_motion();S(0x730)=0;F(0x744)=0;S(0x732)=0;B(0x750)=1;return;
 case 565:case 566:B(0x17c)=8;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 567:case 568:B(0x17c)=8;I(0x180)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 580:case 581:
  B(0x17c)=4;I(0x180)=1;zero_motion();S(0x730)=0;F(0x744)=0;S(0x732)=0;B(0x750)=1;return;
 case 585:case 586:B(0x17c)=10;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 600:case 604:I(0x180)=0;zero_motion();return;
 case 601:case 651:S(0x730)=0;F(0x73c)=10.0f;S(0x732)=0;I(0x180)=0;zero_motion();return;
 case 602:S(0x730)=0;I(0x180)=0;B(0x184)=99;zero_motion();return;
 case 603:S(0x730)=0;S(0x732)=0;I(0x180)=0;zero_motion();return;
 case 605:case 606:zero_motion();I(0x180)=0;B(0x47e)=0;return;
 case 607:zero_motion();B(0x47e)=0;return;
 case 610:I(0x180)=1;zero_motion();return;
 case 612:case 615:
  I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 690: {
  emit_effect(71,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;
  S(0x738)=reinterpret_cast<PatchouliEntryCardDeque *>(reinterpret_cast<unsigned char *>(this)+0x55c)->at(0).code;
  I(0x180)=1;zero_motion();
  const int card=S(0x738);
  switch(card) {
  case 100:
   if(++C(0x624)==0)C(0x624)=1;if(C(0x624)>=5)C(0x624)=4;C(0x629)=-1;C(0x62e)=-1;break;
  case 101:
   if(++C(0x625)==0)C(0x625)=1;if(C(0x625)>=5)C(0x625)=4;C(0x62a)=-1;C(0x62f)=-1;break;
  case 102:
   if(++C(0x626)==0)C(0x626)=1;if(C(0x626)>=5)C(0x626)=4;C(0x62b)=-1;C(0x630)=-1;break;
  case 103:
   if(++C(0x627)==0)C(0x627)=1;if(C(0x627)>=5)C(0x627)=4;C(0x62c)=-1;C(0x631)=-1;break;
  case 104:
   if(++C(0x628)==0)C(0x628)=1;if(C(0x628)>=5)C(0x628)=4;C(0x632)=-1;C(0x62d)=-1;break;
  case 105:
   if(++C(0x629)==0)C(0x629)=1;if(C(0x629)>=5)C(0x629)=4;C(0x624)=-1;C(0x62e)=-1;break;
  case 106:
   if(++C(0x62a)==0)C(0x62a)=1;if(C(0x62a)>=5)C(0x62a)=4;C(0x625)=-1;C(0x62f)=-1;break;
  case 107:
   if(++C(0x62b)==0)C(0x62b)=1;if(C(0x62b)>=5)C(0x62b)=4;C(0x626)=-1;C(0x630)=-1;break;
  case 108:
   if(++C(0x62c)==0)C(0x62c)=1;if(C(0x62c)>=5)C(0x62c)=4;C(0x627)=-1;C(0x631)=-1;break;
  case 109:
   if(++C(0x62d)==0)C(0x62d)=1;if(C(0x62d)>=5)C(0x62d)=4;C(0x628)=-1;C(0x632)=-1;break;
  case 110:
   if(++C(0x62e)==0)C(0x62e)=1;if(C(0x62e)>=5)C(0x62e)=4;C(0x624)=-1;C(0x629)=-1;break;
  case 111:
   if(++C(0x62f)==0)C(0x62f)=1;if(C(0x62f)>=5)C(0x62f)=4;C(0x625)=-1;C(0x62a)=-1;break;
  case 112:
   if(++C(0x630)==0)C(0x630)=1;if(C(0x630)>=5)C(0x630)=4;C(0x626)=-1;C(0x62b)=-1;break;
  case 113:
   if(++C(0x631)==0)C(0x631)=1;if(C(0x631)>=5)C(0x631)=4;C(0x627)=-1;C(0x62c)=-1;break;
  case 114:
   if(++C(0x632)==0)C(0x632)=1;if(C(0x632)>=5)C(0x632)=4;C(0x628)=-1;C(0x62d)=-1;break;
  }
  emit_effect(static_cast<short>(C(0x5c0+card)+130),F(0xec),F(0xf0),1,1);
  dispatch_sequence_window(0,1,60);return;
 }
 case 700:return;
 case 701:case 702:case 703:if(B(0x47e)==0)zero_motion();return;
 case 704:case 707:zero_motion();return;
 case 705:F(0xf4)=6.0f;return;
 case 706:F(0xf4)=-6.0f;return;
 case 708:F(0xf4)=0;S(0x730)=0;return;
 case 709:S(0x730)=0;return;
 case 710:zero_motion();F(0x740)=0;return;
 case 720: {const double y=F(0xf0);if(stage_surface_height_at_x(this)>=y)zero_motion();return;}
 case 721: {const double y=F(0xf0);if(stage_surface_height_at_x(this)>=y)zero_motion();return;}
 case 730:
  zero_motion();B(0x655)=1;finalize_sequence_entry(-1);publish_texture_state(2,-1);copy_action_word_176_to_174();
  S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;dispatch_event(23);return;
 case 797:zero_motion();F(0x100)=0.4f;S(0x730)=0;return;
 case 798:zero_motion();F(0x100)=0.4f;S(0x730)=0;return;
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
