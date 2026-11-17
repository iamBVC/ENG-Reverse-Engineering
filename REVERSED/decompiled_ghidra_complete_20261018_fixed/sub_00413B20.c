/* sub_413B20 @ 00413b20   202 bytes */

undefined1 * __thiscall sub_413B20(int param_1,undefined1 *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  pcVar5 = *(char **)(param_1 + 4);
  *param_2 = param_2._0_1_;
  uVar3 = 0xffffffff;
  *(undefined4 *)(param_2 + 4) = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  *(undefined4 *)(param_2 + 0xc) = 0;
  pcVar6 = pcVar5;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3 - 1;
  if (0xfffffffd < uVar3) {
    sub_56D0A0();
  }
  iVar2 = *(int *)(param_2 + 4);
  if (((iVar2 == 0) || (cVar1 = *(char *)(iVar2 + -1), cVar1 == '\0')) || (cVar1 == -1)) {
    if (uVar3 == 0) {
      sub_413BF0(1);
      return param_2;
    }
    if ((*(uint *)(param_2 + 0xc) < 0x20) && (uVar3 <= *(uint *)(param_2 + 0xc))) goto LAB_00413bbf;
    sub_413BF0(1);
  }
  else if (uVar3 == 0) {
    *(char *)(iVar2 + -1) = cVar1 + -1;
    sub_413BF0(0);
    return param_2;
  }
  sub_413C40(uVar3);
LAB_00413bbf:
  pcVar6 = *(char **)(param_2 + 4);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(uint *)(param_2 + 8) = uVar3;
  *(undefined1 *)(*(int *)(param_2 + 4) + uVar3) = 0;
  return param_2;
}

