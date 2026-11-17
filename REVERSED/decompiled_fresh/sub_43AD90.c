/* sub_43AD90 @ 0043ad90   632 bytes */

undefined4
sub_43AD90(int param_1,int param_2,int param_3,undefined2 *param_4,short *param_5,int param_6)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  void *pvVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  uint *puVar13;
  byte *pbVar14;
  uint local_14;
  
  if ((7 < param_2) && (7 < param_3)) {
    local_14 = 0;
    iVar5 = (int)(param_2 + (param_2 >> 0x1f & 7U)) >> 3;
    iVar4 = -iVar5;
    iVar9 = *(int *)(&DAT_00574298 + iVar5 * 4);
    iVar5 = (int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3;
    if (-iVar5 != -0x20) {
      puVar7 = (uint *)(param_1 + 0x14);
      do {
        uVar10 = 0;
        if (iVar4 != -0x20) {
          do {
            uVar6 = iVar9 << ((byte)uVar10 & 0x1f);
            if ((uVar6 & puVar7[-1]) == 0) {
              uVar11 = 1;
              puVar13 = puVar7;
              if (iVar5 + 1U < 2) {
LAB_0043ae61:
                iVar5 = iVar5 + 1;
                if (iVar5 != 0) {
                  puVar7 = (uint *)(param_1 + 0x10 + local_14 * 4);
                  do {
                    iVar5 = iVar5 + -1;
                    *puVar7 = *puVar7 | iVar9 << ((byte)uVar10 & 0x1f);
                    puVar7 = puVar7 + 1;
                  } while (iVar5 != 0);
                }
                *param_5 = (short)local_14 * 8;
                *param_4 = (short)(uVar10 << 3);
                if (*(int *)(param_1 + 8) == 0) {
                  pvVar8 = _malloc(0x40000);
                  *(void **)(param_1 + 8) = pvVar8;
                  iVar5 = 0;
                  do {
                    iVar5 = iVar5 + 4;
                    *(undefined1 *)(*(int *)(param_1 + 8) + -4 + iVar5) = 0;
                    *(undefined1 *)(*(int *)(param_1 + 8) + -3 + iVar5) = 0;
                    *(undefined1 *)(*(int *)(param_1 + 8) + -2 + iVar5) = 0;
                    *(undefined1 *)(*(int *)(param_1 + 8) + -1 + iVar5) = 0;
                  } while (iVar5 < 0x40000);
                }
                if (param_3 < 1) {
                  return 1;
                }
                param_4 = (undefined2 *)param_3;
                pbVar12 = (byte *)(param_6 + 2);
                iVar5 = (local_14 * 0x800 + uVar10 * 8) * 4;
                do {
                  if (0 < param_2) {
                    param_3 = param_2;
                    iVar9 = iVar5;
                    pbVar14 = pbVar12;
                    do {
                      bVar1 = pbVar14[-2];
                      bVar2 = pbVar14[-1];
                      bVar3 = *pbVar14;
                      if (bVar1 == 0) {
                        if (bVar2 != 0xff) {
LAB_0043af6f:
                          if ((7 < bVar2) || (7 < bVar3)) goto LAB_0043af91;
                          *(undefined1 *)(*(int *)(param_1 + 8) + iVar9) = 8;
                          *(undefined1 *)(*(int *)(param_1 + 8) + 1 + iVar9) = 8;
                          *(undefined1 *)(*(int *)(param_1 + 8) + 2 + iVar9) = 8;
                          goto LAB_0043afa5;
                        }
                        if (bVar3 != 0xff) goto LAB_0043af91;
                        *(undefined1 *)(*(int *)(param_1 + 8) + iVar9) = 0;
                        *(undefined1 *)(*(int *)(param_1 + 8) + 1 + iVar9) = 0;
                        *(undefined1 *)(*(int *)(param_1 + 8) + 2 + iVar9) = 0;
                        *(undefined1 *)(*(int *)(param_1 + 8) + 3 + iVar9) = 0;
                      }
                      else {
                        if (bVar1 < 8) goto LAB_0043af6f;
LAB_0043af91:
                        *(byte *)(iVar9 + *(int *)(param_1 + 8)) = bVar1;
                        *(byte *)(*(int *)(param_1 + 8) + 1 + iVar9) = bVar2;
                        *(byte *)(*(int *)(param_1 + 8) + 2 + iVar9) = bVar3;
LAB_0043afa5:
                        *(undefined1 *)(*(int *)(param_1 + 8) + 3 + iVar9) = 0xff;
                      }
                      pbVar14 = pbVar14 + 3;
                      iVar9 = iVar9 + 4;
                      param_3 = param_3 + -1;
                    } while (param_3 != 0);
                  }
                  iVar5 = iVar5 + 0x400;
                  pbVar12 = pbVar12 + param_2 * 3;
                  param_4 = (undefined2 *)((int)param_4 + -1);
                  if (param_4 == (undefined2 *)0x0) {
                    return 1;
                  }
                } while( true );
              }
              while ((*puVar13 & uVar6) == 0) {
                uVar11 = uVar11 + 1;
                puVar13 = puVar13 + 1;
                if (iVar5 + 1U <= uVar11) goto LAB_0043ae61;
              }
            }
            uVar10 = uVar10 + 1;
          } while (uVar10 < iVar4 + 0x20U);
        }
        puVar7 = puVar7 + 1;
        local_14 = local_14 + 1;
      } while (local_14 < -iVar5 + 0x20U);
    }
  }
  return 0;
}

