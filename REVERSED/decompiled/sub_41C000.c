/* sub_41C000 @ 0041c000   66 bytes */

void sub_41C000(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  do {
    iVar1 = *param_1;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x68) == 2) {
        sub_41BB90(iVar1,param_2);
      }
      if (*(int *)(*param_1 + 0x68) == 1) {
        sub_41BB90(*param_1,param_3);
      }
    }
    param_1 = (int *)param_1[1];
  } while (param_1 != (int *)0x0);
  return;
}

