/* sub_419A60 @ 00419a60   354 bytes */

undefined4 sub_419A60(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined1 local_170 [48];
  undefined1 local_140 [8];
  undefined1 local_138 [48];
  undefined1 local_108 [4];
  undefined1 local_104 [260];
  
  if (param_1 == (int *)0x0) {
    sub_562717(local_104,s_InputDevice__s_00572234,&DAT_00582b50);
    iVar2 = 0;
    do {
      sub_562717(local_170 + iVar2,&DAT_0057224c,*(undefined4 *)((int)&DAT_00584758 + iVar2));
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x38);
    sub_562717(local_138,&DAT_00572244,*(undefined1 *)(DAT_005fcf70 + 0xb));
    sub_405800(local_104,local_170,0);
    return 1;
  }
  sub_562717(local_104,s_InputDevice__s__s_00572278,param_1 + 0x34,param_1 + 0x20);
  sub_562717(local_170,s_X1__08X_Y1__08X_X2__08X_Y2__08X_00572254,param_1[0x17],param_1[0x18],
             param_1[0x19],param_1[0x1a]);
  iVar2 = 0;
  do {
    if (0xffff < *(int *)(iVar2 + param_1[0x1c])) {
      return 0;
    }
    sub_562717(local_140 + iVar2,&DAT_0057224c,*(int *)(iVar2 + param_1[0x1c]));
    iVar2 = iVar2 + 4;
  } while (iVar2 < 0x38);
  iVar2 = 1;
  piVar1 = DAT_00582260;
  while ((((int *)*piVar1 != (int *)0x0 || (piVar1[1] == 0)) && (piVar1 != param_1))) {
    iVar2 = iVar2 + 1;
    piVar1 = (int *)*piVar1;
  }
  sub_562717(local_108,&DAT_00572244,*(undefined1 *)(DAT_005fcf70 + 0xb + iVar2 * 0xc));
  sub_405800(local_104,local_170,0);
  return 1;
}

