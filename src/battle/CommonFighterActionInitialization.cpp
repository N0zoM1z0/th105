// Complete JP1.06a477830 hypothesis from all1272 raw main instructions.
#include "CommonFighterActionInitialization.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
#define U(o) FIELD(unsigned,o)
#define DIR static_cast<unsigned char>(C(0x104))
void CommonActionEntryView::initialize_common_action_entry()
{
 switch(S(0x13c)) {
 case 0:case 1:case 2:case 3:
  if(B(0x47e)==0)zero_motion();return;
 case 6:
  if(!(B(0x724)&4)) {
   if(U(0x6c8)==0 || I(0x6b8)>=0 || I(0x6b4)!=0) {
    if(B(0x47e)==0)zero_motion();F(0x100)=0;return;
   }
  }
  set_action(208);return;
 case 7:
  if((B(0x724)&16) || (U(0x6c8)>0 && I(0x6b8)<0 && C(0x104)*I(0x6b4)>0))set_action(209);
  else {if(B(0x47e)==0)zero_motion();F(0x100)=0;}return;
 case 8:
  if((B(0x724)&8) || (U(0x6c8)>0 && I(0x6b8)<0 && C(0x104)*I(0x6b4)<0))set_action(210);
  else {if(B(0x47e)==0)zero_motion();F(0x100)=0;}return;
 case 10:dispatch_event(30);zero_motion();return;
 case 50:case 57:case 63:
  F(0xf4)=-15.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 51:
  F(0xf4)=-20.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 53:S(0x730)=0;S(0x732)=0;
  // The raw case53 prefix falls into the separate case52 literal load.
 case 52:
  F(0xf4)=-25.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 54:case 60:case 66:
  F(0xf4)=0;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 55:case 58:case 61:case 64:case 67:
  F(0xf4)=-20.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 56:case 62:
  F(0xf4)=-10.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 59:case 65:
  S(0x730)=0;S(0x732)=0;F(0xf4)=-25.0f;F(0xf8)=0;F(0x18c)=0;F(0x190)=0;F(0x12c)=0;return;
 case 70:
  S(0x730)=0;F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;
  if(F(0xf4)>0)S(0x730)=1;
  if(F(0xf4)<0)S(0x730)=-1;
  F(0x12c)=0;return;
 case 71:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.5f;S(0x730)=7;F(0x12c)=0;return;
 case 72:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=1.3f;F(0x12c)=0;return;
 case 73:case 88:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;S(0x730)=7;F(0x12c)=0;return;
 case 74:case 75:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;F(0x12c)=0;return;
 case 76:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  ++S(0x730);F(0x108)=S(0x7a0);F(0x10c)=S(0x7a2);S(0x186)=5;
  emit_effect(38,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  emit_effect(59,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  F(0xf4)=0;F(0xf8)=0;F(0x100)=0;publish_layout_scalar(2.0f);dispatch_event(22);F(0x12c)=0;return;
 case 77:
  F(0xf4)=-F(0x18c);F(0xf8)=F(0x190);F(0x100)=0.8f;
  F(0x108)=S(0x7a0);F(0x10c)=S(0x7a2);F(0x12c)=0;return;
 case 78:
  advance_secondary_event_effect_cycle();
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),F(0xf0),DIR,1);
  ++S(0x730);F(0xf4)=0;F(0xf8)=0;F(0x100)=0;publish_layout_scalar(4.0f);dispatch_event(22);
  emit_effect(38,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  emit_effect(59,static_cast<float>(F(0xec)-C(0x104)*50),static_cast<float>(F(0xf0)+100.0),DIR,1);
  F(0x12c)=0;return;
 case 89:
  advance_secondary_event_effect_cycle();emit_effect(58,F(0xec),F(0xf0),DIR,-1);
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  F(0x12c)=0;return;
 case 97:
  advance_secondary_event_effect_cycle();emit_effect(58,F(0xec),F(0xf0),DIR,-1);
  for(int i=0;i<5;++i)emit_effect(201,F(0xec),F(0xf0),DIR,1);
  F(0x12c)=0;return;
 case 98:zero_motion();B(0x47f)=0;S(0x730)=0;return;
 case 99:
  zero_motion();F(0x73c)=0;F(0x740)=0;F(0x744)=0;B(0x47f)=0;F(0x748)=0;S(0x730)=0;
  F(0x74c)=0;S(0x732)=0;S(0x734)=0;S(0x736)=0;S(0x738)=0;return;
 case 140:F(0xf4)=-11.0f;S(0x730)=0;F(0xf8)=0;F(0x12c)=0;return;
 case 143:case 144:F(0xf4)=-12.0f;S(0x730)=0;F(0xf8)=0;F(0x12c)=0;return;
 case 145:F(0xf4)=-10.0f;F(0xf8)=14.0f;F(0x100)=0.5f;F(0x12c)=0;return;
 case 149:F(0xf4)=-10.0f;F(0xf8)=14.0f;F(0x100)=0.5f;return;
 case 150:case 154:F(0xf4)=-6.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 151:case 155:F(0xf4)=-10.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 152:case 156:F(0xf4)=-13.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 153:case 157:F(0xf4)=-14.5f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 158:F(0xf4)=-6.0f;S(0x730)=7;F(0xf8)=14.0f;S(0x732)=0;F(0x100)=0.75f;return;
 case 159:case 163:F(0xf4)=-12.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 160:case 164:F(0xf4)=-20.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 161:case 165:F(0xf4)=-26.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 162:case 166:F(0xf4)=-29.0f;S(0x730)=0;F(0xf8)=0;I(0x180)=0;return;
 case 167:F(0xf4)=-6.0f;S(0x730)=7;F(0xf8)=8.0f;F(0x100)=0.75f;return;
 case 180:
  zero_motion();F(0xf4)=8.0f;F(0xf8)=12.5f;F(0x100)=0.75f;
  emit_effect(61,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);F(0x12c)=0;return;
 case 181:
  zero_motion();F(0xf4)=-8.0f;F(0xf8)=12.5f;F(0x100)=0.75f;
  emit_effect(61,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);F(0x12c)=0;return;
 case 197:case 198:case 199:zero_motion();return;
 case 200:B(0x47e)=1;
  // The target case200 prefix joins the201..203 actual clear/reset tail.
 case 201:case 202:case 203:
  zero_motion();S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 208:case 209:case 210:case 211:case 212:
  if(B(0x47e)==0)zero_motion();F(0x100)=0;return;
 case 220:case 221:case 222:
  zero_motion();emit_effect(69,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);return;
 case 223:
  B(0x47e)=1;zero_motion();emit_effect(69,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 224:
  zero_motion();emit_effect(69,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 225:case 226:
  zero_motion();emit_effect(69,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;S(0x734)=0;return;
 case 690: {
  emit_effect(71,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;
  if(C(0x55a)>0) {
   S(0x738)=reinterpret_cast<CommonEntryCardDeque *>(reinterpret_cast<unsigned char *>(this)+0x55c)->at(0).code;
   I(0x180)=1;zero_motion();
   switch(S(0x738)) {
   case 100:
    if(++C(0x624)==0)C(0x624)=1;if(C(0x624)>=5)C(0x624)=4;
    C(0x628)=-1;C(0x62c)=-1;C(0x630)=-1;break;
   case 101:
    if(++C(0x625)==0)C(0x625)=1;if(C(0x625)>=5)C(0x625)=4;
    C(0x629)=-1;C(0x62d)=-1;C(0x631)=-1;break;
   case 102:
    if(++C(0x626)==0)C(0x626)=1;if(C(0x626)>=5)C(0x626)=4;
    C(0x62a)=-1;C(0x62e)=-1;C(0x632)=-1;break;
   case 103:
    if(++C(0x627)==0)C(0x627)=1;if(C(0x627)>=5)C(0x627)=4;
    C(0x62b)=-1;C(0x62f)=-1;C(0x633)=-1;break;
   case 104:
    if(++C(0x628)==0)C(0x628)=1;if(C(0x628)>=5)C(0x628)=4;
    C(0x624)=-1;C(0x62c)=-1;C(0x630)=-1;break;
   case 105:
    if(++C(0x629)==0)C(0x629)=1;if(C(0x629)>=5)C(0x629)=4;
    C(0x625)=-1;C(0x62d)=-1;C(0x631)=-1;break;
   case 106:
    if(++C(0x62a)==0)C(0x62a)=1;if(C(0x62a)>=5)C(0x62a)=4;
    C(0x626)=-1;C(0x62e)=-1;C(0x632)=-1;break;
   case 107:
    if(++C(0x62b)==0)C(0x62b)=1;if(C(0x62b)>=5)C(0x62b)=4;
    C(0x627)=-1;C(0x62f)=-1;C(0x633)=-1;break;
   case 108:
    if(++C(0x62c)==0)C(0x62c)=1;if(C(0x62c)>=5)C(0x62c)=4;
    C(0x624)=-1;C(0x628)=-1;C(0x630)=-1;break;
   case 109:
    if(++C(0x62d)==0)C(0x62d)=1;if(C(0x62d)>=5)C(0x62d)=4;
    C(0x625)=-1;C(0x629)=-1;C(0x631)=-1;break;
   case 110:
    if(++C(0x62e)==0)C(0x62e)=1;if(C(0x62e)>=5)C(0x62e)=4;
    C(0x626)=-1;C(0x62a)=-1;C(0x632)=-1;break;
   case 111:
    if(++C(0x62f)==0)C(0x62f)=1;if(C(0x62f)>=5)C(0x62f)=4;
    C(0x627)=-1;C(0x62b)=-1;C(0x633)=-1;break;
   case 112:
    if(++C(0x630)==0)C(0x630)=1;if(C(0x630)>=5)C(0x630)=4;
    C(0x624)=-1;C(0x628)=-1;C(0x62c)=-1;break;
   case 113:
    if(++C(0x631)==0)C(0x631)=1;if(C(0x631)>=5)C(0x631)=4;
    C(0x625)=-1;C(0x629)=-1;C(0x62d)=-1;break;
   case 114:
    if(++C(0x632)==0)C(0x632)=1;if(C(0x632)>=5)C(0x632)=4;
    C(0x626)=-1;C(0x62a)=-1;C(0x62e)=-1;break;
   case 115:
    if(++C(0x633)==0)C(0x633)=1;if(C(0x633)>=5)C(0x633)=4;
    C(0x627)=-1;C(0x62b)=-1;C(0x62f)=-1;break;
   }
  }
  emit_effect(static_cast<short>(C(0x5c0+S(0x738))+130),F(0xec),F(0xf0),1,1);
  dispatch_sequence_window(0,1,60);return;
 }
 case 691:S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();return;
 case 692:
  emit_effect(71,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();dispatch_sequence_window(0,1,60);return;
 case 693:
  emit_effect(71,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();dispatch_sequence_window(0,1,60);return;
 case 694:
  emit_effect(71,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x730)=0;S(0x732)=0;I(0x180)=1;zero_motion();dispatch_sequence_window(0,1,60);return;
 case 695:B(0x184)=1;I(0x180)=0;zero_motion();dispatch_sequence_window(0,1,60);return;
 case 696:
  B(0x184)=1;I(0x180)=0;B(0x47e)=0;zero_motion();
  emit_effect(69,F(0xec),static_cast<float>(F(0xf0)+100.0),DIR,1);
  S(0x48a)=15;dispatch_sequence_window(0,1,60);return;
 case 700:zero_motion();F(0x100)=0;I(0x180)=1;return;
 case 701:case 702:case 703:zero_motion();F(0x100)=0;return;
 case 704:if(F(0x100)==0.0f)F(0x100)=0.5f;return;
 case 705:zero_motion();F(0xf4)=F(0x778);return;
 case 706:zero_motion();F(0xf4)=F(0x77c);return;
 case 709:dispatch_event(30);zero_motion();return;
 case 789:S(0x738)=0;zero_motion();return;
 case 790:S(0x730)=0;zero_motion();return;
 case 795:S(0x730)=0;return;
 case 796:case 799:F(0x73c)=0;zero_motion();return;
 default:return;
 }
}
#undef FIELD
#undef F
#undef S
#undef B
#undef C
#undef I
#undef U
#undef DIR
}
