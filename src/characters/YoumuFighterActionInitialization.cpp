// JP1.06a53A1D0: complete independently reviewed Fighter initializer.
#include "YoumuFighterActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
void YoumuFighterActionEntryView::initialize_action_entry()
{
 if(B(0x7e4)==0) {
  float payload[3]={0,0,0};
  spawn_owned_object(899,static_cast<float>(F(0xec)-C(0x104)*600),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,payload,3);
  B(0x7e4)=1;
 }
 unsigned char phase;
 switch(S(0x13c)) {
 case 4:F(0xf4)=4.0f;return;
 case 5:F(0xf4)=-4.0f;return;
 case 214:F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=14.5f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 311:case 321:case 322:case 323:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;S(0x738)=0;B(0x750)=1;B(0x184)=1;B(0x7cd)=1;return;
 case 304:B(0x47e)=0;I(0x180)=0;B(0x750)=1;B(0x184)=1;B(0x7cd)=1;zero_motion();return;
 case 305:case 308:I(0x180)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 306:case 309:I(0x180)=0;S(0x730)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 307:zero_motion();I(0x180)=0;F(0x73c)=0;S(0x730)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 310:F(0xf4)=0;I(0x180)=0;F(0xf8)=0;S(0x730)=0;B(0x184)=99;F(0x100)=0.5f;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 400:case 401:case 402:case 410:case 411:case 412:
  I(0x180)=1;zero_motion();S(0x738)=0;S(0x736)=0;S(0x734)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 404:I(0x180)=1;S(0x738)=0;S(0x736)=0;S(0x734)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 408:F(0xf4)=14.0f;B(0x47e)=0;I(0x180)=0;S(0x730)=0;F(0xf8)=0;B(0x184)=1;F(0x100)=0;B(0x7cd)=1;return;
 case 414:case 415:case 416:F(0x100)=0;I(0x180)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;S(0x738)=0;S(0x736)=0;S(0x734)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 418:F(0xf4)=14.0f;B(0x47e)=0;I(0x180)=0;S(0x730)=0;F(0xf8)=0;B(0x184)=1;B(0x7cd)=1;return;
 case 500:case 501:I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 505:case 506:case 510:case 511:case 560:case 561:case 565:case 566:case 570:case 571:
  I(0x180)=0;zero_motion();S(0x730)=0;B(0x750)=1;return;
 case 520:case 521:case 540:case 541:case 545:
  I(0x180)=0;B(0x184)=1;B(0x7cd)=1;zero_motion();B(0x750)=1;return;
 case 525:case 526: {
  I(0x180)=0;B(0x184)=1;B(0x7cd)=1;zero_motion();signed char sequence=C(0x609);B(0x750)=1;
  if(sequence>=2)select_sequence(static_cast<short>(sequence));return;
 }
 case 529:B(0x47e)=0;I(0x180)=0;B(0x750)=1;B(0x184)=1;B(0x7cd)=1;zero_motion();return;
 case 530:case 531:I(0x180)=0;B(0x184)=0;zero_motion();B(0x750)=1;return;
 case 546:I(0x180)=0;B(0x184)=3;B(0x7cd)=3;zero_motion();S(0x730)=0;B(0x750)=1;return;
 case 600:case 603:I(0x180)=0;B(0x184)=1;B(0x7cd)=1;zero_motion();S(0x730)=0;return;
 case 601:phase=5;publish_phase:B(0x184)=phase;B(0x7cd)=phase;I(0x180)=0;zero_motion();S(0x730)=0;return;
 case 602:case 605:case 606:case 607:case 710:I(0x180)=0;zero_motion();S(0x730)=0;return;
 case 604:phase=6;goto publish_phase;
 case 720:case 730:I(0x180)=0;zero_motion();S(0x732)=0;S(0x734)=0;S(0x730)=0;return;
 case 797:zero_motion();dispatch_event(31);F(0xf4)=17.5f;S(0x730)=0;F(0xf8)=0;F(0x100)=1.2f;return;
 case 798:zero_motion();dispatch_event(31);F(0xf4)=17.5f;S(0x730)=0;F(0xf8)=0;F(0x100)=1.2f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef C
#undef I
}
