#include "InfoManagerResources.hpp"

#include <stdlib.h>

namespace th105 {

template <typename T>
class TGageValue {
public:
    TGageValue(T target, float start, float span)
        : target_04(target), start_08(start), span_0c(span - start)
    {
    }

    virtual float value();

    T target_04;
    float start_08;
    float span_0c;
};

template <typename T>
float TGageValue<T>::value()
{
    return (static_cast<float>(*target_04) - start_08) / span_0c;
}

template class TGageValue<int *>;
template class TGageValue<short *>;


struct UiEnabledView {
    unsigned char reserved_000[0x14];
    unsigned char enabled_14;
};

struct GaugeUiObjectView {
    unsigned char reserved_000[0xb8];
    void *gauge_b8;
};

struct FighterGaugeView {
    unsigned char reserved_000[0x174];
    short primary_value_174;
    short primary_span_176;
    unsigned char reserved_178[0x304];
    int secondary_value_47c;
    unsigned char reserved_480[0x02];
    short group24_values_482[3];
    short group38_value_488;
    unsigned char reserved_48a[0xce];
    short group88_value_558;
};

static void replace_gauge(GaugeUiObjectView *object, void *gauge)
{
    if (object->gauge_b8 != 0)
        free(object->gauge_b8);
    object->gauge_b8 = gauge;
}

void BattleInfoRecordF8::bind_fighter_46fa90(Fighter *fighter)
{
    BattleInfoRecordF8 *record = this;
    FighterGaugeView *values = reinterpret_cast<FighterGaugeView *>(fighter);
    record->fighter_18 = fighter;
    record->gauge_0c = values->primary_value_174;
    record->gauge_10 = values->secondary_value_47c;

    replace_gauge(
        reinterpret_cast<GaugeUiObjectView *>(record->primary_1c),
        new TGageValue<int *>(&record->gauge_0c, 0.0f,
                              static_cast<float>(values->primary_span_176)));
    replace_gauge(
        reinterpret_cast<GaugeUiObjectView *>(record->secondary_20),
        new TGageValue<int *>(&record->gauge_10, 0.0f,
                              static_cast<float>(values->primary_span_176)));

    unsigned char *fighter_bytes = reinterpret_cast<unsigned char *>(fighter);
    for (int i = 0; i < 5; ++i) {
        float start = static_cast<float>(i * 200);
        replace_gauge(
            reinterpret_cast<GaugeUiObjectView *>(record->group_24[i]),
            new TGageValue<short *>(
                reinterpret_cast<short *>(fighter_bytes + 0x482), start, start + 200.0f));
        replace_gauge(
            reinterpret_cast<GaugeUiObjectView *>(record->group_38[i]),
            new TGageValue<short *>(
                reinterpret_cast<short *>(fighter_bytes + 0x488), 0.0f, 4800.0f));
    }

    for (int i = 0; i < 5; ++i) {
        replace_gauge(
            reinterpret_cast<GaugeUiObjectView *>(record->group_88[i]),
            new TGageValue<short *>(
                reinterpret_cast<short *>(fighter_bytes + 0x558), 0.0f, 500.0f));
        if (record->owned_effect_d8[i] != 0) {
            --*reinterpret_cast<int *>(
                reinterpret_cast<unsigned char *>(record->owned_effect_d8[i]) + 0x158);
            record->owned_effect_d8[i] = 0;
        }
    }

    if (record->tail_ec != 0)
        reinterpret_cast<UiEnabledView *>(record->tail_ec)->enabled_14 = 0;
    if (record->tail_f0 != 0)
        reinterpret_cast<UiEnabledView *>(record->tail_f0)->enabled_14 = 0;
    if (record->tail_f4 != 0)
        reinterpret_cast<UiEnabledView *>(record->tail_f4)->enabled_14 = 0;
}

typedef char TGageValueIntPtrSize[sizeof(TGageValue<int *>) == 0x10 ? 1 : -1];
typedef char TGageValueShortPtrSize[sizeof(TGageValue<short *>) == 0x10 ? 1 : -1];

} // namespace th105
