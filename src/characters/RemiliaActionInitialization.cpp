// JP1.06a554D50: complete action initializer, independently reviewed.
#include "RemiliaActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void RemiliaActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=6.5f;return;
 case 5:F(0xf4)=-6.5f;return;
 case 214:S(0x736)=0;F(0xf4)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=75.0f;F(0x73c)=25.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=17.5f;B(0x184)=1;F(0x100)=0;return;
 case 306:case 325:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:zero_motion();B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 308:case 309:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 310:F(0xf4)=0;S(0x730)=0;B(0x184)=99;I(0x180)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 321:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=2;return;
 case 400:case 401:case 402:case 410:case 411:I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 404:case 406:I(0x180)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=17.5f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=1;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 412:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 414:F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 415:I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 416:B(0x750)=1;I(0x180)=0;return;
 case 418:F(0xf4)=17.5f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 500:case 501:B(0x17c)=0;zero_motion();B(0x184)=1;I(0x180)=0;B(0x47e)=0;return;
 case 505:case 506: {
  B(0x17c)=4;zero_motion();short sequence=FIELD(unsigned short,0x730);
  B(0x184)=1;I(0x180)=0;B(0x47e)=0;select_sequence(sequence);return;
 }
 case 520:case 521:B(0x17c)=1;B(0x750)=1;zero_motion();I(0x180)=1;B(0x47e)=0;return;
 case 525:case 526:B(0x17c)=5;B(0x750)=1;zero_motion();I(0x180)=1;B(0x47e)=0;return;
 case 530:case 531:B(0x17c)=9;zero_motion();B(0x184)=0;B(0x47e)=0;I(0x180)=1;B(0x750)=1;return;
 case 540:case 541:S(0x730)=0;B(0x184)=4;B(0x17c)=2;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 542:case 547:B(0x17c)=2;B(0x184)=1;I(0x180)=0;B(0x750)=0;return;
 case 545:case 546:B(0x17c)=6;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 560:case 561:B(0x17c)=3;B(0x184)=1;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 565:case 566:B(0x17c)=7;I(0x180)=0;zero_motion();B(0x184)=1;B(0x750)=1;return;
 case 567:B(0x17c)=7;I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 599:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 600:F(0x73c)=240.0f;I(0x180)=1;zero_motion();return;
 case 601:case 604:I(0x180)=1;zero_motion();return;
 case 602:case 605:S(0x730)=0;S(0x732)=0;I(0x180)=0;B(0x184)=20;zero_motion();return;
 case 603:I(0x180)=1;F(0x73c)=320.0f;zero_motion();return;
 case 606:S(0x730)=0;S(0x732)=0;I(0x180)=0;B(0x184)=1;zero_motion();return;
 case 607:case 710:case 711:I(0x180)=1;zero_motion();F(0x73c)=0;F(0x744)=0;return;
 case 608:case 610:case 611:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 612:case 615:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 707:zero_motion();return;
 case 708:F(0xf4)=0;S(0x730)=0;return;
 case 709:S(0x730)=0;return;
 case 720:case 721:I(0x180)=0;B(0x184)=1;zero_motion();S(0x730)=0;return;
 case 730:case 731:case 740:I(0x180)=0;B(0x184)=0;zero_motion();S(0x730)=0;S(0x732)=0;return;
 case 797:zero_motion();F(0xf4)=12.0f;S(0x730)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 case 798:zero_motion();F(0xf4)=12.0f;S(0x730)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
