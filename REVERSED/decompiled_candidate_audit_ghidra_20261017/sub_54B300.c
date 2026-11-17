/* Selected Ghidra export at 0054b300. */

void sub_54B300(void)

{
  DWORD DVar1;
  DWORD DVar2;
  uint uVar3;
  int iVar4;
  undefined1 auStack_40 [64];
  
  sub_562717(auStack_40,s__d_d_d_COR_00579044,DAT_00584eb4,DAT_00584eb8,DAT_00584ebc);
  sub_43B790(auStack_40);
  sub_43B8A0();
  sub_439490();
  DVar1 = timeGetTime();
  sub_40F060(PTR_DAT_005724dc + 0x18,PTR_DAT_005724dc + 0x118);
  DVar2 = timeGetTime();
  uVar3 = DVar2 - DVar1;
  while ((uVar3 < 0x2711 && (iVar4 = sub_40E630(), iVar4 == 0))) {
    sub_40F060(PTR_DAT_005724dc + 0x18,PTR_DAT_005724dc + 0x118);
    DVar2 = timeGetTime();
    uVar3 = DVar2 - DVar1;
  }
  sub_415390(1);
  DAT_00584700 = 0xc;
  sub_415340();
  return;
}

