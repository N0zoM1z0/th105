# Fighter character wave handles

Fighter `+0x164` holds an array of 64 four-byte character wave handles. Base
initialization allocates and constructs the array; `0x45F680` loads numbered
`data/se/<character>/%03d.wav` resources into it, and Character destruction
releases each handle before deleting the array. The loader and destructor now
share the same element declaration rather than describing the array as bare
unsigned values in one place.

For Japanese TH10.5 1.06a, the complete wave loader and its two adjacent
resource functions remained exact under the pinned VC8 profile. The Character
destructor retained its prior nonexact candidate hash; sharing the handle type
does not change its status.
