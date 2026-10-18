"""Finite input controls for the original Japanese 1.06a Reimu CPU root.

These initialize actor/container/RNG inputs, never helper results. They are
diagnostic samples, not proof of all numerical or gameplay behavior.
"""
import itertools
import random


def reimu_edge_cases():
    base = dict(action=201, sequence=200, self_x=100.0, other_x=250.0,
                self_y=0.0, other_y=0.0, vx=0.0, vy=0.0, other_action=100,
                resource=1000, mode=3, facing=1, counter=100, policy=-1,
                timer=10, refresh=1, seed=0)
    actions = (200, 300, 301, 302, 303, 304, 305, 306, 307, 308, 320, 321,
               400, 401, 402, 404, 405, 406, 410, 411, 414, 416)
    positions = ((100., -1), (100., 1), (880., 1), (881., 1), (980., 1),
                 (981., 1), (300., -1), (299., -1), (200., -1), (199., -1))
    resources = (-1, 199, 200, 299, 300, 399, 400, 599, 600, 800, 1000)
    counters = (-32768, -1, *range(102), 32767)
    for action, counter, resource in itertools.product(actions, counters, resources):
        index = action * 107 + counter * 13 + resource
        x, facing = positions[index % len(positions)]
        distance = (50., 150., 300., 500., 700.)[index % 5]
        yield dict(base, action=action, counter=counter, resource=resource,
                   self_x=x, facing=facing, other_x=x + facing * distance,
                   self_y=(0., 100., 300.)[index % 3],
                   other_y=(0., 100., 300.)[(index // 3) % 3],
                   sequence=200 + index % 15, skill609=(-1, 0, 1)[index % 3],
                   skill60b=(-1, 0, 1)[(index // 3) % 3])

    # Cancel sequence and signed flag controls bypass later policy selection.
    for action, sequence, counter, variant in itertools.product(
            (302, 303, 304, 305, 306, 307, 400, 404, 410, 414), range(200, 215),
            (85, 94, 95, 96, 100, 101), range(4)):
        x, facing = positions[(sequence + variant) % len(positions)]
        yield dict(base, action=action, sequence=sequence, counter=counter,
                   self_x=x, facing=facing, skill609=(-1, 0, 1, 127)[variant],
                   skill60b=(-1, 0, 1, 127)[variant],
                   sequence_count=(-1, 0, 1, 2)[variant])

    # Keep policy0 live to exercise common attacks. The seed is an input to
    # original MT code, including its normal discarded first draw.
    rng = random.Random(0x48D390)
    distances = (49., 50., 74., 75., 79., 80., 89., 90., 91., 99., 100.,
                 119., 120., 149., 150., 179., 180., 199., 200., 209., 210.,
                 219., 220., 239., 240., 249., 250., 279., 280., 299., 300.,
                 319., 320., 349., 350., 399., 400., 479., 480., 519., 520.,
                 599., 600., 699., 700.)
    for _ in range(16000):
        x = rng.choice((100., 600., 1000.))
        facing = rng.choice((-1, 1))
        distance = rng.choice(distances)
        yield dict(base, policy=0, other_action=0, self_x=x,
                   other_x=x + facing * distance, facing=facing,
                   self_y=rng.choice((0., 50., 100., 200., 300., 500.)),
                   other_y=rng.choice((0., 50., 100., 200., 300., 500.)),
                   vx=rng.choice((-3., 0., 3.)), vy=rng.choice((-3., 0., 3.)),
                   resource=rng.choice(resources), sequence=rng.randrange(200, 215),
                   skill609=rng.choice((-1, 0, 1)), skill60b=rng.choice((-1, 0, 1)),
                   seed=rng.getrandbits(32) & 255)

    # Masked invalid x87 conversion and ordered wall/height predicates.
    for action, bits, key, seed in itertools.product(
            actions, ("7fc00000", "7f800001", "7f800000", "ff800000"),
            ("self_x", "self_y", "other_x", "other_y"), (0, 1)):
        case = dict(base, action=action, counter=95, sequence=214, policy=0, seed=seed)
        case[key + "_bits"] = bits
        yield case
