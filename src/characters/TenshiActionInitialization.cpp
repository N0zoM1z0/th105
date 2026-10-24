// JP1.06a64A0A0: complete target-reviewed action initializer.
#include "TenshiActionInitialization.hpp"
#include <cmath>
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
void TenshiActionEntryView::initialize_action_entry()
{
 float payload404[3];
 switch(S(0x13c)) {
 case 4:F(0xf4)=4.5f;return;
 case 5:F(0xf4)=-4.5f;return;
 case 214:S(0x736)=0;F(0xf4)=0;F(0xf8)=0;F(0x100)=0.6f;F(0x108)=0;F(0x10c)=95.0f;F(0x73c)=12.0f;F(0x74c)=0;return;
 case 300:case 301:case 303:case 322:
  if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 302:if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;B(0x750)=1;return;
 case 304:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 305:F(0xf8)=0;B(0x47e)=0;I(0x180)=0;F(0xf4)=13.5f;B(0x184)=1;F(0x100)=0;return;
 case 306:S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 307:I(0x180)=0;S(0x730)=0;B(0x184)=1;B(0x750)=1;return;
 case 308:zero_motion();B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 309:B(0x184)=1;I(0x180)=0;B(0x750)=1;return;
 case 310:S(0x730)=0;F(0x100)=0.5f;I(0x180)=0;B(0x184)=4;return;
 case 320:B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();return;
 case 321:zero_motion();B(0x184)=1;I(0x180)=0;return;
 case 400:I(0x180)=0;zero_motion();F(0x73c)=0;S(0x730)=0;S(0x732)=0;F(0x744)=0;B(0x750)=1;return;
 case 401:case 402:I(0x180)=0;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 404: {
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;F(0xf8)*=0.2f;
  payload404[0]=0;payload404[1]=0;payload404[2]=2;
  spawn_owned_object(848,F(0xec),F(0xf0),B(0x104),-1,payload404,3);return;
 }
 case 406: {
  float payload[3];
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;
  payload[0]=0;payload[1]=0;payload[2]=2;
  spawn_owned_object(848,F(0xec),F(0xf0),B(0x104),-1,payload,3);return;
 }
 case 408:F(0xf4)=13.5f;B(0x47e)=0;S(0x730)=0;I(0x180)=0;F(0xf8)=0;B(0x184)=4;return;
 case 409:B(0x47e)=0;F(0x100)=0.35f;S(0x730)=0;I(0x180)=0;B(0x184)=1;return;
 case 410:case 411:I(0x180)=0;zero_motion();B(0x750)=1;return;
 case 412:I(0x180)=0;zero_motion();return;
 case 414: {
  float payload[3];
  F(0x100)=0;I(0x180)=0;F(0xf4)*=0.2f;B(0x750)=1;F(0xf8)*=0.2f;
  payload[0]=0;payload[1]=0;payload[2]=2;
  spawn_owned_object(848,F(0xec),F(0xf0),B(0x104),-1,payload,3);return;
 }
 case 415: {
  float payload[3];
  I(0x180)=0;F(0x100)=0;B(0x750)=1;F(0xf4)*=0.2f;F(0xf8)*=0.2f;
  payload[0]=0;payload[1]=0;payload[2]=2;
  spawn_owned_object(848,F(0xec),F(0xf0),B(0x104),-1,payload,3);return;
 }
 case 416:I(0x180)=0;F(0x100)=0;F(0xf4)*=0.2f;F(0xf8)*=0.2f;return;
 case 418:F(0xf4)=11.0f;if(B(0x47e)==0)zero_motion();I(0x180)=0;B(0x184)=1;return;
 case 500:case 501:B(0x17c)=0;zero_motion();B(0x47e)=0;F(0x100)=0.55f;S(0x730)=0;B(0x184)=1;I(0x180)=1;return;
 case 505:B(0x17c)=4;zero_motion();B(0x184)=0;B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 520:case 521:B(0x17c)=1;zero_motion();B(0x47e)=0;S(0x730)=0;B(0x184)=99;I(0x180)=1;return;
 case 525:case 526:case 527:B(0x17c)=5;zero_motion();B(0x184)=0;B(0x47e)=0;S(0x730)=0;I(0x180)=1;return;
 case 540:B(0x17c)=2;I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;B(0x750)=0;return;
 case 542:B(0x17c)=2;B(0x184)=1;I(0x180)=1;B(0x750)=0;return;
 case 545:case 546:case 547:case 548: {
  B(0x17c)=6;I(0x180)=1;zero_motion();B(0x750)=1;
  if(S(0x13c)==547 || S(0x13c)==548) {
   float payload[3];payload[0]=0;payload[1]=0;payload[2]=2;
   spawn_owned_object(848,F(0xec),F(0xf0),B(0x104),-1,payload,3);
  }
  return;
 }
 case 560:case 561:B(0x17c)=3;I(0x180)=0;B(0x184)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;return;
 case 565:case 566:B(0x17c)=7;I(0x180)=0;B(0x184)=0;zero_motion();return;
 case 599:I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 600:case 603:case 606:case 607:case 657:zero_motion();I(0x180)=0;B(0x47e)=0;return;
 case 601:case 604:zero_motion();B(0x184)=1;I(0x180)=0;B(0x47e)=0;return;
 case 602:zero_motion();I(0x180)=0;B(0x184)=1;B(0x47e)=0;return;
 case 605:zero_motion();B(0x184)=1;I(0x180)=0;B(0x47e)=0;S(0x730)=0;return;
 case 700:return;
 case 720: {
  I(0x180)=0;B(0x184)=1;zero_motion();F(0x784)=25.0f;S(0x730)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;
  TenshiActionEntryView *peer=FIELD(TenshiActionEntryView *,0x170);
  float distance=static_cast<float>((F(0xec)-*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(peer)+0xec))/45.0);
  distance=static_cast<float>(std::fabs(distance));F(0x780)=distance;F(0x788)=0.5555555820465088f;return;
 }
 case 730:face_opponent_and_flip_horizontal_velocity();I(0x180)=0;zero_motion();S(0x730)=0;F(0x73c)=0;return;
 case 731:zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;S(0x738)=0;return;
 case 740:case 741:I(0x180)=1;zero_motion();F(0x73c)=0;S(0x730)=0;F(0x740)=0;return;
 case 750: {
  float payload[3];F(0x74c)=0;payload[0]=0;payload[1]=0;payload[2]=0;
  S(0x730)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;S(0x738)=0;
  spawn_owned_object(940,static_cast<float>(F(0xec)+C(0x104)*30),static_cast<float>(F(0xf0)+120.0),B(0x104),1,payload,3);return;
 }
 case 780:zero_motion();return;
 case 788:S(0x730)=0;return;
 case 795:case 797:case 798:S(0x730)=0;F(0xf4)=0;F(0xf8)=-15.0f;F(0x100)=0.5f;return;
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
