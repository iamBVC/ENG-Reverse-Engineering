/* Sound setup at 00545030: preserve contiguous argument records. */
int sub_545030(void)
{
  unsigned int settings[8] = {0, 24, 0, 5, 3, 0, 0, 30};
  unsigned int pool[4] = {64, 256, 30, 0x4000};

  sub_545270();
  DAT_006d9494 = (int)operator_new(0x104);
  if (DAT_006d9494 == 0) return 0;
  sub_546EA0(DAT_006d9494, settings);
  if (DAT_006d9490 == 0) return 0;

  DAT_006d9498 = (int)operator_new(0x6c);
  if (DAT_006d9498 == 0) return 0;
  sub_548650(DAT_006d9498, pool);
  pool[0] = 16;
  pool[1] = 48;
  pool[2] = 30;
  /* The original changes only the low word of the final DWORD. */
  pool[3] = (pool[3] & 0xffff0000) | 16;
  DAT_006d949c = (int)operator_new(0xa8);
  if (DAT_006d949c == 0) return 0;
  sub_548CF0(DAT_006d949c, pool);
  sub_545F90((unsigned short)DAT_005834e0, 128);
  sub_546000((unsigned short)DAT_005834ec, 128);
  sub_545140();
  return 1;
}
