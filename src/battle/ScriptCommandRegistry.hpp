#pragma once

#include <map>
#include <deque>
#include <string>

// Current CScenarioData construction embeds this script registry at +0x35C and
// registers the command family below through one shared VC8 template body.
// Current CScript lifetime now closes the complete 0x34 layout: the command
// map, default factory, one checked pending-factory deque and three runtime
// cells.  The +0x10 cell remains deliberately unnamed/uninitialized.
class CCommand0 {};

class CComCharacter {
public:
    virtual ~CComCharacter();
    virtual void parse(char *string);

    int reserved_04;
    std::string name_08;
    int value_24;
    int value_28;
    unsigned char value_2c;
    unsigned char color_2d[3];
};

typedef char CComCharacter_size_must_be_0x30[
    sizeof(CComCharacter) == 0x30 ? 1 : -1];

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

    CScript();
    ~CScript();
    void clear_commands();

    template <class Command>
    void register_command(int command_id, std::string name);

    CommandMap commands_00;
    CCommandFactoryBase *default_factory_0c;
    void *runtime_10;
    std::deque<CCommandFactoryBase *> pending_14;
    void *runtime_28;
    void *runtime_2c;
    void *runtime_30;
};

typedef char CScriptCommandMap_size_must_be_0x0c[
    sizeof(CScript::CommandMap) == 0x0c ? 1 : -1];
typedef char CScript_size_must_be_0x34[
    sizeof(CScript) == 0x34 ? 1 : -1];
