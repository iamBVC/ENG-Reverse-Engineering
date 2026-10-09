/* sub_547D70 @ 00547d70   122 bytes */

void sub_547D70(int *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    sub_546E30(iVar1);
    *(undefined4 *)(iVar1 + 0xc) = *param_2;
    *(undefined4 *)(iVar1 + 0x10) = param_2[1];
    *(undefined4 *)(iVar1 + 0x14) = param_2[2];
    *(undefined4 *)(iVar1 + 0x18) = param_2[3];
    piVar3 = param_1 + 2;
    while (piVar3 != (int *)0x0) {
      piVar2 = (int *)*piVar3;
      if (piVar2 == (int *)0x0) {
        *(int *)(iVar1 + 8) = param_3;
        break;
      }
      if (param_3 < piVar2[2]) {
        *(int *)(iVar1 + 8) = param_3;
        piVar2[2] = piVar2[2] - param_3;
        break;
      }
      param_3 = param_3 - piVar2[2];
      piVar3 = piVar2;
    }
    sub_546E10(iVar1,piVar3);
    param_1[5] = param_1[5] + 1;
  }
  return;
}

