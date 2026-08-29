#include <string>
#include <string.h>
#include <stdlib.h>

namespace th105 {

extern "C" const char connect_empty_string[];

// This is the target's ordinary std::string::assign(const char *, size_type)
// boundary over the same 0x1C physical std::string object.  Naming the narrow
// method keeps VC8 from selecting a different iterator-template overload for
// the known-length empty assignment.
struct ConnectStringAssignView {
    void assign_bytes(const char *source, unsigned int count);
};

class CMenuConnectEndpointParseView {
public:
    template <typename T>
    T &field(unsigned int offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    void parse_endpoint_442e30(const std::string &source);
};

void CMenuConnectEndpointParseView::parse_endpoint_442e30(
    const std::string &source)
{
    char destination[1024];
    char delimiter[4];
    char *context;

    strncpy_s(destination, sizeof(destination), source.c_str(), 1023);
    strcpy(delimiter, ":");

    char *host = strtok_s(destination, delimiter, &context);
    if (host) {
        reinterpret_cast<ConnectStringAssignView *>(
            &field<std::string>(0x42C))
            ->assign_bytes(host, strlen(host));
        if (context && strlen(context)) {
            char *port = strtok_s(0, delimiter, &context);
            field<int>(0x428) = atol(port);
            return;
        }
    } else {
        reinterpret_cast<ConnectStringAssignView *>(
            &field<std::string>(0x42C))
            ->assign_bytes(connect_empty_string, 0);
    }

    field<int>(0x428) = 10800;
}

} // namespace th105
