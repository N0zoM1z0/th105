#include "NetworkSendState.hpp"

namespace th105 {

class CNetworkBaseCtorDependency {
public:
    CNetworkBaseCtorDependency();
    virtual ~CNetworkBaseCtorDependency();
protected:
    unsigned char reserved_004[0x3b0];
    NetworkSendStateView state_3b4;
    unsigned char reserved_4fc[0x6dc - 0x4fc];
};

class INetworkUDPEventProcCtorView {
public:
    INetworkUDPEventProcCtorView() {}
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    int state_04;
};

class CNetworkServerCtorView : public CNetworkBaseCtorDependency,
                               public INetworkUDPEventProcCtorView {
public:
    CNetworkServerCtorView();
    virtual ~CNetworkServerCtorView();
private:
    unsigned char server_tail_6e4[8];
};

class CNetworkClientCtorView : public CNetworkBaseCtorDependency,
                               public INetworkUDPEventProcCtorView {
public:
    CNetworkClientCtorView();
    virtual ~CNetworkClientCtorView();
};

CNetworkServerCtorView::CNetworkServerCtorView()
{
    state_3b4.publish_callback(static_cast<INetworkUDPEventProcCtorView *>(this));
}

CNetworkClientCtorView::CNetworkClientCtorView()
{
    state_3b4.publish_callback(static_cast<INetworkUDPEventProcCtorView *>(this));
}

extern CNetworkBaseCtorDependency *g_network_session;

CNetworkBaseCtorDependency *__cdecl create_connect_session_43ce00()
{
    CNetworkServerCtorView *session = new CNetworkServerCtorView;
    g_network_session = session;
    return session;
}

CNetworkBaseCtorDependency *__cdecl create_connect_client_43ce80()
{
    CNetworkClientCtorView *session = new CNetworkClientCtorView;
    g_network_session = session;
    return session;
}

typedef char NetworkBaseCtorDependency_size[
    sizeof(CNetworkBaseCtorDependency) == 0x6dc ? 1 : -1];
typedef char NetworkSecondaryCtorView_size[
    sizeof(INetworkUDPEventProcCtorView) == 8 ? 1 : -1];
typedef char NetworkServerCtorView_size[
    sizeof(CNetworkServerCtorView) == 0x6ec ? 1 : -1];
typedef char NetworkClientCtorView_size[
    sizeof(CNetworkClientCtorView) == 0x6e4 ? 1 : -1];

} // namespace th105
