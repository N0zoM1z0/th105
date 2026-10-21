#pragma once

#include <list>
#include <map>
#include <new>
#include <vector>
#include <stddef.h>

namespace th105 {

struct UiDesignObject;

// The primary IColor interface contributes its vptr. The native vector at +4
// contains an allocator subobject before its three pointers at +8/+C/+10.
// The loader passes this+4 to vector operations; all three lifetime bodies
// retain complete canonical matches with the native container.
class DesignColorLifetimeView {
public:
    DesignColorLifetimeView() {}
    virtual ~DesignColorLifetimeView() {}
    virtual void set_color(unsigned int) = 0;
    virtual void set_vertex_colors(const unsigned int *) = 0;
    virtual void multiply_color(unsigned int) = 0;

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

    std::vector<unsigned int> texture_handles_04;
    std::list<UiDesignObject *> objects_14;
    std::map<unsigned int, UiDesignObject *> object_tree_20;
    std::list<UiDesignObject *>::iterator current_2c;
};

typedef char DesignColorLifetimeView_size_must_be_0x04[
    sizeof(DesignColorLifetimeView) == 0x04 ? 1 : -1];
typedef char DesignHandleVector_size_must_be_0x10[
    sizeof(std::vector<unsigned int>) == 0x10 ? 1 : -1];
typedef char CDesignBase_size_must_be_0x34[
    sizeof(CDesignBase) == 0x34 ? 1 : -1];
typedef char CDesignBase_handle_vector_offset_must_be_0x04[
    offsetof(CDesignBase, texture_handles_04) == 0x04 ? 1 : -1];
typedef char CDesignBase_object_list_offset_must_be_0x14[
    offsetof(CDesignBase, objects_14) == 0x14 ? 1 : -1];
typedef char CDesignBase_object_tree_offset_must_be_0x20[
    offsetof(CDesignBase, object_tree_20) == 0x20 ? 1 : -1];
typedef char CDesignBase_current_offset_must_be_0x2c[
    offsetof(CDesignBase, current_2c) == 0x2c ? 1 : -1];

} // namespace th105
