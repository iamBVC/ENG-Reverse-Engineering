/* sub_42AB50 @ 0042ab50   245 bytes */

void sub_42AB50(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  uVar2 = param_3;
  DAT_006d9dbc = (int *)sub_41EF00(param_3);
  sub_415A90(param_2,DAT_006d9dbc,uVar2);
  iVar5 = *DAT_006d9dbc;
  param_3 = DAT_006d9dbc + 1;
  *(int *)(param_1 + 4) = iVar5 + -1;
  while (iVar5 != 0) {
    sub_41F770(&param_3,1,local_8);
    iVar5 = *(int *)(param_1 + 4);
    *(int *)(param_1 + 4) = iVar5 + -1;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  iVar5 = *param_3;
  param_3 = param_3 + 1;
  for (; iVar5 != 0; iVar5 = iVar5 + -1) {
    sub_41F8B0(&param_3,1,local_4);
  }
  if ((DAT_006da330 & 0x100) != 0) {
    piVar1 = param_3 + 1;
    for (iVar5 = *param_3; iVar5 != 0; iVar5 = iVar5 + -1) {
      piVar3 = piVar1 + 4;
      if ((piVar1[1] & 0x1fffffffU) == 0) {
        piVar4 = (int *)0x0;
        param_3 = piVar3;
      }
      else {
        param_3 = piVar3 + piVar1[1] * 2;
        piVar4 = piVar3;
      }
      piVar1[2] = (int)piVar4;
      sub_41F770(&param_3,piVar1[1],piVar1 + 3);
      piVar1 = param_3;
    }
  }
  return;
}

