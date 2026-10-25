// JP1.06a56C840: complete target-reviewed action initializer.
#include "YuyukoActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void YuyukoActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=4.0f;return;
 case 5:F(0xf4)=-4.0f;return;
 case 214:S(0x736)=0;F(0xf4)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=9.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=12.0f;B(0x184)=1;F(0x100)=0;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:case 309:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 308:B(0x184)=4;I(0x180)=0;B(0x750)=1;return;
 case 310:F(0xf4)=0;S(0x730)=0;F(0xf8)=0;I(0x180)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 320:B(0x47e)=0;zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 321:zero_motion();B(0x184)=1;I(0x180)=0;return;
 case 400:case 401:case 411:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 402:case 410:case 412:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;B(0x750)=1;return;
 case 404:case 406:S(0x736)=0;S(0x732)=0;F(0x100)=0;S(0x730)=0;I(0x180)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=14.5f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=1;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 414:case 416:F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x734)=0;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 415:S(0x734)=0;S(0x732)=0;F(0x100)=0;S(0x730)=0;I(0x180)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 418:F(0xf4)=15.0f;B(0x184)=1;I(0x180)=0;return;
 case 500:case 501:B(0x17c)=0;zero_motion();B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 502:case 503:B(0x17c)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;F(0x100)=0;B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 505:case 506:B(0x17c)=4;zero_motion();B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 507:case 508:B(0x17c)=4;F(0xf4)*=0.2f;F(0xf8)*=0.2f;F(0x100)=0;B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 510:case 511:B(0x17c)=8;zero_motion();I(0x180)=1;B(0x47e)=0;S(0x730)=0;F(0x740)=0;return;
 case 512:case 513:F(0xf4)*=0.2f;B(0x47e)=0;S(0x730)=0;B(0x17c)=8;I(0x180)=1;F(0xf8)*=0.2f;F(0x100)=0;F(0x740)=0;return;
 case 520:case 521:B(0x17c)=1;zero_motion();I(0x180)=0;B(0x47e)=0;return;
 case 522:case 523:F(0xf4)*=0.2f;I(0x180)=0;B(0x47e)=0;B(0x17c)=1;F(0xf8)*=0.2f;F(0x100)=0;return;
 case 525:case 526:B(0x17c)=5;zero_motion();I(0x180)=0;B(0x47e)=0;return;
 case 540:case 541:B(0x17c)=2;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 545:case 546:B(0x17c)=6;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 547:B(0x17c)=2;B(0x184)=1;I(0x180)=0;B(0x750)=0;return;
 case 560:case 561:B(0x17c)=3;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 562:B(0x17c)=3;S(0x736)=0;S(0x732)=0;F(0x100)=0;S(0x730)=0;I(0x180)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 565:case 566:case 567:B(0x17c)=7;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 599:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 600:case 602:case 605:case 606:I(0x180)=1;zero_motion();return;
 case 601:case 604:case 608:case 610:case 611:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 651:F(0x100)=0;S(0x730)=0;F(0xf8)*=0.2f;S(0x732)=0;I(0x180)=1;F(0xf4)*=0.2f;return;
 case 603:S(0x730)=0;F(0x740)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 607:case 657:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;return;
 case 612:case 615:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 700:return;
 case 701:case 702:case 703:if(B(0x47e)==0)zero_motion();return;
 case 704:case 707:zero_motion();return;
 case 705:F(0xf4)=6.0f;return;
 case 706:F(0xf4)=-6.0f;return;
 case 708:F(0xf4)=0;S(0x730)=0;return;
 case 709:S(0x730)=0;return;
 case 710:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 720:case 730:I(0x180)=0;zero_motion();S(0x730)=0;F(0x73c)=0;return;
 case 725:F(0xf4)=4.0f;S(0x730)=0;return;
 case 726:S(0x730)=0;F(0xf4)=-4.0f;return;
 case 731:I(0x180)=0;zero_motion();F(0x73c)=0;S(0x730)=0;F(0x740)=F(0xf0);F(0x744)=0;return;
 case 797:S(0x730)=0;dispatch_character_wave_handle(50);return;
 case 798:S(0x730)=0;dispatch_character_wave_handle(50);return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
