#include <stddef.h>
namespace th105 {
struct FighterCommandFlagsView {
    unsigned char reserved_000[0x724];
    unsigned flags_primary_724;
    unsigned flags_secondary_728;
    unsigned char match_command_463500(const char *pattern, int length, int window);
    unsigned char build_command_flags_476b10();
};
typedef char FighterCommandFlagsView_secondary_off[offsetof(FighterCommandFlagsView, flags_secondary_728)==0x728?1:-1];
unsigned char FighterCommandFlagsView::build_command_flags_476b10()
{
    flags_primary_724=0; flags_secondary_728=0;
    if(match_command_463500("NRNR",4,15)) flags_primary_724|=1;
    if(match_command_463500("NLNL",4,15)) flags_primary_724|=2;
    if(match_command_463500("N09",3,20)) flags_primary_724|=0x10;
    if(match_command_463500("N07",3,20)) flags_primary_724|=8;
    if(match_command_463500("N08",3,20)) flags_primary_724|=4;
    if(match_command_463500("DD",2,15)) flags_primary_724|=0x20;
    unsigned char r=match_command_463500("421X",4,20); if(r) flags_secondary_728|=0x1000u<<(r-1);
    r=match_command_463500("214X",4,20); if(r) flags_secondary_728|=0x10u<<(r-1);
    r=match_command_463500("412X",4,20); if(r) flags_secondary_728|=0x10000u<<(r-1);
    r=match_command_463500("623X",4,20); if(r) flags_secondary_728|=0x100u<<(r-1);
    r=match_command_463500("236X",4,20); if(r) flags_secondary_728|=1u<<(r-1);
    r=match_command_463500("4136X",5,25); if(r) flags_secondary_728|=0x100000u<<(r-1);
    r=match_command_463500("6314X",5,25); if(r) flags_secondary_728|=0x1000000u<<(r-1);
    r=match_command_463500("2N2X",4,15); if(r) flags_secondary_728|=0x10000000u<<(r-1);
    return r;
}
}
