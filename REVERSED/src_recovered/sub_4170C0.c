/* Original 004170C0: pop the most recently saved menu state. */
undefined4 sub_4170C0(void)
{
  DAT_00583910 = DAT_00583910 - 1;
  return DAT_005839d4[DAT_00583910];
}
