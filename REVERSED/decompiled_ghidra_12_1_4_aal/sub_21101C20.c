/* sub_21101C20 @ 21101c20   279 bytes */

undefined4 sub_21101C20(int *param_1,LPCSTR param_2,undefined4 param_3,undefined4 *param_4)

{
  int *piVar1;
  undefined4 *puVar2;
  LPSTR lpString1;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 *puVar7;
  bool bVar8;
  
  if (param_4 != (undefined4 *)0x0) {
    for (piVar1 = (int *)*param_4; piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
      iVar4 = 4;
      if (param_1 == (int *)0x0) {
        bVar8 = true;
        piVar6 = &DAT_21112740;
        piVar5 = piVar1;
        do {
          piVar5 = piVar5 + 1;
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar8 = *piVar5 == *piVar6;
          piVar6 = piVar6 + 1;
        } while (bVar8);
        if (bVar8) {
LAB_21101c63:
          if (piVar1 != (int *)0x0) {
            return 0;
          }
          break;
        }
      }
      else {
        bVar8 = true;
        piVar6 = param_1;
        piVar5 = piVar1;
        do {
          piVar5 = piVar5 + 1;
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar8 = *piVar5 == *piVar6;
          piVar6 = piVar6 + 1;
        } while (bVar8);
        if (bVar8) goto LAB_21101c63;
      }
    }
  }
  puVar2 = operator_new(0x1c);
  puVar2[5] = 0;
  *puVar2 = 0;
  puVar7 = puVar2;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  if (param_1 == (int *)0x0) {
    puVar2[1] = DAT_21112740;
    puVar2[2] = DAT_21112744;
    puVar2[3] = DAT_21112748;
    iVar4 = DAT_2111274c;
  }
  else {
    puVar2[1] = *param_1;
    puVar2[2] = param_1[1];
    puVar2[3] = param_1[2];
    iVar4 = param_1[3];
  }
  puVar2[4] = iVar4;
  iVar4 = lstrlenA(param_2);
  lpString1 = operator_new(iVar4 + 1);
  puVar2[6] = lpString1;
  if (lpString1 == (LPSTR)0x0) {
    return 1;
  }
  lstrcpyA(lpString1,param_2);
  puVar7 = (undefined4 *)*param_4;
  if ((undefined4 *)*param_4 != (undefined4 *)0x0) {
    do {
      puVar3 = puVar7;
      puVar7 = (undefined4 *)*puVar3;
    } while ((undefined4 *)*puVar3 != (undefined4 *)0x0);
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = puVar2;
      return 1;
    }
  }
  *param_4 = puVar2;
  return 1;
}

