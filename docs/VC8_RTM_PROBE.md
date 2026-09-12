# VC8 RTM compiler discriminator

## Why test it

The target's Rich build 50727 does not identify a patch revision. The default
private toolchain is SP1 `14.00.50727.762`. Microsoft's
[SP1 back-end change list](https://devblogs.microsoft.com/cppblog/vc2005-sp1-bug-fixes-back-end/)
confirms that the backend changed; it does not explain this game's mismatch.
An RTM experiment must therefore be measured, not assumed equivalent or
assumed to fix the remaining shared giants.

## Official media and pinned extracted payload

The [Microsoft Visual C++ 2005 Express ISO](https://download.microsoft.com/download/A/9/1/A91D6B2B-A798-47DF-9C7E-A97854B7DD18/VC.iso)
is 485,089,280 bytes. Its ISO9660 directory places `Ixpvc.exe` at byte
2,111,488 with size 67,101,880. The payload's embedded CAB contains
`vcsetup.msi` and `vcsetup1.cab`; the MSI identifies the compiler as
`14.0.50727.42`. HTTP range retrieval was verified with a 206 response and
the expected Content-Range. Only this payload is needed, not the whole IDE CD.

```bash
set -eu
mkdir -p build/references/vc8/rtm-media
curl --fail --location --range 2111488-69213367 --max-filesize 67101880 \
  --output build/references/vc8/rtm-media/Ixpvc.exe \
  https://download.microsoft.com/download/A/9/1/A91D6B2B-A798-47DF-9C7E-A97854B7DD18/VC.iso
printf '%s  %s\n' \
  dedb3f0bdf709f97638cfd264c9dad5c1c4967c6f3d5e88ffa473d1ab29408d9 \
  build/references/vc8/rtm-media/Ixpvc.exe | sha256sum -c -
7z x -y -obuild/references/vc8/rtm-media build/references/vc8/rtm-media/Ixpvc.exe
msiextract -C .tools/msvc80-rtm-media build/references/vc8/rtm-media/vcsetup.msi
```

No installer executable is run. `msiextract` preserves the MSI's colon/pipe
directory spellings. On a fresh destination, prepare the compiler-only tree:

```bash
set -eu
test ! -e .tools/msvc80-rtm
rtm_image='.tools/msvc80-rtm-media/Program Files/Microsoft Visual Studio 8:VS80.NET|Microsoft Visual Studio 8'
mkdir .tools/msvc80-rtm
cp -a "$rtm_image/VC:Vc7|Vc7/bin:bin|bin" .tools/msvc80-rtm/bin
cp -a "$rtm_image/VC:Vc7|Vc7/include:include|include" .tools/msvc80-rtm/include
for rtm_pdb in mspdb80.dll mspdbcore.dll mspdbsrv.exe; do
  cp "$rtm_image/Common7:Common7|Common7/IDE:IDE|IDE/$rtm_pdb" .tools/msvc80-rtm/bin/
done
ln -s ../msvc80-sp1/PlatformSDK .tools/msvc80-rtm/PlatformSDK
```

The compiler and C++ headers are RTM; Platform SDK headers deliberately reuse
the existing private SDK. This is a bounded compiler experiment, not a claim
that the original game's complete toolchain installation has been recovered.
Binary/compiler files remain ignored. An earlier incomplete full ISO download
is only `build/references/vc8/VC2005Express.iso.partial`, not verified media.

| Extracted file | SHA-256 |
| --- | --- |
| `bin/cl.exe` | `3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7` |
| `bin/c1xx.dll` | `e4890058a1f928538b27246af1f5c6f95551fc0ad380639b1bf1d6b143b80d09` |
| `bin/c2.dll` | `ebca6ef587d6e028b50cc79fe71dd6155230ecb51014295399e8f00e8865ff86` |

## Measured common-Fighter result

```bash
TH105_MSVC8_ROOT="$PWD/.tools/msvc80-rtm" bash scripts/compile-unit.sh \
  src/battle/FighterCommonActionState.cpp build/common-rtm-baseline.obj
python3 scripts/compare-unit-object.py gpt-web-fighter-common-action-state \
  build/common-rtm-baseline.obj --address 0x004740C0 --json
```

With source at `3883d1e`, RTM and SP1 produce the same canonicalized
10,219-byte comparison-window hash:
`e738dea4320b968d3a5b217c5101f15cc07a300e96ce4bce632fa4528d898bac`.
Both still differ from target at +0x14, have a 10,809-byte section tail and
51/66 instruction/edge-identical diagnostic owners. RTM is **not** an
explanation for this retained source's discrepancy. This does not exclude
other original source, visibility or LTCG contexts.

The existing-object CLI performs no build and verifies no compiler provenance;
it reuses only the unit's relocation and boundary contract. It must not be
used to relabel RTM output as an accepted SP1 build. No match ledger or
default compiler profile is changed by this experiment.
