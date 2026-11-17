/* sub_4280C0 @ 004280c0   279 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4280C0(void)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined2 *puVar6;
  
  if (DAT_006d94dc != (HGLOBAL)0x0) {
    GlobalFree(DAT_006d94dc);
  }
  DAT_006d94dc = GlobalAlloc(0x40,DAT_006da328 * 0x48);
  uVar5 = 0;
  DAT_006d9bdc = 0;
  DAT_006d9bd8 = (undefined4 *)0x0;
  puVar1 = DAT_006d94dc;
  puVar4 = (undefined4 *)0x0;
  if (DAT_006da328 != 0) {
    do {
      DAT_006d9bd8 = puVar1;
      *DAT_006d9bd8 = puVar4;
      DAT_006d9bd8[1] = 0;
      uVar5 = uVar5 + 1;
      puVar1 = DAT_006d9bd8 + 0x12;
      puVar4 = DAT_006d9bd8;
    } while (uVar5 < DAT_006da328);
  }
  uVar5 = sub_563C89();
  uVar3 = sub_563C89();
  _DAT_006d9bc8 = (uVar5 & 0x1f) - (uVar3 & 0x1f);
  uVar5 = sub_563C89();
  uVar3 = sub_563C89();
  _DAT_006d9bcc = (uVar5 & 0x1f) - (uVar3 & 0x1f);
  sub_428D60();
  sub_427FB0();
  DAT_006d9bf0 = 0;
  DAT_006d9be4 = 0;
  DAT_006d94d0 = 0;
  DAT_006d94d4 = 0x40;
  if (DAT_006d94b8 != (HGLOBAL)0x0) {
    GlobalFree(DAT_006d94b8);
  }
  DAT_006d94b8 = GlobalAlloc(0x40,DAT_006da320 << 5);
  sub_4284A0();
  DAT_005ff034 = &LAB_004284d0;
  DAT_005ff038 = &LAB_004321e0;
  puVar6 = (undefined2 *)&DAT_005fef30;
  do {
    uVar2 = sub_563C89();
    *puVar6 = uVar2;
    puVar6 = puVar6 + 1;
  } while ((int)puVar6 < 0x5fef70);
  return;
}

