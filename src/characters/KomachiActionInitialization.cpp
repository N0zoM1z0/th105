// JP1.06a5F6700: complete action initializer, independently reviewed.
#include "KomachiActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void KomachiActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=6.0f;return;
 case 5:F(0xf4)=-5.0f;return;
 case 214:
  reinterpret_cast<KomachiEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=12.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 321:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=17.5f;B(0x184)=1;F(0x100)=0;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:case 308:case 309:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 310:F(0x100)=0.5f;B(0x184)=1;I(0x180)=0;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 400:case 401:case 402:I(0x180)=1;zero_motion();F(0x73c)=0;F(0x740)=0;S(0x730)=0;S(0x732)=0;F(0x744)=0;S(0x734)=0;B(0x750)=1;return;
 case 404:case 405:case 406:F(0x73c)=0;S(0x730)=0;F(0x740)=0;S(0x732)=0;F(0x744)=0;S(0x734)=0;F(0x100)=0;I(0x180)=1;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=17.5f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=1;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 410:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 411:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 412:I(0x180)=1;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 414:F(0x100)=0;S(0x730)=0;F(0xf4)*=0.2f;S(0x732)=0;S(0x736)=0;S(0x738)=0;I(0x180)=1;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 415:case 416:F(0x100)=0;S(0x730)=0;I(0x180)=1;B(0x750)=1;F(0xf4)*=0.2f;S(0x732)=0;S(0x736)=0;F(0xf8)*=0.2f;return;
 case 418:F(0xf4)=17.5f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 500:case 501:B(0x17c)=0;zero_motion();B(0x184)=0;B(0x47e)=0;I(0x180)=1;return;
 case 505:case 506:B(0x17c)=4;zero_motion();B(0x184)=0;B(0x47e)=0;I(0x180)=1;B(0x750)=1;return;
 case 507:case 508:F(0xf4)*=0.1f;B(0x184)=0;B(0x47e)=0;B(0x17c)=4;I(0x180)=1;B(0x750)=1;F(0xf8)*=0.1f;F(0x100)=0;return;
 case 510:case 511:B(0x17c)=8;zero_motion();B(0x184)=0;B(0x47e)=0;I(0x180)=1;return;
 case 520:case 521:B(0x17c)=1;zero_motion();I(0x180)=1;B(0x47e)=0;S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 525:B(0x17c)=5;zero_motion();B(0x184)=8;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 526:B(0x17c)=5;zero_motion();B(0x184)=12;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 540:case 541:case 542:case 543:B(0x17c)=2;S(0x738)=0;I(0x180)=1;zero_motion();B(0x750)=0;return;
 case 545:case 546:B(0x17c)=6;I(0x180)=1;zero_motion();B(0x750)=1;return;
 case 550:F(0x73c)=0;
 publish_550:B(0x184)=1;B(0x17c)=10;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 551:F(0x73c)=1;goto publish_550;
 case 560:case 561:B(0x17c)=3;I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;B(0x750)=1;return;
 case 565:case 566:B(0x17c)=7;I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;B(0x750)=1;return;
 case 599:I(0x180)=1;zero_motion();S(0x732)=0;S(0x736)=0;S(0x730)=0;S(0x738)=0;return;
 case 600:S(0x730)=0;I(0x180)=0;B(0x184)=1;zero_motion();return;
 case 601:I(0x180)=0;B(0x184)=1;zero_motion();return;
 case 602:case 605:case 606:zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 603:S(0x730)=0;B(0x184)=0;I(0x180)=1;zero_motion();return;
 case 604:I(0x180)=0;B(0x184)=1;zero_motion();S(0x730)=0;S(0x732)=0;return;
 case 611:B(0x184)=1;I(0x180)=0;zero_motion();return;
 case 612:case 615:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 710:case 720:case 730:zero_motion();S(0x730)=0;return;
 case 711:zero_motion();S(0x730)=0;S(0x732)=0;return;
 case 732:zero_motion();S(0x730)=0;S(0x738)=0;return;
 case 797:zero_motion();dispatch_indexed_event_member(31);F(0xf4)=12.0f;S(0x730)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 case 798:zero_motion();dispatch_indexed_event_member(31);F(0xf4)=12.0f;S(0x730)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
