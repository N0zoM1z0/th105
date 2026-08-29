#include "MenuConnectStateRuntime.hpp"

#include <deque>
#include <string>

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char connect_endpoint_port_format[];

// Narrow target-backed owner view for the history finalizer.  CMenuConnect's
// exact constructor owns the outer pointer at +0xC48; the nested owner's
// checked deque<string> begins at +0x48.
class CMenuConnectHistoryView : public Menu {
public:
    template <typename T>
    T &field(unsigned int offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    void finish_transition_443d70();
};

void CMenuConnectHistoryView::finish_transition_443d70()
{
    char source[260];
    wsprintfA(
        source,
        connect_endpoint_port_format,
        field<MenuString28>(0x42C).c_str(),
        field<unsigned int>(0x428));

    std::string key(source);
    for (std::deque<std::string>::iterator it =
             (*reinterpret_cast<std::deque<std::string> *>(
                 reinterpret_cast<unsigned char *>(field<void *>(0xC48)) +
                 0x48))
                 .begin();
         it != (*reinterpret_cast<std::deque<std::string> *>(
                    reinterpret_cast<unsigned char *>(field<void *>(0xC48)) +
                    0x48))
                   .end();
         ++it) {
        if (*it == key) {
            (*reinterpret_cast<std::deque<std::string> *>(
                reinterpret_cast<unsigned char *>(field<void *>(0xC48)) +
                0x48))
                .erase(it);
            break;
        }
    }

    (*reinterpret_cast<std::deque<std::string> *>(
        reinterpret_cast<unsigned char *>(field<void *>(0xC48)) + 0x48))
        .push_front(std::string(source));
    if ((*reinterpret_cast<std::deque<std::string> *>(
             reinterpret_cast<unsigned char *>(field<void *>(0xC48)) + 0x48))
            .size() > 5) {
        (*reinterpret_cast<std::deque<std::string> *>(
            reinterpret_cast<unsigned char *>(field<void *>(0xC48)) + 0x48))
            .pop_back();
    }
}

} // namespace th105
