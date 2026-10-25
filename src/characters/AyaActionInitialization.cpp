// JP1.06a617000: complete action initializer, independently reviewed.
#include "AyaActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void AyaActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=5.5f;return;
 case 5:F(0xf4)=-5.5f;return;
 case 214:
  reinterpret_cast<AyaEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=12.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 320:case 321:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;F(0xf4)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;F(0xf4)=17.5f;F(0x100)=0;B(0x184)=1;B(0x47e)=0;I(0x180)=0;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:F(0xf4)=0;S(0x730)=0;F(0xf8)=0;I(0x180)=0;F(0x100)=0;B(0x184)=1;F(0x73c)=25.0f;return;
 case 308:B(0x184)=1;F(0xf4)=0;I(0x180)=0;F(0xf8)=0;return;
 case 309:B(0x184)=1;I(0x180)=0;return;
 case 310:F(0xf4)=0;S(0x730)=0;F(0xf8)=0;I(0x180)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 322:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;F(0xf4)=0;B(0x184)=1;return;
 case 400:case 401:case 410:case 412:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 402:I(0x180)=0;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 404:case 406:I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;F(0x100)=0.5f;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 408: {
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0) {
   F(0xf4)=17.5f;B(0x47e)=0;S(0x730)=0;B(0x184)=1;F(0xf8)=0;I(0x180)=0;
  }
  float speed=static_cast<float>(F(0xf4)-0.5);F(0xf4)=speed;if(speed<0)F(0xf4)=0;
  if(advance_frame_and_dispatch())set_action_and_finalize(0);
  if(S(0x142)==0 && S(0x140)==6)dispatch_character_wave_handle(27);
  return;
 }
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 411:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=0;return;
 case 414:case 416:F(0x100)=0.5f;I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 415:F(0x100)=0.5f;I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=0;return;
 case 418:F(0xf8)=0;F(0x100)=0;F(0x73c)=25.0f;B(0x184)=1;B(0x47e)=0;I(0x180)=0;return;
 case 500:B(0x17c)=0;I(0x180)=0;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 502:B(0x17c)=0;I(0x180)=0;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 505:case 506:B(0x17c)=4;I(0x180)=0;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 507:case 508:B(0x17c)=4;I(0x180)=0;F(0xf4)*=0.25;F(0xf8)*=0.25;S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 510:B(0x17c)=8;I(0x180)=0;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 520:case 521:case 522:case 523:B(0x17c)=1;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 525:case 526:case 527:case 528:B(0x17c)=255;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;S(0x738)=0;B(0x184)=1;return;
 case 529:B(0x17c)=255;zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;return;
 case 530:case 531:case 532:case 533:B(0x17c)=9;zero_motion();I(0x180)=1;B(0x47e)=0;return;
 case 540:B(0x17c)=2;I(0x180)=0;zero_motion();F(0x100)=0;S(0x730)=0;F(0xf4)*=0.25;S(0x732)=0;S(0x736)=0;S(0x738)=0;F(0xf8)*=0.25;return;
 case 545:B(0x17c)=6;B(0x184)=1;F(0xf4)=0;I(0x180)=0;F(0xf8)=0;return;
 case 546:F(0xf4)=0;B(0x184)=0;I(0x180)=0;F(0xf8)=0;B(0x17c)=6;return;
 case 550:case 551:case 552:case 553:B(0x17c)=10;S(0x730)=0;B(0x184)=1;I(0x180)=0;zero_motion();return;
 case 554:B(0x17c)=10;B(0x184)=1;I(0x180)=0;return;
 case 560:case 561:B(0x17c)=3;S(0x730)=0;S(0x732)=0;zero_motion();I(0x180)=0;return;
 case 565:case 567:B(0x17c)=7;S(0x730)=0;S(0x732)=0;zero_motion();I(0x180)=0;return;
 case 600:case 601:case 602:case 604:case 605:case 611:case 661:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 603:I(0x180)=0;zero_motion();F(0x100)=0;S(0x730)=0;F(0xf4)*=0.25;S(0x732)=0;S(0x736)=0;S(0x738)=0;F(0xf8)*=0.25;return;
 case 606:S(0x730)=0;F(0x73c)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;S(0x738)=0;I(0x180)=0;B(0x184)=1;zero_motion();return;
 case 612:case 662:zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 710:case 720:case 721:case 730:S(0x730)=0;S(0x732)=0;S(0x734)=0;zero_motion();return;
 case 740:F(0x73c)=0;S(0x730)=0;F(0x740)=0;S(0x732)=0;F(0x744)=0;S(0x734)=0;F(0x748)=0;S(0x736)=0;S(0x738)=0;F(0x74c)=0;zero_motion();return;
 case 791:zero_motion();return;
 case 797:zero_motion();F(0xf4)=6.0f;F(0xf8)=-30.0f;S(0x730)=0;dispatch_character_wave_handle(14);return;
 case 798:zero_motion();F(0xf4)=6.0f;F(0xf8)=-30.0f;S(0x730)=0;dispatch_character_wave_handle(14);return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
