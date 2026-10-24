#ifndef TH105_MARISA_CPU_POLICY_HPP
#define TH105_MARISA_CPU_POLICY_HPP
namespace th105 {
// Pointer-only call views. Do not construct or embed either receiver.
class MarisaCpuPolicyView { public: void update_cpu_action_policy(); };
class MarisaCpuSequenceView { public: short *at(unsigned index); };
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y, float x);
}
#endif
