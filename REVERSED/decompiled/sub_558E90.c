/* sub_558E90 @ 00558e90   245 bytes */

void sub_558E90(void)

{
  int iVar1;
  uint local_8;
  void *local_4;
  
  DAT_006da31c = 0;
  DAT_006da324 = (void *)0x0;
  DAT_006da33c = (void *)0x0;
  iVar1 = sub_415690(&DAT_00570348,s_DEFANIM_WAD_0057253c);
  if (iVar1 != 0) {
    iVar1 = sub_562AEE(iVar1,&DAT_00570350);
    if (iVar1 != 0) {
      sub_5629E6(&local_8,4,1,iVar1);
      sub_5629E6(&DAT_006da31c,4,1,iVar1);
      sub_5629E6(&local_8,4,1,iVar1);
      DAT_006da324 = operator_new(DAT_006da31c * 4);
      DAT_006da33c = operator_new(local_8);
      sub_5629E6(DAT_006da33c,1,local_8,iVar1);
      local_4 = DAT_006da33c;
      iVar1 = 0;
      if (0 < DAT_006da31c) {
        do {
          sub_41F8B0(&local_4,1,(void *)((int)DAT_006da324 + iVar1 * 4));
          iVar1 = iVar1 + 1;
        } while (iVar1 < DAT_006da31c);
      }
    }
  }
  return;
}

