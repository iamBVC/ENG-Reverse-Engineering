/* sub_546240 @ 00546240   180 bytes */

void sub_546240(int param_1,char param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  
  if (DAT_006d9498 != 0) {
    uVar2 = *(uint *)(DAT_006d9498 + 0x48);
    iVar3 = *(int *)(DAT_006d9498 + 0x44);
    if ((param_2 < '\0') || (uVar4 = (uint)param_2, uVar2 <= uVar4)) {
      cVar5 = '\0';
      if (uVar2 != 0) {
        uVar4 = 0;
        do {
          iVar1 = iVar3 + uVar4 * 0x9c;
          if (((*(int *)(iVar3 + 4 + uVar4 * 0x9c) != 0) && (*(int *)(iVar1 + 0x20) == param_1)) &&
             (*(undefined4 *)(iVar1 + 0x20) = 0, *(short *)(iVar1 + 0x78) != 0)) {
            sub_5489F0(DAT_006d9498 + 0x10,iVar1);
          }
          cVar5 = cVar5 + '\x01';
          uVar4 = (uint)cVar5;
        } while (uVar4 < uVar2);
      }
    }
    else {
      iVar1 = iVar3 + uVar4 * 0x9c;
      if ((*(int *)(iVar3 + 4 + uVar4 * 0x9c) != 0) && (*(int *)(iVar1 + 0x20) == param_1)) {
        *(undefined4 *)(iVar1 + 0x20) = 0;
        sub_5489F0(DAT_006d9498 + 0x10,iVar1);
        return;
      }
    }
  }
  return;
}

