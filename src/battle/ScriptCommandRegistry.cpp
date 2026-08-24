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
template void CScript::register_command<
    TCommand5<int, std::string, int, int, int> >(int, std::string);
template void CScript::register_command<
    TCommand5<int, float, float, float, int> >(int, std::string);
template void CScript::register_command<
    TCommand5<int, float, float, int, int> >(int, std::string);
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


namespace th105 {

void SceneTimelineRegistry::register_builtin_commands()
{
    script_18.register_command<TCommand2<int, int> >(0, "bpm");
    script_18.register_command<TCommand1<std::string> >(2, "bgm");
    script_18.register_command<TCommand5<int, std::string, int, int, int> >(
        1, "pic");
    script_18.register_command<TCommand5<int, float, float, float, int> >(3, "x");
    script_18.register_command<TCommand5<int, float, float, float, int> >(4, "y");
    script_18.register_command<TCommand5<int, float, float, float, int> >(5, "u");
    script_18.register_command<TCommand5<int, float, float, float, int> >(6, "v");
    script_18.register_command<TCommand5<int, float, float, int, int> >(7, "r");
    script_18.register_command<TCommand5<int, float, float, int, int> >(8, "g");
    script_18.register_command<TCommand5<int, float, float, int, int> >(9, "b");
    script_18.register_command<TCommand5<int, float, float, int, int> >(
        10, "alpha");
    script_18.register_command<TCommand5<int, float, float, float, int> >(
        11, "sx");
    script_18.register_command<TCommand5<int, float, float, float, int> >(
        12, "sy");
    script_18.register_command<TCommand5<int, float, float, float, int> >(
        13, "angle");
    script_18.register_command<CCommand0>(15, "play");
    script_18.register_command<TCommand2<int, int> >(14, "interval");
    script_18.register_command<TCommand1<int> >(16, "notify");
    script_18.register_command<TCommand1<int> >(17, "end");
}

} // namespace th105
