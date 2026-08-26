namespace th105 {
struct InfoManagerBaseStoryDependency {
    virtual ~InfoManagerBaseStoryDependency();
    unsigned char storage_004[0x494];
    InfoManagerBaseStoryDependency();
};
struct BattleInfoRecordF8StoryDependency {
    unsigned char storage_000[0xf8];
    BattleInfoRecordF8StoryDependency();
    ~BattleInfoRecordF8StoryDependency();
};
struct CInfoManagerStoryLifecycle : InfoManagerBaseStoryDependency {
    BattleInfoRecordF8StoryDependency record_498;
    CInfoManagerStoryLifecycle();
    virtual ~CInfoManagerStoryLifecycle();
    void initialize_story_info_resources_471e50();
    int release_info_effect_resources_46e990();
};
CInfoManagerStoryLifecycle::CInfoManagerStoryLifecycle()
{
    initialize_story_info_resources_471e50();
}
CInfoManagerStoryLifecycle::~CInfoManagerStoryLifecycle()
{
    release_info_effect_resources_46e990();
}
}
