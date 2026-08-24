#pragma once

#define TH105_TOBJECT_MANAGER_BASE_DECLARATIONS_ONLY
#include "characters/TObjectManagerBase.hpp"
#undef TH105_TOBJECT_MANAGER_BASE_DECLARATIONS_ONLY

#include "SystemEffectObject.hpp"

class SystemEffectObject;

namespace th105 {

// Current ScenarioData and manager callers prove the SystemEffect manager is a
// bare TObjectManagerBase specialization: its tracked-object list remains at
// +0x54 and the complete object is exactly 0x60 bytes.  The render-each member
// takes MSVC's multiple-inheritance pointer-to-member representation; current
// callers materialize the virtual thunk plus a zero this-adjustor naturally.
template <typename ObjectType>
class SystemEffectManager
    : public TObjectManagerBase<ObjectType, ::SystemEffectObjectBase> {
public:
    void release_all_system_effects();
    void render_each(void (::SystemEffectObjectBase::*method)());
};

typedef char SystemEffectManager_size_must_be_0x60[
    sizeof(SystemEffectManager< ::SystemEffectObject>) == 0x60 ? 1 : -1];

} // namespace th105
