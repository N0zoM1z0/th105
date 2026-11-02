#include "engine/SceneBase.hpp"
#include "ui/Tile.hpp"
#include "battle/EffectSprite.hpp"
#include <deque>

namespace th105 {

struct TitleResourceManagerLifetimeView {
    unsigned char release_title_resource_handle(unsigned packed_token);
};
extern TitleResourceManagerLifetimeView g_title_resource_manager;

struct SceneRenderCluster93 {
    unsigned char bytes_00[0x93];
    ~SceneRenderCluster93();
    void cleanup();
};

typedef char SceneRenderCluster93_size[sizeof(SceneRenderCluster93)==0x93?1:-1];

class EndingLifetimeView : public IScene {
public:
    virtual ~EndingLifetimeView();
    SceneRenderCluster93 cluster_04;
    unsigned char alpha_97;
};

class OpeningLifetimeView : public IScene {
public:
    virtual ~OpeningLifetimeView();
    unsigned unknown_04;
    SceneRenderCluster93 cluster_08;
};

class CLoadingLifetimeView : public IScene {
public:
    virtual ~CLoadingLifetimeView();
    unsigned texture_04;
    CSprite sprite_08;
    unsigned char reserved_9c[8];
    std::deque<unsigned char> queue_a4;
    unsigned short timer_b8;
};

class CLogoLifetimeView : public IScene {
public:
    virtual ~CLogoLifetimeView();
    unsigned texture_04;
    CEffectSprite sprite_08;
    CTile tile_f0;
    int state_194;
};

class CLoadingWatchLifetimeView : public IScene {
public:
    virtual ~CLoadingWatchLifetimeView();
    unsigned texture_04;
    CSprite sprite_08;
    unsigned short timer_9c;
    unsigned char reserved_9e[2];
    int state_a0;
};

EndingLifetimeView::~EndingLifetimeView() { cluster_04.cleanup(); }
OpeningLifetimeView::~OpeningLifetimeView() { cluster_08.cleanup(); }
CLoadingLifetimeView::~CLoadingLifetimeView() { g_title_resource_manager.release_title_resource_handle(texture_04); }
CLogoLifetimeView::~CLogoLifetimeView() { g_title_resource_manager.release_title_resource_handle(texture_04); }
CLoadingWatchLifetimeView::~CLoadingWatchLifetimeView() { g_title_resource_manager.release_title_resource_handle(texture_04); }

typedef char Ending_alpha_off[offsetof(EndingLifetimeView,alpha_97)==0x97?1:-1];
typedef char Loading_queue_off[offsetof(CLoadingLifetimeView,queue_a4)==0xa4?1:-1];
typedef char Loading_size[sizeof(CLoadingLifetimeView)==0xbc?1:-1];
typedef char Logo_second_off[offsetof(CLogoLifetimeView,tile_f0)==0xf0?1:-1];
typedef char Logo_size[sizeof(CLogoLifetimeView)==0x198?1:-1];
typedef char Logo_state_off[offsetof(CLogoLifetimeView,state_194)==0x194?1:-1];
typedef char Loading_timer_off[offsetof(CLoadingLifetimeView,timer_b8)==0xb8?1:-1];
typedef char Watch_timer_off[offsetof(CLoadingWatchLifetimeView,timer_9c)==0x9c?1:-1];

} // namespace th105
