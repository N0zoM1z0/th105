#include <deque>
#include "YoumuObjectRecords.hpp"

namespace th105 {

struct YoumuHistoryBaseView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    signed char facing_104;
    unsigned char unknown_105[3];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x0c];
    float field_11c;
    float field_120;
    float field_124;
    float field_128;
    float field_12c;
    unsigned char unknown_130[0x28];
    unsigned record_identifier_158;
    unsigned char unknown_15c[0x648];

    void update_common_history();
};

typedef char YoumuHistoryBaseView_size[
    sizeof(YoumuHistoryBaseView) == 0x7a4 ? 1 : -1];

struct YoumuHistoryView : YoumuHistoryBaseView {
    YoumuObjectRecord record_7a4;
    std::deque<YoumuObjectRecord> records_7d0;

    void update_history();
};

typedef char YoumuHistoryRecordOffset[
    offsetof(YoumuHistoryView, record_7a4) == 0x7a4 ? 1 : -1];
typedef char YoumuHistoryDequeOffset[
    offsetof(YoumuHistoryView, records_7d0) == 0x7d0 ? 1 : -1];

void YoumuHistoryView::update_history()
{
    record_7a4.identifier_00 = record_identifier_158;
    record_7a4.x_04 = x_ec;
    record_7a4.y_08 = y_f0;
    record_7a4.field_0c = field_108;
    record_7a4.field_10 = field_10c;
    record_7a4.field_14 = field_11c;
    record_7a4.field_18 = field_120;
    record_7a4.field_1c = field_124;
    record_7a4.field_20 = field_128;
    record_7a4.field_24 = field_12c;
    record_7a4.facing_28 = static_cast<unsigned char>(facing_104);
    records_7d0.push_front(record_7a4);
    if (records_7d0.size() > 60)
        records_7d0.pop_back();
    record_7a4.phase_29 = 0;
    update_common_history();
}

} // namespace th105
