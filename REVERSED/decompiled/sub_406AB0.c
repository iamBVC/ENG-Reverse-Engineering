/* sub_406AB0 @ 00406ab0   403 bytes */

undefined4 sub_406AB0(int *param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (DAT_0058114c != (void *)0x0) {
    sub_406C50();
  }
  iVar7 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  DAT_00581150 = iVar7;
  if (0 < iVar7) {
    DAT_0058114c = operator_new(iVar7 << 5);
    if (DAT_0058114c == (void *)0x0) {
      DAT_0058114c = (void *)0x0;
    }
    else if (-1 < iVar7 + -1) {
      puVar4 = (undefined4 *)((int)DAT_0058114c + 8);
      do {
        puVar4[-2] = 0;
        puVar4[-1] = 0;
        *puVar4 = 0;
        puVar4[1] = 0;
        puVar4[2] = 0;
        puVar4[3] = 0;
        puVar4[4] = 0;
        puVar4[5] = 0;
        puVar4 = puVar4 + 8;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    if (DAT_0058114c == (void *)0x0) {
      return 0;
    }
    iVar7 = 0;
    if (0 < DAT_00581150) {
      iVar8 = 0;
      do {
        uVar1 = *(undefined4 *)*param_1;
        *param_1 = (int)((undefined4 *)*param_1 + 1);
        *(undefined4 *)(iVar8 + (int)DAT_0058114c) = uVar1;
        uVar1 = *(undefined4 *)*param_1;
        *param_1 = (int)((undefined4 *)*param_1 + 1);
        *(undefined4 *)(iVar8 + 4 + (int)DAT_0058114c) = uVar1;
        uVar1 = *(undefined4 *)*param_1;
        *param_1 = (int)((undefined4 *)*param_1 + 1);
        *(undefined4 *)(iVar8 + 8 + (int)DAT_0058114c) = uVar1;
        if (*(uint *)(iVar8 + (int)DAT_0058114c) == 0) {
          iVar5 = *(int *)(iVar8 + 8 + (int)DAT_0058114c) * *(int *)(iVar8 + 4 + (int)DAT_0058114c);
          if (iVar5 == 0) {
            iVar6 = 0;
          }
          else {
            iVar6 = *param_1;
            *param_1 = iVar5 + iVar6;
          }
LAB_00406c27:
          *(int *)(iVar8 + 0x18 + (int)DAT_0058114c) = iVar6;
        }
        else {
          if ((*(uint *)(iVar8 + (int)DAT_0058114c) & 0x80) == 0) {
            iVar5 = *(int *)(iVar8 + 8 + (int)DAT_0058114c) *
                    *(int *)(iVar8 + 4 + (int)DAT_0058114c) * 2;
            if (iVar5 == 0) {
              iVar6 = 0;
            }
            else {
              iVar6 = *param_1;
              *param_1 = iVar6 + iVar5;
            }
            goto LAB_00406c27;
          }
          pvVar2 = operator_new(*(int *)(iVar8 + 8 + (int)DAT_0058114c) *
                                *(int *)(iVar8 + 4 + (int)DAT_0058114c) * 2);
          *(void **)(iVar8 + 0x18 + (int)DAT_0058114c) = pvVar2;
          if (*(int *)(iVar8 + 0x18 + (int)DAT_0058114c) == 0) {
            return 0;
          }
          iVar5 = *(int *)*param_1;
          piVar3 = (int *)*param_1 + 1;
          *param_1 = (int)piVar3;
          if (iVar5 == 0) {
            piVar3 = (int *)0x0;
          }
          else {
            *param_1 = iVar5 + (int)piVar3;
          }
          sub_406A10(piVar3,*(undefined4 *)(iVar8 + 0x18 + (int)DAT_0058114c),
                     *(undefined4 *)(iVar8 + 4 + (int)DAT_0058114c),
                     *(undefined4 *)(iVar8 + 8 + (int)DAT_0058114c));
        }
        iVar7 = iVar7 + 1;
        iVar8 = iVar8 + 0x20;
      } while (iVar7 < DAT_00581150);
    }
  }
  return 1;
}

