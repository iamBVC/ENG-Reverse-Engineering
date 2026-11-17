/* sub_436E30 @ 00436e30   648 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_436E30(undefined4 param_1,undefined4 param_2,float param_3)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  ushort *puVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float *pfVar11;
  int in_stack_00002010;
  int in_stack_00002014;
  int in_stack_00002018;
  
  sub_562840();
  if (0x100 < in_stack_00002014) {
    return 0;
  }
  iVar9 = 0;
  if (DAT_006d76c8 != 0) {
    *(undefined2 *)(in_stack_00002018 + in_stack_00002010 * 2) = 0;
    in_stack_00002010 = in_stack_00002010 + 1;
    in_stack_00002014 = in_stack_00002014 + -1;
  }
  DAT_005ff730 = in_stack_00002014;
  sub_4370C0();
  iVar8 = 1;
  if (1 < DAT_005ff730) {
    pfVar11 = (float *)&stack0x00000010;
    param_2 = (int *)&stack0x00000440;
    do {
      iVar2 = sub_437460();
      if (iVar2 == 0) {
        iVar8 = iVar8 + -1;
        param_2 = param_2 + -7;
        pfVar11 = pfVar11 + -1;
        (&param_3)[iVar9] = 0.0;
      }
      else {
        if (*(int *)(&stack0x00000424 + iVar9 * 0x1c) < 2) {
          fVar10 = (float10)_DAT_0056e00c;
        }
        else {
          fVar10 = (float10)sub_437330();
        }
        (&param_3)[iVar9] = (float)fVar10;
        if (*param_2 < 2) {
          *pfVar11 = _DAT_0056e00c;
        }
        else {
          fVar10 = (float10)sub_437330();
          *pfVar11 = (float)fVar10;
        }
      }
      iVar2 = 1;
      iVar9 = 0;
      fVar1 = param_3;
      if (0 < iVar8) {
        pfVar5 = (float *)&stack0x00000010;
        do {
          if (fVar1 < *pfVar5) {
            fVar1 = *pfVar5;
            iVar9 = iVar2;
          }
          iVar2 = iVar2 + 1;
          pfVar5 = pfVar5 + 1;
        } while (iVar2 <= iVar8);
      }
      if (fVar1 <= (float)_DAT_0056e470) {
        DAT_005ff730 = iVar8 + 1;
        break;
      }
      param_2 = param_2 + 7;
      iVar8 = iVar8 + 1;
      pfVar11 = pfVar11 + 1;
    } while (iVar8 < DAT_005ff730);
  }
  iVar9 = 0;
  if (0 < DAT_005ff730) {
    puVar6 = (ushort *)(in_stack_00002018 + in_stack_00002010 * 2);
    do {
      sub_437A60();
      iVar8 = sub_437290();
      if (iVar8 != 0) {
        iVar2 = sub_437290();
        iVar3 = sub_437290();
        iVar4 = sub_437290();
        uVar7 = (ushort)((iVar2 / iVar8 << 5 | iVar3 / iVar8) << 5) | (ushort)(iVar4 / iVar8);
        *puVar6 = uVar7;
        if ((DAT_006d76c8 != 0) && (uVar7 == 0)) {
          *puVar6 = 1;
        }
      }
      iVar9 = iVar9 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar9 < DAT_005ff730);
  }
  return 1;
}

