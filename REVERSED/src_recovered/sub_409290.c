/* Selected Ghidra export at 00409290. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_409290(uint *param_1,ushort *param_2,int param_3,int param_4,char param_5)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  float fStack_8;
  float fStack_4;
  
  iVar6 = 0;
  puVar7 = param_2;
  if (0 < param_4) {
    do {
      uVar1 = *puVar7;
      fStack_8 = (float)((byte)uVar1 & 0x1f) * _DAT_0056e11c;
      param_2 = (ushort *)((float)(uVar1 & 0x3e0) * _DAT_0056e124);
      fStack_4 = (float)(uVar1 & 0x7c00) * _DAT_0056e12c;
      if (((uVar1 & 0x8000) != 0) && (*(char *)(iVar6 + param_3) != '\0')) {
        switch(*(char *)(iVar6 + param_3)) {
        case '\x01':
          if (DAT_006d7c6f != '\0') {
            fStack_8 = fStack_8 * _DAT_0056e158;
            param_2 = (ushort *)((float)param_2 * _DAT_0056e158);
            fStack_4 = fStack_4 * _DAT_0056e158;
          }
          break;
        case '\x02':
          if (DAT_006d7c6f == '\0') {
            sub_409510(&fStack_8,&param_2,&fStack_4,
                       fStack_4 * _DAT_0056e130 +
                       (float)param_2 * _DAT_0056e134 + fStack_8 * _DAT_0056e138);
          }
          break;
        case '\x03':
          fStack_8 = 0.0;
          param_2 = (ushort *)0x0;
          fStack_4 = 0.0;
          break;
        case '\x04':
          if (DAT_006d7c6f == '\0') {
            sub_409510(&fStack_8,&param_2,&fStack_4,
                       fStack_4 * _DAT_0056e144 +
                       (float)param_2 * _DAT_0056e140 + fStack_8 * _DAT_0056e13c);
          }
        }
      }
      __ftol();
      uVar2 = __ftol();
      uVar3 = __ftol();
      uVar4 = __ftol();
      uVar5 = uVar4 & 0xff000000 | (uint)CONCAT11(extraout_AH,uVar2) | uVar3 & 0xff0000;
      if ((param_5 != '\0') && (CONCAT11(extraout_AH,uVar2) == 0 && (uVar3 & 0xff0000) == 0)) {
        uVar5 = CONCAT31((int3)((uVar4 & 0xff000000) >> 8),1);
      }
      *param_1 = uVar5;
      iVar6 = iVar6 + 1;
      param_1 = param_1 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar6 < param_4);
  }
  return;
}

