namespace th105 {
struct Fighter;
struct SceneRendererFighterPairView { unsigned char reserved_000[0x0c]; Fighter *fighters_0c[2]; };
extern SceneRendererFighterPairView *g_scene_renderer;
struct InfoEffectManagerReleaseView { void release_all_46eeb0(); };
struct InfoShortRecordBindView { void bind_46a620(void *combo, Fighter *fighter); };
struct BattleInfoRecordBindView { void bind_fighter_46fa90(Fighter *fighter); };
struct InfoLongRecordBindView { void bind_432550(void *resource, int side); };
struct BattleInfoRecordEffectView { void emit_group_effect_46f9f0(int effect_id, int index); };
struct CInfoManagerBaseBindView { void bind_fighters_46ef40(); };
struct CInfoManagerNormalEffectView { void emit_effect_46f820(int effect_id, int record_index, int group_index); };
void CInfoManagerBaseBindView::bind_fighters_46ef40()
{
    unsigned char *self = reinterpret_cast<unsigned char *>(this);
    *reinterpret_cast<int *>(self + 0x494) = 0;
    *reinterpret_cast<int *>(self + 0x484) = 0;
    reinterpret_cast<InfoEffectManagerReleaseView *>(self + 0x08)->release_all_46eeb0();
    Fighter *fighters[2];
    for (int i = 0; i < 2; ++i) {
        fighters[i] = g_scene_renderer->fighters_0c[i];
        reinterpret_cast<InfoShortRecordBindView *>(self + 0x16c + i * 0x34)->bind_46a620(self + 0x100, fighters[i]);
        reinterpret_cast<BattleInfoRecordBindView *>(self + 0x498 + i * 0xf8)->bind_fighter_46fa90(fighters[i]);
        reinterpret_cast<InfoLongRecordBindView *>(self + 0x1d4 + i * 0x154)->bind_432550(reinterpret_cast<unsigned char *>(fighters[i]) + 0x4f0, i);
        *reinterpret_cast<void **>(self + 0x47c + i * 4) = reinterpret_cast<unsigned char *>(fighters[i]) + 0x33c;
    }
}
void CInfoManagerNormalEffectView::emit_effect_46f820(int effect_id, int record_index, int group_index)
{
    reinterpret_cast<BattleInfoRecordEffectView *>(reinterpret_cast<unsigned char *>(this) + 0x498 + record_index * 0xf8)->emit_group_effect_46f9f0(effect_id, group_index);
}
}
