/* sub_40F290 @ 0040f290   66 bytes */

void sub_40F290(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 unaff_retaddr;
  
  DAT_00582cc0 = param_2;
  DAT_005714d4 = param_3;
  (**(code **)(**(int **)(param_1 + 8) + 0x10))(*(int **)(param_1 + 8),&LAB_0040f2e0,param_1,3);
  sub_40F310(*(undefined4 *)(param_1 + 8),5,0,0,unaff_retaddr);
  return;
}

