/* sub_568953 @ 00568953   103 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_568953(uint param_1)

{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  DAT_006da368 = param_1;
  puVar1 = &DAT_0057cd78;
  do {
    if (param_1 == *puVar1) {
      _DAT_006da364 = *(undefined4 *)(iVar2 * 8 + 0x57cd7c);
      return;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < 0x57cee0);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    _DAT_006da364 = 0xd;
    return;
  }
  if ((param_1 < 0xbc) || (_DAT_006da364 = 8, 0xca < param_1)) {
    _DAT_006da364 = 0x16;
  }
  return;
}

