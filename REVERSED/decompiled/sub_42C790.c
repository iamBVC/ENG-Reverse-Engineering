/* sub_42C790 @ 0042c790   144 bytes */

void sub_42C790(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (*DAT_00584648 != 0) {
    do {
      sub_42C680(uVar1,*(undefined2 *)
                        (DAT_005846ec + 0x6c + *(int *)(DAT_00584648[0x13] + uVar1 * 4) * 0x84));
      uVar1 = uVar1 + 1;
    } while (uVar1 < *DAT_00584648);
  }
  if (((DAT_006da330 & 0x10000000) != 0) && (uVar1 = 0, DAT_00584648[8] != 0)) {
    iVar2 = 0;
    do {
      sub_42C680(uVar1 + *DAT_00584648,
                 *(undefined2 *)
                  (DAT_005846ec + 0x6c + *(int *)(DAT_00584648[0x14] + 0x10 + iVar2) * 0x84));
      uVar1 = uVar1 + 1;
      iVar2 = iVar2 + 0x18;
    } while (uVar1 < DAT_00584648[8]);
  }
  return;
}

