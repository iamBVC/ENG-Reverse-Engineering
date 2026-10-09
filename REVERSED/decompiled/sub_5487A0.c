/* sub_5487A0 @ 005487a0   534 bytes */

int sub_5487A0(undefined4 *param_1,int param_2,uint param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = *(uint *)(DAT_006d9498 + 0x48);
  iVar3 = *(int *)(DAT_006d9498 + 0x44);
  uVar5 = param_3;
  if ((param_3 & 0x8000) == 0) {
    uVar5 = param_3 | *(ushort *)(param_1 + 2);
  }
  uVar6 = 0;
  if (param_2 == 0) {
    uVar5 = uVar5 | 0x400;
  }
  if (((uVar5 & 0x304) != 0) && (param_3 = 0, uVar2 != 0)) {
    piVar4 = (int *)(iVar3 + 0x18);
    do {
      if ((undefined4 *)piVar4[-5] == param_1) {
        if (((uVar5 & 0x200) != 0) && (param_3 = param_3 + 1, 4 < param_3)) {
          return 0;
        }
        if ((*(short *)((int)param_1 + 10) == 0) && (*piVar4 == *(int *)(DAT_006d9498 + 0x54))) {
          return 0;
        }
        if (piVar4[2] == param_2) {
          if ((uVar5 & 4) != 0) {
            iVar1 = iVar3 + uVar6 * 0x9c;
            if (*(int *)(iVar3 + 0x10 + uVar6 * 0x9c) == 3) {
              sub_547DF0(DAT_006d9498 + 0x10,iVar1);
            }
            *(undefined2 *)(iVar1 + 0x70) = 0;
            *(undefined2 *)(iVar1 + 0x6e) = *(undefined2 *)(param_1 + 1);
            *(undefined2 *)(iVar1 + 0x6c) = *(undefined2 *)(param_1 + 1);
            *(undefined2 *)(iVar1 + 0x6a) = *(undefined2 *)((int)param_1 + 6);
            *(undefined4 *)(iVar1 + 0x18) = *(undefined4 *)(DAT_006d9498 + 0x54);
            *param_4 = uVar6;
            return iVar1;
          }
          if ((uVar5 & 0x100) != 0) {
            *param_4 = uVar6;
            return 0;
          }
        }
      }
      uVar6 = uVar6 + 1;
      piVar4 = piVar4 + 0x27;
    } while (uVar6 < uVar2);
  }
  uVar6 = 0;
  if (uVar2 != 0) {
    piVar4 = (int *)(iVar3 + 4);
    while( true ) {
      if ((undefined4 *)*piVar4 == (undefined4 *)0x0) {
        if (param_2 != 0) {
          iVar1 = iVar3 + uVar6 * 0x9c;
          *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_2 + 0x30);
          *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_2 + 0x34);
          *(undefined4 *)(iVar1 + 0x2c) = *(undefined4 *)(param_2 + 0x38);
        }
        iVar3 = iVar3 + uVar6 * 0x9c;
        *(undefined4 **)(iVar3 + 4) = param_1;
        *(undefined2 *)(iVar3 + 0x78) = *(undefined2 *)((int)param_1 + 10);
        *(undefined2 *)(iVar3 + 0x6e) = *(undefined2 *)(param_1 + 1);
        *(undefined2 *)(iVar3 + 0x6c) = *(undefined2 *)(param_1 + 1);
        *(undefined2 *)(iVar3 + 0x6a) = *(undefined2 *)((int)param_1 + 6);
        *(undefined4 *)(iVar3 + 0x54) = *param_1;
        *(undefined4 *)(iVar3 + 0x10) = 1;
        *(ushort *)(iVar3 + 0x72) = (-(ushort)(*(short *)((int)param_1 + 10) != 0) & 4) + 4;
        *(undefined4 *)(iVar3 + 0x40) = 0;
        *(undefined2 *)(iVar3 + 0x76) = 0;
        *(undefined4 *)(iVar3 + 0x38) = *(undefined4 *)(DAT_006d9498 + 0x5c);
        *(int *)(iVar3 + 0x34) = *(int *)(DAT_006d9498 + 0x5c) >> 1;
        *(int *)(iVar3 + 0x20) = param_2;
        *(uint *)(iVar3 + 0x3c) = uVar5;
        *(undefined2 *)(iVar3 + 0x70) = 0;
        *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(DAT_006d9498 + 0x54);
        *(int *)(iVar3 + 0x8c) = iVar3;
        *param_4 = uVar6;
        return iVar3;
      }
      if (((*(short *)((int)param_1 + 10) == 0) && ((undefined4 *)*piVar4 == param_1)) &&
         (piVar4[5] == *(int *)(DAT_006d9498 + 0x54))) break;
      uVar6 = uVar6 + 1;
      piVar4 = piVar4 + 0x27;
      if (uVar2 <= uVar6) {
        return 0;
      }
    }
  }
  return 0;
}

