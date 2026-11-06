
## Action 721 destination and facing (2026-11-06)

The native destination comparison `0x51BE83..0x51BEBD` chooses `580 - random`
for current X at least 640 or unordered, and `700 + random` otherwise. Native
`0x51BF0E..0x51BF2B` chooses facing +1 for destination X at least current X or
unordered, and -1 otherwise. The previous ordered `>=` expressions chose the
opposite paths for unordered comparisons. Both source conditions now use the
negated ordered `<` form; finite results are unchanged. Normal-play occurrence
of unordered positions is unknown.

The focused VC8 candidate emits the corresponding `test ah,0x41` conditions at
`0xCCD8` and `0xCD60`, with inverted branch layout. The full root remains
nonexact, section tail 55,646, compared SHA-256
`8aa50027ef8dfad39a00dd2b82a009ffacc9ba8c6c7f664e33eb08d3917ec05b`.
No full-function or exact-byte credit is claimed.
