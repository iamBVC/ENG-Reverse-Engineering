/* sub_211090B0 @ 211090b0   683 bytes */

void __thiscall sub_211090B0(void *this,int param_1,int *param_2,int param_3,int param_4)

{
  byte bVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  int local_138;
  CHAR local_134 [128];
  byte local_b4 [128];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  void *local_28;
  uint local_24;
  int *local_20;
  uint local_1c;
  byte *local_18;
  void *local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  local_28 = this;
  if (((param_2 == (int *)0x0) && (param_3 == 0)) && (param_4 == 0)) {
    sub_21109360(this,param_1,(LPCSTR)0x0,(int *)0x0,0);
    return;
  }
  local_138 = param_1;
  lstrcpyA(local_134,(LPCSTR)param_2);
  if (param_4 != 0) {
    local_18 = local_b4;
    puVar8 = (undefined4 *)(param_3 + 0xc);
    local_c = param_4;
    do {
      lstrcpyA((LPSTR)local_b4,(LPCSTR)puVar8[-2]);
      piVar10 = *(int **)((int)this + 4);
      local_34 = puVar8[-3];
      local_30 = *puVar8;
      local_2c = puVar8[-1];
      local_20 = piVar10;
      local_10 = 0;
      pbVar7 = local_18;
      do {
        bVar1 = *pbVar7;
        local_10 = local_10 + bVar1;
        pbVar7 = pbVar7 + 1;
      } while (bVar1 != 0);
      local_24 = local_10 & 0x1ff;
      if (piVar10[2] == 0) {
        iVar6 = *piVar10;
        piVar12 = (int *)piVar10[0x203];
        local_8 = iVar6 + 0x80;
        local_1c = local_8 * 0x128;
        pvVar2 = operator_new(local_1c);
        local_14 = pvVar2;
        if (pvVar2 != (void *)0x0) {
          if (0 < iVar6) {
            piVar3 = (int *)((int)pvVar2 + 0xc);
            param_2 = piVar12;
            param_3 = iVar6;
            do {
              piVar10 = piVar3 + -3;
              piVar9 = param_2;
              piVar11 = piVar10;
              for (iVar4 = 0x4a; iVar4 != 0; iVar4 = iVar4 + -1) {
                *piVar11 = *piVar9;
                piVar9 = piVar9 + 1;
                piVar11 = piVar11 + 1;
              }
              if (piVar3[-1] != 0) {
                piVar3[-1] = (int)pvVar2 + (piVar3[-1] - (int)piVar12);
              }
              if (*piVar3 != 0) {
                *piVar3 = (int)pvVar2 + (*piVar3 - (int)piVar12);
              }
              if (*piVar10 != 0) {
                *piVar10 = (int)pvVar2 + (*piVar10 - (int)piVar12);
              }
              if (piVar3[-2] != 0) {
                piVar3[-2] = (int)pvVar2 + (piVar3[-2] - (int)piVar12);
              }
              param_2 = param_2 + 0x4a;
              piVar3 = piVar3 + 0x4a;
              param_3 = param_3 + -1;
              piVar10 = local_20;
            } while (param_3 != 0);
          }
          piVar3 = piVar10 + 3;
          param_2 = (int *)0x200;
          do {
            if (*piVar3 != 0) {
              *piVar3 = (int)pvVar2 + (*piVar3 - (int)piVar12);
            }
            piVar3 = piVar3 + 1;
            param_2 = (int *)((int)param_2 + -1);
          } while (param_2 != (int *)0x0);
          if (iVar6 < local_8) {
            iVar4 = (int)pvVar2 + iVar6 * 0x128 + -0x128;
            iVar5 = local_8 - iVar6;
            do {
              *(undefined4 *)(iVar4 + 0x13c) = 0xffffffff;
              *(int *)(iVar4 + 300) = iVar4;
              *(int *)(iVar4 + 0x128) = iVar4 + 0x250;
              iVar4 = iVar4 + 0x128;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
          }
          *(undefined4 *)((int)pvVar2 + iVar6 * 0x128 + 4) = 0;
          *(undefined4 *)((local_1c - 0x128) + (int)pvVar2) = 0;
          *piVar10 = local_8;
          piVar10[1] = (int)pvVar2 + (piVar10[1] - (int)piVar12);
          piVar10[2] = (int)((int)pvVar2 + iVar6 * 0x128);
          sub_2110D4F4((LPVOID)piVar10[0x203]);
          piVar10[0x203] = (int)pvVar2;
          goto LAB_211092d1;
        }
      }
      else {
LAB_211092d1:
        piVar12 = (int *)piVar10[2];
        piVar10[2] = *piVar12;
        *piVar12 = piVar10[1];
        piVar12[1] = 0;
        if (piVar10[1] != 0) {
          *(int **)(piVar10[1] + 4) = piVar12;
        }
        piVar10[1] = (int)piVar12;
        piVar12[4] = local_24;
        piVar12[2] = piVar10[local_24 + 3];
        piVar12[3] = 0;
        if (piVar10[local_24 + 3] != 0) {
          *(int **)(piVar10[local_24 + 3] + 0xc) = piVar12;
        }
        piVar10[local_24 + 3] = (int)piVar12;
        piVar12[5] = (uint)((int)piVar12 - piVar10[0x203]) / 0x128;
        piVar10 = &local_138;
        piVar12 = piVar12 + 6;
        for (iVar6 = 0x44; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar12 = *piVar10;
          piVar10 = piVar10 + 1;
          piVar12 = piVar12 + 1;
        }
      }
      puVar8 = puVar8 + 4;
      local_c = local_c + -1;
      this = local_28;
    } while (local_c != 0);
  }
  return;
}

