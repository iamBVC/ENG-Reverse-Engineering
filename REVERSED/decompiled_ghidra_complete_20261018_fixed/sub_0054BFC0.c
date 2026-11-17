/* sub_54BFC0 @ 0054bfc0   1057 bytes */

undefined4 * sub_54BFC0(int *param_1,undefined4 *param_2,undefined4 param_3,int param_4,int param_5)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  puVar2 = DAT_006d9e3c;
  if (*(uint *)(DAT_00584648 + 8) <= DAT_006d9dc8) {
    uVar5 = 0;
    if (param_1[1] != 0) {
      do {
        sub_54BC00(*param_1);
        uVar5 = uVar5 + 1;
      } while (uVar5 < (uint)param_1[1]);
    }
    return (undefined4 *)0x0;
  }
  if (DAT_006d9e3c != (undefined4 *)0x0) {
    piVar1 = DAT_006d9e3c + 1;
    uVar3 = DAT_006d9e3c[1];
    if (DAT_006d9e3c != (undefined4 *)0x0) {
      puVar7 = DAT_006d9e3c + 0x42;
      DAT_006d9e3c = (undefined4 *)DAT_006d9e3c[1];
      *puVar7 = 0;
      DAT_006d9dc8 = DAT_006d9dc8 + 1;
      *puVar2 = param_3;
      puVar2[6] = s_Blank_005790d0;
      puVar2[0x3c] = param_1[6];
      uVar5 = param_1[3];
      if ((uVar5 & 0x40000) == 0) {
        if (((uVar5 & 0x80000) == 0) && ((uVar5 & 0x8000) == 0)) {
          puVar2[0x30] = 0;
        }
        else {
          uVar3 = sub_41AE20(0xb);
          puVar2[0x30] = uVar3;
        }
      }
      else {
        uVar3 = sub_41AE20(0x10);
        puVar2[0x30] = uVar3;
      }
      if ((param_1[3] & 0xc8000U) != 0) {
        *(undefined2 *)(puVar2[0x30] + 6) = 0;
        *(undefined2 *)(puVar2[0x30] + 0xc) = 0xfffe;
        *(undefined2 *)(puVar2[0x30] + 0x10) = 0xffff;
        *(undefined4 *)(puVar2[0x30] + 0x14) = 0x200;
        *(undefined4 *)(puVar2[0x30] + 0x18) = 0x1000;
      }
      *(undefined2 *)(puVar2 + 0x34) = 0;
      *(undefined2 *)((int)puVar2 + 0xce) = 0;
      *(undefined2 *)(puVar2 + 0x33) = 0;
      *(undefined2 *)((int)puVar2 + 0xd2) = 0x400;
      puVar2[0x4f] = 0x1000;
      puVar2[0x50] = 0;
      puVar2[0x4b] = 0x1000;
      if ((param_1[3] & 0x40000U) != 0) {
        *(undefined2 *)(puVar2[0x30] + 0x36) = 0;
        *(undefined2 *)(puVar2[0x30] + 0x34) = 0;
        *(undefined2 *)(puVar2[0x30] + 0x32) = 0;
        *(undefined2 *)(puVar2[0x30] + 0x38) = 0x400;
        *(undefined2 *)(puVar2[0x30] + 0x3a) = 0;
      }
      *(undefined2 *)((int)puVar2 + 0xc6) = 0;
      if (param_5 == 0) {
        puVar2[3] = 0;
      }
      else {
        puVar2[3] = *param_1;
      }
      iVar4 = param_1[2];
      puVar2[0x40] = iVar4;
      if (param_1[4] == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = param_1[4] & 0x3fffffff;
      }
      iVar6 = param_4 + 0x14 + iVar4 * 4;
      if (iVar4 + param_4 == 0) {
        iVar6 = 0x14;
      }
      iVar4 = sub_41AE20(iVar6 + uVar5);
      puVar2[0x3d] = iVar4;
      if (param_1[4] == 0) {
        puVar2[0x32] = 0;
      }
      else {
        puVar2[0x32] = iVar4 + iVar6 * 4;
      }
      puVar2[0x41] = puVar2[0x3d] + param_4 * 4;
      puVar2[0x3e] = puVar2[0x3d] + 0x50 + param_4 * 4;
      uVar5 = 0;
      if (puVar2[0x40] != 0) {
        iVar4 = 0;
        do {
          uVar5 = uVar5 + 1;
          *(undefined4 *)(iVar4 + puVar2[0x3e]) = 0;
          iVar4 = iVar4 + 0x10;
        } while (uVar5 < (uint)puVar2[0x40]);
      }
      uVar5 = 0;
      if (param_1[1] != 0) {
        do {
          uVar3 = sub_54BC00(*param_1);
          iVar4 = param_1[1] - uVar5;
          uVar5 = uVar5 + 1;
          *(undefined4 *)(puVar2[0x3d] + -4 + iVar4 * 4) = uVar3;
        } while (uVar5 < (uint)param_1[1]);
      }
      puVar2[0x3a] = 0;
      puVar2[0x4e] = param_1[3];
      puVar2[0x3b] = 4;
      *(undefined1 *)((int)puVar2 + 0x152) = 0xff;
      *(undefined1 *)((int)puVar2 + 0x151) = 0xff;
      *(undefined1 *)(puVar2 + 0x54) = 0xff;
      *(undefined1 *)((int)puVar2 + 0x153) = 0xff;
      uVar3 = *(undefined4 *)(*param_1 + 0x118);
      puVar2[0x46] = uVar3;
      puVar2[0x49] = uVar3;
      puVar2[0x48] = *(undefined4 *)(*param_1 + 0x120);
      puVar2[0x47] = *(undefined4 *)(*param_1 + 0x11c);
      puVar7 = param_2;
      puVar8 = puVar2 + 8;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar7 = param_2;
      puVar8 = puVar2 + 0x28;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar7 = puVar2 + 0x10;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *param_2;
        param_2 = param_2 + 1;
        puVar7 = puVar7 + 1;
      }
      puVar2[0x43] = 0x1000;
      puVar2[0x1a] = 0x1000;
      puVar2[0x19] = 0x1000;
      puVar2[0x18] = 0x1000;
      *(undefined2 *)(puVar2 + 0x45) = 0x1000;
      puVar2[4] = 0;
      puVar2[5] = 0;
      *(undefined1 *)((int)puVar2 + 0x132) = 0xff;
      *(undefined1 *)((int)puVar2 + 0x131) = 0xff;
      *(undefined1 *)(puVar2 + 0x4c) = 0;
      if (DAT_006d9dc4 == 0) {
        *(undefined1 *)((int)puVar2 + 0x136) = 0;
      }
      else {
        *(undefined1 *)((int)puVar2 + 0x133) = DAT_006d9e14;
        *(undefined1 *)(puVar2 + 0x4d) = DAT_006d9e15;
        *(undefined1 *)((int)puVar2 + 0x135) = DAT_006d9e16;
        *(undefined1 *)((int)puVar2 + 0x136) = 1;
      }
      *(undefined2 *)((int)puVar2 + 0xfe) = 0;
      *(undefined2 *)(puVar2 + 0x35) = 0xffff;
      sub_54BC30(puVar2);
      if (param_1[5] != 0) {
        puVar2[2] = *param_1;
        *piVar1 = *(int *)(*param_1 + 4);
        if (*(int *)(*param_1 + 4) != 0) {
          *(undefined4 **)(*(int *)(*param_1 + 4) + 8) = puVar2;
        }
        *(undefined4 **)(*param_1 + 4) = puVar2;
        DAT_006d9e18 = puVar2;
        puVar2[0x53] = 0xfffff000;
        return puVar2;
      }
      *piVar1 = (int)DAT_006d9e38;
      if (DAT_006d9e38 != (undefined4 *)0x0) {
        DAT_006d9e38[2] = puVar2;
      }
      DAT_006d9e38 = puVar2;
      uVar3 = DAT_006d9e3c;
    }
    DAT_006d9e3c = (undefined4 *)uVar3;
    puVar2[0x53] = 0xfffff000;
    return puVar2;
  }
  uVar5 = 0;
  if (param_1[1] != 0) {
    do {
      sub_54BC00(*param_1);
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)param_1[1]);
  }
  return (undefined4 *)0x0;
}

