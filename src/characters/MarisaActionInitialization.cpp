// JP1.06a4B89C0: complete target-reviewed action initializer.
#include "MarisaActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
void MarisaActionEntryView::initialize_action_entry()
{
 switch(S(0x13c)) {
 case 4:F(0xf4)=6.0f;return;
 case 5:F(0xf4)=-5.0f;return;
 case 214:
  reinterpret_cast<MarisaEntryScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
  F(0xf4)=0;S(0x736)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=12.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 321:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x47e)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=17.5f;B(0x184)=1;F(0x100)=0;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:case 308:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 309:B(0x184)=1;I(0x180)=0;B(0x750)=1;zero_motion();return;
 case 310:S(0x730)=0;F(0x100)=0.5f;I(0x180)=0;B(0x184)=1;return;
 case 320:B(0x47e)=0;I(0x180)=0;B(0x184)=1;return;
 case 400:case 401:case 402:case 411:
  I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 404:case 406:case 415:
  I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 408:F(0xf4)=17.5f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=1;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 410:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;return;
 case 412:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 414:
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=1;F(0xf8)*=0.2f;return;
 case 416:I(0x180)=0;S(0x738)=0;B(0x184)=1;return;
 case 418:F(0xf4)=17.5f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 420:case 421:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x7a8)=0;S(0x7a4)=0;return;
 case 422:
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x7a8)=0;S(0x7a4)=0;F(0xf8)*=0.2f;return;
 case 430:case 431:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;S(0x7a8)=0;S(0x7a4)=0;return;
 case 432:
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;S(0x7a8)=0;S(0x7a4)=0;F(0xf8)*=0.2f;return;
 case 500:B(0x17c)=0;zero_motion();I(0x180)=0;F(0x100)=0.55f;B(0x47e)=0;S(0x730)=0;B(0x184)=1;return;
 case 504:B(0x17c)=0;zero_motion();F(0xf4)=10.0f;B(0x47e)=0;F(0xf8)=10.0f;S(0x730)=0;B(0x184)=1;F(0x100)=0.55f;I(0x180)=1;return;
 case 505:case 506:B(0x17c)=4;zero_motion();B(0x47e)=0;S(0x730)=0;B(0x184)=1;I(0x180)=1;return;
 case 510:case 512:B(0x17c)=8;zero_motion();F(0x73c)=0;B(0x184)=0;I(0x180)=0;B(0x47e)=0;return;
 case 520:case 521:B(0x17c)=1;zero_motion();B(0x184)=99;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 525:case 526:B(0x17c)=5;zero_motion();B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 530:case 531:B(0x17c)=9;zero_motion();B(0x184)=0;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 540:case 541:B(0x17c)=2;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 542:B(0x17c)=2;B(0x184)=1;I(0x180)=0;B(0x750)=0;return;
 case 545:B(0x17c)=6;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 547:B(0x17c)=6;B(0x184)=1;I(0x180)=0;B(0x750)=0;return;
 case 550:case 551:B(0x17c)=10;I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 560:case 561:B(0x17c)=3;I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 562:case 563:B(0x17c)=3;I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 565:case 566:B(0x17c)=7;I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 567:case 568:B(0x17c)=7;I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 570:case 571:B(0x17c)=11;I(0x180)=0;zero_motion();S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 572:case 573:B(0x17c)=11;I(0x180)=0;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 599:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 600:case 601:case 602:case 608:case 610:case 611:case 658:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 603: {
  float payload[3];S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();
  if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())==0) {
   payload[0]=0;payload[1]=0;payload[2]=10.0f;
   spawn_owned_object(853,F(0xec),F(0xf0),B(0x104),-1,payload,3);
  }
  return;
 }
 case 605:S(0x730)=0;I(0x180)=0;B(0x184)=6;zero_motion();S(0x732)=0;S(0x734)=0;return;
 case 606:zero_motion();B(0x184)=99;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 607:zero_motion();B(0x47e)=0;S(0x730)=0;return;
 case 612:case 615:I(0x180)=1;zero_motion();S(0x738)=0;S(0x736)=0;S(0x732)=0;S(0x730)=0;B(0x750)=1;return;
 case 613:I(0x180)=0;B(0x750)=1;return;
 case 619:case 730:case 732:S(0x730)=0;S(0x732)=0;zero_motion();return;
 case 707:case 720:case 722:zero_motion();return;
 case 708:zero_motion();S(0x730)=0;return;
 case 710:case 711:zero_motion();face_opponent_and_flip_horizontal_velocity();return;
 case 721:zero_motion();S(0x732)=0;S(0x738)=0;S(0x736)=0;return;
 case 731:case 733:S(0x730)=0;F(0x73c)=0;S(0x732)=0;zero_motion();return;
 case 797:S(0x730)=0;dispatch_character_wave_handle(5);return;
 case 798:dispatch_character_wave_handle(5);zero_motion();F(0xf4)=15.0f;S(0x730)=0;F(0xf8)=0;F(0x100)=0.5f;return;
 default:initialize_common_action_entry();return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef I
}
