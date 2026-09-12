# Official VC8 reference library

Use this index to consult the **Visual Studio 2005** documentation when
reconstructing TH105. Repository notes and documentation are hypotheses or
external corroboration; neither overrides freshly attested target instructions
or a reproducible compiler experiment. Exact acceptance remains the complete
canonical comparison.

## Source identity

Microsoft publishes the retired Visual Studio 2005 MSDN collection at its
[official Download Center](https://www.microsoft.com/en-us/download/details.aspx?id=55984).
The selected English Visual C++ volume is
[VS2005_CPP_en-us.pdf](https://download.microsoft.com/download/1/6/d/16d24ada-5317-4de1-b2b2-890b51813d6e/VS2005_CPP_en-us.pdf).

The downloaded file contains **28,890 pages / 109,198,568 bytes**. Its SHA-256 is
`ca6831ccd92d5198fc9f71e0f49c0603b00202acd47b11d500d8e786fcfab509`.
The PDF metadata dates its creation to 2017-01-17; the landing page currently
lists 2024-07-15. Neither date makes this a modern MSVC manual: Microsoft
identifies the collection as Visual Studio 2005 documentation. It does not,
however, identify TH105's original compiler patch level or optimization profile.
The full provenance and physical page ranges are in
[reference-documents.toml](../config/reference-documents.toml).

## Agent reading route

Start with the small [local Markdown index](../build/references/vc8/INDEX.md).
Each topic extract records the source URL, PDF hash and one-based physical PDF
page numbers. Plain-text code blocks preserve the extracted layout without
pretending that PDF tables have been reconstructed perfectly.

The full searchable text is
`build/references/vc8/VS2005_CPP_en-us.txt`. The original PDF stays available for
checking ambiguous tables. All downloaded and generated material stays below
`build/`, outside Git; this guide, source manifest and retrieval script are the
durable repository records. No compiler binaries are downloaded by this tool.

LeanToken's indexed `read` currently rejects these ignored local files. Use its
live `json` lane instead: each topic has a `.json` sibling with `pages`, each
containing `number` and `lines`. For example, query
`build/references/vc8/topics/1627-1628-floating-point-model-fp.json` with
JMESPath `pages[0].lines[0:35]`. This route was tested against the actual MCP.
`scripts/reference-vc8.py --topics` prints the exact Markdown paths; `--search`
returns bounded hits with physical page numbers. Use `--pages FIRST:LAST` to
read directly from the hash-verified PDF when the text cache is unavailable.

```bash
python3 scripts/reference-vc8.py --fetch
python3 scripts/reference-vc8.py --verify
python3 scripts/reference-vc8.py --extract-text
python3 scripts/reference-vc8.py --extract-topics
python3 scripts/reference-vc8.py --topics
python3 scripts/reference-vc8.py --search 'Stack double alignment' --limit 5
python3 scripts/reference-vc8.py --pages 1804:1806
```

Python 3.11+ and Poppler's `pdftotext` are sufficient. Fetching verifies size and
SHA-256 before publishing the download; existing mismatched PDFs fail closed.
Text extraction can take about a minute. Search validates both the original PDF
and the text-cache provenance. `--pages` is bounded to 20 pages per request.
Do not silently update the pinned hash if Microsoft changes the download.

## Topics relevant to matching

| Question | Physical PDF pages |
| --- | --- |
| Available compiler switches and their categories | 1577–1590 |
| x86 `/arch` and SSE selection | 1591–1592 |
| Exception handling model | 1606–1608 |
| Floating-point precision, rounding and exceptions | 1627–1628 |
| Whole-program compilation | 1638–1639 |
| Security-cookie and parameter handling | 1641–1643 |
| Function COMDAT packaging | 1646 |
| Optimization bundles, inlining, global optimization, frame omission | 1660–1672 |
| LTCG, private calling conventions, stack alignment | 1804–1806 |
| x86 arguments, returns and calling conventions | 26784–26794 |
| Per-function floating-point control | 27035–27037 |

## How this informs the current giant-root investigation

The `/fp` topic distinguishes intermediate x87 precision from required float
rounding at source boundaries. A decompiler's `double` temporary is therefore
not automatically an original source local; conversely, replacing it with
`float` can move the rounding point. Check the resulting instruction stream.

The LTCG topic distinguishes speed and size profiles for x86 double alignment,
and explains when private calling-convention changes are possible. Consequently,
one `/O2 /GL` experiment with the wrong frame does **not** establish that all
LTCG profiles are impossible. This motivates bounded experiments; it does not
justify inventing private ABI declarations or assuming TH105 used LTCG here.

The manual is not a specification of switch destination order, tail-merge
selection, register colors or exact opcode encoding. Such claims still require
the pinned VC8 compiler and canonical TH105 evidence. Modern Microsoft Learn
pages may describe later defaults or extensions; use their explicit version
boundaries before applying them to VC8.
