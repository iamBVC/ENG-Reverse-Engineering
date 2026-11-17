/* 00418420: three calls to 00424900, each with six cdecl arguments. */
undefined4 sub_418420(void)
{
  float first = DAT_00573d38;
  float second = DAT_00573d40;

  sub_424900(0x55, 0x1b0, 0, DAT_00573d3c, 0.1f, 1.0f);
  sub_424900(0x6b, 0x1b0, 0, first, 0.0f, 0.9f);
  sub_424900(0x81, 0x1b0, 0, second, 0.2f, 1.8f);
  return 0;
}

