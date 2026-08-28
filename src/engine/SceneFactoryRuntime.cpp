namespace th105 {

struct CLogo { unsigned char bytes[0x198]; CLogo(); };
struct Opening { unsigned char bytes[0x0A0]; Opening(); };
struct CLoading { unsigned char bytes[0x0BC]; CLoading(); };
struct CTitle { unsigned char bytes[0x28C]; CTitle(); };
struct CSelect { unsigned char bytes[0x2ED8]; CSelect(); };
struct CSelectScenario { unsigned char bytes[0x3EC]; CSelectScenario(); };
struct CBattle { unsigned char bytes[0x08]; CBattle(); };
struct Ending { unsigned char bytes[0x98]; Ending(); };
struct CSelectSV { unsigned char bytes[0x2EDC]; CSelectSV(); };
struct CLoadingSV { unsigned char bytes[0x0BC]; CLoadingSV(); };
struct CBattleSV { unsigned char bytes[0x0C]; CBattleSV(); };
struct CSelectCL { unsigned char bytes[0x2EDC]; CSelectCL(); };
struct CLoadingCL { unsigned char bytes[0x0BC]; CLoadingCL(); };
struct CBattleCL { unsigned char bytes[0x0C]; CBattleCL(); };
struct CLoadingWatch { unsigned char bytes[0x0A4]; CLoadingWatch(); };
struct CBattleWatch { unsigned char bytes[0x08]; CBattleWatch(); };

void *__stdcall create_scene_for_id_41e320(int scene)
{
    switch (scene) {
    case 0: return new CLogo;
    case 1: return new Opening;
    case 6: return new CLoading;
    case 2: return new CTitle;
    case 3: return new CSelect;
    case 16: return new CSelectScenario;
    case 5: return new CBattle;
    case 20: return new Ending;
    case 8: return new CSelectSV;
    case 10: return new CLoadingSV;
    case 13: return new CBattleSV;
    case 9: return new CSelectCL;
    case 11: return new CLoadingCL;
    case 14: return new CBattleCL;
    case 12: return new CLoadingWatch;
    case 15: return new CBattleWatch;
    default: return 0;
    }
}

}
