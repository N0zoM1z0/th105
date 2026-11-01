import copy
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_pe as core
import linked_stdcall_graph as graph
from test_linked_pe import VTablePe


class StdcallGraphTests(unittest.TestCase):
    def fixture(self,leaf=bytes.fromhex('8b4424048b54240833c0c20800')):
        source=[0x10001000+i*0x100 for i in range(5)]
        native=[0x401000+i*0x1000 for i in range(5)]
        symbols=['?play@Owner@@QAE_NXZ','?start@Owner@@QAE_NXZ','?update@Owner@@QAE_NXZ',
                 '?handoff@Owner@@QAE_NXZ','?fill@scope@@YGIPAX0@Z']
        def call(a,b):return b'\xe8'+struct.pack('<i',b-a-5)
        def bodies(addresses):
            p,s,u,h,f=addresses
            return [call(p,s)+b'\xc3',call(s,u)+call(s+5,u)+call(s+10,h)+b'\xc3',
                    b'\x6a\x00\x6a\x00'+call(u+4,f)+b'\xc3',
                    b'\x6a\x00\x6a\x00'+call(h+4,f)+b'\xc3',leaf]
        sb,tb=bodies(source),bodies(native);pe=VTablePe();functions={};ledger={}
        root=dict(address='0x00401000',symbol_base=symbols[0],rel32_targets=[symbols[1]+'=0x00402000'])
        f=dict(address='0x00405000',symbol_base=symbols[4],private_from=dict(caller=root['address'],through_exact_caller=True,
            stdcall_graph=dict(stack_bytes=8,nodes=[dict(address=f'0x{native[i]:08X}',symbol_base=symbols[i]) for i in (1,2,3)],
                edges=[dict(caller='0x00401000',callee='0x00402000',sites=['0x00401000']),
                       dict(caller='0x00402000',callee='0x00403000',sites=['0x00402000','0x00402005']),
                       dict(caller='0x00402000',callee='0x00404000',sites=['0x0040200A']),
                       dict(caller='0x00403000',callee='0x00405000',sites=['0x00403004']),
                       dict(caller='0x00404000',callee='0x00405000',sites=['0x00404004'])])))
        unit=dict(kind='linked_candidate',profile=core.PROFILE,source='src/fixture.cpp',object='build/root.dll',
                  link_runtime='static',link_runtime_data=['___security_cookie'],link_data_targets=[],functions=[root,f])
        for i,(a,b,t) in enumerate(zip(source,sb,tb)):
            pe.data[a-0x10000000:a-0x10000000+len(b)]=b
            functions[a]=[(symbols[i],'root.ltcg.obj')];functions[a+len(b)]=[('_after_'+str(i),'root.ltcg.obj')]
            ledger[f'0x{native[i]:08X}']=dict(size=str(len(t)),source_file='src/fixture.cpp' if i==0 else 'src/nested.cpp',status='matching' if i==0 else 'implemented')
        target=dict(zip(native,tb));report=dict(result='exact',address=root['address'],linked_function_va='0x10001000',
            source_body_sha256=hashlib.sha256(sb[0]).hexdigest(),target_sha256=hashlib.sha256(tb[0]).hexdigest(),
            object_compared_sha256=hashlib.sha256(tb[0]).hexdigest(),validated_data_references=[])
        args=dict(function=f,unit=unit,pe=pe,functions=functions,exports={symbols[0]:source[0]},cil_owner='root.ltcg.obj',
                  ledger=ledger,read_target=lambda a,n:target[a][:n],exact_caller_replay=report)
        return args,target

    def run_graph(self,args):
        with patch.object(graph,'source_paths',return_value=({'src/fixture.cpp','src/nested.cpp'},lambda p:p)):
            return core.private_caller_witness(**args)

    def test_full_real_graph_and_exact_root(self):
        args,_=self.fixture();core.validate_contract(args['unit'],set());r=self.run_graph(args)
        self.assertEqual(len(r['nodes']),5);self.assertEqual(len(r['edges']),5)
        self.assertEqual(sum(len(e['target_sites']) for e in r['edges']),6)
        self.assertEqual(r['stack_bytes'],8)
        self.assertEqual(r['exact_root']['address'],'0x00401000')

    def test_rejects_loose_contract_and_fabricated_abi(self):
        changes=[lambda f:f['private_from'].update(through_exact_caller=False),
                 lambda f:f['private_from'].update(source_only_caller=True),
                 lambda f:f['private_from']['stdcall_graph'].update(stack_bytes=True),
                 lambda f:f['private_from']['stdcall_graph'].update(stack_bytes=3),
                 lambda f:f.update(symbol_base='?fill@scope@@QAEIXZ'),
                 lambda f:f.update(eh_cleanup={}),lambda f:f.update(export_name='export_fill')]
        for change in changes:
            args,_=self.fixture();change(args['function'])
            with self.assertRaises(ValueError):core.validate_contract(args['unit'],set())

    def test_root_must_be_public_distinct_and_freshly_exact(self):
        for change in (lambda r:r.update(result='mismatch'),lambda r:r.update(source_body_sha256='0'*64),
                       lambda r:r.update(target_sha256='0'*64),lambda r:r.update(object_compared_sha256='0'*64),
                       lambda r:r.update(linked_function_va='0x10009999')):
            args,_=self.fixture();change(args['exact_caller_replay'])
            with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();args['ledger']['0x00401000']['status']='implemented'
        with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();args['unit']['functions'][0]['private_from']={}
        with self.assertRaises(ValueError):core.validate_contract(args['unit'],set())

    def test_graph_cannot_have_cycles_or_unrelated_nodes(self):
        args,_=self.fixture();g=args['function']['private_from']['stdcall_graph'];g['edges'].append(dict(caller='0x00403000',callee='0x00402000',sites=['0x00403000']))
        with self.assertRaisesRegex(ValueError,'cyclic'):core.validate_contract(args['unit'],set())
        args,_=self.fixture();g=args['function']['private_from']['stdcall_graph'];g['edges']=g['edges'][:-1]
        with self.assertRaises(ValueError):core.validate_contract(args['unit'],set())

    def test_missing_extra_or_wrong_actual_sites_are_rejected(self):
        args,_=self.fixture();args['function']['private_from']['stdcall_graph']['edges'][1]['sites']=['0x00402000']
        with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();args['pe'].data[0x1105:0x110a]=b'\x90'*5
        with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();args['function']['private_from']['stdcall_graph']['edges'][0]['sites']=['0x00401001']
        with self.assertRaises(ValueError):self.run_graph(args)

    def test_root_must_bind_its_actual_first_level_callee(self):
        args,_=self.fixture();args['unit']['functions'][0]['rel32_targets']=[]
        with self.assertRaisesRegex(ValueError,'first-level'):self.run_graph(args)

    def test_every_node_must_have_reviewed_included_source(self):
        for change in (lambda r:r.update(source_file='src/unquoted.cpp'),lambda r:r.update(status='unclassified')):
            args,_=self.fixture();change(args['ledger']['0x00403000'])
            with self.assertRaises(ValueError):self.run_graph(args)

    def test_private_nodes_cannot_be_aliased_exported_or_from_other_objects(self):
        args,_=self.fixture();args['functions'][0x10001200].append(('_alias','root.ltcg.obj'))
        with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();sym=args['functions'][0x10001200][0][0];args['exports'][sym]=0x10001200
        with self.assertRaises(ValueError):self.run_graph(args)
        args,_=self.fixture();sym=args['functions'][0x10001200][0][0];args['functions'][0x10001200]=[(sym,'other.obj')]
        with self.assertRaises(ValueError):self.run_graph(args)

    def test_leaf_cleanup_must_match_all_real_return_paths(self):
        args,target=self.fixture();b=target[0x405000][:-2]+b'\x04\x00';target[0x405000]=b;args['pe'].data[0x1400:0x1400+len(b)]=b
        with self.assertRaisesRegex(ValueError,'stack cleanup'):self.run_graph(args)

    def test_leaf_must_not_use_address_relocations_or_absolute_state(self):
        args,_=self.fixture();args['pe'].DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[SimpleNamespace(type=3,rva=0x1402)])]
        with self.assertRaises(ValueError):self.run_graph(args)
        for b in (bytes.fromhex('a10020400033c0c20800'),bytes.fromhex('64a10000000033c0c20800')):
            args,_=self.fixture(b)
            with self.assertRaises(ValueError):self.run_graph(args)

    def test_only_fully_named_calls_not_data_rewrites(self):
        graph.validate_leaf_replay([dict(symbol='_read',target=0x401000)],[])
        for calls,refs in [([{}],[]),([],[dict(kind='literal')])]:
            with self.assertRaises(ValueError):graph.validate_leaf_replay(calls,refs)

    def test_old_source_only_contract_remains_rejected_without_eh(self):
        args,_=self.fixture();args['function']['private_from']=dict(caller='0x00401000',site='0x00401000',source_only_caller=True)
        with self.assertRaisesRegex(ValueError,'source-only caller requires'):core.validate_contract(args['unit'],set())


if __name__=='__main__':unittest.main()
