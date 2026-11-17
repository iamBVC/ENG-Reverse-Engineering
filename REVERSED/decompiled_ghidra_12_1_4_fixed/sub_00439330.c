/* sub_439330 @ 00439330   338 bytes */

void sub_439330(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 uStack_74;
  undefined4 uStack_70;
  int iStack_6c;
  int iStack_68;
  undefined4 local_64 [20];
  undefined4 local_14;
  
  if (param_1 == (int *)0x0) {
    iVar1 = -0x7fffbffb;
  }
  else {
    (**(code **)(*param_1 + 0x94))(param_1,0);
    iVar1 = (**(code **)(*DAT_00582ce4 + 0x14))(DAT_00582ce4,0,param_1,0,0x1000000,0);
    iVar2 = (**(code **)(*DAT_00582ce4 + 0x34))(DAT_00582ce4,2);
    while (iVar2 == -0x7789fde4) {
      iVar2 = (**(code **)(*DAT_00582ce4 + 0x34))(DAT_00582ce4,2);
    }
    (**(code **)(*param_1 + 0x98))(param_1,0);
  }
  if (DAT_005833e1 == '\0') {
    uStack_74 = 0;
    iStack_6c = DAT_00583374;
    uStack_70 = 0;
    iStack_68 = DAT_00583378;
    if (iVar1 == 0) {
      if (DAT_005833e4._1_1_ != '\0') {
        (**(code **)(*DAT_00582cd8 + 0x50))(DAT_00582cd8,1,&uStack_74,2,0,0x3f800000,0);
      }
      return;
    }
    (**(code **)(*DAT_00582cd8 + 0x50))
              (DAT_00582cd8,1,&uStack_74,(-(DAT_005833e4._1_1_ != '\0') & 2U) + 1,0,0x3f800000,0);
    return;
  }
  if (iVar1 != 0) {
    local_64[0] = 100;
    local_14 = 0;
    (**(code **)(*DAT_00582ce4 + 0x14))(DAT_00582ce4,0,0,0,0x1000600,local_64);
  }
  uVar3 = DAT_00583378 * DAT_00583374;
  puVar5 = DAT_005832f0;
  for (uVar4 = (uVar3 & 0x7fffffff) >> 1; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar5 = 0xffffffff;
    puVar5 = puVar5 + 1;
  }
  for (uVar3 = uVar3 * 2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar5 = 0xff;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  return;
}

