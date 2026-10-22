"""Fail-closed Python callbacks for native emulation engines.

The caller owns the error list, clears it before execution and raises from it
immediately after execution, before accepting any observation.
"""


def guarded_callback(callback, errors):
    def invoke(engine, *arguments):
        try:
            callback(engine, *arguments)
        except Exception as error:
            errors.append(str(error))
            engine.emu_stop()
    return invoke
