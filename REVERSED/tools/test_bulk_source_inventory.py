import csv
import struct
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from make_bulk import (CODE_LABEL_RE, DEC, apply_bulk_patches, collect_source_files, is_game_code,
                       normalize, rename_definition, rewrite_manual_switches, rewrite_verified_e9_tail_jump,
                       undeclared_locals,
                       unresolved_artifacts,
                       sanitize_signature_names,
                       rewrite_pointer_integer_switches)  # noqa: E402


class BulkSourceInventoryTests(unittest.TestCase):
    def test_explicit_register_parameter_is_not_reported_as_unresolved_artifact(self):
        body = "void render(int in_EAX) { *(int *)in_EAX = 7; }\n"
        self.assertEqual(unresolved_artifacts(body, "void render(int in_EAX)"), set())

    def test_unmodeled_register_input_remains_reported(self):
        body = "void render(void) { *(int *)in_EAX = 7; }\n"
        self.assertEqual(unresolved_artifacts(body, "void render(void)"), {"in_EAX"})

    def test_stack_local_detector_recognizes_byte_and_char_declarations(self):
        body = """void render(void)
{
  byte bStack_132;
  char cStack_131;
  bStack_132 = 1;
  cStack_131 = 0;
}
"""
        self.assertEqual(undeclared_locals(body), set())

    def test_stack_local_detector_still_reports_a_missing_stack_local(self):
        body = "void render(void) { bStack_132 = 1; }\n"
        self.assertEqual(undeclared_locals(body), {"bStack_132"})

    def test_prototype_signatures_use_the_same_sanitized_names_as_definitions(self):
        signature = "int Catch@0040fb87(int value)"
        self.assertEqual(
            sanitize_signature_names(signature, {"Catch@0040fb87": "Catch_0040fb87"}),
            "int Catch_0040fb87(int value)",
        )

    def test_real_exception_handlers_are_not_redeclared_as_void_code_labels(self):
        function_names = {"Catch_0040fb87"}
        referenced = {"Catch@0040fb87", "Unwind@0056d91c"}
        normalized = {sanitize_signature_names(name, {"Catch@0040fb87": "Catch_0040fb87"})
                      for name in referenced}
        unresolved = normalized - function_names
        self.assertEqual(unresolved, {"Unwind@0056d91c"})

    def test_verified_e9_thunk_emits_a_naked_tail_jump(self):
        address = 0x402750
        target = 0x402760
        displacement = target - (address + 5)
        machine_code = b"\xE9" + struct.pack("<i", displacement)
        source = """/* sub_402750 @ 00402750 5 bytes */
undefined sub_402750(void)
{
  return FUN_00402760();
}
"""
        rewritten, matched = rewrite_verified_e9_tail_jump(
            source, "sub_402750", machine_code)
        self.assertTrue(matched)
        self.assertIn("__declspec(naked) undefined sub_402750(void)", rewritten)
        self.assertIn("__asm { jmp FUN_00402760 }", rewritten)
        self.assertNotIn("return FUN_00402760();", rewritten)

    def test_e9_thunk_rewrite_requires_machine_and_source_targets_to_match(self):
        address = 0x402750
        machine_code = b"\xE9" + struct.pack("<i", 0x402770 - (address + 5))
        source = "undefined sub_402750(void) { return FUN_00402760(); }"
        rewritten, matched = rewrite_verified_e9_tail_jump(
            source, "sub_402750", machine_code)
        self.assertFalse(matched)
        self.assertEqual(rewritten, source)

    def test_default_build_inventory_uses_the_complete_fresh_ghidra_harvest(self):
        self.assertEqual(DEC, ROOT / "decompiled_ghidra_complete_20261018_all")
        sources = collect_source_files([DEC], ROOT / "src_recovered")
        self.assertEqual(len(sources), 1728)
        self.assertEqual(sources["sub_43CB20"][0], ROOT / "src_recovered" / "sub_43CB20.c")
        self.assertEqual(sources["sub_43CB30"][0], ROOT / "src_recovered" / "sub_43CB30.c")

    def test_internal_413cc0_continuation_is_merged_into_the_recovered_parent(self):
        sources = collect_source_files([DEC], ROOT / "src_recovered")
        self.assertNotIn("sub_413CC0", sources)
        self.assertEqual(sources["sub_413C40"][0], ROOT / "src_recovered" / "sub_413C40.c")

    def test_rewrites_ghidra_manual_switch_with_binary_table_case_order(self):
        source = """int f(void) {
  switch((&switchD_00401000::switchdataD_00402000)[BYTE_0040202c]) {
  case (undefined *)0x403000:
    third();
    break;
  case (undefined *)0x401000:
    first();
    break;
  case (undefined *)0x402000:
    second();
    break;
  }
}
"""
        table = [0x401000, 0x402000, 0x403000]
        rewritten, count = rewrite_manual_switches(
            source, lambda address, entries: table if address == 0x402000 and entries == 3 else [])
        self.assertEqual(count, 1)
        self.assertIn("switch ((unsigned char)BYTE_0040202c)", rewritten)
        self.assertIn("case 2:\n    third();", rewritten)
        self.assertIn("case 0:\n    first();", rewritten)
        self.assertIn("case 1:\n    second();", rewritten)
        self.assertNotIn("switchD_", rewritten)
        self.assertNotIn("undefined *)", rewritten)

    def test_rewrites_pointer_typed_integer_switch_using_pointer_width(self):
        source = """void f(float *local_10) {
  switch(local_10) {
  case (float *)0x217:
  case (float *)0x235:
    work();
    break;
  }
}
"""
        rewritten, count = rewrite_pointer_integer_switches(source)
        self.assertEqual(count, 1)
        self.assertIn("switch ((uintptr_t)local_10)", rewritten)
        self.assertIn("case 0x217:", rewritten)
        self.assertIn("case 0x235:", rewritten)
        self.assertNotIn("case (float *)", rewritten)

    def test_internal_ghidra_auto_names_are_not_mistaken_for_external_code(self):
        self.assertTrue(is_game_code("FUN_0041e440"))
        self.assertTrue(CODE_LABEL_RE.match("FUN_0041e440"))
        self.assertTrue(is_game_code("Catch@0040fb87"))
        self.assertTrue(is_game_code("Unwind@0056d6ab"))
        self.assertFalse(is_game_code("DirectDrawCreate"))
        self.assertFalse(is_game_code("__CxxThrowException"))

    def test_checked_in_compile_patches_fix_verified_errors(self):
        patch_path = ROOT / "src_generated" / "bulk_patches.csv"
        with patch_path.open(encoding="utf-8") as f:
            rows = list(csv.DictReader(f))

        cases = [
            ("sub_547750", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00547750.c",
             "sub_547710(param_1,&local_4,param_3);",
             "sub_547710(param_1,&local_4);"),
            ("sub_56B126", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B126.c",
             "sub_56AB70();", "((void (*)(void))sub_56AB70)();"),
            ("sub_56B139", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B139.c",
             "sub_56AB70();", "((void (*)(void))sub_56AB70)();"),
            ("sub_567FDB", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_567FDB.c",
             "SetUnhandledExceptionFilter(DAT_006da430);",
             "SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)DAT_006da430);"),
            ("sub_408EE0", ROOT / "src_recovered" / "sub_408EE0.c",
             "    case 4:\n    }", "    case 4:\n      break;\n    }"),
            ("sub_40AAB0", ROOT / "src_recovered" / "sub_40AAB0.c",
             "  case 3:\n  }", "  case 3:\n    break;\n  }"),
            ("sub_40A030", ROOT / "src_recovered" / "sub_40A030.c",
             "param_7 = (uint *)param_10;",
             "param_7 = (uint *)(*(uint *)&param_10);"),
            ("sub_56C7DF", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056C7DF.c",
             "sub_56A73D();", "sub_56A73D(param_1);"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pMMStream_>GetMediaStream_MSPID__00572a54",
             "s_pMMStream__GetMediaStream_MSPID__00572a54"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pPrimaryVidStream_>QueryInterfac_005729e0",
             "s_pPrimaryVidStream__QueryInterfac_005729e0"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pDDStream_>CreateSample_NULL__NU_00572990",
             "s_pDDStream__CreateSample_NULL__NU_00572990"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pSample_>GetSurface__pSurface____00572948",
             "s_pSample__GetSurface__pSurface____00572948"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pSurface_>QueryInterface_IID_IDi_005728e0",
             "s_pSurface__QueryInterface_IID_IDi_005728e0"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pMMStream_>SetState_STREAMSTATE__0057289c",
             "s_pMMStream__SetState_STREAMSTATE__0057289c"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "s_pMMStream_>SetState_STREAMSTATE__00572854",
             "s_pMMStream__SetState_STREAMSTATE__00572854"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "sub_414600();", "sub_414600((const char *)ppiStack_238,iVar1);"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "(*(code *)*puRam00000000)(0);",
             "((HRESULT (WINAPI *)(void *,const GUID *,void **))(*(void ***)local_204[2])[0])((void *)local_204[2],(const GUID *)&DAT_0056e60c,(void **)&ppiStack_8);"),
            ("sub_41F0C0", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0041F0C0.c",
             "int sub_41F0C0(int *param_1,int *param_2)",
             "int sub_41F0C0(int *param_1,int *param_2,int *param_3)"),
            ("sub_409290", ROOT / "src_recovered" / "sub_409290.c",
             "param_2 = (ushort *)((float)(uVar1 & 0x3e0) * _DAT_0056e124);",
             "*(float *)&param_2 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;"),
            ("sub_409290", ROOT / "src_recovered" / "sub_409290.c",
             "(float)param_2 * _DAT_0056e134", "*(float *)&param_2 * _DAT_0056e134"),
            ("sub_409290", ROOT / "src_recovered" / "sub_409290.c",
             "(float)param_2 * _DAT_0056e140", "*(float *)&param_2 * _DAT_0056e140"),
            ("sub_409290", ROOT / "src_recovered" / "sub_409290.c",
             "param_2 = (ushort *)((float)param_2 * _DAT_0056e158);",
             "*(float *)&param_2 = *(float *)&param_2 * _DAT_0056e158;"),
            ("sub_40AD30", ROOT / "src_recovered" / "sub_40AD30.c",
             "param_2 = (ushort *)((float)((byte)uVar1 & 0x1f) * _DAT_0056e11c);",
             "*(float *)&param_2 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;"),
            ("sub_40AD30", ROOT / "src_recovered" / "sub_40AD30.c",
             "param_1 = (uint *)((float)(uVar1 & 0x3e0) * _DAT_0056e124);",
             "*(float *)&param_1 = (float)(uVar1 & 0x3e0) * _DAT_0056e124;"),
            ("sub_40AD30", ROOT / "src_recovered" / "sub_40AD30.c",
             "(float)param_1 * _DAT_0056e134", "*(float *)&param_1 * _DAT_0056e134"),
            ("sub_40AD30", ROOT / "src_recovered" / "sub_40AD30.c",
             "(float)param_2 * _DAT_0056e138", "*(float *)&param_2 * _DAT_0056e138"),
            ("sub_40AD30", ROOT / "src_recovered" / "sub_40AD30.c",
             "switchD_0040adbb_caseD_1:\n", "switchD_0040adbb_caseD_1:;\n"),
            ("sub_40AF10", ROOT / "src_recovered" / "sub_40AF10.c",
             "switchD_0040b592_caseD_1:\n", "switchD_0040b592_caseD_1:;\n"),
            ("sub_40AF10", ROOT / "src_recovered" / "sub_40AF10.c",
             "switchD_0040b35d_caseD_1:\n", "switchD_0040b35d_caseD_1:;\n"),
            ("sub_40AF10", ROOT / "src_recovered" / "sub_40AF10.c",
             "switchD_0040b125_caseD_1:\n", "switchD_0040b125_caseD_1:;\n"),
            ("sub_40B750", ROOT / "src_recovered" / "sub_40B750.c",
             "switchD_0040be40_caseD_1:\n", "switchD_0040be40_caseD_1:;\n"),
            ("sub_40B750", ROOT / "src_recovered" / "sub_40B750.c",
             "switchD_0040bbef_caseD_1:\n", "switchD_0040bbef_caseD_1:;\n"),
            ("sub_40B750", ROOT / "src_recovered" / "sub_40B750.c",
             "switchD_0040b998_caseD_1:\n", "switchD_0040b998_caseD_1:;\n"),
            ("sub_4321E0", ROOT / "src_recovered" / "sub_4321E0.c",
             "(float)pfStack_130", "*(float *)&pfStack_130"),
            ("sub_43A110", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0043A110.c",
             "param_4 = (float *)((float)iVar2 * pfVar9[param_1] - pfVar9[3]);",
             "*(float *)&param_4 = (float)iVar2 * pfVar9[param_1] - pfVar9[3];"),
            ("sub_43A110", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0043A110.c",
             "(float)param_4", "*(float *)&param_4"),
            ("sub_43A110", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0043A110.c",
             "param_4 = (float *)(float)fVar12;", "*(float *)&param_4 = (float)fVar12;"),
            ("sub_56D188", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D188.c",
             "exception::~exception(this);", "sub_56D64F((undefined4 *)this);"),
            ("sub_56D23E", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D23E.c",
             "exception::~exception(this);", "sub_56D64F((undefined4 *)this);"),
            ("sub_56D326", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D326.c",
             "exception::~exception(this);", "sub_56D64F((undefined4 *)this);"),
            ("Unwind_0056d91c", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D91C.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x14));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x14));"),
            ("Unwind_0056d930", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D930.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d944", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D944.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d958", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D958.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d980", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D980.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("sub_56814E", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056814E.c",
             "NAN(", "_isnan("),
            ("sub_559A46", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00559A46.c",
             "void sub_559A46(int param_1,int param_2)",
             "void sub_559A46(int in_EAX,int param_1,int param_2)"),
            ("sub_559A46", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00559A46.c",
             "  int in_EAX;", ""),
            ("sub_55DC20", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0055DC20.c",
             "sub_559A46();", "sub_559A46(param_1,param_2,param_3);"),
            ("sub_55E8B6", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0055E8B6.c",
             "sub_559A46();", "sub_559A46(param_1,param_2,param_3);"),
            ("sub_55F55C", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0055F55C.c",
             "sub_559A46();", "sub_559A46(param_1,param_2,param_3);"),
            ("sub_5601F2", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_005601F2.c",
             "sub_559A46();", "sub_559A46(param_1,param_2,param_3);"),
            ("sub_43A610", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0043A610.c",
             "sub_43A110(4);", "sub_43A110(4,param_2,param_3,pfVar2);"),
            ("sub_56D1E1", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D1E1.c",
             "undefined4 * sub_56D1E1(void)", "undefined4 * sub_56D1E1(int param_1)"),
            ("sub_56D0FA", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056D0FA.c",
             "undefined4 * sub_56D0FA(void)", "undefined4 * sub_56D0FA(int param_1)"),
            ("sub_56B376", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B376.c",
             "fVar2 = fVar2 - (float10)(unkint10)(fVar2 / fVar3) * fVar3;",
             "fVar2 = (float10)fmod((double)fVar2,(double)fVar3);"),
            ("sub_56B62E", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B62E.c",
             "fVar2 = fVar2 - (float10)(unkint10)(fVar2 / fVar3) * fVar3;",
             "fVar2 = (float10)fmod((double)fVar2,(double)fVar3);"),
            ("sub_56B57C", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B57C.c",
             "return in_ST0 - (float10)(unkint10)(in_ST0 / in_ST1) * in_ST1;",
             "return (float10)fmod((double)in_ST0,(double)in_ST1);"),
            ("sub_56B834", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B834.c",
             "return in_ST0 - (float10)(unkint10)(in_ST0 / in_ST1) * in_ST1;",
             "return (float10)fmod((double)in_ST0,(double)in_ST1);"),
            ("sub_56B57C", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B57C.c",
             "(float10)sub_56B376()", "((float10 (*)())sub_56B376)()"),
            ("sub_56B57C", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B57C.c",
             "(float10)sub_56B376(in_ST1 * (float10)dRam0057d064)",
             "((float10 (*)())sub_56B376)(in_ST1 * (float10)dRam0057d064)"),
            ("sub_56B834", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B834.c",
             "(float10)sub_56B62E()", "((float10 (*)())sub_56B62E)()"),
            ("sub_56B834", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_56B834.c",
             "(float10)sub_56B62E(in_ST1 * (float10)dRam0057d064)",
             "((float10 (*)())sub_56B62E)(in_ST1 * (float10)dRam0057d064)"),
            ("sub_56B361", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_0056B361.c",
             "sub_56AB70();", "((uint (*)())sub_56AB70)();"),
            ("sub_568519", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00568519.c",
             "sub_5683D0();", "((float10 (*)())sub_5683D0)();"),
            ("sub_563382", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00563382.c",
             "uVar2 = sub_568519();", "uVar2 = ((undefined4 (*)())sub_568519)();"),
            ("sub_5679DD", ROOT / "decompiled_candidate_audit_ghidra_20261017" / "sub_5679DD.c",
             "uVar1 = sub_56AB58();", "uVar1 = ((undefined4 (*)())sub_56AB58)();"),
            ("sub_563382", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00563382.c",
             "  short in_FPUControlWord;",
             "  short in_FPUControlWord; undefined4 _local_4;"),
            ("sub_563382", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00563382.c",
             "  unkbyte10 in_ST7;", "  undefined1 in_ST7[10];"),
            ("sub_563382", ROOT / "decompiled_ghidra_12_1_4_fixed" / "sub_00563382.c",
             "auStack_e = (undefined1  [10])in_ST7;",
             "memcpy(auStack_e,in_ST7,sizeof(auStack_e));"),
            ("sub_56B57C", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056B57C.c",
             "(float10)sub_56B376(in_ST1 * (float10)_DAT_0057d064)",
             "((float10 (*)())sub_56B376)(in_ST1 * (float10)_DAT_0057d064)"),
            ("sub_56B834", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056B834.c",
             "(float10)sub_56B62E(in_ST1 * (float10)_DAT_0057d064)",
             "((float10 (*)())sub_56B62E)(in_ST1 * (float10)_DAT_0057d064)"),
            ("Unwind_0056d91c", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056D91C.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x14));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x14));"),
            ("Unwind_0056d930", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056D930.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d944", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056D944.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d958", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056D958.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
            ("Unwind_0056d980", ROOT / "decompiled_ghidra_complete_20261018_all" / "sub_0056D980.c",
             "exception::~exception(*(exception **)(unaff_EBP + -0x10));",
             "sub_56D64F(*(undefined4 **)(unaff_EBP + -0x10));"),
        ]
        for function, path, old, new in cases:
            with self.subTest(function=function):
                body = path.read_text(encoding="utf-8")
                if function == "sub_559A46":
                    body = normalize(body)
                function_patches = [
                    (r["find"], r["replace"])
                    for r in rows
                    if r["function"] == function
                    and (r["find"] in body
                         or r["replace"].split(" /* PATCH:", 1)[0] in body)
                ]
                patched, count, missing = apply_bulk_patches(body, function_patches)
                # Recovered overrides may carry a verified fix directly. Treat that
                # as satisfied while still requiring every unapplied CSV transformation
                # to be present in its replacement form.
                already_applied = [find for find in missing
                                   if any(find == old and
                                          replacement.split(" /* PATCH:", 1)[0] in body
                                          for old, replacement in function_patches)]
                self.assertEqual(count + len(already_applied), len(function_patches))
                self.assertTrue(all(any(find == old and
                                        replacement.split(" /* PATCH:", 1)[0] in body
                                        for old, replacement in function_patches)
                                    for find in missing))
                self.assertIn(new, patched)
                if old not in new:
                    self.assertNotIn(old, patched)

    def test_recovered_source_overrides_export_by_normalized_function_identity(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            fixed = root / "fixed"
            supplemental = root / "supplemental"
            recovered = root / "recovered"
            for directory in (fixed, supplemental, recovered):
                directory.mkdir()

            with (fixed / "_index.csv").open("w", newline="", encoding="utf-8") as f:
                writer = csv.DictWriter(f, fieldnames=["name", "address", "file"])
                writer.writeheader()
                writer.writerow({"name": "sub_401000", "address": "00401000",
                                 "file": "sub_00401000.c"})
            (fixed / "sub_00401000.c").write_text(
                "int sub_401000(void) { return 1; }\n", encoding="utf-8")
            (supplemental / "sub_402000.c").write_text(
                "int sub_402000(void) { return 2; }\n", encoding="utf-8")
            # The hand-recovered filename has a leading zero, while its definition
            # and the fixed export use the normalized address spelling.
            (recovered / "sub_00401000.c").write_text(
                "int sub_401000(void) { return 3; }\n", encoding="utf-8")

            sources = collect_source_files([fixed, supplemental], recovered)

            self.assertEqual(set(sources), {"sub_401000", "sub_402000"})
            self.assertEqual(sources["sub_401000"][0].parent, recovered)
            self.assertEqual(sources["sub_402000"][0].parent, supplemental)

    def test_verified_ghidra_exports_form_unique_build_sources_with_merged_fragments_removed(self):
        sources = collect_source_files([DEC], ROOT / "src_recovered")

        # The harvest contains 1,686 addresses; recovered callbacks and EH
        # thunks add 39 definitions, while sub_413CC0 is an interior fragment.
        self.assertEqual(len(sources), 1724)
        self.assertTrue(all(path.is_file() for path, _ in sources.values()))
        self.assertIn("sub_56D64F", sources)
        self.assertEqual(sources["sub_56D64F"][0], ROOT / "src_recovered" / "sub_56D64F.c")
        self.assertEqual(sources["sub_5632D2"][0], ROOT / "src_recovered" / "sub_5632D2.c")
        self.assertIn("sub_54FBD0", sources)
        self.assertIn("sub_43CB30", sources)
        self.assertEqual(sources["sub_43CB30"][0].parent.name, "src_recovered")
        for name in ("sub_56D910", "sub_56D924", "sub_56D974"):
            with self.subTest(function=name):
                self.assertEqual(sources[name][0].parent.name, "src_recovered")
        for name in ("sub_54DA90", "sub_54DAC0", "sub_54E880", "sub_54F710"):
            with self.subTest(function=name):
                self.assertEqual(sources[name][0].parent.name, "src_recovered")
        for name in ("sub_4150E0", "sub_415160", "sub_4152E0"):
            with self.subTest(function=name):
                self.assertEqual(sources[name][0].parent.name, "src_recovered")

    def test_duplicate_symbol_repair_renames_only_function_definition(self):
        body = "/* sub_545030 @ 0043cb30 */\n\nvoid sub_545030(void)\n\n{\n}\n"

        renamed = rename_definition(body, "sub_545030", "sub_43CB30")

        self.assertIn("/* sub_545030 @ 0043cb30 */", renamed)
        self.assertIn("void sub_43CB30(void)", renamed)


if __name__ == "__main__":
    unittest.main()
