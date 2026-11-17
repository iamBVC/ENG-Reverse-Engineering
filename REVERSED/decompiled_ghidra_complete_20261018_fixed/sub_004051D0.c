/* sub_4051D0 @ 004051d0   745 bytes */

void sub_4051D0(void)

{
  ushort uVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined1 *puVar8;
  int *piVar9;
  uint local_120;
  undefined1 local_110 [12];
  int local_104;
  undefined1 local_100 [12];
  int aiStack_f4 [61];
  
  if (DAT_006d9e1c != 0) {
    uVar7 = 0;
    uVar6 = (uint)*(ushort *)(DAT_006d9e1c + 0xc6);
    if (uVar6 != 0xffffffff) {
      puVar8 = local_100;
      do {
        sub_404E90(puVar8,DAT_006d9e1c,uVar7);
        uVar7 = uVar7 + 1;
        puVar8 = puVar8 + 0x10;
      } while (uVar7 < uVar6 + 1);
    }
    *(undefined2 *)(DAT_006d9e1c + 0xd4) = 0xffff;
    *(undefined4 *)(DAT_006d9e1c + 0x144) = 0;
    for (iVar2 = DAT_006d9e38; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
      if (((((*(uint *)(iVar2 + 0xe8) & 0x134000) != 0) &&
           (uVar7 = *(uint *)(iVar2 + 0xec), (uVar7 & 0x18000) != 0x18000)) &&
          ((*(uint *)(iVar2 + 0xe8) & 0x800) == 0)) &&
         (((*(uint *)(DAT_006d9e1c + 0xe8) & 0x10000) != 0 ||
          (*(int *)(iVar2 + 0x148) <= *(int *)(iVar2 + 0x13c) * *(int *)(iVar2 + 0x13c))))) {
        if ((uVar7 & 0x20) == 0) {
          if ((uVar7 & 4) != 0) {
            uVar1 = *(ushort *)(iVar2 + 0xc6);
            local_120 = 0;
            if (uVar1 != 0xffffffff) {
              do {
                sub_404E90(local_110,iVar2,local_120);
                if (-1 < (int)uVar6) {
                  piVar9 = aiStack_f4 + uVar6 * 4;
                  uVar7 = uVar6;
                  do {
                    iVar4 = sub_404C10(piVar9 + -3,local_110);
                    iVar5 = local_104;
                    if (iVar4 < (*piVar9 + local_104) * (*piVar9 + local_104) >> 0xc) {
                      if ((*(uint *)(iVar2 + 0xe8) & 0x100000) != 0) {
                        sVar3 = __ftol();
                        sVar3 = ((short)aiStack_f4[uVar7 * 4] - sVar3) + (short)iVar5;
                        *(short *)(iVar2 + 0xd4) = sVar3;
                        *(short *)(DAT_006d9e1c + 0xd4) = sVar3;
                        iVar5 = sub_404D60(local_100 + uVar7 * 0x10,local_110);
                        sVar3 = (short)(iVar5 >> 0xc);
                        *(short *)(DAT_006d9e1c + 0xd6) = sVar3;
                        *(ushort *)(iVar2 + 0xd6) = sVar3 - 0x800U & 0xfff;
                      }
                      *(char *)(DAT_006d9e1c + 0x130) = (char)uVar7;
                      *(char *)(iVar2 + 0x130) = (char)uVar7;
                      goto LAB_004053d1;
                    }
                    uVar7 = uVar7 - 1;
                    piVar9 = piVar9 + -4;
                  } while (-1 < (int)uVar7);
                }
                local_120 = local_120 + 1;
              } while (local_120 < uVar1 + 1);
            }
          }
        }
        else if ((uVar7 & 0x40) != 0) {
          *(uint *)(iVar2 + 0xec) = uVar7 & 0xffffffbf;
LAB_004053d1:
          if ((*(uint *)(iVar2 + 0xe8) & 0x4000) == 0) {
            if ((*(uint *)(iVar2 + 0xe8) & 0x10000) != 0) {
              uVar7 = *(uint *)(DAT_006d9e1c + 0xe8);
              if ((uVar7 & 0x10000000) == 0) {
                if ((uVar7 & 0x40000000) == 0) {
                  *(uint *)(DAT_006d9e1c + 0xe8) = uVar7 | 0x4000000;
                  *(undefined4 *)(DAT_006d9e1c + 0x144) = *(undefined4 *)(iVar2 + 0x140);
                }
              }
              else {
                *(uint *)(iVar2 + 0xe8) = *(uint *)(iVar2 + 0xe8) | 0x4000000;
                *(undefined4 *)(iVar2 + 0x144) = *(undefined4 *)(DAT_006d9e1c + 0x140);
              }
            }
            if ((*(uint *)(iVar2 + 0xe8) & 0x20000) == 0) goto LAB_004054a3;
          }
          else if ((*(uint *)(DAT_006d9e1c + 0xe8) & 0x40000000) == 0) {
            *(uint *)(DAT_006d9e1c + 0xe8) = *(uint *)(DAT_006d9e1c + 0xe8) | 0x4000000;
            *(undefined4 *)(DAT_006d9e1c + 0x144) = *(undefined4 *)(iVar2 + 0x140);
          }
          *(uint *)(iVar2 + 0xe8) = *(uint *)(iVar2 + 0xe8) | 0x4000000;
          *(undefined4 *)(iVar2 + 0x144) = *(undefined4 *)(DAT_006d9e1c + 0x140);
        }
      }
LAB_004054a3:
    }
  }
  return;
}

