#pragma once

#include <string>

// Current 1.06a RTTI exposes one shared polymorphic command base followed by
// concrete TCommandN specializations.  The base contributes only the vptr;
// every concrete command stores the numeric registry id at +0x04 and parsed
// payload beginning at +0x08.
class CCommandBase {
public:
    virtual ~CCommandBase() {}
    virtual void parse(char *string) = 0;
};

class CCommand0 : public CCommandBase {
public:
    int command_id_04;
    virtual void parse(char *string);
};

template <class A>
class TCommand1 : public CCommandBase {
public:
    int command_id_04;
    A arg0_08;
    virtual void parse(char *string);
};

template <class A, class B>
class TCommand2 : public CCommandBase {
public:
    int command_id_04;
    A arg0_08;
    B arg1;
    virtual void parse(char *string);
};

template <class A, class B, class C>
class TCommand3 : public CCommandBase {
public:
    int command_id_04;
    A arg0_08;
    B arg1;
    C arg2;
    virtual void parse(char *string);
};

template <class A, class B, class C, class D>
class TCommand4 : public CCommandBase {
public:
    int command_id_04;
    A arg0_08;
    B arg1;
    C arg2;
    D arg3;
    virtual void parse(char *string);
};

template <class A, class B, class C, class D, class E>
class TCommand5 : public CCommandBase {
public:
    int command_id_04;
    A arg0_08;
    B arg1;
    C arg2;
    D arg3;
    E arg4;
    virtual void parse(char *string);
};

class CComCharacter : public CCommandBase {
public:
    virtual ~CComCharacter();
    virtual void parse(char *string);

    int command_id_04;
    std::string name_08;
    int value_24;
    int value_28;
    unsigned char value_2c;
    unsigned char color_2d[3];
};

typedef char CCommandBase_size_must_be_0x04[
    sizeof(CCommandBase) == 0x04 ? 1 : -1];
typedef char CComCharacter_size_must_be_0x30[
    sizeof(CComCharacter) == 0x30 ? 1 : -1];
