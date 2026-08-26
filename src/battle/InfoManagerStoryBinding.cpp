namespace th105 {
struct Fighter;
struct SceneRendererFighterPairView { unsigned char reserved_000[0x0c]; Fighter *fighters_0c[2]; };
extern SceneRendererFighterPairView *g_scene_renderer;
struct InfoEffectManagerReleaseView { void release_all_46eeb0(); };
struct InfoShortRecordBindView { void bind_46a620(void *combo, Fighter *fighter); };
struct BattleInfoRecordBindView { void bind_fighter_46fa90(Fighter *fighter); };
struct BattleInfoStoryRecordView { void attach_story_fighter_471be0(Fighter *fighter); };
struct InfoLongRecordBindView { void bind_432550(void *resource, int side); };
struct BattleInfoRecordEffectView { void emit_group_effect_46f9f0(int effect_id, int index); };
struct CInfoManagerStoryBindingView {
    void refresh_roster_state_471ec0();
    void bind_fighters_471f10();
    void emit_effect_472060(int effect_id, int side, int index);
};
void CInfoManagerStoryBindingView::refresh_roster_state_471ec0()
{
    unsigned char *self = reinterpret_cast<unsigned char *>(this);
    Fighter *fighter = g_scene_renderer->fighters_0c[1];
    reinterpret_cast<InfoShortRecordBindView *>(self + 0x1a0)->bind_46a620(self + 0x100, fighter);
    *reinterpret_cast<void **>(self + 0x480) = reinterpret_cast<unsigned char *>(fighter) + 0x33c;
    reinterpret_cast<BattleInfoStoryRecordView *>(self + 0x590)->attach_story_fighter_471be0(fighter);
    reinterpret_cast<InfoLongRecordBindView *>(self + 0x328)->bind_432550(reinterpret_cast<unsigned char *>(fighter) + 0x4f0, 1);
}
void CInfoManagerStoryBindingView::bind_fighters_471f10()
{
    unsigned char *self = reinterpret_cast<unsigned char *>(this);
    *reinterpret_cast<int *>(self + 0x484) = 0;
    reinterpret_cast<InfoEffectManagerReleaseView *>(self + 0x08)->release_all_46eeb0();
    Fighter *fighters[2];
    for (int i = 0; i < 2; ++i) {
        fighters[i] = g_scene_renderer->fighters_0c[i];
        reinterpret_cast<InfoShortRecordBindView *>(self + 0x16c + i * 0x34)->bind_46a620(self + 0x100, fighters[i]);
        *reinterpret_cast<void **>(self + 0x47c + i * 4) = reinterpret_cast<unsigned char *>(fighters[i]) + 0x33c;
    }
    reinterpret_cast<BattleInfoRecordBindView *>(self + 0x498)->bind_fighter_46fa90(fighters[0]);
    reinterpret_cast<InfoLongRecordBindView *>(self + 0x1d4)->bind_432550(reinterpret_cast<unsigned char *>(fighters[0]) + 0x4f0, 0);
    reinterpret_cast<BattleInfoStoryRecordView *>(self + 0x590)->attach_story_fighter_471be0(fighters[1]);
    reinterpret_cast<InfoLongRecordBindView *>(self + 0x328)->bind_432550(reinterpret_cast<unsigned char *>(fighters[1]) + 0x4f0, 1);
    *reinterpret_cast<int *>(self + 0x494) = 30;
}
void CInfoManagerStoryBindingView::emit_effect_472060(int effect_id, int side, int index)
{
    if (side == 0)
        reinterpret_cast<BattleInfoRecordEffectView *>(reinterpret_cast<unsigned char *>(this) + 0x498)->emit_group_effect_46f9f0(effect_id, index);
}
}
