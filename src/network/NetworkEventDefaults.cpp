// Native INetworkUDPEventProc default callback policy. The physical base table
// shares the three-word no-op and one-word no-op among multiple event slots.
namespace th105 {
class NetworkEventDefaultsView {
public:
    virtual void on_accepted(unsigned code, const void *payload, unsigned size);
    virtual void on_rejected(unsigned code);
    virtual void on_primary_data(const void *payload, int size);
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
    virtual void on_peer_removed(unsigned slot);
private:
    int state_04;
};
void NetworkEventDefaultsView::on_accepted(unsigned, const void *, unsigned) {}
void NetworkEventDefaultsView::on_rejected(unsigned) {}
void NetworkEventDefaultsView::on_primary_data(const void *, int) {}
void NetworkEventDefaultsView::on_peer_data(unsigned, const void *, int) {}
int NetworkEventDefaultsView::route_payload(unsigned, int *,
    const unsigned char *, int, void **, unsigned short *)
{
    return 9;
}
void NetworkEventDefaultsView::on_peer_removed(unsigned) {}
}
