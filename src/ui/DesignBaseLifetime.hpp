#pragma once

#include <list>
#include <map>
#include <new>

namespace th105 {

struct UiDesignObject;

// Narrow lifetime view of the target's IColor primary base.  This stays
// separate from the retained sprite-facing IColor declaration because the
// original CDesignBase constructor performs no observable base-constructor
// call or value_04 initialization.
class DesignColorLifetimeView {
public:
    DesignColorLifetimeView() {}
    virtual ~DesignColorLifetimeView() {}
    virtual void set_color(unsigned int) = 0;
    virtual void set_vertex_colors(const unsigned int *) = 0;
    virtual void multiply_color(unsigned int) = 0;

    unsigned int value_04;
};

// The target stores exactly three pointers at CDesignBase +0x08.  VC8's
// checked std::vector<unsigned> in the probe profile is 0x10 bytes, so this is
// the narrower source-owned handle-storage contract observed by CDesignBase.
struct DesignHandleVector12 {
    unsigned int *begin;
    unsigned int *end;
    unsigned int *capacity;

    DesignHandleVector12() : begin(0), end(0), capacity(0) {}
    ~DesignHandleVector12()
    {
        if (begin != 0)
            ::operator delete(begin);
        begin = 0;
        end = 0;
        capacity = 0;
    }
};

class CDesignBase : public DesignColorLifetimeView {
public:
    CDesignBase();
    // Deliberately implicit virtual destructor.  The current target does not
    // republish the derived vptr at normal-destruction entry; VC8's implicit
    // special member reproduces that lifetime exactly.

    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual int load(const char *path);
    virtual void virtual_cleanup();
    virtual void move(float x, float y);
    virtual void move_mode(float x, float y, int mode);
    virtual void prepare(int object_id);
    virtual void render();

    DesignHandleVector12 texture_handles_08;
    std::list<UiDesignObject *> objects_14;
    std::map<unsigned int, UiDesignObject *> object_tree_20;
    std::list<UiDesignObject *>::iterator current_2c;
};

typedef char DesignColorLifetimeView_size_must_be_0x08[
    sizeof(DesignColorLifetimeView) == 0x08 ? 1 : -1];
typedef char DesignHandleVector12_size_must_be_0x0c[
    sizeof(DesignHandleVector12) == 0x0c ? 1 : -1];
typedef char CDesignBase_size_must_be_0x34[
    sizeof(CDesignBase) == 0x34 ? 1 : -1];

} // namespace th105
