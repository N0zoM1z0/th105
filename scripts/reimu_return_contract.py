"""Return-register contracts for the Reimu staging and void native probes."""
from __future__ import annotations


def validate_return_symbol(symbol, kind):
    suffixes = {"bool": "@@QAE_NXZ", "void": "@@QAEXXZ"}
    if kind not in suffixes or not symbol.endswith(suffixes[kind]):
        raise ValueError("candidate return contract differs from its noargs thiscall COFF symbol")


def pending_from_return(eax, kind="bool"):
    if kind == "void":
        return False  # A genuine void RET completes; EAX has no result meaning.
    if kind != "bool":
        raise ValueError("unknown candidate return contract")
    value = eax & 0xFF
    if value not in (0, 1):
        raise ValueError("staged dispatcher returned a non-bool result")
    return value == 0
