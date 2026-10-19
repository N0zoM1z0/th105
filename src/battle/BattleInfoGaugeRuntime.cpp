#include "InfoManagerResources.hpp"

#include <new>

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

// Live binding receiver at UI-object +0x18; gauge slot at receiver +0xA0.
// This bounded view does not assign the original UI class name.
struct GaugeBindingView {
    unsigned char reserved_000[0xa0];
    void *gauge_a0;
};

struct GaugeUiObjectView {
    unsigned char reserved_000[0x18];
    GaugeBindingView binding_18;
};

struct FighterGaugeView {
    unsigned char reserved_000[0x174];
    short primary_value_174;
    short primary_span_176;
    unsigned char reserved_178[0x304];
    short secondary_value_47c;
    unsigned char reserved_47e[0x04];
    short group24_values_482[3];
    short group38_value_488;
    unsigned char reserved_48a[0xce];
    short group88_value_558;
};

static void release_gauge(GaugeBindingView *object)
{
    if (object->gauge_a0 != 0)
        ::operator delete(object->gauge_a0);
}

void BattleInfoRecordF8::bind_fighter_46fa90(Fighter *fighter)
{
    BattleInfoRecordF8 *record = this;
    FighterGaugeView *values = reinterpret_cast<FighterGaugeView *>(fighter);
    record->fighter_18 = fighter;
    record->gauge_0c = values->primary_value_174;
    record->gauge_10 = values->secondary_value_47c;

    GaugeBindingView *primary =
        &reinterpret_cast<GaugeUiObjectView *>(record->primary_1c)->binding_18;
    float primary_span = static_cast<float>(values->primary_span_176);
    release_gauge(primary);
    primary->gauge_a0 = new TGageValue<int *>(&record->gauge_0c, 0.0f, primary_span);

    GaugeBindingView *secondary =
        &reinterpret_cast<GaugeUiObjectView *>(record->secondary_20)->binding_18;
    float secondary_span = static_cast<float>(
        reinterpret_cast<FighterGaugeView *>(record->fighter_18)->primary_span_176);
    release_gauge(secondary);
    secondary->gauge_a0 = new TGageValue<int *>(&record->gauge_10, 0.0f, secondary_span);

    for (int i = 0; i < 5; ++i) {
        double start = static_cast<double>(i) * 200.0;
        float start_value = static_cast<float>(start);
        GaugeBindingView *group24 =
            &reinterpret_cast<GaugeUiObjectView *>(record->group_24[i])->binding_18;
        short *value24 = &reinterpret_cast<FighterGaugeView *>(
            record->fighter_18)->group24_values_482[0];
        release_gauge(group24);
        group24->gauge_a0 = new TGageValue<short *>(
            value24, start_value, static_cast<float>(start + 200.0));

        GaugeBindingView *group38 =
            &reinterpret_cast<GaugeUiObjectView *>(record->group_38[i])->binding_18;
        short *value38 = &reinterpret_cast<FighterGaugeView *>(
            record->fighter_18)->group38_value_488;
        release_gauge(group38);
        group38->gauge_a0 = new TGageValue<short *>(value38, 0.0f, 4800.0f);
    }

    for (int i = 0; i < 5; ++i) {
        GaugeBindingView *group88 =
            &reinterpret_cast<GaugeUiObjectView *>(record->group_88[i])->binding_18;
        short *value88 = &reinterpret_cast<FighterGaugeView *>(
            record->fighter_18)->group88_value_558;
        release_gauge(group88);
        group88->gauge_a0 = new TGageValue<short *>(value88, 0.0f, 500.0f);
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

typedef char GaugeBindingPointerOffset[
    offsetof(GaugeBindingView, gauge_a0) == 0xa0 ? 1 : -1];
typedef char GaugeBindingReceiverOffset[
    offsetof(GaugeUiObjectView, binding_18) == 0x18 ? 1 : -1];
typedef char FighterSecondaryValueOffset[
    offsetof(FighterGaugeView, secondary_value_47c) == 0x47c ? 1 : -1];

typedef char TGageValueIntPtrSize[sizeof(TGageValue<int *>) == 0x10 ? 1 : -1];
typedef char TGageValueShortPtrSize[sizeof(TGageValue<short *>) == 0x10 ? 1 : -1];

} // namespace th105
