#include "ScriptCommandRegistry.hpp"

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

inline void assign_command_argument(int &value, char *token)
{
    value = atol(token);
}

inline void assign_command_argument(float &value, char *token)
{
    value = static_cast<float>(atof(token));
}

inline void assign_command_argument(bool &value, char *token)
{
    value = atol(token) != 0;
}

inline void assign_command_argument(unsigned char &value, char *token)
{
    value = static_cast<unsigned char>(atol(token));
}

inline void assign_command_argument(std::string &value, char *token)
{
    ScriptCommandStringAssignView *view =
        reinterpret_cast<ScriptCommandStringAssignView *>(&value);
    if (token)
        view->assign_bytes(token, static_cast<unsigned int>(strlen(token)));
    else
        view->assign_bytes("", 0);
}

} // namespace

void CCommand0::parse(char *)
{
}

template <class A>
void TCommand1<A>::parse(char *string)
{
    char delimiter[2] = ",";
    char *token = strtok_s(string, delimiter, &string);
    assign_command_argument(arg0_08, token);
}

template <class A, class B>
void TCommand2<A, B>::parse(char *string)
{
    char delimiter[2] = ",";
    char *token = strtok_s(string, delimiter, &string);
    assign_command_argument(arg0_08, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg1, token);
}

template <class A, class B, class C>
void TCommand3<A, B, C>::parse(char *string)
{
    char delimiter[2] = ",";
    char *token = strtok_s(string, delimiter, &string);
    assign_command_argument(arg0_08, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg1, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg2, token);
}

template <class A, class B, class C, class D>
void TCommand4<A, B, C, D>::parse(char *string)
{
    char delimiter[2] = ",";
    char *token = strtok_s(string, delimiter, &string);
    assign_command_argument(arg0_08, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg1, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg2, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg3, token);
}

template <class A, class B, class C, class D, class E>
void TCommand5<A, B, C, D, E>::parse(char *string)
{
    char delimiter[2] = ",";
    char *token = strtok_s(string, delimiter, &string);
    assign_command_argument(arg0_08, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg1, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg2, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg3, token);
    token = strtok_s(0, delimiter, &string);
    assign_command_argument(arg4, token);
}

template <class Command>
CCommandBase *CScript::CCommandFactory<Command>::create()
{
    Command *command = new Command;
    command->command_id_04 = command_id_04;
    return command;
}

// The current executable contains exactly these command specializations.  Full
// class instantiation is intentional: it lets VC8 own the implicit lifetimes
// and deleting-destructor folding observed in the RTTI vtables.
template class TCommand2<int, int>;
template class CScript::CCommandFactory<TCommand2<int, int> >;
template class TCommand1<std::string>;
template class CScript::CCommandFactory<TCommand1<std::string> >;
template class TCommand5<int, std::string, int, int, int>;
template class CScript::CCommandFactory<
    TCommand5<int, std::string, int, int, int> >;
template class TCommand5<int, float, float, float, int>;
template class CScript::CCommandFactory<TCommand5<int, float, float, float, int> >;
template class TCommand5<int, float, float, int, int>;
template class CScript::CCommandFactory<TCommand5<int, float, float, int, int> >;
template class TCommand1<int>;
template class CScript::CCommandFactory<TCommand1<int> >;
template class TCommand2<std::string, std::string>;
template class CScript::CCommandFactory<TCommand2<std::string, std::string> >;
template class TCommand2<std::string, int>;
template class CScript::CCommandFactory<TCommand2<std::string, int> >;
template class TCommand4<std::string, int, float, float>;
template class CScript::CCommandFactory<
    TCommand4<std::string, int, float, float> >;
template class TCommand3<std::string, int, bool>;
template class CScript::CCommandFactory<TCommand3<std::string, int, bool> >;
template class TCommand3<std::string, int, int>;
template class CScript::CCommandFactory<TCommand3<std::string, int, int> >;
template class TCommand4<std::string, int, int, int>;
template class CScript::CCommandFactory<TCommand4<std::string, int, int, int> >;
template class TCommand4<unsigned char, unsigned char, unsigned char, unsigned char>;
template class CScript::CCommandFactory<
    TCommand4<unsigned char, unsigned char, unsigned char, unsigned char> >;
template class CScript::CCommandFactory<CCommand0>;
template class CScript::CCommandFactory<CComCharacter>;
