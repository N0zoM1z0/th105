namespace th105 {

// Current CInfoManagerStory construction places this physical record at +0x498.
// The only lifetime-owned state needed here is the five retained effect pointers
// at +0xD8..+0xE8; each referenced object keeps its ownership count at +0x158.
struct BattleInfoEffectRef {
    unsigned char storage_000[0x158];
    int ref_count_158;
};

struct BattleInfoRecordF8Lifetime {
    unsigned char observed_prefix_000[0xD8];
    BattleInfoEffectRef *effect_d8;
    BattleInfoEffectRef *effect_dc;
    BattleInfoEffectRef *effect_e0;
    BattleInfoEffectRef *effect_e4;
    BattleInfoEffectRef *effect_e8;

    BattleInfoRecordF8Lifetime();
    ~BattleInfoRecordF8Lifetime();
};

BattleInfoRecordF8Lifetime::BattleInfoRecordF8Lifetime()
{
    effect_d8 = 0;
    effect_dc = 0;
    effect_e0 = 0;
    effect_e4 = 0;
    effect_e8 = 0;
}

BattleInfoRecordF8Lifetime::~BattleInfoRecordF8Lifetime()
{
    if (effect_d8 != 0) {
        --effect_d8->ref_count_158;
        effect_d8 = 0;
    }
    if (effect_dc != 0) {
        --effect_dc->ref_count_158;
        effect_dc = 0;
    }
    if (effect_e0 != 0) {
        --effect_e0->ref_count_158;
        effect_e0 = 0;
    }
    if (effect_e4 != 0) {
        --effect_e4->ref_count_158;
        effect_e4 = 0;
    }
    if (effect_e8 != 0) {
        --effect_e8->ref_count_158;
        effect_e8 = 0;
    }
}

} // namespace th105
