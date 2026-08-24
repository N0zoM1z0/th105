#include "ScriptCommandRegistry.hpp"

#include <utility>


template <class Command>
void CScript::register_command(int command_id, std::string name)
{
    if (name.compare("") == 0) {
        if (default_factory_0c != 0)
            delete default_factory_0c;
        default_factory_0c = new CCommandFactory<Command>(command_id);
    } else {
        CCommandFactoryBase *factory =
            new CCommandFactory<Command>(command_id);
        commands_00.insert(
            std::pair<std::string, CCommandFactoryBase *>(name, factory));
    }
}


template void CScript::register_command<TCommand2<int, int> >(
    int, std::string);
template void CScript::register_command<TCommand1<std::string> >(
    int, std::string);
template void CScript::register_command<CCommand0>(int, std::string);
template void CScript::register_command<TCommand1<int> >(int, std::string);
template void CScript::register_command<CComCharacter>(int, std::string);
template void CScript::register_command<TCommand2<std::string, std::string> >(
    int, std::string);
template void CScript::register_command<TCommand2<std::string, int> >(
    int, std::string);
template void CScript::register_command<
    TCommand4<std::string, int, float, float> >(int, std::string);
template void CScript::register_command<
    TCommand3<std::string, int, bool> >(int, std::string);
template void CScript::register_command<
    TCommand3<std::string, int, int> >(int, std::string);
template void CScript::register_command<
    TCommand4<std::string, int, int, int> >(int, std::string);
template void CScript::register_command<
    TCommand4<unsigned char, unsigned char, unsigned char, unsigned char> >(
        int, std::string);
