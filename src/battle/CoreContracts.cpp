#include "CoreContracts.hpp"

namespace th105 {
namespace core_contracts {
namespace {

// Compile-only bindings make VC8 reject drift between the declared methods and
// the contract typedefs. This unit is a validator and is not a target TU.
CollisionPhaseFunction const check_collision_phase =
    &CollisionContext::run_attack_projectile_collision_phase;
BodyCollisionFunction const check_body_collision =
    &CollisionContext::resolve_fighter_body_collision;
GeneralHitFunction const check_general_hit =
    &CollisionContext::resolve_general_attack_hit;
ForwardedQuantityFunction const check_forwarded_quantity =
    &CollisionContext::apply_forwarded_quantity_to_pair;
ConsumeSpellEntryFunction const check_consume_spell_entry =
    &Fighter::consume_spell_sequence_entry;
PrepareSpellEntryFunction const check_prepare_spell_entry =
    &Fighter::prepare_next_spell_sequence_entry;
InitializeFighterFunction const check_initialize_fighter =
    &Fighter::initialize_fighter_battle_state;
InitializeFighterFunction const check_initialize_fighter_resources =
    &Fighter::initialize_fighter_spell_resources;
ParseSpellResourcesFunction const check_parse_spell_resources =
    &SpellDataOwner::parse_spell_csv_and_build_card_resources;
FinalizeSpellDataFunction const check_finalize_spell_data =
    &SpellDataOwner::finalize_loaded_spell_data;
SelectSpellRecordFunction const check_select_spell_record =
    &SpellDataOwner::select_spell_record_id;
UpdateObservedStatisticsFunction const check_update_statistics =
    &ScoreData::update_observed_record_statistics;

} // namespace
} // namespace core_contracts
} // namespace th105
