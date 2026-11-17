/* sub_4134F0 @ 004134f0   31 bytes */

int sub_4134F0(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  bool bVar3;
  
  iVar1 = 4;
  bVar3 = true;
  piVar2 = *(int **)(param_1 + 0xc);
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar3 = *piVar2 == *param_2;
    piVar2 = piVar2 + 1;
    param_2 = param_2 + 1;
  } while (bVar3);
  return bVar3 - 1;
}

