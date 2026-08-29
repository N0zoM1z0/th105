#include "../battle/Collision.hpp"

namespace th105 {

struct FighterRosterOwner {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void unknown_0c();
    virtual void unknown_10();
    virtual void unknown_14();
    virtual void unknown_18();
    virtual void unknown_1c();
    virtual void bind_fighters(Fighter *previous, Fighter *current);
};

void Fighter::reset_for_roster_45e040(Fighter *other)
{
    if (other_fighter_170) {
        reinterpret_cast<FighterRosterOwner *>(owned_manager_658)
            ->bind_fighters(other_fighter_170, other);
    }
    other_fighter_170 = other;
}

void Fighter::copy_action_word_176_to_174()
{
    value_174 = maximum_176;
}

} // namespace th105
