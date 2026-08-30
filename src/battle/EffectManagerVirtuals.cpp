#include "EffectManager.hpp"

#include <list>


// Current RTTI places the polymorphic animation base first and the
// non-polymorphic CObjectBase handle state at +0x158.  That real secondary
// base is also why VC8 uses the two-dword {code,this-adjustor} member-pointer
// representation in the effect-manager iterators.
class EffectAnimationBase158 {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void update_slot_28();

    unsigned char unknown_004[0x154];
};


struct EffectHandleState8 {
    unsigned state_158;
    unsigned handle_token_15c;
};


class EffectObjectBase : public EffectAnimationBase158,
                         public EffectHandleState8 {
public:
    virtual void update_slot_28();

    unsigned unknown_160;
    int context_164;
    unsigned unknown_168;
    signed char render_layer_16c;
    unsigned char unknown_16d[3];

    void render_435280();
    void render_if_layer(signed char layer);
    void clear_context_if(int context);
};


typedef char EffectAnimationBase_size_must_be_0x158[
    sizeof(EffectAnimationBase158) == 0x158 ? 1 : -1];
typedef char EffectObjectBase_state_offset_must_be_0x158[
    offsetof(EffectObjectBase, state_158) == 0x158 ? 1 : -1];
typedef char EffectObjectBase_handle_offset_must_be_0x15c[
    offsetof(EffectObjectBase, handle_token_15c) == 0x15c ? 1 : -1];
typedef char EffectObjectBase_context_offset_must_be_0x164[
    offsetof(EffectObjectBase, context_164) == 0x164 ? 1 : -1];
typedef char EffectObjectBase_layer_offset_must_be_0x16c[
    offsetof(EffectObjectBase, render_layer_16c) == 0x16c ? 1 : -1];


namespace th105 {

class EffectResourceManager {
public:
    void release(unsigned resource_id);
};

extern EffectResourceManager g_effect_resource_manager;

} // namespace th105


// The shipped manager TU keeps checked vector::erase(first,last) out of line.
// This declaration-only derived view preserves the real VC8 vector iterator
// ABI while keeping that translation-unit visibility boundary explicit.
class EffectResourceVectorEraseView : public std::vector<unsigned> {
public:
    iterator erase_range(iterator first, iterator last);
};


namespace {

template <typename ObjectType, typename BaseObjectType>
struct EffectManagerListView {
    void *manager_vtable_00;
    CHandleManagerEx<ObjectType> handle_pool_04;
    std::list<BaseObjectType *> linked_objects_54;
};

} // namespace


void EffectObjectBase::render_if_layer(signed char layer)
{
    if (layer == render_layer_16c)
        render_435280();
}


void EffectObjectBase::clear_context_if(int context)
{
    if (context_164 == context)
        context_164 = 0;
}


template <typename ObjectType, typename BaseObjectType>
void TObjectManagerBase<ObjectType, BaseObjectType>::update_and_prune(
    void (BaseObjectType::*method)())
{
    typedef EffectManagerListView<ObjectType, BaseObjectType> ManagerView;
    typedef std::list<BaseObjectType *> ObjectList;

    ManagerView *const manager = reinterpret_cast<ManagerView *>(this);
    for (ObjectList::iterator it = manager->linked_objects_54.begin();
         it != manager->linked_objects_54.end();) {
        ((*it)->*method)();
        if ((*it)->state_158 != 0) {
            ++it;
        } else {
            handle_pool_04.release_handle((*it)->handle_token_15c);
            it = manager->linked_objects_54.erase(it);
        }
    }
}


template <typename ObjectType, typename BaseObjectType>
void TObjectManagerBase<ObjectType, BaseObjectType>::invoke_each(
    void (BaseObjectType::*method)(signed char), signed char value)
{
    typedef EffectManagerListView<ObjectType, BaseObjectType> ManagerView;
    typedef std::list<BaseObjectType *> ObjectList;

    ManagerView *const manager = reinterpret_cast<ManagerView *>(this);
    for (ObjectList::iterator it = manager->linked_objects_54.begin();
         it != manager->linked_objects_54.end(); ++it)
        ((*it)->*method)(value);
}


template <typename ObjectType, typename BaseObjectType>
void TObjectManagerBase<ObjectType, BaseObjectType>::invoke_each(
    void (BaseObjectType::*method)(int), int value)
{
    typedef EffectManagerListView<ObjectType, BaseObjectType> ManagerView;
    typedef std::list<BaseObjectType *> ObjectList;

    ManagerView *const manager = reinterpret_cast<ManagerView *>(this);
    for (ObjectList::iterator it = manager->linked_objects_54.begin();
         it != manager->linked_objects_54.end(); ++it)
        ((*it)->*method)(value);
}


template <typename ObjectType>
void CEffectManager<ObjectType>::load_effect_resource_and_preallocate(
    const char *path, unsigned target_count)
{
    load_effect_resource(path);
    TObjectManagerBase<ObjectType, EffectObjectBase>::preallocate_object_pool(
        target_count);
}


template <typename ObjectType>
void CEffectManager<ObjectType>::clear_effects_and_resources()
{
    TObjectManagerBase<ObjectType, EffectObjectBase>::release_all_tracked_objects();
    for (unsigned i = 0; i < resources_64.size(); ++i)
        th105::g_effect_resource_manager.release(resources_64.at(i));
    EffectResourceVectorEraseView &resources =
        reinterpret_cast<EffectResourceVectorEraseView &>(resources_64);
    resources.erase_range(resources.begin(), resources.end());
}


template <typename ObjectType>
void CEffectManager<ObjectType>::release_all_effects()
{
    TObjectManagerBase<ObjectType, EffectObjectBase>::release_all_tracked_objects();
}


template <typename ObjectType>
void CEffectManager<ObjectType>::update_effects()
{
    TObjectManagerBase<ObjectType, EffectObjectBase>::update_and_prune(
        &EffectObjectBase::update_slot_28);
}


template <typename ObjectType>
void CEffectManager<ObjectType>::render_effects_for_layer(signed char layer)
{
    TObjectManagerBase<ObjectType, EffectObjectBase>::invoke_each(
        &EffectObjectBase::render_if_layer, layer);
}


template <typename ObjectType>
void CEffectManager<ObjectType>::on_effect_manager_idle()
{
}


template <typename ObjectType>
void CEffectManager<ObjectType>::clear_effect_context(int context)
{
    TObjectManagerBase<ObjectType, EffectObjectBase>::invoke_each(
        &EffectObjectBase::clear_context_if, context);
}


#define TH105_INSTANTIATE_EFFECT_LOAD(ObjectType) \
    template void CEffectManager<ObjectType>::load_effect_resource_and_preallocate( \
        const char *, unsigned)

TH105_INSTANTIATE_EFFECT_LOAD(CSelectObject);
TH105_INSTANTIATE_EFFECT_LOAD(WeatherEffectObject);
TH105_INSTANTIATE_EFFECT_LOAD(EffectObject);

#undef TH105_INSTANTIATE_EFFECT_LOAD


template void CEffectManager<CSelectObject>::clear_effects_and_resources();
template void CEffectManager<CSelectObject>::release_all_effects();
template void CEffectManager<CSelectObject>::update_effects();
template void CEffectManager<CSelectObject>::render_effects_for_layer(signed char);
template void CEffectManager<CSelectObject>::on_effect_manager_idle();
template void CEffectManager<CSelectObject>::clear_effect_context(int);

template void TObjectManagerBase<CSelectObject, EffectObjectBase>::update_and_prune(
    void (EffectObjectBase::*)());
template void TObjectManagerBase<CSelectObject, EffectObjectBase>::invoke_each(
    void (EffectObjectBase::*)(signed char), signed char);
template void TObjectManagerBase<CSelectObject, EffectObjectBase>::invoke_each(
    void (EffectObjectBase::*)(int), int);
