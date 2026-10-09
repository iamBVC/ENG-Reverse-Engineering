/* sub_413DA0 @ 00413da0   362 bytes */

undefined4 __thiscall sub_413DA0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  undefined1 local_3c [4];
  char *local_38;
  uint local_34;
  undefined1 local_2c [4];
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0056d878;
  local_c = ExceptionList;
  pcVar6 = *(char **)(param_1 + 4);
  local_3c[0] = (undefined1)param_2;
  ExceptionList = &local_c;
  sub_413BF0(0);
  uVar4 = 0xffffffff;
  pcVar7 = pcVar6;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4 - 1;
  cVar1 = sub_413F10(uVar4,1);
  if (cVar1 != '\0') {
    pcVar7 = local_38;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    local_38[uVar4] = '\0';
    local_34 = uVar4;
  }
  local_4 = 0;
  uVar2 = sub_414030(local_1c,local_3c,&DAT_00571cf8);
  local_4._0_1_ = 1;
  uVar3 = sub_406740(*(undefined4 *)(param_1 + 8));
  uVar2 = sub_414030(local_2c,uVar2,uVar3);
  local_4 = CONCAT31(local_4._1_3_,2);
  sub_414030(param_2,uVar2,&DAT_00571cf4);
  if (local_28 != 0) {
    cVar1 = *(char *)(local_28 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      sub_562941((char *)(local_28 + -1));
    }
    else {
      *(char *)(local_28 + -1) = cVar1 + -1;
    }
  }
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  if (local_18 != 0) {
    cVar1 = *(char *)(local_18 + -1);
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      sub_562941((char *)(local_18 + -1));
    }
    else {
      *(char *)(local_18 + -1) = cVar1 + -1;
    }
  }
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  if (local_38 != (char *)0x0) {
    cVar1 = local_38[-1];
    if ((cVar1 == '\0') || (cVar1 == -1)) {
      sub_562941(local_38 + -1);
    }
    else {
      local_38[-1] = cVar1 + -1;
    }
  }
  ExceptionList = local_c;
  return param_2;
}

