#include <stddef.h>
#include <deque>
namespace th105 {

extern const unsigned char g_command_pattern_map_left[];
extern const unsigned char g_command_pattern_map_right[];

struct FighterCommandFlagsView {
    unsigned char reserved_000[0x104];
    signed char facing_104;
    unsigned char reserved_105[0x60b];
    std::deque<short> input_history_710;
    unsigned flags_primary_724;
    unsigned flags_secondary_728;
    unsigned char match_command_463500(const char *pattern, int length, int window);
    unsigned char build_command_flags_476b10();
};
typedef char FighterCommandFlagsView_history_off[offsetof(FighterCommandFlagsView, input_history_710)==0x710?1:-1];
typedef char FighterCommandFlagsView_secondary_off[offsetof(FighterCommandFlagsView, flags_secondary_728)==0x728?1:-1];

unsigned char FighterCommandFlagsView::match_command_463500(
    const char *pattern,
    int length,
    int window)
{
    typedef std::deque<short>::const_iterator InputIterator;

    const std::deque<short> &history = input_history_710;
    InputIterator cursor = history.end() - static_cast<signed char>(window);
    char translated[20];

    int i = 0;
    if (facing_104 > 0) {
        if (static_cast<signed char>(length) > 0) {
            do {
                translated[i] = g_command_pattern_map_right[
                    static_cast<signed char>(pattern[i])];
                ++i;
            } while (i < static_cast<signed char>(length));
        }
    } else if (static_cast<signed char>(length) > 0) {
        do {
            translated[i] = g_command_pattern_map_left[
                static_cast<signed char>(pattern[i])];
            ++i;
        } while (i < static_cast<signed char>(length));
    }

    int pattern_index = 0;
    while (cursor != history.end()) {
        unsigned char token = translated[pattern_index];

        if (token == 0x0b) {
            if ((static_cast<unsigned char>(*cursor) & 0x08) != 0) {
                ++pattern_index;
                if (pattern_index == static_cast<signed char>(length))
                    return 1;
            }
        } else if (token < 0x10) {
            if ((static_cast<unsigned char>(*cursor) & 0x0f) == token) {
                ++pattern_index;
                if (pattern_index == static_cast<signed char>(length))
                    return 1;

                token = translated[pattern_index];
                if (token >= 0x10 &&
                    pattern_index + 1 == static_cast<signed char>(length)) {
                    if (token != 0xf0) {
                        if ((static_cast<unsigned char>(*cursor) & 0xf0) == token) {
                            ++pattern_index;
                            if (pattern_index == static_cast<signed char>(length))
                                return 1;
                        }
                    } else if ((static_cast<unsigned char>(*cursor) & 0xf0) != 0) {
                        if ((static_cast<unsigned char>(*cursor) & 0x10) != 0)
                            return 1;
                        if ((static_cast<unsigned char>(*cursor) & 0x20) != 0)
                            return 2;
                        if ((static_cast<unsigned char>(*cursor) & 0x40) != 0)
                            return 3;
                        if ((static_cast<unsigned char>(*cursor) & 0x80) != 0)
                            return 4;
                    }
                }
            } else if ((static_cast<unsigned char>(*cursor) & 0xf0) != 0) {
                pattern_index = 0;
            }
        } else if (token != 0xf0) {
            if ((static_cast<unsigned char>(*cursor) & 0xf0) == token) {
                ++pattern_index;
                if (pattern_index == static_cast<signed char>(length))
                    return 1;
            }
        } else if ((static_cast<unsigned char>(*cursor) & 0xf0) != 0) {
            ++pattern_index;
            if (pattern_index == static_cast<signed char>(length)) {
                if ((static_cast<unsigned char>(*cursor) & 0x10) != 0)
                    return 1;
                if ((static_cast<unsigned char>(*cursor) & 0x20) != 0)
                    return 2;
                if ((static_cast<unsigned char>(*cursor) & 0x40) != 0)
                    return 3;
                if ((static_cast<unsigned char>(*cursor) & 0x80) != 0)
                    return 4;
            }
        }
        ++cursor;
    }
    return 0;
}

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
