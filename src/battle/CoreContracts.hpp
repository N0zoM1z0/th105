#pragma once

#include <stddef.h>

#include "Collision.hpp"
#include "SpellData.hpp"
#include "SpellRuntime.hpp"
#include "config/ScoreData.hpp"

namespace th105 {
namespace core_contracts {

// These typedefs encode target-facing C++ method contracts without defining
// placeholder bodies or producing linker-visible replacement functions.
typedef void (CollisionContext::*CollisionPhaseFunction)();
typedef void (CollisionContext::*GeneralHitFunction)(
    AttackCandidate *,
    Fighter *);
typedef void (CollisionContext::*ForwardedQuantityFunction)(
    AttackCandidate *,
    Fighter *,
    int,
    int,
    short,
    signed char);
typedef unsigned char (Fighter::*ConsumeSpellEntryFunction)();
typedef void (Fighter::*PrepareSpellEntryFunction)();
typedef void (Fighter::*InitializeFighterFunction)();
typedef void (SpellDataOwner::*ParseSpellResourcesFunction)(
    const char *,
    const char *,
    void *,
    SpellTree *);
typedef void (SpellDataOwner::*FinalizeSpellDataFunction)();
typedef short (SpellDataOwner::*SelectSpellRecordFunction)();
typedef void (ScoreData::*UpdateObservedStatisticsFunction)(
    int,
    int,
    int,
    int);

enum CoreFunctionAddress {
    ADDRESS_PARSE_SPELL_RESOURCES = 0x00432E20,
    ADDRESS_UPDATE_OBSERVED_STATISTICS = 0x0042C100,
    ADDRESS_CONSUME_SPELL_ENTRY = 0x0045BC30,
    ADDRESS_PREPARE_SPELL_ENTRY = 0x0045C690,
    ADDRESS_INITIALIZE_FIGHTER = 0x0045F140,
    ADDRESS_INITIALIZE_FIGHTER_RESOURCES = 0x00462050,
    ADDRESS_GENERAL_HIT = 0x0046B570,
    ADDRESS_FORWARDED_QUANTITY = 0x0046BBA0,
    ADDRESS_COLLISION_PHASE = 0x0046D620
};

// VC8-compatible compile-time layout checks for complete views. Partial views
// are tracked in config/core-types.csv and intentionally have no sizeof claim.
typedef char CheckAttackCandidateFrameSize[
    sizeof(AttackCandidateFrame) == 0x54 ? 1 : -1];
typedef char CheckCollisionAabbSize[
    sizeof(CollisionAabb) == 0x10 ? 1 : -1];
typedef char CheckCollisionListSize[
    sizeof(CollisionList) == 0x0c ? 1 : -1];
typedef char CheckCollisionListNodeSize[
    sizeof(CollisionListNode) == 0x0c ? 1 : -1];
typedef char CheckFighterSequenceControllerSize[
    sizeof(FighterSequenceController) == 0x14 ? 1 : -1];
typedef char CheckFighterSequenceSlotSize[
    sizeof(FighterSequenceSlot) == 0x98 ? 1 : -1];
typedef char CheckObservedRecordSize[
    sizeof(ObservedRecord24) == 0x18 ? 1 : -1];
typedef char CheckObservedRangeSize[
    sizeof(ObservedRecordRange16) == 0x10 ? 1 : -1];
typedef char CheckSequenceRecordSize[
    sizeof(SequenceRecord4) == 0x04 ? 1 : -1];
typedef char CheckShortDequeSize[
    sizeof(ShortDeque8) == 0x14 ? 1 : -1];
typedef char CheckShapeWordsSize[
    sizeof(ShapeWords) == 0x10 ? 1 : -1];
typedef char CheckSpellRecordSize[
    sizeof(SpellRecordView) == 0x4c ? 1 : -1];
typedef char CheckSpellSpriteWorkSize[
    sizeof(SpellSpriteWork) == 0x94 ? 1 : -1];
typedef char CheckSpellTreeIteratorSize[
    sizeof(SpellTreeIterator) == 0x08 ? 1 : -1];
typedef char CheckWorldAabbSize[
    sizeof(WorldAabb) == 0x10 ? 1 : -1];

typedef char CheckAttackFrameFlagsOffset[
    offsetof(AttackCandidateFrame, flags_50) == 0x50 ? 1 : -1];
typedef char CheckFighterSequenceOffset[
    offsetof(Fighter, sequence_controller_55c) == 0x55c ? 1 : -1];
typedef char CheckFighterCategoryOffset[
    offsetof(Fighter, state_72c) == 0x72c ? 1 : -1];
typedef char CheckSpellRecordResourceOffset[
    offsetof(SpellRecordView, optional_resource_44) == 0x44 ? 1 : -1];
typedef char CheckLoadedSpellIdsOffset[
    offsetof(SpellDataOwner, loaded_spell_ids_20) == 0x20 ? 1 : -1];
typedef char CheckSelectionIdsOffset[
    offsetof(SpellDataOwner, selection_ids_34) == 0x34 ? 1 : -1];
typedef char CheckSelectedValueTableOffset[
    offsetof(SpellDataOwner, selected_value_by_index_48) == 0x48 ? 1 : -1];

} // namespace core_contracts
} // namespace th105
