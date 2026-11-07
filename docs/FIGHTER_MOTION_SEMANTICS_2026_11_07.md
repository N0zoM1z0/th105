# Fighter motion fields

The shared `Fighter` view now names `+0xF4/+0xF8` as X/Y velocity and `+0xFC/+0x100` as X/Y acceleration, matching the existing motion-reset view. The exact zero-motion helper at `0x45AF40` clears all four, the exact position integrator at `0x45AE30` consumes the two velocity components, and target-backed action paths independently write vertical velocity and acceleration. These are semantic role names, not recovered original member spelling.

The X velocity is not by itself a world-X displacement: `0x45AE30` combines it with collision and peer-motion components, applies facing and horizontal scale, checks stage boundaries, and then moves the fighter. Y velocity is scaled separately before the stage-surface clamp. The body-collision resolver also uses X velocity when computing separation. Keeping those operations visible avoids confusing local-facing motion with world coordinates.

The three affected units with matching roots, including the complete body-collision and position-integrator roots, remain exact. The fighter battle reset was already nonexact. Both shared-header lifetime-origin proofs and the fighter-input deque origin proof were rebuilt and passed; no classification changed.
