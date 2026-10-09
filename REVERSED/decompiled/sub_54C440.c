/* sub_54C440 @ 0054c440   95 bytes */

void sub_54C440(void)

{
  int iVar1;
  
  for (iVar1 = DAT_006d9e38; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    if ((*(uint *)(iVar1 + 0xec) & 0x18000) != 0x18000) {
      if ((((*(uint *)(iVar1 + 0xec) & 0x4000) == 0) || ((*(uint *)(iVar1 + 0xe8) & 0x800) != 0)) ||
         (DAT_006d9e1c == 0)) {
        *(undefined4 *)(iVar1 + 0x148) = 0x200000;
        *(undefined4 *)(iVar1 + 0x1c) = 0;
      }
      else {
        sub_54C3F0(iVar1);
      }
    }
  }
  return;
}

