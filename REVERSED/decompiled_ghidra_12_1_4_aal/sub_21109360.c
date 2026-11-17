/* sub_21109360 @ 21109360   765 bytes */

void __thiscall sub_21109360(void *this,int param_1,LPCSTR param_2,int *param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  byte bVar3;
  int *piVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  bool bVar9;
  byte local_114 [128];
  byte local_94 [128];
  int local_14;
  void *local_8;
  
  local_8 = this;
  if ((param_3 == (int *)0x0) || (param_2 == (LPCSTR)0x0)) {
    param_3 = (int *)0xc;
    do {
      piVar4 = *(int **)((int)param_3 + *(int *)((int)this + 4));
      while (piVar1 = piVar4, piVar1 != (int *)0x0) {
        piVar4 = (int *)piVar1[2];
        if ((piVar1[6] == param_1) &&
           ((param_2 == (LPCSTR)0x0 || (iVar7 = lstrcmpA(param_2,(LPCSTR)(piVar1 + 7)), iVar7 == 0))
           )) {
          iVar7 = *(int *)((int)this + 4);
          if (piVar1[2] != 0) {
            *(int *)(piVar1[2] + 0xc) = piVar1[3];
          }
          if (piVar1[3] != 0) {
            *(int *)(piVar1[3] + 8) = piVar1[2];
          }
          piVar1[5] = -1;
          if (*piVar1 != 0) {
            *(int *)(*piVar1 + 4) = piVar1[1];
          }
          if ((int *)piVar1[1] != (int *)0x0) {
            *(int *)piVar1[1] = *piVar1;
          }
          if (*(int **)(iVar7 + 4) == piVar1) {
            *(int *)(iVar7 + 4) = *piVar1;
          }
          piVar2 = (int *)(iVar7 + 0xc + piVar1[4] * 4);
          if ((int *)*piVar2 == piVar1) {
            *piVar2 = piVar1[2];
          }
          *piVar1 = *(int *)(iVar7 + 8);
          piVar1[1] = 0;
          if (*(int *)(iVar7 + 8) != 0) {
            *(int **)(*(int *)(iVar7 + 8) + 4) = piVar1;
          }
          *(int **)(iVar7 + 8) = piVar1;
        }
      }
      param_3 = param_3 + 1;
    } while ((int)param_3 < 0x80c);
  }
  else {
    lstrcpyA((LPSTR)local_114,param_2);
    if (param_4 != 0) {
      param_2 = (LPCSTR)param_4;
      do {
        lstrcpyA((LPSTR)local_94,(LPCSTR)param_3[1]);
        local_14 = *param_3;
        uVar5 = 0;
        pbVar8 = local_94;
        do {
          bVar3 = *pbVar8;
          uVar5 = uVar5 + bVar3;
          pbVar8 = pbVar8 + 1;
        } while (bVar3 != 0);
        for (piVar4 = *(int **)(*(int *)((int)this + 4) + 0xc + (uVar5 & 0x1ff) * 4);
            piVar4 != (int *)0x0; piVar4 = (int *)piVar4[2]) {
          if (local_114[0] == 0) {
            if ((local_14 == piVar4[0x47]) && (param_1 == piVar4[6])) {
              pbVar8 = (byte *)(piVar4 + 0x27);
              pbVar6 = local_94;
              do {
                bVar3 = *pbVar6;
                bVar9 = bVar3 < *pbVar8;
                if (bVar3 != *pbVar8) {
LAB_2110945b:
                  iVar7 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
                  goto joined_r0x211094e7;
                }
                if (bVar3 == 0) break;
                bVar3 = pbVar6[1];
                bVar9 = bVar3 < pbVar8[1];
                if (bVar3 != pbVar8[1]) goto LAB_2110945b;
                pbVar6 = pbVar6 + 2;
                pbVar8 = pbVar8 + 2;
              } while (bVar3 != 0);
              iVar7 = 0;
joined_r0x211094e7:
              if (iVar7 == 0) {
                if (piVar4 != (int *)0x0) {
                  iVar7 = *(int *)((int)local_8 + 4);
                  if (piVar4[2] != 0) {
                    *(int *)(piVar4[2] + 0xc) = piVar4[3];
                  }
                  if (piVar4[3] != 0) {
                    *(int *)(piVar4[3] + 8) = piVar4[2];
                  }
                  piVar4[5] = -1;
                  if (*piVar4 != 0) {
                    *(int *)(*piVar4 + 4) = piVar4[1];
                  }
                  if ((int *)piVar4[1] != (int *)0x0) {
                    *(int *)piVar4[1] = *piVar4;
                  }
                  if (*(int **)(iVar7 + 4) == piVar4) {
                    *(int *)(iVar7 + 4) = *piVar4;
                  }
                  piVar1 = (int *)(iVar7 + 0xc + piVar4[4] * 4);
                  if ((int *)*piVar1 == piVar4) {
                    *piVar1 = piVar4[2];
                  }
                  *piVar4 = *(int *)(iVar7 + 8);
                  piVar4[1] = 0;
                  if (*(int *)(iVar7 + 8) != 0) {
                    *(int **)(*(int *)(iVar7 + 8) + 4) = piVar4;
                  }
                  *(int **)(iVar7 + 8) = piVar4;
                }
                break;
              }
            }
          }
          else if ((local_14 == piVar4[0x47]) && (param_1 == piVar4[6])) {
            pbVar8 = (byte *)(piVar4 + 7);
            pbVar6 = local_114;
            do {
              bVar3 = *pbVar6;
              bVar9 = bVar3 < *pbVar8;
              if (bVar3 != *pbVar8) {
LAB_211094a7:
                iVar7 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
                goto LAB_211094ac;
              }
              if (bVar3 == 0) break;
              bVar3 = pbVar6[1];
              bVar9 = bVar3 < pbVar8[1];
              if (bVar3 != pbVar8[1]) goto LAB_211094a7;
              pbVar6 = pbVar6 + 2;
              pbVar8 = pbVar8 + 2;
            } while (bVar3 != 0);
            iVar7 = 0;
LAB_211094ac:
            if (iVar7 == 0) {
              pbVar8 = (byte *)(piVar4 + 0x27);
              pbVar6 = local_94;
              do {
                bVar3 = *pbVar6;
                bVar9 = bVar3 < *pbVar8;
                if (bVar3 != *pbVar8) {
LAB_211094e0:
                  iVar7 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
                  goto joined_r0x211094e7;
                }
                if (bVar3 == 0) break;
                bVar3 = pbVar6[1];
                bVar9 = bVar3 < pbVar8[1];
                if (bVar3 != pbVar8[1]) goto LAB_211094e0;
                pbVar6 = pbVar6 + 2;
                pbVar8 = pbVar8 + 2;
              } while (bVar3 != 0);
              iVar7 = 0;
              goto joined_r0x211094e7;
            }
          }
        }
        param_3 = param_3 + 4;
        param_2 = param_2 + -1;
        this = local_8;
        if (param_2 == (LPCSTR)0x0) {
          return;
        }
      } while( true );
    }
  }
  return;
}

