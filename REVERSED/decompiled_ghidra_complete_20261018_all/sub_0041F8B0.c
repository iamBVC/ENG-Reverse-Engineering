/* sub_41F8B0 @ 0041f8b0   375 bytes */

undefined4 sub_41F8B0(int *param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 * 0x20 == 0) {
    iVar2 = 0;
    iVar3 = 0;
  }
  else {
    iVar2 = *param_1;
    iVar3 = param_2 * 0x20 + iVar2;
    *param_1 = iVar3;
  }
  *param_3 = iVar2;
  if (param_2 < 1) {
    return CONCAT31((int3)((uint)iVar3 >> 8),1);
  }
  iVar2 = 0;
  do {
    iVar3 = *(int *)(iVar2 + *param_3) * 4;
    if (iVar3 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *param_1;
      *param_1 = iVar3 + iVar5;
    }
    *(int *)(iVar2 + 4 + *param_3) = iVar5;
    iVar3 = *param_3 + iVar2;
    if (*(int *)(iVar3 + 0xc) == 0) {
      iVar3 = *(int *)(iVar3 + 8) * 8;
      if (iVar3 == 0) {
        *(undefined4 *)(iVar2 + 0xc + *param_3) = 0;
      }
      else {
        iVar5 = *param_1;
        *param_1 = iVar3 + iVar5;
        *(int *)(iVar2 + 0xc + *param_3) = iVar5;
      }
    }
    else {
      *(undefined4 *)(iVar3 + 0xc) = 0;
    }
    if (*(int *)(*param_3 + iVar2 + 0x10) != 0) {
      iVar3 = *(int *)(*param_3 + iVar2 + 8) * 4;
      if (iVar3 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = *param_1;
        *param_1 = iVar3 + iVar5;
      }
      *(int *)(iVar2 + 0x14 + *param_3) = iVar5;
    }
    iVar3 = *(int *)(iVar2 + 8 + *param_3) * 4;
    if (iVar3 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *param_1;
      *param_1 = iVar3 + iVar5;
    }
    iVar4 = 0;
    *(int *)(iVar2 + 0x1c + *param_3) = iVar5;
    iVar3 = *param_3;
    if (0 < *(int *)(iVar2 + 8 + iVar3)) {
      do {
        uVar1 = *(uint *)(iVar2 + 0x10 + iVar3);
        if (uVar1 != 0) {
          if (iVar4 == 0) {
            if (uVar1 * 8 == 0) {
              iVar3 = 0;
            }
            else {
              iVar3 = *param_1;
              *param_1 = uVar1 * 8 + iVar3;
            }
            **(int **)(iVar2 + 0x14 + *param_3) = iVar3;
          }
          else if ((uVar1 & 1) == 0) {
            iVar3 = uVar1 * 2;
            if (iVar3 != 0) goto LAB_0041f9a2;
            *(undefined4 *)(*(int *)(iVar2 + 0x14 + *param_3) + iVar4 * 4) = 0;
          }
          else {
            iVar3 = uVar1 * 2 + 2;
            if (iVar3 == 0) {
              *(undefined4 *)(*(int *)(iVar2 + 0x14 + *param_3) + iVar4 * 4) = 0;
            }
            else {
LAB_0041f9a2:
              iVar5 = *param_1;
              *param_1 = iVar3 + iVar5;
              *(int *)(*(int *)(iVar2 + 0x14 + *param_3) + iVar4 * 4) = iVar5;
            }
          }
        }
        iVar3 = *(int *)(iVar2 + 0x18 + *param_3) * 0x40;
        if (iVar3 == 0) {
          iVar5 = 0;
        }
        else {
          iVar5 = *param_1;
          *param_1 = iVar3 + iVar5;
        }
        iVar4 = iVar4 + 1;
        *(int *)(*(int *)(iVar2 + 0x1c + *param_3) + -4 + iVar4 * 4) = iVar5;
        iVar3 = *param_3;
      } while (iVar4 < *(int *)(iVar2 + 8 + iVar3));
    }
    iVar2 = iVar2 + 0x20;
    param_2 = param_2 + -1;
    if (param_2 == 0) {
      return CONCAT31((int3)((uint)iVar2 >> 8),1);
    }
  } while( true );
}

