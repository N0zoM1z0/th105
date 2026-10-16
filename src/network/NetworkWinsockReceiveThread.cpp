namespace th105 {

// The receive loop consumes ECX and has no explicit stack arguments.
// Its protocol helpers still require a closed source unit before recovery.
class NetworkWinsockReceiveView {
public:
    void receive_loop();
};

extern "C" unsigned long __stdcall network_winsock_receive_thread(void *owner)
{
    static_cast<NetworkWinsockReceiveView *>(owner)->receive_loop();
    return 0;
}

} // namespace th105
