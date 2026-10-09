/* sub_43B8A0 @ 0043b8a0   114 bytes */

undefined4 sub_43B8A0(void)

{
  int iVar1;
  
  if (DAT_006d91b8 == (int *)0x0) {
    return 0;
  }
  (**(code **)(*DAT_006d91b8 + 0x94))(DAT_006d91b8,0);
  (**(code **)(*DAT_00582ce4 + 0x14))(DAT_00582ce4,0,DAT_006d91b8,0,0x1000000,0);
  iVar1 = (**(code **)(*DAT_00582ce4 + 0x34))(DAT_00582ce4,2);
  while (iVar1 == -0x7789fde4) {
    iVar1 = (**(code **)(*DAT_00582ce4 + 0x34))(DAT_00582ce4,2);
  }
  (**(code **)(*DAT_006d91b8 + 0x98))(DAT_006d91b8,0);
  return 1;
}

