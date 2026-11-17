/* sub_406880 @ 00406880   265 bytes */

undefined4 sub_406880(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (DAT_00581144 != (void *)0x0) {
    sub_406990();
  }
  iVar5 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  DAT_00581148 = iVar5;
  if (0 < iVar5) {
    DAT_00581144 = operator_new(iVar5 * 0x1c);
    if (DAT_00581144 == (void *)0x0) {
      DAT_00581144 = (void *)0x0;
    }
    else if (-1 < iVar5 + -1) {
      puVar3 = (undefined4 *)((int)DAT_00581144 + 8);
      do {
        puVar3[-2] = 0;
        puVar3[-1] = 0;
        *puVar3 = 0;
        *(undefined1 *)(puVar3 + 1) = 0;
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3[4] = 0;
        puVar3 = puVar3 + 7;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (DAT_00581144 == (void *)0x0) {
      return 0;
    }
    iVar5 = 0;
    if (0 < DAT_00581148) {
      iVar2 = 0;
      do {
        uVar1 = *(undefined4 *)*param_1;
        *param_1 = (int)((undefined4 *)*param_1 + 1);
        *(undefined4 *)(iVar2 + (int)DAT_00581144) = uVar1;
        uVar1 = *(undefined4 *)*param_1;
        *param_1 = (int)((undefined4 *)*param_1 + 1);
        *(undefined4 *)(iVar2 + 4 + (int)DAT_00581144) = uVar1;
        iVar4 = *(int *)(iVar2 + 4 + (int)DAT_00581144) * 2;
        if (iVar4 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = *param_1;
          *param_1 = iVar4 + iVar6;
        }
        *(int *)(iVar2 + 0x14 + (int)DAT_00581144) = iVar6;
        iVar4 = *(int *)(iVar2 + 4 + (int)DAT_00581144);
        if (iVar4 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = *param_1;
          *param_1 = iVar4 + iVar6;
        }
        iVar5 = iVar5 + 1;
        *(int *)(iVar2 + 0x18 + (int)DAT_00581144) = iVar6;
        iVar2 = iVar2 + 0x1c;
      } while (iVar5 < DAT_00581148);
    }
  }
  return 1;
}

