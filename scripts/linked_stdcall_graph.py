"""A complete ordinary stdcall leaf in a bounded, exact-rooted real CIL graph.

Intermediate bodies provide provenance/edges, not byte-equivalence credit.
The leaf still requires its own full canonical comparison with named callees.
"""
import hashlib
import re
import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM


def validate(contract, function, unit):
    address=lambda x:isinstance(x,str) and re.fullmatch(r'0x[0-9A-Fa-f]{8}',x)
    if (not isinstance(contract,dict)
            or set(contract)!={'caller','through_exact_caller','stdcall_graph'}
            or not address(contract['caller']) or contract['through_exact_caller'] is not True):
        raise ValueError('stdcall graph needs its distinct freshly exact exported root')
    if (not re.fullmatch(r'\?[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@YGI.+@Z',function['symbol_base'])
            or any(k in function for k in ('export_name','eh_cleanup','alignment_sites',
                'private_static_leaf','vtable_entry','private_global','private_texture_global'))):
        raise ValueError('stdcall graph leaf must be an ordinary unsigned-return stdcall without alternate contracts')
    roots=[f for f in unit['functions'] if f['address']==contract['caller']]
    if (len(roots)!=1 or roots[0] is function
            or any(k in roots[0] for k in ('private_from','private_global','private_texture_global','vtable_entry'))
            or unit.get('link_runtime')!='static' or unit.get('link_objects')):
        raise ValueError('stdcall graph needs one public real static-runtime source root')
    graph=contract['stdcall_graph']
    if (not isinstance(graph,dict) or set(graph)!={'stack_bytes','nodes','edges'}
            or type(graph['stack_bytes']) is not int or not 4<=graph['stack_bytes']<=32
            or graph['stack_bytes']%4 or not isinstance(graph['nodes'],list)
            or not 1<=len(graph['nodes'])<=4 or not isinstance(graph['edges'],list)
            or not 2<=len(graph['edges'])<=8):
        raise ValueError('stdcall graph needs bounded nodes/edges and observed stack cleanup')
    addresses={contract['caller'],function['address']};symbols={roots[0]['symbol_base'],function['symbol_base']}
    if len(addresses)!=2:raise ValueError('stdcall graph cannot witness itself')
    configured={f['address'] for f in unit['functions']}
    for node in graph['nodes']:
        if (not isinstance(node,dict) or set(node)!={'address','symbol_base'}
                or not address(node['address']) or node['address'] in addresses or node['address'] in configured
                or not isinstance(node['symbol_base'],str)
                or not re.fullmatch(r'\?[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@QAE.+',node['symbol_base'])
                or node['symbol_base'] in symbols):
            raise ValueError('stdcall graph intermediate must be a distinct ordinary private member')
        addresses.add(node['address']);symbols.add(node['symbol_base'])
    pairs=set();adj={a:set() for a in addresses};incoming={a:set() for a in addresses}
    for e in graph['edges']:
        if (not isinstance(e,dict) or set(e)!={'caller','callee','sites'}
                or not address(e['caller']) or not address(e['callee'])
                or e['caller'] not in addresses or e['callee'] not in addresses
                or e['caller']==function['address'] or e['callee']==contract['caller']
                or e['caller']==e['callee'] or (e['caller'],e['callee']) in pairs
                or not isinstance(e['sites'],list) or not 1<=len(e['sites'])<=4
                or any(not address(a) for a in e['sites'])
                or [int(a,0) for a in e['sites']]!=sorted({int(a,0) for a in e['sites']})):
            raise ValueError('stdcall graph edges must be unique complete ordered E8 site sets')
        pairs.add((e['caller'],e['callee']));adj[e['caller']].add(e['callee']);incoming[e['callee']].add(e['caller'])
    def reach(start,edges):
        todo=[start];seen=set()
        while todo:
            a=todo.pop()
            if a not in seen:seen.add(a);todo.extend(edges[a])
        return seen
    if reach(contract['caller'],adj)!=addresses or reach(function['address'],incoming)!=addresses:
        raise ValueError('all stdcall graph nodes must lie on an exact-root-to-leaf path')
    grey=set();black=set()
    def visit(a):
        if a in grey:raise ValueError('stdcall graph cannot be cyclic')
        if a in black:return
        grey.add(a)
        for b in adj[a]:visit(b)
        grey.remove(a);black.add(a)
    visit(contract['caller'])


def source_paths(unit):
    from workflow_manifest import source_dependencies,repository_path
    return {str(p) for p in source_dependencies(unit)},repository_path


def observe(core,function,unit,pe,functions,exports,cil_owner,ledger,read_target,
            report,bindings,game_range):
    contract=function['private_from'];validate(contract,function,unit)
    graph=contract['stdcall_graph'];root=next(f for f in unit['functions'] if f['address']==contract['caller'])
    paths,resolve_path=source_paths(unit)
    nodes=[root,*graph['nodes'],function];facts={};source_rows={};target_rows={};starts={};raws={}
    for node in nodes:
        address=node['address'];row=ledger.get(address,{})
        if (row.get('status') not in ('implemented','matching')
                or str(resolve_path(row.get('source_file',''))) not in paths):
            raise ValueError('stdcall graph node has no reviewed source in the actual included TU')
        private=node is not root
        selector=dict(node)
        if private:selector['private_from']={}
        start=core.source_function_start(selector,functions,exports,cil_owner)
        raw=core.linked_body(pe,functions,start);target=read_target(int(address,0),int(row['size'],0))
        sr=core.decode_closed_body(raw,start);tr=core.decode_closed_body(target,int(address,0))
        source_rows[address]=sr;target_rows[address]=tr;starts[address]=start;raws[address]=raw
        facts[address]=dict(address=address,symbol=node['symbol_base'],source_file=row['source_file'],
            source_va=f'0x{start:08X}',source_size=len(raw),target_size=len(target),
            source_sha256=hashlib.sha256(raw).hexdigest(),target_sha256=hashlib.sha256(target).hexdigest(),
            source_address_roles=core.caller_data_witness(pe,sr,functions,bindings,game_range))
    rf=facts[root['address']]
    if (not report or ledger[root['address']]['status']!='matching' or report.get('result')!='exact'
            or report.get('address')!=root['address'] or report.get('linked_function_va')!=rf['source_va']
            or report.get('source_body_sha256')!=rf['source_sha256']
            or report.get('target_sha256')!=rf['target_sha256']
            or report.get('object_compared_sha256')!=rf['target_sha256']):
        raise ValueError('stdcall graph root lacks its fresh complete exact canonical replay')
    core.validate_body_relocations(pe,starts[root['address']],len(raws[root['address']]),report['validated_data_references'])
    declared={(e['caller'],e['callee']):e['sites'] for e in graph['edges']};edges=[]
    def calls(rows,dest):
        return [i.address for i in rows if i.mnemonic=='call' and i.size==5 and i.bytes[0]==0xe8
                and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==dest]
    for caller in nodes:
        for callee in nodes:
            pair=(caller['address'],callee['address']);wanted=declared.get(pair,[])
            ss=calls(source_rows[pair[0]],starts[pair[1]])
            ts=calls(target_rows[pair[0]],int(pair[1],0))
            if ts!=[int(a,0) for a in wanted] or len(ss)!=len(ts):
                raise ValueError('stdcall graph differs in declared or additional real call edges: '+str(pair))
            if wanted:edges.append(dict(caller=pair[0],callee=pair[1],target_sites=wanted,source_sites=[f'0x{a:08X}' for a in ss]))
    leaf=function['address'];cleanup=graph['stack_bytes']
    for rows in (source_rows[leaf],target_rows[leaf]):
        returns=[i for i in rows if i.mnemonic.startswith('ret')]
        if not returns or any(i.mnemonic!='ret' or int(i.op_str or '0',0)!=cleanup for i in returns):
            raise ValueError('stdcall leaf does not retain its complete observed stack cleanup')
        for i in rows:
            for op in i.operands:
                if op.type==X86_OP_MEM and (op.mem.segment or (not op.mem.base and not op.mem.index)):
                    raise ValueError('stdcall leaf cannot have absolute/segmented state or EH registration')
    core.validate_body_relocations(pe,starts[leaf],len(raws[leaf]),[])
    for a in graph['nodes']:
        if a['symbol_base']+'='+a['address'] in root.get('rel32_targets',[]):continue
        if (root['address'],a['address']) in declared:
            raise ValueError('exact graph root must name every actual first-level callee binding')
    return dict(caller=root['address'],source_leaf_va=f'0x{starts[leaf]:08X}',nodes=list(facts.values()),
        edges=edges,stack_bytes=cleanup,
        exact_root={k:report[k] for k in ('address','source_body_sha256','object_compared_sha256','target_sha256')},
        scope='exact source root and complete closed caller graph; intermediate byte/semantic equivalence not claimed')


def validate_leaf_replay(calls,references):
    if references or any(not isinstance(c,dict) or 'symbol' not in c or 'target' not in c for c in calls):
        raise ValueError('stdcall graph leaf permits only fully named ordinary call relocations, not data bindings')
