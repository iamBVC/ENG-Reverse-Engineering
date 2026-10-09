/* sub_54BAD0 @ 0054bad0   157 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_54BAD0(void)

{
  int local_8;
  int local_4;
  
  if (DAT_006d9e28 != 0) {
    DAT_006d9d20 = *(undefined4 *)(DAT_006d9e28 + 0x30);
    DAT_006d9d24 = *(undefined4 *)(DAT_006d9e28 + 0x34);
    DAT_006d9d28 = *(undefined4 *)(DAT_006d9e28 + 0x38);
    DAT_006d9d2c = *(undefined4 *)(DAT_006d9e28 + 0x3c);
    sub_404DB0(&DAT_006d9d80,&DAT_006d9d20,&local_8,&local_4);
    DAT_005790a4 = local_8 >> 0xc;
    _DAT_005790a0 = local_4 >> 0xc;
    DAT_005790b0 = DAT_006d9d20;
    DAT_005790b4 = DAT_006d9d24;
    DAT_005790b8 = DAT_006d9d28;
    _DAT_005790bc = DAT_006d9d2c;
  }
  return;
}

