#pragma once

#include <map>
#include <string>

// Current CScenarioData construction embeds this script registry at +0x35C and
// registers the command family below through one shared VC8 template body.
// Only the prefix exercised by command registration is named here; later
// CScript state remains deliberately unmodelled.
class CCommand0 {};
class CComCharacter {};

template <class A>
class TCommand1 {};

template <class A, class B>
class TCommand2 {};

template <class A, class B, class C>
class TCommand3 {};

template <class A, class B, class C, class D>
class TCommand4 {};

class CScript {
public:
    class CCommandFactoryBase {
    public:
        virtual ~CCommandFactoryBase() {}
    };

    template <class Command>
    class CCommandFactory : public CCommandFactoryBase {
    public:
        explicit CCommandFactory(int command_id)
            : command_id_04(command_id)
        {
        }

        int command_id_04;
    };

    typedef std::map<std::string, CCommandFactoryBase *> CommandMap;

    template <class Command>
    void register_command(int command_id, std::string name);

    CommandMap commands_00;
    CCommandFactoryBase *default_factory_0c;
};

typedef char CScriptCommandMap_size_must_be_0x0c[
    sizeof(CScript::CommandMap) == 0x0c ? 1 : -1];
