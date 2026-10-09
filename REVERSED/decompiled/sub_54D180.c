/* sub_54D180 @ 0054d180   77 bytes */

void sub_54D180(int *param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  bVar1 = *(byte *)(param_1 + 0x3a);
  while ((bVar1 & 0x12) == 0) {
    uVar2 = *(uint *)*param_1;
    *param_1 = (int)((uint *)*param_1 + 1);
    uVar3 = uVar2 & 0xffff;
    if (uVar3 < 0x45) {
      (*(code *)(&PTR_sub_426500_005796bc)[uVar3])(param_1,(int)(short)(uVar2 >> 0x10));
    }
    else {
      (**(code **)(s_EULOGY_DAT_00578ff0 + uVar3 * 4 + 4))(param_1);
    }
    bVar1 = *(byte *)(param_1 + 0x3a);
  }
  return;
}

