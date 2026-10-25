// JP1.06a62FFF0: complete action initializer, independently reviewed.
#include "IkuActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void IkuActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=6.0f;return;
 case 5:F(0xf4)=-5.0f;return;
 case 214:
  reinterpret_cast<IkuEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=10.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 321:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;F(0xf4)=8.5f;F(0x100)=0;B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 306:I(0x180)=0;S(0x730)=0;B(0x184)=1;return;
 case 307:case 308:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 309:B(0x184)=4;I(0x180)=0;B(0x750)=1;return;
 case 310:F(0xf4)=0;I(0x180)=0;F(0xf8)=0;S(0x730)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 400:case 401:case 402:I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 404:case 406:I(0x180)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=12.5f;F(0xf8)=0;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x730)=0;return;
 case 409:F(0x100)=0.35f;B(0x184)=1;B(0x47e)=0;I(0x180)=0;S(0x730)=0;return;
 case 410:I(0x180)=0;zero_motion();S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 411:I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 412:I(0x180)=0;zero_motion();S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;return;
 case 414:F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 415:S(0x736)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;I(0x180)=0;S(0x732)=0;S(0x730)=0;F(0xf8)*=0.2f;return;
 case 416:case 417:F(0x100)=0;S(0x736)=0;B(0x750)=1;F(0xf4)*=0.15f;I(0x180)=0;S(0x732)=0;S(0x730)=0;F(0xf8)*=0.15f;return;
 case 418:F(0xf4)=10.5f;B(0x184)=1;I(0x180)=0;return;
 case 500:B(0x17c)=0;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=4;return;
 case 501:B(0x17c)=0;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=6;return;
 case 505:case 506:B(0x17c)=4;zero_motion();B(0x184)=0;B(0x47e)=0;S(0x730)=0;I(0x180)=1;B(0x750)=1;return;
 case 520:case 521:B(0x17c)=1;zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 525:case 526:B(0x17c)=5;zero_motion();B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 540:case 541:B(0x17c)=2;I(0x180)=0;zero_motion();B(0x750)=0;return;
 case 545:case 546:B(0x17c)=6;I(0x180)=0;zero_motion();return;
 case 547:I(0x180)=0;B(0x750)=0;B(0x17c)=2;B(0x184)=1;return;
 case 560:case 561:case 562:case 563:B(0x17c)=3;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 565:case 566:B(0x17c)=7;I(0x180)=0;zero_motion();S(0x734)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 567:case 568:B(0x17c)=7;S(0x734)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;I(0x180)=0;S(0x732)=0;S(0x730)=0;F(0xf8)*=0.2f;return;
 case 570:case 571:case 572:case 573:B(0x17c)=11;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 599:I(0x180)=1;zero_motion();S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;return;
 case 600:case 602:case 606:case 650:case 710:case 720:I(0x180)=0;zero_motion();return;
 case 601:zero_motion();I(0x180)=0;B(0x47e)=0;S(0x730)=0;B(0x184)=99;return;
 case 603:I(0x180)=1;zero_motion();return;
 case 605:S(0x730)=0;I(0x180)=0;B(0x184)=6;zero_motion();S(0x732)=0;S(0x734)=0;return;
 case 607:zero_motion();B(0x47e)=0;S(0x730)=0;return;
 case 608:case 609:case 610:case 611:case 660:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 612:case 615:I(0x180)=1;zero_motion();S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 730:I(0x180)=0;zero_motion();S(0x734)=0;return;
 case 740:zero_motion();S(0x736)=0;S(0x738)=0;S(0x732)=0;S(0x730)=0;return;
 case 780:zero_motion();return;
 case 781:F(0x73c)=13.0f;S(0x732)=0;F(0x740)=200.0f;S(0x730)=0;return;
 case 797:case 798:F(0xf4)=10.0f;F(0xf8)=-5.0f;F(0x100)=-0.12f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
