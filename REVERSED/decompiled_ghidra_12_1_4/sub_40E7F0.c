/* sub_40E7F0 @ 0040e7f0   61 bytes */

undefined4 sub_40E7F0(char param_1)

{
  int iVar1;
  
  if (DAT_00582a80 != (int *)0x0) {
    iVar1 = (**(code **)(*DAT_00582a80 + 0x34))
                      (DAT_00582a80,DAT_00582a70,(-(param_1 != '\0') & 0xcU) + 8 | 2);
    if (iVar1 != 0) {
      return 0;
    }
    (**(code **)(*DAT_00582a80 + 0x1c))(DAT_00582a80);
  }
  return 1;
}

