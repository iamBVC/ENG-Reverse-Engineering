/* sub_439280 @ 00439280   176 bytes */

void sub_439280(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int *piStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  int iStack_80;
  undefined4 uStack_7c;
  undefined4 *puStack_78;
  undefined4 local_64 [20];
  undefined4 local_14;
  
  puStack_78 = local_64;
  uStack_7c = 0x1000400;
  iStack_80 = 0;
  local_64[0] = 100;
  local_14 = 0;
  iStack_84 = 0;
  uStack_88 = 0;
  piStack_8c = DAT_00582ce4;
  (**(code **)(*DAT_00582ce4 + 0x14))();
  if (DAT_005833e1 != '\0') {
    uVar1 = DAT_00583378 * DAT_00583374;
    puVar3 = DAT_005832f0;
    for (uVar2 = (uVar1 & 0x7fffffff) >> 1; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = 0xffffffff;
      puVar3 = puVar3 + 1;
    }
    for (uVar1 = uVar1 * 2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar3 = 0xff;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
    return;
  }
  if (DAT_005833e4._1_1_ != '\0') {
    iStack_84 = DAT_00583374;
    iStack_80 = DAT_00583378;
    piStack_8c = (int *)0x0;
    uStack_88 = 0;
    (**(code **)(*DAT_00582cd8 + 0x50))(DAT_00582cd8,1,&piStack_8c,2,0,0x3f800000,0);
  }
  return;
}

