/* sub_41F590 @ 0041f590   99 bytes */

void sub_41F590(int *param_1)

{
  int iVar1;
  
  iVar1 = sub_415690(s_movies_00572ab8,param_1);
  if (iVar1 != 0) {
    sub_545270();
    iVar1 = sub_41EF70(iVar1,DAT_00582ccc,&param_1);
    if (-1 < iVar1) {
      sub_41F0C0(DAT_00582ccc,DAT_00582cdc,param_1);
      (**(code **)(*param_1 + 8))(param_1);
    }
    sub_545030();
  }
  return;
}

