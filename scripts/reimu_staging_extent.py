"""Execution bounds for the unaccepted Reimu source probe and its switch data."""
from __future__ import annotations


def staging_execution_extent(text_size, callable_size, *, allow_switch_metadata=False,
                             metadata_start=None, metadata_limit=None):
    if text_size <= 0 or callable_size <= 0:
        raise ValueError("staging text/callable size must be positive")
    if text_size <= callable_size:
        return text_size
    if not allow_switch_metadata:
        raise ValueError("staging text exceeds the reviewed callable extent")
    if (metadata_start is None or metadata_limit is None
            or not 0 < metadata_start <= callable_size < text_size <= metadata_limit):
        raise ValueError("staging code or switch data exceeds its reviewed extent")
    # The caller must obtain metadata_start from the validated COFF switch map.
    # This bounds execution before data; it does not accept a compiler boundary.
    return metadata_start
