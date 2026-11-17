/* sub_4196D0 @ 004196d0   216 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_4196D0(void)

{
  static unsigned int traced;
  int trace = traced++ < 3;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(PTR_DAT_005724dc + 0x18);
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = (undefined4 *)(PTR_DAT_005724dc + 0x118);
  for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (trace) fprintf(stderr, "[frame] update begin state=%d steps=%d fade=%p target=%d/%d/%d\n", DAT_005846e4, DAT_005724d4, DAT_0058372c, DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_40F060(PTR_DAT_005724dc + 0x18,PTR_DAT_005724dc + 0x118);
  if (trace) fprintf(stderr, "[frame] input poll complete target=%d/%d/%d\n", DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  iVar2 = 0;
  DAT_00573d20 = 1;
  if (0 < DAT_005724d4) {
    do {
      sub_415340();
      iVar2 = iVar2 + 1;
    } while (iVar2 < DAT_005724d4);
  }
  if (trace) fprintf(stderr, "[frame] fade update complete target=%d/%d/%d\n", DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  sub_545C00();
  if (trace) fprintf(stderr, "[frame] audio update complete target=%d/%d/%d\n", DAT_006d9d80, DAT_006d9d84, DAT_006d9d88);
  if (trace) fprintf(stderr, "[frame] state update call %p\n", (&PTR_sub_426500_00579050)[DAT_005846e4]);
  (*(code *)(&PTR_sub_426500_00579050)[DAT_005846e4])();
  if (trace) fprintf(stderr, "[frame] state update complete\n");
  uVar1 = (*(code *)(&PTR_sub_426860_00578f28)[DAT_005846e4])();
  if (trace) fprintf(stderr, "[frame] state dispatch complete result=%u\n", uVar1);
  if (DAT_005846dc != 0) {
    iVar2 = sub_414FB0();
    if ((iVar2 != 0) || (DAT_0058372c == 0)) {
      sub_415390(2);
      _DAT_005846f8 = DAT_00584654;
      DAT_005846e4 = DAT_005846d8;
      PTR_DAT_00571f54[0x54] = 1;
      DAT_005846dc = 0;
    }
  }
  return uVar1;
}
