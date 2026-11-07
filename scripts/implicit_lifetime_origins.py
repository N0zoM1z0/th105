"""Complete canonical origin proofs for reviewed implicit C++ lifetimes.

No masked fingerprints or coverage exceptions. Each owner is freshly built;
source declarations reviewed as implicit are hash-pinned with their headers.
"""
import hashlib
from pathlib import Path
import tomllib
from build import build_unit, compare_unit
from workflow_manifest import ROOT, load_manifest, repository_path, compiler_sha256
from rank_retained_exact import read_coff_function
from scalar_wrapper_origins import verify_comparisons

COMPILER = "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c"

def validate_spec(spec, selected, rows, units, target_sha):
    if (set(spec)!={"schema_version","target_sha256","compiler_sha256","sources","anchors"}
            or type(spec['schema_version'])is not int or spec['schema_version']!=1
            or spec['target_sha256']!=target_sha or spec['compiler_sha256']!=COMPILER):
        raise ValueError('implicit lifetime target/compiler/schema mismatch')
    sources=spec['sources'];anchors=spec['anchors'];by={r['address']:r for r in rows}
    if not isinstance(sources,list) or not sources or len({s['path']for s in sources})!=len(sources):
        raise ValueError('implicit lifetime source review missing or duplicate')
    for s in sources:
        if set(s)!={'path','sha256'} or not str(s['path']).startswith('src/'):
            raise ValueError('implicit lifetime needs reviewed repository source')
        if hashlib.sha256(repository_path(s['path']).read_bytes()).hexdigest()!=s['sha256']:
            raise ValueError('implicit lifetime declaration changed; renew its ownership review')
    if (not anchors or len({a['address']for a in anchors})!=len(anchors)
            or {a['address']for a in anchors}!={r['address']for r in selected}):
        raise ValueError('implicit lifetime selection mismatch')
    groups={}
    for a in anchors:
        if (set(a)!={'address','size','sha256','unit','symbol_base','emitted_symbol','kind'}
                or type(a['size'])is not int or a['size']<=0
                or a['address']not in by or int(by[a['address']]['size'],0)!=a['size']):
            raise ValueError('implicit lifetime extent/schema mismatch')
        prefix={'destructor':'??1','copy_constructor':'??0','default_constructor':'??0'}.get(a['kind'])
        if prefix is None or not a['emitted_symbol'].startswith(prefix):
            raise ValueError('implicit lifetime emitted member kind differs')
        if a['kind']=='default_constructor' and not a['emitted_symbol'].endswith('@@QAE@XZ'):
            raise ValueError('implicit default constructor must be parameterless ordinary thiscall')
        u=units.get(a['unit'],{})
        if (u.get('kind')!='probe' or u.get('profile')!='vc8-sp1-probe-o2'
                or u.get('source')not in {s['path']for s in sources}):
            raise ValueError('implicit lifetime must use its reviewed ordinary owner')
        fs=[f for f in u['functions']if int(f['address'],0)==int(a['address'],0)]
        if len(fs)!=1 or fs[0]['symbol_base']!=a['symbol_base']:
            raise ValueError('implicit lifetime source selector differs')
        groups.setdefault(a['unit'],[]).append(a)
    return groups


def validate(rule, selected, rows, read, target_sha):
    try:
        path=repository_path(rule['implicit_lifetime_anchor_file'])
        spec=tomllib.loads(path.read_text());units=load_manifest()['units']
        groups=validate_spec(spec,selected,rows,units,target_sha)
        if compiler_sha256()!=COMPILER:raise ValueError('implicit lifetime compiler changed')
        for name,anchors in groups.items():
            # Fresh builds must not overwrite other validators' pinned objects.
            unit=dict(units[name])
            unit['object']=str(Path('build/origin-anchors/implicit-lifetimes') / path.stem / (name + '.obj'))
            build_unit(name,unit,True,target_sha)
            obj=repository_path(unit['object'],output=True)
            for a in anchors:
                actual,body,wild,relocs=read_coff_function(obj,a['symbol_base'],None)
                if actual!=a['emitted_symbol'] or len(body)!=a['size']:
                    raise ValueError('implicit lifetime needs its complete emitted member')
                if hashlib.sha256(read(int(a['address'],0),a['size'])).hexdigest()!=a['sha256']:
                    raise ValueError('implicit lifetime native body changed')
            wanted={int(a['address'],0)for a in anchors};view=dict(unit)
            view['functions']=[f for f in unit['functions']if int(f['address'],0)in wanted]
            rc,reports=compare_unit(view,True);verify_comparisons(anchors,reports)
            if rc:raise ValueError('implicit lifetime canonical comparison failed')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError)as exc:
        return [str(rule['id'])+': '+str(exc)]
