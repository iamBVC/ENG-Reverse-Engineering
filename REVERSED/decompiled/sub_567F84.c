/* sub_567F84 @ 00567f84   70 bytes */

undefined4 sub_567F84(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)*param_1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    uVar2 = sub_567E4C();
    return uVar2;
  }
  if ((DAT_006da430 != (code *)0x0) && (iVar3 = sub_56AB40(DAT_006da430), iVar3 != 0)) {
    uVar2 = (*DAT_006da430)(param_1);
    return uVar2;
  }
  return 0;
}

