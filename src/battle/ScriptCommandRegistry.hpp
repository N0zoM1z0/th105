#pragma once

#include <map>
#include <deque>
#include <string>
#include <stddef.h>

// Current CScenarioData construction embeds this script registry at +0x35C and
// registers the command family below through one shared VC8 template body.
// Current CScript lifetime now closes the complete 0x34 layout: the command
// map, default factory, an owned command deque and its12-byte checked iterator.
// The +0x10 cell remains deliberately unnamed/uninitialized. Factory creation
// and command parsing are distinct native virtual calls; pending values are
// CCommandBase objects, not factories.
#include "ScriptCommandRuntime.hpp"

class CScript {
public:
    class CCommandFactoryBase {
    public:
        virtual ~CCommandFactoryBase() {}
        virtual CCommandBase *create() = 0;
    };

    template <class Command>
    class CCommandFactory : public CCommandFactoryBase {
    public:
        explicit CCommandFactory(int command_id)
            : command_id_04(command_id)
        {
        }

        virtual CCommandBase *create();

        int command_id_04;
    };

    typedef std::map<std::string, CCommandFactoryBase *> CommandMap;

    CScript();
    ~CScript();
    void clear_commands();
    void clear_pending_commands();

    template <class Command>
    void register_command(int command_id, std::string name);

    CommandMap commands_00;
    CCommandFactoryBase *default_factory_0c;
    void *runtime_10;
    typedef std::deque<CCommandBase *> PendingCommands;
    PendingCommands pending_14;
    PendingCommands::iterator current_28;
};

typedef char CScriptCommandMap_size_must_be_0x0c[
    sizeof(CScript::CommandMap) == 0x0c ? 1 : -1];
typedef char CScript_iterator_size_must_be_0x0c[
    sizeof(CScript::PendingCommands::iterator) == 0x0c ? 1 : -1];
typedef char CScript_iterator_offset_must_be_0x28[
    offsetof(CScript, current_28) == 0x28 ? 1 : -1];
typedef char CScript_size_must_be_0x34[
    sizeof(CScript) == 0x34 ? 1 : -1];

namespace th105 {

// Opening and staff-roll scene owners both construct this shared timeline
// command registry.  Current 0x004540F0 independently proves CScript begins at
// +0x18; later timeline fields remain outside this observed prefix.
struct SceneTimelineRegistry {
    int bpm_00;
    int field_04;
    int field_08;
    int notify_time_0c;
    int previous_tick_10;
    int accumulated_time_14;
    CScript script_18;

    void register_builtin_commands();
};

typedef char SceneTimelineRegistry_script_offset_must_be_0x18[
    offsetof(SceneTimelineRegistry, script_18) == 0x18 ? 1 : -1];

} // namespace th105
