/* sub_410430 @ 00410430   75 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_410430(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  uVar1 = _DAT_005833e0 & 0xff;
  puVar3 = (undefined4 *)
           ((&PTR_DAT_00573d68)[uVar1 * 6] + *(int *)(&DAT_00573d74 + uVar1 * 0x18) * 0x1c);
  puVar4 = &DAT_00573d28;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  _DAT_00572298 = *(undefined4 *)(&DAT_00573d78 + uVar1 * 0x18);
  DAT_005848cc = *(undefined4 *)(&DAT_00573d7c + uVar1 * 0x18);
  return;
}

