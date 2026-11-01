import copy
import hashlib
from pathlib import Path
import sys
from types import SimpleNamespace
import unittest
from unittest.mock import patch, Mock
import tempfile
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import linked_pe as core
import linked_generated_origins as gen
from test_linked_pe import VTablePe


class LinkedGeneratedOriginTests(unittest.TestCase):
    def fixture(self,raw=b'\x8b\xc1'+b'\x90'*21+b'\xc3'):
        pe=VTablePe();pe.OPTIONAL_HEADER.SizeOfImage=0x5000;pe.data[0x1100:0x1100+len(raw)]=raw
        symbol='?_Ufill@?$vector@IV?$allocator@I@std@@@std@@IAEPAIPAIIABI@Z'
        anchor=dict(address='0x00402000',size=len(raw),symbol=symbol,sha256=hashlib.sha256(raw).hexdigest())
        functions={0x10001100:[(symbol,'i root.ltcg.obj')],0x10001100+len(raw):[('_after','root.ltcg.obj')]}
        rows=[dict(address='0x00401000',size='1',status='matching'),
              dict(address='0x00402000',size=str(len(raw)),status='unclassified')]
        target={0x401000:b'\xc3',0x402000:raw}
        read=lambda a,n:target[a][:n]
        spec=dict(schema_version=1,target_sha256='a'*64,unit='test',proof_roots=['0x00401000'],anchors=[anchor])
        units={'test':dict(kind='linked_candidate',profile=core.PROFILE,functions=[dict(address='0x00401000')])}
        args=dict(pe=pe,functions=functions,cil_owner='root.ltcg.obj',anchor=anchor,rows=rows,read_pe=read)
        return args,target,spec,units

    def test_whole_unmasked_unique_body(self):
        args,_,spec,units=self.fixture()
        gen.validate_spec(spec,[args['rows'][1]],units,args['rows'],'a'*64)
        r=gen.qualify(**args)
        self.assertEqual(r['masked_bytes'],0)
        self.assertEqual(r['canonical_rewrites'],0)
        self.assertEqual(r['nonrelocation_bytes'],24)
        self.assertEqual(r['inventory_matches'],['0x00402000'])

    def test_no_adjustable_masks_or_thresholds(self):
        changes=[lambda s:s.update(min_nonreloc_bytes=1),lambda s:s.update(max_alignment_tail=4),
                 lambda s:s.update(schema_version=True),lambda s:s.update(target_sha256='b'*64),
                 lambda s:s['anchors'][0].update(mask_offsets=[3]),
                 lambda s:s['anchors'][0].update(size=23),
                 lambda s:s['anchors'][0].update(symbol='?handwritten@Game@@QAEXXZ')]
        for change in changes:
            args,_,spec,units=self.fixture();change(spec)
            with self.assertRaises(ValueError):gen.validate_spec(spec,[args['rows'][1]],units,args['rows'],'a'*64)

    def test_requires_existing_matching_roots_in_same_real_unit(self):
        for roots in ([],['0x00402000'],['0x00401000','0x00401000']):
            args,_,spec,units=self.fixture();spec['proof_roots']=roots
            with self.assertRaises(ValueError):gen.validate_spec(spec,[args['rows'][1]],units,args['rows'],'a'*64)
        args,_,spec,units=self.fixture();units['test']['kind']='probe'
        with self.assertRaises(ValueError):gen.validate_spec(spec,[args['rows'][1]],units,args['rows'],'a'*64)

    def test_declared_selection_and_complete_hash_are_required(self):
        args,target,spec,units=self.fixture()
        with self.assertRaises(ValueError):gen.validate_spec(spec,[],units,args['rows'],'a'*64)
        args['anchor']['sha256']='0'*64
        with self.assertRaises(ValueError):gen.qualify(**args)

    def test_unique_cil_symbol_ownership_not_name_guess(self):
        for owner in ('other.ltcg.obj','CIL library: CIL module'):
            args,_,_,_=self.fixture();args['functions'][0x10001100]=[(args['anchor']['symbol'],owner)]
            with self.assertRaises(ValueError):gen.qualify(**args)
        args,_,_,_=self.fixture();args['functions'][0x10001100].append(('_alias','root.ltcg.obj'))
        with self.assertRaises(ValueError):gen.qualify(**args)

    def test_full_inventory_not_review_only_uniqueness(self):
        args,target,_,_=self.fixture();target[0x403000]=target[0x402000]
        args['rows'].append(dict(address='0x00403000',size='24',status='matching'))
        with self.assertRaisesRegex(ValueError,'whole candidate inventory'):gen.qualify(**args)

    def test_source_target_whole_bytes_and_extents_must_agree(self):
        for edit in (lambda b:b[:-1],lambda b:b[:-1]+b'\x90'):
            args,target,_,_=self.fixture();target[0x402000]=edit(target[0x402000])
            with self.assertRaises(ValueError):gen.qualify(**args)
        args,_,_,_=self.fixture();args['functions'][0x10001117]=[('_premature','root.ltcg.obj')]
        with self.assertRaises(ValueError):gen.qualify(**args)

    def test_no_pe_relocations_or_absolute_references(self):
        args,_,_,_=self.fixture();args['pe'].DIRECTORY_ENTRY_BASERELOC=[SimpleNamespace(entries=[SimpleNamespace(type=3,rva=0x1104)])]
        with self.assertRaises(ValueError):gen.qualify(**args)
        for raw in (bytes.fromhex('a100204000')+b'\x90'*18+b'\xc3',
                    bytes.fromhex('b800204000')+b'\x90'*18+b'\xc3'):
            args,_,_,_=self.fixture(raw)
            with self.assertRaises(ValueError):gen.qualify(**args)

    def test_calls_and_external_tails_are_not_generated_proof(self):
        for raw in (bytes.fromhex('e800100000')+b'\x90'*18+b'\xc3',
                    b'\x90'*22+bytes.fromhex('ffd0')+b'\xc3',
                    b'\x90'*22+bytes.fromhex('ffe0')):
            args,_,_,_=self.fixture(raw)
            with self.assertRaises(ValueError):gen.qualify(**args)

    def test_failed_fresh_exact_roots_block_all_helpers(self):
        args,_,spec,units=self.fixture()
        for reports in ([],[dict(address='0x00401000',result='mismatch',target_sha256='a',object_compared_sha256='b')],
                        [dict(address='0x00401000',result='exact',target_sha256='a',object_compared_sha256='b')]):
            with tempfile.TemporaryDirectory() as folder:
                root=Path(folder);anchor=root/'anchor.toml'
                anchor.write_text('schema_version=1\ntarget_sha256="'+spec['target_sha256']+'"\nunit="test"\nproof_roots=["0x00401000"]\n[[anchors]]\naddress="0x00402000"\nsize=24\nsymbol="'+args['anchor']['symbol']+'"\nsha256="'+args['anchor']['sha256']+'"\n')
                rule=dict(id='test',vc8_linked_generated_anchor_file='anchor.toml')
                with patch.object(gen,'ROOT',root), patch('workflow_manifest.load_manifest',return_value={'units':units}), \
                     patch.object(core,'comparator',return_value=Mock()), patch.object(core,'build_linked') as build, \
                     patch.object(core,'compare_linked',return_value=reports),patch.object(gen,'qualify') as qualify:
                    errors=gen.validate(rule,[args['rows'][1]],args['rows'],args['read_pe'],'a'*64)
                    self.assertTrue(errors);build.assert_called_once();qualify.assert_not_called()

    def test_no_helper_threshold_can_be_reduced(self):
        args,_,spec,units=self.fixture()
        for flag in ('mask_offsets','source_only','allow_nonexact_root','max_alignment_tail'):
            edited=copy.deepcopy(spec);edited[flag]=True
            with self.assertRaises(ValueError):gen.validate_spec(edited,[args['rows'][1]],units,args['rows'],'a'*64)

    def test_unreachable_code_and_trailing_code_are_not_dropped(self):
        raw=b'\xc3'+b'\x90'*22+b'\xc3';args,_,_,_=self.fixture(raw)
        with self.assertRaises(ValueError):gen.qualify(**args)


if __name__=='__main__':unittest.main()
