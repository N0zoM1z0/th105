#include "CpuActionPolicies.hpp"
#include "engine/AngleAtan2.hpp"

#include "../battle/Collision.hpp"

#include <stdlib.h>

namespace th105 {

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

unsigned int __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);

#define CPU_FIELD(offset) (reinterpret_cast<unsigned char *>(this) + (offset))
void CpuActionPolicyView::update_default_cpu_action_policy()
{
int v2; // edi
int v3; // eax
int v4; // eax
int v6; // eax
int v7; // edx
int v8; // ecx
int v9; // eax
__int16 v10; // ax
int v11; // eax
__int16 v12; // ax
int v13; // eax
__int16 v14; // cx
double v15; // st7
double v16; // st6
double v17; // st7
bool v18; // zf
double v19; // st6
bool v20; // c0
bool v21; // c3
int v22; // eax
__int16 v23; // cx
int v24; // eax
int v25; // eax
__int16 v26; // cx
int v27; // eax
__int16 v28; // ax
int v29; // eax
__int16 v30; // cx
int v31; // ecx
int v32; // eax
int v33; // edx
int v34; // eax
__int16 v35; // ax
int v36; // eax
int v37; // ecx
double v38; // st7
int v39; // eax
int v40; // ecx
int v41; // eax
__int16 v42; // ax
int v43; // eax
int v44; // ecx
bool v45; // zf
int v46; // eax
int v47; // eax
__int16 v48; // ax
int v49; // edx
int v50; // eax
__int16 v51; // ax
int v52; // eax
__int16 v53; // ax
int v54; // eax
int v55; // eax
int v56; // eax
__int16 v57; // cx
int v58; // eax
__int16 v59; // cx
int v62; // eax
int v63; // ecx
__int16 v64; // ax
bool v65; // zf
int v66; // eax
__int16 v67; // ax
double v68; // st7
int v69; // eax
__int16 v70; // ax
int v71; // eax
int v72; // ecx
int v73; // edx
int v74; // ecx
int v75; // eax
int v76; // eax
int v77; // eax
int v78; // ecx
int v79; // eax
int v80; // eax
int v81; // eax
int v82; // ecx
int v83; // ecx
__int16 v84; // ax
char v89; // dl
int v90; // eax
char v91; // cl
int v93; // eax
int v94; // eax
double v95; // st7
double v96; // st6
double v97; // st7
int v98; // edi
double v99; // st7
double v100; // st7
bool v101; // cc
char v102; // al
int v103; // edx
int v104; // ecx
__int16 v105; // ax
char v107; // al
int v108; // ecx
__int16 v109; // ax
char v110; // al
float v117; // [esp+18h] [ebp-Ch]
float v118; // [esp+1Ch] [ebp-8h]
v2 = *(_DWORD *)CPU_FIELD(368);
*(_DWORD *)CPU_FIELD(1828) = 0;
*(_DWORD *)CPU_FIELD(1832) = 0;
v3 = (int)(*(float *)(v2 + 236) - *(float *)CPU_FIELD(236));
v117 = (float)abs(v3);
v4 = (int)(*(float *)(v2 + 240) - *(float *)CPU_FIELD(240));
*(__int16 *)CPU_FIELD(1896) -= 1;
v118 = (float)abs(v4);
*(_DWORD *)CPU_FIELD(1724) = 0;
*(_DWORD *)CPU_FIELD(1728) = 0;
*(_DWORD *)CPU_FIELD(1732) = 0;
*(_DWORD *)CPU_FIELD(1736) = 0;
*(_DWORD *)CPU_FIELD(1740) = 0;
*(_DWORD *)CPU_FIELD(1744) = 0;
if ( *(__int16 *)CPU_FIELD(316) > 49 && *(__int16 *)CPU_FIELD(316) < 150 )
{
*(_WORD *)CPU_FIELD(1900) = 0;
*(_WORD *)CPU_FIELD(1898) = 0;
*(_WORD *)CPU_FIELD(1894) = 0;
*(_WORD *)CPU_FIELD(1896) = 0;
*(_WORD *)CPU_FIELD(1892) = 0;
if ( mt19937_next_u32() % 0x64 <= 0xA )
{
*(_DWORD *)CPU_FIELD(1724) = 1;
*(_DWORD *)CPU_FIELD(1716) = selector_random_roll(3u) - 1;
}
}
if ( *(__int16 *)CPU_FIELD(316) <= 199 )
{
*(_WORD *)CPU_FIELD(1900) = 0;
*(_WORD *)CPU_FIELD(1892) = 0;
}
v6 = selector_random_roll(0x3E8u);
v7 = *(_DWORD *)CPU_FIELD(368);
*(_WORD *)CPU_FIELD(1902) = v6;
if ( *(__int16 *)(v7 + 372) <= 0 )
return;
switch ( *(__int16 *)CPU_FIELD(316) )
{
case 0xC8:
if ( !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = 100;
if ( v117 >= 700.0 )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u) + 1;
}
v8 = *(_DWORD *)CPU_FIELD(368);
if ( (*(float *)CPU_FIELD(236) > *(float *)(v8 + 236) && *(_BYTE *)CPU_FIELD(260) == 0xFF
|| *(float *)CPU_FIELD(236) < *(float *)(v8 + 236) && *(_BYTE *)CPU_FIELD(260) == 1)
&& *(__int16 *)CPU_FIELD(1892) >= 50 )
{
if ( v117 < 220.0 && static_cast<unsigned>(selector_random_roll(0x3E8u)) < 0x55u && v118 < 50.0 )
{
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
}
else if ( v117 >= 150.0 && v117 <= 300.0 && v118 < 50.0
          && static_cast<unsigned>(selector_random_roll(0x3E8u)) < 0x32u )
{
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
}
else if ( v117 >= 250.0 && v117 <= 300.0 && v118 > 50.0 && v118 < 150.0
          && static_cast<unsigned>(selector_random_roll(0x3E8u)) < 0x32u )
{
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1732) = 2;
}
}
break;
case 0x12C:
v9 = *(_DWORD *)CPU_FIELD(384);
if ( !v9 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v9 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v10 = *(_WORD *)CPU_FIELD(1892);
if ( v10 >= 10 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
if ( v10 > 90 )
{
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = 1;
}
else
{
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
}
break;
case 0x12D:
v11 = *(_DWORD *)CPU_FIELD(384);
if ( !v11 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v11 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v12 = *(_WORD *)CPU_FIELD(1892);
if ( v12 < 20 )
goto LABEL_54;
if ( v12 <= 65 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
if ( v12 > 85 )
goto LABEL_55;
if ( *(__int16 *)CPU_FIELD(1154) < 400 )
{
LABEL_54:
if ( v12 >= 85 )
{
LABEL_55:
if ( v12 <= 95 && *(__int16 *)CPU_FIELD(1154) >= 400 && 0.0 == *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
goto LABEL_327;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
break;
case 0x12E:
v13 = *(_DWORD *)CPU_FIELD(384);
if ( v13 )
{
if ( v13 != 3 && !*(_WORD *)CPU_FIELD(1892) )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
else
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
v14 = *(_WORD *)CPU_FIELD(1892);
if ( v14 < 0 )
goto LABEL_68;
if ( v14 > 30 )
goto LABEL_69;
if ( *(__int16 *)CPU_FIELD(1154) >= 300 )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_68:
if ( v14 < 30 )
goto LABEL_72;
LABEL_69:
if ( v14 > 50 )
goto LABEL_73;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_72:
if ( v14 < 50 )
goto LABEL_75;
LABEL_73:
if ( v14 <= 60 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
goto LABEL_326;
LABEL_75:
if ( v14 < 60 )
goto LABEL_80;
}
if ( v14 <= 65 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 200 && 0.0 == *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
goto LABEL_327;
}
LABEL_80:
if ( v14 < 65 )
goto LABEL_84;
}
if ( v14 > 75 )
goto LABEL_85;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_84:
if ( v14 < 75 )
goto LABEL_89;
LABEL_85:
if ( v14 > 85 || *(__int16 *)CPU_FIELD(1154) < 400 || *(_DWORD *)CPU_FIELD(384) == 1 )
{
LABEL_89:
if ( v14 >= 95 && v14 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v15 = 860.0;
v16 = 960.0;
switch ( *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) )
{
case 0xC8:
v17 = v16;
if ( (*(float *)CPU_FIELD(236) <= v16 || *(_BYTE *)CPU_FIELD(260) != 1)
&& (*(float *)CPU_FIELD(236) >= 300.0 || *(_BYTE *)CPU_FIELD(260) != 0xFF) )
{
if ( *(float *)CPU_FIELD(236) > v17 && *(_BYTE *)CPU_FIELD(260) == 1 )
goto LABEL_435;
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
}
v18 = *(_DWORD *)CPU_FIELD(384) == 1;
if ( !v18 )
{
if ( *(float *)CPU_FIELD(236) > v17 && *(_BYTE *)CPU_FIELD(260) == 1 )
goto LABEL_435;
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
}
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
case 0xC9:
goto LABEL_100;
case 0xCA:
goto LABEL_104;
case 0xCD:
if ( (*(float *)CPU_FIELD(236) <= 860.0 || *(_BYTE *)CPU_FIELD(260) != 1)
&& (*(float *)CPU_FIELD(236) >= 400.0 || *(_BYTE *)CPU_FIELD(260) != 0xFF)
|| *(_DWORD *)CPU_FIELD(384) != 1 )
{
goto LABEL_111;
}
*(_DWORD *)CPU_FIELD(1744) = 2;
break;
case 0xD4:
goto LABEL_111;
default:
goto LABEL_350;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
break;
case 0x12F:
v22 = *(_DWORD *)CPU_FIELD(384);
if ( v22 )
{
if ( v22 != 3 && !*(_WORD *)CPU_FIELD(1892) )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
else
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
v23 = *(_WORD *)CPU_FIELD(1892);
if ( v23 < 0 )
goto LABEL_121;
if ( v23 > 30 )
goto LABEL_122;
if ( v117 < 80.0 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
goto LABEL_327;
}
LABEL_121:
if ( v23 >= 30 )
{
LABEL_122:
if ( v23 <= 50 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
goto LABEL_334;
}
if ( v23 <= 75 )
{
v24 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = v24;
*(_DWORD *)CPU_FIELD(1720) = 1;
}
}
break;
case 0x130:
v25 = *(_DWORD *)CPU_FIELD(384);
if ( v25 )
{
if ( v25 != 3 && !*(_WORD *)CPU_FIELD(1892) )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
else
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
v26 = *(_WORD *)CPU_FIELD(1892);
if ( v26 < 0 )
goto LABEL_136;
if ( v26 > 30 )
goto LABEL_137;
if ( *(__int16 *)CPU_FIELD(1154) >= 300 )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_136:
if ( v26 < 30 )
goto LABEL_139;
LABEL_137:
if ( v26 <= 50 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
goto LABEL_322;
LABEL_139:
if ( v26 < 50 )
goto LABEL_142;
}
if ( v26 <= 60 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
goto LABEL_326;
LABEL_142:
if ( v26 < 60 )
goto LABEL_147;
}
if ( v26 <= 65 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 200 && 0.0 == *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
goto LABEL_327;
}
LABEL_147:
if ( v26 < 65 )
goto LABEL_151;
}
if ( v26 > 75 )
goto LABEL_152;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_151:
if ( v26 < 75 )
goto LABEL_156;
LABEL_152:
if ( v26 > 85 || *(__int16 *)CPU_FIELD(1154) < 400 || *(_DWORD *)CPU_FIELD(384) == 1 )
{
LABEL_156:
if ( v26 >= 95 && v26 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
switch ( *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) )
{
case 0xC8:
case 0xC9:
case 0xCA:
goto LABEL_435;
case 0xCD:
case 0xD4:
goto LABEL_413;
default:
goto LABEL_350;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
break;
case 0x131:
v27 = *(_DWORD *)CPU_FIELD(384);
if ( !v27 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v27 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v28 = *(_WORD *)CPU_FIELD(1892);
if ( v28 >= 65 && v28 <= 75 && *(__int16 *)CPU_FIELD(1154) >= 400 )
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
case 0x132:
v29 = *(_DWORD *)CPU_FIELD(384);
if ( v29 )
{
if ( v29 != 3 && !*(_WORD *)CPU_FIELD(1892) )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
else
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
v30 = *(_WORD *)CPU_FIELD(1892);
if ( v30 < 0 )
goto LABEL_178;
if ( v30 > 15 )
goto LABEL_179;
if ( *(float *)CPU_FIELD(240) < (double)*(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
v31 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 1;
*(_DWORD *)CPU_FIELD(1716) = v31;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_178:
if ( v30 < 15 )
goto LABEL_182;
LABEL_179:
if ( v30 > 25 )
goto LABEL_183;
if ( *(__int16 *)CPU_FIELD(1154) >= 300 )
{
v32 = *(_DWORD *)CPU_FIELD(368);
v33 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_32 = (float)((*(float *)(v32 + 236) - *(float *)CPU_FIELD(236)) * (double)v33);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v32 + 240) - *(float *)CPU_FIELD(240), angle_x_32) >= 30;
break;
}
LABEL_182:
if ( v30 < 25 )
goto LABEL_186;
LABEL_183:
if ( v30 > 30 )
goto LABEL_187;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_186:
if ( v30 < 30 )
goto LABEL_191;
LABEL_187:
if ( v30 > 35 )
goto LABEL_192;
if ( *(__int16 *)CPU_FIELD(1154) < 400 || v118 >= 80.0 )
{
LABEL_191:
if ( v30 >= 35 )
{
LABEL_192:
if ( v30 <= 40
&& *(__int16 *)CPU_FIELD(1154) >= 400
&& v118 > 100.0
&& *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) < (double)*(float *)CPU_FIELD(240) )
{
*(_DWORD *)CPU_FIELD(1832) = 64;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
break;
case 0x133:
v34 = *(_DWORD *)CPU_FIELD(384);
if ( !v34 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v34 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v35 = *(_WORD *)CPU_FIELD(1892);
if ( v35 < 0 )
goto LABEL_206;
if ( v35 > 30 )
goto LABEL_207;
if ( *(__int16 *)CPU_FIELD(1154) >= 300 )
{
v36 = *(_DWORD *)CPU_FIELD(368);
v37 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_36 = (float)((*(float *)(v36 + 236) - *(float *)CPU_FIELD(236)) * (double)v37);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v36 + 240) - *(float *)CPU_FIELD(240), angle_x_36) >= 30;
break;
}
LABEL_206:
if ( v35 < 30 )
goto LABEL_211;
LABEL_207:
if ( v35 <= 40 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 300 )
{
v39 = *(_DWORD *)CPU_FIELD(368);
v40 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_39 = (float)((*(float *)(v39 + 236) - *(float *)CPU_FIELD(236)) * (double)v40);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v39 + 240) - *(float *)CPU_FIELD(240), angle_x_39) >= 30;
break;
}
LABEL_211:
if ( v35 < 40 )
goto LABEL_215;
}
if ( v35 > 45 )
goto LABEL_216;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_215:
if ( v35 < 45 )
goto LABEL_220;
LABEL_216:
if ( v35 <= 55 && *(__int16 *)CPU_FIELD(1154) >= 400 && *(_DWORD *)CPU_FIELD(384) == 1 )
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
else
{
LABEL_220:
if ( v35 >= 95
&& v35 <= 100
&& *(char *)CPU_FIELD(1370) > 0
&& (unsigned int)(*(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) - 211) < 2 )
{
goto LABEL_413;
}
}
break;
case 0x134:
v41 = *(_DWORD *)CPU_FIELD(384);
if ( v41 )
{
if ( v41 != 3 && !*(_WORD *)CPU_FIELD(1892) )
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
else
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
v42 = *(_WORD *)CPU_FIELD(1892);
if ( v42 < 0 )
goto LABEL_234;
if ( v42 > 25 )
goto LABEL_235;
if ( *(__int16 *)CPU_FIELD(1154) < 300 )
{
LABEL_234:
if ( v42 >= 25 )
{
LABEL_235:
if ( v42 <= 35 && *(__int16 *)CPU_FIELD(1154) >= 300 )
goto LABEL_326;
}
if ( v42 >= 95 && v42 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v45 = *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211;
goto LABEL_412;
}
}
else
{
v43 = *(_DWORD *)CPU_FIELD(368);
v44 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_43 = (float)((*(float *)(v43 + 236) - *(float *)CPU_FIELD(236)) * (double)v44);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v43 + 240) - *(float *)CPU_FIELD(240), angle_x_43) >= 20;
}
break;
case 0x140:
v46 = *(_DWORD *)CPU_FIELD(384);
if ( !v46 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v46 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
if ( *(_WORD *)CPU_FIELD(1892) <= 0x5Au )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
break;
case 0x141:
v47 = *(_DWORD *)CPU_FIELD(384);
if ( !v47 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v47 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v48 = *(_WORD *)CPU_FIELD(1892);
if ( v48 < 0 )
goto LABEL_264;
if ( v48 <= 50 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
if ( v48 <= 65 )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
if ( v48 <= 80 )
{
v49 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = v49;
*(_DWORD *)CPU_FIELD(1720) = 1;
break;
}
if ( v48 > 90 )
goto LABEL_265;
if ( *(__int16 *)CPU_FIELD(1154) < 400 )
{
LABEL_264:
if ( v48 >= 90 )
{
LABEL_265:
if ( v48 <= 95 && *(__int16 *)CPU_FIELD(1154) >= 400 && 0.0 == *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1724) = 2;
goto LABEL_327;
}
}
}
else
{
LABEL_263:
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
break;
case 0x142:
v50 = *(_DWORD *)CPU_FIELD(384);
if ( !v50 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v50 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v51 = *(_WORD *)CPU_FIELD(1892);
if ( v51 < 50 )
goto LABEL_278;
if ( v51 > 75 )
goto LABEL_279;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_278:
if ( v51 < 75 )
goto LABEL_283;
LABEL_279:
if ( v51 > 85 || *(__int16 *)CPU_FIELD(1154) < 400 || *(_DWORD *)CPU_FIELD(384) == 1 )
{
LABEL_283:
if ( v51 >= 95 && v51 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v15 = 860.0;
v16 = 960.0;
switch ( *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) )
{
case 0xC8:
LABEL_93:
v17 = v16;
if ( (*(float *)CPU_FIELD(236) <= v16 || *(_BYTE *)CPU_FIELD(260) != 1)
&& (*(float *)CPU_FIELD(236) >= 300.0 || *(_BYTE *)CPU_FIELD(260) != 0xFF) )
{
goto LABEL_101;
}
v18 = *(_DWORD *)CPU_FIELD(384) == 1;
goto LABEL_98;
case 0xC9:
LABEL_100:
v17 = v16;
goto LABEL_101;
case 0xCA:
goto LABEL_104;
case 0xCD:
if ( (*(float *)CPU_FIELD(236) <= 860.0 || *(_BYTE *)CPU_FIELD(260) != 1)
&& (*(float *)CPU_FIELD(236) >= 400.0 || *(_BYTE *)CPU_FIELD(260) != 0xFF)
|| *(_DWORD *)CPU_FIELD(384) != 1 )
{
goto LABEL_111;
}
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
case 0xD4:
LABEL_111:
v19 = *(float *)CPU_FIELD(236);
v20 = v19 < v15;
v21 = v19 == v15;
goto LABEL_408;
default:
goto LABEL_350;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
break;
case 0x190:
case 0x191:
v52 = *(_DWORD *)CPU_FIELD(384);
if ( !v52 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v52 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v53 = *(_WORD *)CPU_FIELD(1892);
if ( v53 < 0 )
goto LABEL_302;
if ( v53 <= 10 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
goto LABEL_327;
}
LABEL_302:
if ( v53 < 10 )
goto LABEL_308;
}
if ( v53 > 20 || *(__int16 *)CPU_FIELD(1154) < 400 )
{
LABEL_308:
if ( v53 >= 95 && v53 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v54 = *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) - 202;
if ( !v54 )
goto LABEL_435;
v55 = v54 - 3;
if ( v55 )
{
if ( v55 == 6 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
break;
}
}
else
{
*(_DWORD *)CPU_FIELD(1744) = 2;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 2;
}
break;
case 0x192:
v56 = *(_DWORD *)CPU_FIELD(384);
if ( !v56 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v56 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v57 = *(_WORD *)CPU_FIELD(1892);
if ( v57 < 0 )
goto LABEL_323;
if ( v57 > 10 )
goto LABEL_324;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
LABEL_322:
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_323:
if ( v57 < 10 )
goto LABEL_328;
LABEL_324:
if ( v57 > 20 )
goto LABEL_329;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
LABEL_326:
*(_DWORD *)CPU_FIELD(1732) = 2;
LABEL_327:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 1;
break;
}
LABEL_328:
if ( v57 < 20 )
goto LABEL_335;
LABEL_329:
if ( v57 <= 30 )
{
if ( *(__int16 *)CPU_FIELD(1154) >= 400 && v117 < 450.0 && v118 < 100.0 )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
LABEL_334:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
LABEL_335:
if ( v57 < 30 )
break;
}
if ( v57 <= 45 && *(__int16 *)CPU_FIELD(1154) >= 400 )
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
case 0x194:
case 0x195:
case 0x196:
v58 = *(_DWORD *)CPU_FIELD(384);
if ( !v58 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v58 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v59 = *(_WORD *)CPU_FIELD(1892);
if ( v59 >= 0 && v59 <= 10 && *(__int16 *)CPU_FIELD(1154) >= 400
     && v117 < 500.0 && v118 < 100.0 )
{
v62 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = v62;
LABEL_349:
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
if ( v59 >= 10 && v59 <= 20
&& *(__int16 *)CPU_FIELD(1154) >= 400
&& v118 < 100.0
&& *(float *)CPU_FIELD(240) > *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 1;
break;
}
if ( v59 >= 20 && v59 <= 30 && *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
break;
}
if ( v59 >= 30 && v59 <= 40
&& *(__int16 *)CPU_FIELD(1154) >= 400
&& v118 > 100.0
&& *(float *)CPU_FIELD(240) > *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
if ( v59 >= 95 && v59 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v65 = *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211;
goto LABEL_434;
}
break;
case 0x19A:
case 0x19C:
v66 = *(_DWORD *)CPU_FIELD(384);
if ( !v66 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v66 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v67 = *(_WORD *)CPU_FIELD(1892);
if ( v67 < 50 )
goto LABEL_394;
if ( v67 > 75 )
goto LABEL_395;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_394:
if ( v67 < 75 )
goto LABEL_399;
LABEL_395:
if ( v67 > 80 || *(__int16 *)CPU_FIELD(1154) < 400 || *(_DWORD *)CPU_FIELD(384) == 1 )
{
LABEL_399:
if ( v67 >= 95 && v67 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v17 = 960.0;
switch ( *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) )
{
case 0xC8:
if ( *(float *)CPU_FIELD(236) <= 960.0 || *(_BYTE *)CPU_FIELD(260) != 1 )
{
if ( *(float *)CPU_FIELD(236) >= 300.0 )
goto LABEL_101;
v18 = *(_BYTE *)CPU_FIELD(260) == 0xFF;
LABEL_98:
if ( !v18 )
goto LABEL_101;
}
goto LABEL_99;
case 0xC9:
LABEL_101:
if ( *(float *)CPU_FIELD(236) > v17 && *(_BYTE *)CPU_FIELD(260) == 1 )
goto LABEL_435;
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
case 0xCA:
LABEL_104:
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
case 0xCD:
LABEL_99:
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_350;
case 0xD4:
v68 = *(float *)CPU_FIELD(236);
v20 = v68 < 860.0;
v21 = v68 == 860.0;
LABEL_408:
if ( !v20 && !v21 && *(_BYTE *)CPU_FIELD(260) == 1 )
goto LABEL_413;
if ( *(float *)CPU_FIELD(236) >= 400.0 )
goto LABEL_350;
v45 = *(_BYTE *)CPU_FIELD(260) == 0xFF;
break;
default:
goto LABEL_350;
}
LABEL_412:
if ( v45 )
{
LABEL_413:
v65 = *(_DWORD *)CPU_FIELD(384) == 1;
goto LABEL_434;
}
}
}
else
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
break;
case 0x19E:
case 0x19F:
case 0x1A0:
v69 = *(_DWORD *)CPU_FIELD(384);
if ( !v69 )
{
*(_WORD *)CPU_FIELD(1892) = 0;
}
else if ( v69 != 3 && !*(_WORD *)CPU_FIELD(1892) )
{
*(_WORD *)CPU_FIELD(1892) = selector_random_roll(0x64u);
}
v70 = *(_WORD *)CPU_FIELD(1892);
if ( v70 < 40 )
goto LABEL_423;
if ( v70 > 45 )
goto LABEL_424;
if ( *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
break;
}
LABEL_423:
if ( v70 < 45 )
goto LABEL_428;
LABEL_424:
if ( v70 <= 55 && *(__int16 *)CPU_FIELD(1154) >= 400 && *(_DWORD *)CPU_FIELD(384) == 1 )
{
*(_DWORD *)CPU_FIELD(1832) = 32;
}
else
{
LABEL_428:
if ( v70 >= 95 && v70 <= 100 && *(char *)CPU_FIELD(1370) > 0 )
{
v71 = *(__int16 *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) - 211;
if ( !v71 )
goto LABEL_435;
if ( v71 == 1 )
{
v65 = v118 < 150.0;
LABEL_434:
if ( v65 )
LABEL_435:
*(_DWORD *)CPU_FIELD(1744) = 2;
}
}
}
break;
default:
break;
}
LABEL_350:
if ( *(_WORD *)CPU_FIELD(1894) )
goto LABEL_523;
if ( !*(_WORD *)CPU_FIELD(1900) )
*(_WORD *)CPU_FIELD(1900) = selector_random_roll(0x64u);
v63 = *(_DWORD *)CPU_FIELD(368);
if ( (!( *(float *)CPU_FIELD(236) > (double)*(float *)(v63 + 236) ) || *(_BYTE *)CPU_FIELD(260) != 0xFF)
&& (!( *(float *)CPU_FIELD(236) < (double)*(float *)(v63 + 236) ) || *(_BYTE *)CPU_FIELD(260) != 1) )
{
goto LABEL_523;
}
v64 = *(_WORD *)(v63 + 316);
if ( v64 > 95 && v64 < 140 )
goto LABEL_523;
if ( 0.0 == *(float *)CPU_FIELD(240) )
{
}
else
{
if ( *(float *)(v63 + 240) != 0.0f )
{
if ( *(char *)CPU_FIELD(1370) > 0 )
{
if ( v117 < 150.0 && selector_random_roll(0x3E8u) < 2u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 > 150.0
&& v118 < 200.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 212 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
}
if ( (double)(120 * ((*(float *)CPU_FIELD(244) > 0.0) + 1)) >= v117 )
{
v79 = *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) > (double)*(float *)CPU_FIELD(240)
&& *(float *)CPU_FIELD(248) > 0.0;
if ( (double)(150 * v79 + 100) > v118 && selector_random_roll(0x3E8u) < 0x32u )
goto LABEL_607;
}
if ( v117 > 180.0
|| *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) >= (double)*(float *)CPU_FIELD(240)
|| v118 <= 60.0
|| selector_random_roll(0x3E8u) >= 0x4Bu )
{
if ( v117 > 280.0
|| v117 < 90.0
|| v118 >= 100.0
|| *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) <= (double)*(float *)CPU_FIELD(240)
|| selector_random_roll(0x3E8u) >= 0x4Bu )
{
if ( (double)(180 * (v118 < 200.0) + 120) < v117 && selector_random_roll(0x3E8u) < 0x32u )
{
v81 = *(_DWORD *)CPU_FIELD(368);
v82 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_81 = (float)((*(float *)(v81 + 236) - *(float *)CPU_FIELD(236)) * (double)v82);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v81 + 240) - *(float *)CPU_FIELD(240), angle_x_81) >= 30;
}
if ( v117 > 250.0 && v118 < 200.0 && selector_random_roll(0x3E8u) < 0x14u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1716) = 0;
}
if ( v117 > 150.0 && v117 < 500.0 && v118 < 100.0 && selector_random_roll(0x3E8u) < 0x14u )
{
v83 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1716) = v83;
}
if ( v117 < 300.0
&& v118 > 200.0
&& *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) < (double)*(float *)CPU_FIELD(240)
&& selector_random_roll(0x3E8u) < 0x19u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1716) = 0;
}
}
else
{
v80 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = v80;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
goto LABEL_523;
}
}
else
{
if ( *(char *)CPU_FIELD(1370) > 0 )
{
if ( v117 < 150.0 && selector_random_roll(0x3E8u) < 2u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 > 150.0
&& v118 < 200.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 212 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
}
if ( v117 < 450.0 && v117 > 90.0 && selector_random_roll(0x3E8u) <= 5u && *(__int16 *)CPU_FIELD(1154) >= 600 )
{
*(_DWORD *)CPU_FIELD(1832) = 64;
goto LABEL_523;
}
if ( v117 < 450.0
&& *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) < (double)*(float *)CPU_FIELD(240)
&& selector_random_roll(0x3E8u) <= 7u
&& *(__int16 *)CPU_FIELD(1154) >= 800 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
goto LABEL_523;
}
if ( (double)(120 * ((*(float *)CPU_FIELD(244) > 0.0) + 1)) >= v117 )
{
v76 = *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) > (double)*(float *)CPU_FIELD(240)
&& *(float *)CPU_FIELD(248) > 0.0;
if ( (double)(150 * v76 + 100) > v118 && selector_random_roll(0x3E8u) < 0x32u )
goto LABEL_607;
}
if ( v117 > 180.0
|| *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) >= (double)*(float *)CPU_FIELD(240)
|| selector_random_roll(0x3E8u) >= 0x4Bu )
{
if ( *(__int16 *)CPU_FIELD(1902) <= *(__int16 *)CPU_FIELD(1154) )
{
if ( (double)(180 * (v118 < 200.0) + 120) < v117 && selector_random_roll(0x3E8u) < 0x32u )
{
v77 = *(_DWORD *)CPU_FIELD(368);
v78 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
float angle_x_77 = (float)((*(float *)(v77 + 236) - *(float *)CPU_FIELD(236)) * (double)v78);
*(_DWORD *)CPU_FIELD(1720) = -(__int16)(int)atan2_degrees(
    *(float *)(v77 + 240) - *(float *)CPU_FIELD(240), angle_x_77) >= 30;
}
if ( v117 > 250.0 && v118 < 200.0 && selector_random_roll(0x3E8u) < 0x14u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1716) = 0;
}
if ( v117 < 300.0
&& v118 > 200.0
&& *(float *)(*(_DWORD *)CPU_FIELD(368) + 240) < (double)*(float *)CPU_FIELD(240)
&& selector_random_roll(0x3E8u) < 0x19u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1720) = 1;
*(_DWORD *)CPU_FIELD(1716) = 0;
}
}
goto LABEL_523;
}
}
LABEL_612:
*(_DWORD *)CPU_FIELD(1724) = 2;
goto LABEL_613;
}
if ( 0.0 != *(float *)(v63 + 240) )
{
if ( v117 < 520.0 && v117 > 240.0 && v118 < 250.0 && selector_random_roll(0x3E8u) <= 2u && *(__int16 *)CPU_FIELD(1154) >= 600 )
{
*(_DWORD *)CPU_FIELD(1832) = 64;
goto LABEL_523;
}
if ( *(char *)CPU_FIELD(1370) > 0
&& (v117 < 300.0 && selector_random_roll(0x3E8u) < 5u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 200
|| v117 < 150.0 && selector_random_roll(0x3E8u) < 5u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 201
|| v117 > 200.0 && selector_random_roll(0x3E8u) < 3u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 202
|| v117 > 150.0
&& v118 < 150.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 205
|| v117 < 150.0 && selector_random_roll(0x3E8u) < 2u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211
|| v117 > 150.0
&& v118 < 200.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 212) )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( selector_random_roll(0x3E8u) >= 0x4Bu || v117 >= 200.0 || v117 <= 120.0 || v118 >= 75.0 )
{
if ( *(__int16 *)CPU_FIELD(1902) <= *(__int16 *)CPU_FIELD(1154) )
{
if ( selector_random_roll(0x3E8u) >= 0xAu || *(__int16 *)CPU_FIELD(1154) < 600 || v118 >= 200.0 || v117 >= 450.0 )
{
if ( selector_random_roll(0x3E8u) < 0xAu && *(__int16 *)CPU_FIELD(1154) >= 600 && v118 < 200.0 && v117 < 450.0 )
{
v75 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = v75;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
}
else
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
}
goto LABEL_523;
}
goto LABEL_440;
}
if ( v117 <= 90.0 )
{
if ( selector_random_roll(0x3E8u) < 0x46u )
{
LABEL_607:
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
goto LABEL_523;
}
if ( selector_random_roll(0x3E8u) < 0x46u )
goto LABEL_612;
}
if ( selector_random_roll(0x3E8u) >= 0x4Bu || v117 >= 350.0 || v117 <= 120.0 )
{
if ( *(char *)CPU_FIELD(1370) > 0 )
{
if ( v117 < 300.0 && selector_random_roll(0x3E8u) < 5u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 200 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 < 150.0 && selector_random_roll(0x3E8u) < 5u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 201 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 > 200.0 && selector_random_roll(0x3E8u) < 3u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 202 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 > 150.0
&& v118 < 150.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 205 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 < 150.0 && selector_random_roll(0x3E8u) < 2u && *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 211 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
if ( v117 > 150.0
&& v118 < 200.0
&& selector_random_roll(0x3E8u) < 5u
&& *(_WORD *)reinterpret_cast<FighterSequenceController *>(CPU_FIELD(1372))->entry_at_checked(0) == 212 )
{
*(_DWORD *)CPU_FIELD(1744) = 2;
goto LABEL_523;
}
}
if ( v117 <= 180.0 )
{
if ( v117 >= 90.0 && selector_random_roll(0x3E8u) < 0x32u )
goto LABEL_607;
if ( v117 >= 120.0 && selector_random_roll(0x3E8u) <= 0x32u )
{
v72 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = v72;
*(_DWORD *)CPU_FIELD(1720) = 1;
goto LABEL_523;
}
}
if ( v117 <= 250.0 && v117 >= 90.0 && selector_random_roll(0x3E8u) <= 0x32u )
{
v73 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1724) = 2;
*(_DWORD *)CPU_FIELD(1716) = v73;
*(_DWORD *)CPU_FIELD(1720) = 0;
goto LABEL_523;
}
if ( v117 < 640.0 && v117 > 350.0 && selector_random_roll(0x3E8u) <= 5u && *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 32;
goto LABEL_523;
}
if ( v117 > 90.0 && selector_random_roll(0x3E8u) <= 0xFu && *(__int16 *)CPU_FIELD(1154) >= 400 )
{
*(_DWORD *)CPU_FIELD(1832) = 2;
goto LABEL_523;
}
if ( *(__int16 *)CPU_FIELD(1902) > *(__int16 *)CPU_FIELD(1154) )
goto LABEL_523;
if ( v117 >= 120.0 && selector_random_roll(0x3E8u) <= 5u )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
LABEL_613:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 1;
goto LABEL_523;
}
if ( v117 < 180.0 )
goto LABEL_523;
if ( selector_random_roll(0x3E8u) <= 0xAu )
{
*(_DWORD *)CPU_FIELD(1728) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
goto LABEL_523;
}
if ( v117 < 240.0 )
{
if ( selector_random_roll(0x3E8u) <= 5u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
goto LABEL_613;
}
}
else if ( selector_random_roll(0x3E8u) <= 5u )
{
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = 0;
goto LABEL_523;
}
if ( v117 <= 600.0 && selector_random_roll(0x3E8u) <= 5u )
{
v74 = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1732) = 2;
*(_DWORD *)CPU_FIELD(1716) = v74;
*(_DWORD *)CPU_FIELD(1720) = 0;
}
goto LABEL_523;
}
LABEL_440:
*(_WORD *)CPU_FIELD(1894) = 100;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x14u) + 10;
LABEL_523:
switch ( *(_WORD *)CPU_FIELD(1894) )
{
case 0:
if ( *(__int16 *)CPU_FIELD(1896) > 0 )
return;
v84 = selector_random_roll(0x64u);
*(_WORD *)CPU_FIELD(1898) = v84;
if ( *(float *)CPU_FIELD(240) == 0.0f )
{
}
else
{
v98 = *(_DWORD *)CPU_FIELD(368);
if ( 0.0 == *(float *)(v98 + 240) )
{
v99 = v117;
if ( v117 <= 90.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
goto LABEL_888;
if ( v84 >= 0 && v84 <= 29 && v118 > 200.0 )
{
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
if ( v84 < 30 || v84 > 44 )
{
LABEL_888:
if ( v84 < 45 || v84 > 59 || v118 <= 150.0 )
goto LABEL_1025;
goto LABEL_889;
}
goto LABEL_953;
}
if ( v99 <= 240.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
goto LABEL_900;
if ( v84 >= 0 && v84 <= 29 && v118 > 100.0 )
goto LABEL_960;
if ( v84 < 30 || v84 > 44 )
{
LABEL_900:
if ( v84 >= 45 && v84 <= 54 )
goto LABEL_901;
if ( v84 < 55 )
goto LABEL_SIGNED_RANGE_27;
if ( v84 <= 64 )
goto LABEL_889;
LABEL_SIGNED_RANGE_27:
LABEL_992:
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x28u);
return;
}
LABEL_953:
*(_WORD *)CPU_FIELD(1894) = 11;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
if ( v99 >= 520.0 )
{
if ( v84 < 0 || v84 > 34 )
{
if ( v84 < 35 || v84 > 39 )
goto LABEL_875;
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 10;
}
else
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 20;
}
return;
}
if ( v99 < 240.0 )
return;
if ( v84 < 0 )
goto LABEL_SIGNED_RANGE_01;
if ( v84 > 9 )
goto LABEL_SIGNED_RANGE_01;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0xFu) + 15;
return;
}
LABEL_SIGNED_RANGE_01:
if ( v84 < 10 )
goto LABEL_SIGNED_RANGE_02;
if ( v84 > 19 )
goto LABEL_SIGNED_RANGE_02;
{
*(_WORD *)CPU_FIELD(1894) = 11;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 30;
return;
}
LABEL_SIGNED_RANGE_02:
if ( v84 < 20 )
goto LABEL_SIGNED_RANGE_03;
if ( v84 > 24 )
goto LABEL_SIGNED_RANGE_03;
{
*(_WORD *)CPU_FIELD(1894) = 12;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 20;
return;
}
LABEL_SIGNED_RANGE_03:
if ( v84 < 45 || v84 > 54 )
{
if ( v84 < 55 )
goto LABEL_875;
if ( v84 > 64 )
goto LABEL_875;
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x14u) + 15;
return;
}
LABEL_972:
v93 = *(_BYTE *)CPU_FIELD(260) == 0xFF;
goto LABEL_982;
}
v100 = v117;
if ( v117 > 90.0 )
{
if ( v100 <= 240.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( v84 >= 0 && v84 <= 14 && *(float *)(v98 + 240) < (double)*(float *)CPU_FIELD(240) )
goto LABEL_953;
if ( v84 >= 15 && v84 <= 29 && v118 > 150.0 )
goto LABEL_960;
}
if ( v84 >= 30 && v84 <= 34 )
goto LABEL_960;
if ( v84 >= 35 && v84 <= 44 )
goto LABEL_889;
if ( v84 < 45 || v84 > 47 )
{
if ( v84 < 48 || v84 > 50 )
{
if ( v84 < 51 || v84 > 54 )
goto LABEL_1025;
goto LABEL_969;
}
goto LABEL_989;
}
goto LABEL_986;
}
if ( v100 < 520.0 )
{
if ( v100 < 240.0 )
return;
if ( v84 < 0 )
goto LABEL_SIGNED_RANGE_04;
if ( v84 > 4 )
goto LABEL_SIGNED_RANGE_04;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
LABEL_SIGNED_RANGE_04:
if ( v84 < 5 )
goto LABEL_SIGNED_RANGE_05;
if ( v84 > 9 )
goto LABEL_SIGNED_RANGE_05;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
LABEL_SIGNED_RANGE_05:
if ( v84 < 45 || v84 > 47 )
{
if ( v84 < 48 || v84 > 50 )
{
if ( v84 < 51 || v84 > 54 )
goto LABEL_992;
goto LABEL_969;
}
LABEL_989:
*(_WORD *)CPU_FIELD(1894) = 16;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x14u) + 5;
return;
}
LABEL_986:
*(_WORD *)CPU_FIELD(1894) = 17;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x14u) + 5;
return;
}
if ( v84 >= 0 && v84 < 4 )
goto LABEL_972;
if ( v84 < 4 || v84 > 5 )
goto LABEL_983;
}
else if ( v84 < 0 || v84 > 5 )
{
if ( v118 <= 320.0 )
goto LABEL_1025;
if ( *(float *)(v98 + 240) > (double)*(float *)CPU_FIELD(240) )
{
if ( v84 < 5 )
goto LABEL_SIGNED_RANGE_06;
if ( v84 > 9 )
goto LABEL_SIGNED_RANGE_06;
{
*(_WORD *)CPU_FIELD(1894) = 12;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
LABEL_SIGNED_RANGE_06:
if ( v84 >= 10 && v84 <= 14 )
goto LABEL_953;
if ( v84 >= 15 && v84 <= 24 )
goto LABEL_972;
}
if ( *(float *)(v98 + 240) >= (double)*(float *)CPU_FIELD(240) )
goto LABEL_1025;
if ( v84 < 25 || v84 > 27 )
{
if ( v84 < 28 || v84 > 31 )
{
if ( v84 < 32 || v84 > 35 )
{
if ( v84 < 36 || v84 > 39 )
goto LABEL_1025;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
}
LABEL_969:
*(_WORD *)CPU_FIELD(1894) = 18;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x14u) + 5;
return;
}
goto LABEL_989;
}
goto LABEL_986;
}
LABEL_975:
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
if ( !*(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
}
else
{
if ( v117 <= 90.0 )
{
v95 = v118;
if ( v118 > 100.0 )
{
if ( v84 >= 0 && v84 <= 6 )
goto LABEL_671;
if ( v84 >= 7 && v84 <= 10 && v95 >= 200.0 )
goto LABEL_800;
if ( v84 >= 11 && v84 <= 18 )
goto LABEL_804;
if ( v84 >= 19 && v84 <= 24 && v95 >= 200.0 )
goto LABEL_808;
}
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f)
|| v84 < 25
|| v84 > 49
|| v95 < 250.0 )
{
if ( v84 < 50 )
goto LABEL_SIGNED_RANGE_07;
if ( v84 > 69 )
goto LABEL_SIGNED_RANGE_07;
{
*(_WORD *)CPU_FIELD(1894) = (v89 == 1) + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
LABEL_SIGNED_RANGE_07:
if ( v84 >= 70 && v84 <= 74 )
goto LABEL_889;
goto LABEL_875;
}
{
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
}
if ( v117 <= 240.0 )
{
if ( v84 >= 0 && v84 <= 6 )
goto LABEL_671;
if ( v84 < 7 || v84 > 10 )
{
v96 = v118;
}
else
{
v96 = v118;
if ( v118 >= 200.0 )
goto LABEL_800;
}
if ( v84 >= 11 && v84 <= 18 )
goto LABEL_804;
if ( v84 >= 19 && v84 <= 24 && v96 >= 200.0 )
goto LABEL_808;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 )
{
v97 = v96;
if ( *(float *)CPU_FIELD(236) < 240.0 )
{
LABEL_815:
if ( v84 >= 35 && v84 <= 50 && v97 >= 400.0 )
goto LABEL_788;
LABEL_819:
if ( v84 < 50 || v84 > 69 )
{
if ( v84 < 70 )
goto LABEL_875;
if ( v84 > 74 )
goto LABEL_875;
goto LABEL_889;
}
goto LABEL_725;
}
}
else
{
v97 = v96;
}
if ( v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f )
goto LABEL_819;
goto LABEL_815;
}
if ( v117 >= 520.0 )
{
if ( v84 >= 0 && v84 <= 9 )
goto LABEL_826;
if ( v84 >= 10 && v84 <= 19 )
goto LABEL_829;
if ( v84 >= 20 && v84 <= 24 )
goto LABEL_832;
if ( v84 >= 25 && v84 <= 29 )
goto LABEL_835;
if ( v84 >= 30 && v84 <= 39 )
{
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
if ( v84 < 40 || v84 > 49 )
{
if ( v84 < 50 )
goto LABEL_SIGNED_RANGE_09;
if ( v84 > 54 )
goto LABEL_SIGNED_RANGE_09;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
LABEL_SIGNED_RANGE_09:
if ( v84 < 55 )
goto LABEL_SIGNED_RANGE_10;
if ( v84 > 95 )
goto LABEL_SIGNED_RANGE_10;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 45;
return;
}
LABEL_SIGNED_RANGE_10:
goto LABEL_875;
}
goto LABEL_863;
}
if ( v117 < 240.0 )
return;
if ( v84 >= 0 && v84 <= 6 )
goto LABEL_671;
if ( v84 >= 7 && v84 <= 12 )
goto LABEL_800;
if ( v84 >= 13 && v84 <= 20 )
goto LABEL_804;
if ( v84 >= 21 && v84 <= 30 )
goto LABEL_808;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( v84 < 40 )
goto LABEL_SIGNED_RANGE_11;
if ( v84 > 49 )
goto LABEL_SIGNED_RANGE_11;
{
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
LABEL_SIGNED_RANGE_11:
if ( v84 >= 50 && v84 <= 59 )
{
LABEL_863:
*(_WORD *)CPU_FIELD(1894) = 6;
return;
}
}
if ( v84 < 60 )
goto LABEL_SIGNED_RANGE_13;
if ( v84 > 64 )
goto LABEL_SIGNED_RANGE_13;
{
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 10;
return;
}
LABEL_SIGNED_RANGE_13:
if ( v84 < 65 || v84 > 79 )
{
if ( v84 < 80 )
goto LABEL_SIGNED_RANGE_14;
if ( v84 > 89 )
goto LABEL_SIGNED_RANGE_14;
{
*(_WORD *)CPU_FIELD(1894) = (v89 == 1) + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x28u) + 10;
return;
}
LABEL_SIGNED_RANGE_14:
if ( v84 >= 90 && v84 <= 99 )
*(_WORD *)CPU_FIELD(1894) = (v89 == 1) + 9;
goto LABEL_875;
}
LABEL_901:
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 20;
return;
}
if ( v117 <= 90.0 )
{
if ( v84 >= 0 && v84 <= 9 )
goto LABEL_826;
if ( v84 >= 10 && v84 <= 14 )
goto LABEL_829;
if ( v84 >= 15 && v84 <= 29 )
goto LABEL_832;
if ( v84 >= 30 && v84 <= 39 )
goto LABEL_835;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( v84 >= 40 && v84 <= 44 )
{
LABEL_654:
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
if ( v84 >= 45 && v84 <= 49 )
goto LABEL_658;
}
if ( v84 < 50 || v84 > 74 )
{
if ( v84 >= 75
&& v84 <= 89
&& (v89 == 1 && *(float *)CPU_FIELD(236) >= 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) <= 1040.0f) )
{
goto LABEL_889;
}
LABEL_875:
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0xAu);
return;
}
goto LABEL_725;
LABEL_835:
*(_WORD *)CPU_FIELD(1894) = 8;
return;
LABEL_832:
*(_WORD *)CPU_FIELD(1894) = 5;
return;
LABEL_829:
*(_WORD *)CPU_FIELD(1894) = 7;
return;
LABEL_826:
*(_WORD *)CPU_FIELD(1894) = 4;
return;
}
if ( v117 <= 240.0 )
{
if ( v84 >= 0 && v84 <= 2 )
{
LABEL_671:
*(_WORD *)CPU_FIELD(1894) = 4;
return;
}
if ( v84 < 3 || v84 > 5 )
{
if ( v84 < 6 || v84 > 8 )
{
if ( v84 < 9 || v84 > 11 )
{
if ( v84 < 12 )
goto LABEL_SIGNED_RANGE_17;
if ( v84 > 14 )
goto LABEL_SIGNED_RANGE_17;
{
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
LABEL_SIGNED_RANGE_17:
if ( v84 >= 15 && v84 <= 17 )
goto LABEL_682;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
{
LABEL_691:
if ( v84 < 30 )
goto LABEL_SIGNED_RANGE_18;
if ( v84 > 39 )
goto LABEL_SIGNED_RANGE_18;
{
v90 = v89 == -1;
LABEL_726:
*(_WORD *)CPU_FIELD(1894) = v90 + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
LABEL_SIGNED_RANGE_18:
if ( v84 < 40 || v84 > 54 )
{
if ( v84 < 55 || v84 > 69 )
{
if ( v84 < 70 || v84 > 89 )
goto LABEL_875;
LABEL_889:
*(_WORD *)CPU_FIELD(1894) = (v89 == 1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
LABEL_725:
v90 = v89 == 1;
goto LABEL_726;
}
LABEL_788:
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 15;
return;
}
if ( v84 < 20 || v84 > 24 )
{
if ( v84 < 25 || v84 > 29 )
goto LABEL_691;
LABEL_757:
*(_WORD *)CPU_FIELD(1894) = 6;
return;
}
LABEL_860:
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
LABEL_808:
*(_WORD *)CPU_FIELD(1894) = 8;
return;
}
LABEL_804:
*(_WORD *)CPU_FIELD(1894) = 5;
return;
}
LABEL_800:
*(_WORD *)CPU_FIELD(1894) = 7;
return;
}
if ( v117 >= 520.0 )
{
if ( v84 >= 0 && v84 <= 4 )
goto LABEL_671;
if ( v84 >= 5 && v84 <= 9 )
goto LABEL_800;
if ( v84 >= 10 && v84 <= 14 )
goto LABEL_804;
if ( v84 >= 15 && v84 <= 17 )
goto LABEL_808;
if ( v84 < 18 )
goto LABEL_SIGNED_RANGE_19;
if ( v84 > 24 )
goto LABEL_SIGNED_RANGE_19;
{
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
LABEL_SIGNED_RANGE_19:
if ( v84 < 25 )
goto LABEL_SIGNED_RANGE_20;
if ( v84 > 29 )
goto LABEL_SIGNED_RANGE_20;
{
LABEL_658:
*(_WORD *)CPU_FIELD(1894) = 6;
return;
}
LABEL_SIGNED_RANGE_20:
if ( v84 < 30 )
goto LABEL_SIGNED_RANGE_21;
if ( v84 > 44 )
goto LABEL_SIGNED_RANGE_21;
{
*(_WORD *)CPU_FIELD(1894) = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 30;
return;
}
LABEL_SIGNED_RANGE_21:
if ( v84 < 45 )
goto LABEL_SIGNED_RANGE_22;
if ( v84 > 79 )
goto LABEL_SIGNED_RANGE_22;
{
*(_WORD *)CPU_FIELD(1894) = 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 60;
return;
}
LABEL_SIGNED_RANGE_22:
if ( v84 >= 80 && v84 <= 82 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) >= 240.0 )
goto LABEL_725;
if ( v89 == -1 && *(float *)CPU_FIELD(236) <= 1040.0f )
goto LABEL_725;
}
if ( v84 < 83 || v84 > 89 )
goto LABEL_875;
v91 = *(_BYTE *)CPU_FIELD(260);
if ( v91 == 1 && *(float *)CPU_FIELD(236) >= 240.0 )
{
v93 = 1;
LABEL_982:
*(_WORD *)CPU_FIELD(1894) = v93 + 9;
LABEL_983:
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
return;
}
if ( v91 != -1 || *(float *)CPU_FIELD(236) > 1040.0f )
goto LABEL_875;
v93 = 0;
goto LABEL_982;
}
if ( v117 >= 240.0 )
{
if ( v84 >= 0 && v84 <= 2 )
goto LABEL_671;
if ( v84 >= 3 && v84 <= 5 )
goto LABEL_800;
if ( v84 >= 6 && v84 <= 8 )
goto LABEL_804;
if ( v84 >= 9 && v84 <= 11 )
goto LABEL_808;
if ( v84 < 12 )
goto LABEL_SIGNED_RANGE_24;
if ( v84 > 15 )
goto LABEL_SIGNED_RANGE_24;
{
*(_WORD *)CPU_FIELD(1894) = 3;
return;
}
LABEL_SIGNED_RANGE_24:
if ( v84 < 16 )
goto LABEL_SIGNED_RANGE_25;
if ( v84 > 18 )
goto LABEL_SIGNED_RANGE_25;
{
LABEL_682:
*(_WORD *)CPU_FIELD(1894) = 6;
return;
}
LABEL_SIGNED_RANGE_25:
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( v84 >= 20 && v84 <= 29 )
goto LABEL_860;
if ( v84 >= 30 && v84 <= 39 )
{
*(_WORD *)CPU_FIELD(1894) = 6;
return;
}
}
if ( v84 < 40 )
goto LABEL_SIGNED_RANGE_26;
if ( v84 > 54 )
goto LABEL_SIGNED_RANGE_26;
{
v94 = v89 == -1;
goto LABEL_766;
}
LABEL_SIGNED_RANGE_26:
if ( v84 < 55 || v84 > 79 )
{
if ( v84 < 80 || v84 > 84 )
{
if ( v84 < 85 || v84 > 99 )
goto LABEL_875;
goto LABEL_889;
}
v94 = v89 == 1;
LABEL_766:
*(_WORD *)CPU_FIELD(1894) = v94 + 1;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu) + 10;
return;
}
LABEL_960:
*(_WORD *)CPU_FIELD(1894) = (v89 == -1) + 9;
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x1Eu);
}
return;
case 1:
v101 = *(__int16 *)CPU_FIELD(1896) <= 0;
*(_DWORD *)CPU_FIELD(1716) = 1;
if ( v101 )
{
*(_WORD *)CPU_FIELD(1894) = 0;
if ( selector_random_roll(0x64u) <= 0xAu )
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);
}
return;
case 2:
v101 = *(__int16 *)CPU_FIELD(1896) <= 0;
*(_DWORD *)CPU_FIELD(1716) = -1;
if ( v101 )
{
LABEL_994:
*(_WORD *)CPU_FIELD(1894) = 0;
if ( selector_random_roll(0x64u) <= 0xAu )
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);
}
return;
case 3:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 4:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 5:
*(_DWORD *)CPU_FIELD(1716) = 1;
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 6:
*(_DWORD *)CPU_FIELD(1828) = 16;
goto LABEL_1003;
case 7:
*(_DWORD *)CPU_FIELD(1828) = 4;
goto LABEL_1003;
case 8:
*(_DWORD *)CPU_FIELD(1828) = 8;
LABEL_1003:
if ( !(*(float *)CPU_FIELD(240) > 0.0f) )
return;
goto LABEL_1023;
case 9:
v102 = *(_BYTE *)CPU_FIELD(260);
v103 = v102 != 1;
v104 = v102;
v105 = *(_WORD *)CPU_FIELD(316);
*(_DWORD *)CPU_FIELD(1716) = v104;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1828) = v103 + 1;
if ( v105 == 200 )
goto LABEL_1022;
if ( v105 == 202 )
goto LABEL_1022;
goto LABEL_1008;
case 0xA:
v107 = *(_BYTE *)CPU_FIELD(260);
v108 = -v107;
v18 = v107 == -1;
v109 = *(_WORD *)CPU_FIELD(316);
*(_DWORD *)CPU_FIELD(1716) = v108;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1828) = !v18 + 1;
if ( v109 == 201 )
goto LABEL_1022;
if ( v109 == 203 )
goto LABEL_1022;
goto LABEL_1008;
case 0xB:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xC:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xD:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xE:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
goto LABEL_1016;
case 0xF:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
LABEL_1016:
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0x10:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
goto LABEL_1020;
case 0x11:
*(_DWORD *)CPU_FIELD(1716) = 0;
goto LABEL_1020;
case 0x12:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
LABEL_1020:
*(_DWORD *)CPU_FIELD(1720) = 1;
*(_DWORD *)CPU_FIELD(1736) = 1;
LABEL_1021:
if ( *(_WORD *)CPU_FIELD(316) == 214 )
{
LABEL_1022:
if ( *(__int16 *)CPU_FIELD(1896) <= 0 )
{
LABEL_1023:
*(_WORD *)CPU_FIELD(1894) = 0;
if ( selector_random_roll(0x64u) > 0x64u )
return;
goto LABEL_1025;
LABEL_1025:
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);
}
}
else
{
LABEL_1008:
*(_WORD *)CPU_FIELD(1894) = 0;
}
return;
case 0x64:
v110 = *(_BYTE *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1716) = v110;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1724) = 0;
v101 = *(__int16 *)CPU_FIELD(1896) <= 0;
*(_DWORD *)CPU_FIELD(1828) = (v110 != 1) + 1;
*(_DWORD *)CPU_FIELD(1728) = 0;
*(_DWORD *)CPU_FIELD(1732) = 0;
*(_DWORD *)CPU_FIELD(1736) = 0;
if ( v101 )
{
*(_WORD *)CPU_FIELD(1894) = 0;
if ( selector_random_roll(0x64u) <= 0x64u )
*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);
return;
}
if ( *(_WORD *)CPU_FIELD(316) == 200 && v117 < 220.0 )
*(_DWORD *)CPU_FIELD(1724) = 2;
return;
default:
return;
}
}
#undef CPU_FIELD

} // namespace th105
