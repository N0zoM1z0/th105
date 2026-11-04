#include "ScriptCommandRegistry.hpp"

CCommandBase *CScript::next_command()
{
    if (current_28 == pending_14.end())
        return 0;
    CCommandBase *command = *current_28;
    ++current_28;
    return command;
}
