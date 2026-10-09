/* sub_439160 @ 00439160   276 bytes */

void sub_439160(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 local_74;
  undefined4 local_70;
  int local_6c;
  int local_68;
  undefined4 local_64 [20];
  undefined4 local_14;
  
  iVar1 = sub_43B8A0();
  uVar2 = -(uint)(iVar1 != 0) & 0x7fffbffb;
  if (DAT_005833e1 != '\0') {
    if (uVar2 != 0x7fffbffb) {
      local_64[0] = 100;
      local_14 = sub_40C250(DAT_006d7c74,&DAT_005833c0);
      (**(code **)(*DAT_00582ce4 + 0x14))(DAT_00582ce4,0,0,0,0x1000600,local_64);
    }
    uVar2 = DAT_00583378 * DAT_00583374;
    puVar4 = DAT_005832f0;
    for (uVar3 = (uVar2 & 0x7fffffff) >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = 0xffffffff;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = uVar2 * 2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar4 = 0xff;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    return;
  }
  local_74 = 0;
  local_6c = DAT_00583374;
  local_70 = 0;
  local_68 = DAT_00583378;
  if (uVar2 != 0x7fffbffb) {
    (**(code **)(*DAT_00582cd8 + 0x50))
              (DAT_00582cd8,1,&local_74,(-(DAT_005833e4._1_1_ != '\0') & 2U) + 1,DAT_006d7c74,
               0x3f800000,0);
    return;
  }
  if (DAT_005833e4._1_1_ != '\0') {
    (**(code **)(*DAT_00582cd8 + 0x50))(DAT_00582cd8,1,&local_74,2,DAT_006d7c74,0x3f800000,0);
  }
  return;
}

