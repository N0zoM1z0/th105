#include "ScriptCommandRegistry.hpp"

CScript::CScript()
    : commands_00(), pending_14(),
      runtime_28(0), runtime_2c(0), runtime_30(0)
{
    default_factory_0c = 0;
}

CScript::~CScript()
{
    clear_commands();
}

void CScript::clear_commands()
{
    while (!pending_14.empty()) {
        CCommandFactoryBase *command = pending_14.back();
        pending_14.pop_back();
        delete command;
    }

    for (CommandMap::iterator it = commands_00.begin();
         it != commands_00.end(); ++it)
        delete it->second;

    commands_00.clear();

    if (default_factory_0c != 0) {
        delete default_factory_0c;
        default_factory_0c = 0;
    }
}
