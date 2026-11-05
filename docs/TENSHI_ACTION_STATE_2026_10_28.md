
## Action 214 flight effect facing, 2026-11-05

Native `0x63F4B4..0x63F524` captures the unsigned effect-facing byte before sine and reloads signed facing after cosine for X. The earlier candidate read signed facing between the two lookups. Ordinary locals now preserve the two native read points; fresh VC8 captures direction at `0x20F5` and reloads signed facing at `0x212D`, after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 47784-byte root remains non-exact (candidate section tail 49032, first mismatch +8); no exact credit is claimed.
