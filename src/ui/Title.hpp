#pragma once

#include "assets/ResourceHandleManager.hpp"
#include "../engine/SceneBase.hpp"

extern "C" const unsigned int title_color_vtable_anchor[];
extern "C" void __cdecl _invalid_parameter_noinfo();

namespace th105 {

struct UiDesignObject;

struct UiDesignTree;

struct UiDesignTreeNode {
    UiDesignTreeNode *left;
    UiDesignTreeNode *parent;
    UiDesignTreeNode *right;
    unsigned int key;
    UiDesignObject *value;
    unsigned char color;
    unsigned char is_nil;
    unsigned char reserved_16[2];
};

struct UiDesignTreeIterator {
    UiDesignTree *owner;
    UiDesignTreeNode *node;
};

struct UiDesignTree {
    unsigned int reserved_00;
    UiDesignTreeNode *head;
    unsigned char reserved_08[0x0C];

    UiDesignTreeIterator find(const unsigned int *key);
};

typedef char UiDesignTreeNode_size_must_be_0x18[
    sizeof(UiDesignTreeNode) == 0x18 ? 1 : -1];
typedef char UiDesignTreeIterator_size_must_be_0x08[
    sizeof(UiDesignTreeIterator) == 0x08 ? 1 : -1];
typedef char UiDesignTree_size_must_be_0x14[
    sizeof(UiDesignTree) == 0x14 ? 1 : -1];

// 0x006ECD40 is the concrete CHandleManager<IDirect3DTexture9 *> instance.
// In particular, its eight cache cells begin at +0x64.
struct TitleResourceManager : CHandleManager4 {
    unsigned int *load_texture(
        unsigned int *result,
        const char *path,
        unsigned int *width,
        unsigned int *height);
    unsigned char release_title_resource_handle(unsigned int handle);
    void bind_texture(unsigned int handle, int stage);
};

extern TitleResourceManager g_title_resource_manager;

struct TitleColor94 {
    const unsigned int *vtable;
    unsigned char reserved[0x90];

    ~TitleColor94()
    {
        vtable = title_color_vtable_anchor;
    }
};

struct TitleColorA4 {
    const unsigned int *vtable;
    unsigned char reserved[0xA0];

    ~TitleColorA4()
    {
        vtable = title_color_vtable_anchor;
    }
};

struct TitleDesignResource {
    typedef void (__thiscall *VirtualCleanup)(TitleDesignResource *self);
    typedef void (__thiscall *Prepare)(TitleDesignResource *self, int object_id);
    typedef void (__thiscall *Render)(TitleDesignResource *self);

    void **vtable;
    unsigned char reserved_04[0x1C];
    UiDesignTree object_tree_20;

    TitleDesignResource();
    ~TitleDesignResource();

    void bind_object(UiDesignObject **result, int object_id);
    void bind_object_alt(UiDesignObject **result, int object_id);
    __forceinline UiDesignObject *find_object(int object_id)
    {
        unsigned int key = object_id;
        UiDesignTreeIterator found = object_tree_20.find(&key);

        if (found.owner == 0 || found.owner != &object_tree_20)
            _invalid_parameter_noinfo();
        if (found.node == object_tree_20.head)
            return 0;
        if (found.owner == 0)
            _invalid_parameter_noinfo();
        if (found.node == found.owner->head)
            _invalid_parameter_noinfo();
        return found.node->value;
    }

    __forceinline void virtual_cleanup()
    {
        reinterpret_cast<VirtualCleanup>(vtable[5])(this);
    }

    __forceinline void prepare(int object_id)
    {
        reinterpret_cast<Prepare>(vtable[8])(this, object_id);
    }

    __forceinline void render()
    {
        reinterpret_cast<Render>(vtable[9])(this);
    }

    __forceinline void load(const char *path)
    {
        typedef void (__thiscall *Load)(TitleDesignResource *, const char *);
        reinterpret_cast<Load>(vtable[4])(this, path);
    }
};

typedef char TitleDesignResource_size_must_be_0x34[
    sizeof(TitleDesignResource) == 0x34 ? 1 : -1];

class CTitle : public CSceneBase {
public:
    virtual ~CTitle();
    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);

    void advance_menu_item_wave();

private:
    unsigned int texture_08;
    TitleColor94 color_0c;
    unsigned int texture_a0;
    TitleColor94 color_a4;
    TitleColorA4 color_138;
    TitleDesignResource design_1dc;
    unsigned char reserved_210[0x44];
    float menu_item_wave_offsets[12];
    int reserved_0284;
    int menu_item_wave_counter;
};

typedef char CTitle_size_must_be_0x28c[sizeof(CTitle) == 0x28c ? 1 : -1];

} // namespace th105
