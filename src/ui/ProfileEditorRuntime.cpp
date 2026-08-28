#include "ProfileMenu.hpp"

namespace th105 {

extern int g_profile_editor_record_limit;

void ProfileEditor168::initialize(void *records, int record_limit)
{
    source_008 = records;
    record_limit_164 = record_limit;
    g_profile_editor_record_limit = record_limit;
    if (record_limit >= 1023)
        g_profile_editor_record_limit = 1023;

    unsigned char *record = static_cast<unsigned char *>(source_008);
    width_154 = *reinterpret_cast<int *>(record + 0x114);
    record += 0x0c;
    x_158 = *reinterpret_cast<int *>(record + 0x118) + record[0x111];
    y_15c = *reinterpret_cast<int *>(record + 0x11c) + record[0x111];
    state_160 = 0;
}

} // namespace th105
