# Score sequence result update

The game-owned method at `0x0042CF70` checks the game and session modes, finds
the first matching 24-byte score record and increments its sequence-result
counter. Direct expressions for the actual vector's begin and end preserve the
checked iterator's owner validation without inserting manual checks.

The configured VC8 build and a separately compiled object each compare 159/159
against the target. Both resolved bodies have SHA-256
`6c772b740b8d672b600fec4ddb0211bad97c315d5148309f710c2d12a46e8922`.
The previous 142-byte result and its native observer remain historical. The
independent Factory acceptance is pending, so this source-present function
receives no exact credit yet. No new gameplay or exception-equivalence claim is
made.
