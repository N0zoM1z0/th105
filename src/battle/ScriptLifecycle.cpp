#include "ScriptCommandRegistry.hpp"

CScript::CScript()
    : commands_00(), pending_14(),
      current_28()
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
        CCommandBase *command = pending_14.back();
        // Native405770 destroys the live command before removing its queue slot.
        delete command;
        pending_14.pop_back();
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
