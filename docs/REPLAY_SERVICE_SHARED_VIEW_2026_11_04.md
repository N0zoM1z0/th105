# Shared replay service view

The replay header reader, replay-list formatter, menu browse and refresh now
share one pointer-only `ReplayHeaderServiceView`. Both observed methods are on
the same receiver returned by `get_replay_header_service`; the view is never
constructed and does not claim the complete service layout. This removes
conflicting separate declarations while preserving the target-backed member
symbols and calling conventions.

Fresh replay preserves the exact 313-byte header reader and its complete 48-byte
EH code and 44-byte metadata audit; the 159-byte list constructor, 501-byte list
formatter, and 229-byte menu refresh also remain exact. The browse candidate
remains nonexact and its entire compared candidate SHA remains unchanged at
`a9291ef45090e8a2ba5f8296f72c566b65a1c0034b14a818709c4e6dab139dae`.
No exact bytes are added, and no whole-application link or real file I/O is
claimed. Receipts: `build/frontier-replay-service-owner-20261104/`.
All 1,030 target-independent CI tests and generated-progress checks passed.
