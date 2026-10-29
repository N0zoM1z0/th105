// JP1.06a RTTI-owned CharacterEx normal/scalar destruction.
namespace th105 {
// Destructor-only interface views. No complete Character allocation is made.
class CharacterLifetimeBaseView {
public:
 virtual ~CharacterLifetimeBaseView() = 0;
};
class CharacterExLifetimeView : public CharacterLifetimeBaseView {
public:
 virtual ~CharacterExLifetimeView();
};
CharacterExLifetimeView::~CharacterExLifetimeView() {}
}
