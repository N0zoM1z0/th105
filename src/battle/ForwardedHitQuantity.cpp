#include "Collision.hpp"

namespace th105 {

namespace {

typedef void (__thiscall *ContextDepletionCallback)(
    CollisionContext *context, Fighter *fighter);

void invoke_context_slot_2c(
    CollisionContext *context,
    Fighter *fighter)
{
    ContextDepletionCallback callback =
        reinterpret_cast<ContextDepletionCallback>(
            (*reinterpret_cast<void ***>(context))[11]);
    callback(context, fighter);
}

} // namespace

void CollisionContext::apply_forwarded_quantity_to_pair(
    AttackCandidate *candidate,
    Fighter *fighter,
    int quantity,
    int scalar_per_thousand,
    short forwarded_counter_delta,
    signed char use_dynamic_scalar)
{
    register int applied_quantity = quantity;
    if (static_cast<signed char>(
            is_state_13c_in_32_95(fighter)) == 0 &&
        fighter->field_4a4 == 0) {
        reset_hit_exchange_scratch(candidate->owner_16c, fighter);
    }

    if (use_dynamic_scalar != 0) {
        applied_quantity = static_cast<int>(
            candidate->calculate_forwarded_quantity() * applied_quantity);
    }

    fighter->adjust_capped_counter_558(
        static_cast<short>(applied_quantity / 20));
    candidate->owner_16c->value_498 += forwarded_counter_delta;
    candidate->owner_16c->scalar_494 =
        (static_cast<float>(scalar_per_thousand) / 1000.0f) *
        candidate->owner_16c->scalar_494;
    candidate->owner_16c->value_49a +=
        static_cast<short>(applied_quantity);

    if (candidate->owner_16c->factor_4d4 > 0.0f) {
        int recovered = static_cast<int>(
            candidate->owner_16c->factor_4d4 * applied_quantity);
        recovered = static_cast<short>(recovered);
        int next = fighter->value_174 + recovered;
        if (fighter->maximum_176 <= next) {
            next = fighter->maximum_176;
        }
        fighter->value_174 = static_cast<short>(next);
    }

    fighter->value_174 -= static_cast<short>(applied_quantity);
    if (fighter->value_174 <= 0) {
        fighter->value_174 = 0;
        invoke_context_slot_2c(this, fighter);
    }
    fighter->accumulated_hit_quantity_178 += applied_quantity;
}

} // namespace th105
