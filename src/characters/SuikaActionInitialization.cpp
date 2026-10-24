// JP1.06a5AD4A0: complete target-reviewed source; whole function remains nonexact.
#include "SuikaActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void SuikaActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=5.5f;return;
 case 5:F(0xf4)=-5.5f;return;
 case 214:
  S(0x736)=0;F(0xf4)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=72.0f;F(0x73c)=9.0f;F(0x74c)=0;return;
 case 300:case 301:
  B(0x750)=1;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 303:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=9.0f;B(0x184)=2;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:B(0x184)=1;I(0x180)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 308:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 309:
  B(0x184)=1;I(0x180)=0;
  if(F(0xf4)>8.0f)F(0xf4)=8.0f;
  if(F(0xf4)<-8.0f)F(0xf4)=-8.0f;
  B(0x750)=1;return;
 case 310:F(0xf4)=0;S(0x730)=0;F(0xf8)=0;I(0x180)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 321:case 322:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 330:B(0x184)=1;I(0x180)=0;F(0xf4)*=0.5;F(0xf8)=6.0f;return;
 case 331:zero_motion();B(0x184)=6;I(0x180)=0;return;
 case 400:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;B(0x750)=1;return;
 case 401:I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 402:B(0x184)=1;I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 404:case 405:case 406:
  I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x734)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=10.0f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=3;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 410:case 411:case 412:I(0x180)=0;zero_motion();S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 414:case 415:case 416:
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 418:F(0xf4)=17.5f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 500:case 501:
  B(0x750)=1;B(0x17c)=0;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;S(0x732)=0;B(0x184)=1;return;
 case 505:case 506:case 507:case 508:
  B(0x17c)=4;B(0x750)=1;zero_motion();B(0x184)=0;B(0x47e)=0;S(0x730)=0;S(0x732)=0;I(0x180)=1;return;
 case 520:case 521:case 522:case 523:
  B(0x17c)=1;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 525:case 526:B(0x17c)=5;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 530:case 531:B(0x17c)=9;zero_motion();B(0x184)=0;B(0x47e)=0;I(0x180)=1;return;
 case 540:case 541:
  B(0x17c)=2;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 542:I(0x180)=0;B(0x750)=0;B(0x17c)=2;B(0x184)=1;return;
 case 545:case 546:S(0x730)=0;B(0x17c)=6;I(0x180)=0;zero_motion();B(0x750)=0;return;
 case 560:case 561:B(0x17c)=3;I(0x180)=1;zero_motion();B(0x750)=1;return;
 case 565:case 566:
  B(0x17c)=7;I(0x180)=1;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 567:
  B(0x17c)=7;I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;
  F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 599:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 600:case 650:I(0x180)=1;zero_motion();S(0x730)=0;return;
 case 601:case 604:B(0x184)=1;I(0x180)=0;zero_motion();return;
 case 602:S(0x730)=0;I(0x180)=0;F(0x73c)=1;B(0x184)=1;zero_motion();return;
 case 603:S(0x730)=0;S(0x732)=0;I(0x180)=0;B(0x184)=1;zero_motion();return;
 case 605:case 730:S(0x730)=0;I(0x180)=0;F(0x73c)=2;B(0x184)=1;zero_motion();return;
 case 606:zero_motion();I(0x180)=0;B(0x47e)=0;return;
 case 607:zero_motion();B(0x47e)=0;S(0x730)=0;return;
 case 608:S(0x730)=0;S(0x732)=0;B(0x184)=0;I(0x180)=0;zero_motion();return;
 case 610:case 611:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 612:case 615:
  I(0x180)=1;zero_motion();S(0x738)=0;S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 700:return;
 case 701:case 702:case 703:if(B(0x47e)==0)zero_motion();return;
 case 704:case 707:case 710:case 711:case 720:zero_motion();return;
 case 705:F(0xf4)=6.0f;return;
 case 706:F(0xf4)=-6.0f;return;
 case 708:S(0x730)=0;F(0xf4)=0;return;
 case 709:S(0x730)=0;return;
 case 740:
  F(0x73c)=0;S(0x730)=0;F(0x740)=0;S(0x732)=0;S(0x734)=0;F(0x748)=0;B(0x184)=0;I(0x180)=0;zero_motion();return;
 case 751:zero_motion();F(0x73c)=0;B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x730)=0;S(0x732)=0;return;
 case 795:F(0x73c)=200.0f;S(0x734)=0;dispatch_character_wave_handle(19);return;
 case 797:case 798: {
  float payload[3];
  F(0xf8)=3.0f;S(0x734)=0;F(0x100)=0.1f;dispatch_character_wave_handle(19);
  for(float index=0;index<8.0f;index+=1.0f) {
   payload[0]=static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(40)))+(index*45.0-20.0));
   payload[1]=static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(12)))+16.0);
   payload[2]=0;
   spawn_owned_object(999,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1,payload,3);
  }
  return;
 }
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
