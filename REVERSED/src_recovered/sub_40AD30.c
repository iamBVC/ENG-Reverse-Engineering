/* Selected Ghidra export at 0040ad30. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_40AD30(uint *param_1,ushort *param_2,int param_3,int param_4,char param_5)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined1 extraout_AH;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  ushort *puVar8;
  float fStack_8;
  float fStack_4;
  
  iVar7 = 0;
  puVar6 = param_1;
  puVar8 = param_2;
  if (0 < param_4) {
    do {
      uVar1 = *puVar8;
      param_2 = (ushort *)((float)((byte)uVar1 & 0x1f) * _DAT_0056e11c);
      fStack_4 = (float)(uVar1 & 0x7c00);
      param_1 = (uint *)((float)(uVar1 & 0x3e0) * _DAT_0056e124);
      fStack_8 = (float)(int)fStack_4 * _DAT_0056e12c;
      if (((uVar1 & 0x8000) == 0) || (*(char *)(iVar7 + param_3) == '\0')) {
switchD_0040adbb_caseD_1:
      }
      else {
        switch(*(char *)(iVar7 + param_3)) {
        case '\x01':
          goto switchD_0040adbb_caseD_1;
        case '\x02':
        case '\x04':
          fStack_4 = fStack_8 * _DAT_0056e130 +
                     (float)param_1 * _DAT_0056e134 + (float)param_2 * _DAT_0056e138;
          sub_409510(&param_2,&param_1,&fStack_8,fStack_4);
          if (fStack_4 != _DAT_0056e00c) goto switchD_0040adbb_caseD_1;
          break;
        case '\x03':
          param_2 = (ushort *)0x0;
          param_1 = (uint *)0x0;
          fStack_8 = 0.0;
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
      *puVar6 = uVar5;
      iVar7 = iVar7 + 1;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar7 < param_4);
  }
  return;
}

