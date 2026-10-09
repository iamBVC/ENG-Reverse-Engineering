/* sub_40E830 @ 0040e830   76 bytes */

undefined4 sub_40E830(int *param_1,char param_2,char param_3)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    iVar1 = (**(code **)(*param_1 + 0x34))
                      (param_1,DAT_00582a70,
                       2 - (param_2 != '\0') | (-(uint)(param_3 != '\0') & 0xfffffffc) + 8);
    if (iVar1 != 0) {
      return 0;
    }
    iVar1 = (**(code **)(*param_1 + 0x1c))(param_1);
    if (iVar1 != 0) {
      return 0;
    }
  }
  return 1;
}

