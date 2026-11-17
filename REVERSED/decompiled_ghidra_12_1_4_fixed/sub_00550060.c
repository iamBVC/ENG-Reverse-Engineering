/* sub_550060 @ 00550060   98 bytes */

void sub_550060(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = sub_54BC00(param_1);
  iVar1 = *param_1;
  iVar6 = *(int *)(iVar1 + 4 + param_2 * 4);
  piVar2 = (int *)(iVar1 + 4 + param_2 * 4);
  if (iVar6 != 0) {
    while( true ) {
      piVar4 = piVar2 + 2;
      if ((piVar2[1] & 0xffffU) == 0x44) {
        iVar5 = (int)(short)((uint)piVar2[1] >> 0x10);
      }
      else {
        iVar5 = *piVar4;
        piVar4 = piVar2 + 3;
      }
      if (iVar3 == iVar5) break;
      iVar6 = iVar6 + -1;
      piVar2 = piVar4;
      if (iVar6 == 0) {
        return;
      }
    }
    *param_1 = iVar1 + *piVar4 * 4;
  }
  return;
}

