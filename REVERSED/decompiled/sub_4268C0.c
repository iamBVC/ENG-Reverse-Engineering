/* sub_4268C0 @ 004268c0   702 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4268C0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    DAT_00584e70 = 0x5000;
    sub_426890();
    sub_426500();
    DAT_005fcf90 = DAT_00584e64;
    puVar2 = &DAT_005fd054;
    for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    DAT_005fcf84 = DAT_00584e60 >> 0xc;
    DAT_005fcf8c = 0;
    DAT_005fcf74 = 0;
    DAT_005fcf78 = 0;
    DAT_005fcf80 = 0;
    DAT_005fcf7c = 0;
    DAT_005fcf88 = DAT_00584e70;
    _DAT_005fcf94 = 0;
    DAT_005fcf98 = 0;
    DAT_005fd03c = 0;
    _DAT_005fd040 = 0;
    DAT_005fd044 = 0;
    DAT_006d9e74 = 0;
    DAT_006da300 = 0;
    DAT_006da2f8 = 0;
    _DAT_00573410 = 0;
    DAT_00573413 = 0;
    DAT_00573428 = 0xffffffe0;
    _DAT_00573450 = 0;
    DAT_00573453 = 0;
    _DAT_00573468 = 0xffffffe0;
    _DAT_00573650 = 0;
    DAT_00573653 = 0;
    DAT_00573668 = 0xffffffe0;
    _DAT_00573610 = 0;
    DAT_00573613 = 0;
    DAT_00573628 = 0xffffffe0;
    _DAT_00573690 = 0;
    DAT_00573693 = 0;
    DAT_005736a8 = 0xffffffe0;
    _DAT_00573710 = 0;
    DAT_00573713 = 0;
    DAT_00573728 = 0xffffffe0;
    _DAT_005736d0 = 0;
    DAT_005736d3 = 0;
    DAT_005736e8 = 0xffffffe0;
    _DAT_00573790 = 0;
    DAT_00573793 = 0;
    DAT_005737a8 = 0xffffffe0;
    DAT_006da2dc = 0;
    DAT_006da2e0 = 0x3f000;
    DAT_0057341c = 0x33;
    _DAT_0057345c = 0x40;
    sub_426870(&DAT_00573410);
    sub_426870(&DAT_00573450);
    sub_426870(&DAT_00573610);
    sub_426870(&DAT_00573690);
    sub_426870(&DAT_005736d0);
    sub_426870(&DAT_00573710);
    sub_426870(&DAT_00573490);
    sub_426870(&DAT_005734d0);
    sub_426870(&DAT_00573510);
    sub_426870(&DAT_00573550);
    sub_426870(&DAT_00573590);
    sub_426870(&DAT_005735d0);
    sub_426870(&DAT_00573750);
    sub_426870(&DAT_00573790);
    if ((&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] == 0) {
      _DAT_00573650 = 0;
    }
    else if ((DAT_006d94e8 == '\0') && (DAT_005fd090 == 0)) {
      sub_426870(&DAT_00573650);
    }
    if (DAT_00584ff4 == 0) {
      _DAT_00573610 = 0;
    }
    else if ((DAT_006d94e8 == '\0') && (DAT_005fd090 == 0)) {
      sub_426870(&DAT_00573610);
    }
    if (DAT_00584e60 == 0) {
      _DAT_00573690 = 0;
    }
    else if ((DAT_006d94e8 == '\0') && (DAT_005fd090 == 0)) {
      sub_426870(&DAT_00573690);
    }
    if ((DAT_00584ffc & 0xfffff000) == 0) {
      _DAT_00573710 = 0;
    }
    else if ((DAT_006d94e8 == '\0') && (DAT_005fd090 == 0)) {
      sub_426870(&DAT_00573710);
      return;
    }
  }
  return;
}

