/* sub_40C6E0 @ 0040c6e0   881 bytes */

void sub_40C6E0(void)

{
  undefined4 uVar1;
  byte bVar2;
  byte bVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  uint local_8;
  
  local_8 = 0;
  if (DAT_00581134 != 0) {
    pbVar9 = (byte *)((int)DAT_00581138 + 9);
    puVar8 = DAT_00581138;
    do {
      switch(pbVar9[-7]) {
      case 1:
      case 2:
        iVar7 = DAT_00581154 + (uint)*puVar8 * 0x14;
        *(float *)(iVar7 + 0xc) =
             (float)(int)((uint)pbVar9[-2] + (int)(char)pbVar9[-3]) /
             (float)*(int *)(*(char *)(iVar7 + 2) * 0x20 + 8 + DAT_0058114c);
        iVar7 = DAT_00581154 + (uint)*puVar8 * 0x14;
        *(float *)(iVar7 + 0x10) =
             (float)(int)((uint)pbVar9[-5] + (uint)pbVar9[-2] + 1 + (int)(char)pbVar9[-3]) /
             (float)*(int *)(*(char *)(iVar7 + 2) * 0x20 + 8 + DAT_0058114c);
        if (pbVar9[-7] == 1) {
          bVar2 = pbVar9[-3] - pbVar9[-4];
          pbVar9[-3] = bVar2;
          if ((char)bVar2 < '\0') {
            pbVar9[-3] = bVar2 + pbVar9[-5] + 1;
          }
        }
        else {
          bVar2 = pbVar9[-4] + pbVar9[-3];
          pbVar9[-3] = bVar2;
          if ((int)(uint)pbVar9[-5] < (int)(char)bVar2) {
            pbVar9[-3] = (bVar2 - pbVar9[-5]) - 1;
          }
        }
        break;
      case 7:
      case 9:
        if (pbVar9[2] == 0) {
          pbVar9[2] = pbVar9[-3];
          uVar5 = (uint)*pbVar9;
          iVar7 = *(int *)(DAT_00581144 + 8 + (uint)*(ushort *)(pbVar9 + -5) * 0x1c);
          uVar1 = *(undefined4 *)(iVar7 + uVar5 * 4);
          puVar4 = (undefined4 *)(iVar7 + uVar5 * 4);
          if (pbVar9[-1] < uVar5) {
            do {
              *puVar4 = puVar4[-1];
              puVar4 = puVar4 + -1;
              uVar5 = uVar5 - 1;
            } while (pbVar9[-1] < uVar5);
          }
          *puVar4 = uVar1;
          *(undefined1 *)(DAT_00581144 + 0xc + (uint)*(ushort *)(pbVar9 + -5) * 0x1c) = 1;
        }
        else {
          pbVar9[2] = pbVar9[2] - 1;
        }
        break;
      case 8:
        if (pbVar9[-2] == 0) {
          pbVar9[-2] = pbVar9[-5];
          if (pbVar9[-1] == 0) {
            bVar2 = pbVar9[-3];
            pbVar9[-3] = bVar2 + 1;
            if ((byte)(bVar2 + 1) == pbVar9[-4]) {
              pbVar9[-3] = 0;
            }
          }
          else {
            bVar2 = pbVar9[-3];
            if (*pbVar9 == 0) {
              pbVar9[-3] = bVar2 + 1;
              if ((byte)(bVar2 + 1) == pbVar9[-4]) {
                *pbVar9 = 1;
                pbVar9[-3] = bVar2 - 1;
              }
            }
            else if (bVar2 == 0) {
              pbVar9[-3] = 1;
              *pbVar9 = 0;
            }
            else {
              pbVar9[-3] = bVar2 - 1;
            }
          }
          puVar4 = (undefined4 *)(*(int *)(pbVar9 + 3) + (uint)pbVar9[-3] * 0x14);
          puVar10 = (undefined4 *)(DAT_00581154 + (uint)*puVar8 * 0x14);
          for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar10 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar10 = puVar10 + 1;
          }
        }
        else {
          pbVar9[-2] = pbVar9[-2] - 1;
        }
        break;
      case 10:
      case 0xb:
        if (pbVar9[-7] == 0xb) {
          bVar2 = pbVar9[-3] - pbVar9[-4];
          pbVar9[-3] = bVar2;
          if ((char)bVar2 < '\0') {
            pbVar9[-3] = pbVar9[-5] + bVar2 + 1;
            if (*pbVar9 == 0) {
              *pbVar9 = pbVar9[-1] - 1;
            }
            else {
              *pbVar9 = *pbVar9 - 1;
            }
LAB_0040c8e3:
            iVar7 = *(int *)(pbVar9 + 3);
            bVar2 = *pbVar9;
            bVar3 = __ftol();
            pbVar9[-2] = bVar3;
            puVar4 = (undefined4 *)(iVar7 + (uint)bVar2 * 0x14);
            puVar10 = (undefined4 *)(DAT_00581154 + (uint)*puVar8 * 0x14);
            for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar10 = *puVar4;
              puVar4 = puVar4 + 1;
              puVar10 = puVar10 + 1;
            }
          }
        }
        else {
          bVar2 = pbVar9[-4] + pbVar9[-3];
          pbVar9[-3] = bVar2;
          if ((int)(uint)pbVar9[-5] < (int)(char)bVar2) {
            pbVar9[-3] = (bVar2 - pbVar9[-5]) - 1;
            if ((int)(uint)*pbVar9 < (int)(pbVar9[-1] - 1)) {
              *pbVar9 = *pbVar9 + 1;
            }
            else {
              *pbVar9 = 0;
            }
            goto LAB_0040c8e3;
          }
        }
        iVar7 = DAT_00581154 + (uint)*puVar8 * 0x14;
        *(float *)(iVar7 + 0xc) =
             (float)(int)((uint)pbVar9[-2] + (int)(char)pbVar9[-3]) /
             (float)*(int *)(*(char *)(iVar7 + 2) * 0x20 + 8 + DAT_0058114c);
        iVar7 = DAT_00581154 + (uint)*puVar8 * 0x14;
        *(float *)(iVar7 + 0x10) =
             (float)(int)((uint)pbVar9[-5] + (uint)pbVar9[-2] + 1 + (int)(char)pbVar9[-3]) /
             (float)*(int *)(*(char *)(iVar7 + 2) * 0x20 + 8 + DAT_0058114c);
      }
      puVar8 = puVar8 + 8;
      pbVar9 = pbVar9 + 0x10;
      local_8 = local_8 + 1;
    } while (local_8 < DAT_00581134);
  }
  return;
}

