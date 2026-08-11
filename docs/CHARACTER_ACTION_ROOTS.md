# Character action-root survey

This is the breadth-first map for the fifteen character-specific action-change
and input/skill/spell dispatch roots. It was generated from one SHA-attested
IDA MCP session with:

```bash
python3 scripts/character-root-survey.py --kind action-change \
  --output build/character-action-survey.json
python3 scripts/character-root-survey.py --kind input-dispatch \
  --output build/character-input-survey.json
```

The function ledger remains authoritative for boundaries. Case values below
are observed switch labels in IDA pseudocode, not inferred gameplay names.
They provide address-bounded work packets and expose each character's normal,
skill, and spell families without claiming complete source reconstruction.

## Action-change roots

Every root dispatches from the fighter action word and directly calls
`0x00459970` to reset velocity/acceleration. Twelve IDA boundaries agree with
the ledger. IDA extends Reimu, Yukari, and Udonge by 18, 14, and 24 bytes;
those extra chunks are rejected and must not alter ledger sizes.

| Fighter | Address | Ledger bytes | IDA boundary | Observed action cases `>=198` |
| --- | ---: | ---: | --- | --- |
| Reimu | `0x00491480` | 3767 | conflict: 3785 | 214; 301–310; 320–322; 400–402; 404; 406; 408; 410; 412; 414; 416; 418; 500–503; 505–508; 510–513; 520–523; 525–526; 530–531; 540–541; 545–546; 550–551; 565–566; 600–602; 604–606; 608–610; 612; 614; 616; 619; 650–651; 658; 669; 695–696; 710–711; 720–721; 730–731; 740; 760; 797–798 |
| Marisa | `0x004B81F0` | 2446 | agrees | 300–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 420–422; 430–432; 504–506; 510; 512; 520–521; 525–526; 530–531; 540–542; 545; 547; 550–551; 560–563; 565–568; 570–573; 599–603; 605–608; 610–613; 615; 619; 658; 707–708; 710–711; 720–722; 730–733 |
| Sakuya | `0x004DDB20` | 2106 | agrees | 300–310; 320–322; 400–402; 404–406; 408–412; 414–416; 418; 501–506; 520–521; 525–526; 540–543; 545–548; 560–562; 565–566; 599–613; 615; 656; 707–708; 710–711; 720–722; 730; 740 |
| Alice | `0x004F9320` | 1551 | agrees | 198; 214; 300–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 501; 505–508; 520–523; 525–526; 530–531; 540–543; 545–548; 560; 565–566; 568; 570; 600–609; 710–711; 720–721; 730 |
| Patchouli | `0x0051D140` | 3132 | agrees | 198; 214; 300–310; 320–322; 400–402; 404; 406–412; 414–416; 418; 505–506; 520–521; 525–526; 540–542; 545–546; 560–561; 565–568; 580–581; 585–586; 600–607; 610; 612–613; 615; 651; 690; 700–710; 720–721; 730 |
| Youmu | `0x00539D70` | 1424 | agrees | 300–311; 320–323; 400–402; 404; 408; 410–412; 414–416; 418; 505–506; 510–511; 520–521; 525–526; 529–531; 540–541; 545–546; 560–561; 565–566; 570–571; 600–607; 710; 720; 730 |
| Remilia | `0x00554A00` | 1802 | agrees | 300–310; 320–322; 325; 400–402; 404; 406; 408–412; 414–416; 418; 505–506; 520–521; 525–526; 530–531; 540–542; 545–547; 560–561; 565–567; 599–608; 610–613; 615; 707–711; 720–721; 730–731; 740 |
| Yuyuko | `0x0056C490` | 2083 | agrees | 300–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 502–503; 505–508; 510–513; 520–523; 525–526; 540–541; 545–547; 560–562; 565–567; 599–608; 610–613; 615; 651; 657; 700–710; 720; 725–726; 730–731 |
| Yukari | `0x00589F20` | 3441 | conflict: 3455 | 214; 301–310; 320–322; 400–402; 404; 406; 408; 410–412; 414–416; 418; 500–503; 505–506; 510–511; 520–523; 525–526; 540–543; 545–548; 562–563; 565–566; 600–607; 615; 656; 700–701; 708; 710; 720–721; 730; 740–741; 750; 797–798 |
| Suika | `0x005ACC10` | 2577 | agrees | 300–310; 320–322; 330–331; 400–402; 404–406; 408–412; 414–416; 418; 505–508; 520–523; 525–526; 530–531; 540–542; 545–546; 560–561; 565–567; 599–608; 610–613; 615; 650; 700–711; 720; 730; 740; 751 |
| Udonge | `0x005D4610` | 4033 | conflict: 4057 | 214; 302–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 500–501; 505–506; 510–511; 520–521; 525–531; 540–541; 545–546; 550–551; 565–568; 600; 602–603; 605–609; 650; 652; 655; 700–710; 725–726; 730; 797–798 |
| Komachi | `0x005F5DE0` | 1971 | agrees | 300–310; 320–322; 400–402; 404–406; 408–412; 414–416; 418; 505–508; 510–511; 520–521; 525–526; 540–543; 545–546; 550–551; 560–561; 565–566; 599–606; 611–613; 615; 710–711; 720; 730; 732 |
| Aya | `0x006166A0` | 2049 | agrees | 300–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 502; 505–508; 510; 520–523; 525–533; 540; 545–546; 550–554; 560–561; 565; 567; 600–606; 611–612; 661–662; 710; 720–721; 730; 740 |
| Iku | `0x0062F4B0` | 1842 | agrees | 300–310; 320–322; 400–402; 404; 406; 408–412; 414–418; 501; 505–506; 520–521; 525–526; 540–541; 545–547; 560–563; 565–568; 570–573; 599–603; 605–613; 615; 650; 660; 710; 720; 730; 740 |
| Tenshi | `0x006495C0` | 2453 | agrees | 300–310; 320–322; 400–402; 404; 406; 408–412; 414–416; 418; 505; 520–521; 525–527; 540; 542; 545–548; 560–561; 565–566; 599–607; 657; 700; 720; 730–731; 740–741; 750; 788; 795; 797–798 |

## Input, skill, and spell dispatch roots

All fifteen IDA boundaries agree with the ledger. Every dispatcher directly
reaches the same fourteen shared command helpers: `0x00493300`, `0x00493380`,
`0x00493490`, `0x00493540`, `0x00493580`, `0x004935D0`, `0x00493920`,
`0x00493A10`, `0x00493B00`, `0x00493C90`, `0x0045B9E0`, `0x0045BBB0`,
`0x004631E0`, and `0x00434860`. The mirrored `200/201` gate at `0x004937D0`
has fourteen dispatcher callers. This proves that character work should retain
one shared command prelude and reconstruct only the character-specific branch
tails.

| Fighter | Address | Bytes | Observed record/action cases |
| --- | ---: | ---: | --- |
| Reimu | `0x00494050` | 6952 | 200–201; 206; 208–210; 214; 219; 300; 320–321 |
| Marisa | `0x004B9A60` | 7664 | 200–219; 300; 320–321 |
| Sakuya | `0x004DEF70` | 5897 | 200–209; 300; 320–321 |
| Alice | `0x004FA5C0` | 6677 | 200–209; 300; 320–321 |
| Patchouli | `0x0051EA60` | 6351 | 200–207; 210 |
| Youmu | `0x0053B040` | 6017 | 200–207; 300; 320–322 |
| Remilia | `0x00555D90` | 5415 | 200–207 |
| Yuyuko | `0x0056D8E0` | 6180 | 200–208 |
| Yukari | `0x0058BBA0` | 6233 | 200–207; 215; 300; 320–321 |
| Suika | `0x005AE470` | 5849 | 200–208; 300; 320–321 |
| Udonge | `0x005D63F0` | 6684 | 200; 202–203; 205–209; 300; 320–321 |
| Komachi | `0x005F7190` | 6181 | 200–206; 211; 300; 320–321 |
| Aya | `0x00617B20` | 7161 | 200–202; 205–206; 211–212; 300; 320–321 |
| Iku | `0x00630800` | 6302 | 200–203; 205–210 |
| Tenshi | `0x0064AB80` | 5352 | 200–207 |

## Work allocation

Use one character per bounded lane. Begin with an IDA work packet for its
action-change root and input dispatcher, retain the shared command declarations,
and split source by normal `300/320/400`, skill `500`-series, spell `600`-series,
and character terminal/special `700+` groups. Boundary-conflicted action roots
must compare only the ledger span until direct target instructions prove any
additional bytes belong to that entry.
