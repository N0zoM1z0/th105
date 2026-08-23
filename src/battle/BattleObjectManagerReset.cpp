#include <list>
#include <windows.h>

namespace th105 {

struct BattleObjectManagerResetView {
    void reset_battle_render_state_and_signal_465f70();

private:
    template <typename T>
    __forceinline T &field(unsigned offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    __forceinline std::list<int> &pending_values_28()
    {
        return field<std::list<int> >(0x28);
    }

    __forceinline std::list<int> &active_values_34()
    {
        return field<std::list<int> >(0x34);
    }
};

void BattleObjectManagerResetView::reset_battle_render_state_and_signal_465f70()
{
    field<float>(0x48) = -0.5f;
    field<float>(0x4c) = -0.5f;
    const bool transfer_pending = !pending_values_28().empty();
    field<float>(0x6c) = 639.5f;
    field<int>(0x114) = 0;
    field<int>(0xc4) = -1;
    field<float>(0x70) = -0.5f;
    field<int>(0xa0) = -1;
    field<float>(0x90) = -0.5f;
    field<int>(0x7c) = -1;
    field<int>(0x58) = -1;
    field<float>(0x94) = 479.5f;
    field<unsigned char>(0xf8) = 0xff;
    field<float>(0xb8) = 479.5f;
    field<int>(0xfc) = 0;
    field<float>(0xb4) = 639.5f;
    field<float>(0xbc) = 1.0f;
    field<float>(0x98) = 1.0f;
    field<float>(0x74) = 1.0f;
    field<float>(0x50) = 1.0f;
    field<float>(0xc0) = 1.0f;
    field<float>(0x9c) = 1.0f;
    field<float>(0x78) = 1.0f;
    field<float>(0x54) = 1.0f;
    field<float>(0xe8) = 0.0f;
    field<float>(0xe0) = 0.0f;
    field<float>(0xec) = 0.30000001f;
    field<float>(0xe4) = 0.30000001f;
    field<float>(0x108) = 0.0f;
    field<float>(0x104) = 0.0f;
    field<float>(0x100) = 0.0f;
    field<float>(0x110) = 0.0f;
    field<float>(0x10c) = 0.0f;

    if (transfer_pending) {
        std::list<int> &active = active_values_34();
        do {
            active.push_back(pending_values_28().front());
            pending_values_28().pop_front();
        } while (!pending_values_28().empty());
    }

    SetEvent(field<HANDLE>(0x24));
}

} // namespace th105
