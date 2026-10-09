/* sub_42C460 @ 0042c460   62 bytes */

void sub_42C460(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x5c)) {
    do {
      sub_41BCC0(*(undefined4 *)(*(int *)(param_1 + 0x60) + iVar1 * 4));
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x5c));
  }
  sub_41BCC0(DAT_00581164);
  return;
}

