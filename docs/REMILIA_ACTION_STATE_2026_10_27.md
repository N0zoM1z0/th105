
### Fan and orbit direction reads (2026-11-05)

The pinned target's fan-817, ring-902 and object-903 paths capture unsigned direction before sine and reload signed facing after cosine, for example `0x54C4BA..0x54C538`, `0x551E08..0x551E9C` and `0x553784..0x5537F4`. The earlier candidate used an early cached signed value. The source now makes the two reads explicit while retaining the angle and radius reloads and original coordinate associations. Rebuilt dispatch code shows the later signed read at four fan-817 sites, eight ring-902 sites and the object-903 site. Trig helpers do not ordinarily mutate the receiver; no normal-play effect is claimed from this ordering correction.

Strict callable-boundary comparison remains nonmatching: target 61,962 bytes, candidate section tail 63,100 bytes, first difference +47. The separate 63,316-byte original full payload includes tables; neither size comparison establishes exactness or adds match credit.
