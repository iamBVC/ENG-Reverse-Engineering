/* sub_5458D0 @ 005458d0   811 bytes */

void sub_5458D0(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined2 extraout_var;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  uint uVar7;
  undefined4 unaff_EBP;
  uint uVar8;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  undefined4 uStack_4;
  
  if (((DAT_006d949c != 0) && (*(int *)(DAT_006d949c + 0xa4) != 0)) &&
     ((*(byte *)(DAT_006d949c + 0x54) & 1) == 0)) {
    uVar8 = CONCAT22((short)((uint)unaff_EBP >> 0x10),*(short *)(DAT_006d949c + 0xa0));
    local_10 = 0;
    local_c = *(uint *)(*(int *)(DAT_006d949c + 0x10) + 0x3c);
    if (0 < *(short *)(DAT_006d949c + 0xa0)) {
      local_14 = 0;
      local_8 = uVar8;
      do {
        iVar1 = *(int *)(*(int *)(DAT_006d949c + 0xa4) + local_14 * 4);
        uVar2 = sub_547C00(iVar1);
        if (*(uint *)(iVar1 + 0x10) < uVar2) {
          uVar7 = *(uint *)(iVar1 + 0x14);
          uVar6 = uVar7 - *(uint *)(iVar1 + 0x10);
          if ((uVar2 < uVar7) && (0 < (int)uVar6)) {
            uVar6 = ((uVar7 - uVar2) * *(int *)(iVar1 + 0x1c)) / uVar6;
          }
          else {
            uVar6 = 0;
          }
        }
        else {
          uVar6 = *(uint *)(iVar1 + 0x1c);
        }
        uVar2 = (int)(*(int *)(DAT_006d9490 + 0x100) * uVar6) >> 0xc;
        if ((*(uint *)(iVar1 + 0x18) & 0x10000) == 0) {
          if (uVar2 == 0) {
LAB_00545a5b:
            if (*(int *)(iVar1 + 0x20) == 0) goto LAB_00545b78;
          }
          else if (*(int *)(iVar1 + 0x20) == 0) {
            iVar3 = sub_5499A0(DAT_006d949c,*(undefined2 *)(iVar1 + 0x18));
            if (iVar3 == 0) {
              sub_549A00(DAT_006d949c,CONCAT22(extraout_var_00,*(undefined2 *)(iVar1 + 0x18)),0);
              sub_549AC0(DAT_006d949c,CONCAT22(extraout_var,*(undefined2 *)(iVar1 + 0x18)));
            }
            uVar6 = 1 << ((byte)local_14 & 0x1f);
            *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | uVar6;
            local_18 = 0;
            do {
              iVar3 = *(int *)(*(int *)(DAT_006d949c + 0xa4) + (short)local_18 * 4);
              if ((*(uint *)(iVar3 + 0x20) != 0) &&
                 (uVar8 = local_8, *(int *)(iVar1 + 0x18) == *(int *)(iVar3 + 0x18))) {
                *(uint *)(iVar3 + 0x20) =
                     1 << ((byte)local_18 & 0x1f) | uVar6 | *(uint *)(iVar3 + 0x20);
                *(uint *)(iVar1 + 0x20) =
                     *(uint *)(iVar1 + 0x20) | 1 << ((byte)local_18 & 0x1f) | uVar6;
              }
              local_18 = local_18 + 1;
            } while ((short)local_18 < (short)uVar8);
            goto LAB_00545a5b;
          }
          if (*(uint *)(iVar1 + 0x24) != uVar2) {
            local_18 = 0;
            uVar6 = uVar2;
            do {
              if ((((short)local_10 != (short)local_18) &&
                  (iVar3 = *(int *)(*(int *)(DAT_006d949c + 0xa4) + (short)local_18 * 4),
                  (*(uint *)(iVar1 + 0x20) & *(uint *)(iVar3 + 0x20)) != 0)) &&
                 (uVar7 = *(uint *)(iVar3 + 0x24), uVar2 < uVar7)) {
                uVar6 = uVar7;
              }
              local_18 = local_18 + 1;
            } while ((short)local_18 < (short)uVar8);
            if (uVar6 == uVar2) {
              sub_5499D0(DAT_006d949c,CONCAT22((short)(uVar6 >> 0x10),*(undefined2 *)(iVar1 + 0x18))
                         ,&local_18);
              uVar6 = (int)(short)local_18 + 1;
              uVar7 = uVar6;
              if (((int)uVar2 <= (int)uVar6) &&
                 (uVar4 = (int)(short)local_18 - 1, uVar7 = uVar2, (int)uVar2 < (int)uVar4)) {
                uVar7 = uVar4;
              }
              *(uint *)(iVar1 + 0x24) = uVar7;
              sub_549A00(DAT_006d949c,CONCAT22((short)(uVar6 >> 0x10),*(undefined2 *)(iVar1 + 0x18))
                         ,uVar7);
            }
            else {
              *(uint *)(iVar1 + 0x24) = uVar2;
            }
            if (*(int *)(iVar1 + 0x24) == 0) {
              local_18 = 0;
              do {
                iVar3 = *(int *)(*(int *)(DAT_006d949c + 0xa4) + (short)local_18 * 4);
                uVar2 = *(uint *)(iVar3 + 0x20);
                if ((*(uint *)(iVar1 + 0x20) & uVar2) != 0) {
                  *(uint *)(iVar3 + 0x20) = ~(1 << ((byte)local_18 & 0x1f)) & uVar2;
                }
                local_18 = local_18 + 1;
              } while ((short)local_18 < (short)uVar8);
              if ((*(int *)(iVar1 + 0x20) == 0) &&
                 (iVar3 = sub_5499A0(DAT_006d949c,*(undefined2 *)(iVar1 + 0x18)), iVar3 != 0)) {
                sub_549A70(DAT_006d949c,CONCAT22(extraout_var_01,*(undefined2 *)(iVar1 + 0x18)));
              }
              *(undefined4 *)(iVar1 + 0x20) = 0;
            }
          }
        }
        else if (local_c < uVar2) {
          local_c = uVar2;
        }
LAB_00545b78:
        local_10 = local_10 + 1;
        local_14 = local_14 + 1;
      } while ((short)local_10 < (short)uVar8);
    }
    if ((local_c != *(uint *)(*(int *)(DAT_006d949c + 0x10) + 0x38)) &&
       (*(uint *)(*(int *)(DAT_006d949c + 0x10) + 0x38) = local_c, DAT_005834f4 != 0)) {
      uStack_4 = 0;
      local_8 = local_c;
      sub_544FC0(0,0x42480000,(float)local_c);
      *(uint *)(DAT_006d9490 + 0x68) = *(uint *)(DAT_006d9490 + 0x68) | 3;
      uVar5 = __ftol();
      *(undefined4 *)(DAT_006d9490 + 0x6c) = uVar5;
      *(undefined4 *)(DAT_006d9490 + 0x70) = uVar5;
    }
  }
  return;
}

