/* sub_41D2C0 @ 0041d2c0   101 bytes */

void sub_41D2C0(undefined4 param_1,uint param_2)

{
  DWORD DVar1;
  DWORD DVar2;
  uint uVar3;
  
  sub_43B790(param_1);
  sub_43B8A0();
  sub_439490();
  sub_43C940();
  DVar1 = timeGetTime();
  DVar2 = timeGetTime();
  uVar3 = DVar2 - DVar1;
  while ((uVar3 <= param_2 &&
         (sub_40F060(PTR_DAT_005724dc + 0x18,PTR_DAT_005724dc + 0x118),
         (PTR_DAT_005724dc[0x19] & 0x80) == 0))) {
    DVar2 = timeGetTime();
    uVar3 = DVar2 - DVar1;
  }
  return;
}

