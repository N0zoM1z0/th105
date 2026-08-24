#include "ScriptCommandRegistry.hpp"

CScript::CScript()
    : commands_00(), pending_14(),
      runtime_28(0), runtime_2c(0), runtime_30(0)
{
    default_factory_0c = 0;
}


#include <stdlib.h>
#include <string.h>

extern "C" char *__cdecl strtok_s(
    char *string,
    const char *delimiter,
    char **context);

struct ScriptCommandStringAssignView {
    void assign_bytes(const char *source, unsigned int length);
};

namespace {

inline char script_hex_nibble(char value)
{
    if (static_cast<unsigned char>(value - '0') <= 9)
        return static_cast<char>(value - '0');
    if (static_cast<unsigned char>(value - 'a') <= 5)
        return static_cast<char>(value - 'W');
    if (static_cast<unsigned char>(value - 'A') <= 5)
        return static_cast<char>(value - '7');
    return 0;
}

} // namespace

void CComCharacter::parse(char *string)
{
    char delimiter[2] = ",";

    char *token = strtok_s(string, delimiter, &string);
    reinterpret_cast<ScriptCommandStringAssignView *>(&name_08)
        ->assign_bytes(token, static_cast<unsigned int>(strlen(token)));

    token = strtok_s(0, delimiter, &string);
    value_24 = atol(token);
    token = strtok_s(0, delimiter, &string);
    value_28 = atol(token);
    token = strtok_s(0, delimiter, &string);
    value_2c = static_cast<unsigned char>(atol(token));
    token = strtok_s(0, delimiter, &string);

    color_2d[0] = static_cast<unsigned char>(
        (script_hex_nibble(token[0]) << 4) | script_hex_nibble(token[1]));
    color_2d[1] = static_cast<unsigned char>(
        (script_hex_nibble(token[2]) << 4) | script_hex_nibble(token[3]));
    color_2d[2] = static_cast<unsigned char>(
        (script_hex_nibble(token[4]) << 4) | script_hex_nibble(token[5]));
}
